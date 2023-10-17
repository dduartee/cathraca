//-------------------------------------------------------------------------------------------------------------------------
//Biblioteca e parametros do sensor biometrico

#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // pinos de leitura do sensor biometrico

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

//-------------------------------------------------------------------------------------------------------------------------

#include <LiquidCrystal.h>

#define RS 12
#define EN 11
#define D4 4
#define D5 5
#define D6 6
#define D7 7
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

#include <Servo.h>
Servo servo;

const int pinoBuzzer = 8;

void setup()
{
  Serial.begin(9600); //inicia o monitor serial do arduino, com taxa de 9600

  finger.begin(57600); // defina a taxa de dados para a porta serial do sensor biometrico

  lcd.begin(16, 2);
  lcd.clear();

  servo.attach(10);
  pinMode(pinoBuzzer, OUTPUT);
  if (finger.verifyPassword())
  {
    lcd.print("Sensor biometrico encontrado!");
    Serial.println(F("Sensor biometrico encontrado!"));
    digitalWrite(pinoBuzzer, HIGH);
    delay(500);
    digitalWrite(pinoBuzzer, LOW);
    delay(1000);
  }
  else
  {
    lcd.print("NAO foi possivel encontrar o sensor biometrico.");
    Serial.println(F("NAO foi possivel encontrar o sensor biometrico."));
    while (true)
    {
      digitalWrite(pinoBuzzer, HIGH);
      delay(1000);
      digitalWrite(pinoBuzzer, LOW);
      delay(500);
    }
  }
  digitalWrite(pinoBuzzer, LOW);
}
int leituraBiometrica()
{
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)
    return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)
    return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)
  {
    lcd.clear();
    lcd.print("Acesso negado!");
    servo.write(0);
    digitalWrite(pinoBuzzer, HIGH);
    delay(1500);
    digitalWrite(pinoBuzzer, LOW);
    return -1;
  }
  else
  {
    return finger.fingerID;
  }
}
void liberaEntrada(int ID)
{
  digitalWrite(pinoBuzzer, HIGH);
  delay(500);
  digitalWrite(pinoBuzzer, LOW);
  char *nome = getNomeUsuario(ID);
  digitalWrite(pinoLedVerde, HIGH);
  Serial.print(F("ID encontrado #"));
  Serial.println(ID);
  lcd.clear();
  servo.write(100);
  lcd.setCursor(0, 0);
  lcd.print("Entrada liberada!");
  lcd.setCursor(0, 1);
  lcd.print("Olá, ");
  lcd.print(nome);
  lcd.print(", seja bem vindo.");
  lcd.autoscroll();
  delay(2000); //INTERVALO DE 2 SEGUNDOS

  servo.write(0);
}
void loop()
{
  Serial.println();
  Serial.println(F("MENU:"));
  Serial.println();
  Serial.println(F("Digite 1 para cadastrar nova digital"));
  Serial.println(F("Digite 2 para remover uma digital"));
  Serial.println(F("Digite 3 para ver as digitais cadastradas"));
  numMenu = readnumber(); // Armazena caractere lido
  Serial.println();

  if (numMenu == 1)
  {
    cadastraDigital();
  }
  else if (numMenu == 2)
  {
    apagaDigital();
  }
  else if (numMenu == 3)
  {
    mostraDigitais();
  }

  int ID = leituraBiometrica(); //funcao para ler a biometria e retornar o ID da pessoa
  if (ID != -1)
  {
    liberaEntrada(ID);
  }
}

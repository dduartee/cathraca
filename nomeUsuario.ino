/*
Função para retornar o nome do usuário a partir do ID
*/
char* getNomeUsuario(int fingerID) {
    // Matriz com a relação de ids com nomes
    char* nomes[10][2] = {
        {"0", "Usuário 0"},
        {"1", "Usuário 1"},
        {"2", "Usuário 2"},
        {"3", "Usuário 3"},
        {"4", "Usuário 4"},
        {"5", "Usuário 5"},
        {"6", "Usuário 6"},
        {"7", "Usuário 7"},
        {"8", "Usuário 8"},
        {"9", "Usuário 9"}
    };

    for (int i = 0; i < 100; i++) {
        int userID = (int) nomes[i][0];
        if (userID == fingerID) {
            return nomes[i][1];
        } else {
            return "Usuário não encontrado";
        }
    }
}
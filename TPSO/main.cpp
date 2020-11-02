using namespace std;
#include <iostream>

void leituraArquivo(FILE *arquivo);

int main() {
    std::cout << "Teste" << std::endl;
    FILE* arquivo;
    char* valores[50];
    char linhas[50];
}

void leituraArquivo(FILE* arquivo, char* valores, char linha[]) {

    arquivo = fopen("entrada.txt","r");

    if (arquivo == NULL)
        printf("Problema na abertura do arquivo!");

    while(fgets(linha, sizeof linha, arquivo) != NULL)
    {
        valores[i] = strdup(linha);
        i++;
        numPalavras++;
    }

    fclose(arquivo);
}

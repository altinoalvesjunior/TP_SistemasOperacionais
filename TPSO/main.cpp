#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <sstream>

using namespace std;

void menu();
void escreverArquivo();

int main() {

    ifstream arquivo;

    string linha1;
    string vazio;
    string linha3;

    arquivo.open("teste.txt");

    if(arquivo.is_open()) {
        getline(arquivo, linha1);
        getline(arquivo, vazio);
        getline(arquivo, linha3);
        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo!" << endl;
    }

    vector<int> sequenciaReferencia;
    stringstream sstream(linha1);

    for (int i; sstream >> i;) {
        sequenciaReferencia.push_back(i);
        if (sstream.peek() == ',' || sstream.peek() == ' ')
            sstream.ignore();
    }

    cout << "O vetor eh: ";

    for (int i = 0; i < sequenciaReferencia.size(); i++)
        cout << "[" << sequenciaReferencia[i] << "]";

    int quadros = stoi(linha3);
    cout << endl << "A quantidade de quadros é: ";
    cout << quadros << endl;

    escreverArquivo();

    return 0;
}

void menu(){
    cout << endl << "----- MENU -----" << endl;
    cout << endl << " 1 - Importar arquivo" << endl;
    cout << " 2 - Exportar arquivo" << endl;
    cout << endl << "Escolha: ";
}

void escreverArquivo() {

    ofstream arquivoSaida;
    arquivoSaida.open("config.txt", ios_base::in);

    if(!arquivoSaida)
        arquivoSaida.open("config.txt");

    arquivoSaida << "Teste";

    arquivoSaida.close();
}

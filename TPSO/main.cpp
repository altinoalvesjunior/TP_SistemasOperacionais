#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
using namespace std;

struct estrutura
{
    string sequenciaReferencia;
    int numeroPaginas;
};

void menu();

int main() {

    ifstream arquivo;

    string sequenciaReferencia;
    string vazio;
    string linha3;

    arquivo.open("teste.txt");

    if(arquivo.is_open()) {
        getline(arquivo, sequenciaReferencia);
        //cout << sequenciaReferencia << endl;

        getline(arquivo, vazio);

        getline(arquivo, linha3);
        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo!" << endl;
    }

    //Converte string em vetor char, ainda necessita ajustes
    int tam = sequenciaReferencia.length();
    char p[tam];
    strcpy(p, sequenciaReferencia.c_str());

    cout << "Vetor: ";
    for(int i = 0; i< sizeof(p); i++){
        if(p[i] != ',' && p[i] != ' '){
            cout << "[" << p[i] << "]";
        }
    }

    // Converte linha do arquivo de quadros em inteiro
    int quadros = stoi(linha3);
    cout << endl << "A quantidade de quadros é: ";
    cout << quadros << endl;

    /*dif

    stringstream ss(quadros);
    vector<int> v;

    int hlp;
    while(ss >> hlp)
    {
        v.push_back(hlp);
    }

    for(auto i: v)
    cout << i << '\n'; */

    return 0;
}

void menu(){
    cout << endl << "----- MENU -----" << endl;
    cout << endl << " 1 - Importar arquivo" << endl;
    cout << " 2 - Exportar arquivo" << endl;
    cout << endl << "Escolha: ";
}

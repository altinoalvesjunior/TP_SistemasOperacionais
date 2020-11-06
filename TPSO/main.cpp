#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <vector>

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
    string quadros;

    arquivo.open("teste.txt");

    if(arquivo.is_open()) {
        getline(arquivo, sequenciaReferencia);
        //cout << sequenciaReferencia << endl;

        getline(arquivo, vazio);

        getline(arquivo, quadros);
        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo!" << endl;
    }

    /*int tam = sequenciaReferencia.length();
    char p[tam];
    strcpy(p, sequenciaReferencia.c_str());

    for(int i = 0; i< sizeof(p); i++){
      if(p[i] != ',')
      cout << "[" << p[i] << "]" << endl;
    }*/

    stringstream ss(quadros);
    vector<int> v;

    int hlp;
    while(ss >> hlp)
    {
        v.push_back(hlp);
    }

    for(auto i: v)
        cout << i*2 << '\n';


    return 0;
}

void menu(){
    cout << endl << "----- MENU -----" << endl;
    cout << endl << " 1 - Importar arquivo" << endl;
    cout << " 2 - Exportar arquivo" << endl;
    cout << endl << "Escolha: ";
}
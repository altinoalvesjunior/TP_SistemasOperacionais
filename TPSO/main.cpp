#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void menu();
void escreverArquivo();

int main() {

    ifstream arquivo;

    string linha1;
    string linha2;

    arquivo.open("/Users/altino/Documents/TP_SistemasOperacionais/TPSO/teste.txt");

    if(arquivo.is_open()) {
        getline(arquivo, linha1);
        getline(arquivo, linha2);
        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo!" << endl;
        exit(1);
    }

    vector<int> sequenciaReferencia;
    stringstream sstream(linha1);

    for (int i; sstream >> i;) {
        sequenciaReferencia.push_back(i);
        if (sstream.peek() == ',' || sstream.peek() == ' ' || sstream.peek() == '.')
            sstream.ignore();
    }

    cout << "O vetor eh: ";

    for (int i = 0; i < sequenciaReferencia.size(); i++)
        cout << "[" << sequenciaReferencia[i] << "]";

    int quadros = stoi(linha2);
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
    arquivoSaida.open("/Users/altino/Documents/TP_SistemasOperacionais/TPSO/saida-teste.txt", ios_base::in);

    if(!(arquivoSaida))
        arquivoSaida.open("/Users/altino/Documents/TP_SistemasOperacionais/TPSO/saida-teste.txt");

    arquivoSaida << "Teste";

    arquivoSaida.close();
}

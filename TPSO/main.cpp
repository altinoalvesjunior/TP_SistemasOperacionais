#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int quadros;

bool BuscaMemoria(int *vetor, int valor){
    for (int i = 0; i < quadros; i++){
        if (valor == vetor[i])
            return true;
        else
            return false;
    }

}

void FIFO(vector <int> ListaProcessos){
    int MEMORIA[quadros];
    int FaltaPag = 0;
    int numProcessos = ListaProcessos.size();
    int i;
    int count=0;

    if (numProcessos == 0){
        puts("Não existem processos");
    }

    for(i=0 ; i < numProcessos ; i++){
        if(!BuscaMemoria(MEMORIA, ListaProcessos[i])){
            if(count == quadros){
                count = 0;
            }
            MEMORIA[count] = ListaProcessos[i];
            FaltaPag++;
            count++;
        }
        for(int i=0 ; i<quadros ; i++){
            cout << MEMORIA[i] << " ";
        }
        puts("");

    }

    cout << "FIFO " << FaltaPag << endl;
}

void menu();
vector<int> lerArquivo(std::ifstream& arquivo);
void escreverArquivo();

int main() {

    ifstream arquivo;

    /*string linha1;
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
    cout << quadros << endl;*/

    escreverArquivo();

    vector <int> sequencia;
    sequencia = lerArquivo(arquivo);

   /* for(int i = 0; i < sequencia.size(); i++) {
        cout << "[" <<  sequencia[i] << "]";
    }*/

    FIFO(sequencia);

    return 0;
}

void menu(){
    cout << endl << "----- MENU -----" << endl;
    cout << endl << " 1 - Importar arquivo" << endl;
    cout << " 2 - Exportar arquivo" << endl;
    cout << endl << "Escolha: ";
}

vector<int> lerArquivo(std::ifstream& arquivo) {

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

    vector<int> vetor;
    stringstream sstream(linha1);

    for (int i; sstream >> i;) {
        vetor.push_back(i);

        if (sstream.peek() == ',' || sstream.peek() == ' ' || sstream.peek() == '.')
            sstream.ignore();
    }

    quadros = stoi(linha2);

    return vetor;
}

void escreverArquivo() {

    ofstream arquivoSaida;
    arquivoSaida.open("/Users/altino/Documents/TP_SistemasOperacionais/TPSO/saida-teste.txt", ios_base::in);

    if(!(arquivoSaida))
        arquivoSaida.open("/Users/altino/Documents/TP_SistemasOperacionais/TPSO/saida-teste.txt");

    arquivoSaida << "Teste";

    arquivoSaida.close();
}


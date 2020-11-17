#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;
vector <int> ListaProcessos;
int quadros;

void menu();
vector<int> lerArquivo(std::ifstream& arquivo);
void escreverArquivo();
void FIFO(vector<int> paginas);

int main() {

    ifstream arquivo;

    vector <int> sequencia;
    sequencia = lerArquivo(arquivo);

    cout << "Sequência: ";

    for(int i = 0; i < sequencia.size(); i++)
        cout << "[" <<  sequencia[i] << "]";

    cout << endl << "Número de Quadros: " << quadros;

    cout << endl << endl;

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

void FIFO(vector<int> paginas) {

    vector<int> s;
    int encontrou = 0;
    int indice = 0;
    queue<int> filaAux;

    int erros = 0;

    for (int i=0; i<paginas.size(); i++)
    {
        if (s.size() < quadros)
        {
            for(int j=0 ; j<s.size() ; j++)
            {
                if(s[j] == paginas[i])
                    encontrou = 1;
            }

            if(encontrou == 0) {
                s.push_back(paginas[i]);
                printf("%02d     ", paginas[i]);

                for(int j=0 ; j<s.size() ; j++){
                    printf("%d ", s[j]);
                }
                printf("\n");

                filaAux.push(paginas[i]);
            }

            else {
                printf("%02d     ", paginas[i]);

                for(int j = 0; j < s.size(); j++){
                    printf("%d ", s[j]);
                }

                printf("\n");
            }

            encontrou = 0;
        }

        else
        {

            for(int j=0 ; j<s.size() ; j++)
                if(s[j] == paginas[i])
                    encontrou = 1;

            if(encontrou == 0) {
                int val = filaAux.front();

                filaAux.pop();
                for(int j=0 ; j<s.size() ; j++)
                {
                    if(s[j] == val)
                    {
                        indice = j;
                        break;
                    }
                }
                s[indice] = paginas[i];

                filaAux.push(paginas[i]);
                printf("%02d F   ",paginas[i]);
                for(int j=0 ; j<s.size() ; j++){
                    printf("%d ",s[j]);
                }
                printf("\n");
                erros++;
            }

            else {
                printf("%02d     ",paginas[i]);

                for(int j=0 ; j<s.size() ; j++){
                    printf("%d ",s[j]);
                }
                printf("\n");
            }
            encontrou = 0;
        }
    }
    printf("-------------------------------------\n"
           "Number of page faults = %d\n", erros);
}

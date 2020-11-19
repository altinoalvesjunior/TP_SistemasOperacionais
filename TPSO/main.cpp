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
void OPT(vector<int> paginas);
int encontrarProximo(vector<int> sequencia, int dado, int curr);
void rodapeArquivo (int erros, int requisicoes, int taxaErro);

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
    OPT(sequencia);

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

void escreverArquivo(int conteudo) {

    ofstream arquivoSaida;
    arquivoSaida.open("/Users/altino/Documents/TP_SistemasOperacionais/TPSO/saida-teste.txt", std::ios_base::app);

    /*if(!(arquivoSaida))
        arquivoSaida.open("/Users/altino/Documents/TP_SistemasOperacionais/TPSO/saida-teste.txt");*/
    if(conteudo == -1){
        arquivoSaida << endl;
    }
    else {
        arquivoSaida << conteudo << " ";
    }

    arquivoSaida.close();
}

void escreverStringArquivo(string conteudo) {

    ofstream arquivoSaida;
    arquivoSaida.open("/Users/altino/Documents/TP_SistemasOperacionais/TPSO/saida-teste.txt", std::ios_base::app);

    /*if(!(arquivoSaida))
        arquivoSaida.open("/Users/altino/Documents/TP_SistemasOperacionais/TPSO/saida-teste.txt");*/

    arquivoSaida << conteudo;

    arquivoSaida.close();
}

void rodapeArquivo (int erros, int requisicoes, int taxaErro) {
    escreverStringArquivo("ACERTOS\n");
    escreverStringArquivo("ERROS\n");
    escreverArquivo(erros);
    escreverStringArquivo("TOTAL REQUISICOES\n");
    escreverArquivo(requisicoes);
    escreverStringArquivo("TAXA DE ERRO\n");
    escreverArquivo(taxaErro);
}

void FIFO(vector<int> paginas) {

    vector<int> s;
    int encontrou = 0;
    int indice = 0;
    int requisicoes = 0;
    queue<int> filaAux;

    int erros = 0;

    escreverStringArquivo("EVOLUCAO\n");

    for (int i=0; i<paginas.size(); i++)
    {
        string converte;

        if (s.size() < quadros)
        {
            for(int j = 0; j < s.size(); j++)
                if(s[j] == paginas[i])
                    encontrou = 1;

            if(encontrou == 0) {
                s.push_back(paginas[i]);
                printf("%02d     ", paginas[i]);
                requisicoes++;

                for(int j=0 ; j<s.size() ; j++){
                    printf("%d ", s[j]);
                    escreverArquivo(round(s[j]));
                }
                printf("\n");
                escreverArquivo(-1);

                filaAux.push(paginas[i]);
            }

            else {
                printf("%02d     ", paginas[i]);
                requisicoes++;

                for(int j = 0; j < s.size(); j++){
                    printf("%d ", s[j]);
                    escreverArquivo(round(s[j]));
                }

                printf("\n");
                escreverArquivo(-1);
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
                for(int j = 0; j < s.size(); j++)
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
                requisicoes++;
                for(int j=0 ; j<s.size() ; j++){
                    printf("%d ",s[j]);
                    escreverArquivo(round(s[j]));
                }
                printf("\n");
                escreverArquivo(-1);
                erros++;
            }

            else {
                printf("%02d     ",paginas[i]);
                requisicoes++;
                for(int j=0 ; j<s.size() ; j++){
                    printf("%d ",s[j]);
                    escreverArquivo(round(s[j]));
                }
                printf("\n");
                escreverArquivo(-1);
            }
            encontrou = 0;
        }
    }

    string d = std::to_string((erros/requisicoes));

    escreverStringArquivo("ACERTOS\n");
    escreverStringArquivo("ERROS\n");
    escreverArquivo(erros);
    escreverStringArquivo("TOTAL REQUISICOES\n");
    escreverArquivo(requisicoes);
    escreverStringArquivo("TAXA DE ERRO\n");
    escreverStringArquivo(d);

    printf("-------------------------------------\n"
           "Erros = %d\n", erros);
}

int encontrarProximo(vector<int> sequencia, int dado, int curr) {
    int distancia = 1;

    for (int i = curr + 1; i < sequencia.size(); i++) {
        if (dado == sequencia[i])
            return distancia;
        distancia++;
    }

    return INT_MAX;
}

void OPT(vector<int> paginas) {
    vector<int> dadoPagina;
    vector<int> order;

    int erros = 0;
    bool encontrou = false;
    int closest = 0;

    for (int i = 0; i < paginas.size(); i++) {

        for (int j = 0; j < order.size(); j++)
            --order[j];

        encontrou = false;

        for (int j = 0; j < dadoPagina.size(); j++) {
            cout << dadoPagina[j] << " ";
            escreverArquivo(dadoPagina[j]);
            if (paginas[i] == dadoPagina[j]) {
                order[j] = encontrarProximo(paginas, dadoPagina[j], i);
                encontrou = true;
            }
        }

        if (!(encontrou)) {
            // cout << "Page fault. ";
            erros++;
            if (dadoPagina.size() < quadros) {
                dadoPagina.push_back(paginas[i]);
                order.push_back(encontrarProximo(paginas, paginas[i], i));
                cout << endl;
                escreverArquivo(-1);
            }
            else {
                closest = 0;
                for (int x = 0; x < order.size(); x++) {
                    if (order[x] > order[closest]) {
                        closest = x;
                    }
                }
                cout << "Replacing: " << dadoPagina[closest] << endl;
                escreverArquivo(-1);
                dadoPagina[closest] = paginas[i];
                order[closest] = encontrarProximo(paginas, dadoPagina[closest], i);
            }
        }
        else {
            //cout << "Found" << endl;
            cout << endl;
            escreverArquivo(-1);
        }
    }
    cout << "Number of faults: " << erros << endl;
    cout << "Page fault rate: " << erros << "/" << paginas.size() << endl;

    escreverStringArquivo("ACERTOS\n");
    escreverStringArquivo("ERROS\n");
    escreverArquivo(erros);
    escreverStringArquivo("TOTAL REQUISICOES\n");
    escreverArquivo(paginas.size());
    escreverStringArquivo("TAXA DE ERRO\n");
}
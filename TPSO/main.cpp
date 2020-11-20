#include<stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include<math.h>

using namespace std;

int quadros;
vector <int> sequencia;

void menu();
vector<int> lerArquivo(std::ifstream& arquivo);
void escreverArquivo(int);
void FIFO(vector<int> paginas);
void OPT(vector<int> paginas);
int encontrarProximo(vector<int> sequencia, int dado, int curr);
void rodapeArquivo (int acertos, int erros, int requisicoes, float taxaErro);
void FinalizarAlgoritmo();

int main() {
    ifstream arquivo;
    int option;

    do{
        cout << endl << "\t\t----- MENU -----" << endl;
        cout << "---- Algoritmo de Substituicao de Pagina ----" << endl;
        cout << endl << " 1 - Importar arquivo" << endl;
        cout << " 2 - Executar FIFO" << endl;
        cout << " 3 - Executar OPT" << endl;
        cout << " 4 - Finalizar" << endl;
        cout << endl << "Escolha: ";
        cin >> option;

        switch(option){
            case 1:
                sequencia = lerArquivo(arquivo);
                cout << "Sequencia: ";
                for(int i = 0; i < sequencia.size(); i++)
                    cout << "[" <<  sequencia[i] << "]";
                cout << endl << "Numero de Quadros: " << quadros;
                cout << endl << endl;
            break;
            case 2:
                cout << "\nEVOLUCAO FIFO" << endl;
                FIFO(sequencia);
            break;
            case 3:
                cout << "\nEVOLUCAO OPT" << endl;
                OPT(sequencia);
            break;
            case 4:
                FinalizarAlgoritmo();
                cout << "\n\tSaindo do programa!\n";
            break;
            default:
                cout << "\n Escolha uma opcao valida!\n";
            break;
        }
        printf("-------------------------------------\n");
    }while(option != 4);
    return 0;
}

vector<int> lerArquivo(std::ifstream& arquivo) {

    string linha1;
    string linha2;

    arquivo.open("teste.txt");

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
    arquivoSaida.open("saida.txt", std::ios_base::app);
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
    arquivoSaida.open("saida.txt", std::ios_base::app);

    if(!(arquivoSaida))
        arquivoSaida.open("saida.txt");

    arquivoSaida << conteudo;

    arquivoSaida.close();
}

void escreverFloatArquivo(float conteudo) {

    ofstream arquivoSaida;
    arquivoSaida.open("saida.txt", std::ios_base::app);
    arquivoSaida << std::setprecision(2) << conteudo;

    arquivoSaida.close();
}

void rodapeArquivo (int acertos, int erros, int requisicoes, float taxaErro) {
    escreverStringArquivo("\nACERTOS\n");
    escreverArquivo(acertos);
    escreverStringArquivo("\nERROS\n");
    escreverArquivo(erros);
    escreverStringArquivo("\nTOTAL REQUISICOES\n");
    escreverArquivo(requisicoes);
    escreverStringArquivo("\nTAXA DE ERRO\n");
    escreverFloatArquivo(taxaErro);

    escreverStringArquivo("\n---------------------------------\n");
}

void FinalizarAlgoritmo(){
    cout << "Deseja apagar o arquivo de saida? --- (saida.txt) --- " << endl;
    cout << endl << " 1 - Sim" << endl << " 2 - Nao" << endl << " Escolha: ";
    int deleta;
    cin >> deleta;

    if(deleta == 1) {
        std::remove("saida.txt");
    }
}



void FIFO(vector<int> paginas) {

    vector<int> s;
    int encontrou = 0;
    int indice = 0;
    int requisicoes = 0;
    queue<int> filaAux;

    int erros = 0;

    escreverStringArquivo("EVOLUÇÃO FIFO\n");

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
                requisicoes++;
                erros++;

                for(int j=0 ; j<s.size(); j++){
                    printf("%d ", s[j]);
                    escreverArquivo(round(s[j]));
                }
                printf("\n");
                escreverArquivo(-1);

                filaAux.push(paginas[i]);
            }

            else {
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

    float taxaErro = ((float) erros/(float) requisicoes);
    int acertos = (requisicoes - erros);

    rodapeArquivo(acertos, erros, requisicoes, taxaErro);

    printf("-------------------------------------\n"
           "Erros = %d\n"
           "Acertos = %d\n"
           "Requisicoes = %d\n"
           "Taxa de erro = %.2f\n", erros, acertos, requisicoes, taxaErro);
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

    escreverStringArquivo("EVOLUÇÃO OPT");
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
                cout << endl;
                escreverArquivo(-1);
                dadoPagina[closest] = paginas[i];
                order[closest] = encontrarProximo(paginas, dadoPagina[closest], i);
            }
        }
        else {
            cout << endl;
            escreverArquivo(-1);
        }
    }

    int acertos = (paginas.size() - erros);
    float taxaErro = ((float) erros/(float) paginas.size());

    rodapeArquivo(acertos, erros, paginas.size(), taxaErro);

    printf("-------------------------------------\n"
           "Erros = %d\n"
           "Acertos = %d\n"
           "Requisicoes = %d\n"
           "Taxa de erro = %.2f\n", erros, acertos, paginas.size(), taxaErro);
}


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <filesystem>
#include "archivos.h"
using namespace std;
#include "comprension.h"

//nodo del arbo
struct Node {
    char simbolo;
    int frecuencia;
    Node *izq, *der;

};

//Funcion para asignar un  nuevo nodo en el arbol
Node* getNode(char simbolo, int frecuencia, Node* izq, Node* der){
    Node* nodo = new Node();

    nodo->simbolo = simbolo;
    nodo->frecuencia = frecuencia;
    nodo->izq = izq;
    nodo->der = der;
    return nodo;
}

//objeto de comparacion que sera usado para ordenar la pila
struct comp {
    bool operator()(Node* i, Node* d){
        return i->frecuencia > d->frecuencia;
    }
};

//Revisa el arbol de Huffman y guarda los codigos en un mapa
void encode(Node* raiz, string str, unordered_map<char, string> &CodigoHuffman){
    if(raiz == nullptr)
        return;
    if(!raiz->izq && !raiz->der){
        CodigoHuffman[raiz->simbolo] = str;
    }
    encode(raiz->izq, str + "0", CodigoHuffman);
    encode(raiz->der, str + "1", CodigoHuffman);
}

//Revisa el arbol y decodifica los simnbolos codificados
void decode(Node* raiz, int &index, string str) {
    if(raiz == nullptr){
        return;
    }
    if (!raiz->izq && !raiz->der){
        cout << raiz -> simbolo;
        return;
    }
    index++;
    if(str[index] == '0')
        decode(raiz->izq, index, str);
    else
        decode(raiz->der, index, str);
}

//crea el arbol de Huffman y decodificas dados los simbolos
void crearArbol(string text) {
// Cuenta la cantidad de veces que aparece cada simbolo y la guardsa en el mapa
unordered_map<char, int> frecuencia;
for (char simbolo: text){
    frecuencia[simbolo]++;
}
//crea una cola de prioridad para guardar los nodos del arbol
priority_queue<Node*, vector<Node*>, comp> pq;
//Agrega a la cola de prioridad los nodos de cada simbolo
for(auto pair: frecuencia){
    pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
}
//Hacer todo el proceso hasta que haya mas de 1 nodo en la cola
while (pq.size() != 1) {
    Node *izq = pq.top(); pq.pop();
    Node *der = pq.top(); pq.pop();
    int sum = izq->frecuencia + der->frecuencia;
    pq.push(getNode('\0', sum, izq, der));
}
Node* raiz = pq.top();
//Imprime los codigos para cada simbolo
unordered_map<char, string> codigoHuffman;
encode(raiz, "", codigoHuffman);
cout << "\nLos codigos Huffman son:\n" << '\n';
for (auto pair: codigoHuffman) {
    cout << pair.first << " " << pair.second << '\n';
}
//Imprime el mensaje original que el usuario ingreso directamente, el codificado
//y decodifica el codificado y lo imprime de nuevo
cout << "\nEl mensaje original era:\n" << text << '\n';
string str = "";
for (char simbolo: text){
    str += codigoHuffman[simbolo];
}
cout << "\nEl texto codificado es: \n" << str << '\n';
int index = -1;
cout << "\nEl texto decodificado es: \n";
while (index < (int)str.size()- 2){
    decode(raiz, index, str);
}
cout << "\n\n\n";
}

int main () {
    cout << "\n\n\n-------------------------------------------------------------------";
    cout << "\n          Comprension y Descompresion con el Metodo de Huffman";
    cout << "\n                                 Programacion I";
    cout << "\n-----------------------------------------------------------------------";
    string text;
    cout << "\nIngrese el mensaje que desea comprimir: ";
    getline(cin, text);

    //Guarda la entrada del usuario en un archivo de texto
    ofstream outputFile("mensaje_del_usuario.txt");
    if(outputFile.is_open()){
        outputFile << text;
        outputFile.close();
        cout << "\nEl mensaje se ha guardado en el archivo 'mensaje_del_usuario.txt'.\n";
    }else{
        cout <<" \nErro al guardar el archivo.\n";
    }
    crearArbol(text);
    cout << "\n";
    return 0;
}

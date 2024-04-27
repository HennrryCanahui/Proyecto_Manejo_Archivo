#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <unordered_map>
#include <filesystem>
#include "archivos.h"
#include "comprension.h"
//#include <ncurses.h>
#include <sys/stat.h>
using namespace std;
using namespace std;


using namespace std;
string contenido, descifrado, linea;

// Función para cifrar el texto
string cifrar(string texto, int clave) {
    string texto_cifrado;
    for (char& c : texto) {
        if (isalpha(c)) {
            char offset = isupper(c) ? 'A' : 'a';
            c = static_cast<char>((c - offset + clave) % 26 + offset);
        }
        texto_cifrado += c;
    }
    return texto_cifrado;
}

// Función para descifrar el texto
string descifrar(string texto_cifrado, int clave) {
    descifrado = cifrar(texto_cifrado, 26 - clave);
    return descifrado;
}

// Función para leer el contenido del archivo
string Leer_contenido(string Ubicacion_Archivo_User){
    ifstream archivo;
    archivo.open(Ubicacion_Archivo_User);
    if(archivo.is_open()){
        while(getline(archivo, linea)){
            contenido += linea + "\n";
        }
        archivo.close();
    }
    cout << "\nDocumento leido\n";
    return contenido;
}

// Función para modificar el documento
void Modificar_Documento(string Ubicacion_Archivo_User, string Nuevo_texto){
    ofstream archivo_salida(Ubicacion_Archivo_User);
    if (archivo_salida.is_open()) {
        archivo_salida << Nuevo_texto;
        archivo_salida.close();
    }
}

#include <iostream>
#include <vector>


// Función para leer palabras desde el archivo
std::vector<std::string> leerPalabrasDesdeArchivo(const std::string& rutaArchivo) {
    std::vector<std::string> palabras;
    std::string palabra;
    std::ifstream archivo(rutaArchivo);

    if (archivo.is_open()) {
        while (archivo >> palabra) {
            palabras.push_back(palabra);
        }
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
    }

    return palabras;
}

// Función para guardar la palabra en el archivo
void guardarPalabraEnArchivo(const std::string& palabra, const std::string& rutaArchivo) {
    std::ofstream archivo(rutaArchivo, std::ios::app);

    if (archivo.is_open()) {
        archivo << palabra << std::endl;
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo para escribir." << std::endl;
    }
}

// Función para mostrar todas las palabras del archivo
void mostrarPalabrasGuardadas(const std::string& rutaArchivo) {
    std::vector<std::string> palabras = leerPalabrasDesdeArchivo(rutaArchivo);
    std::cout << "Palabras guardadas en el archivo:" << std::endl;
    for (const auto& palabra : palabras) {
        std::cout << palabra << std::endl;
    }
}

// Función para proporcionar pistas al jugador
void proporcionarPista(std::string& palabraAdivinada, const std::string& palabraSecreta, int& intentos, int& pistasDisponibles) {
    if (pistasDisponibles > 0) {
        std::cout << "Pista: ";
        // Encuentra una letra no revelada y muéstrala como pista
        for (size_t i = 0; i < palabraSecreta.length(); ++i) {
            if (palabraAdivinada[i] == '_') {
                palabraAdivinada[i] = palabraSecreta[i];
                --intentos;
                --pistasDisponibles;
                std::cout << "Una letra de la palabra es '" << palabraSecreta[i] << "'." << std::endl;
                break;
            }
        }
    } else {
        std::cout << "No tienes más pistas disponibles." << std::endl;
    }
}

// Función principal del juego
void jugarAdivinanzaDePalabras() {
    std::string rutaArchivo = "C:\\Users\\gesle\\Desktop\\palabras.txt"; // Cambia 'TuUsuario' por tu nombre de usuario
    std::string palabraJugador1;
    std::cout << "Jugador 1, ingresa una palabra: ";
    std::cin >> palabraJugador1;
    guardarPalabraEnArchivo(palabraJugador1, rutaArchivo);

    std::vector<std::string> palabras = leerPalabrasDesdeArchivo(rutaArchivo);
    std::string palabraSecreta = palabraJugador1;
    std::string palabraAdivinada(palabraSecreta.length(), '_');

    int intentos = palabraSecreta.length();
    int pistasDisponibles = 0;
    if (palabraSecreta.length() > 7) {
        pistasDisponibles = 3;
    } else if (palabraSecreta.length() > 3) {
        pistasDisponibles = 2;
    }
    char letra;
    bool adivinado = false;

    std::cout << "Bienvenido al juego de adivina la palabra" << std::endl;
    std::cout << "Tienes " << intentos << " intentos para adivinar la palabra." << std::endl;
    std::cout << "Escribe 'P' para una pista." << std::endl;

    while (intentos > 0 && !adivinado) {
        std::cout << "Palabra adivinada: " << palabraAdivinada << std::endl;
        std::cout << "Te quedan " << intentos << " intentos. Escribe 'P' para una pista." << std::endl;
        std::string entrada;
        std::cin >> entrada;
        if (entrada == "P") {
            proporcionarPista(palabraAdivinada, palabraSecreta, intentos, pistasDisponibles);
        } else {
            letra = entrada[0];
            bool letraEncontrada = false;
            for (size_t i = 0; i < palabraSecreta.length(); ++i) {
                if (palabraSecreta[i] == letra && palabraAdivinada[i] == '_') {
                    palabraAdivinada[i] = letra;
                    letraEncontrada = true;
                }
            }

            if (!letraEncontrada) {
                --intentos;
                std::cout << "Incorrecto. Te quedan " << intentos << " intentos." << std::endl;
            } else {
                std::cout << "Correcto!" << std::endl;
            }
        }

        adivinado = (palabraAdivinada == palabraSecreta);
    }

    if (adivinado) {
        std::cout << "Felicidades, Jugador 2 adivinaste la palabra: " << palabraSecreta << std::endl;
    } else {
        std::cout << "Lo siento, Jugador 2 no adivinaste la palabra. Era: " << palabraSecreta << std::endl;
    }
}


std::ifstream abrirArchivo(const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        throw std::runtime_error("Error al abrir el archivo: " + rutaArchivo);
    }
    return archivo;
}

// Función para buscar palabras
std::vector<std::string> buscarPalabraEnArchivo(std::ifstream& archivo, const std::string& palabraClave) {
    std::vector<std::string> lineasEncontradas;
    std::string linea;
    int numeroLinea = 0;

    while (std::getline(archivo, linea)) {
        ++numeroLinea;
        if (linea.find(palabraClave) != std::string::npos) {
            lineasEncontradas.push_back(std::to_string(numeroLinea) + " - " + linea);
        }
    }

    return lineasEncontradas;
}



namespace fs = std::filesystem;

// Función para obtener la ruta de la carpeta del usuario
std::string obtenerRutaCarpeta() {
    std::string folderPath;
    std::cout << "Introduce la ruta de la carpeta: ";
    std::cin >> folderPath;
    return folderPath;
}

// Función para verificar si la carpeta existe
bool verificarCarpeta(const std::string& folderPath) {
    return fs::exists(folderPath) && fs::is_directory(folderPath);
}

// Función para recorrer los archivos en la carpeta
std::pair<int, long long> recorrerArchivos(const std::string& folderPath) {
    int fileCount = 0;
    long long totalSize = 0;
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (fs::is_regular_file(entry)) {
            ++fileCount;
            totalSize += fs::file_size(entry);
        }
    }
    return {fileCount, totalSize};
}


/*


// Función para inicializar ncurses
void inicializarNcurses() {
    initscr();
    cbreak();
    noecho();
}

// Función para crear una ventana emergente y obtener una cadena de texto
std::string obtenerCadenaDeVentanaEmergente(int alto, int ancho, int inicioY, int inicioX, const char* mensaje) {
    WINDOW* ventana = newwin(alto, ancho, inicioY, inicioX);
    box(ventana, 0, 0);
    mvwprintw(ventana, 1, 1, mensaje);
    wrefresh(ventana);

    char cadena[256];
    wgetstr(ventana, cadena);

    delwin(ventana);

    return std::string(cadena);
}

// Función para abrir un archivo
std::ifstream abrirArchivo(const std::string& ruta) {
    std::ifstream archivo(ruta);
    if (!archivo) {
        throw std::runtime_error("No se pudo abrir el archivo");
    }
    return archivo;
}

// Función para buscar una palabra en un archivo
std::vector<std::string> buscarPalabraEnArchivo(std::ifstream& archivo, const std::string& palabra) {
    // Implementa tu lógica aquí
    return std::vector<std::string>();
}

*/

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



// Función para generar un número aleatorio de 4 dígitos
int generarNumeroAleatorio() {
    srand(time(0));
    return rand() % 9000 + 1000;
}

// Función para leer el contenido del archivo
std::string leerContenido(std::string ubicacionArchivo){
    std::ifstream archivo;
    std::string contenido, linea;
    archivo.open(ubicacionArchivo);
    if(archivo.is_open()){
        while(getline(archivo, linea)){
            contenido += linea + "\n";
        }
        archivo.close();
    }
    std::cout << "\nDocumento leido\n";
    return contenido;
}

// Función para escribir en el archivo
void escribirContenido(std::string ubicacionArchivo, std::string contenido){
    std::ofstream archivo;
    archivo.open(ubicacionArchivo);
    if(archivo.is_open()){
        archivo << contenido;
        archivo.close();
    }
}

long getFileSize(const std::string &filePath) {
    struct stat stat_buf;
    int rc = stat(filePath.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

// Función para obtener la fecha de última modificación
string getLastModifiedTime(const string &filePath) {
    struct stat attr;
    stat(filePath.c_str(), &attr);
    return ctime(&attr.st_mtime);
}

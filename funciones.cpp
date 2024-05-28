#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <unordered_map>
#include <filesystem>
#include <sys/stat.h>
#include "comprension.h"
using namespace std;
namespace fs = std::filesystem;

// Función para cifrar el texto
string cifrar(const string& texto, int clave) {
    string texto_cifrado;
    for (char c : texto) {
        if (isalpha(c)) {
            char offset = isupper(c) ? 'A' : 'a';
            c = static_cast<char>((c - offset + clave) % 26 + offset);
        }
        texto_cifrado += c;
    }
    return texto_cifrado;
}

// Función para descifrar el texto
string descifrar(const string& texto_cifrado, int clave) {
    return cifrar(texto_cifrado, 26 - clave);
}

// Función para leer el contenido del archivo
string leerContenido(const string& ubicacionArchivo) {
    ifstream archivo(ubicacionArchivo);
    string contenido, linea;
    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            contenido += linea + "\n";
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo para leer." << endl;
    }
    cout << "\nDocumento leído\n";
    return contenido;
}

// Función para escribir en el archivo
void escribirContenido(const string& ubicacionArchivo, const string& contenido) {
    ofstream archivo(ubicacionArchivo);
    if (archivo.is_open()) {
        archivo << contenido;
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
    }
}

// Función para generar un número aleatorio de 4 dígitos
int generarNumeroAleatorio() {
    srand(time(0));
    return rand() % 9000 + 1000;
}

// Función para leer palabras desde el archivo
vector<string> leerPalabrasDesdeArchivo(const string& rutaArchivo) {
    vector<string> palabras;
    string palabra;
    ifstream archivo(rutaArchivo);
    if (archivo.is_open()) {
        while (archivo >> palabra) {
            palabras.push_back(palabra);
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo." << endl;
    }
    return palabras;
}

// Función para guardar la palabra en el archivo
void guardarPalabraEnArchivo(const string& palabra, const string& rutaArchivo) {
    ofstream archivo(rutaArchivo, ios::app);
    if (archivo.is_open()) {
        archivo << palabra << endl;
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
    }
}

// Función para mostrar todas las palabras del archivo
void mostrarPalabrasGuardadas(const string& rutaArchivo) {
    vector<string> palabras = leerPalabrasDesdeArchivo(rutaArchivo);
    cout << "Palabras guardadas en el archivo:" << endl;
    for (const auto& palabra : palabras) {
        cout << palabra << endl;
    }
}

// Función para proporcionar pistas al jugador
void proporcionarPista(string& palabraAdivinada, const string& palabraSecreta, int& intentos, int& pistasDisponibles) {
    if (pistasDisponibles > 0) {
        cout << "Pista: ";
        for (size_t i = 0; i < palabraSecreta.length(); ++i) {
            if (palabraAdivinada[i] == '_') {
                palabraAdivinada[i] = palabraSecreta[i];
                --intentos;
                --pistasDisponibles;
                cout << "Una letra de la palabra es '" << palabraSecreta[i] << "'." << endl;
                break;
            }
        }
    } else {
        cout << "No tienes más pistas disponibles." << endl;
    }
}

// Función principal del juego
void jugarAdivinanzaDePalabras() {
    string rutaArchivo = "C:\\Users\\gesle\\Desktop\\palabras.txt";
    string palabraJugador1;
    cout << "Jugador 1, ingresa una palabra: ";
    cin >> palabraJugador1;
    guardarPalabraEnArchivo(palabraJugador1, rutaArchivo);

    vector<string> palabras = leerPalabrasDesdeArchivo(rutaArchivo);
    string palabraSecreta = palabraJugador1;
    string palabraAdivinada(palabraSecreta.length(), '_');

    int intentos = palabraSecreta.length();
    int pistasDisponibles = (palabraSecreta.length() > 7) ? 3 : (palabraSecreta.length() > 3) ? 2 : 0;
    bool adivinado = false;

    cout << "Bienvenido al juego de adivina la palabra" << endl;
    cout << "Tienes " << intentos << " intentos para adivinar la palabra." << endl;
    cout << "Escribe 'P' para una pista." << endl;

    while (intentos > 0 && !adivinado) {
        cout << "Palabra adivinada: " << palabraAdivinada << endl;
        cout << "Te quedan " << intentos << " intentos. Escribe 'P' para una pista." << endl;
        string entrada;
        cin >> entrada;
        if (entrada == "P") {
            proporcionarPista(palabraAdivinada, palabraSecreta, intentos, pistasDisponibles);
        } else {
            char letra = entrada[0];
            bool letraEncontrada = false;
            for (size_t i = 0; i < palabraSecreta.length(); ++i) {
                if (palabraSecreta[i] == letra && palabraAdivinada[i] == '_') {
                    palabraAdivinada[i] = letra;
                    letraEncontrada = true;
                }
            }
            if (!letraEncontrada) {
                --intentos;
                cout << "Incorrecto. Te quedan " << intentos << " intentos." << endl;
            } else {
                cout << "Correcto!" << endl;
            }
        }
        adivinado = (palabraAdivinada == palabraSecreta);
    }

    if (adivinado) {
        cout << "Felicidades, Jugador 2 adivinaste la palabra: " << palabraSecreta << endl;
    } else {
        cout << "Lo siento, Jugador 2 no adivinaste la palabra. Era: " << palabraSecreta << endl;
    }
}

// Función para obtener la ruta de la carpeta del usuario
string obtenerRutaCarpeta() {
    string folderPath;
    cout << "Introduce la ruta de la carpeta: ";
    cin >> folderPath;
    return folderPath;
}

// Función para verificar si la carpeta existe
bool verificarCarpeta(const string& folderPath) {
    return fs::exists(folderPath) && fs::is_directory(folderPath);
}

// Función para recorrer los archivos en la carpeta
pair<int, long long> recorrerArchivos(const string& folderPath) {
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

// Función para obtener el tamaño del archivo
long getFileSize(const string& filePath) {
    struct stat stat_buf;
    int rc = stat(filePath.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

// Función para obtener la fecha de última modificación
string getLastModifiedTime(const string& filePath) {
    struct stat attr;
    stat(filePath.c_str(), &attr);
    return ctime(&attr.st_mtime);
}

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
#include <bitset>
using namespace std;
namespace fs = std::filesystem;
const string RUTA_ARCHIVO = "C:\\Users\\hennr\\OneDrive\\Escritorio\\Nueva carpeta (3)\\palabras.txt";

string seleccionarArchivo();

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

// Función para proporcionar pistas al jugador
void proporcionarPista(string& palabraAdivinada, const string& palabraSecreta, int& intentos, int& pistasDisponibles) {
    if (pistasDisponibles > 0) {
        for (size_t i = 0; i < palabraSecreta.length(); ++i) {
            if (palabraAdivinada[i] == '_') {
                palabraAdivinada[i] = palabraSecreta[i];
                --pistasDisponibles;
                cout << "Pista: Una letra de la palabra es '" << palabraSecreta[i] << "'." << endl;
                break;
            }
        }
    } else {
        cout << "No tienes mas pistas disponibles." << endl;
    }
}

// Función principal del juego
void jugarAdivinanzaDePalabras() {
    vector<string> palabras = leerPalabrasDesdeArchivo(RUTA_ARCHIVO);

    if (palabras.empty()) {
        cout << "No hay palabras disponibles para adivinar." << endl;
        return;
    }

    srand(time(0));
    string palabraSecreta = palabras[rand() % palabras.size()];
    string palabraAdivinada(palabraSecreta.length(), '_');

    int intentos = palabraSecreta.length();
    int pistasDisponibles = (palabraSecreta.length() < 4) ? 2 : (palabraSecreta.length() <= 6) ? 4 : 6;
    bool adivinado = false;
    int puntos = 0;

    cout << "Bienvenido al juego de adivina la palabra" << endl;
    cout << "Tienes " << intentos << " intentos para adivinar la palabra." << endl;
    cout << "Escribe 'P' para una pista." << endl;

    while (intentos > 0 && !adivinado) {
        cout << "Palabra adivinada: " << palabraAdivinada << endl;
        cout << "Te quedan " << intentos << " intentos y " << pistasDisponibles << " pistas." << endl;
        cout << "Escribe una letra o 'P' para una pista: ";
        string entrada;
        cin >> entrada;

        if (entrada == "P") {
            proporcionarPista(palabraAdivinada, palabraSecreta, intentos, pistasDisponibles);
            puntos -= 1; // Restar puntos por usar una pista
        } else {
            char letra = entrada[0];
            bool letraEncontrada = false;
            for (size_t i = 0; i < palabraSecreta.length(); ++i) {
                if (palabraSecreta[i] == letra && palabraAdivinada[i] == '_') {
                    palabraAdivinada[i] = letra;
                    letraEncontrada = true;
                    puntos += 2; // Sumar puntos por adivinar una letra
                }
            }
            if (!letraEncontrada) {
                --intentos;
                cout << "Incorrecto. Te quedan " << intentos << " intentos." << endl;
                puntos -= 1; // Restar puntos por intento fallido
            } else {
                cout << "Correcto!" << endl;
            }
        }
        adivinado = (palabraAdivinada == palabraSecreta);
    }

    if (adivinado) {
        cout << "Felicidades, adivinaste la palabra: " << palabraSecreta << endl;
        puntos += 10; // Sumar puntos por adivinar la palabra completa
    } else {
        cout << "Lo siento, no adivinaste la palabra. Era: " << palabraSecreta << endl;
    }

    cout << "Tu puntuacion final es: " << puntos << endl;
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



// funcion de texto binario

void leerYTraducirArchivoABinario() {
    string nombreArchivo = seleccionarArchivo();

    if (nombreArchivo.empty()) {
        cerr << "No se seleccionó ningún archivo." << endl;
        return;
    }

    // Abrir el archivo original en modo lectura binaria
    ifstream archivoEntrada(nombreArchivo, ios::binary);
    if (!archivoEntrada) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    // Leer el contenido del archivo
    string contenido((istreambuf_iterator<char>(archivoEntrada)), istreambuf_iterator<char>());
    archivoEntrada.close();

    // Crear el nombre del nuevo archivo
    size_t posicionPunto = nombreArchivo.find_last_of(".");
    string nombreArchivoBinario;
    if (posicionPunto == string::npos) {
        nombreArchivoBinario = nombreArchivo + "_traduccion_binario.txt";
    } else {
        nombreArchivoBinario = nombreArchivo.substr(0, posicionPunto) + "_traduccion_binario.txt";
    }

    // Abrir el nuevo archivo en modo escritura
    ofstream archivoSalida(nombreArchivoBinario);
    if (!archivoSalida) {
        cerr << "Error al crear el archivo " << nombreArchivoBinario << endl;
        return;
    }

    // Convertir el contenido a binario y escribirlo en el nuevo archivo
    for (char c : contenido) {
        bitset<8> bits(c);
        archivoSalida << bits << ' '; // Agregar un espacio después de cada 8 bits
    }

    archivoSalida.close();
    cout << "La traduccion a binario ha sido guardada en " << nombreArchivoBinario << endl;
}

// Funcion para traducir binario a texto

string binarioATexto(const string& binario) {
    stringstream textoStream;
    string byte;
    for (size_t i = 0; i < binario.length(); i += 9) { // 8 bits + 1 espacio
        byte = binario.substr(i, 8);
        if (byte.length() == 8) {
            try {
                char letra = static_cast<char>(bitset<8>(byte).to_ulong());
                textoStream << letra;
            } catch (const invalid_argument& e) {
                cerr << "Cadena binaria inválida: " << byte << endl;
                return "";
            }
        }
    }
    return textoStream.str();
}

// Función para traducir el archivo de binario a texto y guardar en un nuevo archivo
void traducirArchivoBinarioATexto(const string& rutaArchivo) {
    // Leer el contenido del archivo original
    ifstream archivoBinario(rutaArchivo);
    if (!archivoBinario.is_open()) {
        cerr << "No se pudo abrir el archivo: " << rutaArchivo << endl;
        return;
    }

    stringstream buffer;
    buffer << archivoBinario.rdbuf();
    string contenidoBinario = buffer.str();
    archivoBinario.close();

    // Convertir el contenido binario a texto
    string textoTraducido = binarioATexto(contenidoBinario);

    if (textoTraducido.empty()) {
        cerr << "No se pudo traducir el archivo binario a texto." << endl;
        return;
    }

    // Generar el nombre del nuevo archivo
    size_t puntoPos = rutaArchivo.find_last_of('.');
    string nombreArchivoNuevo = rutaArchivo.substr(0, puntoPos) + "_traducido_a_texto.txt";

    // Guardar el texto traducido en el nuevo archivo
    ofstream archivoTexto(nombreArchivoNuevo);
    if (!archivoTexto.is_open()) {
        cerr << "No se pudo crear el archivo: " << nombreArchivoNuevo << endl;
        return;
    }

    archivoTexto << textoTraducido;
    archivoTexto.close();

    cout << "Archivo traducido y guardado en: " << nombreArchivoNuevo << endl;
}

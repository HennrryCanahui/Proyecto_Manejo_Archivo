#include <string>
#include <fstream>

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

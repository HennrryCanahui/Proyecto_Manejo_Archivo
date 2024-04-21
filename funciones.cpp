#include <fstream>
#include <string>
using namespace std;

// Función para cifrar el texto
string cifrar(string texto, int clave) {
    string texto_cifrado = "";
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
    return cifrar(texto_cifrado, 26 - clave);
}

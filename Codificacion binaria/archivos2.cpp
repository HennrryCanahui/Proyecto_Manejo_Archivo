#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
#include "archivos.h"
using namespace std;
#include "archivos2.h"
int main() {
    ifstream archivo("log.txt");
    if (!archivo) {
        cout << "No se pudo abrir el archivo de log\n";
        return 1;
    }

    int contadorErrores = 0;
    string linea;
    while (getline(archivo, linea)) {
        if (linea.find("Error") != string::npos) {
            ++contadorErrores;
        }
    }

    cout << "Numero de errores: " << contadorErrores << '\n';

    return 0;
}
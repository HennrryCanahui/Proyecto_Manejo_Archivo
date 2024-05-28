#include <iostream>
#include <windows.h>
using namespace std;


// function para seleccionar un archivo a través de una interfaz
string seleccionarArchivo() {
    OPENFILENAME ofn;
    char fileName[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFilter = "Todos los archivos\0*.*\0";
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "";
    if (GetOpenFileName(&ofn))
        return fileName;
    return "";
}



// menu
void mostrarMenu() {
    cout << "\n===========================================================\n";
    cout << "                  MENU DE OPCIONES         \n";
    cout << "===========================================================\n";
    cout << "  1. Cifrar archivo                  ";
    cout << "  2. Descifrar archivo\n";
    cout << "  3. Lester f(2)                 ";
    cout << "  4. Juego de palabras\n";
    cout << "  5. Lester f(1)        ";
    cout << "  6. info de capetas\n";
    cout << "  7. Game                   ";
    cout << "  8. Codification binario\n";
    cout << "  9. Salir\n";
    cout << "===========================================================\n";
    cout << "  Por favor, seleccione una opcion: ";
}
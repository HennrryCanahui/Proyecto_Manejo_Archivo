#include <iostream>
#include <windows.h>
#include <shlobj.h>
using namespace std;


// funcion para seleccionar un archivo atraves de una interfaz
string seleccionarArchivo() {
    OPENFILENAME ofn;
    char fileName[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "Todos los archivos\0*.*\0";
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "";
    if (GetOpenFileName(&ofn))
        return fileName;
    return "";
}



// funcion para seleccion de carpetas atraves de una interfaz
string seleccionarCarpeta() {
    BROWSEINFO bi = {0};
    bi.lpszTitle = "Elige una carpeta:";
    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

    if (pidl != 0) {
        TCHAR path[MAX_PATH];
        if (SHGetPathFromIDList(pidl, path)) {
            return path;
        }
    }
    return "";
}

// menu
void mostrarMenu() {
    cout << "\n===========================================================\n";
    cout << "                  MENU DE OPCIONES         \n";
    cout << "===========================================================\n";
    cout << "  1. Cifrar archivo                  ";
    cout << "  2. Descifrar archivo\n";
    cout << "  3. Editar archivo                  ";
    cout << "  4. Eliminar archivo\n";
    cout << "  5. Opcion 5                        ";
    cout << "  6. Opcion 6\n";
    cout << "  7. Opcion 7                        ";
    cout << "  8. Opcion 8\n";
    cout << "  9. Salir\n";
    cout << "===========================================================\n";
    cout << "  Por favor, seleccione una opcion: ";
}
#include <iostream>
#include <windows.h>
#include <shlobj.h>
#include <string>
using namespace std;


// Función para seleccionar un archivo a través de una interfaz
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





string seleccionarCarpeta(HWND hwndOwner = nullptr) {
    BROWSEINFO bi;
    ZeroMemory(&bi, sizeof(bi));
    char buffer[MAX_PATH];

    bi.hwndOwner = hwndOwner;
    bi.pidlRoot = NULL;
    bi.pszDisplayName = buffer;
    bi.lpszTitle = "Seleccione una carpeta";
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    bi.lpfn = NULL;
    bi.lParam = 0;
    bi.iImage = 0;

    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
    if (pidl != NULL) {
        if (SHGetPathFromIDList(pidl, buffer)) {
            string folderPath(buffer);
            CoTaskMemFree(pidl); // Liberar memoria asignada para pidl
            return folderPath;
        }
        CoTaskMemFree(pidl); // Liberar memoria asignada para pidl en caso de fallo
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
    cout << "  3. Traductor binario               ";
    cout << "  4. Traductor binario a texto\n";
    cout << "  5. Info carpeta                    ";
    cout << "  6. Info ultima modificacion\n";
    cout << "  7. Game                            ";
    cout << "  8. Juego de palabras\n";
    cout << "  9. Salir\n";
    cout << "===========================================================\n";
    cout << "  Por favor, seleccione una opcion: ";
}
#include <iostream>
#include <fstream>
#include "interfaz.cpp"
#include "funciones.cpp"
/*
 * <|°_°|>
*/
using namespace std;

string Ubicacion_Carpeta_User,Ubicacion_Archivo_User;

char R_cifrado, R_descifrado,opcion, opcion_caso_uno;
int clave = 3;

int main() {
    do{
        mostrarMenu();
        cin >> opcion;
        switch (opcion) {
            case '1': {
                Ubicacion_Archivo_User = seleccionarArchivo();
                contenido = Leer_contenido(Ubicacion_Archivo_User);
                string texto_cifrado = cifrar(contenido, clave);
                Modificar_Documento(Ubicacion_Archivo_User, texto_cifrado);
                cout<<"Documento cifrado\n";
                break;
            }
            case '2': {
                Ubicacion_Archivo_User = seleccionarArchivo();
                contenido = Leer_contenido(Ubicacion_Archivo_User);
                string texto_descifrado = descifrar(contenido, clave);
                Modificar_Documento(Ubicacion_Archivo_User, texto_descifrado);
                cout<<"Documento descifrado\n";
                break;
            }

            case '3':{
                // Implementa la funcionalidad aquí
                cout << "opcion 3 seleccionado\n";
                break;
            }
            case '4':{
                // Implementa la funcionalidad aquí
                cout << "opcion 4 seleccionado\n";
                break;
            }
            case '5':{
                // Implementa la funcionalidad aquí
                cout << "opcion 5 seleccionado\n";
                break;
            }
            case '6':{
                // Implementa la funcionalidad aquí
                cout << "opcion 6 seleccionado\n";
                break;
            }
            case '7':{
                // Implementa la funcionalidad aquí
                cout << "opcion 7 seleccionado\n";
                break;
            }
            case '8':{
                // Implementa la funcionalidad aquí
                cout << "opcion 8 seleccionado\n";
                break;
            }
            case '9':{
                // Implementa la funcionalidad aquí
                cout << "opcion 9 seleccionado\n";
                break;
            }
            default:
                cout << "--------------------------------------------------------\n";
                cout << "             Opcion invalida. Intente de nuevo.\n";
                cout << "---------------------------------------------------------\n";
                system("pause");
        }

    }while(opcion <= '0');



    return 0;
}

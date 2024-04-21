#include <iostream>
#include <fstream>
#include <filesystem>
#include "interfaz.cpp"
#include "funciones.cpp"
/*
 * <|°_°|>
*/
using namespace std;
string Ubicacion_Carpeta_User,Ubicacion_Archivo_User,texto_cifrado ,contenido, copia;
char asdf;
int opcion, clave = 3;

int main() {
    cout << "selecciona una opcion 1- carpeta, 2- archivo\n" << ":";
    cin >> opcion;
    if (opcion == 1) {
        Ubicacion_Carpeta_User = seleccionarCarpeta();
    } else {
        Ubicacion_Archivo_User = seleccionarArchivo();
    }

    ifstream archivo(Ubicacion_Archivo_User);
    if(archivo.is_open()){
        cout<<"archivo entotrado"<<endl;
        while(getline(archivo, contenido)){
            copia += contenido;
        }
        archivo.close(); // Cierra el archivo después de leerlo

        cout<<"quieres cifrar el documento S /N \n:";cin>>asdf;
        if(asdf == 's' or asdf =='S'){
            texto_cifrado = cifrar(copia, clave);

            ofstream archivo_salida(Ubicacion_Archivo_User);
            if (archivo_salida.is_open()) {
                archivo_salida << texto_cifrado;
                archivo_salida.close();
                cout<<"cifrado con exito!";
            }
            cout<<"quieres descifrar el documento S /N \n:";cin>>asdf;
            if(asdf == 's' or asdf =='S') {
                string texto_descifrado = descifrar(texto_cifrado, clave);
                ofstream archivo_salida(Ubicacion_Archivo_User);
                if (archivo_salida.is_open()) {
                    archivo_salida << texto_descifrado;
                    archivo_salida.close();
                    cout << "descifrado con exito!";
                }
            }
        }
    }else{
        cout<<"no ta we"<<endl;
    }

    return 0;
}

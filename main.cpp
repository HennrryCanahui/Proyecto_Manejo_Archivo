#include <iostream>
#include <fstream>
#include "interfaz.cpp"
#include "funciones.cpp"

/*
 * <|°_°|>
*/

using namespace std;

[[maybe_unused]] string Ubicacion_Carpeta_User, Ubicacion_Archivo_User;

[[maybe_unused]] char R_cifrado, R_descifrado, opcion, opcion_caso_uno;
int clave = 3;

int main() {
    do {
        mostrarMenu();
        cin >> opcion;
        switch (opcion) {
            case '1': {
                Ubicacion_Archivo_User = seleccionarArchivo();
                string contenido = leerContenido(Ubicacion_Archivo_User);
                string texto_cifrado = cifrar(contenido, clave);
                escribirContenido(Ubicacion_Archivo_User, texto_cifrado);
                cout << "Documento cifrado\n";
                break;
            }
            case '2': {
                Ubicacion_Archivo_User = seleccionarArchivo();
                string contenido = leerContenido(Ubicacion_Archivo_User);
                string texto_descifrado = descifrar(contenido, clave);
                escribirContenido(Ubicacion_Archivo_User, texto_descifrado);
                cout << "Documento descifrado\n";
                break;
            }
            case '3': {
                // función de jr
                break;
            }
            case '4': {
                jugarAdivinanzaDePalabras();
                break;
            }
            case '5': {
                try {
                    string folderPath = obtenerRutaCarpeta();

                    if (!verificarCarpeta(folderPath)) {
                        cerr << "La carpeta especificada no existe o no es válida." << endl;
                        return 1;
                    }

                    auto [fileCount, totalSize] = recorrerArchivos(folderPath);

                    cout << "Cantidad de archivos en la carpeta: " << fileCount << endl;
                    cout << "Tamaño total de los archivos: " << totalSize << " bytes" << endl;
                } catch (const exception& e) {
                    cerr << "Error al procesar la carpeta: " << e.what() << endl;
                    return 1;
                }
                break;
            }
            case '6': {
                string ubicacionArchivoUser = seleccionarArchivo();

                ifstream file(ubicacionArchivoUser);
                cout << "file is: " << ubicacionArchivoUser;
                if (!file) {
                    cerr << "El archivo no existe en el escritorio." << endl;
                    return 1;
                }

                // Obtener y mostrar el tamaño del archivo
                long fileSize = getFileSize(ubicacionArchivoUser);
                cout << "Tamaño del archivo: " << fileSize << " bytes" << endl;

                // Obtener y mostrar la fecha de última modificación
                string lastModified = getLastModifiedTime(ubicacionArchivoUser);
                cout << "Última modificación: " << lastModified;
                break;
            }
            case '7': {
                string ubicacionArchivo = seleccionarArchivo();
                string contenido = leerContenido(ubicacionArchivo);

                int numeroAleatorio1 = generarNumeroAleatorio();
                int numeroAleatorio2 = generarNumeroAleatorio();
                cout << "¿Cual es la suma de " << numeroAleatorio1 << " y " << numeroAleatorio2 << "?\n";

                int respuesta;
                cout << "Introduce tu respuesta: ";
                cin >> respuesta;

                if (respuesta == numeroAleatorio1 + numeroAleatorio2) {
                    cout << "¡Has ganado! Tu archivo se mantiene igual." << endl;
                } else {
                    cout << "Has perdido. Tu archivo será cifrado." << endl;
                    string contenidoCifrado = cifrar(contenido, numeroAleatorio1 + numeroAleatorio2);
                    escribirContenido(ubicacionArchivo, contenidoCifrado);
                }

                break;
            }
            case '8': {
                // función de jr
                break;
            }
            default: {
                cout << "--------------------------------------------------------\n";
                cout << "             Opción inválida. Intente de nuevo.\n";
                cout << "---------------------------------------------------------\n";
                system("pause");
            }
        }
    } while (opcion <= '0');
    return 0;
}

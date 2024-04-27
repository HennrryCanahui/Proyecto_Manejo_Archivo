
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
                /*
                inicializarNcurses();

                std::string ruta = obtenerCadenaDeVentanaEmergente(5, 50, 10, 10, "Introduce la ruta del archivo:");
                std::string palabra = obtenerCadenaDeVentanaEmergente(5, 50, 17, 10, "Introduce la palabra clave:");

                try {
                    std::ifstream archivo = abrirArchivo(ruta);
                    std::vector<std::string> lineasEncontradas = buscarPalabraEnArchivo(archivo, palabra);

                    for (const auto& linea : lineasEncontradas) {
                        std::cout << linea << std::endl;
                    }
                } catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }

                endwin();
                */
                break;
            }
            case '4':{
                jugarAdivinanzaDePalabras();
                mostrarPalabrasGuardadas("D:\\Proyecto_Manejo_Archivo\\palabras.txt");
                break;
            }
            case '5':{
                try {
                    std::string folderPath = obtenerRutaCarpeta();

                    if (!verificarCarpeta(folderPath)) {
                        std::cerr << "La carpeta especificada no existe o no es válida." << std::endl;
                        return 1;
                    }

                    auto [fileCount, totalSize] = recorrerArchivos(folderPath);

                    std::cout << "Cantidad de archivos en la carpeta: " << fileCount << std::endl;
                    std::cout << "Tamaño total de los archivos: " << totalSize << " bytes" << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Error al procesar la carpeta: " << e.what() << std::endl;
                    return 1;
                }
                break;
            }
            case '6':{
                string Ubicacion_Archivo_User;


                Ubicacion_Archivo_User = seleccionarArchivo();

                ifstream file(Ubicacion_Archivo_User);
                cout<<"file is: "<< Ubicacion_Archivo_User;
                if (!file) {
                    std::cerr << "El archivo no existe en el escritorio." << endl;
                    return 1;
                }

                // Obtener y mostrar el tamaño del archivo
                long fileSize = getFileSize(Ubicacion_Archivo_User);
                cout << "Tamaño del archivo: " << fileSize << " bytes" << endl;

                // Obtener y mostrar la fecha de última modificación
                string lastModified = getLastModifiedTime(Ubicacion_Archivo_User);
                cout << "Última modificación: " << lastModified;
                break;
            }
            case '7':{
                std::string ubicacionArchivo;
                ubicacionArchivo = seleccionarArchivo();
                std::string contenido = leerContenido(ubicacionArchivo);

                int numeroAleatorio1 = generarNumeroAleatorio();
                int numeroAleatorio2 = generarNumeroAleatorio();
                std::cout << "¿Cual es la suma de " << numeroAleatorio1 << " y " << numeroAleatorio2 << "?\n";

                int respuesta;
                std::cout << "Introduce tu respuesta: ";
                std::cin >> respuesta;

                if (respuesta == numeroAleatorio1 + numeroAleatorio2) {
                    std::cout << "¡Has ganado! Tu archivo se mantiene igual." << std::endl;
                } else {
                    std::cout << "Has perdido. Tu archivo será cifrado." << std::endl;
                    std::string contenidoCifrado = cifrar(contenido, numeroAleatorio1 + numeroAleatorio2);
                    escribirContenido(ubicacionArchivo, contenidoCifrado);
                }

                break;
            }
            case '8':{
                // abrir la funcion en la otra carpeta
                /*
                cout << "\n\n\n-------------------------------------------------------------------";
                cout << "\n          Comprension y Descompresion con el Metodo de Huffman";
                cout << "\n                                 Programacion I";
                cout << "\n-----------------------------------------------------------------------";
                string text;
                cout << "\nIngrese el mensaje que desea comprimir: ";
                getline(cin, text);

                //Guarda la entrada del usuario en un archivo de texto
                ofstream outputFile("mensaje_del_usuario.txt");
                if(outputFile.is_open()){
                    outputFile << text;
                    outputFile.close();
                    cout << "\nEl mensaje se ha guardado en el archivo 'mensaje_del_usuario.txt'.\n";
                }else{
                    cout <<" \nErro al guardar el archivo.\n";
                }
                crearArbol(text);
                cout << "\n";



                 */
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

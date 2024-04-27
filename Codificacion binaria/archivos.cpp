#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
#include "archivos.h"
using namespace std;

struct Tarea {
    string descripcion;
    bool completada;
};

void guardarTareas(const vector <Tarea> & tareas) {
    ofstream archivo("tareas.txt");
    for (const auto& tarea : tareas) {
        archivo << (tarea.completada ? "1" : "0") << "\n" << tarea.descripcion << "\n";
    }
}

    vector<Tarea> cargarTareas() {
        vector<Tarea> tareas;
        ifstream archivo("tareas.txt");
    while (archivo) {
        Tarea tarea;
        string linea;
        getline(archivo, linea);
        tarea.completada = (linea == "1");
        getline(archivo, tarea.descripcion);
        if (!tarea.descripcion.empty()) {
            tareas.push_back(tarea);
        }
    }
    return tareas;
}

int main() {
    vector<Tarea> tareas = cargarTareas();

    while (true) {
        cout << "1. Agregar tarea\n2. Eliminar tarea\n3. Marcar tarea como completada\n4. Salir\n";
        int opcion;
        cin >> opcion;

        if (opcion == 1) {
            cout << "Ingrese la descripcion de la tarea: ";
            string descripcion;
            cin.ignore();
            getline(std::cin, descripcion);
            tareas.push_back({descripcion, false});
        } else if (opcion == 2) {
            cout << "Ingrese el numero de la tarea a eliminar: ";
            int numero;
            cin >> numero;
            tareas.erase(tareas.begin() + numero - 1);
        } else if (opcion == 3) {
            cout << "Ingrese el numero de la tarea a marcar como completada: ";
            int numero;
            cin >> numero;
            tareas[numero - 1].completada = true;
        } else if (opcion == 4) {
            break;
        }

        guardarTareas(tareas);
    }

    return 0;
}

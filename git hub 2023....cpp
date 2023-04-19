#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

struct Paciente {
    string nombre;
    int edad;
    double copago;
    Paciente* izq;
    Paciente* der;

    Paciente(string n, int e, double c) {
        nombre = n;
        edad = e;
        copago = c;
        izq = NULL;
        der = NULL;
    }
};

class Hospital {
private:
    map<int, Paciente*> pacientes_por_anio;

public:
    void agregar_paciente() {
        string nombre;
        int edad;
        double copago;

        cout << "Ingrese el nombre del paciente: ";
        cin >> nombre;
        cout << "Ingrese la edad del paciente: ";
        cin >> edad;
        cout << "Ingrese el valor del copago por cita del paciente: ";
        cin >> copago;

        Paciente* nuevo_paciente = new Paciente(nombre, edad, copago);

        if (pacientes_por_anio.count(edad) == 0) {
            pacientes_por_anio[edad] = nuevo_paciente;
        } else {
            Paciente* actual = pacientes_por_anio[edad];
            while (true) {
                if (nuevo_paciente->copago < actual->copago) {
                    if (actual->izq == NULL) {
                        actual->izq = nuevo_paciente;
                        break;
                    } else {
                        actual = actual->izq;
                    }
                } else {
                    if (actual->der == NULL) {
                        actual->der = nuevo_paciente;
                        break;
                    } else {
                        actual = actual->der;
                    }
                }
            }
        }
    }

    double calcular_valor_cancelado_por_paciente() {
        double total = 0;
        for (auto it = pacientes_por_anio.begin(); it != pacientes_por_anio.end(); ++it) {
            Paciente* actual = it->second;
            while (actual != NULL) {
                total += actual->copago;
                actual = actual->izq;
            }
            actual = it->second->der;
            while (actual != NULL) {
                total += actual->copago;
                actual = actual->der;
            }
        }
        return total;
    }

    void calcular_promedio_cancelado_por_anio() {
        for (auto it = pacientes_por_anio.begin(); it != pacientes_por_anio.end(); ++it) {
            int anio = it->first;
            Paciente* actual = it->second;

            vector<double> copagos;
            while (actual != NULL) {
                copagos.push_back(actual->copago);
                actual = actual->izq;
            }
            actual = it->second->der;
            while (actual != NULL) {
                copagos.push_back(actual->copago);
                actual = actual->der;
            }

            double suma = 0;
            for (int i = 0; i < copagos.size(); ++i) {
                suma += copagos[i];
            }

            double promedio = suma / copagos.size();
            cout << "Promedio de copagos para el anio " << anio << ": " << promedio << endl;
        }
    }
};

int main() {
    Hospital hospital;

    int opcion;
    do {
        cout << endl;
        cout << "Menu:" << endl;
        cout << "1. Agregar paciente" << endl;
        cout << "Calcular valor total cancelado por pacientes" << endl;
cout << "3. Calcular promedio de copagos por año" << endl;
cout << "4. Salir" << endl;
cout << "Ingrese una opcion: ";
cin >> opcion; switch (opcion) {
     case 1:
         hospital.agregar_paciente();
         break;
     case 2:
         cout << "El valor total cancelado por pacientes es: " << hospital.calcular_valor_cancelado_por_paciente() << endl;
         break;
     case 3:
         hospital.calcular_promedio_cancelado_por_anio();
         break;
     case 4:
         cout << "Saliendo del programa..." << endl;
         break;
     default:
         cout << "Opcion invalida, por favor ingrese una opcion valida." << endl;
         break;
 }
} while (opcion != 4);

return 0;
}
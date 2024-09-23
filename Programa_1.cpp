#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Definir las funciones
double funcion1(double x) {
    return (x * x) * cos(x) - 2 * x;
}

double funcion2(double x) {
    return (6 - (2 / (x * x))) * ((exp(2) + x) / 4) + 1;
}

double funcion3(double x) {
    return pow(x, 3) - 3 * sin(pow(x, 2)) + 1;
}

double funcion4(double x) {
    return pow(x, 3) + 6 * pow(x, 2) + 9.4 * x + 2.5;
}

// Funci�n para imprimir la tabla de valores
void imprimirTablaValores(double (*funcion)(double), double x_start, double x_end, int puntos) {
    cout << fixed << setprecision(6);
    
    cout << "\n=====================================\n";
    cout << "\nValores de la funci�n:\n";
    cout << "-------------------------------------\n";
    cout << "|    x    |        f(x)             |\n";
    cout << "-------------------------------------\n";
    
    for (int i = 0; i <= puntos; ++i) {
        double x = x_start + (x_end - x_start) * (i / static_cast<double>(puntos));
        double y = funcion(x);
        cout << "| " << fixed << setprecision(2) << setw(7) << x << " | " << setw(20) << y << " |\n";
    }
    cout << "=====================================\n";
}

// Pregunta si desea buscar otra ra�z
bool preguntarOtraRaiz() {
    char respuesta;
    cout << "�Desea obtener otra ra�z? (s/n): ";
    cin >> respuesta;

    return (respuesta == 's' || respuesta == 'S'); // Devuelve verdadero si elige 's'
}

// M�todo de bisecci�n
double biseccion(double (*funcion)(double), double a, double b, double tol, int max_iter) {

	cout << fixed << setprecision(6);

	double f_a = funcion(a);
	double f_b = funcion(b);
	double x, error = 1.0;
	int iter = 0;
	
	cout << "\n==========================================================================================================\n";
	cout << "Inter\t a\t b\t f(a)\t f(b)\t x\t f(x)\t error%\n";
	cout << "\n==========================================================================================================\n";
	while (iter < max_iter) {
		
		x = (a + b) / 2 ;
		double f_x = funcion(x);
		
		cout << iter + 1 << "\t" << a << "\t" << b << "\t" << f_a << "\t" << f_b << "\t" << x << "\t" << f_x;
		 if (iter > 0){
		 	error = (fabs(a - b) / fabs( a));
		 	cout << "\t" << error << "\t";
		 }	else {
		 	cout << "\tN/A\n";
		 }
		 
		 if(error < tol){
		 	cout << "se alcanzo la tolerancia" << iter+1 << "con error relativo" << error << "\n";
		 	break;
		 }
		 
		 if (f_x < 0){
		 	a = x;
		 } else {
		 	b = x;
		 }
		 iter ++;
	}
	if (iter == max_iter){
		cout << "se alcanzo el numero maximo de iteraciones sin cumplir la tolerancia\n";
	}
	cout << "\n==========================================================================================================\n";
	return x;

}
// M�todo de la secante
double secante(double (*funcion)(double), double x0, double x1, double tol, int max_iter) {
    cout << fixed << setprecision(6);
    
  double f_x0 = funcion(x0);
    double f_x1 = funcion(x1);
    double x2, error = 1.0;
    int iter = 0;

    cout << "Iter\t x0\t x1\t f(x0)\t f(x1)\t x2\t f(x2)\t Error%\n";

    while (iter < max_iter) {
        // Aplicar el m�todo de la secante
        x2 = x1 - f_x1 * (x1 - x0) / (f_x1 - f_x0);
        double f_x2 = funcion(x2);
        
        // Imprimir los resultados de cada iteraci�n
        cout << "\n==========================================================================================================\n";
        cout << iter + 1 << "\t" << x0 << "\t" << x1 << "\t" << f_x0 << "\t" << f_x1 << "\t" << x2 << "\t" << f_x2;
		cout << "\n==========================================================================================================\n";
        // Calcular el error relativo, excepto en la primera iteraci�n
        if (iter > 0) {
            error = (fabs(x1 - x0) / fabs( x1));
            cout << "\t" << error << "\n";  // Imprimir error en iteraciones posteriores
        } else {
            cout << "\tN/A\n";  // No se puede calcular error en la primera iteraci�n
        }

        // Verificar el criterio de parada
        if (error < tol) {
            cout << "Se alcanz� la tolerancia en la iteraci�n " << iter + 1 << " con error relativo " << error << "\n";
            break;
        }

        // Actualizar los valores para la siguiente iteraci�n
        
        x0 = x1;
        //f_x0 = f_x1;
        x1 = x2;
        //f_x1 = f_x2;

        iter++;
    }

    if (iter == max_iter) {
        cout << "Se alcanz� el n�mero m�ximo de iteraciones sin cumplir la tolerancia.\n";
    }

	cout << "\n==========================================================================================================\n";
    return x2;  // Devuelve la ra�z aproximada
}




// Men� de funciones
// Men� de funciones
void menuFunciones(int metodo) {
    int opcion;
    double a, b, tol;
    int max_iter;

    do {
        cout << "\nSelecciona la funci�n:\n";
        cout << "1. f(x) = (x^2)cos(x) - 2x\n";
        cout << "2. f(x) = (6 - (2/x^2))((e^2+x)/4) + 1\n";
        cout << "3. f(x) = x^3 - 3sen(x^2) + 1\n";
        cout << "4. f(x) = x^3 + 6x^2 + 9.4x + 2.5\n";
        cout << "5. Salir al men� de m�todos\n";
        cout << "Opci�n: ";
        cin >> opcion;

        if (opcion == 5) {
            break; // Regresa al men� de m�todos
        }

        double (*funcion)(double);
        switch (opcion) {
            case 1: funcion = funcion1; break;
            case 2: funcion = funcion2; break;
            case 3: funcion = funcion3; break;
            case 4: funcion = funcion4; break;
            default: cout << "Opci�n inv�lida.\n"; continue;
        }


        imprimirTablaValores(funcion, -10.0, 10.0, 20);
        
        cout << "\nPresione ENTER para continuar...";
        cin.ignore();  
        cin.get();  

        // Pedir par�metros para el m�todo
        if (metodo == 1) { // Bisecci�n
            cout << "Ingrese el intervalo (a b): ";
            cout << "a: ";
            cin >> a;
            cout << "b: ";
            cin >> b;
            cout << "Ingrese el m�ximo de iteraciones: ";
            cin >> max_iter;
            cout << "Ingrese la tolerancia: ";
            cin >> tol;
            biseccion(funcion, a, b, tol, max_iter);  // Ahora se llama a la funci�n de bisecci�n correctamente
        } else if (metodo == 2) { // Secante
            double x0, x1;
            cout << "Ingrese el valor inicial (x0 y x1): ";
            cout << "x0: ";
            cin >> x0;
            cout << "x1: ";
            cin >> x1;
            cout << "Ingrese el m�ximo de iteraciones: ";
            cin >> max_iter;
            cout << "Ingrese la tolerancia: ";
            cin >> tol;
            secante(funcion, x0, x1, tol, max_iter);  // Llamar correctamente a la funci�n secante
        }

    } while (preguntarOtraRaiz());  // Pregunta si quiere otra ra�z
}
// Men� de m�todos
void menuMetodos() {
    int metodo;

    do {
        cout << "\nSelecciona el m�todo:\n";
        cout << "1. Bisecci�n\n";
        cout << "2. Secante\n";
        cout << "3. Salir\n";
        cout << "Opci�n: ";
        cin >> metodo;

        if (metodo == 3) {
            cout << "Saliendo del programa.\n";
            break;
        }

        menuFunciones(metodo);  // Llama al men� de funciones con el m�todo seleccionado

    } while (true);
}

// Funci�n principal
int main() {
    menuMetodos();  // Llama al men� de m�todos
    return 0;
}

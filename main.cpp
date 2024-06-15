#include <iostream>
#include <cmath>
#include <functional>

// Función que implementa el método de la secante
double metodoSecante(std::function<double(double)> func, double x0, double x1, double tolerancia, int maxIter) {
    double f0 = func(x0);
    double f1 = func(x1);
    double x2;

    for (int iter = 0; iter < maxIter; ++iter) {
        if (std::fabs(f1 - f0) < 1e-15) { // Evitar división por cero
            std::cerr << "Diferencia de función muy pequeña, posible división por cero." << std::endl;
            return x1;
        }

        x2 = x1 - f1 * (x1 - x0) / (f1 - f0); // Fórmula del método de la secante

        if (std::fabs(x2 - x1) < tolerancia) { // Comprobar si la convergencia es suficiente
            std::cout << "Convergencia alcanzada después de " << iter + 1 << " iteraciones." << std::endl;
            return x2;
        }

        // Actualizar para la siguiente iteración
        x0 = x1;
        f0 = f1;
        x1 = x2;
        f1 = func(x1);
    }

    std::cerr << "No se alcanzó la convergencia después de " << maxIter << " iteraciones." << std::endl;
    return x2;
}

// Función de ejemplo 1: f(x) = x^2 - 2
double funcionEjemplo1(double x) {
    return x * x - 2;}

// Función de ejemplo 2: f(x) = cos(x) - x
double funcionEjemplo2(double x) {
    return std::cos(x) - x;
}

// Función de ejemplo 3: f(x) = e^x - 3x
double funcionEjemplo3(double x) {
    return std::exp(x) - 3 * x;
}

int main() {
    int opcion;
    double x0, x1, tolerancia;
    int maxIter;

    std::cout << "Seleccione la función a utilizar:\n";
    std::cout << "1. f(x) = x^2 - 2\n";
    std::cout << "2. f(x) = cos(x) - x\n";
    std::cout << "3. f(x) = e^x - 3x\n";
    std::cin >> opcion;

    std::cout << "Ingrese el primer valor inicial x0: ";
    std::cin >> x0;
    std::cout << "Ingrese el segundo valor inicial x1: ";
    std::cin >> x1;
    std::cout << "Ingrese la tolerancia: ";
    std::cin >> tolerancia;
    std::cout << "Ingrese el número máximo de iteraciones: ";
    std::cin >> maxIter;

    std::function<double(double)> func;

    switch (opcion) {
        case 1:
            func = funcionEjemplo1;
            break;
        case 2:
            func = funcionEjemplo2;
            break;
        case 3:
            func = funcionEjemplo3;
            break;
        default:
            std::cerr << "Opción inválida." << std::endl;
            return -1;
    }

    double raiz = metodoSecante(func, x0, x1, tolerancia, maxIter);

    std::cout << "Una raíz aproximada es: " << raiz << std::endl;

    return 0;
}

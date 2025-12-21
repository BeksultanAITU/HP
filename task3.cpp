#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <omp.h>  // Для OpenMP

int main() {
    const int SIZE = 1000000;  // Размер массива

    // Динамическое выделение памяти
    int* arr = new int[SIZE];

    // Инициализация генератора случайных чисел
    std::srand(std::time(nullptr)); 

    // Заполнение массива случайными числами от 1 до 100
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = std::rand() % 100 + 1;  // Генерация случайного числа
    }

    // Последовательный поиск (для сравнения)
    int min_val = arr[0];
    int max_val = arr[0];

    // Замер времени для последовательного поиска
    auto start_seq = std::chrono::high_resolution_clock::now();

    for (int i = 1; i < SIZE; ++i) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
    }

    auto end_seq = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_seq = end_seq - start_seq;

    // Параллельный поиск с использованием OpenMP
    int min_val_par = arr[0];
    int max_val_par = arr[0];

    // Замер времени для параллельного поиска
    auto start_par = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for reduction(min: min_val_par) reduction(max: max_val_par)
    for (int i = 1; i < SIZE; ++i) {
        if (arr[i] < min_val_par) min_val_par = arr[i];
        if (arr[i] > max_val_par) max_val_par = arr[i];
    }

    auto end_par = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_par = end_par - start_par;

    // Вывод результатов
    std::cout << "Sequential Min: " << min_val << ", Max: " << max_val << std::endl;
    std::cout << "Parallel Min: " << min_val_par << ", Max: " << max_val_par << std::endl;
    std::cout << "Sequential Time: " << duration_seq.count() << " seconds" << std::endl;
    std::cout << "Parallel Time: " << duration_par.count() << " seconds" << std::endl;

    // Освобождение памяти
    delete[] arr;

    return 0;
}

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <omp.h>  // Для OpenMP

int main() {
    const int SIZE = 5000000;  // Размер массива

    // Динамическое выделение памяти
    int* arr = new int[SIZE];

    // Инициализация генератора случайных чисел
    std::srand(std::time(nullptr)); 

    // Заполнение массива случайными числами от 1 до 100
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = std::rand() % 100 + 1;  // Генерация случайного числа
    }

    // Последовательное вычисление среднего значения
    auto start_seq = std::chrono::high_resolution_clock::now();
    
    int sum_seq = 0;
    for (int i = 0; i < SIZE; ++i) {
        sum_seq += arr[i];
    }

    double average_seq = static_cast<double>(sum_seq) / SIZE;
    auto end_seq = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_seq = end_seq - start_seq;

    // Параллельное вычисление среднего значения с использованием OpenMP и редукции
    auto start_par = std::chrono::high_resolution_clock::now();
    
    int sum_par = 0;

    #pragma omp parallel for reduction(+: sum_par)
    for (int i = 0; i < SIZE; ++i) {
        sum_par += arr[i];
    }

    double average_par = static_cast<double>(sum_par) / SIZE;
    auto end_par = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_par = end_par - start_par;

    // Вывод результатов
    std::cout << "Sequential Average: " << average_seq << std::endl;
    std::cout << "Parallel Average: " << average_par << std::endl;
    std::cout << "Sequential Time: " << duration_seq.count() << " seconds" << std::endl;
    std::cout << "Parallel Time: " << duration_par.count() << " seconds" << std::endl;

    // Освобождение памяти
    delete[] arr;

    return 0;
}

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>  // Для замера времени

int main() {
    const int SIZE = 1000000;  // Размер массива

    // Динамическое выделение памяти для массива
    int* arr = new int[SIZE];

    // Инициализация генератора случайных чисел
    std::srand(std::time(nullptr)); 

    // Заполнение массива случайными числами от 1 до 100
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = std::rand() % 100 + 1; // Генерация случайного числа
    }

    // Замер времени начала выполнения алгоритма
    auto start = std::chrono::high_resolution_clock::now();

    // Поиск минимального и максимального элементов
    int min_val = arr[0];
    int max_val = arr[0];

    for (int i = 1; i < SIZE; ++i) {
        if (arr[i] < min_val) min_val = arr[i];  // Обновляем минимальное значение
        if (arr[i] > max_val) max_val = arr[i];  // Обновляем максимальное значение
    }

    // Замер времени конца выполнения алгоритма
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;  // Время выполнения

    // Вывод результатов
    std::cout << "Sequential Min: " << min_val << ", Max: " << max_val << std::endl;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

    // Освобождение памяти
    delete[] arr;

    return 0;
}

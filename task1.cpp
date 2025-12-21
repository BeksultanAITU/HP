#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Определяем размер массива
    const int SIZE = 50000;
    
    // Динамическое выделение памяти под массив целых чисел
    int* arr = new int[SIZE];
    
    // Инициализация генератора случайных чисел с текущим временем
    std::srand(std::time(nullptr)); 
    
    // Переменная для хранения суммы элементов массива
    int sum = 0;
    
    // Заполнение массива случайными числами от 1 до 100
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = std::rand() % 100 + 1; // Генерация случайного числа
        sum += arr[i]; // Добавляем число в сумму
    }

    // Вычисление среднего значения массива
    double average = static_cast<double>(sum) / SIZE;
    std::cout << "Average value of array elements: " << average << std::endl;

    // Освобождение памяти после использования массива
    delete[] arr;
    
    return 0;
}

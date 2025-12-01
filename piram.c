#include <stdio.h>

// Функция восстановления свойства кучи (просеивание вниз)
void heapify(int arr[], int n, int i) {
    int largest = i;          // Изначально считаем корень наибольшим
    int left = 2 * i + 1;     // Левый потомок
    int right = 2 * i + 2;    // Правый потомок

    // Если левый потомок больше корня
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Если правый потомок больше текущего наибольшего
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Если наибольший элемент не корень
    if (largest != i) {
        // Меняем местами
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Рекурсивно применяем heapify к затронутому поддереву
        heapify(arr, n, largest);
    }
}

// Основная функция пирамидальной сортировки
void heapSort(int arr[], int n) {
    // Построение кучи (перегруппировка массива)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Извлечение элементов из кучи один за другим
    for (int i = n - 1; i > 0; i--) {
        // Переместить текущий корень в конец
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Вызвать heapify на уменьшенной куче
        heapify(arr, i, 0);
    }
}

// Вспомогательная функция для вывода массива
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

// Пример использования
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Исходный массив: ");
    printArray(arr, n);

    heapSort(arr, n);

    printf("Отсортированный массив: ");
    printArray(arr, n);

    return 0;
}
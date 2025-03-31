#include <stdio.h>

void arr_input(int *arr, int size) { // функция для ввода чисел в массив
    for (int i = 0; i < size; i++) {
        int input;
        if (scanf("%d", &input) != 1) {
            return;
        }
        arr[i] = input;
    }
}

void swap(int *a, int *b) { // функция swap для смены значений

    int temp = *a;
    *a = *b;
    *b = temp;

}

void heapify(int *arr, int size, int root) { // функция heapify для создания кучи и смены значений идя по ветке дерева. arr - массив для сортировки, size - размер arr, root - корневой узел кучи, а также индекс arr

    // создаем значения для наибольшего и следующих(левого/правого)значений
    int largest = root;
    int left_leaf = 2 * root + 1;
    int right_leaf = 2 * root + 2;

    // проверяем зачения слева и справа, если одно больше другого, то становится наибольшим
    if (left_leaf < size && arr[left_leaf] > arr[largest]) {
        largest = left_leaf;
    }

    if (right_leaf < size && arr[right_leaf] > arr[largest]) {
        largest = right_leaf;
    }

    // если наибольшее не равно корневому узлу, то рекурсией преобразуем затронутую ветку
    if (largest != root) {
        swap(&arr[root], &arr[largest]);
        heapify(arr, size, largest);
    }
}

void heap_sort(int *arr, int size) { // основная функция для сортировки массива

    for (int i = size / 2 - 1; i >= 0; i--) { // создаем кучу на массиве
        heapify(arr, size, i);
    }

    for (int i = size - 1; i >= 0; i--) { // извлекаем элементы из кучи
        swap(&arr[0], &arr[i]); // кидаем текущий корень в конец
        heapify(arr, i, 0); // проходимся по меньшей куче
    }
}

int main() { // управляющая функция

    int N;

    if (scanf("%d", &N)!=1) { //валдидация пользовательской длины массива
        return 0;
    };

    int arr[N]; // массив

    arr_input(arr, N);
    heap_sort(arr, N);

    for (int i = 0; i < N; i++) { // печатаем массив
        printf("%d ", arr[i]);
    }
    return 0;
}

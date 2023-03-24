#include <stdio.h>

// Selection Sort
void selectionSort(int arr[], int size) {
    for(int i = 0; i < size - 1; i++) {
        // First : Pick ( i ) th data
        int min = i; 

        // Second : Find the data smaller then arr[min] from i + 1 to size
        for(int j = i + 1; j < size; j++) {
            if(arr[min] > arr[j]) min = j;
        }

        // Third : Swap arr[min] ( : Minimum value), arr[i] ( : Now location)
        if(min != i) {
            int tmp = arr[min];
            arr[min] = arr[i];
            arr[i] = tmp;
        }
    }
}

int main(void) {
    int n = 10;
    int arr[10] = {9, 7, 5, 3, 1, 10, 8, 6, 4, 2};

    selectionSort(arr, n);

    // Debug Print
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    return 0;
}
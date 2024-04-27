#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void swap(int Ls[], int i, int j) {
    int temp = Ls[i];
    Ls[i] = Ls[j];
    Ls[j] = temp;
}

int part(int Ls[], int lo, int hi, int pInd) {
    swap(Ls, pInd, lo);
    int pivPos, lt, rt;
    int pv;
    lt = lo + 1;
    rt = hi;
    pv = Ls[lo];
    while (lt < rt) {
        for (; lt <= hi && Ls[lt] <= pv; lt++);
        for (; Ls[rt] > pv; rt--);
        if (lt < rt) {
            swap(Ls, lt, rt);
            lt++;
            rt--;
        }
    }
    if (Ls[lt] < pv && lt <= hi)
        pivPos = lt;
    else
        pivPos = lt - 1;
    swap(Ls, lo, pivPos);
    return pivPos;
}

int qselect(int L[], int n, int k) {
    int pivot = 0;
    int lo = 0;
    int hi = n - 1;
    int pivotIndex = part(L, lo, hi, pivot);
    if (k < pivotIndex)
        return qselect(L, pivotIndex, k);
    else if (k > pivotIndex)
        return qselect(L + pivotIndex + 1, n - pivotIndex - 1, k - pivotIndex - 1);
    else
        return pivotIndex;
}

void quicksort(int Ls[], int lo, int hi) {
    if (lo < hi) {
        int pInd = qselect(Ls + lo, hi - lo + 1, (hi - lo + 1) / 2);
        int pivPos = part(Ls, lo, hi, lo + pInd); // Partition the array
        quicksort(Ls, lo, pivPos - 1); // Recursively sort the left subarray
        quicksort(Ls, pivPos + 1, hi); // Recursively sort the right subarray
    }
}

int main() {
    FILE* fptr = fopen("int0.txt", "r");
    int* array = (int*)malloc(1000 * sizeof(int));
    for (int i = 0; i < 1000; i++) {
        fscanf(fptr, "%d", &array[i]);
    }
    fclose(fptr);

    double time_taken;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    quicksort(array, 0, 999);
    gettimeofday(&end, NULL);

    printf("Sorted array: ");
    for (int i = 0; i < 1000; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    time_taken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1e-6;
    printf("Time taken: %lf seconds\n", time_taken);

    free(array);
    return 0;
}

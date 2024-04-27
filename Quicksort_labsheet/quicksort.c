#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct Person {
    int id;
    char *name;
    int age;
    int height;
    int weight;
} Person;

// Swap function to exchange two elements in an array
void swap(int Ls[], int i, int j) {
    int temp = Ls[i];
    Ls[i] = Ls[j];
    Ls[j] = temp;
}

int threePart(int Ls[], int lo, int hi, int pInd) {
    swap(Ls, pInd, hi-1);
    int pivPos, lt, rt, mid;
    int pv;
    lt = lo;
    rt = hi-2;
    mid = lo;
    pv = Ls[hi-1];
    while (mid <= rt) {
        if (Ls[mid] < pv) {
            swap(Ls, lt, mid);
            lt++;
            mid++;
        }
        else if (Ls[mid] > pv) {
            swap(Ls, mid, rt);
            rt--;
        }
        else {
            mid++;
        }
    }
    swap(Ls, mid, hi-1);
    return mid;
}
// Ls[lo..hi] is the input array; Ls[pInd] is the pivot
int part(int Ls[], int lo, int hi, int pInd) {
    swap(Ls, pInd, lo);
    int pivPos, lt, rt;
    int pv;
    lt = lo + 1;
    rt = hi;
    pv = Ls[lo];
    while (lt < rt) {
        for (; lt <= hi && Ls[lt] <= pv; lt++);
        // Ls[j]<=pv  for j in lo..lt-1
        for (; Ls[rt] > pv; rt--);
        // Ls[j]>pv  for j in rt+1..hi
        if (lt < rt) {
            swap(Ls, lt, rt);
            lt++;
            rt--;
        }
    }
    if (Ls[lt] < pv && lt <= hi)
        pivPos = lt;
    else
        pivPos = lt- 1;
    swap(Ls, lo, pivPos);
    // Postcond.: (Ls[j]<=pv for j in lo..pivPos-1) and (Ls[j]>pv for j in pivPos+1..hi)
    return pivPos;
}

int lomuto_part(int Ls[], int lo, int hi, int pInd) {
    swap(Ls, pInd, hi);
    int pv = Ls[hi];
    int i = lo - 1;
    for (int j = lo; j < hi; j++) {
        if (Ls[j] < pv) {
            i++;
            swap(Ls, i, j);
        }
    }
    swap(Ls, i + 1, hi);
    return i + 1;
}

int qselect(int L[], int n, int k) {
    int pivot = 0;
    int lo = 0;
    int hi = n - 1;
    int pInd = part(L, lo, hi, pivot);
    if (k <= pInd)
        return qselect(L, pInd, k);
    else if (k > pInd + 1)
        return qselect(L + pInd + 1, n - pInd - 1, k - pInd - 1);
    else
        return pInd;
}

void quicksort(int Ls[], int lo, int hi) {
    if (lo < hi) {
        int pInd = qselect(Ls + lo, hi - lo + 1, (hi - lo + 1) / 2);
        int pivPos = part(Ls, lo, hi, pInd); // Partition the array
        quicksort(Ls, lo, pivPos - 1); // Recursively sort the left subarray
        quicksort(Ls, pivPos + 1, hi); // Recursively sort the right subarray
    }
}

int main() {
    FILE* fptr = fopen("int0.txt", "r");
    int* array = (int*)malloc(1000*sizeof(int));
    for(int i = 0; i<1000; i++) {
        fscanf(fptr, "%d", &array[i]);
    }
    double time_taken;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    quicksort(array, 0, 999);
    gettimeofday(&end, NULL);
    for(int i = 0; i<1000; i++) {
        printf("%d ", array[i]);
    }
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    printf("\nTime taken: %lf\n", time_taken);
    fclose(fptr);
    return 0;
}

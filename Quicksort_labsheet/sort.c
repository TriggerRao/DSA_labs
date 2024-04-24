#include <stdio.h>
#include <stdlib.h>

typedef struct person {
    int id;
    char *name;
    int age;
    int height;
    int weight;
} Person;

// Swap function to exchange two elements in an array
void swap(Person Ls[], int i, int j) {
    Person temp = Ls[i];
    Ls[i] = Ls[j];
    Ls[j] = temp;
}

int threePart(Person Ls[], int lo, int hi, int pInd) {
    swap(Ls, pInd, hi-1);
    int pivPos, lt, rt, mid;
    Person pv;
    lt = lo;
    rt = hi-2;
    mid = lo;
    pv = Ls[hi-1];
    while (mid <= rt) {
        if (Ls[mid].height < pv.height) {
            swap(Ls, lt, mid);
            lt++;
            mid++;
        }
        else if (Ls[mid].height > pv.height) {
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
int part(Person Ls[], int lo, int hi, int pInd) {
    swap(Ls, pInd, lo);
    int pivPos, lt, rt;
    Person pv;
    lt = lo + 1;
    rt = hi;
    pv = Ls[lo];
    while (lt < rt) {
        for (; lt <= hi && Ls[lt].height <= pv.height; lt++);
        // Ls[j]<=pv  for j in lo..lt-1
        for (; Ls[rt].height > pv.height; rt--);
        // Ls[j]>pv  for j in rt+1..hi
        if (lt < rt) {
            swap(Ls, lt, rt);
            lt++;
            rt--;
        }
    }
    if (Ls[lt].height < pv.height && lt <= hi)
        pivPos = lt;
    else
        pivPos = lt- 1;
    swap(Ls, lo, pivPos);
    // Postcond.: (Ls[j]<=pv for j in lo..pivPos-1) and (Ls[j]>pv for j in pivPos+1..hi)
    return pivPos;
}

void quicksort(Person Ls[], int lo, int hi) {
    if (lo < hi) {
        int pInd = (lo + hi) / 2; // Choose a pivot index (can be optimized)
        int pivPos = part(Ls, lo, hi, pInd); // Partition the array
        quicksort(Ls, lo, pivPos - 1); // Recursively sort the left subarray
        quicksort(Ls, pivPos + 1, hi); // Recursively sort the right subarray
    }
}

int main() {
    FILE* fptr = fopen("dat1000.csv", "r");
    Person* array = (Person*)malloc(1000*sizeof(Person));
    for(int i = 0; i<1000; i++) {
        array[i].name = (char*)malloc(100*sizeof(char));
        fscanf(fptr, "%d, %[^,], %d, %d, %d", &array[i].id, array[i].name, &array[i].age, &array[i].height, &array[i].weight);
    } 
    quicksort(array, 0, 999);
    for(int i = 0; i<1000; i++) {
        printf("%d ", array[i].height);
    }
    printf("\n");
    fclose(fptr);
    return 0;
}
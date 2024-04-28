#include <stdio.h>
#include <stdlib.h>

struct heap {
    int *data;
    int size;
    int capacity;
    int depth;
};
typedef struct heap* Heap;

Heap heap_create() {
    Heap h = malloc(sizeof(struct heap));
    h->data = malloc(sizeof(int));
    h->size = 0;
    h->capacity = 1;
    h->depth = 0;
    return h;
}

void add_to_heap(Heap h, int value) {
    if (h->size == h->capacity) {
        h->capacity *= 2;
        h->data = realloc(h->data, h->capacity * sizeof(int));
    }
    h->data[h->size] = value;
    h->size++;
    if(1<<(h->depth+1)-1<h->size) h->depth++;
    for(int i = (h->size); i >= 0; i/=2) {
        if(h->data[i-1]>h->data[i/2 - 1]) {
            int temp = h->data[i-1];
            h->data[i-1] = h->data[i/2 - 1];
            h->data[i/2 - 1] = temp;
        }
        else break;
    }
}

int parent(Heap h, int index) {
    return (index-1)/2;
}

int left_child(Heap h, int index) {
    int left = 2*index+1;
    return left;
}

int right_child(Heap h, int index) {    
    int right = 2*index + 2;
    return right;
}

void max_heapify(Heap h, int index) {
    int left = left_child(h, index);
    int right = right_child(h, index);
    int largest = index;
    if (left < h->size && h->data[left] > h->data[largest]) largest = left;
    if (right < h->size && h->data[right] > h->data[largest]) largest = right;
    if (largest != index)
    {
        int temp = h->data[index];
        h->data[index] = h->data[largest];
        h->data[largest] = temp;
        max_heapify(h, largest);
    } 
}

Heap build_max_heap(Heap h) {
    for(int i = h->size/2; i >= 1; i--) {
        max_heapify(h, i-1);
    }
    return h;
}

void min_heapify(Heap h, int index) {
    int left = left_child(h, index);
    int right = right_child(h, index);
    int smallest = index;
    if (left < h->size && h->data[left] < h->data[smallest]) smallest = left;
    if (right < h->size && h->data[right] < h->data[smallest]) smallest = right;
    if (smallest != index)
    {
        int temp = h->data[index];
        h->data[index] = h->data[smallest];
        h->data[smallest] = temp;
        min_heapify(h, smallest);
    } 
}

Heap build_min_heap(Heap h) {
    for(int i = h->size/2; i >= 0; i--) {
        min_heapify(h, i);
    }
    return h;
}

int no_nodes(Heap h, int depth) {
    if(depth==h->depth) return h->size - (1<<h->depth) + 1;
    else if(depth<h->depth) return 1<<(depth+1) - 1;
    else return 0;
}

void heap_sort(Heap h) {
    h = build_max_heap(h);
    for (int i = h->size - 1; i >= 1; i--) {
        // printf("%d %d\n", h->size, h->data[0]);
        int temp = h->data[0];
        h->data[0] = h->data[i];
        h->data[i] = temp;
        h->size = h->size - 1;
        max_heapify(h, 0);
    }
    // printf("%d\n", h->data[0]);
}

void printHeap(Heap h) {
    for(int i = 0; i < h->size; i++) {
        printf("%d ", h->data[i]);
    }
    printf("\n");
}

int main() {
    Heap h = heap_create();
    add_to_heap(h, 10);
    add_to_heap(h, 20);
    add_to_heap(h, 15);
    add_to_heap(h, 40);
    add_to_heap(h, 50);
    add_to_heap(h, 100);
    add_to_heap(h, 25);
    add_to_heap(h, 45);
    add_to_heap(h, 30);
    add_to_heap(h, 35);
    printHeap(h);
    heap_sort(h);
    for(int i = 0; i < 10; i++) {
        printf("%d ", h->data[i]);
    }
    printf("\n");
    return 0; 
}

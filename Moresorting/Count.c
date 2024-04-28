#include <stdio.h>
#include <stdlib.h>

void preprocess(int *numbers, int n, int k, int *count, int *min, int *max) {
    *min = k; // Initialize min to a large value
    *max = 0; // Initialize max to a small value
    
    // Initialize count array
    for (int i = 0; i <= k; i++) {
        count[i] = 0;
    }
    
    // Process input numbers
    for (int i = 0; i < n; i++) {
        int num = numbers[i];
        count[num]++;
        if (num < *min) {
            *min = num;
        }
        if (num > *max) {
            *max = num;
        }
    }
}

int main() {
    int n, k;
    printf("Enter the number of integers (n): ");
    scanf("%d", &n);
    printf("Enter the maximum value (k): ");
    scanf("%d", &k);
    
    int 

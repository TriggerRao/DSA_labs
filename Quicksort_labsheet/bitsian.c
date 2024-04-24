#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

typedef struct bitsian {
    char name[50];
    char rollno[20];
} bitsian;

void swap1(bitsian arr[], int i, int j) {
    bitsian temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int inptr(char* rollno, char**ptr) {
    char branch[2];
    strncpy(branch, rollno+4, 2);
    branch[2] = '\0';
    // printf("%s\n", branch);
    for(int i = 0; i<7; i++) {
        for(int j = 0; j<2; j++) {
            if(branch[j] != ptr[i][j]) {
                break;
            }
            if(j == 1) {
                return 1;
            }
        }
    }
    return 0;
}

void segregate(bitsian* arr, char** ptr, int size) {
    int left = 0, right = size - 1;
    while (left < right) {
        while (inptr(arr[left].rollno, ptr) && left < right)
            left++;
        while (!inptr(arr[right].rollno, ptr) && left < right)
            right--;
        if (left < right) {
            swap1(arr, left, right);
            left++;
            right--;
        }
    }
}

int main() {
    FILE* fptr = fopen("bitsians.csv", "r");
    if (fptr == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int siz = 1028;
    if (fgets(line, sizeof(line), fptr) != NULL) {
        printf("Read line: %s\n", line); // Print the line read by fgets
        if (sscanf(line, "%d", &siz) != 1) { // Note the space after %d
            printf("Error assigning size\n");
        }
    } else {
        printf("Error reading array size.\n");
        fclose(fptr);
        return 1;
    }

    bitsian* array = (bitsian*)malloc(siz * sizeof(bitsian));
    if (array == NULL) {
        printf("Memory allocation failed.\n");
        fclose(fptr);
        return 1;
    }

    for (int i = 0; i < siz; i++) {
        if (fgets(line, sizeof(line), fptr) != NULL) {
            char* rollno = strtok(line, ",");
            char* name = strtok(NULL, "\n");
            if (rollno != NULL && name != NULL) {
                strcpy(array[i].rollno, rollno);
                strcpy(array[i].name, name);
            } else {
                printf("Error reading data from file.\n");
                free(array);
                fclose(fptr);
                return 1;
            }
        } else {
            printf("Error reading data from file.\n");
            free(array);
            fclose(fptr);
            return 1;
        }
    }

    printf("Original array: of size %d\n", siz);
    for (int i = 0; i < siz; i++) {
        // printf("%s %s\n", array[i].rollno, array[i].name);
    }

    fclose(fptr);
    char* ptr[7] = {"AB", "A2", "B1", "B2", "B3", "B4", "B5"};
    segregate(array, ptr, siz);
    for(int i = 0; i<siz; i++) {
        printf("%s\n", array[i].rollno);
    }
    free(array);
    return 0;
}

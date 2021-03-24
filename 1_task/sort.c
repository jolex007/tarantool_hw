#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <memory.h>
#include "fibers/api.h"

Scheduler* scheduler;

char** filenames;
size_t file_id;
size_t sorted_files;
size_t num_of_files;
int* sizes;
int** numbers_in_file;


size_t
count_of_numbers_in_file(FILE* file) {
    size_t size = 0;
    int num;
    while (fscanf(file, "%d", &num) > 0) {
        size++;
    }
    return size;
}

void
read_numbers(int* numbers, size_t size, FILE* file) {
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &numbers[i]);
    }
}

void
my_merge(int* to, int* beg_1, int* end_1, int* beg_2, int* end_2) {
    while (beg_1 < end_1 || beg_2 < end_2) {
        if (beg_1 == end_1) {
            *to = *beg_2;
            beg_2++;
        } else if (beg_2 == end_2) {
            *to = *beg_1;
            beg_1++;
        } else if (*beg_1 < *beg_2) {
            *to = *beg_1;
            beg_1++;
        } else {
            *to = *beg_2;
            beg_2++;
        }
        to++;
    }
}

void
my_mergesort(size_t begin, size_t end, int* numbers, int* buffer) {
    if (end - begin == 1) {
        return;
    }

    size_t med = (begin + end) / 2;
    my_mergesort(begin, med, numbers, buffer);
    my_mergesort(med, end, numbers, buffer);

    memcpy(buffer + begin, numbers + begin, (end - begin) * sizeof(int));

    my_merge(numbers + begin, buffer + begin, buffer + med, buffer + med, buffer + end);
}

void
sort_file() {
    int file_num = file_id++;
    char* filename = filenames[file_num];
    

    FILE* file = fopen(filename, "r");
    size_t size = count_of_numbers_in_file(file);
    sizes[file_num] = size;
    
    
    int* numbers = malloc(size * sizeof(int));
    numbers_in_file[file_num] = numbers;
    int* buffer = malloc(size * sizeof(int));

    

    fclose(file);
    file = fopen(filename, "r");

    read_numbers(numbers, size, file);

    fclose(file);
    file = fopen(filename, "w");

    my_mergesort(0, size, numbers, buffer);

    for (size_t i = 0; i < size; i++) {
        fprintf(file, "%d ", numbers[i]);
    }

    fclose(file);
    free(buffer);
    sorted_files++;
}

void
merge_files() {
    if (sorted_files < num_of_files) {
        Yield();
    }

    FILE* result_file = fopen("result.txt", "w");
    
    size_t iter[sorted_files];
    memset(iter, 0, sorted_files * sizeof(size_t));

    size_t ready = 0;
    while (ready < sorted_files) {
        int min = INT32_MAX;
        int n_min;
        for (int i = 0; i < sorted_files; i++) {
            if (iter[i] < sizes[i] && numbers_in_file[i][iter[i]] < min) {
                min = numbers_in_file[i][iter[i]];
                n_min = i;
            }
        }

        fprintf(result_file, "%d ", min);
        iter[n_min]++;

        if (iter[n_min] == sizes[n_min]) {
            ready++;
        }
    }

    fclose(result_file);
}

int
main(int argc, char* argv[]) {

    scheduler = malloc(sizeof(Scheduler));
    SetupScheduler(scheduler);

    filenames = &argv[1];
    file_id = 0;
    sorted_files = 0;
    num_of_files = argc - 1;
    sizes = malloc(num_of_files * sizeof(int));
    numbers_in_file = malloc(num_of_files * sizeof(int*));



    for (int i = 1; i < argc; i++) {
        SpawnFiber(sort_file, scheduler);
    }
    SpawnFiber(merge_files, scheduler);

    RunScheduler(scheduler);

    for (int i = 0; i < num_of_files; i++) {
        free(numbers_in_file[i]);
    }
    free(sizes);
    free(numbers_in_file);
    free(scheduler);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20000
#define SIZE_COUNT 6
#define SEED 12345


long long count = 0;


int make_random(void)
{
    return ((rand() << 15) | rand()) % 1000001;
}


void copy_array(int src[], int dst[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        dst[i] = src[i];
}


int is_sorted(int a[], int n)
{
    int i;
    for (i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1])
            return 0;
    }
    return 1;
}

/* 1) 삽입 정렬 */
void insertion_sort(int a[], int n)
{
    int i, j, key;

    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;

        while (j >= 0) {
            count++;               
            if (a[j] > key) {
                a[j + 1] = a[j];
                j--;
            } else {
                break;
            }
        }
        a[j + 1] = key;
    }
}

/*
 * 2)  간격 gap으로 정렬하는 함수
 */
void gap_insertion(int a[], int n, int gap)
{
    int i, j, key;

    for (i = gap; i < n; i++) {
        key = a[i];
        j = i - gap;

        while (j >= 0) {
            count++;               
            if (a[j] > key) {
                a[j + gap] = a[j];
                j = j - gap;
            } else {
                break;
            }
        }
        a[j + gap] = key;
    }
}

/* 쉘 정렬*/
void shell_sort_original(int a[], int n)
{
    int gap;

    for (gap = n / 2; gap >= 1; gap = gap / 2)
        gap_insertion(a, n, gap);
}

/* 쉘 정렬 - Knuth 간격 */
void shell_sort_knuth(int a[], int n)
{
    int h = 1;
  
    while (h * 3 + 1 < n)
        h = h * 3 + 1;

    while (h >= 1) {
        gap_insertion(a, n, h);
        h = (h - 1) / 3;
    }
}

int main(void)
{
    int sizes[SIZE_COUNT] = {1000, 2000, 4000, 8000, 16000, 20000};
    static int original[MAX_N];
    static int work[MAX_N];
    int s, i, n;
    long long c_ins, c_orig, c_knuth;
    int ok_ins, ok_orig, ok_knuth;

    srand(SEED);

    for (s = 0; s < SIZE_COUNT; s++) {
        n = sizes[s];

   
        for (i = 0; i < n; i++)
            original[i] = make_random();

        /* 삽입 정렬 */
        copy_array(original, work, n);
        count = 0;
        insertion_sort(work, n);
        c_ins = count;
        ok_ins = is_sorted(work, n);

        /* 쉘 정렬 (기본 간격) */
        copy_array(original, work, n);
        count = 0;
        shell_sort_original(work, n);
        c_orig = count;
        ok_orig = is_sorted(work, n);

        /* 쉘 정렬 (Knuth 간격) */
        copy_array(original, work, n);
        count = 0;
        shell_sort_knuth(work, n);
        c_knuth = count;
        ok_knuth = is_sorted(work, n);

        printf("Data Size : %d\n\n", n);
        printf("Insertion Sort       : %lld comparisons\n", c_ins);
        printf("Shell Sort (Original): %lld comparisons\n", c_orig);
        printf("Shell Sort (Knuth)   : %lld comparisons\n", c_knuth);
        printf("Sorted Check         : %s / %s / %s\n\n",
               ok_ins ? "OK" : "FAIL",
               ok_orig ? "OK" : "FAIL",
               ok_knuth ? "OK" : "FAIL");
    }

    return 0;
}

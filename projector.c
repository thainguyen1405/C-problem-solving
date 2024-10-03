//Programming Assignment 6
//Thai Nguyen
//th313791
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

typedef struct {
    double angle;
    int people;
} Group;

//Function prototypes
void mergeSort(Group *arr, int l, int r);
void merge(Group *arr, int l, int m, int r);

int main() {
    int N, A;   // 1 <= N <= 500,000 & 1 <= A <= 359
    scanf("%d %d", &N, &A);
	
	//Allocate Memory
    Group *groups = (Group *)malloc(2 * N * sizeof(Group));
    if (groups == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        int x, y, s;  // 0 <= |x|, |y| <= 1,000,000; 1 <= s <= 1,000;
        scanf("%d %d %d", &x, &y, &s);

		//Find the angle degrees
        double angle = atan2(y, x) * 180 / M_PI;
        if (angle < 0) angle += 360; // Make sure that 0 <= angle < 360

        //Manage angle wrap-around, duplicate each group entry.
        groups[i].angle = angle;
        groups[i].people = s;
        groups[i + N].angle = angle + 360;
        groups[i + N].people = s;
    }

    //Sort the groups by angles
    mergeSort(groups, 0, 2 * N - 1);

    int minN = INT_MAX;
    int left = 0, right = 0;
    int count = 0;

    while (right < 2 * N) {
        if (groups[right].angle - groups[left].angle <= A) {
            count += groups[right].people;
            right++;
        } else {
            count -= groups[left].people;
            left++;
        }

        if (count < minN) {
            minN = count;
        }
    }
	
	//Find the MAX angle for projection
    double maxA = 0;
    for (int i = 1; i < 2 * N; i++) {
        double space = groups[i].angle - groups[i - 1].angle;
        if (space > maxA) {
            maxA = space;
        }
    }
	
	//Print result & free the struct
    printf("%d\n%.4lf\n", minN, maxA);
    free(groups);
    return 0;
}

//Using Merge Sort
void mergeSort(Group *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge(Group *arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    Group *L = malloc(n1 * sizeof(Group));
    Group *R = malloc(n2 * sizeof(Group));
    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = arr[m + 1 + i];
    }
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].angle <= R[j].angle) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }
    free(L);
    free(R);
}

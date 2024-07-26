#include "the1.h"

void swapFunc(unsigned short &a, unsigned short &b){
    unsigned short temp = a;
    a = b;
    b = temp;
}

int chooseMedianPivot(unsigned short* arr, int low, int high, long &swap, double &avg_dist, double &max_dist) {
    int mid = (high + low) / 2;
    unsigned short a = arr[low], b = arr[mid], c = arr[high];
    int medianIndex;
    
    if ((a >= b && a <= c) || (a >= c && a <= b)) {
        medianIndex = low;
    } else if ((b >= a && b <= c) || (b >= c && b <= a)) {
        medianIndex = mid;
    } else {
        medianIndex = high;
    }
    
    return medianIndex;
}

int partitionHoare(unsigned short* arr, int low, int high, long &swap, double &avg_dist, double &max_dist, bool mod_of_3) {
    if(mod_of_3 && high - low >= 2){
        int medianIndex = chooseMedianPivot(arr, low, high, swap, avg_dist, max_dist);
        if (medianIndex != (low + high) / 2 && arr[medianIndex] != arr[(low + high) / 2]) {
            swapFunc(arr[medianIndex], arr[(low + high) / 2]);
            swap++;
            int dist = medianIndex - (low + high) / 2;
            if(dist < 0){
                dist *= -1;
            }
            avg_dist += dist;
            if (dist > max_dist) {
                max_dist = dist;
            }
        }
    }
    unsigned short pivot = arr[(low + high) / 2];
    int i = low - 1;
    int j = high + 1;
    while (true) {
        do {
            i++;
        } while (arr[i] > pivot); // descending order
        do {
            j--;
        } while (arr[j] < pivot); // descending order
        if (i >= j) {
            return j;
        }
        swapFunc(arr[i], arr[j]);
        swap++;
        int dist = i - j;
        if(dist < 0){
            dist *= -1;
        }
        avg_dist += dist;
        if (dist > max_dist) {
            max_dist = dist;
        }
    }
}

int partitionLomuto(unsigned short* arr, int low, int high, long &swap, double &avg_dist, double &max_dist, bool mod_of_3) {
    if(mod_of_3 && high - low >= 2){
        int medianIndex = chooseMedianPivot(arr, low, high, swap, avg_dist, max_dist);
        if (medianIndex != high && arr[medianIndex] != arr[high]) {
            swapFunc(arr[medianIndex], arr[high]);
            swap++;
            int dist = medianIndex - high;
            if(dist < 0){
                dist *= -1;
            }
            avg_dist += dist;
            if (dist > max_dist) {
                max_dist = dist;
            }
        }
    }
    unsigned short pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] >= pivot) {
            i++;
            swapFunc(arr[i], arr[j]);
            swap++;
            int dist = i - j;
            if(dist < 0){
                dist *= -1;
            }
            avg_dist += dist;
            if (dist > max_dist) {
                max_dist = dist;
            }
        }
    }
    swapFunc(arr[i + 1], arr[high]);
    swap++;
    int dist = (i + 1) - high;
    if(dist < 0){
        dist *= -1;
    }
    avg_dist += dist;
    if (dist > max_dist) {
        max_dist = dist;
    }
    return i + 1;
}

void quickSortRec(unsigned short* arr, int low, int high, long &swap, double &avg_dist, double &max_dist, bool hoare, int &numRecursiveCalls, bool mod_of_3) {
    numRecursiveCalls++;
    if (low < high) {
        int partitionIndex;
        if (hoare) {
            partitionIndex = partitionHoare(arr, low, high, swap, avg_dist, max_dist, mod_of_3);
            quickSortRec(arr, low, partitionIndex, swap, avg_dist, max_dist, hoare, numRecursiveCalls, mod_of_3);
            quickSortRec(arr, partitionIndex + 1, high, swap, avg_dist, max_dist, hoare, numRecursiveCalls, mod_of_3);
        } else {
            partitionIndex = partitionLomuto(arr, low, high, swap, avg_dist, max_dist, mod_of_3);
            quickSortRec(arr, low, partitionIndex - 1, swap, avg_dist, max_dist, hoare, numRecursiveCalls, mod_of_3);
            quickSortRec(arr, partitionIndex + 1, high, swap, avg_dist, max_dist, hoare, numRecursiveCalls, mod_of_3);
        }
    }
}

int quickSort(unsigned short* arr, long &swap, double &avg_dist, double &max_dist, bool hoare, bool median_of_3, int size) {
    swap = 0;
    avg_dist = 0;
    max_dist = 0;
    int numRecursiveCalls = 0;

    quickSortRec(arr, 0, size - 1, swap, avg_dist, max_dist, hoare, numRecursiveCalls, median_of_3);

    if (swap > 0) {
        avg_dist /= swap; // calculate average distance
    }

    return numRecursiveCalls;
}
#include "the2.h"

// do not add extra libraries here
/*
    arr       : array to be sorted, in order to get points this array should contain be in sorted state before returning
    ascending : true for ascending, false for descending 
    size      : number of elements in the array
*/

int counting_sort(std::string *arr, int size, int index, bool ascending){
    int count_array[27] = {0};
    int total_iterations = 0;
    std::string output_array[size];
    int char_index = 0;
    
    for(int i = 0; i < size; i++){
        if(index < arr[i].size()){
            char_index = arr[i][index] - 'A' + 1;
        }
        else{
            char_index = 0;
        }
        count_array[char_index]++;
        total_iterations++;
    }
    
    if(ascending){
        for(int i = 1; i < 27; i++){
            count_array[i] += count_array[i - 1];
            total_iterations++;
        }
    }
    else{
        for(int i = 25; i >= 0; i--){
            count_array[i] += count_array[i + 1];
            total_iterations++;
        }
    }
    
    for(int i = size - 1; i >= 0; i--){
        if(index < arr[i].size()){
            char_index = arr[i][index] - 'A' + 1;
        }
        else{
            char_index = 0;
        }
        output_array[count_array[char_index] - 1] = arr[i];
        count_array[char_index]--;
        total_iterations++;
    }
    
    for(int i = 0; i < size; i++){
        arr[i] = output_array[i];
        total_iterations++;
    }
    return total_iterations;
}

int radix_string_sort(std::string *arr, int size, bool ascending) {
    int max_length = 0;
    for (int i = 0; i < size; i++) {
        max_length = std::max(max_length, (int)arr[i].size());
    }

    int total_iterations = 0;
    for (int index = max_length - 1; index >= 0; index--) {
        total_iterations += counting_sort(arr, size, index, ascending);
    }


    return total_iterations;
}
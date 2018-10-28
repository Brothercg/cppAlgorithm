#include <iostream>
#include "SortTestHelper.h"
#include "Student.h"

using namespace std;

template <typename T>
void  selectionSort(T arr[], int n) {

    for(int i = 0; i < n; i ++){

        int minIndex = i;
        for(int j = i + 1; j < n; j++)
            if(arr[j] < arr[minIndex])
                minIndex = j;

        swap(arr[i], arr[minIndex]);
    }
}

template <typename T>
void insertionSort(T arr[], int n) {
    for(int i = 1; i < n; i++){

        //find the correct location to insert the arr[i]
        for(int j = i; j > 0 ; j--){
            if(arr[j] < arr[j-1])
                //这样的插入排序在佳交换的时候十分耗时。
                swap(arr[j], arr[j - 1]);
            else
                break;
        }
    }
}

/**
 * core idea: abandon use "swap"，use a Temporary variables to store the  insert value
 * */
template <typename T>
void insertionSortImprove(T arr[], int n) {
    for(int i = 1; i < n; i++){
        T temp = arr[i];
        for(int j = i; j > 0; j--){
            if(arr[j-1] > temp)
                arr[j] = arr[j-1];
            else{
                arr[j-1] = temp;
                break;
            }
        }
    }
}

/**
 * Bubble Sort
 */

/**
 * Shell sort
 */


int main() {


    int n = 10000;
    int *arr = SortTestHelper::generateNearlyOrderedArray(n,100);
    int *arr2 = SortTestHelper::copyIntArray(arr,n);
    int *arr3 = SortTestHelper::copyIntArray(arr,n);

    //The test of selection Sort
    SortTestHelper::testSort("Selection Sort", selectionSort, arr, n);
    SortTestHelper::testSort("Insertion Sort", insertionSort, arr2, n);
    SortTestHelper::testSort("insertionImprove Sort", insertionSortImprove, arr3, n);


    // The custom structure test in selectionSort.
//    Student stu[4] = { {"D",90} , {"C",100} , {"B",95} , {"A", 95} };
//    selectionSort(stu, 4);
//    for(int i = 0; i < 4; i++)
//        cout << stu[i];



    delete[](arr);
    delete[](arr2);
    return 0;
}
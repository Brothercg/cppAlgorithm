#include <iostream>
#include "SortTestHelper.h"
#include "Student.h"


//所有排序按照从小到大排序。

using namespace std;

/**
 * 选择排序
 * */

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

/**
 * 插入排序
 * */
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

template <typename T>
void bubbleSort(T arr[], int n) {
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
        }
    }
}

/**
 * Shell sort: 按照步长进行插入排序。
 */

template <typename T>
void shellSort(T arr[], int n) {
    int step = (n-1)/2;

    while (step > 0){

//        cout << "Step: "  << step  << endl;
        for(int i = step ; i < n  ; i ++){
            for(int j = i; j >= step; j -= step){
                if(arr[j] < arr[j - step]){
//                    cout << "swap " << j << "---" << j - step << endl;
                    swap(arr[j], arr[j - step]);
                }
                else
                    break;
            }

        }

        step = step / 2;
    }
}

/**
 * 归并排序
 * */

template <typename T>
void __merge(T arr[], int l, int mid, int r) {

    //copy the arr to aux
    T aux[r - l + 1];
    for(int i = l; i <= r; i++)
        aux[i - l] = arr[i];

    int i = l, j = mid + 1;
    for(int k = i; k <= r; k++) {

        if( i > mid){
            arr[k] = aux[j - l];
            j++;
        }

        else if( j > r ){
            arr[k] = aux[i - l];
            i++;
        }

        else if( aux[i - l] <  aux[j - l]) {
            arr[k] = aux[i - l];
            i++;
        }else{
            arr[k] = aux[j - l];
            j++;
        }
    }
}

//递归使用归并排序，对arr[l...r]的范围使用归并排序。r是最后一个元素的位置，不是最后元素的位置。
template <typename T>
void __mergeSort(T arr[], int l, int r){

    //处理递归到低的情况
    if(l >= r)
        return;

    int mid = (l+r)/2;
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid + 1, r);
    __merge(arr, l, mid, r);
}

template <typename T>
void  mergeSort(T arr[], int n){
    __mergeSort(arr, 0, n-1);
}

int main() {


    int n = 50000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, 100000);
    int *arr2 = SortTestHelper::copyIntArray(arr,n);
    int *arr3 = SortTestHelper::copyIntArray(arr,n);
    int *arr4 = SortTestHelper::copyIntArray(arr,n);
    int *arr5 = SortTestHelper::copyIntArray(arr,n);
    int *arr6 = SortTestHelper::copyIntArray(arr,n);


//    SortTestHelper::printArray(arr,n);

    //The test of selection Sort
    SortTestHelper::testSort("Selection Sort", selectionSort, arr, n);
    SortTestHelper::testSort("Insertion Sort", insertionSort, arr2, n);
    SortTestHelper::testSort("insertionImprove Sort", insertionSortImprove, arr3, n);
    SortTestHelper::testSort("Bubble Sort: ", bubbleSort, arr4, n);
    SortTestHelper::testSort("Shell Sort: ", shellSort, arr5, n);
    SortTestHelper::testSort("Merge Sort: ", mergeSort, arr6, n);


    // The custom structure test in selectionSort.
//    Student stu[4] = { {"D",90} , {"C",100} , {"B",95} , {"A", 95} };
//    selectionSort(stu, 4);
//    for(int i = 0; i < 4; i++)
//        cout << stu[i];


    delete[](arr);
    delete[](arr2);
    delete[](arr3);
    delete[](arr4);
    delete[](arr5);
    delete[](arr6);

    return 0;
}
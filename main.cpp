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
 * insert Sort  对于有序的数组将降到O(n)的级别。
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


template <typename T>
void insertionSort(T arr[], int l, int r) {
    for(int i = l + 1; i < r; i++){
        T e = arr[i];
        //find the correct location to insert the arr[i]
        int j;
        for(j = i; j > l && arr[j - i] > e; j--)
            arr[j] = arr[j - 1];
        arr[j] = e;
    }
    return;
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

        //左侧已经遍历完了，把右侧接上去
        if( i > mid){
            arr[k] = aux[j - l];
            j++;
        }

        //右侧已经遍历完了，把左侧接上去
        else if( j > r ){
            arr[k] = aux[i - l];
            i++;
        }

        //左右两侧都没有遍历完成
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

    //首先处理递归到低的情况
    if(l >= r)
        return;

    //l和r都非常大的时候很可能产生溢出错误
    int mid = (l+r)/2;
    //对arr l到mid 进行归并排序。
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid + 1, r);
    __merge(arr, l, mid, r);
}

template <typename T>
void  mergeSort(T arr[], int n){
    __mergeSort(arr, 0, n-1);
}

/**
 * 归并排序提高之二,只有当左右两段都还是处于无序的状态的时候才继续进行递归排序。
 * */

template <typename T>
void __improveMergeSort_1(T arr[], int l, int r){

    //首先处理递归到低的情况
    if(l >= r)
        return;

    //l和r都非常大的时候很可能产生溢出错误
    int mid = (l+r)/2;
    //对arr l到mid 进行归并排序。
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid + 1, r);

    //提升点！！！！！！
    if( arr[mid] > arr[mid + 1])
        __merge(arr, l, mid, r);
}

template <typename T>
void improveMergeSort_1(T arr[], int n){
    __improveMergeSort_1(arr, 0, n-1);
}

/**
 * 归并排序提高之二,在归并排序提高一的基础上提出一点，当需要归并的段落很短的时候，
 * 使用插入排序。以提高效率。
 * */

template <typename T>
void __improveMergeSort_2(T arr[], int l, int r){

    //首先处理递归到低的情况
//    if(l >= r)
//        return;

    //提升点2
    //数组越短的时候有序的概率就越大。
    if(r - l <= 15){
        insertionSort(arr, l, r);
        return;
    }


    //l和r都非常大的时候很可能产生溢出错误
    int mid = (l+r)/2;
    //对arr l到mid 进行归并排序。
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid + 1, r);

    //提升点1
    if( arr[mid] > arr[mid + 1])
        __merge(arr, l, mid, r);
}

template <typename T>
void  improveMergeSort_2(T arr[], int n){
    __improveMergeSort_2(arr, 0, n-1);
}

/**
 * 自底向上的归并排序。
 * 优点：
 *      1、没有使用数组的下标，所以可以用nlog(n)的复杂度来处理类似链表的问题。
 * */
 template <typename T>
 void mergeSortBU(T arr[], int n){
     for(int size = 1; size <= n; size += size )
         //确保i + size不会越界。
         for(int i = 0; i + size < n; i += size + size)
             //对arr[i...i+size-1]和arr[i + size ... i+ 2*size-1]进行归并
             __merge(arr, i, i + size-1, min(i + size + size - 1, n - 1));
 }




int main() {


    int n = 50000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, 100000);
//    int *arr = SortTestHelper::generateNearlyOrderedArray(n, 10);
    int *arr2 = SortTestHelper::copyIntArray(arr,n);
    int *arr3 = SortTestHelper::copyIntArray(arr,n);
    int *arr4 = SortTestHelper::copyIntArray(arr,n);
    int *arr5 = SortTestHelper::copyIntArray(arr,n);
    int *arr6 = SortTestHelper::copyIntArray(arr,n);
    int *arr7 = SortTestHelper::copyIntArray(arr,n);
    int *arr8 = SortTestHelper::copyIntArray(arr,n);
    int *arr9 = SortTestHelper::copyIntArray(arr,n);


//    SortTestHelper::printArray(arr,n);

    //The test of selection Sort
    SortTestHelper::testSort("Selection Sort", selectionSort, arr, n);
    SortTestHelper::testSort("Insertion Sort", insertionSort, arr2, n);
    SortTestHelper::testSort("InsertionImprove Sort", insertionSortImprove, arr3, n);
    SortTestHelper::testSort("Bubble Sort: ", bubbleSort, arr4, n);
    SortTestHelper::testSort("Shell Sort: ", shellSort, arr5, n);
    SortTestHelper::testSort("Merge Sort: ", mergeSort, arr6, n);
    SortTestHelper::testSort("Improved Merge Sort 1: ", improveMergeSort_1, arr7, n);
    SortTestHelper::testSort("Improved Merge Sort 2: ", improveMergeSort_2, arr8, n);
    SortTestHelper::testSort("mergeSortBU: ", mergeSortBU, arr9, n);

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
//
// Created by 陈广 on 2018/10/23.
//

#ifndef CPPALGORITHM_SORTTESTHELPER_H
#define CPPALGORITHM_SORTTESTHELPER_H

#include <iostream>
#include <cassert>

using namespace std;
//生成有n个元素的随机数组，每个元素的范围为[rangeL, rangeR]
namespace SortTestHelper{
    int* generateRandomArray(int n, int rangeL, int rangeR) {

        assert(rangeL <= rangeR);

        int *arr = new int[n];
        srand(time(NULL));
        for(int i = 0; i < n; i++)
            arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
        return arr;
    }

    template <typename T>
    void printArray(T arr[], int n){
        for (int i = 0; i < n; i++)
            cout << arr[i] << ' ';
        cout << endl;

        return;
    }

    template <typename T>
    bool isSortTrue(T arr[], int n){
        for(int i = 0; i < n-1; i++){
            if(arr[i] > arr[i+1])
                return false;
        }
        return true;
    }

    template <typename T>
    void testSort(string sortName, void(*sort)(T[], int n), T arr[], int n){

        clock_t startTime = clock();
        sort(arr,n);
        clock_t endTime = clock();

        assert( isSortTrue(arr, n) );

        cout << sortName << ": " << double(endTime - startTime) / CLOCKS_PER_SEC << "S" << endl;

        return;
    }

    int* copyIntArray(int a[], int n){
        int* arr = new int[n];
        copy(a, a+n, arr);
        return arr;
    }

    int* generateNearlyOrderedArray(int n, int swapTimes) {
        int *arr = new int[n];
        for(int i = 0; i < n; i++)
            arr[i] = i;

        srand(time(NULL));

        for(int i = 0; i < swapTimes; i++){
            int posx = rand()%n;
            int posy = rand()%n;

            swap(arr[posx], arr[posy]);
        }

        return arr;
    }
}

#endif //CPPALGORITHM_SORTTESTHELPER_H


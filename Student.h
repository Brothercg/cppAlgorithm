//
// Created by 陈广 on 2018/10/23.
//

#ifndef CPPALGORITHM_STUDENT_H
#define CPPALGORITHM_STUDENT_H

#include<iostream>
#include <string>

using namespace std;

struct Student{
    string name;
    int score;

    //运算符重载,意思就是重载了Student对象之间关于"<"这个符号的定义，是比较对象之间，关于score的大小。
    bool operator<(const Student &otherStudent){
        return score != otherStudent.score ? score < otherStudent.score : name < otherStudent.name;
    }

    //重载<<输出，友元函数
    friend ostream& operator<<(ostream &os, const Student &student) {
        os<<"Student: " << student.name << " " << student.score << endl;
        return os;
    }
};

#endif //CPPALGORITHM_STUDENT_H

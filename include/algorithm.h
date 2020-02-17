//
// Created by zhouxin on 2019/11/14.
//
#pragma once
#ifndef B_SPLINE_SURFACE_ALGORITHM_H
#define B_SPLINE_SURFACE_ALGORITHM_H
#include <iostream>
#include <vector>

using namespace std;
using namespace Eigen;

//对于给了控制点的情况，直接生成控制向量
void vector_get(vector<double> &U,int p,int n){
    int m = p + n + 1;
    U.resize(m + 1);
    for(int i=0;i<=m;i++){
        if(i <= p){
            U[i] = 0;
        }
        else if(i < n + 1){
            U[i] = i * 1.0 / m;
        }
        else U[i] = 1;
    }

}


//对于给了表面点的情况，控制点的生成方式不同
void new_vector_get(vector<double> &U,int p,int n,const vector<double> &t){
    int m = p + n + 1;
    U.resize(m + 1);
    for(int i=0;i<=m;i++){
        if(i <= p){
            U[i] = 0;
        }
        else if(i < n + 1){
            int sum_p = 0;
            for(int j=i-p;j<i;j++){
                sum_p = sum_p + t[j];
            }
            U[i] = (1.0 / p) * sum_p;
        }
        else U[i] = 1;
    }

}

//基函数，思路简单，模仿De Boor过程
double BaseFunction(const int i,const int p,const double u,const vector<double> U_V){
    double u_value = 0;
    if(p == 0){
        if(u>=U_V[i] && u<U_V[i+1])
            return 1.0;
        else
            return 0;
    }
    else{
        double length_left = U_V[i + p] - U_V[i];
        double length_right = U_V[i + p + 1] - U_V[i + 1];
        if(length_left == 0.0){
            length_left = 1;
        }
        if(length_right == 0.0){
            length_right = 1;
        }
        u_value = ((u - U_V[i]) / length_left) * BaseFunction(i,p-1,u,U_V) +
                  ((U_V[i + p + 1] - u) / length_right) * BaseFunction(i+1,p-1,u,U_V);
        return u_value;
    }
}


//针对interpolation的要求，进行向量生成
void parameter_get(vector<double> &u,vector<Vector3d> D){
    int max_posi = D.size() - 1;
    double L = 0;
    vector<double> LL;
    for(int i=0;i<max_posi;i++){
        Vector3d tmp = D[i + 1] - D[i];
        LL.push_back(L);
        L = L + sqrt(tmp[0] * tmp[0] + tmp[1] * tmp[1] + tmp[2] * tmp[2]);
    }
    for(int i=0;i<max_posi;i++){
        u[i] = LL[i] / L;
    }
    u[0] = 0.1;
    u[max_posi] = 0.9;
}


#endif //B_SPLINE_SURFACE_ALGORITHM_H

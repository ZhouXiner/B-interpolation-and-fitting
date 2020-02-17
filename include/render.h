//
// Created by zhouxin on 2019/11/14.
//
#pragma once
#ifndef B_SPLINE_SURFACE_RENDER_H
#define B_SPLINE_SURFACE_RENDER_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <GL/glut.h>
#include <string>
#include <memory>
#include <Eigen/Cholesky>
#include <Eigen/LU>
#include <Eigen/QR>
#include <Eigen/SVD>
#include "../include/dataset.h"



typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatXX;
int M_,N_,P_,Q_,U_,V_,choice_;
vector<vector<Vec3d>> pts_; //控制点
vector<vector<Vec3d>> surface_pts_;  //表面点

int num_surface_points_ = 100;
vector<double> U_vector_;
vector<double> V_vector_;

//3代表了x,y,z三个方向的坐标，每一层的mat确定一个平面
//这些构造的目的时为了求解时方便矩阵运算
vector<MatXX> Data_Points(3);  //数据点
vector<MatXX> Points(3);
vector<MatXX> Tmp_Points(3);
vector<MatXX> Base_value(2);  //基函数

GLfloat angle_ =10.0f;
GLfloat xDirection_ = 0.0f;
GLfloat yDirection_ = 0.0f;
GLfloat zDirection_ = 10.0f;
double view_size = 40;
int height_ = 1000;
int width_ = 1000;
int show_surface_ = 1,show_point_ = 1,show_this_way_ = 1;

void init();
void get_data(Dataset::Ptr dataset);
void display();
void KeyBoards(unsigned char key,int x,int y);
void interpolation(); //对于给了平面点的情况，需要先求出控制点

#endif //B_SPLINE_SURFACE_RENDER_H

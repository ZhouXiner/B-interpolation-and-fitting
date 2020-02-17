//
// Created by zhouxin on 2019/11/14.
//
#pragma once
#ifndef B_SPLINE_SURFACE_DATASET_H
#define B_SPLINE_SURFACE_DATASET_H
#include <iostream>
#include <vector>
#include <string>
#include <experimental/filesystem>
#include <unistd.h>
#include <memory>
#include <opencv2/opencv.hpp>
#include <Eigen/Core>
#include <vector>
#include<unistd.h>


using namespace std;
using namespace cv;
using namespace Eigen;

class Dataset{
public:
    typedef std::shared_ptr<Dataset> Ptr;
    typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatXX;

    int M_,N_,P_,Q_,U_,V_,choice;

    cv::Mat info_; //因为只能读成一行，所以只好一个个读取，对于(i,j,k)，就是(0,3*i*(M+1) + 3*j + 0),(0,3*i*(M+1) + 3*j + 1),(0,3*i*(M+1) + 3*j + 2)
    vector<vector<Vec3d>> pts_;
    string data_path_;
    string points_path_;


    vector<MatXX> Data_Points;
    Dataset();
    void points_get();   //获取已知的控制点
    void true_points_get(); //获取表面上的点
    void fitting();  //交互界面
};

#endif //B_SPLINE_SURFACE_DATASET_H

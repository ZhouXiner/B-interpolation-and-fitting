//
// Created by zhouxin on 2019/11/14.
//

#include "../include/dataset.h"

namespace fs = std::experimental::filesystem;


Dataset::Dataset() {
    data_path_ = "./points_info/";
    points_path_ = "./points_surface/";
};

void Dataset::points_get() {
    int cnt = 0;
    vector<string> paths;
    for(auto &files: fs::directory_iterator(data_path_)) {
        auto &files_path = files.path();
        auto files_type = files_path.extension().string();
        if (files_type == ".yaml") {
            std::cout << ++cnt << "  " << files_path.string() << std::endl;
            paths.push_back(files_path.string());
        }
    }
    while(1)
    {
        std::cout << "Press the number between 1 to " << cnt << " and ENTER to show the surface!" << std::endl;
        std::cout << "Press the number 0 to exit!" << std::endl;
        int choice;
        std::cin >> choice;
        if(choice > cnt || choice < 0){
            std::cout << "invaid choice!" << std::endl;
            continue;
        }
        else if(choice == 0){
            std::exit(014);
        }
        else{
            string used_path = paths[choice - 1];
            cv::FileStorage file_(used_path, cv::FileStorage::READ);
            file_["pts"] >> info_;
            file_["M"] >> M_;
            file_["N"] >> N_;
            file_["P"] >> P_;
            file_["Q"] >> Q_;
            U_ = P_ + M_ + 1;
            V_ = Q_ + N_ + 1;

            pts_.resize(M_+1);

            for(int i=0;i<M_+1;i++){
                for(int j=0;j<N_+1;j++){
                    Vec3d p(info_.at<double>(0,3*i*(M_+1) + 3*j + 0),info_.at<double>(0,3*i*(M_+1) + 3*j + 1),info_.at<double>(0,3*i*(M_+1) + 3*j + 2));
                    pts_[i].push_back(p);
                }
            }

            cout << "The points size is: " << M_ + 1<< "x" << N_ + 1<< "x" << 3 << endl;
            cout << "The U vector size: " << U_ + 1 << endl;
            cout << "The V vector size: " << V_ + 1 << endl;
            return;
        }
    }

}

void Dataset::true_points_get() {
    int cnt = 0;
    vector<string> paths;
    for(auto &files: fs::directory_iterator(points_path_)) {
        auto &files_path = files.path();
        auto files_type = files_path.extension().string();
        if (files_type == ".yaml") {
            std::cout << ++cnt << "  " << files_path.string() << std::endl;
            paths.push_back(files_path.string());
        }
    }
    while(1)
    {
        std::cout << "Press the number between 1 to " << cnt << " and ENTER to show the surface!" << std::endl;
        std::cout << "Press the number 0 to exit!" << std::endl;
        int choice;
        std::cin >> choice;
        if(choice > cnt || choice < 0){
            std::cout << "invaid choice!" << std::endl;
            continue;
        }
        else if(choice == 0){
            std::exit(014);
        }
        else{
            string used_path = paths[choice - 1];
            cv::FileStorage file_(used_path, cv::FileStorage::READ);
            file_["pts"] >> info_;
            file_["M"] >> M_;
            file_["N"] >> N_;
            file_["P"] >> P_;
            file_["Q"] >> Q_;
            U_ = P_ + M_ + 1;
            V_ = Q_ + N_ + 1;


            Data_Points.resize(3);
            for(int i=0;i<3;i++){
                Data_Points[i].resize(M_ + 1,N_ + 1);
            }

            for(int i = 0;i<M_ + 1;i++){
                for(int j=0;j<N_+1;j++){
                    Data_Points[0](i,j) = info_.at<double>(0,3*i*(M_+1) + 3*j + 0);
                    Data_Points[1](i,j) = info_.at<double>(0,3*i*(M_+1) + 3*j + 1);
                    Data_Points[2](i,j) = info_.at<double>(0,3*i*(M_+1) + 3*j + 2);
                }
            }

            cout << "The points size is: " << M_ + 1<< "x" << N_ + 1<< "x" << 3 << endl;
            cout << "The U vector size: " << U_ + 1 << endl;
            cout << "The V vector size: " << V_ + 1 << endl;
            return;
        }
    }
}

void Dataset::fitting(){
    while(1)
    {
        std::cout << "Fitting using points_in_surface(0) or control_points(1) " << endl;
        std::cout << "Input 0 or 1" << endl;
        std::cin >> choice;
        if(choice != 0 && choice != 1){
            std::cout << "wrong input!" << endl;
            continue;
        }
        else if(choice == 1){
            points_get();
        }
        else{
            true_points_get();
        }
        return;
    }

}
//
// Created by zhouxin on 2019/11/14.
//
#include "../include/render.h"
#include <cstdlib>
#include "../include/algorithm.h"

void get_data(Dataset::Ptr dataset){
    M_ = dataset->M_;
    N_ = dataset->N_;
    P_ = dataset->P_;
    Q_ = dataset->Q_;
    U_ = dataset->U_;
    V_ = dataset->V_;
    pts_ = dataset->pts_;
    choice_ = dataset->choice;

    vector_get(U_vector_, P_, M_);
    vector_get(V_vector_, Q_, N_);

    if(choice_ == 0){
        for(int i=0;i<3;i++){
            Data_Points[i].resize(M_ + 1,N_ + 1);
            Points[i].resize(M_ + 1,N_+1);
            Points[i].resize(M_ + 1,N_+1);
        }
        Base_value[0].resize(M_+1,M_+1);
        Base_value[1].resize(N_+1,N_+1);

        cout << "ok" << endl;
        for(int i=0;i<3;i++){
            Data_Points[i] = dataset->Data_Points[i];
        }

        interpolation();
    }
    //for b_spline

    //change position
    Vec3d center_v(0, 0, 0);

    int cnt = 0;

    for (int i = 0; i < M_ + 1; i++) {
        for (int j = 0; j < N_ + 1; j++) {
            center_v = center_v + pts_[i][j];
            cnt++;
        }
    }
    center_v = center_v / cnt;

    for (int i = 0; i < M_ + 1; i++) {
        for (int j = 0; j < N_ + 1; j++) {
            pts_[i][j] = pts_[i][j] - center_v;
            view_size = max(view_size,double(max(pts_[i][j][0],double(max(pts_[i][j][1],pts_[i][i][2])))));
        }
    }
    view_size = int(view_size * 1.5);
}

void init() {
    //for glut show
    glClearColor(1.0, 1.0, 1.0, 1.0); //利用预设的值清空缓冲区,就是北京颜色

    glOrtho(-view_size, view_size, -view_size, view_size, -view_size, view_size);//设置一个框框的大小，来装入物体
    gluLookAt(xDirection_, yDirection_, zDirection_, 0, 0, 0, 0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glPushMatrix();

    //绘制背景控制点和控制点连线
    if(show_point_ && choice_){

        glColor3f(1.0, 0.0, 0.0);
        glPointSize(10.0f);
        glBegin(GL_POINTS);
        for (int i = 0; i < M_ + 1; i++){
            for (int j = 0; j < N_ + 1; j++){
                glVertex3d(pts_[i][j][0],pts_[i][j][1],pts_[i][j][2]);
            }
        }
        glEnd();

        for (int i = 0; i < M_ + 1; i++){
            glBegin(GL_LINE_STRIP);
            for (int j = 0; j < N_ + 1; j++){
                glVertex3d(pts_[i][j][0],pts_[i][j][1],pts_[i][j][2]);
            }
            glEnd();
        }
        glColor3f(0.0, 1.0, 0.0);
        for (int i = 0; i < N_ + 1; i++){
            glBegin(GL_LINE_STRIP);
            for (int j = 0; j < M_ + 1; j++){
                glVertex3d(pts_[j][i][0],pts_[j][i][1],pts_[j][i][2]);
            }
            glEnd();
        }
    }

    if(show_point_ && !choice_){

        glColor3f(1.0, 0.0, 0.0);
        glPointSize(10.0f);
        glBegin(GL_POINTS);
        for (int i = 0; i < M_ + 1; i++){
            for (int j = 0; j < N_ + 1; j++){
                glVertex3d(surface_pts_[i][j][0],surface_pts_[i][j][1],surface_pts_[i][j][2]);
            }
        }
        glEnd();

        for (int i = 0; i < M_ + 1; i++){
            glBegin(GL_LINE_STRIP);
            for (int j = 0; j < N_ + 1; j++){
                glVertex3d(surface_pts_[i][j][0],surface_pts_[i][j][1],surface_pts_[i][j][2]);
            }
            glEnd();
        }
        glColor3f(0.0, 1.0, 0.0);
        for (int i = 0; i < N_ + 1; i++){
            glBegin(GL_LINE_STRIP);
            for (int j = 0; j < M_ + 1; j++){
                glVertex3d(surface_pts_[j][i][0],surface_pts_[j][i][1],surface_pts_[j][i][2]);
            }
            glEnd();
        }
    }

    if(show_surface_){

        glColor3f(0.0, 0.0, 1.0);
        //glPointSize(10.0f);
        //glBegin(GL_POINTS);

        //在u和v两个方向上进行遍历，表面的疏密程度由你的迭代决定
        for(double u=0;u<=1; u = u + 1.0 / num_surface_points_){
            glBegin(GL_LINE_STRIP);
            for(double v=0;v<=1; v = v + 1.0 / num_surface_points_){
                Vec3d p(0,0,0);
                for(int x=0;x<M_+1;x++){
                    double size_u = BaseFunction(x,P_,u,U_vector_);

                    for(int y=0;y<N_+1;y++){
                        double size_v = BaseFunction(y,Q_,v,V_vector_);
                        p = p + size_u * size_v * pts_[x][y];
                    }
                }
                glVertex3d(p[0],p[1],p[2]);
            }
            glEnd();
        }
    }
    glutSwapBuffers();
    glPopMatrix();
}

void KeyBoards(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            glMatrixMode(GL_MODELVIEW);
            glRotatef(angle_, -1, 0, 0);
            glutPostRedisplay();
            break;
        case 'a':
            glMatrixMode(GL_MODELVIEW);
            glRotatef(angle_, 0, 0, 1);
            glutPostRedisplay();
            break;
        case 's':
            glMatrixMode(GL_MODELVIEW);
            glRotatef(angle_, 1, 0, 0);
            glutPostRedisplay();
            break;
        case 'd':
            glMatrixMode(GL_MODELVIEW);
            glRotatef(angle_, 0, 0, -1);
            glutPostRedisplay();
            break;
        case 'q':
            glMatrixMode(GL_MODELVIEW);
            glRotatef(angle_, 0, -1, 0);
            glutPostRedisplay();
            break;
        case 'e':
            glMatrixMode(GL_MODELVIEW);
            glRotatef(angle_, 0, 1, 0);
            glutPostRedisplay();
            break;
        case 'c':
            if (show_surface_ == 0) {
                show_surface_ = 1;
            } else {
                show_surface_ = 0;
            }
            glutPostRedisplay();
            break;
        case 'v':
            if (show_point_ == 0) {
                show_point_ = 1;
            } else {
                show_point_ = 0;
            }
            glutPostRedisplay();
            break;
        case 'b':
            if (show_this_way_ == 0) {
                show_this_way_ = 1;
            } else {
                show_this_way_ = 0;
            }
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
    }
}

/**
 * 对于给了surface点的情况，先求出控制点，再利用控制点拟合表面
 */
void interpolation()
{

    vector<double> s(M_ + 1),t(N_ + 1);

    //将型值点数据参数化，求出需要带入基函数求解的s和t
    vector<vector<double>> uu(N_ + 1);

    for(int j=0;j<=N_;j++){
        vector<Vector3d> D;
        vector<double> tmP_(M_ + 1);
        for(int i=0;i<=M_;i++){
            Vector3d d(Data_Points[0](i,j),Data_Points[1](i,j),Data_Points[2](i,j));
            D.push_back(d);
        }
        parameter_get(tmP_,D);
        uu[j].swap(tmP_);
    }


    for(int i=0;i<=M_;i++){
        double uu_value = 0;
        for(int j=0;j<=N_;j++){
            uu_value += uu[j][i];
        }
        s[i] = uu_value / (N_ + 1);
    }

    vector<vector<double>> vv(M_ + 1);
    for(int i=0;i<=M_;i++){
        vector<Vector3d> D;
        vector<double> tmQ_(N_ + 1);
        for(int j=0;j<=N_;j++){
            Vector3d d(Data_Points[0](i,j),Data_Points[1](i,j),Data_Points[2](i,j));
            D.push_back(d);
        }
        parameter_get(tmQ_,D);
        vv[i].swap(tmQ_);
    }

    for(int j=0;j<=N_;j++){
        double vv_value = 0;
        for(int i=0;i<=M_;i++){
            vv_value += vv[i][j];
        }
        t[j] = vv_value / (M_ + 1);
    }


    //生成U和V的控制向量
    new_vector_get(U_vector_, P_, M_,s);
    new_vector_get(V_vector_, Q_, N_,t);

    for(int i=0;i<=M_;i++){
        for(int j=0;j<=M_;j++){
            Base_value[0](i,j) = BaseFunction(j,P_,s[i],U_vector_);
        }
    }


    for(int i=0;i<=N_;i++){
        for(int j=0;j<=N_;j++){
            Base_value[1](i,j) = BaseFunction(j,Q_,t[i],V_vector_);
        }
    }

    //直接利用QR方法求解出控制点
    for(int i=0;i<3;i++){
        Tmp_Points[i] = Base_value[0].colPivHouseholderQr().solve(Data_Points[i]);
        MatXX ppp;
        ppp = Base_value[1].colPivHouseholderQr().solve(Tmp_Points[i].transpose());
        Points[i] = ppp.transpose();

    }

    pts_.clear();
    pts_.resize(M_+1);
    surface_pts_.resize(M_+1);


    //得到控制点和表面点信息
    for(int i=0;i<M_+1;i++){
        for(int j=0;j<N_+1;j++){
            Vec3d p(Points[0](i,j),Points[1](i,j),Points[2](i,j));
            Vec3d surface_p(Data_Points[0](i,j),Data_Points[1](i,j),Data_Points[2](i,j));
            pts_[i].push_back(p);
            surface_pts_[i].push_back(surface_p);
            cout << surface_p << endl;
        }
    }
}

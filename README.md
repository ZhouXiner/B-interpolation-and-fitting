# B-interpolation-and-fit-
必备包
==
Eigen,Opencv,OpenGL,GLUT  
    
      
编译与运行
==
编译：进入项目目录，执行以下操作：  
    
  ```
mkdir build  
cd build  
cmake ..  
make
  ```  
  运行：执行以下操作  
  ```
  cd ..
  ./build/B_Spline_surface  
  ```
基础说明  
==
事实上，B样条的拟合较为简单，列出几个关键词，自行搜索即可，笔者列举几个自己觉得有用的  
B样条的完整知识：https://blog.csdn.net/tuqu/article/details/4749586  
B样条基本知识：https://blog.csdn.net/qq_40597317/article/details/81155571  
BaseFuction可以参考我的algorithm.h，我的参考网页找不到了，抱歉  
我假设大家已经知道B样条的基本知识，插值部分才是我上传代码的原因，因为网上找不太到相关的靠谱知识，方便大家多做参考  

插值部分
==  
拟合流程：生成基函数，再基于已知控制点，生成surface  
但是对于插值流程，必须先基于表面点得到控制点，再基于控制点求出surface  

基于表面点求出控制点  
=  
![image](https://github.com/ZhouXiner/B-interpolation-and-fit-/blob/master/PIC/Screenshot%20from%202020-02-17%2013-51-34.png)  其实就是处理这个式子(书中 Surface Global Interpolation部分)，基于这个公式，反解出控制点P  
我们知道的只有数据点D，首先需要得到基函数N和遍历的点s,t





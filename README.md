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
![image](https://github.com/ZhouXiner/B-interpolation-and-fit-/blob/master/PIC/Screenshot%20from%202020-02-17%2013-51-34.png)  
其实就是处理这个式子(书中 Surface Global Interpolation部分)，基于这个公式，反解出控制点P  
我们知道的只有数据点D，首先需要得到基函数N的节点向量u,v和遍历的参数s,t  

基函数N的节点向量u,v  
基于数据点D，就能够构造基函数N，详见书中第一部分，Uniform、Chord、Centripetal等不同的构建方法，能够得到u，v  

遍历的参数s,t  
当得到节点向量u，v之后，就可以得到参数s，t，即图片：  
![image](https://github.com/ZhouXiner/B-interpolation-and-fit-/blob/master/PIC/Screenshot%20from%202020-02-17%2013-47-48.png)    
详见书中 第一部分的Parameters and Knot Vectors for Surfaces  

得到节点向量和s，t之后，我们如何反解出控制点?先看对于二维的曲线如何反解  

对于二维的曲线信息
=
![image](https://github.com/ZhouXiner/B-interpolation-and-fit-/blob/master/PIC/Screenshot%20from%202020-02-17%2013-50-29.png)  
我们根据上面求出了N的节点向量和参数u(即上面的s,t)，将其矩阵化，得到  
![image](https://github.com/ZhouXiner/B-interpolation-and-fit-/blob/master/PIC/Screenshot%20from%202020-02-17%2013-50-38.png)  
即  
![image](https://github.com/ZhouXiner/B-interpolation-and-fit-/blob/master/PIC/Screenshot%20from%202020-02-17%2013-50-57.png)  
不多说了，对于AX=B的矩阵，你可以采用LU分解等等办法求出X，即这里的P，EIGEN库提供了求解方法，如果想自己实现，可以参见书中的第二部分Solving Systems of Linear Equations  

对于三维曲面  
=  [1]  
![image](https://github.com/ZhouXiner/B-interpolation-and-fit-/blob/master/PIC/Screenshot%20from%202020-02-17%2013-51-34.png)   
其中有[2]    
![image](https://github.com/ZhouXiner/B-interpolation-and-fit-/blob/master/PIC/Screenshot%20from%202020-02-17%2013-51-47.png)   
进而原式可以改写成[3]    
![image](https://github.com/ZhouXiner/B-interpolation-and-fit-/blob/master/PIC/Screenshot%20from%202020-02-17%2013-51-52.png)  
即将其拆为两次的二维的求解过程，我们根据[3]先求出Q，再根据[2]求出P  










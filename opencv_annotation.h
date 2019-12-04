#ifndef OPENCV_ANNOTATION_H
#define OPENCV_ANNOTATION_H

#include <QMainWindow>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;


class opencv_annotation : public QMainWindow
{
    Q_OBJECT
public:

   void initialize();
   void CallBackFunc(int event,int x,int y,int flags,void* userdata);


private:
    cv::Point p1,p2;
    string windowName="Annotation";
    Mat image;


signals:
    void run();

public slots:
    void get_image(Mat image);
};

#endif // OPENCV_ANNOTATION_H

#ifndef YOLOV3_H
#define YOLOV3_H
#include<QFile>
#include<QVector>
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv/cv.hpp>

class yolov3:public QObject
{
       Q_OBJECT

public:
    yolov3();
    QVector<QString>classes;
    QVector<int>classids;
    QVector<float>confidences;
    QVector<QRect>boxes;

    cv::Mat image;




signals:
     void send_boxes(QVector<QRect>&qbox);



private:

     //initialize the parameter
    float confThreshold=0.5; //confidence threshold
    float nmsThreshold =0.4; //Non-maxium suppression threshold
    int inpWidth=416;   //Width of network's input image
    int inpHeight=416; //Height of network's input image
    

   QString classesFile="coco.names";
   QString line;
   QString modelConfiguration="yolov3.cfg";
   QString modelWeights="yolov3.weights";

   void load_network();






 
private slots:
   void recieve_image(cv::Mat& img);
    
    
    
    
    
    
    
    
    
};

#endif // YOLOV3_H

#include "yolov3.h"
#include<QTextStream>
#include<opencv2/dnn.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include<opencv2/opencv.hpp>



yolov3::yolov3()
{

    using namespace cv;
    using namespace dnn;


}

void yolov3::load_network()
{

    classes.clear();

    QFile inputFile(classesFile);

    if(inputFile.open(QIODevice::ReadOnly))
    {

       QTextStream in(&inputFile);

       while(!in.atEnd())
       {

              QString line=in.readLine();
              classes.push_front(line);
       }

    }
    else{
          std::cout<<"File is not opened"<<std::endl;
    }

    //Load the network

    cv::dnn::Net net =cv::dnn::reareadNetFromDarknet(modelConfiguration, modelWeights);
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);


    cv::Mat frame,blob;

    //get the Next image...
    frame=image;

    //convert the image to blob

    cv::dnn::blobFromImages(frame,blob,1/255,cvSize(inpHeight,inpHeight),Scalar(0,0,0),true,false);

    net.setInput(blob);
    QVector<cv::Mat>outs;

    net.forward(outs,getcOutputsNames(net));


   //removing boxes from outputs....


    for(int i=0;i<outs.size();i++)
    {
        // Scan through all the bounding boxes output from the network and keep only the
                // ones with high confidence scores. Assign the box's class label as the class
                // with the highest score for the box.

        float *data=(float*)outs[i].data;
        for(int j=0;j<outs[i].rows;++j,data+=outs[i].cols){

             cv::Mat scores=outs[i].row(j).colRange(5,out[i].cols);
             Point classIdPoint;
             double confidences;



             //get the value and location of the maximum score
             cv::minMaxLoc(scores,0,&confidences,0,&classIdPoint);

             if(confidences>confThreshold)
             {

                 int centerX=(int)(data[0]*frame.cols);
                 int centerY=(int)(data[1]*frame.rows);
                 int width=(int)(data[2]*frame.cols);
                 int height=(int)(data[3]*frame.cols);

                 int left=centerX-width/2;
                 int top=centerY-height/2;

                 classIds.oush_back(classIdPoint.x);
                 confidences.push_back((float)confidences);
                 boxes.push_back(Rect(left,top,width,height));



             }

        }



    }


    // Perform non maximum suppression to eliminate redundant overlapping boxes with
       // lower confidences

    QVector<int>indices;
    cv::dnn::NMSBoxes(boxes,confidences,confThreshold,nmsThreshold,indices);

   QVectdor<QRect>qbox;

    for(int i=0;i<indices.size();i++){

        int idx=indices[i];
        cv::Rect box=boxes[idx];
        qbox.push_back(box);

    }
    emit send_boxes(qbox);




}

void yolov3::recieve_image(cv::Mat &img)
{
   image=img;

}

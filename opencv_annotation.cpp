#include "opencv_annotation.h"


void opencv_annotation:: CallBackFunc(int event,int x,int y,int flags,void* userdata)
{
    if(event==EVENT_LBUTTONDOWN && p1.x==-1 && p1.y ==-1){
        p1=Point(x,y);
        std::cout<<"Left button clicked"<<std::endl;
    }
    else if(event==EVENT_LBUTTONDOWN &&p1.x!=-1 && p1.y!=-1){
       p2=Point(x,y);
       std::cout<<"Yes line drawing"<<std::endl;
       cv::imshow(windowName,image);
       emit run();
       p1=p2;
    }
    else if(event==EVENT_RBUTTONDOWN){
        p1.x=-1;
        p1.y=-1;
        std::cout<<"Right button clicked"<<std::endl;
    }

}

void opencv_annotation::get_image(Mat image)
{
    image=image;

}

void opencv_annotation::initialize()
{
     cv::Point x(-1,-1);
     p1=x;
     windowName="Annotation";
     image=image;
}

void opencv_annotation::run(){

         cv:: namedWindow(windowName,1);
         cv::setMouseCallback(windowName,CallBackFunc,NULL);
            cv::imshow(windowName,image);


}

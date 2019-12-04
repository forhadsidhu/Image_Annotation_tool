#include "matdisplay.h"
#include<QFileDialog>
#include<QString>
#include<stdio.h>
#include<iostream>
#include<QFile>
#include<QTextStream>

matDisplay::matDisplay(QWidget* parent):QLabel(parent)

{
      //  mPix.load(image_path);
         std::cout<<"YA"<<std::endl;
        //std::cout<<img_path.toStdString()<<std::endl;

       // mPix.fill(Qt::white);




       //set everything to false as nothing has started yet
       mousePressed = true;
       drawStarted = false;

       //default is line
       selectedTool = -1;
       QPen myPen(Qt::red, 4, Qt::SolidLine);
       painter.setPen(myPen);


       QString data;


}


matDisplay::~matDisplay()
{

}

//sending mouse position
void matDisplay::mouseMoveEvent(QMouseEvent *mouse_event)
{

    //As mouse is moving set the second point again and again
       // and update continuously
       if(mouse_event->type() == QEvent::MouseMove){
           if(selectedTool == 1){
               mRect.setBottomRight(mouse_event->pos());

           }
           else if (selectedTool == 2){
               mLine.setP2(mouse_event->pos());


           }
       }







       //it calls the paintEven() function continuously
       update();


    QPoint mouse_pos=mouse_event->pos();
    emit send_mouse_pos(mouse_pos);



}

void matDisplay::mousePressEvent(QMouseEvent *mouse_event)
{
    //Mouse is pressed for the first time
        mousePressed = true;

        //set the initial line points, both are same
        if(selectedTool == 1){
            mRect.setTopLeft(mouse_event->pos());
            mRect.setBottomRight(mouse_event->pos());


        }
        else if (selectedTool == 2){
            mLine.setP1(mouse_event->pos());
            mLine.setP2(mouse_event->pos());

            //push the point in the vector.

        }

        if (mouse_event->button()==Qt::LeftButton){

             std::cout<<"Yes left button clicked"<<std::endl;

             QPoint t;
             t.setY(mouse_event->pos().x());
             t.setX(mouse_event->pos().y());

             vc.push_back(t);

            }


        if (mouse_event->button()==Qt::RightButton){


                QPoint t;
                t.setY(mouse_event->pos().x());
                t.setX(mouse_event->pos().y());

               vc.push_back(t);
               emit send_point_vector(vc);
               vc.clear();

                std::cout<<"Yes right button clicked"<<std::endl;

            }


}

void matDisplay::mouseReleaseEvent(QMouseEvent *mouse_event)
{



    QPen myPen(Qt::black, 2, Qt::SolidLine);
    painter.setPen(myPen);


    //When mouse is released update for the one last time
    mousePressed = false;
    update();
}

void matDisplay::paintEvent(QPaintEvent *mouse_event)
{
    QPen myPen(Qt::black, 2, Qt::SolidLine);
    painter.setPen(myPen);
    painter.begin(this);

     //When the mouse is pressed
     if(mousePressed){
         // we are taking QPixmap reference again and again
         //on mouse move and drawing a line again and again
         //hence the painter view has a feeling of dynamic drawing
         QPen myPen(Qt::red, 4, Qt::SolidLine);
         painter.setPen(myPen);
         painter.drawPixmap(0,0,mPix);
         if(selectedTool == 1){
             QPen myPen(Qt::red, 4, Qt::SolidLine);
             painter.setPen(myPen);
             painter.drawRect(mRect);
         }
         else if(selectedTool == 2){
             QPen myPen(Qt::red, 4, Qt::SolidLine);
             painter.setPen(myPen);
             painter.drawLine(mLine);
             }

         drawStarted = true;
     }
     else if (drawStarted){
         // It created a QPainter object by taking  a reference
         // to the QPixmap object created earlier, then draws a line
         // using that object, then sets the earlier painter object
         // with the newly modified QPixmap object
         QPainter tempPainter(&mPix);
         if(selectedTool == 1){
             QPen myPen(Qt::black, 2, Qt::SolidLine);
             painter.setPen(myPen);
             tempPainter.drawRect(mRect);
         }
         else if(selectedTool == 2){
             QPen myPen(Qt::black, 2, Qt::SolidLine);
             painter.setPen(myPen);
             tempPainter.drawLine(mLine);
         }


         QPen myPen(Qt::red, 4, Qt::SolidLine);
         painter.setPen(myPen);
         painter.drawPixmap(0,0,mPix);
     }







     painter.end();
}

void matDisplay::receive_image_path(QString &path)
{
    std::cout<<path.toStdString()<<std::endl;
    img_path=path;





     mPix = QPixmap(QDir::toNativeSeparators(img_path));
     std::cout<<mousePressed<<std::endl;

     //When mouse is released update for the one last time
     mousePressed = false;
     update();






}

void matDisplay::receive_tool_selection(int tool)
{
    selectedTool=tool;

}


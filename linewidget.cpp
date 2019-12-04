#include "linewidget.h"
#include <QMouseEvent>
#include <QPainter>

linewidget::linewidget(QWidget *parent) : QWidget(parent)
{



        mPix = QPixmap(400,400);
        mPix.fill(Qt::white);

        //set everything to false as nothing has started yet
        mousePressed = false;
        drawStarted = false;

        //default is line
        selectedTool = 2;

}
void linewidget::mousePressEvent(QMouseEvent* event){
    //Mouse is pressed for the first time
    mousePressed = true;

    //set the initial line points, both are same
    if(selectedTool == 1){
        mRect.setTopLeft(event->pos());
        mRect.setBottomRight(event->pos());
    }
    else if (selectedTool == 2){
        mLine.setP1(event->pos());
        mLine.setP2(event->pos());
    }
}

void linewidget::mouseMoveEvent(QMouseEvent* event){

    //As mouse is moving set the second point again and again
    // and update continuously
    if(event->type() == QEvent::MouseMove){
        if(selectedTool == 1){
            mRect.setBottomRight(event->pos());
        }
        else if (selectedTool == 2){
            mLine.setP2(event->pos());
        }
    }

    //it calls the paintEven() function continuously
    update();
}
void linewidget::mouseReleaseEvent(QMouseEvent *event){

    //When mouse is released update for the one last time
    mousePressed = false;
    update();
}

void linewidget::paintEvent(QPaintEvent *event){

    painter.begin(this);

    //When the mouse is pressed
    if(mousePressed){
        // we are taking QPixmap reference again and again
        //on mouse move and drawing a line again and again
        //hence the painter view has a feeling of dynamic drawing
        painter.drawPixmap(0,0,mPix);
        if(selectedTool == 1)
            painter.drawRect(mRect);
        else if(selectedTool == 2)
            painter.drawLine(mLine);

        drawStarted = true;
    }
    else if (drawStarted){
        // It created a QPainter object by taking  a reference
        // to the QPixmap object created earlier, then draws a line
        // using that object, then sets the earlier painter object
        // with the newly modified QPixmap object
        QPainter tempPainter(&mPix);
        if(selectedTool == 1)
            tempPainter.drawRect(mRect);
        else if(selectedTool == 2)
            tempPainter.drawLine(mLine);

        painter.drawPixmap(0,0,mPix);
    }

    painter.end();
}


//only two button is on the ui btnLine and btnRect
void linewidget::on_btnLine_clicked()
{
    selectedTool = 2;
}

void linewidget::on_btnRect_clicked()
{
    selectedTool = 1;
}



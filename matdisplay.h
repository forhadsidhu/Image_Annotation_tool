#ifndef MATDISPLAY_H
#define MATDISPLAY_H

#include <QObject>
#include <QWidget>
#include<QLabel>
#include<QMouseEvent>
#include<QLabel>
#include<QPainter>
#include<QTextStream>
#include<Qvector>

namespace Ui {
    class matDisplay;
}


class matDisplay : public QLabel
{
    Q_OBJECT



public:
    matDisplay(QWidget *parent=0); //constructor with default arguments
   // void display_image();
   // QString image_path;


    bool mousePressed;
    bool drawStarted;
    int selectedTool;


    ~matDisplay();


protected:

    void mouseMoveEvent(QMouseEvent *mouse_event);
    void mousePressEvent(QMouseEvent *mouse_event);
    void mouseReleaseEvent(QMouseEvent *mouse_event);
    void paintEvent(QPaintEvent *mouse_event);


signals:
  void send_mouse_pos(QPoint& pos);

  void send_point_vector(QVector<QPoint>&points);


private slots:
  void receive_image_path(QString& path);
  void receive_tool_selection(int tool);
private:


    //we declare a linewidget pointer object using namespace identifier;


    Ui::matDisplay *ui;
    QPainter painter;

    QPixmap mPix;
    QLine mLine;
    QRect mRect;
    QString img_path;
    QTextStream stream;
    QFile file;
    QVector<QPoint>vc;
    QString lbl;



};

#endif // MATDISPLAY_H

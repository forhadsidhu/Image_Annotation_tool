#ifndef IMAGEANNOTATION_H
#define IMAGEANNOTATION_H

#include <QMainWindow>
#include<matdisplay.h>
#include<QString>
#include<stdio.h>
#include<iostream>
#include<QFileDialog>
#include<QListWidget>
#include<QListWidgetItem>
#include<QVector>
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv/cv.hpp>

namespace Ui {
class ImageAnnotation;
}

class ImageAnnotation : public QMainWindow
{
    Q_OBJECT

public:


    explicit ImageAnnotation(QWidget *parent = 0);
   // QString filename;

    QPoint pos;




    ~ImageAnnotation();




signals:
    void send_image_path(QString& path);
    void send_image(cv::Mat image);
    void send_tool_signal(int tool);


private slots:

    void on_pushButton_clicked();
    void receive_signal(QPoint& pos);


    void on_next_clicked();

    void on_file_list_itemClicked(QListWidgetItem *item);

    void on_prev_clicked();

    void receive_points(QVector<QPoint>&points);

    void on_toolButton_clicked();

    void receieve_boxes(QVector<QRect>&boxes);


    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ImageAnnotation *ui;
    int indx;
    QStringList filenames;
    QDir directory;
    QRect final_rect;
    QLine final_line;
    bool f=false;
    QVector<QString>txt_list;
    QString annotation_label;
    QString txt;







};

#endif // IMAGEANNOTATION_H

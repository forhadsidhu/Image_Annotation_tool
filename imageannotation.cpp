#include "imageannotation.h"
#include "ui_imageannotation.h"
#include "matdisplay.h"
#include<QFileDialog>
#include<QString>
#include<stdio.h>
#include<iostream>
#include<QFile>
#include<yolov3.h>



ImageAnnotation::ImageAnnotation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageAnnotation)
{
    ui->setupUi(this);
    indx=0;

    //matDisplay draw;
    int r=0;

    //initaliza the image label
    annotation_label="";
     txt="";

    connect(this,SIGNAL(send_image_path(QString& )),ui->image_label,SLOT(receive_image_path(QString&)));
     connect(this,SIGNAL(send_tool_signal(int)),ui->image_label,SLOT( receive_tool_selection(int)));

    connect(ui->image_label,SIGNAL(send_point_vector(QVector<QPoint>&)),this,SLOT(receive_points(QVector<QPoint>&)));

//twconnect(&yolov3,SIGNAL(send_boxes(QVector<QRect>&)),this,SLOT(receieve_boxes(QVector<QRect>&)));
}

ImageAnnotation::~ImageAnnotation()
{
    delete ui;
}

void ImageAnnotation::on_pushButton_clicked()
{

   // QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

   // QStringList files = QFileDialog::getOpenFileNames(this,tr("Open File"),"",

                                                                    // tr("All Files (*.jpg *.jpg *.png *.zip)"));

     directory = QFileDialog::getExistingDirectory(this, tr("select directory"));





     filenames = directory.entryList(QStringList() << "*.jpg" << "*.JPG",QDir::Files);





        QString str =directory.filePath(filenames.at(0)) ;

        cv::Mat image= cv::imread(str.toStdString());
        emit send_image(image);


       // ui->pushButton->setText(str);

        emit send_image_path(str);




        indx++;
        QStringList items;

        for(int i=0;i<filenames.size();i++)
        {
          items +=filenames[i];


        }
        ui->file_list->addItems(items);


   /*
    filenames=files;

               QString str =filenames.at(indx) ;
               emit send_image_path(str);
               indx++;




    /*
     ui->pushButton->setText(fileName);

    fileName=QDir::toNativeSeparators(fileName);



     QPixmap pix(fileName);
     QImage image;
     bool valid=image.load(fileName);

     emit send_image_path(fileName);
   */











   // ui->pushButton->setText(QString::number(height));
    // ui->pushButton->setText(QString::number(pos.x()));

    /*
    if(valid){


        // ui->pushButton->setText("Image);
       // ui->image_label->setText("Image");
       // ui->pushButton->setText(QString::number(height));
        QSize sizeOfImage = image.size();
        int height = sizeOfImage.height();
        int width = sizeOfImage.width();

        std::cout<<height<<" "<<width<<std::endl;



        // ui->image_label->setPixmap(QPixmap::fromImage(image));


    }
    */

}

void ImageAnnotation::receive_signal(QPoint &pos)
{
    pos=pos;
}





void ImageAnnotation::on_next_clicked()
{
    if(indx<filenames.size()){
     indx++;
    QString str =directory.filePath(filenames.at(indx)) ;
    //ui->pushButton->setText(str);

    emit send_image_path(str);
    }

}

void ImageAnnotation::on_file_list_itemClicked(QListWidgetItem *item)
{

      int index=ui->file_list->currentRow();
      //std::cout<<index<<std::endl;
      indx=index;


     const QString& s = ui->file_list->currentItem()->text();
     QString str =directory.filePath(s) ;
     emit send_image_path(str);
     //ui->pushButton->setText(str);
}


void ImageAnnotation::on_prev_clicked()
{
    if(indx>0)
    {
      indx-=1;
      QString str =directory.filePath(filenames.at(indx)) ;
      //ui->pushButton->setText(str);

      emit send_image_path(str);
    }
}

void ImageAnnotation::receive_points(QVector<QPoint> &points)
{

    QVector<QPoint>ans=points;

    std::cout<<"Vector found"<<std::endl;







     QString str =directory.filePath(filenames.at(indx)) ;

     txt+=str;
     txt+=" ";

     int points_size=points.size();
     std::cout<<points_size<<std::endl;


     txt+=QString::number(points_size);
     txt+=" ";


    for(int i=0;i<points.size();i++)
    {
        int x,y;

        x = points.at(i).x();
        y = points.at(i).y();

        txt+=QString::number(x);
        txt+=" ";
        txt+=QString::number(y);
        txt+=" ";

        std::cout<<x<<" "<<y<<std::endl;

    }











}

void ImageAnnotation::on_toolButton_clicked()
{

    QString absolute=directory.absolutePath();


   absolute+="//";
   absolute+="output.txt";

 //ui->prev->setText(absolute);




   QString fileName(absolute);

   QFile file(fileName);






   if(file.open(QIODevice::WriteOnly | QIODevice::Text)){

     //  std::cout<<"Open"<<std::endl;
       QTextStream stream(&file);




    for(int i=0;i<txt_list.size();i++){
          QString txt="";

            txt+=txt_list[i];

            stream<<txt<<endl;





    }

       std::cout<<"Open"<<std::endl;

   }
   else{
        std::cout<<"not opended"<<std::endl;
         file.close();
   }


}

void ImageAnnotation::receieve_boxes(QVector<QRect> &boxes)
{
  for(int i=0;i<boxes.size();i++)
  {
       std::cout<<"yes box is printing"<<std::endl;

  }
}



void ImageAnnotation::on_toolButton_2_clicked()
{
      int t=2;
      emit send_tool_signal(t);
}

void ImageAnnotation::on_toolButton_3_clicked()
{
    int t=1;
    emit send_tool_signal(t);
}

void ImageAnnotation::on_pushButton_2_clicked()
{
    QString oka=ui->lineEdit->text();

    //annotation_label=oka;
    txt+=oka;
    txt_list.push_back(txt);
    txt="";


}

void ImageAnnotation::on_pushButton_3_clicked()
{
    if(txt_list.size()>0){
    txt_list.pop_back();
    }
}

#include "Main_Window.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPainter>
#include <QDebug>

#include "Graphics_Question_Block.h"
#include "ROM_Reader.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QMainWindow *mainWindow = new QMainWindow();

    QGraphicsScene *scene = new QGraphicsScene(0, 0, 100, 100);
    QGraphicsView *view = new QGraphicsView(scene);
    mainWindow->setCentralWidget(view);
    view->scale(4, 4);

    //Set the background color
    QBrush *brush = new QBrush(QColor(146, 144, 255));
    view->setBackgroundBrush(*brush);

    ROM_Reader romReader;
    romReader.Open_ROM(app.applicationDirPath()+"/SMB1.nes");
    Graphics_Question_Block *tileTest = new Graphics_Question_Block(&romReader);
    scene->addItem(tileTest);


    /*
    //0xAARRGGBB
    //Keep the alpha channel to FF at all times
    QImage image1(8, 8, QImage::Format_ARGB32);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            image1.setPixel(i, j, 0x00000000); //transparent
        }
    }
    QImage image2(8, 8, QImage::Format_ARGB32);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            image2.setPixel(i, j, 0xFFFF0000); //red
        }
    }
    QImage image3(8, 8, QImage::Format_ARGB32);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            image3.setPixel(i, j, 0xFF00FF00); //green
        }
    }
    QImage image4(8, 8, QImage::Format_ARGB32);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            image4.setPixel(i, j, 0xFFFFFF00); //yellow
        }
    }
    QGraphicsPixmapItem *item1 = scene->addPixmap(QPixmap::fromImage(image1));
    item1->setOffset(0, 0);
    QGraphicsPixmapItem *item2 = scene->addPixmap(QPixmap::fromImage(image2));
    item2->setOffset(8, 0);
    QGraphicsPixmapItem *item3 = scene->addPixmap(QPixmap::fromImage(image3));
    item3->setOffset(0, 8);
    QGraphicsPixmapItem *item4 = scene->addPixmap(QPixmap::fromImage(image4));
    item4->setOffset(8, 8);*/

    mainWindow->show();
    return app.exec();
}

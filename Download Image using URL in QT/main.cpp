#include <QCoreApplication>
#include "downloadimage.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    DownloadImage download;
    download.setUrl("https://i.pinimg.com/474x/c5/8a/41/c58a412762da568b8811995d06feed03.jpg");
    download.setPath("C:/Users/HP/Downloads/troy.jpg");
    download.start();
    return a.exec();
}

#include "downloadimage.h"

DownloadImage::DownloadImage(QObject *parent) : QObject(parent)
{
    connect(&manager,&QNetworkAccessManager::finished,this,&DownloadImage::downloadImage);
}

QString DownloadImage::getUrl() const
{
    return url;
}

void DownloadImage::setUrl(const QString &value)
{
    url = value;
}

QString DownloadImage::getPath() const
{
    return path;
}

void DownloadImage::setPath(const QString &value)
{
    path = value;
}

void DownloadImage::start() {

    QUrl qurl(url);
    QNetworkRequest request(qurl);
    manager.get(request);

}

void DownloadImage::downloadImage(QNetworkReply *reply) {

    QByteArray bytes = reply->readAll();
    QImage* image = new QImage();
    image->loadFromData(bytes);
    image->save(path);
    delete image;

}

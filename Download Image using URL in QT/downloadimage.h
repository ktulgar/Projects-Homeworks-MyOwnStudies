#ifndef DOWNLOADIMAGE_H
#define DOWNLOADIMAGE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QByteArray>
#include <QString>
#include <QImage>

class DownloadImage : public QObject
{
    Q_OBJECT
public:
    explicit DownloadImage(QObject *parent = nullptr);

    QString getUrl() const;
    void setUrl(const QString &value);

    QString getPath() const;
    void setPath(const QString &value);

    void start();

signals:

private slots:
    void downloadImage(QNetworkReply *reply);


private:
     QNetworkAccessManager manager;
     QString url;
     QString path;

};

#endif // DOWNLOADIMAGE_H

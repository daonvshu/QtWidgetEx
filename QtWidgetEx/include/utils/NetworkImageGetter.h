#pragma once

#include <qthread.h>

#include <QtNetwork/QNetworkRequest>

#include <qpixmap.h>

class NetworkImageGetter : public QThread {
    Q_OBJECT

public:
    explicit NetworkImageGetter(const QString& url, QObject* parent = nullptr);
    ~NetworkImageGetter();

    NetworkImageGetter* header(const QByteArray& rawHeader, const QByteArray& headerValue);
    NetworkImageGetter* header(QNetworkRequest::KnownHeaders header, const QVariant& value);

signals:
    void hasErr(int code);
    void getImage(QPixmap pixmap);

protected:
    void run() override;

private:
    QString targetUrl;

    QHash<QByteArray, QByteArray> rawHeaders;
    QHash<QNetworkRequest::KnownHeaders, QVariant> knownHeaders;
};
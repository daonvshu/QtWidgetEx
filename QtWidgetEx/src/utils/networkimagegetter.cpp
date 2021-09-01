#include "utils/networkimagegetter.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkProxy>
#include <QtNetwork/QNetworkReply>

#include <qeventloop.h>

#include <qtimer.h>

#include <qdebug.h>

NetworkImageGetter::NetworkImageGetter(const QString& url, QObject* parent)
    : QThread(parent)
    , targetUrl(url)
{
}

NetworkImageGetter::~NetworkImageGetter() {
    //qDebug() << "network image getter released!";
}

NetworkImageGetter* NetworkImageGetter::header(const QByteArray& rawHeader, const QByteArray& headerValue) {
    rawHeaders.insert(rawHeader, headerValue);
    return this;
}

NetworkImageGetter* NetworkImageGetter::header(QNetworkRequest::KnownHeaders header, const QVariant& value) {
    knownHeaders.insert(header, value);
    return this;
}

void NetworkImageGetter::run() {
    auto manager = new QNetworkAccessManager;
    manager->setProxy(QNetworkProxy::NoProxy);

    QNetworkRequest request;
    request.setUrl(QUrl(targetUrl));

    QHashIterator<QByteArray, QByteArray> iterator0(rawHeaders);
    while (iterator0.hasNext()) {
        request.setRawHeader(iterator0.next().key(), iterator0.value());
    }

    QHashIterator<QNetworkRequest::KnownHeaders, QVariant> iterator1(knownHeaders);
    while (iterator1.hasNext()) {
        request.setHeader(iterator1.next().key(), iterator1.value());
    }

    QEventLoop loop;

    connect(manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);

    auto reply = manager->get(request);

    QTimer timeout;
    connect(&timeout, &QTimer::timeout, [&] {
        reply->abort();
        qDebug() << "get image timeout!";
        loop.quit();
    });
    timeout.setSingleShot(true);
    timeout.start(6000);
    loop.exec();
    timeout.stop();

    auto statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    int statusCodeV;
    if (statusCode.isValid() && (statusCodeV = statusCode.toInt()) != 200) {
        qDebug() << "network error, status: " << statusCodeV;
        emit hasErr(statusCodeV);
    } else {
        auto err = reply->error();
        if (statusCode.isValid() || err == QNetworkReply::NoError) {
            QPixmap pixmap;
            pixmap.loadFromData(reply->readAll());
            emit getImage(pixmap);
        } else {
            qDebug() << err;
            emit hasErr(err);
        }
    }

    delete reply;
    delete manager;

    deleteLater();
}

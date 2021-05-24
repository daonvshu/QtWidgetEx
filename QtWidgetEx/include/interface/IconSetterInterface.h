#pragma once

#include "ImageSetterInterface.h"

#include <qpixmap.h>
#include <qimage.h>
#include <qpixmapcache.h>
#include <qicon.h>

#include "utils/NetworkImageGetter.h"

EX_BEGIN_NAMESPACE
class IconSetterCallback {
public:
    virtual void setIconSync(const QIcon& icon, bool resize, const QSize& size) = 0;
};

class IconSetterInterface: public ImageSetterInterface {
public:
    explicit IconSetterInterface(IconSetterCallback* iconSetterCallback, QObject* parent = nullptr);

    ~IconSetterInterface();

private:
    void setDataInMainThread(const QVariant& value) override;

public:
    virtual void operator=(const QPixmap& pximap) override;
    virtual void operator=(const QImage& image) override;
    virtual void operator=(const QString& imagePath) override;
    virtual void operator=(const QIcon& icon);

    IconSetterInterface& target(const QSize& size) {
        ImageSetterInterface::target(size);
        return *this;
    }

    inline IconSetterInterface& target(int w, int h) {
        ImageSetterInterface::target(QSize(w, h));
        return *this;
    }

    inline IconSetterInterface& targetW(int w) {
        ImageSetterInterface::target(w, -1);
        return *this;
    }

    inline IconSetterInterface& targetH(int h) {
        ImageSetterInterface::target(-1, h);
        return *this;
    }

    inline IconSetterInterface& noScale() {
        targetIsSet = false;
        return *this;
    }

    inline IconSetterInterface& network(
        const QString& url,
        const QString& placeholder = QString(),
        const QString& err = QString()
    ) {
        ImageSetterInterface::network(url, placeholder, err);
        return *this;
    }

    inline IconSetterInterface& network2(
        const QString& url,
        const QPixmap& placeholder = QPixmap(),
        const QPixmap& err = QPixmap()
    ) {
        ImageSetterInterface::network2(url, placeholder, err);
        return *this;
    }

private:
    void operator=(const QBitmap& bitmap);

private:
    IconSetterCallback* iconSetterCallback;
};
EX_END_NAMESPACE
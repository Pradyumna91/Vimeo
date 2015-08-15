#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include <QObject>
#include "video.h"
#include "OpenShot.h"

class Transformer : public QObject
{
    Q_OBJECT
public:
    explicit Transformer(QObject *parent = 0);

signals:
    void editingDone(QString outputFilepath);

public slots:
    void addOverlay(QString video, QString imageFilePath);
};

#endif // TRANSFORMER_H

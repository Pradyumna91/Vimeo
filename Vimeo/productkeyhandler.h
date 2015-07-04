#ifndef UTILITY_H
#define UTILITY_H

#include <QObject>

class ProductKeyHandler : public QObject
{
    Q_OBJECT
public:
    static bool isLincensedProduct();
    static bool isValidProductKey(QString productKey);
};

#endif // UTILITY_H

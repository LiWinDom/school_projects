#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QString>
#include <QListWidget>

#include "classes.h"

class Functions
{
public:
    void addSegment(Polynomial*& plc, Segment* segment);

    QString polynomialToText(Polynomial* plc);

    void checkPolychelous(const QString& text);

    Polynomial* textToPolynomial(QString text);

    void addPolynomial(Base*& base, Polynomial* plc);

    void updateList(QListWidget*& listWidget, Base* base);


    Polynomial* sum(Polynomial* plc1, Polynomial* plc2);

    Polynomial* mult(Polynomial* plc1, Polynomial* plc2);

    Polynomial* der(Polynomial* plc, const uint8_t& by);
};

#endif // FUNCTIONS_H

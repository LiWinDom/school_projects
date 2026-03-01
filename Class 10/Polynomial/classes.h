#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <QString>

struct Segment {
    int32_t coef = 1;
    uint16_t deg[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    Segment* next = nullptr;
};

struct Polynomial {
    Segment* data = nullptr;
    Polynomial* next = nullptr;
};

struct Base {
    Polynomial* data = nullptr;
};

class Error {
public:
    Error(const QString& type, const QString& descr);

    QString type;
    QString descr;
};

#endif // CLASSES_H

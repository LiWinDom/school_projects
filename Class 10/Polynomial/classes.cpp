#include "classes.h"

Error::Error(const QString& type, const QString& descr) {
    this->type = type;
    this->descr = descr;
}

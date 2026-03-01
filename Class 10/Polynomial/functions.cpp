#include "functions.h"

void Functions::addSegment(Polynomial*& plc, Segment* segment) {
    if (segment->coef == 0) return;
    if (plc->data == nullptr) {
        plc->data = segment;
        return;
    }
    Segment* p = plc->data;
    Segment* last = nullptr;
    while (p != nullptr) {
        for (uint8_t i = 0; i < 26; ++i) {
            if (p->deg[i] > segment->deg[i]) break;
            if (p->deg[i] < segment->deg[i]) {
                segment->next = p;
                if (last == nullptr) {
                    plc->data = segment;
                }
                else {
                    last->next = segment;
                }
                return;
            }
            if (i == 25) {
                p->coef += segment->coef;
                if (p->coef == 0) {
                    if (last == nullptr) {
                        plc->data = p->next;
                    }
                    else {
                        last->next = p->next;
                    }
                    delete p;
                }
                return;
            }
        }
        last = p;
        p = p->next;
    }
    last->next = segment;
    return;
}

QString Functions::polynomialToText(Polynomial* plc) {
    QString text;
    Segment* segment = plc->data;
    while (segment != nullptr) {
        if (text != "") {
            if (segment->coef > 0) {
                text += '+';
            }
        }
        bool allEmpty = true;
        for (uint8_t i = 0; i < 26; ++i) {
            if (segment->deg[i] != 0) {
                allEmpty = false;
                break;
            }
        }
        if (std::abs(segment->coef) != 1 || allEmpty) {
            text += QString::number(segment->coef);
        }
        else if (segment->coef == -1) {
            text += '-';
        }
        for (uint8_t i = 0; i < 26; ++i) {
            if (segment->deg[i] != 0) {
                char letter = i + 'a';
                text += letter;
                if (segment->deg[i] != 1) {
                    text+= '^' + QString::number(segment->deg[i]);
                }
            }
        }
        segment = segment->next;
    }
    if (text == "") return "0";
    return text;
}

void Functions::checkPolychelous(const QString& text) {
    QString last = "start";
    for (uint8_t i = 0; i < text.size(); ++i) {
        if (last == "start") {
            if (text[i] == ' ') {
                continue;
            }
            if (text[i] == '-' || text[i] == '+') {
                last = "operator";
                continue;
            }
            if (text[i] >= '0' && text[i] <= '9') {
                last = "number";
                continue;
            }
            if (text[i] >= 'a' && text[i] <= 'z') {
                last = "letter";
                continue;
            }
        }
        if (last == "operator") {
            if (text[i] == ' ') {
                continue;
            }
            if (text[i] >= '0' && text[i] <= '9') {
                last = "number";
                continue;
            }
            if (text[i] >= 'a' && text[i] <= 'z') {
                last = "letter";
                continue;
            }
        }
        if (last == "number") {
            if (text[i] == ' ') {
                last = "numSpace";
                continue;
            }
            if (text[i] == '-' || text[i] == '+') {
                last = "operator";
                continue;
            }
            if (text[i] >= '0' && text[i] <= '9') {
                continue;
            }
            if (text[i] >= 'a' && text[i] <= 'z') {
                last = "letter";
                continue;
            }
        }
        if (last == "letter") {
            if (text[i] == ' ') {
                continue;
            }
            if (text[i] == '-' || text[i] == '+') {
                last = "operator";
                continue;
            }
            if (text[i] >= 'a' && text[i] <= 'z') {
                continue;
            }
            if (text[i] == '^') {
                last = "^";
                continue;
            }
        }
        if (last == "numSpace") {
            if (text[i] == ' ') {
                continue;
            }
            if (text[i] == '-' || text[i] == '+') {
                last = "operator";
                continue;
            }
            if (text[i] >= 'a' && text[i] <= 'z') {
                last = "letter";
                continue;
            }
        }
        if (last == "^") {
            if (text[i] == ' ') {
                continue;
            }
            if (text[i] >= '0' && text[i] <= '9') {
                last = "degree";
                continue;
            }
        }
        if (last == "degree") {
            if (text[i] == ' ') {
                last = "degSpace";
                continue;
            }
            if (text[i] == '-' || text[i] == '+') {
                last = "operator";
                continue;
            }
            if (text[i] >= '0' && text[i] <= '9') {
                continue;
            }
            if (text[i] >= 'a' && text[i] <= 'z') {
                last = "letter";
                continue;
            }
        }
        if (last == "degSpace") {
            if (text[i] == ' ') {
                continue;
            }
            if (text[i] == '-' || text[i] == '+') {
                last = "operator";
                continue;
            }
            if (text[i] >= 'a' && text[i] <= 'z') {
                last = "letter";
                continue;
            }
        }
        throw new Error("Input", QString::fromStdString("Unexpected \"") + text[i] + QString::fromStdString("\" at position ") + QString::number(i + 1));
    }
    if (last == "start") {
        throw new Error("Input", "Cannot add empty polynomial");
    }
    if (last == "operator" || last == "^") {
        throw new Error("Input", "Unexpected end of polynomial");
    }
    return;
}

Polynomial* Functions::textToPolynomial(QString text) {
    this->checkPolychelous(text);

    Polynomial* newPlc = new Polynomial;
    Segment* segment = new Segment;

    std::string newText = text.replace(" ", "").toStdString();
    QString last = "start";
    bool negCoef = false;
    uint8_t lastLetter = 0;
    uint16_t deg = 0;
    for (uint8_t i = 0; i < newText.size(); ++i) {
        if (last == "start") {
            if (newText[i] == '-') {
                last = "operator";
                negCoef = true;
                continue;
            }
            if (newText[i] >= '0' && newText[i] <= '9') {
                last = "number";
                segment->coef = (segment->coef - 1) * 10 + (newText[i] & 15);
                continue;
            }
            if (newText[i] >= 'a' && newText[i] <= 'z') {
                last = "letter";
                ++segment->deg[newText[i] - 'a'];
                lastLetter = newText[i] - 'a';
                continue;
            }
        }
        if (last == "operator") {
            if (newText[i] >= '0' && newText[i] <= '9') {
                last = "number";
                segment->coef = (segment->coef - 1) * 10 + (newText[i] & 15);
                continue;
            }
            if (newText[i] >= 'a' && newText[i] <= 'z') {
                last = "letter";
                ++segment->deg[newText[i] - 'a'];
                lastLetter = newText[i] - 'a';
                continue;
            }
        }
        if (last == "number") {
            if (newText[i] == '-' || newText[i] == '+') {
                last = "operator";
                if (negCoef) {
                    segment->coef = -segment->coef;
                }
                this->addSegment(newPlc, segment);
                segment = new Segment;
                if (newText[i] == '-') negCoef = true;
                else negCoef = false;
                continue;
            }
            if (newText[i] >= '0' && newText[i] <= '9') {
                segment->coef = segment->coef * 10 + (newText[i] & 15);
                continue;
            }
            if (newText[i] >= 'a' && newText[i] <= 'z') {
                last = "letter";
                ++segment->deg[newText[i] - 'a'];
                lastLetter = newText[i] - 'a';
                continue;
            }
        }
        if (last == "letter") {
            if (newText[i] == '-' || newText[i] == '+') {
                last = "operator";
                if (negCoef) {
                    segment->coef = -segment->coef;
                }
                this->addSegment(newPlc, segment);
                segment = new Segment;
                if (newText[i] == '-') negCoef = true;
                else negCoef = false;
                continue;
            }
            if (newText[i] >= 'a' && newText[i] <= 'z') {
                ++segment->deg[newText[i] - 'a'];
                lastLetter = newText[i] - 'a';
                continue;
            }
            if (newText[i] == '^') {
                last = "degree";
                continue;
            }
        }
        if (last == "degree") {
            if (newText[i] == '-' || newText[i] == '+') {
                last = "operator";
                segment->deg[lastLetter] += deg - 1;
                deg = 0;
                this->addSegment(newPlc, segment);
                segment = new Segment;
                if (newText[i] == '-') negCoef = true;
                else negCoef = false;
                continue;
            }
            if (newText[i] >= '0' && newText[i] <= '9') {
                deg = deg * 10 + (newText[i] & 15);
                if (i + 1 == newText.size()) {
                    segment->deg[lastLetter] += deg - 1;
                }
                continue;
            }
            if (newText[i] >= 'a' && newText[i] <= 'z') {
                last = "letter";
                segment->deg[lastLetter] += deg - 1;
                ++segment->deg[newText[i] - 'a'];
                lastLetter = newText[i] - 'a';
                deg = 0;
                continue;
            }
        }
    }
    if (negCoef) {
        segment->coef = -segment->coef;
    }
    this->addSegment(newPlc, segment);

    return newPlc;
}

void Functions::addPolynomial(Base*& base, Polynomial* plc) {
    if (base->data == nullptr) {
        base->data = plc;
        return;
    }
    Polynomial* p = base->data;
    while(p->next != nullptr) {
        p = p->next;
    }
    p->next = plc;

    return;
}

void Functions::updateList(QListWidget*& listWidget, Base* base) {
    listWidget->clear();
    Polynomial* p = base->data;
    while (p != nullptr) {
        listWidget->addItem(this->polynomialToText(p));
        p = p->next;
    }
    return;
}

Polynomial* Functions::sum(Polynomial* plc1, Polynomial* plc2) {
    Polynomial* plc = new Polynomial;
    Segment* sg1 = plc1->data, *sg2 = plc2->data;

    while (sg1 != nullptr) {
        Segment* newSg = new Segment;
        newSg->coef = sg1->coef;
        for (uint8_t i = 0; i < 26; ++i) {
            newSg->deg[i] = sg1->deg[i];
        }
        this->addSegment(plc, newSg);
        sg1 = sg1->next;
    }
    while (sg2 != nullptr) {
        Segment* newSg = new Segment;
        newSg->coef = sg2->coef;
        for (uint8_t i = 0; i < 26; ++i) {
            newSg->deg[i] = sg2->deg[i];
        }
        this->addSegment(plc, newSg);
        sg2 = sg2->next;
    }

    return plc;
}

Polynomial* Functions::mult(Polynomial* plc1, Polynomial* plc2) {
    Polynomial* plc = new Polynomial;
    Segment* sg1 = plc1->data;

    while (sg1 != nullptr) {
        Segment* sg2 = plc2->data;
        while (sg2 != nullptr) {
            Segment* newSg = new Segment;
            newSg->coef = sg1->coef * sg2->coef;
            for (uint8_t i = 0; i < 26; ++i) {
                newSg->deg[i] = sg1->deg[i] + sg2->deg[i];
            }
            this->addSegment(plc, newSg);
            sg2 = sg2->next;
        }
        sg1 = sg1->next;
    }

    return plc;
}

Polynomial* Functions::der(Polynomial* plc, const uint8_t& by) {
    Polynomial* newPlc = new Polynomial;
    Segment* sg = plc->data;

    while (sg != nullptr) {
        Segment* newSg = new Segment;
        newSg->coef = sg->coef;
        for (uint8_t i = 0; i < 26; ++i) {
            if (i == by) {
                newSg->coef *= sg->deg[i];
                newSg->deg[i] = sg->deg[i] - 1;
            }
            else {
                newSg->deg[i] = sg->deg[i];
            }
        }
        this->addSegment(newPlc, newSg);
        sg = sg->next;
    }

    return newPlc;
}

#ifndef ELEMENT_H
#define ELEMENT_H

class Element{
public:
    virtual ~Element()= default;
    virtual int isElem() = 0;
};

#endif // ELEMENT_H

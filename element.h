#ifndef ELEMENTH
#define ELEMENTH

#include "defines.h"

class Element
{
protected:
    float x, y;

public:
    Element(float, float);
    inline ~Element() {};

    void setX(float);
    void setY(float);

    void updatePosition(float, float);

    void copy(Element &);

    //void drawThisAndSubs();
    inline virtual void draw(float = 0, float = 0) const {};
};

/*class ElementQueue
{
    private:
        struct Node
        {
            Element element;
            Node *next;
        };

        Node *start;
    public:
        ElementQueue();

        void addNode(Element &);
        void removeNode(short int);
        void destroyQueue();
};*/

class ElementSquareShape : public Element
{
protected:
    float w;

public:
    ElementSquareShape(float, float, float);

    void setW(float);

    void updateSize(float);
    virtual void updateSizeAndPosition(float, float, float);

    bool isWithinThis(float, float) const;
};

#endif
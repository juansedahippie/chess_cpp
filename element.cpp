#include "element.h"

Element::Element(float x_in, float y_in)
{
    setX(x_in);
    setY(y_in);
}

void Element::setX(float x_in) { x = x_in; }
void Element::setY(float y_in) { y = y_in; }

void Element::updatePosition(float x_in, float y_in)
{
    setX(x_in);
    setY(y_in);
}

void Element::copy(Element &in)
{
    setX(in.x);
    setY(in.y);
}

/*ElementQueue::ElementQueue()
{
    start = nullptr;
}

void ElementQueue::addNode(Element &)
{

}*/

ElementSquareShape::ElementSquareShape(float x_in, float y_in, float w_in) : Element(x_in, y_in)
{
    setW(w_in);
}

void ElementSquareShape::setW(float w_in) { w = w_in; }

void ElementSquareShape::updateSize(float w_in)
{
    setW(w_in);
}

void ElementSquareShape::updateSizeAndPosition(float x_in, float y_in, float w_in)
{
    updatePosition(x_in, y_in);
    updateSize(w_in);
}

bool ElementSquareShape::isWithinThis(float x_in, float y_in) const
{
    return ((x_in > x) && (x_in < x + w) && (y_in > y) && (y_in < y + w));
}
#ifndef WIDGETBASE_H_INCLUDED
#define WIDGETBASE_H_INCLUDED

#include "../coor.h"
#include "../graphicsPlus.h"

#include "graphics.hpp"

//Mother of all widgets.
class widgetBase
{
    protected:
        virtual void draw(); //...
        virtual void redraw(); //clears, then draws
        void addFrame();
        int width;
        int height;
        coor upperLeftCorner;
        coor downerRightCorner;
        coor origo;
        vector <widgetBase*> subWidgets;
    public:
        widgetBase(coor upperLeftCorn, coor downerRightCorn);
        virtual ~widgetBase();
        virtual void update();
        virtual void mouseUp();
        virtual void mouseDown();
        virtual void mouseWheelUp(event mE);
        virtual void mouseWheelDown(event mE);
        virtual void keyDown(event kE);
        virtual void keyUp(event kE);
        virtual void clearWid(); //clears
        virtual void saveData(){};

        static const string DATA_FILE_NAME;
};

#endif // WIDGETBASE_H_INCLUDED
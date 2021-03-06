#ifndef FIELD_H
#define FIELD_H

#include "../../../coor.h"
#include "../../../graphicsPlus.h"
#include "../../../widgets/lButton.h"
#include "field objects/road.h"
#include "field objects/barrack.h"
#include "field objects/village.h"
#include "field objects/stronghold.h"
#include "field objects/mountain.h"

class gameScreen;
class player;

class field
{
    public:
        field(gameScreen* gS, coor coordinate);
        virtual ~field();
        void draw();
        string getType(){return type;};
        void addPart(string part);
        void addOwner(player* owner);
        void removeOwner(player* owner);
        bool isOwner(player* owner);
        bool hasPart(string part);
        bool canAct(player* who);
        bool canBuild(string part);
        void activateStronghold(player* owner); //if it's a stronghold, it gets owner
        void assaultChange(bool changeTo); //if it's a stronghold, assaultChosen changes to @changeTo
        player* objectOwner();
        player* strongholdBuilder();
        void destroyObject();

        static const int WIDTH=30; //=height
        coor origo;
        coor coordinate; //in fields
        vector<player*> owners;
        static const string BLANK;
        static const string ROAD;
        static const string BARRACK;
        static const string VILLAGE;
        static const string STRONGHOLD;
        static const string MOUNTAIN;

    protected:
        gameScreen* myGameScreen;
        string type;
        vector<fieldObject*> myParts;
    private:
};

#endif // FIELD_H

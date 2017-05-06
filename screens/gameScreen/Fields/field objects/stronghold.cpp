#include "stronghold.h"
#include "../../player.h"
#include "../field.h"

stronghold::stronghold(coor origo)
: fieldObject(origo,"pics/game objects/StrongholdBase.kep")
//"pics/game objects/nations/"+owner->nation+"/Stronghold.kep
{
    type=STRONGHOLD;
}

stronghold::~stronghold()
{
    //dtor
}

void stronghold::draw()
{
    fieldObject::draw();
    if (hasOwner)
        territory.draw();
}

void stronghold::gotOwner(player* bowner)
{
    owner=bowner;
    pic.addNewPic("pics/game objects/nations/"+owner->nation+"/Stronghold.kep", origo);
    hasOwner=true;
    pic.setScaleX((double)field::WIDTH/(double)pic.getWidth());
    pic.setScaleY((double)field::WIDTH/(double)pic.getHeight());
    owner->strongholdNumber++;
    territory.addNewPic("pics/game objects/Territory"+numToString(RADIUS)+".kep",origo);
    territory.setScaleX((double)(field::WIDTH*7)/(double)territory.NORMAL_WIDTH);
    territory.setScaleY((double)(field::WIDTH*7)/(double)territory.NORMAL_HEIGHT);
}

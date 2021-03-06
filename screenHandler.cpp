#include "screenHandler.h"

void screenHandler::exitGame()
{
    exitAwesomeness=true;
}

void screenHandler::switchScreen(screen *&currScr)
{
    delete currScr;
    screensAlive.pop_back();
    clearScreen();
    if (screen::switchTo==screen::GAME_SCREEN)
        currScr=new gameScreen();
    else if (screen::switchTo==screen::MENU_SCREEN)
        currScr=new menuScreen();
    else if (screen::switchTo==screen::MAP_EDITOR)
        currScr=new mapEditor();
    else if (screen::switchTo==screen::SETTINGS_SCREEN)
        currScr=new settingsScreen();
    else if (screen::switchTo==screen::TERMINATED)
    {
        exitReqested=false;
        for (screen* s:screensAlive) //drawing screens
            s->draw();
    }
    else if (screen::switchTo==screen::EXIT)
        exitGame();
    if (screen::switchTo!=screen::TERMINATED)
    {
        for (int i=screensAlive.size()-1;i>=0;i--)
        {
            delete screensAlive[i];
            screensAlive.pop_back();
        }
        screensAlive.push_back(currScr);
    }
    screen::switchTo=screen::STAY;
}

void screenHandler::addSub(string newSubName)
{
    screen* currScr;
    if (newSubName==screen::CONFIRM_EXIT)
    {
        if (exitReqested)
            exitGame();
        else
        {
            currScr=new confirmExitScreen();
            exitReqested=true;
        }
    }
    else if (screen::newSub==screen::HOW_TO_PLAY_SCREEN)
        currScr=new howToPlayScreen();
    else if (screen::newSub==screen::HELPII)
        currScr=new helpII();
    else if (screen::newSub==screen::HELPIII)
        currScr=new helpIII();
    else if (screen::newSub==screen::HELPIV)
        currScr=new helpIV();
    else if (screen::newSub==screen::BUILD_CHOOSER_SCREEN)
        currScr=new buildChooserScreen((gameScreen*)screensAlive[screensAlive.size()-1]);
    else if (screen::newSub==screen::PONY_SCREEN)
        currScr=new PonyScreen();
    else if (screen::newSub==screen::NEW_TURN_SCREEN)
        currScr=new newTurnScreen((gameScreen*)screensAlive[screensAlive.size()-1]);
    else if (screen::newSub==screen::SAVE_MAP)
        currScr=new saveMap((mapEditor*)screensAlive[screensAlive.size()-1]);
    else if (screen::newSub==screen::VICTORY_MESSAGE)
        currScr=new victoryMessage((gameScreen*)screensAlive[screensAlive.size()-1]);
    screensAlive.push_back(currScr);
    screen::newSub=screen::STAY;
}

void screenHandler::soul() //the soul of the whole game
{
    gout.open(WINDOW_X,WINDOW_Y);
    screensAlive.push_back(new menuScreen());
    while (!exitAwesomeness)
    {
        event ev;
        gin.timer(1000.0/FPS);
        screen* currentScreen=screensAlive[screensAlive.size()-1];
        while (gin>>ev&&screen::switchTo==screen::STAY&&screen::newSub==screen::STAY)
        {
            screensAlive[screensAlive.size()-1]->soul(ev);
        }
        if (screen::switchTo!=screen::STAY)
            switchScreen(currentScreen);
        if (screen::newSub!=screen::STAY)
            addSub(screen::newSub);
    }
}

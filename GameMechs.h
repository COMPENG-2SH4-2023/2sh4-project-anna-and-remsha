#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <stdlib.h>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        objPos foodPos; //added member holding the most recently generated food objPos
        char input;
        bool exitFlag;

        bool loseFlag; //added member
        int score; // added member
        
        int boardSizeX;
        int boardSizeY;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY); 
        ~GameMechs();
        
        bool getExitFlagStatus();
        void setExitTrue();

        bool getLoseFlagStatus(); //added member
        void setLoseFlag(); // added member

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX();
        int getBoardSizeY();

        int getScore(); // added member
        void incrementScore(); // added member

        void generateFood(objPosArrayList* playerPosList); //added member
        void getFoodPos(objPos &returnPos); //added member

};

#endif
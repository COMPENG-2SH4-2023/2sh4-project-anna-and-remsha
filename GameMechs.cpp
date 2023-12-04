#include "GameMechs.h"
#include "MacUILib.h"
#include <stdlib.h>
#include <time.h>

GameMechs::GameMechs()
{
    input = 0;
    loseFlag = false;
    exitFlag = false;
    boardSizeX = 20;
    boardSizeY = 10;
    score = 0;

    //initialize food
    foodPos.x = 0;
    foodPos.y = 0;
    foodPos.symbol = 'o';
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = boardX;
    boardSizeY = boardY;

    //initialize food
    foodPos.x = 0;
    foodPos.y = 0;
    foodPos.symbol = 'o';
}

// do you need a destructor?
GameMechs:: ~GameMechs(){}
// no

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

char GameMechs::getInput()
{
    // get input from macui 
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();   
    }

    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = 1;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;

}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::generateFood(objPosArrayList* playerPosList){
    int i;
    int x,y;//randomly generated x and y coord
    
    objPos blockOff; //objpos temp for body elements

    do {
        //generate random xy coords
        x = rand() % (boardSizeX-2) ;
        y = rand() % (boardSizeY-2) ;

        for(i=0; i<playerPosList->getSize(); ++i) //every element in body list
        {
            playerPosList->getElement(blockOff, i);    

            if(((x+1)!=blockOff.x) || ((y+1)!=blockOff.y )) //if x or y are different from body
            {
                //set food xy coords 
                foodPos.x = (x+1);
                foodPos.y = (y+1);       
            }
            else{ //if xy match body then start dowhile again
                break;
            }
 
        }
    } while((foodPos.x==blockOff.x) && (foodPos.y==blockOff.y)); //repeat loop and regenerate if xy match

}

void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}
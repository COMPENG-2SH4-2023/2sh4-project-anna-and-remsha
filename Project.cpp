#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"
//rand
#include <stdlib.h>
#include <time.h>

using namespace std;

#define DELAY_CONST 100000
#define MAX_DELAY_CONST 999999 // max delay to show player lose message

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

GameMechs* myGMRef; ///create new gamemech for this game
Player* myPlayer; ///create player 
int moveCount =0;///remove later


int main(void)
{

    Initialize();

    while(myGMRef->getExitFlagStatus() == false)  //loops through as long as the exit flag is false
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }
    
    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGMRef = new GameMechs(26,13); ///create new gamemech for this game
    myPlayer = new Player(myGMRef); ///create player 

    srand(time(NULL)); //seed random generator

    //temp store starting player pos
    objPosArrayList* playerSpawn = myPlayer->getPlayerPos();
    //generate food item 
    myGMRef->generateFood(playerSpawn);

}

void GetInput(void)
{
   char keyBoardInput = myGMRef->getInput();

   if(keyBoardInput == ' '){ // exit character is ' '
        myGMRef->setExitTrue();
   }
    
}


void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    myGMRef->clearInput(); // prevents repeated processing of input
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    bool drawn;

    int boardX=myGMRef->getBoardSizeX(), boardY=myGMRef->getBoardSizeY(); //get() for board dimensions
    char matrix[boardX][boardY] = {0}; //create empty matrix matching board dimensions

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    //playerBody = new objPosArrayList();

    objPos tempBody;

    //store food current position -- change?
    objPos currentFood;
    myGMRef->getFoodPos(currentFood);

    int x;
    int y;

    for(y = 0; y < boardY; y++) //loops through rows
    {
        for(x = 0; x < boardX; x++) // loops through columns
        {
            drawn = false;

            // iterate through every element in the list
            for(int i = 0; i < playerBody->getSize(); i++)
            {
                playerBody->getElement(tempBody, i);

                if(tempBody.x == x && tempBody.y == y)
                {
                    //MacUILib_printf("%c", tempBody.symbol);
                    matrix[x][y] = tempBody.symbol;
                    drawn = true;
                    break;
                }
            }

            if(drawn) continue; // if player body was drawn, don't draw anything below

            else if(x == 0 || y == 0 || x == boardX - 1 || y == boardY - 1) // creates boundary of game board
            {
                matrix[x][y] = '#';
            }
            else if(x == currentFood.x && y == currentFood.y) //if xy is food pos
            {
                matrix[x][y] = currentFood.symbol; //adds the food on board
            }
            else
            {
                matrix[x][y] = ' '; // fills the rest of the board with empty space within the boundary
            }
        }
    }   

    for(int y = 0; y < boardY; y++) //loop to display the board and player
    {
        for(int x = 0; x < boardX; x++)
        {
            MacUILib_printf("%c", matrix[x][y]);
        }
        MacUILib_printf("\n");
    }

    objPos tempPos;
    playerBody->getHeadElement(tempPos);
    
    MacUILib_printf("BoardSize is: %dx%d, Player Pos: <%d,%d> '%c'\n ", boardX, boardY, tempPos.x, tempPos.y, tempPos.symbol);
    //MacUILib_printf("\nFood Pos: <%d,%d> '%c'\n",currentFood.x,currentFood.y,currentFood.symbol);        
    MacUILib_printf("\nMove count: %d Score: %d\n",moveCount++,myGMRef->getScore());
    
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{   
    MacUILib_clearScreen();    

    if(myGMRef->getLoseFlagStatus()==true)
    {
        MacUILib_printf("\nGAME OVER! YOU LOST\n");

    }    
    else
    {
        MacUILib_printf("\nGAME ENDED\n");
    }
    MacUILib_printf("Move count: %d Score: %d\n",moveCount,myGMRef->getScore());

    // loop to have multiple 1 second delays (total 3 seconds)
    for (int i=0; i < 3; i++)
    {
        MacUILib_Delay(MAX_DELAY_CONST); // wait few seconds for user to read message then clean up
    }

    delete(myGMRef);
    delete(myPlayer);

    MacUILib_uninit();
}

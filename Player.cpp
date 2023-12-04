#include "Player.h"
#include <iostream>




Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    // more actions to be included
    // can implement simplified version of below code
    
    //create playerpos for head of snake at middle of board
    objPos playerPos;
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,
                        mainGameMechsRef->getBoardSizeY()/2,
                        '@');
    //create list for snake whole body
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(playerPos);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos array list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic        

    ///ensure input isn't illegal with direction
    if((myDir==UP)&&((mainGameMechsRef->getInput())=='s'))
    {
        mainGameMechsRef->setInput('w');
    }
    if((myDir==DOWN)&&((mainGameMechsRef->getInput())=='w'))
    {
        mainGameMechsRef->setInput('s');  
    }
    if((myDir==RIGHT)&&((mainGameMechsRef->getInput())=='a'))
    {
        mainGameMechsRef->setInput('f');
    }
    if((myDir==LEFT)&&((mainGameMechsRef->getInput())=='d'))
    {
        mainGameMechsRef->setInput('a');
    }

    if((mainGameMechsRef->getInput()) != 0)  // if not null character
    {
        ///update direction according to input
        switch(mainGameMechsRef->getInput())
        {                      
            case ' ':  // exit
                mainGameMechsRef->setExitTrue();
                break;
            case 'w':
                myDir = UP;
                break;
            case 'a':
                myDir = LEFT;
                break;
            case 's':
                myDir = DOWN;
                break;
            case 'd':
                myDir = RIGHT;
                break;
            default:
                break;
        }
        mainGameMechsRef->clearInput();
    }   
}


bool Player::checkSelfCollision() 
{ 
    objPos currentHead; // holding the position information of the current head
    playerPosList->getHeadElement(currentHead);

    objPos currentBody; // variable for holding body object information 

    for(int i=1; i<playerPosList->getSize(); i++) //every element in body list
    {
        playerPosList->getElement(currentBody, i);
        // check if x,y coordinates of head == x,y coordinates of any body element
        if((currentHead.x==currentBody.x) && (currentHead.y==currentBody.y))
        { 
            return true;
        }
    }
    return false; //no collision detected
}


void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    objPos currentHead; // holding the current position information of the head
    playerPosList->getHeadElement(currentHead);
    // updating the coordinate position according to direction with wraparound
    switch(myDir){       
        default:
        case STOP:
            break;
        case RIGHT:
            currentHead.x+=1;
            if (currentHead.x > (mainGameMechsRef->getBoardSizeX()-2))
            {
                currentHead.x = 1;
            }
            break;
        case LEFT:
            currentHead.x-=1;
            if (currentHead.x < 1)
            {
                currentHead.x = (mainGameMechsRef->getBoardSizeX()-2);
            }
            break;
        case UP:
            currentHead.y-=1;
            if (currentHead.y < 1)
            {
                currentHead.y = (mainGameMechsRef->getBoardSizeY()-2);
            }
            break;
        case DOWN:
            currentHead.y+=1;
            if (currentHead.y > (mainGameMechsRef->getBoardSizeY()-2))
            {
                currentHead.y = 1;
            }
            break;
    }

    // after the move is made, check if player committed a self-collision -> if true, player loses and game over
    if(checkSelfCollision()) {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }

    objPos currentFood;
    mainGameMechsRef->getFoodPos(currentFood);

    //check if head collided with food, if so then generate new food and add segment to body and score
    if (currentHead.x==currentFood.x && currentHead.y==currentFood.y)
    {
        mainGameMechsRef->generateFood(playerPosList);
        playerPosList->insertHead(currentHead);
        mainGameMechsRef->incrementScore();
    }
    else
    {
        // new current head should be inserted to the head of the list
        playerPosList->insertHead(currentHead);
        //then, remove tail to move body 'forward'
        playerPosList->removeTail();
    }
}



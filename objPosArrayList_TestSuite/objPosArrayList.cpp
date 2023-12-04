#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; // 200 elements on heap
    listSize = 0; // no valid element in list upon start up
    arrayCapacity = ARRAY_MAX_CAP; // array capacity should be max

}

objPosArrayList::~objPosArrayList()
{
    delete[] aList; //call destructor of all instances in array
}

int objPosArrayList::getSize()
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{

    if(listSize == arrayCapacity) // checking if listSize is at capacity
    {
        return;
    }

    for(int i = listSize; i > 0; i--)
    {
        aList[i].setObjPos(aList[i-1]); // object position for previous element; shuffle all elements towards tail
    }

    aList[0].setObjPos(thisPos); //overrides first element with incoming element

    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
   if(listSize == arrayCapacity) // checking if listSize is at capacity
    {
        return;
    }


    //shuffling is not required since element is being added to end, previous elements remain unchanged
    aList[listSize].setObjPos(thisPos); // adds tail element 

    listSize++;
}

void objPosArrayList::removeHead()
{
    if(listSize <= 0)
    {
        return;
    }

    for(int i = 0; i < listSize - 1; i++)
    {
        aList[i].setObjPos(aList[i+1]); // shuffles all elements towards the head, which removes the current head element
    }

    listSize--; // listSize decreases since head element is removed

}

void objPosArrayList::removeTail()
{
    if(listSize <= 0)
    {
        return;
    }
    
    listSize--; //decreases size of list, removing the tail element
    
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[listSize - 1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if(index >= 0 && index < listSize) //checking if index is within bounds
    {
        returnPos.setObjPos(aList[index]);
    }

}

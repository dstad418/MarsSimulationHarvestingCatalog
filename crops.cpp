#include <string.h>
#include "crops.h"

//  CONSTRUCTORS, DESTRUCTORS, AND WHERE OVERLOADED OPERATORS WOULD NORMALLY GO.
crop::crop() : planterNum(0), cropType(NULL), next(nullptr)
{
}
       
crop::crop(int boxNum, char* cropName) : planterNum(boxNum), cropType(nullptr), next(nullptr)
{
    setCropName(cropName);
}

crop::~crop()
{
    planterNum = 0;
    delete [] cropType;
    cropType = nullptr;
    next = nullptr;
}

//  SETTERS FOR POINTER DATA MEMBERS
void crop::setNext(crop* ptrToNext)
{
    next = ptrToNext;
}       

//  GETTERS FOR POINTER DATA MEMBERS
crop* crop::getNext() const
{
    return next;
}

//  GETTERS FOR DATA MEMBER VARIABLES   
int crop::getPlanterNum() const
{
    return planterNum;
}

char* crop::getCropType() const
{
    return cropType;         
}
/*
void crop::getCropType(char* cropToCopy) const
{
    strcpy(cropToCopy, this->cropType);
}
*/

//  SETTERS FOR DATA MEMBER VARIABLES
void crop::setCropName(char* namePtr)
{
    this->cropType = new char[strlen(namePtr + 1)];
    strcpy(this->cropType, namePtr);        
}

#ifndef _BST_
#define _BST_

#include "binaryTree.h"
#include "crops.h"
#include "struct.h"
#include "string.h"
#include <iostream>

using namespace std;


/*
TO DO: 

    planter
    |
    V
    plantermgr
        BST Data member
    |
    V
    BST
        Array of 2^h-1 NODES in a BST format
            Initial memory cost, but PRUNE will be much faster with no shifting, and harvest will 
            only have a few comparisons to make per node, depending on how many boxes are added.
        NODE = itemType + int value to match w/ hashmap value + internal pointers?
        Hashmap to determine position in BST
        Handles collision as LL chaining
            boxNum % 1000 

    /\
    |
    Crops
*/




/*
 *
 *          PRIVATE/PROTECTED MEMBER VARIABLE IMPLEMENTATION
 *
*/


// Initializing the tree- as mentioned before it's HUGE, but I wanted to go for speed since 
// almost half of my grade depending on it.
node* BST::initializeTree(int start, int end)
{
    if(start > end)
    {
        return nullptr;        
    }
    
    int middle = ((start + end) /2);

    node* ptr = new node(middle);

    ptr->leftChild = initializeTree(start, middle-1); 
    ptr->rightChild = initializeTree(middle+1, end);

    return ptr;
}

//recursive delete
void BST::clearTree(node* getRidOfThisTree)
{
    if(getRidOfThisTree != nullptr)
    {
        clearTree(getRidOfThisTree->leftChild);       
        clearTree(getRidOfThisTree->rightChild);
        delete getRidOfThisTree;
    }    
}

// recursive call to add
void BST::balancedAdd(int key, crop* crops, node* ptr)
{   
    if(key == ptr->key)
    {
        if(ptr->cropHead == nullptr)
        {
            ptr->cropHead = crops;
        }
        else
        {
            crops->setNext(ptr->cropHead);
            ptr->cropHead = crops;
        }
    }
    else if(key < ptr->key)
    {
        balancedAdd(key, crops, ptr->leftChild);        
    }
    else
    {
        balancedAdd(key, crops, ptr->rightChild);        
    }    
}


// The function that had me drawing diagrams and using the full surface of my whiteboard.
void BST::findRange(node* ptrToRoot, int startIndex, int stopIndex, char* cropType, int startKey, int stopKey, int treeHeight, int arr[], int& index)
{    
    bool sentinel = false;
           
    if(startKey <= ptrToRoot->key && ptrToRoot->key <= stopKey) // w/i range
    {
        crop* temp = ptrToRoot->cropHead;
        sentinel = true;
        while(temp)
        {
            if((strcmp(temp->getCropType(),cropType) == 0) && temp->getPlanterNum() >= startIndex && temp->getPlanterNum() <= stopIndex)
            {
             //   cout << temp->getPlanterNum() << " ";
                arr[index] = temp->getPlanterNum();
                index++;
            }  
            
            temp = temp->getNext();             
        }
    }
    // So much time into all the the variation that could have happened
    if((ptrToRoot->key > stopKey || sentinel == true) && treeHeight != twoHMinusOne) 
    {
        findRange(ptrToRoot->leftChild, startIndex, stopIndex, cropType, startKey, stopKey, treeHeight+1, arr, index);
    }
    if(((ptrToRoot->key < stopKey && ptrToRoot->key < startKey) || sentinel == true) && treeHeight != twoHMinusOne) 
    {
        findRange(ptrToRoot->rightChild, startIndex, stopIndex, cropType, startKey, stopKey, treeHeight+1, arr, index);
    }
}


void BST::removeValue(int delIndex, node* finder, int nodeKey, int currentLevel)
{
    if(finder->key == nodeKey && finder->cropHead != nullptr) // if we found it!
    {
        crop* unit = finder->cropHead;
        crop* prev = nullptr;

        if(finder->cropHead->getPlanterNum() == delIndex && unit->getNext() == nullptr)
        {
            delete unit;
            unit = nullptr;
            finder->cropHead = nullptr;        
        }
        else
        {
            while(unit)
            {
                prev = unit;
                unit = unit->getNext();
            
                if(unit->getPlanterNum() == delIndex)
                {
                    prev->setNext(unit->getNext());
                    delete unit;
                    unit = nullptr;
                    prev = nullptr;
                }
                else if(unit->getPlanterNum() == delIndex && unit->getNext() == nullptr)   
                {
                    delete unit;
                    unit = nullptr;
                    prev = nullptr;        
                }
            }
        }
    }
    else if(finder->key < nodeKey && currentLevel != twoHMinusOne) //if IT > us
    {
        removeValue(delIndex, finder->rightChild, nodeKey, currentLevel+1);        
    }
    else if(currentLevel != twoHMinusOne) // if IT < us
    {
        removeValue(delIndex, finder->leftChild, nodeKey, currentLevel+1);
    }
}


int BST::findKey(int boxNum)
{
    return (boxNum % maxTreeSize);        
}



/*
 *
 *          PUBLIC MEMBER VARIABLE IMPLEMENTATION
 *
*/



//*********************CONSTRUCTOR AND DRESTRUCTORS*******************************
BST::BST() 
{
    rootPtr = initializeTree(0, maxTreeSize);
}

BST::~BST()
{
    clearTree(rootPtr);
}
//********************************************************************************


//Insert OR Plant
void BST::addItem(int boxNum, char* cropName)
{    
    node* temp = rootPtr;

    crop* itemToAdd = new crop(boxNum, cropName);       
    balancedAdd(findKey(boxNum), itemToAdd, temp);

    temp = nullptr;
}


//Remove OR Prune
void BST::removeItem(int toRemove)
{   
    node* searchPtr = rootPtr;
    int removeKey = findKey(toRemove);
    int currentLevel = 1;
    removeValue(toRemove, searchPtr, removeKey, currentLevel);
}


//Harvest
void BST::harvest(char* name, int start, int stop)
{   // A lot went into this function, more than anything else
    node* search = rootPtr;
    int startKey = findKey(start);
    int stopKey = findKey(stop);
    int treeHeight = 1; 
    int array[100];
    int newArray[100];
    int index = 0;
    int tempNum = 0;

    // We know the height of a full BST is  2^h-1, ours is 2^13-1, so this value will have us from over-extending and constantly comparing PtrNext values;
    findRange(search, start, stop, name, startKey, stopKey, treeHeight, array, index);           
   
   
   // I spent so much time trying to get my traverse function to print in order, I gave up and did a fast
   // and inefficient sort... 
    for(int i = 0; i < index; i++)
    {
        for(int j = i+1; j < index; j++)
        {
            if(array[j] < array[i])
            {
                tempNum = array[i];
                array[i] = array[j];
                array[j] = tempNum;
            }     
        }
    }
    for(int k = 0; k < index; k++)
    {
        cout << array[k] << " ";
    }
}


#endif

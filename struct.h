#ifndef _STRUCT_
#define _STRUCT_

#include "crops.h"


struct node
{
    int key;
    crop* cropHead;
    node* leftChild;
    node* rightChild;
    node(int num): key(num), cropHead(nullptr), leftChild(nullptr), rightChild(nullptr){}
};

#endif

#ifndef _PLANTERMGR_
#define _PLANTERMGR_

#include "binaryTree.h"

class plantermgr
{
    private:
        BST binaryCrop;

    public:
        void plant(int boxNum, char* cropName);
        void harvest(char* cropName, int start, int stop);
        void prune(int boxNum);
};

#endif

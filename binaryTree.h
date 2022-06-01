#ifndef _BINARYTREE_
#define _BINARYTREE_

#include "crops.h"
#include "struct.h"

class BST
{
    private:
        //private variables
        const int maxTreeSize = 131071; 
            //(2^h - 1), to ensure a full BST + Prime Num
            //This seems brute-forcish, but since so many points were weighing on it being
            //blazing fast, I wanted a large tree w/ LL to handle collisions.
        const int twoHMinusOne = 17;
        node* rootPtr;

        //private function
        int findKey(int boxNum);


    protected:        
        node* initializeTree(int start, int end);
        // Deletes tree, requires ptr as parameter, so kept it protected
        void clearTree(node* getRidOfThisTree);
        void balancedAdd(int key, crop* crops, node* ptr);
        void findRange(node* ptrToRoot, int startIndex, int stopIndex, char* cropType, int startKey, int stopKey, int treeHeight, int arr[], int& index);
        void removeValue(int delIndex, node* finder, int nodeKey, int currentLevel);
  
    public:
        /*  Constructor, Destructor and Operator Overload Block */
        BST();
        ~BST();
        BST(const BST& otherTree) = delete;
        BST& operator=(const BST& otherTree) = delete;

        /*  Template function block */
        void addItem(int boxNum, char* cropName); //Plant
        void removeItem(int toRemove); //Prune
        void harvest(char* name, int start, int stop);

};


#endif

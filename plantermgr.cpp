#include "plantermgr.h"
#include <iostream>
#include "string.h"

using namespace std;

void plantermgr::plant(int boxNum, char* cropName)
{
    cout << "Planting " << cropName << " in box " << boxNum << endl;
    binaryCrop.addItem(boxNum, cropName);
}


void plantermgr::harvest(char* cropName, int start, int stop)
{
    cout << "Harvesting " << cropName << " from boxes " << start << " to " << stop << ". The following boxes will be harvested: "; // << strcmp(cropName, "hi");

    binaryCrop.harvest(cropName, start, stop);

    cout << endl << endl;
}


void plantermgr::prune(int boxNum)
{
    cout << "Pruning box number " << boxNum << "." << endl;
    binaryCrop.removeItem(boxNum);
}

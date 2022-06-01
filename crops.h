#ifndef _CROPS_
#define _CROPS_

class crop
{
    private:
        int planterNum;
        char* cropType;  
        crop* next;      
  
        // VARIABLE SETTER
        void setCropName(char* namePtr);
    
    public:
        //CONSTRUCTORS, DESTRUCTORS, ASSIGNMENT OVERLOAD
        crop();
        crop(int boxNum, char* cropName);
        ~crop();
        crop(const crop& otherCrop) = delete;
        crop& operator=(const crop& otherCrop) = delete;
       
        // POINTER SETTERS        
        void setNext(crop* ptrToNext);

        // POINTER GETTERS
        crop* getNext() const;
        
        //VARIABLE GETTERS
        int getPlanterNum() const;
        char* getCropType() const;
        //void getCropType(char* cropToCopy) const;
};


#endif

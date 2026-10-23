
#include <stdio.h>
#include <stdint.h>


struct BugTestStruct {

    uint8_t array00[256];
    uint8_t arrayff[256]; // bytes in this array shouldn't get printed
};


void printArray(const uint8_t* arrayToPrint, const size_t arraySize) {

    for (size_t i = 0; i < arraySize; i++) {
        printf("%02x ", arrayToPrint[i]);
    }

    printf("\n");
}


void copyTest(uint8_t* destination, const uint8_t* source, const uint8_t startIdx, const uint8_t howManyBytes) {

    for (uint8_t i = 0; i < howManyBytes; i++) {
        destination[i] = source[(uint8_t)(i + startIdx)];
    }
}


int main() {
    
    uint8_t copyDestination[25] = { 0 };
    

    // this struct is used so the prints show the 0xff bytes
    struct BugTestStruct bugTestStruct = { 0 };

    for (size_t i = 0; i < sizeof(bugTestStruct.arrayff); i++) {
        bugTestStruct.arrayff[i] = 0xff;
    }


    //
    // the prints should print all 00s,
    // but instead the ff bytes get copied into copyDestination unless compiler optimizations are disabled
    copyTest(copyDestination, bugTestStruct.array00, 246, sizeof(copyDestination));
    printArray(copyDestination, sizeof(copyDestination));

    copyTest(copyDestination, bugTestStruct.array00, 247, sizeof(copyDestination));
    printArray(copyDestination, sizeof(copyDestination));

    copyTest(copyDestination, bugTestStruct.array00, 248, sizeof(copyDestination));
    printArray(copyDestination, sizeof(copyDestination));

    copyTest(copyDestination, bugTestStruct.array00, 249, sizeof(copyDestination));
    printArray(copyDestination, sizeof(copyDestination));

    copyTest(copyDestination, bugTestStruct.array00, 250, sizeof(copyDestination));
    printArray(copyDestination, sizeof(copyDestination));

    copyTest(copyDestination, bugTestStruct.array00, 251, sizeof(copyDestination));
    printArray(copyDestination, sizeof(copyDestination));

    copyTest(copyDestination, bugTestStruct.array00, 252, sizeof(copyDestination));
    printArray(copyDestination, sizeof(copyDestination));

    copyTest(copyDestination, bugTestStruct.array00, 253, sizeof(copyDestination));
    printArray(copyDestination, sizeof(copyDestination));

    copyTest(copyDestination, bugTestStruct.array00, 254, sizeof(copyDestination));
    printArray(copyDestination, sizeof(copyDestination));

    copyTest(copyDestination, bugTestStruct.array00, 255, sizeof(copyDestination));
    printArray(copyDestination, sizeof(copyDestination));
    //


    return 0;
}

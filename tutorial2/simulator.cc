#include "tutorial2_CODE/definitions.h"
#include <fstream>
#include <iostream>

int main()
{
    allocateMem();
    std::cout << "Initialising" << std::endl;
    initialize();
    initializeSparse();

    std::cout << "Simulating" << std::endl;
    std::ofstream stream("spikes.csv");
    while(t < 1000.0f) {
        stepTime();
        pullExcCurrentSpikesFromDevice();
        pullInhCurrentSpikesFromDevice();

        for(unsigned int i = 0; i < getExcCurrentSpikeCount(); i++) {
            stream << t << ", " << getExcCurrentSpikes()[i] << std::endl;
        }

        for(unsigned int i = 0; i < getInhCurrentSpikeCount(); i++) {
            stream << t << ", " << 8000 + getInhCurrentSpikes()[i] << std::endl;
        }
    }

    return EXIT_SUCCESS;
}

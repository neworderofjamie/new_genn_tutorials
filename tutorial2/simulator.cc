#include "tutorial2_CODE/definitions.h"
#include <fstream>

int main()
{
    allocateMem();
    std::cout << "Initialising" << std::endl;
    initialize();
    inittutorial2();

    std::ofstream stream("spikes.csv");

    std::cout << "Simulating" << std::endl;
    // Advance time
    while(t < 1000.0f) {
#ifdef CPU_ONLY
        stepTimeCPU();
#else
        stepTimeGPU();
        pullExcCurrentSpikesFromDevice();
        pullInhCurrentSpikesFromDevice();
#endif

        for(unsigned int i = 0; i < spikeCount_Exc; i++) {
            stream << t << ", " << spike_Exc[i] << std::endl;
        }
        for(unsigned int i = 0; i < spikeCount_Inh; i++) {
            stream << t << ", " << 8000 + spike_Inh[i] << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
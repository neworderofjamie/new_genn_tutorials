#include "tutorial1_CODE/definitions.h"
#include <fstream>

int main()
{
    allocateMem();
    initialize();

    std::ofstream stream("state.csv");

    // Advance time
    while(t < 200.0f) {
#ifdef CPU_ONLY
        stepTimeCPU();
#else
        stepTimeGPU();
        pullNeuronStateFromDevice();
#endif
        stream << t << "," << VNeuron[0] << "," << UNeuron[0] << std::endl;
    }

    return EXIT_SUCCESS;
}
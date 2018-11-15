#include "tutorial1_CODE/definitions.h"
#include <fstream>

int main()
{
    allocateMem();
    initialize();


    aNeurons[0] = 0.02; bNeurons[0] = 0.2;  cNeurons[0] = -65.0;    dNeurons[0] = 8.0;  // RS
    aNeurons[1] = 0.1;  bNeurons[1] = 0.2;  cNeurons[1] = -65.0;    dNeurons[1] = 2.0;  // FS
    aNeurons[2] = 0.02; bNeurons[2] = 0.2;  cNeurons[2] = -50.0;    dNeurons[2] = 2.0;  // CH
    aNeurons[3] = 0.02; bNeurons[3] = 0.2;  cNeurons[3] = -55.0;    dNeurons[3] = 4.0;  // IB

    inittutorial1();

    std::ofstream stream("state.csv");

    // Advance time
    while(t < 200.0f) {
#ifdef CPU_ONLY
        stepTimeCPU();
#else
        stepTimeGPU();
        pullNeuronsStateFromDevice();
#endif
        stream << t << "," << VNeurons[0] << "," << VNeurons[1] << "," << VNeurons[2] << "," << VNeurons[3] << std::endl;
    }

    return EXIT_SUCCESS;
}
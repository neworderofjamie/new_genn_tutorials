// VA benchmark includes
#include "parameters.h"

// GeNN userprojects includes
#include "spikeRecorder.h"

// Auto-generated model code
#include "va_benchmark_CODE/definitions.h"

int main()
{
    allocateMem();
    initialize();
    initializeSparse();

    // Open CSV output files
    SpikeRecorder<> spikes(&getECurrentSpikes, &getECurrentSpikeCount, "spikes.csv", ",", true);

    // Loop through timesteps
    while(t < 10000.0f) {
        // Simulate
        stepTime();

        pullECurrentSpikesFromDevice();

        spikes.record(t);
    }

    return EXIT_SUCCESS;
}

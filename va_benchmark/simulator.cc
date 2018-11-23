// VA benchmark includes
#include "parameters.h"
#include "spike_csv_recorder.h"

// Auto-generated model code
#include "va_benchmark_CODE/definitions.h"

int main()
{
    allocateMem();
    initialize();
    initva_benchmark();

    // Open CSV output files
    SpikeCSVRecorder spikes("spikes.csv", glbSpkCntE, glbSpkE);

    // Loop through timesteps
    while(t < 10000.0f) {
        // Simulate
#ifndef CPU_ONLY
        stepTimeGPU();

        pullECurrentSpikesFromDevice();
#else
        stepTimeCPU();
#endif

        spikes.record(t);
    }

    return EXIT_SUCCESS;
}

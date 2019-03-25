// VA benchmark includes
#include "parameters.h"
#include "spike_csv_recorder.h"

// Auto-generated model code
#include "va_benchmark_CODE/definitions.h"

int main()
{
    allocateMem();
    initialize();
    initializeSparse();

    // Open CSV output files
    SpikeCSVRecorder spikes("spikes.csv", glbSpkCntE, glbSpkE);

    // Loop through timesteps
    while(t < 10000.0f) {
        // Simulate
        stepTime();

        pullECurrentSpikesFromDevice();

        spikes.record(t);
    }

    return EXIT_SUCCESS;
}

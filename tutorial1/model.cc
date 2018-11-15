#include "modelSpec.h"

void modelDefinition(NNmodel &model)
{
    initGeNN();
    model.setDT(0.1);
    model.setName("tutorial1");

    // Izhikevich model parameters
    NeuronModels::Izhikevich::ParamValues paramValues(
        0.02,           // 0 - A
        0.2,            // 1 - B
        -65.0,          // 2 - C
        8.0);           // 3 - D
    NeuronModels::Izhikevich::VarValues initValues(
        -65.0,          // 0 - V
        -20.0);         // 1 - U

    // Create population of Izhikevich neurons
    model.addNeuronPopulation<NeuronModels::Izhikevich>("Neuron", 1, paramValues, initValues);

    // DC current source parameters
    CurrentSourceModels::DC::ParamValues currentSourceParamVals(
        10.0);  // 0 - magnitude

    model.addCurrentSource<CurrentSourceModels::DC>("CurrentSource", "Neuron", currentSourceParamVals, {});

    model.finalize();
}
#include "modelSpec.h"

void modelDefinition(NNmodel &model)
{
    model.setDT(0.1);
    model.setName("tutorial1");

    // Izhikevich model parameters
    NeuronModels::IzhikevichVariable::ParamValues paramValues;
    NeuronModels::IzhikevichVariable::VarValues initValues(
        -65.0,                  // 0 - V
        -20.0,                  // 1 - U
        uninitialisedVar(),     // 2 - A
        uninitialisedVar(),     // 3 - B
        uninitialisedVar(),     // 4 - C
        uninitialisedVar());    // 5 - D
    model.addNeuronPopulation<NeuronModels::IzhikevichVariable>("Neurons", 4,
                                                                paramValues, initValues);

    // DC current source parameters
    CurrentSourceModels::DC::ParamValues currentSourceParamVals(
        10.0);  // 0 - magnitude

    model.addCurrentSource<CurrentSourceModels::DC>("CurrentSource", "Neurons",
                                                    currentSourceParamVals, {});
}

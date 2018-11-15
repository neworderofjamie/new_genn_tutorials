#include "modelSpec.h"

#include "../extra/lif.h"

void modelDefinition(NNmodel &model)
{
    GENN_PREFERENCES::autoInitSparseVars = true;
    initGeNN();
    model.setDT(1.0);
    model.setName("tutorial2");

    InitVarSnippet::Uniform::ParamValues vDist(
        -60.0,  // 0 - min
        -50.0);  // 1 - max

    // LIF model parameters
    LIF::ParamValues lifParams(
        1.0,    // 0 - C
        20.0,   // 1 - TauM
        -49.0,  // 2 - Vrest
        -60,  // 3 - Vreset
        -50.0, // 4 - Vthresh
        0.0,    // 5 - Ioffset
        5.0);    // 6 - TauRefrac

    // LIF initial conditions
    LIF::VarValues lifInit(
        initVar<InitVarSnippet::Uniform>(vDist),     // 0 - V
        0.0);   // 1 - RefracTime

    model.addNeuronPopulation<LIF>("Exc", 3200, lifParams, lifInit);
    model.addNeuronPopulation<LIF>("Inh", 800, lifParams, lifInit);

    WeightUpdateModels::StaticPulse::VarValues excSynInitValues(0.162); // 0 - g
    WeightUpdateModels::StaticPulse::VarValues inhSynInitValues(-0.9); // 0 - g

    InitSparseConnectivitySnippet::FixedProbability::ParamValues fixedProb(
        0.02); // 0 - prob

    model.addSynapsePopulation<WeightUpdateModels::StaticPulse, PostsynapticModels::DeltaCurr>(
        "Exc_Exc", SynapseMatrixType::RAGGED_GLOBALG, NO_DELAY,
        "Exc", "Exc",
        {}, excSynInitValues,
        {}, {},
        initConnectivity<InitSparseConnectivitySnippet::FixedProbabilityNoAutapse>(fixedProb));
    model.addSynapsePopulation<WeightUpdateModels::StaticPulse, PostsynapticModels::DeltaCurr>(
        "Exc_Inh", SynapseMatrixType::RAGGED_GLOBALG, NO_DELAY,
        "Exc", "Inh",
        {}, excSynInitValues,
        {}, {},
        initConnectivity<InitSparseConnectivitySnippet::FixedProbability>(fixedProb));
    model.addSynapsePopulation<WeightUpdateModels::StaticPulse, PostsynapticModels::DeltaCurr>(
        "Inh_Inh", SynapseMatrixType::RAGGED_GLOBALG, NO_DELAY,
        "Inh", "Inh",
        {}, inhSynInitValues,
        {}, {},
        initConnectivity<InitSparseConnectivitySnippet::FixedProbabilityNoAutapse>(fixedProb));
    model.addSynapsePopulation<WeightUpdateModels::StaticPulse, PostsynapticModels::DeltaCurr>(
        "Inh_Exc", SynapseMatrixType::RAGGED_GLOBALG, NO_DELAY,
        "Inh", "Exc",
        {}, inhSynInitValues,
        {}, {},
        initConnectivity<InitSparseConnectivitySnippet::FixedProbability>(fixedProb));

    model.finalize();
}
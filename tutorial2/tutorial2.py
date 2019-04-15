import numpy as np
import matplotlib.pyplot as plt
from pygenn import genn_wrapper, genn_model

model = genn_model.GeNNModel("float", "tutorial2_pygenn")
model.dT = 1.0

izk_params = {"a": 0.02, "b": 0.2, "c": -65.0, "d": 8.0}
izk_init = {"V": -65.0,
            "U": genn_model.init_var("Uniform", {"min": 0.0, "max": 20.0})}

stim_params = {"amp": 4.0}

exc_syn_init = {"g": 0.05}
inh_syn_init = {"g": -0.25}

fixed_prob = {"prob": 0.1}

exc = model.add_neuron_population("Exc", 8000, "Izhikevich", izk_params, izk_init)
inh = model.add_neuron_population("Inh", 2000, "Izhikevich", izk_params, izk_init)

model.add_current_source("ExcStim", "DC", "Exc", stim_params, {})
model.add_current_source("InhStim", "DC", "Inh", stim_params, {})

model.add_synapse_population("Exc_Exc", "SPARSE_GLOBALG", genn_wrapper.NO_DELAY,
    exc, exc,
    "StaticPulse", {}, exc_syn_init, {}, {},
    "DeltaCurr", {}, {},
    genn_model.init_connectivity("FixedProbabilityNoAutapse", fixed_prob))

model.add_synapse_population("Exc_Inh", "SPARSE_GLOBALG", genn_wrapper.NO_DELAY,
    exc, inh,
    "StaticPulse", {}, exc_syn_init, {}, {},
    "DeltaCurr", {}, {},
    genn_model.init_connectivity("FixedProbability", fixed_prob))

model.add_synapse_population("Inh_Inh", "SPARSE_GLOBALG", genn_wrapper.NO_DELAY,
    inh, inh,
    "StaticPulse", {}, inh_syn_init, {}, {},
    "DeltaCurr", {}, {},
    genn_model.init_connectivity("FixedProbabilityNoAutapse", fixed_prob))

model.add_synapse_population("Inh_Exc", "SPARSE_GLOBALG", genn_wrapper.NO_DELAY,
    inh, exc,
    "StaticPulse", {}, inh_syn_init, {}, {},
    "DeltaCurr", {}, {},
    genn_model.init_connectivity("FixedProbability", fixed_prob))

model.build()
model.load()

spike_ids = np.asarray([])
spike_times = np.asarray([])

while model.t < 1000.0:
    model.step_time()
    model.pull_current_spikes_from_device("Exc")
    model.pull_current_spikes_from_device("Inh")

    inh_t = np.ones(inh.current_spikes.shape) * model.t
    exc_t = np.ones(exc.current_spikes.shape) * model.t

    spike_ids = np.hstack((spike_ids, exc.current_spikes, inh.current_spikes + 8000))
    spike_times = np.hstack((spike_times, exc_t, inh_t))

# Create plot
fig, axes = plt.subplots(2)

# Compute histograms, dividing 1s simulation into 100 10ms bins
rate_hist, rate_bins = np.histogram(spike_times, bins=100)

# Convert histogram into Hz (spikes per 1000ms)
rate_hist = np.multiply(rate_hist, 1000.0 / 10.0, dtype=float)

# Convert histogram into average per neuron
rate_hist /= 10000.0

axes[0].scatter(spike_times, spike_ids, s=1)
axes[1].bar(rate_bins[:-1], rate_hist, 10.0)

axes[0].set_ylabel("Neuron number")
axes[1].set_xlabel("Time [ms]")
axes[1].set_ylabel("Average rate [Hz]")

# Show plot
plt.show()

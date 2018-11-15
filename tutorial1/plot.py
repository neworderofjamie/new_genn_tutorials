import matplotlib.pyplot as plt
import numpy as np

state = np.loadtxt("state.csv", delimiter=",")

# Create plot
figure, axes = plt.subplots(4, sharex=True)

# Plot voltages
for i, t in enumerate(["RS", "FS", "CH", "IB"]):
    axes[i].set_title(t)
    axes[i].set_ylabel("V [mV]")
    axes[i].plot(state[:,0], state[:,1 + i])

axes[-1].set_xlabel("Time [ms]")

# Show plot
plt.show()

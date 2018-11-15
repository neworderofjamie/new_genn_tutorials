import matplotlib.pyplot as plt
import numpy as np

state = np.loadtxt("spikes.csv", delimiter=",")

# Create plot
figure, axis = plt.subplots()

axis.scatter(state[:,0], state[:,1], s=1)
axis.set_xlabel("Time [ms]")

# Show plot
plt.show()

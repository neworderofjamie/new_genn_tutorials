import matplotlib.pyplot as plt
import numpy as np

state = np.loadtxt("state.csv", delimiter=",")

# Create plot
figure, axis = plt.subplots()

# Plot voltages
axis.plot(state[:,0], state[:,1], label="V")
axis.plot(state[:,0], state[:,2], label="U")
axis.legend()

# Show plot
plt.show()

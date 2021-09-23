import matplotlib.pyplot as plt

file = open("training.log", 'r')
lines = file.readlines()
data = [float(x) for x in lines]
plt.plot(data)
plt.xlabel("Game")
plt.ylabel("Loss")
plt.show()

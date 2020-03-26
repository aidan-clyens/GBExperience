import matplotlib.pyplot as plt
import numpy as np
import csv

expected_vals = []
vals = []

with open("../output/timing_analysis.csv", "r") as f:
    reader = csv.reader(f)

    for row in reader:
        expected_vals.append(int(row[0]))
        vals.append(int(row[1]))


print("Mean: ", np.mean(vals), "ns")
print("Max: ", np.max(vals), "ns")
print("Min: ", np.min(vals), "ns")


plt.title("Timing Analysis")
plt.plot(expected_vals, '-r')
plt.plot(vals, '-b')
plt.ylim([0, max(vals) / 2])
plt.xlim([0, len(vals)])
plt.xlabel("Iteration")
plt.ylabel("Cycle Time (ns)")
plt.grid()
plt.show()

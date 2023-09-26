#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np

points = np.loadtxt("points.txt", delimiter=",")

fig, ax = plt.subplots(subplot_kw=dict(projection="3d"))
ax.plot(*points.T, linewidth=0.5)
plt.show()

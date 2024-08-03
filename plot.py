#!/usr/bin/env python3

import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np

points = np.loadtxt("points.csv", delimiter=",", skiprows=1)

mpl.style.use("seaborn-v0_8-deep")

fig, ax = plt.subplots(subplot_kw=dict(projection="3d"))
fig.suptitle("Lorenz System", size="x-large")
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("z")
ax.set_xlim3d([min(points.T[0]), max(points.T[0])])
ax.set_ylim3d([min(points.T[1]), max(points.T[1])])
ax.set_zlim3d([min(points.T[2]), max(points.T[2])])

ax.plot(*points.T, linewidth=0.5)
ax.scatter(*points[0], label="Initial point")
ax.legend()

fig.tight_layout()

plt.show()

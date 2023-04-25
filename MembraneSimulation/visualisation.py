from pyqtgraph.Qt import QtCore, QtGui, QtWidgets
import pyqtgraph.opengl as gl
import pyqtgraph as pg
import numpy as np
import sys
import os

sample_frequency = 100
data_path = "Data\\"

files = [(os.path.join(data_path, f), int(f.split("_")[-1]) // sample_frequency) for f in os.listdir(data_path) if os.path.isfile(os.path.join(data_path, f)) and f.startswith("sim_step_")]

global frames
frames = list(range(len(files)))

sample_count = len(frames)

for i, (path, index) in enumerate(files):
    print(f"Loading: {i}/{sample_count}", end="\r")
    with open(path, "r") as f:
        frames[index] = [tuple((float(val) for val in line.split(","))) for line in f.read().split("\n") if line]

print(f"Done loading {sample_count} samples")

frames = np.array(frames)

global time
time = 0

app = QtWidgets.QApplication(sys.argv)
w = gl.GLViewWidget()
w.opts['distance'] = 40
w.setWindowTitle("Membrane-Simulation")
w.setGeometry(100, 100, 1920, 1080)
w.show()

scatters = []

for i in range(len(frames[0])):
    p = frames[time][i]
    scatters.append(gl.GLScatterPlotItem(
        pos = p,
        color = [1,1,1,1]
    ))
    w.addItem(scatters[i])

def update():
    global time
    global scatters
    time = time + 1
    if time >= sample_count:
        time = 0
    
    for i in range(len(frames[0])):
        scatters[i].setData(pos=frames[time][i])

timer = QtCore.QTimer()
timer.timeout.connect(update)
timer.start(10)

QtWidgets.QApplication.instance().exec_()

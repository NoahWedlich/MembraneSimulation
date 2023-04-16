import numpy as np
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.axes3d as p3
import matplotlib.animation as animation
import os

sample_frequency = 100
data_path = "Data\\"

files = [(os.path.join(data_path, f), int(f.split("_")[-1]) // sample_frequency) for f in os.listdir(data_path) if os.path.isfile(os.path.join(data_path, f)) and f.startswith("sim_step_")]

frames = list(range(len(files)))

sample_count = len(frames)

i = 1
for (path, index) in files:
    print(f"Loading: {i}/{sample_count}", end="\r")
    i = i + 1
    with open(path, "r") as f:
        frames[index] = [tuple((float(val) for val in line.split(","))) for line in f.read().split("\n") if line]

print(f"Done loading {sample_count} samples")

frames = np.array(frames)

print(frames.shape)

def animate(iteration, data, scatters):
    for i in range(data.shape[1]):
        scatters[i]._offsets3d = (data[iteration,i,0:1], data[iteration,i,1:2], data[iteration,i,2:3])
    return scatters

fig = plt.figure()
ax = p3.Axes3D(fig)

scatters = [ax.scatter(frames[0,i,0:1], frames[0,i,1:2], frames[0,i,2:3]) for i in range(frames.shape[1])]

ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")
ax.set_zlim3d([-50,50])

ax.set_title(f"Simulation Visualisation with {sample_count} samples")

ani = animation.FuncAnimation(fig, animate, sample_count, fargs=(frames, scatters), interval=50, blit=False, repeat=True)

print("Rendering")

def render_progress(current_frame, total_frames):
    print(f"Rendering: {current_frame}/{total_frames}", end="\r")

Writer = animation.writers["ffmpeg"]
writer = Writer(fps=10, bitrate=1800, extra_args=['-vcodec', 'libx264'])
ani.save("simulation_visualisation_3.mp4", writer=writer, progress_callback=render_progress)

print("\nDone Rendering!")

# plt.show()

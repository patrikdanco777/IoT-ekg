import serial
import matplotlib.pyplot as plt
from collections import deque

ser = serial.Serial('COM14', 115200)  # ZMEŇ COM port
buffer = deque(maxlen=2500)

plt.ion()
fig, ax = plt.subplots()
line, = ax.plot([], [], lw=1)
ax.set_ylim(-1000, 1000)
ax.set_xlim(0, 2500)
ax.set_title("EKG")
ax.set_xlabel("čas")
ax.set_ylabel("amplitúda")

while True:
    try:
        data = ser.readline().decode().strip()
        ekg, bpm = data.split(",")
        buffer.append(float(ekg))

        line.set_ydata(buffer)
        line.set_xdata(range(len(buffer)))
        ax.set_title(f"EKG  |  BPM: {bpm}")
        plt.pause(0.001)

    except:
        pass

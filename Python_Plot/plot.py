import pandas as pd
import matplotlib.pyplot as plt

file_path = r"output/output1.csv"

data = pd.read_csv(file_path)

print(data.columns)

# Plot each altitude vs timestamp
plt.figure()

plt.plot(data["timestamp"], data["gps_altitude"], label="GPS Altitude")
plt.plot(data["timestamp"], data["altimeter_1_altitude"], label="Altimeter 1")
plt.plot(data["timestamp"], data["altimeter_2_altitude"], label="Altimeter 2")
plt.plot(data["timestamp"], data["estimatedHeight"], label="Estimated Height")

# Labels and title
plt.xlabel("Timestamp")
plt.ylabel("Altitude")
plt.title("Altitude Comparison")
plt.legend()
plt.grid()

plt.show()


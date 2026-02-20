# import pandas as pd
# import matplotlib.pyplot as plt

# file_path = r"Given_Data/log1.csv"

# data = pd.read_csv(file_path)

# print(data.columns)

# # Plot each altitude vs timestamp
# plt.figure()

# plt.plot(data["timestamp"], data["gps_altitude"], label="GPS Altitude")
# plt.plot(data["timestamp"], data["altimeter_1_altitude"], label="Altimeter 1")
# plt.plot(data["timestamp"], data["altimeter_2_altitude"], label="Altimeter 2")

# # Labels and title
# plt.xlabel("Timestamp")
# plt.ylabel("Altitude")
# plt.title("Altitude Comparison")
# plt.legend()
# plt.grid()

# plt.show()

import pandas as pd
import matplotlib.pyplot as plt

# >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
# EDIT THESE TWO LINES WITH YOUR FILE PATHS
raw_file = "Given_Data/log1.csv"
est_file = "Given_Data/output_estimated.csv"
# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

# Load CSVs
raw = pd.read_csv(raw_file)
est = pd.read_csv(est_file)

# Merge on timestamp
df = pd.merge(raw, est, on="timestamp", suffixes=("_raw", "_est"))

# Create figure
plt.figure(figsize=(14, 8))

# Raw altimeters
plt.plot(df["timestamp"], df["altimeter_1_altitude_raw"], label="Altimeter 1 (raw)", alpha=0.6)
plt.plot(df["timestamp"], df["altimeter_2_altitude_raw"], label="Altimeter 2 (raw)", alpha=0.6)

# Raw GPS altitude
plt.plot(df["timestamp"], df["gps_altitude_raw"], label="GPS Altitude (MSL)", alpha=0.6)

# Estimated AGL
plt.plot(df["timestamp"], df["agl_est"], label="Estimated AGL", linewidth=2.5, color="black")

plt.title("Aircraft Altitude Measurements and Estimated AGL")
plt.xlabel("Timestamp (0.01s increments)")
plt.ylabel("Altitude (meters)")
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()
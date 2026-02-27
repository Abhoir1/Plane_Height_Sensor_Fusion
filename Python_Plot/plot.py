import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# ── Load data ──────────────────────────────────────────────────────────────────
file_path = r"output/output2.csv"
data = pd.read_csv(file_path)

fig, axes = plt.subplots(2, 1, figsize=(16, 14))

# ── Plot 1: Full overview - Raw vs Estimated ───────────────────────────────────
axes[0].plot(data["timestamp"], data["altimeter_1_altitude"], 
             alpha=0.4, linewidth=0.5, label="Altimeter 1", color="steelblue")
axes[0].plot(data["timestamp"], data["altimeter_2_altitude"], 
             alpha=0.4, linewidth=0.5, label="Altimeter 2", color="orange")
axes[0].plot(data["timestamp"], data["estimatedHeight"], 
             linewidth=1.2, label="Estimated Height", color="green")
axes[0].set_title("Raw Altimeter Readings vs Estimated Height", fontsize=13)
axes[0].set_ylabel("Height AGL (m)")
axes[0].legend()
axes[0].grid(True, alpha=0.3)


# ── Plot 2: Zoomed into spike region ──────────────────────────────────────────
# Find first region where altimeter spikes above a threshold
# threshold = data["estimatedHeight"].max() * 2  # spikes are typically much higher than estimated
# spike_candidates = data[data["altimeter_1_altitude"] > threshold]

# if not spike_candidates.empty:
spike_start = 90
spike_end   = 500


zoomed = data[(data["timestamp"] >= spike_start) & (data["timestamp"] <= spike_end)]
axes[1].plot(zoomed["timestamp"], zoomed["altimeter_1_altitude"], 
             alpha=0.5, linewidth=0.8, label="Altimeter 1", color="steelblue")
axes[1].plot(zoomed["timestamp"], zoomed["altimeter_2_altitude"], 
             alpha=0.5, linewidth=0.8, label="Altimeter 2", color="orange")
axes[1].plot(zoomed["timestamp"], zoomed["estimatedHeight"], 
             linewidth=1.5, label="Estimated Height", color="green")
axes[1].set_title("Zoomed - Spike Rejection Detail", fontsize=13)
axes[1].set_ylabel("Height AGL (m)")
axes[1].legend()
axes[1].grid(True, alpha=0.3)


# ── Save and show ──────────────────────────────────────────────────────────────
plt.tight_layout()
plt.subplots_adjust(hspace=0.2)  # do this AFTER all plotting, BEFORE savefig/show

plt.savefig("plots/log2_analysis.png", dpi=150)
plt.show()
print("Plot saved to plots/log2_analysis.png")
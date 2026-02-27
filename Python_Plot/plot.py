import pandas as pd
import matplotlib.pyplot as plt

# ── Load data ──────────────────────────────────────────────────────────────────
file_path = r"output/output1.csv"
data = pd.read_csv(file_path)

fig, axes = plt.subplots(2, 1, figsize=(16, 16))
plt.subplots_adjust(hspace=0.4)

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

# ── Plot 2: Zoomed into specific timestamp range ───────────────────────────────
spike_start = 6000
spike_end   = 9000

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
# plt.savefig("plots/log1_analysis.png", dpi=150, bbox_inches="tight")
plt.show()
print("Plot saved to plots/log1_analysis.png")
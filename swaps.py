# -----------------------------
# Visualise timings stored by xor_vs_regular_swap.cpp

import pandas as pd
import matplotlib.pyplot as plt
import pathlib

csv_path = pathlib.Path("swap_results.csv")
if not csv_path.exists():
    raise FileNotFoundError("swap_results.csv not found – run swap_bench first!")

df = pd.read_csv(csv_path)
print(df.tail())        # peek at the most recent entries

# Bar chart – last run by default
row = df.iloc[-1]
methods = ["Temp-var", "XOR"]
times   = [row["temp_seconds"], row["xor_seconds"]]

plt.figure()
plt.bar(methods, times)
plt.title(f"Swap benchmark ({int(row['swaps']):,} swaps)")
plt.ylabel("Time [seconds]")
plt.text(0.5, max(times)*0.9, f"XOR / Temp = {row['ratio']:.2f}×",
         ha="center")
plt.tight_layout()
plt.savefig("swap_benchmark.png")
plt.show()

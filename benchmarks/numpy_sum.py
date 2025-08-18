import numpy as np

input_path = "/home/saddy/code/GitHub/Igris/data/large_random_data.csv"
output_path = "output.csv"

# Load only first 2 columns (col_1 and col_2), skip header for numeric load
data = np.loadtxt(input_path, delimiter=",", skiprows=1, usecols=(0, 1))

# Sum the two columns
col_sum = data[:, 0] + data[:, 1]

# Load full CSV as strings to preserve all columns
with open(input_path, "r") as f:
    header = f.readline().strip()
    rest = f.read().splitlines()

# Split each row into a list
rows = [r.split(",") for r in rest]

# Append col_sum to each row
for i, s in enumerate(col_sum):
    rows[i].append(str(s))

# Write to file
with open(output_path, "w") as f:
    f.write(header + ",col_sum\n")
    for r in rows:
        f.write(",".join(r) + "\n")

print("CSV processed and saved successfully.")


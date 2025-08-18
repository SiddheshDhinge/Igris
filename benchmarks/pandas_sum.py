import pandas as pd

# Read CSV into DataFrame
df = pd.read_csv("/home/saddy/code/GitHub/Igris/data/large_random_data.csv")  # Replace with your input CSV path

# Create 'col_sum' as sum of col_1 and col_2
df["col_sum"] = df["col_1"] + df["col_2"]

# Save DataFrame back to CSV
df.to_csv("output.csv", index=False)  # Replace with desired output path

print("CSV processed and saved successfully.")


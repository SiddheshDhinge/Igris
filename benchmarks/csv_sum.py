import csv

input_path = "/home/saddy/code/GitHub/Igris/data/large_random_data.csv"   # Change to your CSV file path
output_path = "output.csv" # Change to desired output file path

with open(input_path, newline='') as infile, open(output_path, 'w', newline='') as outfile:
    reader = csv.DictReader(infile)
    fieldnames = reader.fieldnames + ["col_sum"]

    writer = csv.DictWriter(outfile, fieldnames=fieldnames)
    writer.writeheader()

    for row in reader:
        try:
            col1 = float(row["col_1"])
            col2 = float(row["col_2"])
        except ValueError:
            col1 = col2 = 0.0  # Handle non-numeric gracefully

        row["col_sum"] = col1 + col2
        writer.writerow(row)

print("CSV processed and saved successfully.")


import pyarrow.csv as pv
import pyarrow.compute as pc
import pyarrow as pa
import pyarrow.csv as csv
import pyarrow.feather as feather

# Read CSV into Arrow Table
table = pv.read_csv("/home/saddy/code/GitHub/Igris/data/large_random_data.csv")

# Add col_sum
col_sum = pc.add(table["col_1"], table["col_2"])
table = table.append_column("col_sum", col_sum)

# Write back to CSV
csv.write_csv(table, "output.csv")


import polars as pl

df = pl.read_csv("/home/saddy/code/GitHub/Igris/data/large_random_data.csv")  # Very fast Rust-based CSV parser
df = df.with_columns((pl.col("col_1") + pl.col("col_2")).alias("col_sum"))
df.write_csv("output.csv")


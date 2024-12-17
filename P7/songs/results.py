import sqlite3

# Connect to the SQLite database
db_file = "songs.db"
output_file = "results.txt"
sql_files = [f"{i}.sql" for i in range(1, 9)]  # List of SQL file names

# Function to execute a SQL file and log the results
def execute_sql_file(db_conn, sql_file):
    try:
        with open(sql_file, 'r') as file:
            # Read all lines, skipping comments (lines starting with "--")
            lines = file.readlines()
            sql_queries = "".join(line for line in lines if not line.strip().startswith("--"))

        # Execute each query in the file
        cursor = db_conn.cursor()

        # Fetch results for SELECT queries
        results = []
        for query in sql_queries.split(';'):
            query = query.strip()
            if query:  # Skip empty queries from splitting
                if query.lower().startswith("select"):
                    cursor.execute(query)
                    results.append(cursor.fetchall())
                else:
                    cursor.execute(query)  # For non-SELECT queries
        db_conn.commit()

        # Return the SQL queries and their results
        return sql_queries, results

    except Exception as e:
        return str(e), None  # Log errors if any occur

# Main function to process all SQL files
def main():
    with sqlite3.connect(db_file) as conn, open(output_file, 'w') as output:
        for sql_file in sql_files:
            output.write(f"SQL File: {sql_file}\n")
            try:
                queries, results = execute_sql_file(conn, sql_file)
                output.write(f"SQL Queries:\n{queries}\n")
                if results:
                    output.write("Execution Results:\n")
                    for result in results:
                        if result:  # Check if results are not empty
                            for row in result:
                                output.write(f"{row}\n")
                        else:
                            output.write("No data returned by this query.\n")
                else:
                    output.write("No results or non-SELECT queries executed.\n")
            except Exception as e:
                output.write(f"Error executing {sql_file}: {e}\n")
            output.write("\n" + "-"*50 + "\n\n")  # Separator between SQL files

if __name__ == "__main__":
    main()

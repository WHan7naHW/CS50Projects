# [Movies](https://cs50.harvard.edu/x/2024/psets/7/movies/)

## Problem to Solve

Provided to you is a file called movies.db, a SQLite database that stores data from IMDb about movies, the people who directed and starred in them, and their ratings. Write SQL queries to answer questions about this database of movies.

## Test
1. To test your queries in VS Code, you can query the database by running

    ```$ cat 1.sql | sqlite3 movies.db > output.txt```
  
    to redirect the output of the query to a text file called output.txt.

2. Check how many rows are returned by your query

    ```$ wc -l output.txt```
    
    It shows ```10280 output.txt``` meaning that exclude 4 lines of title and form edges, there are 10,276 rows in total.

3. Or directly show the result by running

    ```$ cat 2.sql | sqlite3 movies.db```

    in which case it will show
    
    ```
    +-------+
    | birth |
    +-------+
    | 1988  |
    +-------+
    ```

4. A single ```>``` will create or overwrite the file. Use the same command with ```>>``` to append to the file.

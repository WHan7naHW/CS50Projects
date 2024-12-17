# [Movies](https://cs50.harvard.edu/x/2024/psets/7/movies/)


## Usage
1. To test your queries in VS Code, you can query the database by running

    ```$ cat 1.sql | sqlite3 movies.db > output.txt```
  
    to redirect the output of the query to a text file called output.txt. 

2. Check how many rows are returned by your query

    ```$ wc -l output.txt```
    
    It shows ```10280 output.txt``` meaning that exclude 4 lines of title and form edges, there are 10,276 rows in total.

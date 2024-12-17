import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Missing command-line argument. Usage: python dna.py *.csv *.txt")
        sys.exit()

    # Read database file into a variable
    database_rows = []
    with open(sys.argv[1]) as file_csv:
        database = csv.DictReader(file_csv)
        for row in database:
            database_rows.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as file_txt:
        sequence = file_txt.read()

    # Find longest match of each STR in DNA sequence
    STR = []
    for subsequence in database.fieldnames:
        if subsequence != "name":
            STR.append(longest_match(sequence, subsequence))

    # Check database for matching profiles
    for person in database_rows:
        # extract STR values from database rows
        database_STR = [int(person[field]) for field in database.fieldnames[1:]]

        # compare STR in the database with target STR
        if database_STR == STR:
            print(person["name"])
            break

    else:
        # If the STR counts do not match exactly with any of the individuals in the CSV file
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()

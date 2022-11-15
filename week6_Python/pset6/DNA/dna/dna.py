import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt\n")

    # Read database file into a variable
    database = []

    file = sys.argv[1]

    with open(file, "r") as f:
        reader = csv.DictReader(f)
        for row in reader:
            database.append(row)

    # Read DNA sequence file into a variable

    text = sys.argv[2]

    with open(text, "r") as person:
        reader = csv.reader(person)
        for row in reader:
            dna_sequence = str(row)

    # Find longest match of each STR in DNA sequence

    # form a dictionary of nucleotides based on the database fields
    molecules = {}

    for k in database[0]:
        molecules[k] = 0
    del molecules['name']

    # molecules dict will keep count for each STR - longest sequence
    # molecules = {'AGATC': 0, 'TTTTTTCT': 0, 'AATG': 0, 'TCTAG': 0, 'GATA': 0, 'TATC': 0, 'GAAA': 0, 'TCTG': 0}

    for key in molecules:
        molecules[key] = str(longest_match(dna_sequence, key))


    # Check database for matching profiles

    print(search_person_all(molecules, database))

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

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


# check only for one person of the database if it matches with the given DNA sequence

def match_by_person(molecules, person):

    for k, v in molecules.items():
        if v != person[k]:
            return False

    return True


# loop through each row (person) to check if there is a match

def search_person_all(molecules, database):

    l = len(database)

    for i in range(l):
        if match_by_person(molecules, database[i]):
            return database[i]['name']

    return 'No match'


main()

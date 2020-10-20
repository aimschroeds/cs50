import sys, csv

# Check if DNA sequence's STR repeat sequences is in database provided


# Create dictionary for dna database
def create_dna_db(file):
    dna_csv = open(file)
    dna_reader = csv.DictReader(dna_csv)
    return dna_reader


# Get db headers to determine STR sequences to check for
def get_str_sequences(db):
    headers = db.fieldnames
    # Skip first item in array as this is 'name' field and not an STR sequence
    return headers[1:]


# Get sequence from txt file
def get_sequence(file):
    sequence_file = open(file, "r")
    sequence = sequence_file.read()
    return sequence


# Check number of times the sequence repeats consecutively
def sequence_repeats(sequence, str_strings):
    str_occurrences = {}
    for j in range(len(str_strings)):
        max_repeat = 0
        repeat = 0
        i = 0
        while (i < len(sequence)):
            _str_len = len(str_strings[j])
            if (str_strings[j] == sequence[i:i+_str_len]):
                repeat = repeat + 1
                i = i + _str_len
            else:
                if (repeat > max_repeat):
                    max_repeat = repeat
                repeat = 0
                i = i + 1
        # Check if latest repeating string is new max repeating string
        if (repeat > max_repeat):
            max_repeat = repeat
        str_occurrences[str_strings[j]] = max_repeat
    return str_occurrences


# Check to whom DNA belongs
def get_dna_owner(str_sequences, identifying_sequences, dna_db):
    for row in dna_db:
        j = 0
        match = False
        for j in range(len(str_sequences)):
            field = str_sequences[j]
            if (int(row[field]) == int(identifying_sequences[field])):
                match = True
                j = j + 1
                continue
            else:
                match = False
                break
        if (match == True):
            matched_person = row["name"]
            return matched_person
    return "No match"


if (len(sys.argv) != 3):
    print("Incorrect usage: python dna.py file.csv sequence.txt")
else:
    dna_db = create_dna_db(sys.argv[1])
    str_sequences = get_str_sequences(dna_db)
    sequence_string = get_sequence(sys.argv[2])
    identifying_sequences = sequence_repeats(sequence_string, str_sequences)
    identify_dna = get_dna_owner(str_sequences, identifying_sequences, dna_db)
    print(identify_dna)
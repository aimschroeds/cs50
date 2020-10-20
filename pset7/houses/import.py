# This will implement importing of Hogwarts students to a sqlite db from csv input via command line

import sys, csv, cs50


# Create dictionary for student info
def create_students_dict(file):
    students_csv = open(file)
    students_reader = csv.DictReader(students_csv)
    return students_reader, students_csv


# Open database
def open_db():
    db = cs50.SQL("sqlite:///students.db")
    return db


# Write student data to db
def write_students_to_db(stud_dict, db):
    for row in stud_dict:
        name_arr = row['name'].split()
        if len(name_arr) == 2:
            first_name = name_arr[0]
            middle_name = None
            last_name = name_arr[1]
        else:
            first_name = name_arr[0]
            middle_name = name_arr[1]
            last_name = name_arr[2]
        # Insert students
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first_name, middle_name, last_name, row['house'], row['birth'])


# If incorrect number of command lines arguments provided, exit
if (len(sys.argv) != 2):
    print("Incorrect usage: python import.py file.csv")
    sys.exit(1)
# Start running import process
else:
    students_dict = create_students_dict(sys.argv[1])
    db = open_db()
    write_students_to_db(students_dict[0], db)
    students_dict[1].close()
    sys.exit(0)
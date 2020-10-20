import sys
import cs50
# Print list of students for requested house


# Open sqlite db containing student info
def open_students_db():
    db = cs50.SQL("sqlite:///students.db")
    return db


# Query sqlite db for students from selected house
def get_student_data(house, db):
    rows = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", house)
    return rows


# Print list of students from selected house
def print_students(student_data):
    for row in student_data:
        if row['middle'] != None:
            name = " ".join([row['first'], row['middle'], row['last']])
        else:
            name = " ".join([row['first'], row['last']])
        print(name + ", born " + str(row['birth']))


# If incorrect number of command lines arguments provided, exit
if (len(sys.argv) != 2):
    print("Incorrect usage: python roster.py house")
    sys.exit(1)
# Start building roster
else:
    db = open_students_db()
    student_data = get_student_data(sys.argv[1], db)
    print_students(student_data)
    sys.exit(0)
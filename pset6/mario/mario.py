# Get height from user input
while True:
    height = input("Height: ")
    try:
        height = int(height)
    except:
        print("Please use a digit between 1 and 8.")
        continue
    if height < 1 or height > 8:
        print("Please use a digit between 1 and 8.")
        continue
    break


# Function to print spaces
def print_spaces(n):
    for space in range(n):
        print(" ", end='')


# Function to print blocks
def print_blocks(n):
    for block in range(n):
        print("#", end='')


# Loop over range from 1 - height to print each row of blocks
for i in range(1, height + 1):
    print_spaces(height - i)
    print_blocks(i)
    print_spaces(2)
    print_blocks(i)
    print("")
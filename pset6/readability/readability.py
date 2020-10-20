from cs50 import get_string

# Readability measure using Coleman-Liau index


# Get text input
def get_text():
    text = get_string("Text: ")
    return text


# Get word, letter and sentence count
def get_text_breakdown(text):
    word_count = 1;
    sentence_count = 0;
    letter_count = 0;
    for char in range(len(text)):
        c = text[char]
        if (c == " "):
            word_count = word_count + 1
        elif (c == '!' or c == '?' or c == '.'):
            sentence_count = sentence_count + 1
        else:
            letter_count = letter_count + 1
    counts_array = []
    counts_array.append(sentence_count)
    counts_array.append(letter_count)
    counts_array.append(word_count)
    return counts_array


# Get Coleman-Liau index value
# 0.0588 * L - 0.296 * S - 15.8,
# where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text
def get_coleman_liau(counts_array):
    sentence_count = counts_array[0]
    letter_count = counts_array[1]
    word_count = counts_array[2]
    L = (letter_count / word_count) * 100
    S = (sentence_count / word_count) * 100
    coleman_liau_index_val = int(0.0588 * L - 0.296 * S - 15.8)
    if (coleman_liau_index_val < 1):
        return "Before Grade 1"
    elif (coleman_liau_index_val > 15):
        return "Grade 16+"
    else:
        return "Grade " + str(coleman_liau_index_val)

print(get_coleman_liau(get_text_breakdown(get_text())))
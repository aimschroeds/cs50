from cs50 import get_string

# Credit card number validity checker


# Get credit card input
def get_credit_card():
    credit_card_number = get_string("What is your credit card number?\n")
    try:
        credit_card_number_int = int(credit_card_number)
        return credit_card_number
    except:
        return "INVALID"


# Check if Visa, MasterCard or Amex
def check_credit_card_company(first_2_chars, credit_card_len):
    # Check if Visa
    first_2_chars_int = int(first_2_chars)
    first_char_int = int(first_2_chars[0])
    second_char_int = int(first_2_chars[1])
    if (first_char_int == 4 and (credit_card_len == 13 or credit_card_len == 16)):
        return "VISA"
    elif ((first_2_chars_int == 34 or first_2_chars_int == 37) and credit_card_len == 15):
        return "AMEX"
    elif (first_char_int == 5 and (second_char_int > 0 and second_char_int < 6) and credit_card_len == 16):
        return "MASTERCARD"
    else:
        return "INVALID"


# Check if Luhn's Algorithm is met
def luhm_valid(cc_number_as_str):
    credit_card_len = len(cc_number_as_str)
    # Luhn 1 - Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
    i = -2
    luhn_1_product_digits = 0
    while (credit_card_len * -1) <= i:
        luhn_1_times_2 = int(cc_number_as_str[i]) * 2
        luhn_1_times_2_str = str(luhn_1_times_2)
        luhn_1_times_2_digits_summed = 0
        if (len(luhn_1_times_2_str) > 1):
            luhn_1_times_2_digits_summed = int(luhn_1_times_2_str[0]) + int(luhn_1_times_2_str[1])
        else:
            luhn_1_times_2_digits_summed = luhn_1_times_2
        luhn_1_product_digits = luhn_1_product_digits + luhn_1_times_2_digits_summed
        i = i - 2

    j = -1
    # Add the sum to the sum of the digits that weren’t multiplied by 2.
    luhn_2_sum_digits = luhn_1_product_digits
    while (credit_card_len * -1) <= j:
        luhn_2_sum_digits = luhn_2_sum_digits + int(cc_number_as_str[j])
        j = j - 2

    #If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
    if (luhn_2_sum_digits % 10 == 0):
        return check_credit_card_company(cc_number_as_str[:2], credit_card_len)
    else:
        return "INVALID"


credit_card = get_credit_card()
if(credit_card != "INVALID"):
    print(luhm_valid(credit_card))
else:
    print(credit_card)
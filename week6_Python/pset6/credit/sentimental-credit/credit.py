from cs50 import get_string, get_int
import re


def main():

    card = get_string("Enter card number: \n")

    # validate card based on type
    card_type = validate_type(card)

    # check if the first filter is passesed and calculate checksum, otherwise return
    if card_type == "INVALID":
        print("INVALID")
    elif (checksum(card) % 10 == 0):
        print(card_type)
    else:
        print("INVALID")


# validate card
def validate_type(card):
    if re.fullmatch("^34|37\d{13}$", card):
        return "AMEX"
    elif re.fullmatch("^5[1-5]\d{14}$", card):
        return "MASTERCARD"
    elif len(card) == 13 and re.fullmatch("^4\d{12}$", card):
        return "VISA"
    elif len(card) == 16 and re.fullmatch("^4\d{15}$", card):
        return "VISA"
    else:
        return "INVALID"


# compute checksum
def checksum(card):
    length = len(card)
    temp_card = list(card)

    for k in range(0, length):
        temp_card[k] = int(temp_card[k])

    suma_odd = 0

    # sum from digits of the card that must be * 2
    for i in range(length-2, -1, -2):
        if temp_card[i] * 2 > 9:
            sum_list = temp_card[i] * 2
            suma_odd = suma_odd + sum_list % 10 + sum_list // 10
        else:
            suma_odd = suma_odd + temp_card[i]*2

    suma_even = suma_odd

    # sum from digits only
    for j in range(length-1, -1, -2):
        suma_even = suma_even + temp_card[j]

    return suma_even


if __name__ == '__main__':
    main()

from cs50 import get_int


def checksum(n):
    # check if the card is valid with Luhn’s Algorithm
    sum = 0
    # get an array of reversed digits
    reverse = [int(d) for d in str(n)][::-1]

    for i, digit in enumerate(reverse):
        if i % 2 == 1:
            product = digit * 2
            sum += product // 10 + product % 10
        else:
            sum += digit

    return sum % 10 == 0


def checkserver(n):
    # check the card server
    digits = len(str(n))
    prefix = int(str(n)[:2])

    # AMEX
    if digits == 15 and prefix in {34, 37}:
        return "AMEX"
    # MASTERCARD
    elif digits == 16 and 51 <= prefix <= 55:
        return "MASTERCARD"
    # VISA
    elif digits in {13, 16} and 40 <= prefix <= 49:
        return "VISA"
    # INVALID
    return "INVALID"


def main():
    # prompt for a card number
    n = get_int("Number: ")

    # print the result
    if checksum(n):
        print(checkserver(n))
    else:
        print("INVALID")


if __name__ == "__main__":
    main()

from cs50 import get_int

while True:
    # get the pyramid's height
    n = get_int("Height: ")
    # positive integer between 1 and 8, inclusive
    if 0 < n <= 8:
        break

for i in range(1, n + 1):
    # left space
    space = " " * (n - i)
    # half pyramid
    hashtag = "#" * i
    # combine and print
    print(space + hashtag + "  " + hashtag)

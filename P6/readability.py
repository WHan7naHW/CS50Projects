from cs50 import get_string


def count_letters(text):
    # count the number of letters
    return sum(1 for char in text if char.isalpha())


def count_words(text):
    # count the number of words
    return len(text.split())


def count_sentences(text):
    # count the number of sentences
    return sum(1 for char in text if char in '.!?')


def cl_index(letters, words, sentences):
    # compute the index with Coleman-Liau formula
    # average number of letters per 100 words
    L = (letters / words) * 100
    # average number of sentences per 100 words
    S = (sentences / words) * 100
    # index = 0.0588 * L - 0.296 * S - 15.8
    return round(0.0588 * L - 0.296 * S - 15.8)


def main():
    # prompt user for text
    text = get_string("Text: ")

    # obtain counts
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # compute index
    index = cl_index(letters, words, sentences)

    # output answer of grade level
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


if __name__ == "__main__":
    main()

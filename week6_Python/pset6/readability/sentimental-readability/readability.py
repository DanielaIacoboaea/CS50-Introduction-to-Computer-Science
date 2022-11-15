from cs50 import get_string


# readability Coleman-Liau index:
# index = 0.0588 * L - 0.296 * S - 15.8

# 65 letters / 14 words avg of 464.29 letters per 100 words.
# 14 words ... 65 letters
# 100 words .... x letters
# x = 100 * 65 / 14 -> 464.28


def main():

    # get input from user
    text = get_string("Enter the paragraph:\n")

    # use a dictionary to keep the count for letters, words & sentences
    dict_count = {
        "letters": 0,
        "words": 0,
        "sentences": 0
    }

    # call separate functions to count l, s, w
    s_count = count_sentences(text)
    dict_count["sentences"] = s_count

    w_count = count_words(text)
    dict_count["words"] = w_count

    l_count = count_letters(text)
    dict_count["letters"] = l_count

    # calculate average no of letters/words
    avg_L = 100 * dict_count["letters"] / dict_count["words"]
    # calculate average no of sentences/words
    avg_S = 100 * dict_count["sentences"] / dict_count["words"]

    index = round(0.0588 * avg_L - 0.296 * avg_S - 15.8)
    print_grade(index)


def count_sentences(text):

    dot = text.count('.')
    exclamation = text.count('!')
    question = text.count('?')

    counter = dot + exclamation + question

    return counter


def count_words(text):

    words = text.split()
    count = len(words)

    return count


def count_letters(text):
    count = 0

    for character in text:
        if character.isalpha():
            count += 1

    return count


def print_grade(index):
    if index < 1:
        return print("Before Grade 1")
    elif index >= 16:
        return print("Grade 16+")
    else:
        return print("Grade", index)


if __name__ == '__main__':
    main()
from cs50 import get_string

text = get_string("Text: ")
letter_count = 0
digit_count = 0
special_count = 0
word_count = 1
sentence_count = 0

if text:
    for i in range(len(text)):
        if text[i].isalpha():
            letter_count += 1
        elif text[i].isnumeric():
            digit_count += 1
        elif text[i] in ["?", "!", "."]:
            sentence_count += 1
        elif text[i] == " " and text[i + 1]:
            word_count += 1
        else:
            special_count += 1

    average_letters = float(letter_count / word_count * 100)
    average_sentences = float(sentence_count / word_count * 100)

    # Calculate readability
    readability_index = round(0.0588 * average_letters - 0.296 * average_sentences - 15.8)

    if readability_index >= 16:
        print("Grade 16+")
    elif readability_index < 1:
        print("Before Grade 1")
    else:
        print("Grade", readability_index)

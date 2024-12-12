def get_h():
    while True:
        try:
            height = int(input("Height: "))

            if height > 0 and height < 9:
                return height

        except ValueError as error:
            print(error)


def print_h(height):

    for line in range(height):
        print(" " * (height - line - 1), end="")
        print("#" * (line + 1))


# Call the function
print_h(get_h())

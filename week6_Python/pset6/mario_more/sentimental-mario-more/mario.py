from cs50 import get_int


def main():
    # request height of the pyramid
    h = request_input()
    
    # print the pyramid
    print_pyramid(h)


# validate user input
def request_input():

    height = get_int("Enter pyramind height(1-8):\n")

    while height < 1 or height > 8:
        print("Try again!")
        height = get_int("Enter pyramind height(1-8):\n")

    return height


# print half pyramid based on height
def print_pyramid(height):
    for i in range(0, height):
        print(" "*(height-i-1), end="")
        print("#"*(i+1) + "  " + "#"*(i+1))


if __name__ == "__main__":
    main()

# COMP1021 Lab 2 Python Sketchbook
# Name:POON, Chun Yuen Alexander
# Student ID:20857904
# Email: cyapoon@connect.edu.hk

import turtle       # Import the turtle module for the program

turtle.width(4)
turtle.speed(10)

##### Initialize the colour
fillcolor = "black"
turtle.pencolor("black")
turtle.fillcolor(fillcolor)

print("Welcome to the Python Sketchbook!")

##### While loop to repeat the main menu

# Initialize the option to empty in order to enter the while loop
option = ""


while option != "q": # While the option is not "q"
    print()
    print("Please choose one of the following options:")
    print()
    print("m - Move the turtle")
    print("t - Rotate the turtle")
    print("l - Draw a line")
    print("r - Draw a rectangle")
    print("c - Draw a circle")
    print("p - Change the pen colour of the turtle")
    print("f - Change the fill colour of the turtle")
    print("g - Draw a generated flower")
    print("e - Draw a generated explosion")
    print("a - Draw the author's information")
    print("q - Quit the program")
    print()

    option = input("Please enter your option: ")

    ##### Handle the move option
    if option == "m":
        print()

        # Ask the user for the x and y value
        x = input("Please enter the x value: ")
        x = int(x)
        y = input("Please enter the y value: ")
        y = int(y)

        # Move the turtle without drawing anything
        turtle.up()
        turtle.goto(x, y)
        turtle.down()

    ##### Handle the rotate option
    if option == "t":
        print()

        # Ask the user for the angle of roration
        thisangle = input("Please enter the angle of rotation: ")
        thisangle = int(thisangle)

        #rotate the turtle
        turtle.left(thisangle)

    ##### Handle the line option
    if option == "l":
        print()

        # Ask the user for the x and y value
        x = input("Please enter the x value: ")
        x = int(x)
        y = input("Please enter the y value: ")
        y = int(y)

        # Move the turtle and draw a line
        turtle.goto(x, y)

    ##### Handle the rectangle option
    if option == "r":
        print()

        # Ask the user the width and the height of the rectangle
        width = input("Please enter the width of the rectangle: ")
        width = int(width)
        height = input("Please enter the height of the rectabgle: ")
        height = int(height)

        # Added to allow fill with fill colour
        turtle.begin_fill()
        
        turtle.forward(width)
        turtle.left(90)
        turtle.forward(height)
        turtle.left(90)
        turtle.forward(width)
        turtle.left(90)
        turtle.forward(height)
        turtle.left(90)

        #Added to allow fill with fill colour
        turtle.end_fill()
        

    ##### Handle the circle option
    if option == "c":
        print()

        # Ask the user for the radius of the circle
        radius = input("Please enter the radius of the circle: ")
        radius = int(radius)
        # Added to allow fill with fill colour
        turtle.begin_fill()
        
        turtle.circle(radius)

        # Added to allow fill with fill colour
        turtle.end_fill()

    ##### Handle the pen colour option
    if option == "p":
        print()

        # Ask for the pen color
        pencolor = input("Please enter a colour name for the pen colour: ")
        turtle.pencolor(pencolor)

    ##### Handle the fill colour option
    if option == "f":
        print()

        # Ask for the fill color
        fillcolor = input("Please enter a colour name for the fill colour: ")
        turtle.fillcolor(fillcolor)

    ##### Handle the generated flower option
    if option == "g":
        print()

        # Ask the user for the size of the flower petal
        size = input("Please enter the size of the flower petal: ")
        size = int(size)

        # Draw the generated flower
        # Outer loop: repeat 12 times for drawing 12 basic shapes
        for u in range(12):
            # Inner loop: repeat 3 times
            for v in range(3):
                turtle.forward(size)
                turtle.left(120)
            turtle.left(30)
            
    ##### Handle the generated explosion
    if option == "e":
        print()

        # Ask for the size of the explosion
        size = input("Please enter the size of the explosion(>150): ")
        size = int(size)

        for colour in ["MediumPurple1","MediumPurple2","MediumPurple3","MediumPurple4",\
                       "OrangeRed1","OrangeRed2","OrangeRed3","OrangeRed4",\
                       "gold1","gold2","gold3","gold4",\
                       "yellow1","yellow2","yellow3","yellow4"]:
            turtle.pencolor(colour)
            turtle.dot(size)
            size = size - 10

    ##### Handle the author's information
    if option == "a":

        # Draw the character "P"
        turtle.pencolor("red")
        turtle.up()
        turtle.goto(-100,0)
        turtle.left(90)
        turtle.down()
        turtle.forward(100)
        turtle.right(90)
        turtle.forward(50)
        turtle.right(90)
        turtle.forward(40)
        turtle.right(90)
        turtle.forward(50)

        # Draw the character "O"
        turtle.pencolor("brown")
        turtle.up()
        turtle.goto(0,100)
        turtle.down()
        turtle.left(90)
        turtle.forward(100)
        turtle.left(90)
        turtle.forward(50)
        turtle.left(90)
        turtle.forward(100)
        turtle.left(90)
        turtle.forward(50)


        # Draw the character "O"
        turtle.pencolor("gold")
        turtle.up()
        turtle.goto(100,100)
        turtle.down()
        turtle.left(90)
        turtle.forward(100)
        turtle.left(90)
        turtle.forward(50)
        turtle.left(90)
        turtle.forward(100)
        turtle.left(90)
        turtle.forward(50)

        # Draw the character "N"
        turtle.pencolor("yellow")
        turtle.up()
        turtle.goto(200,0)
        turtle.down()
        turtle.right(90)
        turtle.forward(100)
        turtle.right(150)
        turtle.forward(115)
        turtle.left(150)
        turtle.forward(100)
        

turtle.done()














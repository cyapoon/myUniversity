# Name:POON, Chun Yuen Alexander
# Student ID:20857904


import turtle

turtle.setup(800,600)    # Set the width and height be 800 x 600

number_of_divisions = 8  # The number of subdivisions around the centre
turtle_width = 3         # The width of the turtles

# Don't show the animation
turtle.tracer(False)

# Draw the background lines

backgroundLineTurtle = turtle.Turtle()

backgroundLineTurtle.width(1)

backgroundLineTurtle.down()
backgroundLineTurtle.color("gray84") # Draw the centered line
for i in range(number_of_divisions):
    backgroundLineTurtle.forward(500)
    backgroundLineTurtle.backward(500)
    backgroundLineTurtle.left(360 / number_of_divisions)

backgroundLineTurtle.up()

# Show the instructions
backgroundLineTurtle.color("purple")
backgroundLineTurtle.goto(-turtle.window_width()/2+50, 100)
backgroundLineTurtle.write("""s - change a colour for one of the colour buttons
m - all 8 drawing turtles go to middle
c - clear all drawings made by the 8 drawing turtles
""", font=("Arial", 14, "normal"))

backgroundLineTurtle.hideturtle()

# Set up a turtle for handling message on the turtle screen
textTurtle = turtle.Turtle()
# This sets the colour of the text to red
textTurtle.color("red")
# We do not want it to show/draw anything, except the message text
textTurtle.up() 
# Set it the be at center, near the colour selections
textTurtle.goto(0, -200)
# We do not want to show it on the screen
textTurtle.hideturtle()


# Part 2 Preparing the drawing turtles

# The drawing turtles are put in a list
allDrawingTurtles = [] 

# Part 2.1 Add the 8 turtles in the list
for i in range(number_of_divisions):
    newTurtle = turtle.Turtle()
    # Set-ups
    newTurtle.speed(0)
    newTurtle.width(turtle_width)
    newTurtle.hideturtle()
    
    allDrawingTurtles.append(newTurtle)
    
# Part 2.2 Set up the first turtle for drawing
dragTurtle = allDrawingTurtles[0]
dragTurtle.showturtle()
dragTurtle.shape("circle")
dragTurtle.shapesize(2,2)

# Part 3 Preparing the basic drawing system
# Set up the ondrag event
def draw(x, y):
    dragTurtle.ondrag(None)
    turtle.tracer(False)

    textTurtle.clear() # Added in Part 5.1 for clearing the message from textTurtle

    dragTurtle.goto(x, y)

    x_transform = [1, 1, -1, -1, 1, 1, -1, -1] # This represents + + - - + + - -
    y_transform = [1, -1, 1, -1, 1, -1, 1, -1] # This represents + - + - + - + -

    for i in range(1, number_of_divisions):
        if i < 4:
            new_x = x * x_transform[i]
            new_y = y * y_transform[i]

        else:
            new_x = y * y_transform[i]
            new_y = x * x_transform[i]

        allDrawingTurtles[i].goto(new_x,new_y)
    turtle.tracer(True)
    dragTurtle.ondrag(draw)

dragTurtle.ondrag(draw)

# Part 5.2 clear all drawings made by the 8 drawing turtles
def clearDrawing():    
    for cturtle in allDrawingTurtles:
        turtle.tracer(False)
        cturtle.clear()
        turtle.tracer(True)
    textTurtle.clear() # clear the previous message
    textTurtle.write("The screen is cleared", \
                       align="center", font=("Arial", 14, "normal"))
    

turtle.onkeypress(clearDrawing,"c")


# Part 5.3 all 8 drawing turtles go to middle
def goToMiddle():
    
    turtle.tracer(False)
    for mturtle in allDrawingTurtles:
        mturtle.up()
        mturtle.goto(0, 0)
        mturtle.down()
    turtle.tracer(True)
    textTurtle.clear() # clear the previous message
    textTurtle.write("All 8 drawing turtles returned to middle", \
                    align="center", font=("Arial", 14, "normal"))

turtle.onkeypress(goToMiddle,"m")


# Part 4 handling the colour selection
# Make the colour selection turtles
# Here is the list of colours
colours = ["black", "orange red", "lawn green", "medium purple", "light sky blue", "orchid", "gold"]

# Part 4.2 Set up the onclick event
def handleColourChange(x, y):
    if x <= -130:
        for thisturtle in allDrawingTurtles:
            thisturtle.color(colours[0])
    elif x <= -80:
        for thisturtle in allDrawingTurtles:
            thisturtle.color(colours[1])
    elif x <= -30:
        for thisturtle in allDrawingTurtles:
            thisturtle.color(colours[2])
    elif x <= 20:
        for thisturtle in allDrawingTurtles:
            thisturtle.color(colours[3])
    elif x <= 70:
        for thisturtle in allDrawingTurtles:
            thisturtle.color(colours[4])
    elif x <= 120:
        for thisturtle in allDrawingTurtles:
            thisturtle.color(colours[5])
    elif x <= 180:
        for thisturtle in allDrawingTurtles:
            thisturtle.color(colours[6])

# Part 5.4 change a colour in the colour selection
def changeColour():
    index = turtle.textinput("Please type the index number for the turtle:(0-6)",\
                            None)
    if index != None:
        index = int(index)
        while index not in range(0,7):
            index = turtle.textinput("The number is not between '0' and '7'. Please type a number(0-6) again", None)
            if int(index) in range(0,7):
                index = int(index)
                break
            
            
        
        cColor = turtle.textinput("Please type the color you want to use e.g. LightBlue2:", None)
        if cColor != None:
            colours[index] = cColor
        for i in range(len(colours)):
            turtle.tracer(False)
            t = turtle.Turtle()
            t.shape("square")
            t.shapesize(2,2)
            t.up()
            t.color(colours[i])
            t.goto(-150 + 50 * i, -250)
            t.onclick(handleColourChange)
            colourSelectionTurtles.append(t)
            textTurtle.clear() # clear the previous message
            textTurtle.write("The colour is set and can be used", \
                    align="center", font=("Arial", 14, "normal"))
        turtle.tracer(True)
    turtle.listen()

turtle.onkeypress(changeColour,"s")

# Part 4.1 Make the colour selection turtles
colourSelectionTurtles = []

for i in range(len(colours)):
    # 0,1,2,3,4,5,6
    t = turtle.Turtle()
    t.shape("square")
    t.shapesize(2,2)
    t.up()
    t.color(colours[i])
    t.goto(-150 + 50 * i, -250)
    t.onclick(handleColourChange)
    colourSelectionTurtles.append(t)


turtle.tracer(True)
turtle.listen()

turtle.done()


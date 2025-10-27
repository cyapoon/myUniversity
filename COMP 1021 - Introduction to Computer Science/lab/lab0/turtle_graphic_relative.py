import turtle
import random

# code for drawing rectangle relatively

random_x = random.randint(-300,300)
random_y = random.randint(-300,300)

turtle.up()
turtle.goto(random_x,random_y) # going to start position
turtle.down()

random_angle = random.randint(0,360)
turtle.left(random_angle) # or turtle.right(random_angle)

random_width = random.randint(50,150)
random_height = random.randint(50,150)
turtle.color("blue","yellow")
turtle.width(5)

turtle.begin_fill()
turtle.forward(random_width)
turtle.left(90)
turtle.forward(random_height)
turtle.left(90)
turtle.forward(random_width)
turtle.left(90)
turtle.forward(random_height)
turtle.left(90)
turtle.end_fill()
# Finish

turtle.done()

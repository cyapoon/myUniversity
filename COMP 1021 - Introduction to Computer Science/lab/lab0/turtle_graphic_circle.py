import turtle
import random

colors = ["Royal Blue","Pale Green","Gold","Rosy Brown","Coral","Orchid"]
# code for drawing circle relatively

num_of_loops = 0
while num_of_loops < 5:  #Run the loop of five times, i.e. 0,1,2,3,4
    random_x = random.randint(-300,300)
    random_y = random.randint(-300,300)

    turtle.up()
    turtle.goto(random_x,random_y) # going to start position
    turtle.down()


    random_radius = random.randint(50,100)
    random_color = random.choice(colors)
    random1_color = random.choice(colors)
    turtle.color(random1_color,random_color)
    turtle.width(5)

    turtle.begin_fill()
    turtle.circle(random_radius)
    turtle.end_fill()
    num_of_loops = num_of_loops + 1

# Finish
turtle.done()

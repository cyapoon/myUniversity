import turtle

# code for printing helloworld in the canvas, and draw rectangle
turtle.write("Hello World!") #print "Hello World" here

turtle.up()
turtle.goto(-100,50) # going to start position
turtle.down()

turtle.color("blue")
turtle.width(5)
turtle.goto(-100,-50)
turtle.goto(100,-50)
turtle.goto(100,50)
turtle.goto(-100,50) # Finish

turtle.done()

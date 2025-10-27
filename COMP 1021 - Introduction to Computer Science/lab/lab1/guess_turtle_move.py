import random                     #Import the "random" library
import turtle                     # Umport 'turtle' library

target = 0                        #We will store the number to be guessed here
finished = False                  #This is true if the game has finished
geuss_input_text = ""             #We will store text ihn here
guess_input = 0                   #We will store a number in here
count = 0
xposition = -100
yposition = 150

turtle.up()
#Generate a new integer random number
target = random.randint(1,100)
turtle.goto(xposition,yposition)
turtle.write("I am thinking of a number. What number am I thinking of?",font=
             ("Arial",40,"bold"))
yposition = yposition - 40

#Do the main game loop
while not finished:
    #Get the users' guess
    guess_input_text = turtle.textinput("Guessing Game",
                                        "Please enter a number between 1 and 100:")
    guess_input = int(guess_input_text)

    count = count + 1

    #check the users'guess
    if guess_input < 1 or guess_input > 100:
        turtle.goto(xposition,yposition)
        turtle.write("Please enter an integer between 1 and 100", font=("Arial",40,"bold"))
        yposition = yposition - 40
    elif guess_input > target:
        turtle.goto(xposition,yposition)
        turtle.write("Too large.",font=("Arial",40,"bold"))
        yposition = yposition - 40
    elif guess_input < target:
        turtle.goto(xposition,yposition)
        turtle.write("Too small.",font=("Arial",40,"bold"))
        yposition = yposition - 40
    else:
        finished = True

# At this point, the game is finished
turtle.goto(xposition,yposition)
turtle.write("You got it! My number is "+ str(target) +" .",font=("Arial",40,"bold"))
yposition = yposition - 40
turtle.goto(xposition,yposition)
turtle.write("It took you "+ str(count) +" guesses to get the number.",font=("Arial",40,"bold"))
yposition = yposition - 40
turtle.done()

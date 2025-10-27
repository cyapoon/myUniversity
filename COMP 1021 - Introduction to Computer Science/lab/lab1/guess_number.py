import random                     #Import the "random" library

target = 0                        #We will store the number to be guessed here
finished = False                  #This is true if the game has finished
geuss_input_text = ""             #We will store text ihn here
guess_input = 0                   #We will store a number in here
count = 0

#Generate a new integer random number
target = random.randint(1,100)
print("I am thinking of a number. What number am I thinking of?")

#Do the main game loop
while not finished:
    #Get the users' guess
    guess_input_text = input("Please enter a number between 1 and 100:")
    guess_input = int(guess_input_text)

    count = count + 1

    #check the users'guess
    if guess_input < 1 or guess_input > 100:
        print("Please enter an integer between 1 and 100")
    elif guess_input > target:
        print("Too large.")
    elif guess_input < target:
        print("Too small.")
    else:
        finished = True

# At this point, the game is finished
print("You got it! My number is", target,".")
print("It took you", count,"guesses to get the number.")

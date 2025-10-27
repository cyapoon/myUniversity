# COMP1021 Robot Game Lab
# Name       : POON, Chun Yuen Alexander
# Email      : cyapoon@connect.ust.hk
# Student ID : 20857904

# The following line imports the game function library and map into
#  this main program.
from game_lib import *

# This is the only 'memory' of the robot that you can use to store things
#
# You are expected to use it to store only a string, which indicates the
#  current 'state' of the robot.
currentStateForTask1 = "Go north"
currentStateForTask2 = "Go north"
currentStateForTask3 = "Go north"
currentStateForTask4 = "Go north"

# These functions helps the robot to make the decision about what it needs
#  to do in order to get to the exit of the map.
# 
#  The function should return one of the following:
#     "NORTH"    which means the robot decides to go north
#     "SOUTH"    which means the robot decides to go south
#     "EAST"     which means the robot decides to go east
#     "WEST"     which means the robot decides to go west
#     "NONE"     which means the robot decides to stay in the same place

# Your task is to help the robot to make a decision on what to do next
#
#  A collection of functions that you will find very useful are shown here:
#
#    northIsWall()    returns True if the robot detects that the north side is blocked, otherwise it returns False
#    southIsWall()    returns True if the robot detects that the south side is blocked, otherwise it returns False
#    eastIsWall()     returns True if the robot detects that the east side is blocked, otherwise it returns False
#    westIsWall()     returns True if the robot detects that the west side is blocked, otherwise it returns False
#


# This is the function for task 0
def makeDecisionForTask0():
    return "NORTH"

# This is the function for task 1
def makeDecisionForTask1():
    global currentStateForTask1
    
    # When the robot is in 'Go north' state...
    if currentStateForTask1 == "Go north":
        if northIsWall():
            currentStateForTask1 = "Go east"
            return "EAST"
        else:
            return "NORTH" # This gets extended with your logic
    # When the robot is in 'Go east' state...
    elif currentStateForTask1 == "Go east":
        if not northIsWall():
            return "NORTH"
        else:
            return "EAST"


# This is the function for task 2
def makeDecisionForTask2():
    global currentStateForTask2

    # When the robot is in 'Go north' state...
    if currentStateForTask2 == "Go north":
        if northIsWall():
            currentStateForTask2 = "Go east"
            return "EAST"
        else:
            return "NORTH"
    # When the robot is in 'Go east' state...
    elif currentStateForTask2 == "Go east":
        if not northIsWall():
            return "NORTH"
        elif eastIsWall():
            currentStateForTask2 = "Go west"
            return "WEST"
        else:
            return "EAST"


    # When the robot is in 'Go west' state...
    elif currentStateForTask2 == "Go west":
        if not northIsWall():
            return "NORTH"
        else:
            return "WEST"
    
            



# This is the function for task 3
def makeDecisionForTask3():
    global currentStateForTask3

   # When the robot is in 'Go north' state...
    if currentStateForTask3 == "Go north":
        if northIsWall():
            currentStateForTask3 = "Go east"
            return "EAST"
        else:
            return "NORTH"
    # When the robot is in 'Go east' state...
    elif currentStateForTask3 == "Go east":
        if not northIsWall():
            return "NORTH"
        elif not eastIsWall():
            return "EAST"
        else:
            currentStateForTask3 = "Go west"
            return "WEST"


    # When the robot is in 'Go west' state...
    elif currentStateForTask3 == "Go west":
        if not northIsWall():
            currentStateForTask3 = "Go north"
            return "NORTH"
        else:
            return "WEST"


# This is the function for task 4
def makeDecisionForTask4():
    global currentStateForTask4

    # When the robot is in 'Go north' state...
    if currentStateForTask4 == "Go north":
        if not eastIsWall():
            currentStateForTask4 = "Go east"
            return "EAST"
        elif northIsWall():
            currentStateForTask4 = "Go west"
            return "WEST"
        else:
            return "NORTH"

    # When the robot is in 'Go east' state...
    if currentStateForTask4 == "Go east":
        if not southIsWall():
            currentStateForTask4 = "Go south"
            return "SOUTH"
        elif eastIsWall():
            currentStateForTask4 = "Go north"
            return "NORTH"
        else:
            return "EAST"


    # When the robot is in 'Go south' state...
    if currentStateForTask4 == "Go south":
        if not westIsWall():
            currentStateForTask4 = "Go west"
            return "WEST"
        elif southIsWall():
            currentStateForTask4 = "Go east"
            return "EAST"
        else:
            return "SOUTH"

    # When the robot is in 'Go west' state...
    if currentStateForTask4 == "Go west":
        if not northIsWall():
            currentStateForTask4 = "Go north"
            return "NORTH"
        elif westIsWall():
            currentStateForTask4 = "Go south"
            return "SOUTH"
        else:
            return "WEST"
            
        


# The following line of code chooses the map of the game before it starts
# 
# You can change the map of the game by changing the parameters:
# 
# - Parameter 1 can be either:
#   - "task0", "task1", "task2", "task3" or "task4"
#     which mean the predefined maps from the task that you want to work on
#
#   - "custom"
#     which means any customized map(s) that you can add in game_map.py
#
# - Parameter 2 is a number representing the map you want to use
chooseGameMap("custom", 0)

#####
#
# !!! You DO NOT need to change anything from this point onwards !!!
#
#####

# Using the makeDecision function to set the Decision function used in each of the tasks
assignDecisionFuncForTask0(makeDecisionForTask0)
assignDecisionFuncForTask1(makeDecisionForTask1)
assignDecisionFuncForTask2(makeDecisionForTask2)
assignDecisionFuncForTask3(makeDecisionForTask3)
assignDecisionFuncForTask4(makeDecisionForTask4)

# Start the game
startGame()


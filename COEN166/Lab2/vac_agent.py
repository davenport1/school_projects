# Class: COEN 166 AI
# Name: Matthew Davenport
# Date: 9/26/2022
# Title: Lab 2 – Vacuum Cleaner Agent
# Description: This program wil demonstrate a vacuum cleaner
#               agent taking actions to clean or move based on a 
#               two square state 
import time
# Agent class
# Contains a list of three elements
#   first element is the state of the left square 'dirty' or 'clean'
#   second element is the state of the right square 'dirty' or 'clean'
#   third element is the current location of the vaccuum, 0 for left, 1 for right
# contains three action functions
#   suck changes the current square from 'dirty' to 'clean'
#   move_left moves the position from right to left
#   move_ right moves the position from left to right
class agent:
    state = ["dirty", "dirty", 0]
    # initial state with defaults set to dirty and the current position on the left square
    def __init__(self, left_state = "dirty", right_state = "dirty", current_loc = 0):
        self.state[0] = left_state
        self.state[1] = right_state
        self.state[2] = current_loc

    # change the location given to clean
    def suck(current_agent, loc_to_clean):
        current_agent.state[loc_to_clean] = "clean"
    # move agent to left square
    def move_left(current_agent):
        current_agent.state[2] = 0

    # move agent to right square
    def move_right(current_agent):
        current_agent.state[2] = 1

# take the current state and run the agent returning the moves and cost incurred
def run_agent(current_agent):
    start = time.time()                                     # time agent
    cost = 0                                                # keep track of total moves/cost made
    moves = []                                              # keep track of each move made
    # begin loop to run agent
    while current_agent.state[0] == "dirty" or current_agent.state[1] == "dirty":       # check if state is all clean
        if current_agent.state[2] == 0:                     # agent is in left square, determine clean or dirty and move or suck
            if current_agent.state[0] == "dirty":
                current_agent.suck(0)
                cost += 1                                   # keep track of moves and cost
                moves.append("suck")
            else:
                current_agent.move_right()
                cost += 1
                moves.append("right")
        elif current_agent.state[2] == 1:                     # agent is in right square, determine clean or dirty and move or suck
            if current_agent.state[1] == "dirty":
                current_agent.suck(1)
                cost += 1                                   # keep track of moves and cost
                moves.append("suck")
            else: 
                current_agent.move_left()
                cost += 1
                moves.append("left")

    moves.append(cost)
    # put cost into last element of moves 
    end = time.time()
    print("Agent took ", (end - start), " to execute")
    return moves


# test cases
test_1 = ["dirty", "dirty", 0]
test_2 = ["dirty", "dirty", 1]
test_3 = ["dirty", "clean", 0]
test_4 = ["dirty", "clean", 1]
test_5 = ["clean", "dirty", 0]
test_6 = ["clean", "dirty", 1]
test_7 = ["clean", "clean", 0]
test_8 = ["clean", "clean", 1]
tests = [test_1, test_2, test_3, test_4, test_5, test_6, test_7, test_8]


# load each elemenet of tests inner list as the agent
for x in range(0,7):
    # for y in range(0,2):
    test_agent = agent(tests[x][0], tests[x][1], tests[x][2])
    moves = run_agent(test_agent)
    print(moves)

# last element of moves is total cost agent incurred


# Expected output: 
# Agent took  3.5762786865234375e-06  to execute
# ['suck', 'right', 'suck', 3]
# Agent took  1.6689300537109375e-06  to execute
# ['suck', 'left', 'suck', 3]
# Agent took  7.152557373046875e-07  to execute
# ['suck', 1]
# Agent took  9.5367431640625e-07  to execute
# ['left', 'suck', 2]
# Agent took  1.430511474609375e-06  to execute
# ['right', 'suck', 2]
# Agent took  9.5367431640625e-07  to execute
# ['suck', 1]
# Agent took  4.76837158203125e-07  to execute
# [0]







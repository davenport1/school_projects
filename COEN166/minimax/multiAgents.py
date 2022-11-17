# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from argparse import Action
from util import manhattanDistance
from game import Directions
import random, util
import multiagentTestClasses

from game import Agent

class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"
        return successorGameState.getScore()

def scoreEvaluationFunction(currentGameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        "*** YOUR CODE HERE ***"
        
        # how is depth = 4 reached
        # how does root evaluate best Action
        # how go from ghost 3 to pacman agent
        # how does the recursive program work 
        initial_depth = 1
        agentIndex = 0
        # subfunctions: 
        # first function : called by pacman agent, pacman agent wants to maximize the value
        #   take 3 args
        #   1) current game state, 2) the agent index, 0 because only pacman agent calls it
        #   3) depth indicating what depth we are at
        def max_value(currentState, index, depth):
            valueList = []                                      # value list to store all possible values in list game states, stores values of game states
            actionList = currentState.getLegalActions(0)        # fetch actions agent can make
            if not actionList:
                return scoreEvaluationFunction(currentState)    # defined line 79
            for action in actionList:
                nextState = currentState.generateSuccessor(0, action) # generate state of leftmost child node
                value = min_value(nextState, 1, depth)          # index should always be one because after pacman makes move, ghost 1 will make move
                valueList.append(value)
                
            if depth == 1:                                      # at root node, return the best action to take
                bestActionIndex = valueList.index(max(valueList))
                bestAction = actionList[bestActionIndex]
                return bestAction
            else:                                               # not at root node, propogate the value score up the tree
                return max(valueList)
            
            # G3 = ghost 3, G2 = ghost 2 etc see graph in handout

        def min_value(currentState, index, depth):                          # index refers to which ghost (1/2/3) ghost is the MIN agent
            valueList = []
            actionList = currentState.getLegalActions(index)
            if not actionList:
                return scoreEvaluationFunction(currentState)    # defined line 79
            if index == currentState.getNumAgents() - 1:           # for ghost 3 move
                for action in actionList:
                    nextState = currentState.generateSuccessor(index,action)
                    if depth == self.depth:                     # end of game because self depth is at the max depth of the current game
                        value = scoreEvaluationFunction(nextState)
                        valueList.append(value)
                    else:
                        depth += 1
                        value = max_value(currentState, 0, depth) # after ghost 3 move, pacman goes, who is MAX agent
                        valueList.append(value)
            else:
                # depth stays same, were at ghost 1 or 2
                for action in actionList:
                    nextState = currentState.generateSuccessor(index, action)
                    index += 1
                    value = min_value(nextState, index, depth)
                    valueList.append(value)
            
            return min(valueList)
        
        return max_value(gameState, agentIndex, initial_depth)
        
            
                
                
class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        util.raiseNotDefined()

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        "*** YOUR CODE HERE ***"
        util.raiseNotDefined()

def betterEvaluationFunction(currentGameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: <write something here so we know what you did>
    """
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()

# Abbreviation
better = betterEvaluationFunction

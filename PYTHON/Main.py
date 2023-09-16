
from State import State
from BFS import BFS, printWaysToGetGoal
from Node import Node
#
state = State(10, 0, 0)

result = BFS(state)
printWaysToGetGoal(result)

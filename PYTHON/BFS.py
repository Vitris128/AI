# from collections import deque
from State import State
from Node import Node
import Constant as Constant

action = ["First State",
          "pour water X to Y",
          "pour water X to Z",
          "pour water Y to X",
          "pour water Y to Z",
          "pour water Z to X",
          "pour water Z to Y"]


def compareState(state: State, stateTwo: State):
    return state.x == stateTwo.x and state.y == stateTwo.y and state.z == stateTwo.z


def goalCheck(state: State):
    return state.x == Constant.GOAL or state.y == Constant.GOAL or state.z == Constant.GOAL


def BFS(state: State):
    root: Node
    newNode: Node
    OpenStack = []
    CloseStack = []
    root.state = state
    root.parent = None
    root.no_func = 0
    OpenStack.append(root)

    while len(OpenStack) > 0:
        node = OpenStack.pop()
        CloseStack.append(node)

        if goalCheck(node.state):
            return node
        for i in range(1, 6):
            newState: State
            newState = node.state.call_operator(i)
            if newState in OpenStack or newState in CloseStack:
                continue
            newNode: Node
            newNode.state = newState
            newNode.parent = node
            newNode.no_func = i
            OpenStack.append(newNode)

    return None


def printWaysToGetGoal(state: State):
    stackPrint = []
    while state.parent:
        stackPrint.append(state)
        state = state.parent
    stackPrint.append(state)
    no_action = 0
    while stackPrint is not None:
        print('Action {0}: {1}'.format(no_action, action[stackPrint[-1].no_func]))
        stackPrint[-1].printState()
        stackPrint.pop()
        no_action += 1

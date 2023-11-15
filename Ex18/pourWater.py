# from queue import Queue
from collections import deque
from typing import Any

TANK_X = 9
TANK_Y = 4
EMPTY = 0
GOAL = 6

MAXLENGTH = 100


action = ["Init State", "Pour Full X", "Pour Full Y","Pour Empty X","Pour Empty Y", "Pour X to Y", "Pour Y to X"]

class State:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def print_state(self):
        print(f"X = {self.x}, Y = {self.y}")

    def goal_check(self):
        return self.x == GOAL or self.y == GOAL


def pourFullX(currentState: State) -> State or None:
    newState = State()
    if currentState.x < TANK_X:
        newState.x = TANK_X
        newState.y = currentState.y
        return newState
    return None


def pourFullY(currentState: State) -> State or None:
    newState = State()
    if currentState.y < TANK_Y:
        newState.y = TANK_Y
        newState.x = currentState.x
        return newState
    return None


def pourEmptyX(currentState: State) -> State or None:
    if currentState.x == EMPTY:
        return None
    newState = State()
    newState.x = EMPTY
    newState.y = currentState.y
    return newState


def pourEmptyY(currentState: State) -> State or None:
    if currentState.y == EMPTY:
        return None
    newState = State()
    newState.y = EMPTY
    newState.x = currentState.x
    return newState


def pourXtoY(currentState: State) -> State or None:
    if currentState.x == 0 or currentState.y == TANK_Y:
        return None
    newState = State()
    newState.x = max(currentState.x - (TANK_Y - currentState.y), EMPTY)
    newState.y = min(currentState.y + currentState.x, TANK_Y)
    return newState


def pourYtoX(currentState: State) -> State or None:
    if currentState.y == 0 or currentState.x == TANK_X:
        return None
    newState = State()
    newState.y = max(currentState.y - (TANK_X - currentState.x), EMPTY)
    newState.x = min(currentState.y + currentState.x, TANK_X)
    return newState


def call_operator(currentState: State, option) -> State | None:
    if option == 1:
        return pourFullX(currentState)
    if option == 2:
        return pourFullY(currentState)
    if option == 3:
        return pourEmptyX(currentState)
    if option == 4:
        return pourEmptyY(currentState)
    if option == 5:
        return pourXtoY(currentState)
    if option == 6:
        return pourYtoX(currentState)
    return None


class Node:
    def __init__(self, state, parent, no_function):
        self.state = state
        self.parent = parent
        self.no_function = no_function


def compare_states(S1: State, S2: State) -> bool:
    return S1.x == S2.x and S1.y == S2.y


def find_state(state: State, queue):
    for node in queue:
        if compare_states(node.state, state):
            return True
    return False


def BFS_algorithm(initial_state: State):
    OpenBFS = []
    CloseBFS = []

    root = Node(initial_state, None, 0)
    OpenBFS.append(root)

    while OpenBFS:
        node = OpenBFS.pop(0)
        CloseBFS.append(node)

        if node.state.goal_check():
            return node

        for opt in range(1,7):

            new_state = call_operator(node.state, opt)
            if new_state == None:
                continue
            if find_state(new_state, CloseBFS) or find_state(new_state, OpenBFS):
                continue
            new_node = Node(new_state, node, opt)
            OpenBFS.append(new_node)
    return None


def print_ways_to_get_goal(node):
    stack_print = []

    while node.parent is not None:
        stack_print.append(node)
        node = node.parent

    stack_print.append(node)
    no_act = 0
    while stack_print:
        print(f"Action:{no_act} {action[stack_print[-1].no_function]}:")
        (stack_print[-1].state.print_state())
        print()
        stack_print.pop()
        no_act +=1

cur_S = State(5,4)
p = BFS_algorithm(cur_S)
print_ways_to_get_goal(p)

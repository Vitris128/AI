# from queue import Queue
from collections import deque

EMPTY = 0
MAXLENGTH = 100
MAXGLASSES = 6
GLASSESPERMOVE = 3
UP = 1
DOWN = 0


# action = ["--First State--", "Move 1 Monk:", "Move 1 Demon:", "Move 2 Monk:", "Move 1 Monk and 1 Demon:",
# "Move 2 Demon:"]

class State:
    def __init__(self):
        self.arrGlasses = [1 if i % 2 == 0 else 0 for i in range(6)]

    def print_state(self):
        for glass in self.arrGlasses:
            if glass == DOWN:
                print("DOWN", end="\t")
            else:
                print("UP", end="\t")
        print()

    def goal_check(self):
        return all(glass == DOWN for glass in self.arrGlasses)


def flip_glass(currentState: State, start_pos) -> State or None:
    if start_pos < 1 or start_pos > (MAXGLASSES - GLASSESPERMOVE + 1):
        return None

    result = State()
    result.arrGlasses = currentState.arrGlasses[:]

    for i in range(start_pos - 1, start_pos - 1 + GLASSESPERMOVE):
        result.arrGlasses[i] = not currentState.arrGlasses[i]

    return result


def call_operator(currentState: State, option) -> State:
    return flip_glass(currentState, option)


class Node:
    def __init__(self, state, parent, no_function):
        self.state = state
        self.parent = parent
        self.no_function = no_function


def compare_states(S1: State, S2: State) -> bool:
    return S1.arrGlasses == S2.arrGlasses


def find_state(state, open_queue):
    for node in open_queue:
        if compare_states(node.state, state):
            return True
    return False


def BFS_algorithm(initial_state: State):
    OpenBFS = deque()
    CloseBFS = deque()

    root = Node(initial_state, None, 0)
    OpenBFS.append(root)

    while OpenBFS:
        node: Node
        node = OpenBFS.popleft()
        CloseBFS.append(node)

        if node.state.goal_check():
            return node

        for opt in range(4, 0, -1):
            new_state = State()

            new_state = call_operator(node.state, opt)
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

    no_action = 0
    while stack_print:
        print(f"Action {no_action}:")
        (stack_print[-1].state.print_state())
        print()
        stack_print.pop()
        no_action += 1


cur_S = State()
p = BFS_algorithm(cur_S)
print_ways_to_get_goal(p)

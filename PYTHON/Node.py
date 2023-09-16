from State import State


class Node:
    state: State
    parent: State
    no_func: int

    def __init__(self):
        self.state = State(0, 0, 0)
        self.parent = State(0, 0, 0)
        self.no_func = 0

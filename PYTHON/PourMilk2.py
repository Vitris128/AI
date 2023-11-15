TANK_X = 8
TANK_Y = 5
TANK_Z = 3
EMPTY = 0
GOAL = 4

action = ["Init State",
          "Pour X to Y",
          "Pour X to Z",
          "Pour Y to X",
          "Pour Y to Z",
          "Pour Z to X",
          "Pour Z to Y"]


class State:
    def __init__(self, x=0, y=0, z=0):
        self.x = x
        self.y = y
        self.z = z

    def print_state(self):
        print(f"X = {self.x}, Y = {self.y}, Z = {self.z}")

    def goal_check(self):
        return self.x == GOAL or self.y == GOAL or self.z == GOAL


def pourXtoY(currentState: State) -> State or None:
    if currentState.x == 0 or currentState.y == TANK_Y:
        return None
    newState = State()
    newState.x = max(currentState.x - (TANK_Y - currentState.y), EMPTY)
    newState.y = min(currentState.y + currentState.x, TANK_Y)
    newState.z = currentState.z
    return newState


def pourXtoZ(currentState: State) -> State or None:
    if currentState.x == 0 or currentState.z == TANK_Z:
        return None
    newState = State()
    newState.x = max(currentState.x - (TANK_Z - currentState.z), EMPTY)
    newState.z = min(currentState.z + currentState.x, TANK_Z)
    newState.y = currentState.y
    return newState


def pourYtoX(currentState: State) -> State or None:
    if currentState.y == 0 or currentState.x == TANK_X:
        return None
    newState = State()
    newState.y = max(currentState.y - (TANK_X - currentState.x), EMPTY)
    newState.x = min(currentState.y + currentState.x, TANK_X)
    newState.z = currentState.z
    return newState


def pourYtoZ(currentState: State) -> State or None:
    if currentState.y == 0 or currentState.z == TANK_Z:
        return None
    newState = State()
    newState.y = max(currentState.y - (TANK_Z - currentState.z), EMPTY)
    newState.z = min(currentState.z + currentState.y, TANK_Z)
    newState.x = currentState.x
    return newState


def pourZtoX(currentState: State) -> State or None:
    if currentState.z == 0 or currentState.x == TANK_X:
        return None
    newState = State()
    newState.z = max(currentState.z - (TANK_X - currentState.x), EMPTY)
    newState.x = min(currentState.z + currentState.x, TANK_X)
    newState.y = currentState.y
    return newState


def pourZtoY(currentState: State) -> State or None:
    if currentState.z == 0 or currentState.y == TANK_Y:
        return None
    newState = State()
    newState.z = max(currentState.z - (TANK_Y - currentState.y), EMPTY)
    newState.y = min(currentState.z + currentState.y, TANK_Y)
    newState.x = currentState.x
    return newState


def call_operator(currentState: State, option) -> State | None:
    if option == 1:
        return pourXtoY(currentState)
    if option == 2:
        return pourXtoZ(currentState)
    if option == 3:
        return pourYtoX(currentState)
    if option == 4:
        return pourYtoZ(currentState)
    if option == 5:
        return pourZtoX(currentState)
    if option == 6:
        return pourZtoY(currentState)
    return None


class Node:
    def __init__(self, state, parent, no_function):
        self.state = state
        self.parent = parent
        self.no_function = no_function


def compare_states(S1: State, S2: State) -> bool:
    return S1.x == S2.x and S1.y == S2.y and S1.z == S2.z


def find_state(state: State, stack):
    for node in stack:
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

        for opt in range(1, 7):

            new_state = call_operator(node.state, opt)
            if new_state == None:
                continue
            if find_state(new_state, CloseBFS) or find_state(new_state, OpenBFS):
                continue
            new_node = Node(new_state, node, opt)
            OpenBFS.append(new_node)
    return None


def print_ways_to_get_goal(node):
    if node == None:
        print("No way to get the goal.")
        return
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
        no_act += 1


cur_S = State(8, 0, 0)

p = BFS_algorithm(cur_S)
print_ways_to_get_goal(p)

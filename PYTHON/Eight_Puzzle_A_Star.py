import copy

ROWS = 3
COLS = 3
EMPTY = 0
MAX_OPERATOR = 4
MAXLENGTH = 2000

action = ["First State", "Move cell EMPTY to UP", "Move cell EMPTY to DOWN", "Move cell EMPTY to LEFT",
          "Move cell EMPTY to RIGHT"]


class State:
    def __init__(self):
        self.eightPuzzel = [[0] * COLS for _ in range(ROWS)]
        self.emptyRow = 0
        self.emptyCol = 0

    def printState(self):
        print("\n--------")
        for row in range(ROWS):
            for col in range(COLS):
                print(f"| {self.eightPuzzel[row][col]} ", end="")
            print("|")
        print("--------")


def compareStates(state1, state2):
    if state1.emptyRow != state2.emptyRow or state1.emptyCol != state2.emptyCol:
        return False
    for row in range(ROWS):
        for col in range(COLS):
            if state1.eightPuzzel[row][col] != state2.eightPuzzel[row][col]:
                return False
    return True


def goalCheck(state, goal):
    return compareStates(state, goal)


def upOperator(state, result):
    empRowCurrent, empColCurrent = state.emptyRow, state.emptyCol
    if empRowCurrent > 0:
        result.emptyRow = empRowCurrent - 1
        result.emptyCol = empColCurrent
        result.eightPuzzel[empRowCurrent][empColCurrent] = state.eightPuzzel[empRowCurrent - 1][empColCurrent]
        result.eightPuzzel[empRowCurrent - 1][empColCurrent] = EMPTY
        return 1
    return 0


def downOperator(state, result):
    empRowCurrent, empColCurrent = state.emptyRow, state.emptyCol
    if empRowCurrent < ROWS - 1:
        result.emptyRow = empRowCurrent + 1
        result.emptyCol = empColCurrent
        result.eightPuzzel[empRowCurrent][empColCurrent] = state.eightPuzzel[empRowCurrent + 1][empColCurrent]
        result.eightPuzzel[empRowCurrent + 1][empColCurrent] = EMPTY
        return 1
    return 0


def leftOperator(state, result):
    empRowCurrent, empColCurrent = state.emptyRow, state.emptyCol
    if empColCurrent > 0:
        result.emptyRow = empRowCurrent
        result.emptyCol = empColCurrent - 1
        result.eightPuzzel[empRowCurrent][empColCurrent] = state.eightPuzzel[empRowCurrent][empColCurrent - 1]
        result.eightPuzzel[empRowCurrent][empColCurrent - 1] = EMPTY
        return 1
    return 0


def rightOperator(state, result):
    empRowCurrent, empColCurrent = state.emptyRow, state.emptyCol
    if empColCurrent < COLS - 1:
        result.emptyRow = empRowCurrent
        result.emptyCol = empColCurrent + 1
        result.eightPuzzel[empRowCurrent][empColCurrent] = state.eightPuzzel[empRowCurrent][empColCurrent + 1]
        result.eightPuzzel[empRowCurrent][empColCurrent + 1] = EMPTY
        return 1
    return 0


def callOperators(state, result, opt):
    switch = {
        1: upOperator,
        2: downOperator,
        3: leftOperator,
        4: rightOperator,
    }
    return switch[opt](state, result)


def heuristicOne(state, goal):
    count = 0
    for row in range(ROWS):
        for col in range(COLS):
            if state.eightPuzzel[row][col] != goal.eightPuzzel[row][col]:
                count += 1
    return count


class Node:
    def __init__(self):
        self.state = State()
        self.parent = None
        self.no_function = 0
        self.f = 0
        self.g = 0
        self.h = 0


def findState(state: State, stack):
    for i in range(len(stack)):
        if compareStates(stack[i].state, state):
            return stack[i], i
    return None, -1


def sortList(lst):
    lst.sort(key=lambda x: x.f)


def A_Star(initial_state, goal_state):
    Open_A_Star = []
    Close_A_Star = []
    root = Node()
    root.state = initial_state
    root.parent = None
    root.no_function = 0
    root.g = 0
    root.h = heuristicOne(root.state, goal_state)
    root.f = root.g + root.h
    Open_A_Star.append(root)
    while Open_A_Star:
        node = Open_A_Star.pop(0)
        Close_A_Star.append(node)
        if goalCheck(node.state, goal_state):
            return node
        for opt in range(1, MAX_OPERATOR + 1):
            new_state = copy.deepcopy(node.state)
            if callOperators(node.state, new_state, opt):
                new_node = Node()
                new_node.state = new_state
                new_node.parent = node
                new_node.no_function = opt
                new_node.g = node.g + 1
                new_node.h = heuristicOne(new_state, goal_state)
                new_node.f = new_node.g + new_node.h

                nodeFoundOpen, posOpen = findState(new_state, Open_A_Star)
                nodeFoundClose, posClose = findState(new_state, Close_A_Star)
                if nodeFoundOpen is None and nodeFoundClose is None:
                    Open_A_Star.append(new_node)
                elif nodeFoundOpen is not None and nodeFoundOpen.g > new_node.g:
                    del Open_A_Star[posOpen]
                    Open_A_Star.insert(posOpen, new_node)
                elif nodeFoundClose is not None and nodeFoundClose.g > new_node.g:
                    del Close_A_Star[posClose]
                    Open_A_Star.append(new_node)
                sortList(Open_A_Star)
    return None


def printWaysToGetGoal(node):
    if Node == None:
        print("No solution found.")
    listPrint = []
    while node.parent is not None:
        listPrint.insert(0, node)
        node = node.parent
    listPrint.insert(0, node)

    no_action = 0
    for i, item in enumerate(listPrint, 1):
        print(f"\nAction {no_action}: {action[item.no_function]}")
        item.state.printState()
        no_action += 1


if __name__ == "__main__":
    state = State()
    goal = State()
    state.emptyCol = 0
    state.emptyRow = 1
    state.eightPuzzel = [
        [2, 8, 1],
        [0, 4, 3],
        [7, 6, 5]
    ]

    goal.emptyCol = 1
    goal.emptyRow = 1
    goal.eightPuzzel = [
        [1, 2, 3],
        [8, 0, 4],
        [7, 6, 5]
    ]

    p = A_Star(state, goal)
    printWaysToGetGoal(p)

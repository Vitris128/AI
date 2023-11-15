import copy

MAXLENGTH = 100
MAXPERSON = 3
EMPTY = 0

action = ["--First State--", "Move 1 Monk", "Move 1 Demon", "Move 2 Monk", "Move 1 Monk and 1 Demon",
          "Move 2 Demon"]


class State:
    def __init__(self, Monk, Demon, Boat_Loc):
        self.Monk = Monk
        self.Demon = Demon
        self.Boat_Loc = Boat_Loc

    def printState(self):
        if self.Boat_Loc == 'A':
            print("\nA:{}:{}-Boat-------B:{}:{}".format(self.Monk, self.Demon, MAXPERSON - self.Monk,
                                                        MAXPERSON - self.Demon))
        elif self.Boat_Loc == 'B':
            print("\nA:{}:{}-------Boat-B:{}:{}".format(self.Monk, self.Demon, MAXPERSON - self.Monk,
                                                        MAXPERSON - self.Demon))

    def goalCheck(self):
        return self.Monk == 0 and self.Demon == 0 and self.Boat_Loc == 'B'

    @property
    def checkState(self):
        if self.Demon > MAXPERSON or self.Demon < 0 or self.Monk > MAXPERSON or self.Monk < 0:
            return 0
        if 0 < self.Monk < self.Demon:
            return 0
        if 0 < (MAXPERSON - self.Monk) < (MAXPERSON - self.Demon):
            return 0
        return 1


def moveBoat(c):
    return 'B' if c == 'A' else 'A'


def moveOneMonk(currentState, result):
    if result.Boat_Loc == 'A':
        result.Monk -= 1
        if result.checkState:
            result.Boat_Loc = moveBoat(currentState.Boat_Loc)
            return result
        return None
    else:
        result.Monk += 1
        if result.checkState:
            result.Boat_Loc = moveBoat(currentState.Boat_Loc)
            return result
        return None


def moveOneDemon(currentState, result):
    if result.Boat_Loc == 'A':
        result.Demon -= 1
        if result.checkState:
            result.Boat_Loc = moveBoat(currentState.Boat_Loc)
            return result
        return None
    else:
        result.Demon += 1
        if result.checkState:
            result.Boat_Loc = moveBoat(currentState.Boat_Loc)
            return result
        return None


def moveTwoMonks(currentState, result):
    if result.Boat_Loc == 'A':
        result.Monk -= 2
        if result.checkState:
            result.Boat_Loc = moveBoat(currentState.Boat_Loc)
            return result
        return None
    else:
        result.Monk += 2
        if result.checkState:
            result.Boat_Loc = moveBoat(currentState.Boat_Loc)
            return result
        return None


def moveMonkAndDemon(currentState, result):
    if result.Boat_Loc == 'A':
        result.Monk -= 1
        result.Demon -= 1
        if result.checkState:
            result.Boat_Loc = moveBoat(currentState.Boat_Loc)
            return result
        return None
    else:
        result.Monk += 1
        result.Demon += 1
        if result.checkState:
            result.Boat_Loc = moveBoat(currentState.Boat_Loc)
            return result
        return None


def moveTwoDemon(currentState, result):
    if result.Boat_Loc == 'A':
        result.Demon -= 2
        if result.checkState:
            result.Boat_Loc = moveBoat(currentState.Boat_Loc)
            return result
        return None
    else:
        result.Demon += 2
        if result.checkState:
            result.Boat_Loc = moveBoat(currentState.Boat_Loc)
            return result
        return None


def call_operator(currentState, result, option) -> State | None:
    if option == 1:
        return moveOneMonk(currentState, result)
    if option == 2:
        return moveOneDemon(currentState, result)
    if option == 3:
        return moveTwoMonks(currentState, result)
    if option == 4:
        return moveMonkAndDemon(currentState, result)
    if option == 5:
        return moveTwoDemon(currentState, result)
    print("Invalid option")
    return None


class Node:
    def __init__(self, state, parent, no_Function):
        self.state: State = state
        self.parent = parent
        self.no_Function = no_Function


def compareStates(S1: State, S2: State):
    return S1.Demon == S2.Demon and S1.Monk == S2.Monk and S1.Boat_Loc == S2.Boat_Loc


def findState(state: State, stack):
    for node in stack:
        if compareStates(node.state, state):
            return True
    return False


def DFS_Algorithm(state):
    OpenDFS, CloseDFS = [], []

    root = Node(state, None, 0)
    OpenDFS.append(root)

    while OpenDFS:
        node: Node = OpenDFS.pop()
        CloseDFS.append(node)

        if node.state.goalCheck():
            return node
        for opt in range(1, 6):
            newState = call_operator(node.state, copy.deepcopy(node.state), opt)
            if newState is None:
                continue
            if findState(newState, CloseDFS) or findState(newState, OpenDFS):
                continue
            newNode = Node(newState, node, opt)
            OpenDFS.append(newNode)
    return None


def printWaysToGetGoal(node):
    if node is None:
        print("No way to get the goal.")
        return
    stack_print = []

    while node.parent is not None:
        stack_print.append(node)
        node = node.parent

    stack_print.append(node)
    no_act = 0
    while stack_print:
        print(f"Action:{no_act} {action[stack_print[-1].no_Function]}:")
        stack_print[-1].state.printState()
        print()
        stack_print.pop()
        no_act += 1


if __name__ == "__main__":
    cur_S = State(3, 3, 'A')
    p = DFS_Algorithm(cur_S)
    print("LOCATION: (MONK : DEMON)\n")
    printWaysToGetGoal(p)

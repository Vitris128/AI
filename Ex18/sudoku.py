MAX_LENGTH = 100
NB_ROWS = 9
NB_COLUMNS = 9

MAX_VALUE = 10
EMPTY = 0
AREA_SQUARE_SIZE = 3
INF = 999999


class Coord:
    def __init__(self, x, y):
        self.x = x
        self.y = y


class Constrains:
    def __init__(self):
        self.data = [[0] * (NB_ROWS * NB_COLUMNS) for _ in range(NB_ROWS * NB_COLUMNS)]
        self.n = NB_ROWS * NB_COLUMNS


def init_constrains(constrains):
    for i in range(NB_ROWS * NB_COLUMNS):
        for j in range(NB_ROWS * NB_COLUMNS):
            constrains.data[i][j] = 0
    constrains.n = NB_ROWS * NB_COLUMNS


def index_of(coord):
    return NB_ROWS * coord.x + coord.y


def position_of_vertex(vertex):
    coord = Coord(0, 0)
    coord.x = vertex // NB_ROWS
    coord.y = vertex % NB_COLUMNS
    return coord


def add_constrain(constrains, source, target):
    u = index_of(source)
    v = index_of(target)
    if constrains.data[u][v] == 0:
        constrains.data[u][v] = 1
        constrains.data[v][u] = 1
        return 1
    return 0


def get_constrains(constrains, coord):
    v = index_of(coord)
    constrains_list = []
    for i in range(constrains.n):
        if constrains.data[v][i] == 1:
            constrains_list.append(position_of_vertex(i))
    return constrains_list


class Sudoku:
    def __init__(self):
        self.cells = [[EMPTY] * NB_COLUMNS for _ in range(NB_ROWS)]
        self.constrains = Constrains()


def init_sudoku(board):
    for i in range(NB_ROWS):
        for j in range(NB_COLUMNS):
            board.cells[i][j] = EMPTY
    init_constrains(board.constrains)


def init_sudoku_with_values(board, input_board):
    for i in range(NB_ROWS):
        for j in range(NB_COLUMNS):
            board.cells[i][j] = input_board[i][j]
    init_constrains(board.constrains)


def print_sudoku(board):
    print("Sudoku:")
    for i in range(NB_ROWS):
        if i % AREA_SQUARE_SIZE == 0:
            print("-------------------------")
        for j in range(NB_COLUMNS):
            if j % AREA_SQUARE_SIZE == 0:
                print("|", end=" ")
            print(f"{board.cells[i][j]} ", end="")
        print("|")
    print("-------------------------")


def is_filled_sudoku(board):
    for i in range(NB_ROWS):
        for j in range(NB_COLUMNS):
            if board.cells[i][j] == EMPTY:
                return 0
    return 1


def spread_constrains_form(position: Coord, constrains: Constrains, changeds: list):
    row, column = position.x, position.y
    for i in range(NB_ROWS):
        if i != row:
            pos = Coord(i, column)
            if add_constrain(constrains, position, pos):
                changeds.append(pos)
    for i in range(NB_COLUMNS):
        if i != column:
            pos = Coord(row, i)
            if add_constrain(constrains, position, pos):
                changeds.append(pos)

    for i in range(AREA_SQUARE_SIZE):
        for j in range(AREA_SQUARE_SIZE):
            area_x = (row // AREA_SQUARE_SIZE) * AREA_SQUARE_SIZE
            area_y = (column // AREA_SQUARE_SIZE) * AREA_SQUARE_SIZE
            if area_x + i != row or area_y + j != column:
                pos = Coord(area_x + i, area_y + j)
                if add_constrain(constrains, position, pos):
                    changeds.append(pos)


def get_available_values(position, board):
    pos_list = get_constrains(board.constrains, position)
    availables = [1] * MAX_VALUE
    for i in range(len(pos_list)):
        pos = pos_list[i]
        if board.cells[pos.x][pos.y] != EMPTY:
            availables[board.cells[pos.x][pos.y]] = 0
    available_list = []
    for i in range(1, MAX_VALUE):
        if availables[i]:
            available_list.append(i)
    return available_list


def get_next_empty_cell(board):
    for i in range(NB_ROWS):
        for j in range(NB_COLUMNS):
            pos = Coord(i, j)
            if board.cells[i][j] == EMPTY:
                return pos


def get_next_min_domain_cell(board):
    min_length = INF
    cell = Coord(0, 0)
    for i in range(NB_ROWS):
        for j in range(NB_COLUMNS):
            if board.cells[i][j] == EMPTY:
                pos = Coord(i, j)
                available_length = len(get_available_values(pos, board))
                if available_length < min_length:
                    min_length = available_length
                    cell = pos
    return cell


explored_counter = 0


def sudoku_backtracking(board):
    global explored_counter
    if is_filled_sudoku(board):
        return 1
    position = get_next_empty_cell(board)
    # position = get_next_min_domain_cell(sudoku)
    available = get_available_values(position, board)
    if len(available) == 0:
        return 0
    for j in range(len(available)):
        value = available[j]
        board.cells[position.x][position.y] = value
        explored_counter += 1
        if sudoku_backtracking(board):
            return 1
        board.cells[position.x][position.y] = EMPTY
    return 0


def solve_sudoku(board):
    global explored_counter
    init_constrains(board.constrains)
    for i in range(NB_ROWS):
        for j in range(NB_COLUMNS):
            history = []
            pos = Coord(i, j)
            spread_constrains_form(pos, board.constrains, history)
    explored_counter = 0
    if sudoku_backtracking(board):
        print("Solved")
    else:
        print("Can not solve")
    print(f"Explored {explored_counter} states")
    return board


if __name__ == "__main__":
    sudoku = Sudoku()
    inputs = [
        [0, 6, 1, 0, 0, 7, 0, 0, 3],
        [0, 9, 2, 0, 0, 3, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 8, 5, 3, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 5, 0, 4],
        [5, 0, 0, 0, 0, 8, 0, 0, 0],
        [0, 4, 0, 0, 0, 0, 0, 0, 1],
        [0, 0, 0, 1, 6, 0, 8, 0, 0],
        [6, 0, 0, 0, 0, 0, 0, 0, 0],
    ]
    init_sudoku_with_values(sudoku, inputs)
    print_sudoku(sudoku)
    result = solve_sudoku(sudoku)
    print_sudoku(result)

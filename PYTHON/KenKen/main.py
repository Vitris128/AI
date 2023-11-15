from utils import read_cage_from_file

board = read_cage_from_file("input_cage3.txt")
board.iteration_count = 0

if not board.solve():
    print("Can't solve")
    print(board)
else:
    print(f'Steps count: {board.iteration_count}')

    print("\nKenKen board:")
    board.print_values()

    print("\nCages board:")
    board.print_cages()

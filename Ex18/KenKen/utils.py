from board import Board
from helper_classes import Coordinate


def read_cage_from_file(file_path: str):
    board = Board()
    with open(file_path, 'r') as file:
        for line in file:
            parts = line.strip().split()
            value = int(parts[0])
            operator = parts[1]
            num_coordinates = int(parts[2])

            coordinates = [Coordinate(int(parts[i]), int(parts[i + 1])) for i in range(3, 3 + 2 * num_coordinates, 2)]

            board.create_cage(value, operator, coordinates)

    return board

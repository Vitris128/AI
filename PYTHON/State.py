import Constant as Constant


class State:
    x: int
    y: int
    z: int
    parent: object

    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    def printState(self):
        print('X: {}\tY: {}\tZ: {}'.format(self.x, self.y, self.z))

    def pourXY(self):
        if self.x > Constant.EMPTY and self.y < Constant.TANK_CAPACITY_Y:
            pour = Constant.TANK_CAPACITY_Y - self.y
            self.y = min(Constant.TANK_CAPACITY_Y, self.y + self.x)
            self.x = max(self.x - pour, 0)
            return True
        return False

    def pourXZ(self):
        if self.x > Constant.EMPTY and self.z < Constant.TANK_CAPACITY_Z:
            pour = Constant.TANK_CAPACITY_Z - self.z
            self.z = min(Constant.TANK_CAPACITY_Z, self.z + self.x)
            self.x = max(self.x - pour, 0)
            return True
        return False

    def pourYX(self):
        if self.y > Constant.EMPTY and self.x < Constant.TANK_CAPACITY_Y:
            pour = Constant.TANK_CAPACITY_X - self.x
            self.x = min(Constant.TANK_CAPACITY_X, self.y + self.x)
            self.y = max(self.y - pour, 0)
            return True
        return False

    def pourYZ(self):
        if self.y > Constant.EMPTY and self.z < Constant.TANK_CAPACITY_Z:
            pour = Constant.TANK_CAPACITY_Z - self.z
            self.z = min(Constant.TANK_CAPACITY_Z, self.z + self.y)
            self.y = max(self.y - pour, 0)
            return True
        return False

    def pourZX(self):
        if self.z > Constant.EMPTY and self.x < Constant.TANK_CAPACITY_X:
            pour = Constant.TANK_CAPACITY_X - self.x
            self.x = min(Constant.TANK_CAPACITY_X, self.z + self.x)
            self.z = max(self.z - pour, 0)
            return True
        return False

    def pourZY(self):
        if self.z > Constant.EMPTY and self.y < Constant.TANK_CAPACITY_Z:
            pour = Constant.TANK_CAPACITY_Y - self.y
            self.y = min(Constant.TANK_CAPACITY_Y, self.z + self.y)
            self.z = max(self.z - pour, 0)
            return True
        return False

    def call_operator(self, option):
        match option:
            case 1:
                # print("Pour X to Y:")
                return self.pourXY()
            case 2:
                # print("Pour X to Z:")
                return self.pourXZ()
            case 3:
                # print("Pour Y to X")
                return self.pourYX()
            case 4:
                # print("Pour Y to Z")
                return self.pourYZ()
            case 5:
                # print("Pour Z to X")
                return self.pourZX()
            case 6:
                # print("Pour Z to Y")
                return self.pourZY()

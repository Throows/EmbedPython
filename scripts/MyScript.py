import sys
import mygame

class Operation:

    a: float
    b: float
    result: int

    def __init__(self):
        self.a = mygame.GetRandomInt()
        self.b = mygame.GetRandomInt()

    def Add(self):
        print("Calculating...")
        self.result = self.b + self.a
        return self.result

    def SetNumber(self, a, b):
        self.a = a
        self.b = b

    def GetResult(self) -> float: 
        self.Add()
        print("Result: " + str(self.result))
        return self.result

if __name__ == "__main__":
    print("This script is not meant to be run directly.")
    print("Please run the EPy cpp program instead.")
    sys.exit(0)
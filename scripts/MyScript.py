import sys
import mygame

data = {
    "Name" : "Operation",
    "Description" : "A simple operation class.",
    "Version" : "1.0.0",
    "Author" : "Romain Berthoule",
    "Type" : "Addition Class",
    "UUID" : 329130
}

class Operation:

    a: float
    b: float
    result: int

    def __init__(self, a, b):
        self.a = a
        self.b = b

    def GetInfo(self) -> dict:
        return self.data

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
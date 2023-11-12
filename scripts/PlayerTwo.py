import sys
import mygame
import random

class Player:

    PlayerData: dict

    def __init__(self):
        self.PlayerData = {
            "Name" : "Soldier",
            "Health" : 320,
            "Damage" : 15,
            "Armor" : 60,
            "Speed" : 350,
            "Level" : 0,
            "Experience" : 0,
        }

    def GetInfo(self) -> str:
        return self.PlayerData["Name"]

    def ChoseAction(self) -> int:
        randAction = random.randint(0, 3)
        print(self.PlayerData["Name"] + " chose action " + str(randAction))
        return randAction
    
    def DoNothing(self) -> bool:
        print("I'm doing nothing.")
        return True
    
    def DoAttack(self) -> bool:
        print("I'm doing an attack.")
        return True
    
    def DoDefend(self) -> bool:
        print("I'm defending.")
        return True
    
    def DoRun(self) -> bool:
        print("I'm running away.")
        return True


if __name__ == "__main__":
    print("This script is not meant to be run directly.")
    print("Please run the EPy cpp program instead.")
    sys.exit(0)
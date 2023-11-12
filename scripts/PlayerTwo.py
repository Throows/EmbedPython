import sys
import mygame
import random

class Player:

    PlayerData: dict

    def __init__(self):
        """
        This is the base Stats for the Player (Constant values).
        """
        self.PlayerData = {
            "Name" : "Soldier",
            "Health" : 170,
            "Damage" : 15,
            "Armor" : 30,
            "Speed" : 350,
        }

    def GetInfo(self) -> str:
        return self.PlayerData["Name"]

    def ChoseAction(self) -> int:
        randAction = random.randint(0, 3)
        return randAction
    
    def DoNothing(self) -> bool:
        print(self.PlayerData["Name"] + " -> I'm doing nothing.")
        return True
    
    def DoAttack(self) -> bool:
        print(self.PlayerData["Name"] + " -> I'm doing a Small attack !")
        return True
    
    def DoDefend(self) -> bool:
        print(self.PlayerData["Name"] + " -> I'm defending.")
        return True
    
    def DoRun(self) -> bool:
        print(self.PlayerData["Name"] + " -> I'm running away.")
        return True


if __name__ == "__main__":
    print("This script is not meant to be run directly.")
    print("Please run the EPy cpp program instead.")
    sys.exit(0)
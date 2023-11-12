import sys
import mygame
import random

PlayerData = {
    "Name" : "Throows",
    "Health" : 100,
    "Damage" : 30,
    "Armor" : 16,
    "Speed" : 420,
    "Level" : 0,
    "Experience" : 0,
}

class Player:

    def GetInfo(self) -> str:
        return PlayerData["Name"]

    def ChoseAction(self) -> int:
        randAction = random.randint(0, 3)
        print(PlayerData["Name"] + " chose action " + str(randAction))
        return randAction
    
    def DoNothing() -> bool:
        print("I'm doing nothing.")
        return True
    
    def DoAttack() -> bool:
        print("I'm doing an attack.")
        return True
    
    def DoDefend() -> bool:
        print("I'm defending.")
        return True
    
    def DoRun() -> bool:
        print("I'm running away.")
        return True


if __name__ == "__main__":
    print("This script is not meant to be run directly.")
    print("Please run the EPy cpp program instead.")
    sys.exit(0)
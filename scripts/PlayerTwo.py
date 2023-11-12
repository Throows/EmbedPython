import sys
import mygame
import random

def OnCreatePlayer():
    PlayerData = {
        "Name" : "Soldier",
        "Health" : 170,
        "Damage" : 15,
        "Armor" : 30,
        "Speed" : 350
    }
    return PlayerData

def OnChoseAction() -> int:
    randAction = random.randint(0, 3)
    return randAction
    
def DoNothing() -> bool:
    #mygame.Say("2 - I'm doing nothing.")
    print("2 - I'm doing nothing.")
    return True
    
def DoAttack() -> bool:
    #mygame.Say("2 - I'm doing a Small attack !")
    print("2 - I'm doing a Small attack !")
    return True
    
def DoDefend() -> bool:
    #mygame.Say("2 - I'm defending.")
    print("2 - I'm defending.")
    return True
    
def DoRun() -> bool:
    #mygame.Say("2 - I'm running away.")
    print("2 - I'm running away.")
    return True

if __name__ == "__main__":
    print("This script is not meant to be run directly.")
    print("Please run the EPy cpp program instead.")
    sys.exit(0)
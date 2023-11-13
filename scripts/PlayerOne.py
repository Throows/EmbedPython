import sys
import mygame

PlayerData = {
    "Name" : "Throows",
    "Health" : 100,
    "Damage" : 30,
    "Armor" : 16,
    "Speed" : 420,
}

def OnCreatePlayer():
    return PlayerData

def OnChoseAction() -> int:
    return mygame.GetRandomInt()
    
def DoNothing() -> bool:
    mygame.Say("I'm doing nothing.")
    return True
    
def DoAttack() -> bool:
    mygame.Say("I'm doing a huge attack !")
    return True
    
def DoDefend() -> bool:
    mygame.Say("I'm defending.")
    return True
    
def DoRun() -> bool:
    mygame.Say("I'm running away.")
    return True

if __name__ == "__main__":
    print("This script is not meant to be run directly.")
    print("Please run the EPy cpp program instead.")
    sys.exit(0)
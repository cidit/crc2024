import math
import random
import curses
import sys
from types import prepare_class
# For your imports look at the rulebook to see what is allowed
# Pour les import permis allez vous référer au livre des règlements
"""part_5.py
This is the template file for the part 4 of the Prelim 1.
Ceci est le fichier template pour la partie 4 du Prelim 1.
"""

### Don't forget to write your own tests with pytest ###
### Noubliez pas d'aller écrire vos propres tests ave pytest ###
def part_5(text: str):
    """
    Print the 5 given words in an interesting format.

    Parameters:
        text (str): The input string containing 5 words.

    Returns:
        what you want.
    """
    ### You code goes here ###
    ### Votre code va ici ###
    
    


    return


# You can make you own test with simple print but you will need to make pytest to have all the points
# Vous pouvez faire des tests avec print simple mais il faut utiliser pytest pour avoir tous les points

# print(part_5('voici un petit texte test')) 
# # Expected output: ???

def main(stdscr: curses.window):
    if len(sys.argv) < 2:
        return
    alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    text = sys.argv[1].upper()
    iterations = len(text) * 5

    while True:
        stdscr.clear()
        curr_letter = math.floor(iterations/len(text))
        toprint = text[0:curr_letter]
        toprint += "".join(random.choice(alphabet) for n in range(len(text) - curr_letter))
        stdscr.addstr(toprint)
        stdscr.refresh()
        curses.napms(20)
        iterations += 1

if __name__ == "__main__":
    curses.wrapper(main)

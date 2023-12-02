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
    words = text.split()
    rowNbr = len(words) * 2
    longest_lenght = max(map(lambda word: len(word), words))
    words = list(map(lambda word: word.ljust(longest_lenght), words))
    rows = ["" for row in range(rowNbr)]
    for line in range(rowNbr):
        if line % 2 == 0:    
            for idx, char in enumerate(words[int(line/2)]): 
                if idx % 2 == 0:
                    rows[line] += char + " "
 
        else :
            for idx, char in enumerate(words[int(line/2)]): 
                if idx % 2 != 0:
                    rows[line] += " " + char
    cascade = map(lambda row: row, rows)
    return list(cascade)
    


    return


# You can make you own test with simple print but you will need to make pytest to have all the points
# Vous pouvez faire des tests avec print simple mais il faut utiliser pytest pour avoir tous les points

def print_cascade(cascade) -> None:
    for level in cascade:
        print(level)


print_cascade(part_5('Les volcants uniques du pacifique')) 
# # Expected output: ???


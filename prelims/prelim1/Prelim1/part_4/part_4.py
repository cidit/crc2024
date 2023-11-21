# For your imports look at the rulebook to see what is allowed
# Pour les import permis allez vous référer au livre des règlements
"""part_4.py
This is the template file for the part 4 of the Prelim 1.
Ceci est le fichier template pour la partie 4 du Prelim 1.
"""

def part_4(text: str):
    """
    Print the 5 given words in a cascade.

    Parameters:
        text (str): The input string containing 5 words.

    Returns:
        list[str]: The cascade separated by level.
    """

    ### You code goes here ###
    ### Votre code va ici ###

    words = text.split()
    # TODO: what if last character is not alpha? (ex: !, ?, .)    
    longest_length = max(map(lambda word: len(word), words))
    words = map(lambda word: word.ljust(longest_length), words)
    rows = [" " * row for row in range(longest_length)]
    for word in words:
        for idx, char in enumerate(word):
            rows[idx] += char + " "
    cascade = map(lambda row: row[0:-1], rows)

    return list(cascade)

# To help you visualize your cascade
# Pour vous aider à visualiser votre cascade
def print_cascade(cascade) -> None:
    for level in cascade:
        print(level)

# Uncomment the following print to test your function without pytest
# Décommenter la suite pour des tests sans pytest

# print_cascade(part_4('voici un petit texte test')) 
# # Expected output: ["v u p t t",
# #                   " o n e e e",
# #                   "  i   t x s",
# #                   "   c   i t t",
# #                   "    i   t e  "]

# print_cascade(part_4('la prog est vraiment fun'))
#  # Expected output: ['l p e v f',
#  #                  #' a r s r u',
#  #                  #'    o t a n',
#  #                  #'     g   i  ',
#  #                  #'          m  ',
#  #                  #'           e  ',
#  #                  #'            n  ',
#  #                  #'             t  ']

# print_cascade(part_4('This is a simple test')
# # Expected output: ['T i a s t',
# #                   ' h s   i e',
# #                   '  i     m s',
# #                   '   s     p t',
# #                   '          l  ',
# #                   '           e  ']

# print_cascade(part_4('in the right order please'))
# # Expected output: ['i t r o p',
# #                   ' n h i r l',
# #                   '    e g d e',
# #                   '       h e a',
# #                   '        t r s',
# #                   '             e']

# For your imports look at the rulebook to see what is allowed
# Pour les import permis allez vous référer au livre des règlements
"""part_4.py
This is the template file for the part 4 of the Prelim 2.
Ceci est le fichier template pour la partie 4 du Prelim 2.
"""
from math import floor


def encode(base: int, number: int) -> list[int]:
    remainder = number
    terms = []
    while remainder / base != 0:
        r = remainder % base
        terms.insert(0, r)
        remainder = floor(remainder / base)
    return terms


def part_4(base: int, number: int) -> str:
    """
    Base shifting into modular arithmetic

    Parameters:
        base (int): The base to which you convert.
        number (int): The number to convert

    Returns:
        int: Final 4-digits code
    """
    ### You code goes here ###
    ### Votre code va ici ###
    STEPS = 5
    for _ in range(0, STEPS):
        terms = encode(base, number)
        concat = "".join(map(str, terms))
        number = int(concat)

    step_one = str(number)

    files = [[], [], [], []]
    for digit in step_one:
        digit = int(digit)
        files[digit % 4].append(digit)

    def cumul_file(file: list[int]) -> int:
        if len(file) == 0:
            return 0
        while len(file) > 1:
            s = sum(file)
            file = list(map(int, str(s)))
        return file[0]

    files = [cumul_file(file) for file in files]
    return "".join(map(str, files))


# Uncomment the following print to test your function without pytest
# Décommenter la suite pour des tests sans pytest

# print(part_4(29, 982)) # Expected: '0330'
# print(part_4(23, 1053))  # Expected: '8400'
# print(part_4(65, 812)) # Expected: '0707'

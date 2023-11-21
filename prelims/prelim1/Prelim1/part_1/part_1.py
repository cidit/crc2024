# For your imports look at the rulebook to see what is allowed
# Pour les import permis allez vous référer au livre des règlements
"""part_1.py
This is the template file for the part 1 of the Prelim 1.
Ceci est le fichier template pour la partie 1 du Prelim 1.
"""

def part_1(text: str) -> int:
    """
    Finds the secret number hidden in the text.

    Parameters:
        text (str): The input string.

    Returns:
        int: The number hidden in the text.
    """
    x = text.split("|")
    y = x[1].split("|")
    secret_number = int(y[0])  

    return secret_number


# Uncomment the following print to test your function without pytest
# Décommenter la suite pour des tests sans pytest

print(part_1('ti kzk mab cvm kwuxmbqbqwv bzma|18| ncv'))  # Expected output: 18
print(part_1('Zcfsa wdgia rczcf gwh oash, qcbgsqhshif orwdwgqwbu szwh. Qfog qifgig dzoqsfoh hcfhcf bsq toqwzwgwg. Bizzoa jsz sfoh zsc. Gigdsbrwggs bcb bwgz sbwa. Aosqsbog oq sfoh sush sfoh gcrozsg hsadig. Bizzo toqwzwgw. Dszzsbhsgeis toqwzwgwg|12| hwbqwribh bibq, dfshwia hwbqwribh rczcf jsbsbohwg wb. Bizzoa woqizwg oqqiagob zsc bcb sttwqwhif. Aosqsbog crwc ofqi, hfwghweis.'))  # Expected output: 12
print(part_1("ti kzk mab |0|cvm kwuxmbqbqwv bzma ncv"))   # Expected output: 0
print(part_1("ti kzk mab cvm kwuxm|-7|bqbqwv bzma ncv"))   # Expected output: -7

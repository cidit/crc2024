import functools

# For your imports look at the rulebook to see what is allowed
# Pour les import permis allez vous référer au livre des règlements
"""part_2.py
This is the template file for the part 2 of the Prelim 1.
Ceci est le fichier template pour la partie 2 du Prelim 1.
"""

def part_2(text: str, key: int) -> str:
    """
    Decrypts the text with Caesar cypher.

    Parameters:
        text (str): The input string.
        key  (int): The shifting key.

    Returns:
        str: The decrypted text.
    """

    def over_under_flow(num: int, min: int, max: int) -> int:
        diff = max - min +1
        if (num < min):
            return num + diff
        elif (num > max):
            return num - diff
        else:
            return num

    @functools.cache
    def map_char(char: str, key: int):
        ichar = ord(char)
        new_ichar = (
            over_under_flow(ichar + key, min=ord('a'), max=ord('z'))
            if char.islower()
            else over_under_flow(ichar + key, min=ord('A'), max=ord('Z'))
        )
        return chr(new_ichar)

    decrypted_text = "".join([map_char(c, key) if c.isalpha() else c for c in text])
    return decrypted_text


# Uncomment the following print to test your function without pytest
# Décommenter la suite pour des tests sans pytest

# print(part_2('ti kzk mab cvm kwuxmbqbqwv bzma ncv!', 18))  # Expected output: la crc est une competition tres fun!
# print(part_2('Zcfsa wdgia rczcf gwh oash, qcbgsqhshif orwdwgqwbu szwh. Qfog qifgig dzoqsfoh hcfhcf bsq toqwzwgwg. Bizzoa jsz sfoh zsc. Gigdsbrwggs bcb bwgz sbwa. Aosqsbog oq sfoh sush sfoh gcrozsg hsadig. Bizzo toqwzwgw. Dszzsbhsgeis toqwzwgwg hwbqwribh bibq, dfshwia hwbqwribh rczcf jsbsbohwg wb. Bizzoa woqizwg oqqiagob zsc bcb sttwqwhif. Aosqsbog crwc ofqi, hfwghweis.', 12))
# # Expected output: Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras cursus placerat tortor nec facilisis. Nullam vel erat leo. Suspendisse non nisl enim. Maecenas ac erat eget erat sodales tempus. Nulla facilisi. Pellentesque facilisis tincidunt nunc, pretium tincidunt dolor venenatis in. Nullam iaculis accumsan leo non efficitur. Maecenas odio arcu, tristique.
# print(part_2("This text is really good as is!", 0))   # Expected output: This text is really good as is!
# print(part_2("Cb jo oiggw o fsqizcbg", -14))   # Expected output: On va aussi a reculons

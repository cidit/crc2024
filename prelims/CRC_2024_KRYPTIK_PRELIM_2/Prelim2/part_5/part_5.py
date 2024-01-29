# For your imports look at the rulebook to see what is allowed
# Pour les import permis allez vous référer au livre des règlements
"""part_5.py
This is the template file for the part 5 of the Prelim 2.
Ceci est le fichier template pour la partie 5 du Prelim 2.
"""

def part_5(p: str, q: str, e: str, M: str) :
    """
    Find the C and d number in RSA encryption.

    Parameters:
        p (str): The first prime.
        q (str): The second prime.
        e (str): The exponent.
        M (str): The message to encode.

    Returns:
        (int, int) : A tuple containing the C and d from RSA encryption 
    """
    d = 0
    ### You code goes here ###
    ### Votre code va ici ###

    ip = int(p)
    iq = int(q)

    n = ip * iq
    phi_n = (ip-1)*(iq-1)    

    ie = int(e)
    iM = int(M)

    C=pow(iM, ie)% n
    
    d=(1%phi_n)/ie

    # WHAT THE HELL IS `v` (ಥ﹏ಥ)
    # u = 0
    # v = 0
    # for i in range(0, n):
    #     if e * i + phi_n * % u == 1

    return (C, d)


# Uncomment the following print to test your function without pytest
# Décommenter la suite pour des tests sans pytest

# print(part_5('0023', '8111', '1579', '0330')) # Expected: (168442, 127459)
# print(part_5('3617', '4567', '3517', '8400')) # Expected: (13038683, 8379733)
# print(part_5('5051', '5557', '3833', '0707')) # Expected: (26895292, 16016297)


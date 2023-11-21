# For your imports look at the rulebook to see what is allowed
# Pour les import permis allez vous référer au livre des règlements
"""part_3.py
This is the template file for the part 3 of the Prelim 1.
Ceci est le fichier template pour la partie 3 du Prelim 1.
"""


def part_3(text: str) -> str:
    """
    Extracts the 5 most common words.

    Parameters:
        text (str): The input string.

    Returns:
        str: The 5 most common words in order.
    """

    ### You code goes here ###
    ### Votre code va ici ###

    words = text.split()
    occurences: dict = {}

    for word in words:
        saved_count = occurences.get(word)
        count = 0 if saved_count is None else saved_count
        occurences[word] = count + 1

    sorted_occurences = sorted(
        occurences.items(),
        # take the second element, the count
        key=lambda element: element[1],
        reverse=True,
    )
    take_5 = sorted_occurences[:5]
    # take the first element, the word
    word_only = map(lambda elem: elem[0], take_5)
    return " ".join(word_only)


# Uncomment the following print to test your function without pytest
# Décommenter la suite pour des tests sans pytest

# print(part_3('chien le chat maison voiture message arbre secret soleil fleurs musique rive montagne est ordinateur plage le cell lune livre mer secret ceci le restaurant amis message le voyage chanson bateau hiver automne neige amour sport bonheur le art danse message avion jardin secret livre parc est cadeau table est chapeau porte lunettes secret chemin message commande fort pont or argent fourchette ceci message couteau tasse montre chapeau guitare le piano balance le nuage parapluie est balle chocolat ceci message chaussettes radio silence plume pinceau secret tableau nuage le bougie chemin miroir porte montre papier le lampe sac message bonjour le sable'))
# # Expected output: 'le message secret est ceci'
# print(part_3('chocolat la pluie est la plage est pomme la sapin la musique fun vraiment ordinateur prog prog cauchemar la montagne bonjour arbre prog amour livre vraiment prog couleur danse guitare voyage chanson est horizon fleur fun prog livre lune ballon vraiment ami prince la plume prog vent porte la table aventure la neige est chaussure histoire bateau'))
# # Expected output: 'la prog est vraiment fun'
# print(part_3('This is a simple test This is a simple This is a This is This')
# # Expected output: 'This is a simple test'
# print(part_3('please order right the in in the right order right the in in the in'))
# # Expected output: 'in the right order please'

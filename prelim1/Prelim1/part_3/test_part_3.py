### This is the test file and you are NOT supposed to modify it (unless you want to add more tests) ###
### Ceci est le fichier de test et vous n'êtes PAS supposé le modifier (sauf si vous voulez ajouter plus de tests) ###

# To run the test run the command pytest in the terminal being in the right folder (go see test instructions if needed)
# Pour rouler les tests avec pytest utilisez le terminal dans le bon folder et exécutez la commande pytest (voir le fichier donnée sur les tests)

from part_3 import part_3

def test_from_problem_description():
    assert part_3("chien le chat maison voiture message arbre secret soleil fleurs \
                  musique rive montagne est ordinateur plage le cell lune livre mer secret \
                  ceci restaurant amis le voyage chanson bateau hiver automne neige amour \
                  sport bonheur le art danse message avion jardin livre parc est cadeau table \
                  chapeau porte lunettes secret chemin message commande fort pont or argent \
                  fourchette message couteau tasse montre chapeau guitare le piano balance le \
                  nuage parapluie est balle chocolat ceci message chaussettes radio silence plume \
                  pinceau secret tableau nuage le bougie chemin miroir porte montre papier le \
                  lampe sac message bonjour le sable") == "le message secret est ceci"
    
    assert part_3("chocolat la pluie est la plage est pomme la sapin la musique fun vraiment \
                  ordinateur prog prog cauchemar la montagne bonjour arbre prog amour livre \
                  vraiment prog couleur danse guitare voyage chanson est horizon fleur fun prog \
                  livre lune ballon vraiment ami prince la plume prog vent porte la table \
                  aventure la neige est chaussure histoire bateau") == "la prog est vraiment fun"

def test_simple():
    assert part_3("This is a simple test This is a simple This is a This is This") == "This is a simple test"

def test_reversed():
    assert part_3("please order right the in in the right order right the in in the in") == "in the right order please"

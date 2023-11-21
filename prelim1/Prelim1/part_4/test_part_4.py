### This is the test file and you are NOT supposed to modify it (unless you want to add more tests) ###
### Ceci est le fichier de test et vous n'êtes PAS supposé le modifier (sauf si vous voulez ajouter plus de tests) ###

# To run the test run the command pytest in the terminal being in the right folder (go see test instructions if needed)
# Pour rouler les tests avec pytest utilisez le terminal dans le bon folder et exécutez la commande pytest (voir le fichier donnée sur les tests)

from part_4 import part_4

def test_from_problem_description():
    assert part_4("voici un petit texte test") == [ "v u p t t",
                                                    " o n e e e",
                                                    "  i   t x s",
                                                    "   c   i t t",
                                                    "    i   t e  "]
    
    assert part_4("la prog est vraiment fun") == [  "l p e v f",
                                                    " a r s r u",
                                                    "    o t a n",
                                                    "     g   i  ",
                                                    "          m  ",
                                                    "           e  ",
                                                    "            n  ",
                                                    "             t  "]

def test_simple():
    assert part_4("This is a simple test") == [ "T i a s t",
                                                " h s   i e",
                                                "  i     m s",
                                                "   s     p t",
                                                "          l  ",
                                                "           e  "]

def test_simple_2():
    assert part_4("in the right order please") == [ "i t r o p",
                                                    " n h i r l",
                                                    "    e g d e",
                                                    "       h e a",
                                                    "        t r s",
                                                    "             e"]

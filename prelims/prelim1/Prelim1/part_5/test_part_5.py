# To run the test run the command pytest in the terminal being in the right folder (go see test instructions if needed)
# Pour rouler les tests avec pytest utilisez le terminal dans le bon folder et exécutez la commande pytest (voir le fichier donnée sur les tests)

from part_5 import part_5

def test_from_problem_description():
    assert part_5("voici un petit texte test") == [ "v i i ",
                                                    " o c",
                                                    "",
                                                    "u     ",
                                                    " n  ",
                                                    "",
                                                    "p t t ",
                                                    " e i",
                                                    "",
                                                    "t x e ",
                                                    " e t",
                                                    "",
                                                    "t s   ",
                                                    " e t",
                                                    ""] 

def test_simple():
    assert part_5("Les volcants uniques du pacifique") == [ "L s       ",
                                                            " e      ",
                                                            "",
                                                            "v l a t   ",
                                                            " o c n s",
                                                            "",
                                                            "u i u s   ",
                                                            " n q e  ",
                                                            "",
                                                            "d         ",
                                                            " u      ",
                                                            "",
                                                            "p c f q e ",
                                                            " a i i u",
                                                            ""] 

def test_simple_2():
    assert part_5("") == None 
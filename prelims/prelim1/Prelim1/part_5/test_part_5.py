# To run the test run the command pytest in the terminal being in the right folder (go see test instructions if needed)
# Pour rouler les tests avec pytest utilisez le terminal dans le bon folder et exécutez la commande pytest (voir le fichier donnée sur les tests)

from part_5 import part_5

def test_from_problem_description():
    assert part_5("voici un petit texte test") == None # You specify the expected output

def test_simple():
    assert part_5("") == None # You specify the expected output and the input

def test_simple_2():
    assert part_5("") == None # You specify the expected output and the input
# To run the test run the command pytest in the terminal being in the right folder (go see test instructions if needed)
# Pour rouler les tests avec pytest utilisez le terminal dans le bon folder et exécutez la commande pytest (voir le fichier donnée sur les tests)

from part_5 import part_5

def test_from_problem_description():
    assert part_5('0023', '8111', '1579', '0330') == (168442, 127459)

def test_simple():
    assert part_5('3617', '4567', '3517', '8400') == (13038683, 8379733)

def test_simple_2():
    assert part_5('5051', '5557', '3833', '0707') == (26895292, 16016297)

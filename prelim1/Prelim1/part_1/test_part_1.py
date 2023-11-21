### This is the test file and you are NOT supposed to modify it (unless you want to add more tests) ###
### Ceci est le fichier de test et vous n'êtes PAS supposé le modifier (sauf si vous voulez ajouter plus de tests) ###

# To run the test run the command pytest in the terminal being in the right folder (go see test instructions if needed)
# Pour rouler les tests avec pytest utilisez le terminal dans le bon folder et exécutez la commande pytest (voir le fichier donnée sur les tests)

from part_1 import part_1

def test_from_problem_description():
    assert part_1("ti kzk mab cvm kwuxmbqbqwv bzma|18| ncv") == 18
    assert part_1("Zcfsa wdgia rczcf gwh oash, qcbgsqhshif orwdwgqwbu szwh. \
                  Qfog qifgig dzoqsfoh hcfhcf bsq toqwzwgwg. Bizzoa jsz sfoh zsc. \
                  Gigdsbrwggs bcb bwgz sbwa. Aosqsbog oq sfoh sush sfoh gcrozsg hsadig. \
                  Bizzo toqwzwgw. Dszzsbhsgeis toqwzwgwg|12| hwbqwribh bibq, \
                  dfshwia hwbqwribh rczcf jsbsbohwg wb. Bizzoa woqizwg oqqiagob zsc bcb sttwqwhif. \
                  Aosqsbog crwc ofqi, hfwghweis.") == 12

def test_with_zero():
    assert part_1("ti kzk mab |0|cvm kwuxmbqbqwv bzma ncv") == 0

def test_with_negative():
    assert part_1("ti kzk mab cvm kwuxm|-7|bqbqwv bzma ncv") == -7

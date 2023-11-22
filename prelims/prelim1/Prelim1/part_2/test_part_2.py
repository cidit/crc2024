### This is the test file and you are NOT supposed to modify it (unless you want to add more tests) ###
### Ceci est le fichier de test et vous n'êtes PAS supposé le modifier (sauf si vous voulez ajouter plus de tests) ###

# To run the test run the command pytest in the terminal being in the right folder (go see test instructions if needed)
# Pour rouler les tests avec pytest utilisez le terminal dans le bon folder et exécutez la commande pytest (voir le fichier donnée sur les tests)

from part_2 import part_2

def test_from_problem_description():
    assert part_2("ti kzk mab cvm kwuxmbqbqwv bzma ncv!", 18) == "la crc est une competition tres fun!"
    assert part_2("Zcfsa wdgia rczcf gwh oash, qcbgsqhshif orwdwgqwbu szwh. "\
                  "Qfog qifgig dzoqsfoh hcfhcf bsq toqwzwgwg. Bizzoa jsz sfoh zsc. "\
                  "Gigdsbrwggs bcb bwgz sbwa. Aosqsbog oq sfoh sush sfoh gcrozsg hsadig. "\
                  "Bizzo toqwzwgw. Dszzsbhsgeis toqwzwgwg hwbqwribh bibq, "\
                  "dfshwia hwbqwribh rczcf jsbsbohwg wb. Bizzoa woqizwg oqqiagob zsc bcb sttwqwhif. "\
                  "Aosqsbog crwc ofqi, hfwghweis.", 12) == \
                        "Lorem ipsum dolor sit amet, "\
                        "consectetur adipiscing elit. Cras cursus placerat tortor nec facilisis. "\
                        "Nullam vel erat leo. Suspendisse non nisl enim. "\
                        "Maecenas ac erat eget erat sodales tempus. Nulla facilisi. "\
                        "Pellentesque facilisis tincidunt nunc, pretium tincidunt dolor venenatis in. "\
                        "Nullam iaculis accumsan leo non efficitur. Maecenas odio arcu, tristique."

def test_with_zero():
    assert part_2("This text is really good as is!", 0) == "This text is really good as is!"

def test_with_negative():
    assert part_2("Cb jo oiggw o fsqizcbg", -14) == "On va aussi a reculons"



def timings(functions):
    import timeit
    import os
    if os.getenv("TIMEIT") == "TRUE":
        print("timings:")
        for f in functions:
            time = timeit.timeit(f, number=10_000)
            print(f"{f.__name__}, {time*1_000}ms")
timings([
    test_from_problem_description,
    test_with_zero,
    test_with_negative,
])

def part_5(text: str):

    words = text.split()
    rowNbr = len(words) * 3
    longest_lenght = max(map(lambda word: len(word), words))
    if longest_lenght == 0 :
        return None
    
    words = list(map(lambda word: word.ljust(longest_lenght), words))
    rows = ["" for row in range(rowNbr)]
    for line in range(0, rowNbr, 3):
        for idx, char in enumerate(words[int(line/3)]):
            if idx % 2 == 0:
                rows[line] += char + " "
            else :
                rows[line + 1] += " " + char 
                                   
    cascade = map(lambda row: row, rows)
    return list(cascade)
    

def print_cascade(cascade) -> None:
    for level in cascade:
        print(level)


print_cascade(part_5('Les volcants uniques du pacifique')) 




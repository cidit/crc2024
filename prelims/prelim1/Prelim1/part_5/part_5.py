def part_5(text: str):
    
    if text == None or len(text) == 0:
        return None
    words = text.split()
    rowNbr = len(words) * 3
    longest_lenght = max(map(lambda word: len(word), words))
    
    words = list(map(lambda word: word.ljust(longest_lenght), words))
    rows = ["" for row in range(rowNbr)]
    for line in range(0, rowNbr, 3):
        for idx, char in enumerate(words[int(line/3)]):
            if idx % 2 == 0:
                rows[line] += char + " "
            else :
                rows[line + 1] += " " + char 
                                   
    snake = map(lambda row: row, rows)
    return list(snake)
    

def print_snake(snake) -> None:
    for line in snake:
        print(line)


print_snake(part_5('Les volcants uniques du pacifique')) 




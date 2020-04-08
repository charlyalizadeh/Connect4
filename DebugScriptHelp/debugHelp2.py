def displayMat(part1,part2):
    for i in range(64):
        if (part2 >> i) & 1:
            print(' 1',end=' ')
        else:
            print(' 0',end=' ')
        if i == int(i/12)*12+int(i/12)-1 and i!=0:
            print()
    print()
    for i in range(64):
        if (part1 >> i) & 1:
            print(' 1',end=' ')
        else:
            print(' 0',end=' ')
        if i == (int(i/12)*12+int(i/12)-1) and i!=0:
            print()


while True:
    part1 = int(input('part1 : '))
    part2 = int(input('part2 : '))
    displayMat(part1,part2)
    print()

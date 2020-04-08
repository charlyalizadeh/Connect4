def displayMat(part16bits,part64bits):
    for i in range(64):
        if (part64bits >> i) & 1:
            print(' 1',end=' ')
        else:
            print(' 0',end=' ')
        if i == int(i/12)*12+int(i/12)-1 and i!=0:
            print()
    for i in range(16):
        if (part16bits >> i) & 1:
            print(' 1',end=' ')
        else:
            print(' 0',end=' ')
        if i==0:
            print()


while True:
    part16bits = int(input('part8bits : '))
    part64bits = int(input('part64bits : '))
    displayMat(part16bits,part64bits)
    print()


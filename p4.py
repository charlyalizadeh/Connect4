import os

def clearTerminal():
    if os.name == 'nt':
        os.system('cls')
    elif os.name == 'posix':
        os.system('clear')
"""
┏ ┓ ━ ┃ ┳ ┻ ┫ ┣ ╋ ┗ ┛
┏━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┳━┓
┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃
┣━╋━╋━╋━╋━╋━╋━╋━╋━╋━╋━╋━┫
┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃
┣━╋━╋━╋━╋━╋━╋━╋━╋━╋━╋━╋━┫
┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃
┣━╋━╋━╋━╋━╋━╋━╋━╋━╋━╋━╋━┫
┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃
┣━╋━╋━╋━╋━╋━╋━╋━╋━╋━╋━╋━┫
┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃
┣━╋━╋━╋━╋━╋━╋━╋━╋━╋━╋━╋━┫
┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃ ┃
┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛
┏━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┓
┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃
┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃
┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃
┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃
┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃
┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫
┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃   ┃
┗━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┛
Un state est définie par une liste de la forme :
    [ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
      0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
      0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
      0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
      0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
      0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ]

      Avec 0 := Case vide
           1 := Case IA
          -1 := Case Adversaire

"""

def display(state,ai = '⚫', opponent = '⚪'):
    print('  0   1   2   3   4   5   6   7   8   9  10  11  ')
    print('┏━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┓')
    for i in range(6):
        print('┃',end='')
        for j in range(12):
            if state[i*12+j]==1:
                print(f' {ai}┃',end='')
            elif state[i*12+j]==-1:
                print(f' {opponent}┃',end='')
            else:
                print(f'   ┃',end='')
        print()
        if i == 5:
            print('┗━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┛')
        else:
            print('┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫')
    print()


def actions(state):
    possibleMove = [j for j in range(12) if state[j]==0]
    return possibleMove

def results(state,action,player):
    newState = state[:]
    for i in range(5,-1,-1):
        if newState[i*12+action] == 0:
            newState[i*12+action] = player
            break
    return newState


def heuristic(state):
    tempHeuristic = 0
    for i in range(6*12):
        tempHeuristic+=state[i]
    return tempHeuristic

def minmax(state,player,depth,alpha,beta):
    if depth==0:
        return heuristic(state)

    if player == 1:
        value = -5000
        for a in actions(state):
            value = max(value,minmax(results(state,a,player),-player,depth-1,alpha,beta))
            if value>=beta:
                return value
            alpha = max(alpha,value)
        return value

    if player == -1:
        value = 5000
        for a in actions(state):
            value = min(value,minmax(results(state,a,player),-player,depth,alpha,beta))
            if value<=alpha:
                return value
            beta = min(beta,value)
        return value

def findBestMove(state,depth):
    bestMove = -1
    bestValue = -5000
    for a in actions(state):
        value = minmax(state,1,depth-1,-5000,5000)
        if value>bestValue:
            bestValue = value
            bestMove = a
    return bestMove


def game():
    state = [ 0 , 0 , 0 , 0 , 0 , 0 , 0  , 0 , 0 , 0 , 0 , 0 ,
          0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
          0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
          0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
          0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
          0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ]
    firstPlayerChoice = input('Voulez vous commencer ? [y/n]')
    depth = 5
    if firstPlayerChoice == 'n':
        state = results(state,findBestMove(state,depth),1)
    while True: 
        clearTerminal()
        display(state)
        action = -1
        while action not in actions(state):
            action = int(input('Saissez une acion valide : '))
        state = results(state,action,-1)
        clearTerminal()
        display(state)
        state = results(state,findBestMove(state,depth),1)

game()





     














    

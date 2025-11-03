
def count_wins(dice1, dice2):
    assert len(dice1) == 6 and len(dice2) == 6
    dice1_wins, dice2_wins = 0, 0
    
    # write your code here
    combs = [(x, y) for x in dice1 for y in dice2]
    for x, y in combs:
        if x > y:
            dice1_wins += 1
        elif x < y:
            dice2_wins += 1
    return (dice1_wins, dice2_wins)

def find_the_best_dice(dices):
    assert all(len(dice) == 6 for dice in dices)

    # write your code here
    # use your implementation of count_wins method if necessary
    max_wins = len(dices) - 1
    for i, dice in enumerate(dices):
        wins = 0
        for j, other_dice in enumerate(dices):
            if i != j:
                result = count_wins(dice, other_dice)
                wins += (result[0] > result[1])  # count wins against other dice
        if wins == max_wins:
            return i

    return -1

# Implement a function that takes a list of dices (possibly more than three) and returns a strategy. The strategy is a dictionary:
# If, after analyzing the given list of dices, you decide to choose a dice first, set strategy["choose_first"] to True and set strategy["first_dice"] to be the (0-based) index of the dice you would like to choose
# If you would like to be the second one to choose a dice, set strategy["choose_first"] to False. Then, specify, for each dice that your opponent may take, the dice that you would take in return. Namely, for each i from 0 to len(dices)-1, set strategy[i] to an index j of the dice that you would take if the opponent takes the i-th dice first.
def compute_strategy(dices):
    assert all(len(dice) == 6 for dice in dices)

    strategy = dict()
        
    # write your code here
    decision = find_the_best_dice(dices)
    if decision == -1:
        strategy["choose_first"] = False
        for i in range(len(dices)):
            better_dice = None
            max_wins = -1
            for j in range(len(dices)):
                if i != j:
                    wins = count_wins(dices[i], dices[j])[1]
                    if wins > max_wins:
                        max_wins = wins
                        better_dice = j
                        
            strategy[i] = better_dice
    else:
        strategy["choose_first"] = True
        strategy["first_dice"] = decision

    return strategy



# dice1 = [1, 1, 6, 6, 8, 8]
# dice2 = [2, 2, 4, 4, 9, 9]

# print(count_wins(dice1, dice2))

# dices = [[3, 3, 3, 3, 3, 3], [6, 6, 2, 2, 2, 2], [4, 4, 4, 4, 0, 0], [5, 5, 5, 1, 1, 1]]
# print(find_the_best_dice(dices))

dices = [[4, 4, 4, 4, 0, 0], [7, 7, 3, 3, 3, 3], [6, 6, 2, 2, 2, 2], [5, 5, 5, 1, 1, 1]]
print(compute_strategy(dices))
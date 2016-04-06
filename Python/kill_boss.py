#!/usr/bin/python

args = raw_input()
args = args.split(' ')

hp = int(args[0])
mp = int(args[1])
boss_hp = int(args[2])
# continue
con = True
# round
rd = 0
while con:
    rd += 1
    # if having mp, so just use it
    if mp - 10 >= 0:
        mp -= 10
        boss_hp -= 60
        if boss_hp <= 0:
            break
        hp -= 10
    elif mp < 10 and rd >=5:
        # if having hp, after mp recovered
        # judge mp
        if 0 <= mp < 2 and boss_hp > 51 - 1:
            if rd % 5 == 0 or (rd+1) % 5 == 0 or (rd+2) % 5 == 0:
                big_attack = True
            else:
                big_attack = False
            if big_attack:
                if hp - 30 - 10 * 2 > 0:
                    mp += 4
                    if rd % 5 == 0:
                        hp -= 30
                    else:
                        hp -= 10
                else:
                    boss_hp -= 10
                    if boss_hp <= 0:
                        break
                    hp -= 10
            else:
                # otherwise, select to attack 
                boss_hp -= 10
                if boss_hp <= 0:
                    break
                hp -= 10
        elif 2 <= mp < 6 and boss_hp > 34:
            if rd % 5 == 0 or (rd+1) % 5 == 0:
                big_attack = True
            else:
                big_attack = False
            if big_attack:
                if hp - 30 - 10 > 0:
                    mp += 4
                    if rd % 5 == 0:
                        hp -= 30
                    else:
                        hp -= 10
                else:
                    boss_hp -= 10
                    if boss_hp <= 0:
                        break
                    hp -= 10
            else:
                boss_hp -= 10
                if boss_hp <= 0:
                    break
                hp -= 10
        elif mp >= 6 and boss_hp > 17:
            if rd % 5 == 0:
                big_attack = True
            else:
                big_attack = False
            if big_attack:
                if hp - 30 > 0:
                    mp += 4
                    if rd % 5 == 0:
                        hp -= 30
                    else:
                        hp -= 10
                else:
                    boss_hp -= 10
                    if boss_hp <= 0:
                        break
                    hp -= 10
            else:
                boss_hp -= 10
                if boss_hp <= 0:
                    break
                hp -= 10
        else:
            boss_hp -= 10
            if boss_hp <= 0:
                break
            hp -= 10
    else:
        boss_hp -= 10
        if boss_hp <= 0:
            break
        hp -= 10
    if hp <= 0 or boss_hp <= 0:
        con = False

if hp <= 0:
    print -1
else:
    print rd

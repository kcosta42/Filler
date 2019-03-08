# Filler

Disclaimer
----------
> In School 42, almost every project must be written according to a coding syntax standard (also known as "[Norme](./docs/norme.fr.pdf)").
>
> That's why some parts may be strange

About
-----
>The principle is simple: two players are displayed on a board and must place in turn the centerpiece of the game (provided in the form of a ruby ​​executable). The game stops as soon as nothing has been added to the board. The winner is the one who controls the most space on the board

This is the second project of the Algorithms branch at School 42 Paris

Installation
------------
Run
```
make fclean && make
chmod 755 kcosta.filler
cp kcosta.filler ./resources/players/
cd resources
```

Usage
-----
`./filler_vm -f path [-i | -p1 path | -p2 path] [-s | -q | -t time]`
* -f: use a map file (required)
* -p1: use filler binary as a first player
* -p2: use filler binary as a second player
* -t: set timeout in second
* -q: quiet mode
* -i: interactive mode(default)
* -s: use the seed number (initialization random)

### Example
`./filler_vm -f maps/map00 -p1 players/kcosta.filler -p2 players/abanlin.filler`
```
launched players/kcosta.filler
$$$ exec p1 : [players/kcosta.filler]
launched players/abanlin.filler
$$$ exec p2 : [players/abanlin.filler]
.
.
.
Plateau 15 17:
    01234567890123456
000 XXXXXXXXXXXXXXXX.
001 XXXXXXXXXXXXXXXX.
002 XXXXXXXXXXXXXxXX.
003 XXXXXXXXXXXXXx...
004 .OOOOOX..XX......
005 ....OOXXXXX......
006 .....OOOOXXX.....
007 ...O.OOOOOOXXXO..
008 ..OO.OO.OOOOOXOOO
009 ...OOOOOO..OOXXOO
010 .....OOOOOOOOOXOO
011 ......OO.OOOOOXOO
012 .......O.OOOOXXOO
013 .......OOOOOOOOOO
014 ...........OOOOOO
Piece 1 2:
**
<got (O): [7, 14]
.
.
.
== O fin: 97
== X fin: 65
```

Result can be seen in `filler.trace`
```
> cat filler.trace
seed = 6307
players/kcosta.filler won
Score:
97AGAINST65
```

##### Project done in 2017

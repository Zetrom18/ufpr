from Game import BattleShip as BS

gteste = BS.Grid(5, 5, 1, 1)

print(gteste)

gteste.get_attacked(1,0,0)
gteste.get_attacked(1,0,1)
gteste.get_attacked(1,0,2)

print(gteste.can_play())
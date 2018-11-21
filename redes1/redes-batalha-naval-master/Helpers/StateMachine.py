from Game import BattleShip


class StateMachine:

    def __init__(self):
        self.has_token = False
        self.playing = False
        self.being_attacked = False
        self.has_sunk = False
        self.player = 0
        self.battle = BattleShip.BattleShip
        self.target = 0
        self.pos_x = -1
        self.pos_y = -1

    def check_message(self, message):
        self.has_token = message.is_token
        self.has_sunk = message.is_sank
        self.being_attacked = int(message.target_player) == self.player

    def get_target(self):
        self.target = input("Choose your target (1, 2, 3 ou 4) - remember not to shot yourself !")
        self.pos_x = input("Choose an X position (0 - 5)")
        self.pos_y = input("Choose an Y position (0 - 5)")

    def set_token(self, state):
        self.has_token = state

    def start_playing(self):
        self.player = int(input("Player Number: "))
        self.playing = True
        if self.player == 1:
            self.has_token = True

    def stop_playing(self):
        self.playing = False

    def set_player(self, number):
        self.player = number

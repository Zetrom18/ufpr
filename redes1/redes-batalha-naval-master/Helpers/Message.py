import json


class Message:

    def __init__(self):
        self.is_token = False
        self.is_sank = False
        self.is_connecting = False
        self.target_player = 0
        self.player = 0
        self.pos_x = 0
        self.pos_y = 0

    def is_token(self):
        return self.is_token

    def set_attack(self, states):
        self.target_player = states.target
        self.pos_x = states.pos_x
        self.pos_y = states.pos_y

    def set_sank(self):
        self.is_sank = False

    def set_connecting(self):
        self.is_connecting = True

    def set_token(self):
        self.is_token = True

    def get_dict(self):
        return json.dumps(self.__dict__)

    def set_player(self, player):
        self.player = player

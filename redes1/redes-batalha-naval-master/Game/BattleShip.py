import sys


class BattleShip:

    def __init__(self, board_size, n_ships):
        """
        " Ships will always be 3x1
        " if mode == 0: ships will be filled randomly
        " if mode == 1: player will select each ships placement
        """
        self.board_size = 0
        self.board = []
        self.board = self.start_board(board_size, n_ships, 1)
        # self.player = self.choose_number()

    def print_board(self):
        string = ""
        for i in range(-1,self.board_size+1):
            for j in range(-1,self.board_size+1):
                if i == -1 or i == self.board_size or j == -1 or j == self.board_size:
                    string += "+"
                elif self.board[i][j] == 0:
                    string += " "
                elif self.board[i][j] == -1:
                    string += "X"
                else:
                    string += str(self.board[i][j])
                string += " "
            string += "\n"
        print(string)


    def start_board(self, board_size, n_ships, mode):
        self.board_size = board_size
        for i in range(board_size):
            self.board.append([])
            for j in range(board_size):
                self.board[i].append(0)

        for i in range(n_ships):
            if mode == 0:
                print("Modo em desenvolvimento")
                break
            elif mode == 1:
                while (True):
                    while (True):
                        coord = input("Selecione coordenada inicial do barco %s (ex: 0 0): " % (i + 1)).split()
                        try:
                            initial_x = int(coord[0])
                            initial_y = int(coord[1])
                            if initial_y >= 0 and initial_y < board_size:
                                if initial_x >= 0 and initial_x < board_size:
                                    break
                            print("Coordenada fora do tabuleiro, tente novamente")
                        except:
                            print("Formato incorreto, tente novamente")

                    while (True):
                        possib = []
                        if initial_y + 2 < board_size:
                            possib.append((initial_x, initial_y + 2))
                        if initial_x + 2 < board_size:
                            possib.append((initial_x + 2, initial_y))
                        if initial_y - 2 >= 0:
                            possib.append((initial_x, initial_y - 2))
                        if initial_x - 2 >= 0:
                            possib.append((initial_x - 2, initial_y))
                        print("Agora, selecione a coordenada final do barco %s" % (i + 1))
                        coord = input("(opcoes: %s): " % possib).split()
                        try:
                            final_x = int(coord[0])
                            final_y = int(coord[1])
                            if tuple([final_x, final_y]) in possib:
                                break
                        except:
                            print("Formato incorreto, tente novamente")

                    if self.board[initial_y][initial_x] > 0:
                        pass
                    elif self.board[final_y][final_x] > 0:
                        pass
                    elif self.board[int((initial_y + final_y)/2)][int((initial_x + final_x)/2)] > 0:
                        pass
                    else:
                        self.board[initial_y][initial_x] = i + 1
                        self.board[final_y][final_x] = i + 1
                        self.board[int((initial_y + final_y)/2)][int((initial_x + final_x)/2)] = i + 1
                        break

                    print("Sinto muito, ja existe um navio nesta posicao, tente novamente")

        print("Tabuleiro inicializado, pronto para jogar")

        return self.board

    def find_ship(self, ship, x, y):
        if x+1 < self.board_size and self.board[y][x+1] == ship:
            return True
        if x+2 < self.board_size and self.board[y][x+2] == ship:
            return True

        if x-1 < self.board_size and self.board[y][x-1] == ship:
            return True
        if x-2 < self.board_size and self.board[y][x-2] == ship:
            return True

        if y+1 < self.board_size and self.board[y+1][x] == ship:
            return True
        if y+2 < self.board_size and self.board[y+2][x] == ship:
            return True

        if y-1 < self.board_size and self.board[y-1][x] == ship:
            return True
        if y-2 < self.board_size and self.board[y-2][x] == ship:
            return True

        return False

    def get_attacked(self, player, hit_x, hit_y):
        # print("Voce foi atacado pelo jogador %s" % player)
        print("Nas coordenadas x: %s, y: %s" % (hit_x, hit_y))
        hit = self.board[int(hit_y)][int(hit_x)]
        if hit == 0:
            print("Errou!")
        elif hit == -1:
            print("Atingiu uma area ja atacada, sorte?")
            return -1
        else:
            print("Atingiu o navio %s!" % hit)
            self.board[int(hit_y)][int(hit_x)] = -1
            if not self.find_ship(hit, int(hit_x), int(hit_y)):
                print("Navio %s abatido!" % hit)
                return -2
            return -1
        return 0

    def can_play(self):
        for i in range(len(self.board)):
            for j in range(len(self.board[i])):
                if self.board[i][j] > 0:
                    return True
        return False

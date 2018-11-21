class Grid():

    def __init__ (self, height, width, mode, shipNumb):
        """
        " Ships will always be 3x1
        " if mode == 0: ships will be filled randomly
        " if mode == 1: player will select each ships placement
        """
        grid = []
        for i in range(height):
            grid.append([])
            for j in range(width):
                grid[i].append(0)
        for i in range(shipNumb):
            if mode == 0:
                print("Modo em desenvolvimento")
                break
            elif mode == 1:
                while(True):
                    while(True):
                        coord = raw_input("Selecione coordenada inicial do barco %s (ex: 0 0): " % (i+1)).split()
                        try:
                            initial_x = int(coord[0])
                            initial_y = int(coord[1])
                            if initial_y >= 0 and initial_y <= height:
                                if initial_x >= 0 and initial_x <= width:
                                    break
                            print("Coordenada fora do tabuleiro, tente novamente")
                        except:
                            print("Formato incorreto, tente novamente")
                    while(True):
                        possib = []
                        if initial_y+2 < height:
                            possib.append((initial_x,initial_y+2))
                        if initial_x+2 < width:
                            possib.append((initial_x+2,initial_y))
                        if initial_y-2 >= 0:
                            possib.append((initial_x,initial_y-2))
                        if initial_x-2 >= 0:
                            possib.append((initial_x-2,initial_y))
                        print("Agora, selecione a coordenada final do barco %s" % (i+1))
                        coord = raw_input("(opcoes: %s): " % possib).split()
                        try:
                            final_x = int(coord[0])
                            final_y = int(coord[1])
                            if tuple([final_x,final_y]) in possib:
                                break
                        except:
                            print("Formato incorreto, tente novamente")
                    if grid[initial_y][initial_x] > 0:
                        pass
                    elif grid[final_y][final_x] > 0:
                        pass
                    elif grid[(initial_y+final_y)/2][(initial_x+final_x)/2] > 0:
                        pass
                    else:
                        grid[initial_y][initial_x] = i+1
                        grid[final_y][final_x] = i+1
                        grid[(initial_y+final_y)/2][(initial_x+final_x)/2] = i+1
                        break
                    print("Sinto muito, ja existe um navio nesta posicao, tente novamente")
        print("Tabuleiro inicializado, pronto para jogar")
        self.grid = grid
        self.height = height
        self.width = width

    def find_ship(self, ship, x, y):
        grid = self.grid
        try:
            if grid[y][x+1] == ship:
                return True
            if grid[y][x+2] == ship:
                return True
        except:
            pass
        try:
            if grid[y][x-1] == ship:
                return True
            if grid[y][x-2] == ship:
                return True
        except:
            pass
        try:
            if grid[y+1][x] == ship:
                return True
            if grid[y+2][x] == ship:
                return True
        except:
            pass
        try:
            if grid[y-1][x] == ship:
                return True
            if grid[y-2][x] == ship:
                   return True
        except:
            pass
        return False

    def get_attacked(self, attacker, hit_x, hit_y):
        print("Voce foi atacado pelo jogador %s" % attacker)
        print("Nas coordenadas x: {0}, y: {1}".format(hit_x, hit_y))
        hit = self.grid[hit_y][hit_x]
        if hit == 0:
            print("Errou!")
        elif hit == -1:
            print("Atingiu uma area ja atacada, sorte?")
            # TODO - Checar se retorna 0 ou -1 neste caso
            return -1
        else:
            print("Atingiu o navio %s!" % hit)
            if not self.find_ship(hit, hit_x, hit_y):
                print("Navio %s abatido!" % hit)
                # TODO - Checar se jogador ainda possui navios disponiveis (canPlay), avisar todos os jogadores que o navio foi abatido
            self.grid[hit_y][hit_x] = -1
            return -1
        return 0

    def can_play(self):
        for i in range(len(self.grid)):
            for j in range(len(self.grid[i])):
                if self.grid[i][j] > 0:
                    return True
        # TODO - avisar todos os jogadores que tal jogador perdeu
        return False
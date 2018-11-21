import sys
import getopt
import socket


class Parser:

    def __init__(self, argv):
        self.input = argv
        self.help = '\n\nbatalha.py --hp <hostPort>\n' \
                    '-t <targetAddress> --tp <targetPort>\n' \
                    '-b <board-size (Optional)> -s <number-of-ships (Optional)>\n' \
                    '--help: shows this message'

        self.server_address = socket.gethostname()
        self.server_port = 2420

        self.target_address = socket.gethostname()
        self.target_port = 2421

        self.board_size = 5
        self.number_of_ships = 2

    def parse(self):
        try:
            opts, args = getopt.getopt(self.input, 't:b:s', ['help', 'hp=', 'tp='])
        except getopt.GetoptError:
            print(self.help)
            sys.exit(2)
        for opt, arg in opts:
            if opt == '--help':
                print(self.help)
                sys.exit()
            elif opt in "--hp":
                self.server_port = arg
            elif opt in "-t":
                self.target_address = arg
            elif opt in "--tp":
                self.target_port = arg
            elif opt in "-b":
                print ('-b = ', arg)
                self.board_size = arg
            elif opt in "-s":
                print ('-s = ', arg)
                self.number_of_ships = arg

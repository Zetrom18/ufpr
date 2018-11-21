#!/usr/bin/python

import sys
from Helpers import Parser, Socket, StateMachine, Message
from Game import BattleShip 


def main(argv):

    inp = Parser.Parser(argv)
    inp.parse()

    print('\n\n >> Board size = ' + str(inp.board_size) + 'X' + str(inp.board_size))
    print('\n\n >> ' + str(inp.number_of_ships) + 'Ships of size 23x1')

    socket = Socket.Socket()

    socket.serve(inp.server_port)
    socket.set_next(inp.target_port, inp.target_address)

    states = StateMachine.StateMachine()
    states.start_playing()

    got_message = Message.Message()

    battle = BattleShip.BattleShip(inp.board_size,inp.number_of_ships)

    while states.playing:
        print('\n>>> Play >>>\n')
        battle.print_board()
        if states.has_token:

            # # Choose target
            states.get_target()

            # Sends attack message
            message = Message.Message()
            message.set_attack(states)
            socket.send_message(message)

            # Checks if sank a ship
            got_message.__dict__ = socket.receive_message()
            states.check_message(got_message)

            # Notify everyone by passing the message
            if states.has_sunk:
                print("ship from player " + str(states.player) + "has sunk")
                socket.send_message(got_message)

            # Creates new message with token
            got_message = Message.Message()
            got_message.set_token()

            got_message.set_player(str(states.player))

            # Send message
            socket.send_message(got_message)
            states.set_token(False)

        else:

            # Receives message
            got_message.__dict__ = socket.receive_message()
            states.check_message(got_message)

            # Checks if i'm the one being attacked
            if states.being_attacked:
                print('Got Attacked :C')
                if battle.get_attacked(got_message.player, got_message.pos_x, got_message.pos_y) == -2:
                # if False:
                    got_message.set_sank()

                # If my boat sank, add to the message
                if states.has_sunk:
                    print("ship from player " + str(states.player) + "has sunk")

            # Checks the message is the token
            if not got_message.is_token:
                socket.send_message(got_message)

            # Checks if player is still playing
            if not battle.can_play():
                states.stop_playing()

    # Keep transmitting
    while True:
        message = socket.receive_message()
        socket.send_message(message)


if __name__ == '__main__': 

        main(sys.argv[1:])

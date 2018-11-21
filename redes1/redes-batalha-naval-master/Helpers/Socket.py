import socket
import json


class Socket:

    def __init__(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.settimeout(6)

        self.target_port = 4321
        self.target_address = 'localhost'
        self.target_path = (self.target_address, self.target_port)

        self.server_port = 4322
        self.server_address = 'localhost'
        self.server_path = (self.server_address, self.server_port)

    def serve(self, host_port):
        self.server_port = int(host_port)
        self.server_address = socket.gethostname()

        self.server_path = (self.server_address, self.server_port)

        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind(self.server_path)
        print("UDP: Listening on IP:" + self.server_address + ':' + str(self.server_port))

    def set_next(self, target_port, target_address):

        self.target_port = int(target_port)
        self.target_address = target_address
        self.target_path = (self.target_address, self.target_port)

        print("UDP: Connected to IP:" + self.target_address + ':' + str(self.target_port))

    def receive_message(self):
        data, address = self.sock.recvfrom(1024)  # buffer size is 1024 bytes
        # print('>>>got this data:', data)
        return dict(json.loads(data.decode('utf-8')))

    def send_message(self, message):
        message_dict = message.get_dict()
        # print(">>Sending > > > UDP: Message = " + message_dict +
        #       " >> Target: " + self.target_address + ':' + str(self.target_port))
        return self.sock.sendto(message_dict.encode('utf-8'), self.target_path)

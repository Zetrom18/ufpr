import random
import json

class ModelRepository:

    def __init__(self):
        self.modelos = ["Cascata", "Espiral"]

    def listar(self):
        return self.modelos

    def buscar(self, key):
        return self.modelos[key]

class GameRepository:
    def __init__(self):
        self.cargos = {
            '1': 'Analista',
            '2': 'Projetista',
            '3': 'BD',
            '4': 'Programador',
            '5': 'Testador'
        }

class DescRepository:

    def save(self):
        data = {}
        for proj in self.projs:
            data[proj['nome']] = proj['desc']
        with open("descProj.json", "w") as f:
            f.write(json.dumps(data))

    def __init__(self):
        self.projs = []
        with open("descProj.json", "r") as f:
            data = json.loads(f.read())
            for nome, desc in data.items():
                self.projs.append({"nome": nome, "desc": desc})

    def get_random(self):
        return random.choice(self.projs)

    def newDesc(self, nome, desc):
        self.projs.append({"nome": nome, "desc": desc})
        self.save()

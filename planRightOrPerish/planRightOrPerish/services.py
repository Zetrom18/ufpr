import random
from repositories import ModelRepository
from models import Projeto, Desenvolvedor, Habilidade


class PlayerService:
    def __init__(self):
        self.modelRepo = ModelRepository()
        self.projeto = Projeto()

    def escolhe_modelo(self, indice):
        if indice == "1":
            self.projeto.defineModelo(self.modelRepo.buscar(int(indice) - 1), self.projeto.orcamento)
            return self.projeto.modelo.nome
        else:
            print("Opção não implementada, escolhendo 1")
            self.projeto.defineModelo(self.modelRepo.buscar(0), self.projeto.orcamento)
            return self.projeto.modelo.nome

    def estabelece_cronograma(self, tempoEstimado):
        try:
            self.projeto.estabeleceCronograma(int(tempoEstimado))
        except:
            print("Cronograma invalido, esolhendo 100 dias")
            self.projeto.estabeleceCronograma(100)

    def estabelece_orcamento(self, orcamento):
        try:
            self.projeto.estabeleceOrcamento(float(orcamento))
        except:
            print("Orcamento invalido, esolhendo 10.000 BitCruzadosReais")
            self.projeto.estabeleceOrcamento(10000.0)

    def define_etapa(self):
        try:
            self.etapaAtual = self.projeto.iniciaEtapa()
        except:
            print("Erro ao definir etapa")

    def gera_desenvolvedores(self, cargos, range_salario, max_salario):
        desvio = 20
        desenvs = []
        for i in range(3):
            salario = float(random.choice(range(range_salario[0], range_salario[1])))
            nivel = int(100 - ((max_salario - salario) / 100))
            habilidades = []
            for key, cargo in cargos.items():
                habilidades.append(Habilidade(cargo, random.choice(range(max(nivel-desvio,0), min(nivel+desvio,101)))))
            desenvs.append(Desenvolvedor(salario, habilidades))
        return desenvs

    def contrata_desenvolvedor(self, novo_desenvolvedor, cargo):
        try:
            novo_desenvolvedor.setCargo(cargo)
            self.projeto.desenvolvedores.append(novo_desenvolvedor)
            print('{} contratado como {} nível {}. salario: {} BCZ$'.format(novo_desenvolvedor.nome,
                                                                           novo_desenvolvedor.cargo.nome,
                                                                           novo_desenvolvedor.cargo.nivel,
                                                                           novo_desenvolvedor.salario))
        except Exception as ex:
            print("Erro ao contratar desenvolvedor")
            print(str(ex))

    def demite_desenvolvedor(self, id):
        try:
            del self.projeto.desenvolvedores[int(id)]
        except Exception as ex:
            print("Erro ao demitir desenvolvedor - id invalido")
            print(str(ex))


# class GameService:
#     def __init__(self):
#

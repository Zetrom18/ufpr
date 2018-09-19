from random import randint


class Projeto():

    def setListaDesenvolvedor(self, ld):
        self.desenvolvedores = ld

    def defineModelo(self, modelo, orcamento):
        self.modelo = ModeloCicloVida(modelo, orcamento)

    def getDesenvolvedor(self, id):
        if type(id) == type(0):
            return self.desenvolvedores[id]
        for dev in self.desenvolvedores:
            if id == dev.nome:
                return dev
        return None

    def iniciaEtapa(self):
        return self.modelo.etapas[self.modelo.proxEtapa()]

    def estabeleceCronograma(self, tempoEstimado):
        self.cronograma = Cronograma(tempoEstimado)

    def estabeleceOrcamento(self, orcamento):
        self.orcamento = orcamento

    def finalizaDia(self):
        self.cronograma.atualizaTempoGasto()
        self.modelo.etapas[self.modelo.etapaAtiva].finalizaDia()

    def modificaAtividades(self):
        pass

    def __init__(self):
        self.nome = ""
        self.orcamento = 0.0
        self.caixa = 0
        self.descricao = ""
        self.desenvolvedores = []


class Etapa():
    def criaAtividade(self, desc, custo, dev):
        at = Atividade(desc, custo)
        dev.associaAtividade(at)
        self.listaAtividades.append(at)

    def getListaAtividades(self):
        return self.listaAtividades

    def finalizaDia(self):
        self.cronograma.atualizaTempoGasto()

    def modificaAtividades(self, atividade, **kwargs):
        if "descricao" in kwargs:
            atividade.descricao = kwargs['descricao']
        if "custo" in kwargs:
            atividade.custo = kwargs['custo']

    def __init__(self, nome, descricao, orcamento):
        self.nome = nome
        self.descricao = descricao
        self.orcamento = orcamento
        self.listaAtividades = []


class Desenvolvedor():
    def associaAtividade(self, atividade):
        self.atividades.append(atividade)

    def getHabilidade(self, id):
        if type(id) == type(0):
            return self.habilidades[id]
        for hbl in self.habilidades:
            if id == hbl.nome:
                return hbl
        return None

    def setCargo(self, cargo):
        self.cargo = self.getHabilidade(cargo)

    def __init__(self, salario, habilidades):
        self.nome = "Juca" + str(randint(0, 100))
        self.atividades = []
        self.salario = salario
        self.habilidades = habilidades


class Atividade():
    def __init__(self, desc, custo):
        self.descricao = desc
        self.custo = custo


class ModeloCicloVida():
    def proxEtapa(self):
        if self.etapaAtiva is None:
            self.etapaAtiva = 0
        else:
            self.etapaAtiva += 1
        return self.etapaAtiva

    def __init__(self, nome, orcamento):
        self.nome = nome
        self.etapas = []
        if self.nome == "Cascata":
            self.etapas.append(Etapa("Requisitos", "Nesta fase, são estabelecidos os requisitos do produto que o idealizador almeja desenvolver, o que normalmente se baseia nos serviços que precisam ser fornecidos, nas limitações aceitáveis e os objetivos do software.", orcamento/5))
            self.etapas.append(Etapa("Projeto", "O projeto de elaboração do sistema é composto por vários processos que se centralizam em quatro atributos diferentes do sistema, sendo: a estrutura de dados, a arquitetura do software, caracterização das interfaces e detalhes procedimentais.", orcamento/5))
            self.etapas.append(Etapa("Implementação", "A etapa de implementação é quando os programas são criados. Caso o projeto tenha um nível de detalhamento mais avançado, a etapa de codificação pode ser implementada de maneira automática.", orcamento/5))
            self.etapas.append(Etapa("Teste", "Após o fim da etapa de codificação, inicia-se a fase da realização de teste do sistema. Este processo de teste é focado em dois pontos principais, que são as lógicas internas do software e as suas funcionalidades externas.", orcamento/5))
            self.etapas.append(Etapa("Manutenção", "A fase da manutenção se baseia na correção de erros que não detectados durante os testes, em melhorias funcionais e de preferência com os demais tipos de suporte. Esta etapa faz parte do ciclo de vida do produto de software e não pertence apenas ao seu desenvolvimento. As melhorias e alterações para correções do software podem ser classificadas como parte do processo de desenvolvimento.", orcamento/5))
        self.etapaAtiva = None


class Cronograma():
    def atualizaTempoGasto(self):
        pass

    def __init__(self,tempoEstimado):
        self.tempoEstimado = tempoEstimado
        self.progresso = 0
        self.tempoGasto = 0


class Habilidade():
    def __init__(self, nome, nivel):
        self.nome = nome
        self.nivel = nivel

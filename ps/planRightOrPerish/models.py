import random


class Projeto():

    def setListaDesenvolvedor(self, ld):
        self.desenvolvedores = ld

    def defineModelo(self, modelo, orcamento):
        self.modelo = ModeloCicloVida(modelo, orcamento, self.cronograma.tempoEstimado)

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
        return self.modelo.etapas[self.modelo.etapaAtiva].finalizaDia(self.desenvolvedores)

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

    def geraRelatorio(self, devs):
        relatorio = []
        for dev in devs:
            relatorio.append({"dev": dev, "relatorio": dev.geraRelatorio()})
        return relatorio

    def finalizaDia(self, devs):
        self.cronograma.atualizaTempoGasto()
        return self.geraRelatorio(devs)

    def modificaAtividades(self, atividade, **kwargs):
        if "descricao" in kwargs:
            atividade.descricao = kwargs['descricao']
        if "custo" in kwargs:
            atividade.custo = kwargs['custo']

    def __init__(self, nome, descricao, orcamento, cronograma):
        self.nome = nome
        self.descricao = descricao
        self.orcamento = orcamento
        self.cronograma = Cronograma(cronograma)
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

    def calculaRendimento(self):
        options = [100]*50 + [70]*50 + [50]*20 + [0]*5 + [1]*10
        return random.choice(options)

    def geraProdutividade(self):
        prod = self.calculaRendimento()
        if prod == 70:
            self.relatorio.append("Está tendo mal dia")
        elif prod == 50:
            self.relatorio.append("Em treinamento")
        elif prod == 0:
            self.relatorio.append("Computador quebrou")
        elif prod == 1:
            self.relatorio.append("Se demitiu")
            self.demitido = True
        return prod

    def geraRelatorio(self):
        if self.demitido: 
            return self.relatorio

        prod = self.cargo.nivel*self.produtividade/100
        i = 0
        while prod > 0 and len(self.atividades) > 0:
            if prod > self.atividades[i].dificuldade:
                prod -= self.atividades[i].dificuldade
                # adiciona que terminou a atividade ao relatorio e remove atividade da lista
                self.relatorio.append("Atividade {} foi finalizada".format(self.atividades.pop(i).descricao))
            else:
                self.atividades[i].dificuldade -= prod
                prod = 0
                i += 1
        self.produtividade = self.geraProdutividade()
        return self.relatorio



    def __init__(self, salario, habilidades):
        self.nome = "Juca" + str(random.randint(0, 100))
        self.atividades = []
        self.salario = salario
        self.habilidades = habilidades
        self.produtividade = 100
        self.relatorio = []
        self.demitido = False


class Atividade():
    def __init__(self, desc, dificuldade):
        self.descricao = desc
        self.dificuldade = dificuldade # Quantidade de pontos necessarios para completar a atividade


class ModeloCicloVida():
    def existeProxima(self):
        if self.etapaAtiva is None:
            return True
        try:
            self.etapas[self.etapaAtiva + 1]
            return True
        except:  
            return False

    def proxEtapa(self):
        if self.etapaAtiva is None:
            self.etapaAtiva = 0
        else:
            self.etapaAtiva += 1
        return self.etapaAtiva

    def __init__(self, nome, orcamento, cronograma):
        self.nome = nome
        self.etapas = []
        if self.nome == "Cascata":
            self.etapas.append(Etapa("Requisitos", "Nesta fase, são estabelecidos os requisitos do produto que o idealizador almeja desenvolver, o que normalmente se baseia nos serviços que precisam ser fornecidos, nas limitações aceitáveis e os objetivos do software.", orcamento/5, cronograma/5))
            self.etapas.append(Etapa("Projeto", "O projeto de elaboração do sistema é composto por vários processos que se centralizam em quatro atributos diferentes do sistema, sendo: a estrutura de dados, a arquitetura do software, caracterização das interfaces e detalhes procedimentais.", orcamento/5, cronograma/5))
            self.etapas.append(Etapa("Implementação", "A etapa de implementação é quando os programas são criados. Caso o projeto tenha um nível de detalhamento mais avançado, a etapa de codificação pode ser implementada de maneira automática.", orcamento/5, cronograma/5))
            self.etapas.append(Etapa("Teste", "Após o fim da etapa de codificação, inicia-se a fase da realização de teste do sistema. Este processo de teste é focado em dois pontos principais, que são as lógicas internas do software e as suas funcionalidades externas.", orcamento/5, cronograma/5))
            self.etapas.append(Etapa("Manutenção", "A fase da manutenção se baseia na correção de erros que não detectados durante os testes, em melhorias funcionais e de preferência com os demais tipos de suporte. Esta etapa faz parte do ciclo de vida do produto de software e não pertence apenas ao seu desenvolvimento. As melhorias e alterações para correções do software podem ser classificadas como parte do processo de desenvolvimento.", orcamento/5, cronograma/5))
        self.etapaAtiva = None


class Cronograma():
    def atualizaTempoGasto(self):
        self.tempoGasto += 1
        if self.tempoGasto > self.tempoEstimado:
            return 1
        return 0

    def __init__(self, tempoEstimado):
        self.tempoEstimado = tempoEstimado
        self.progresso = 0
        self.tempoGasto = 0


class Habilidade():
    def __init__(self, nome, nivel):
        self.nome = nome
        self.nivel = nivel # Quantidade de pontos produzidos por dia para a finalização de atividades

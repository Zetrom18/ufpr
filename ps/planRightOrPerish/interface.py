from controle import Controle
from repositories import DescRepository, GameRepository


class Interface:

    #=======================================================================#
    #=============================TELAS=====================================#
    def menuInicial(self):
        # print("\033[H\033[J")
        print('\t#==================================================#')
        print('\t#=============# Plan Right or Perish #=============#')
        print('\t#==================================================#')
        print('\t#====================#  Menu  #====================#')
        print('\t#==================================================#')
        print('\t#                                                  #')
        print('\t#                  1. Iniciar Jogo                 #')
        print('\t#                  2. Configuracoes                #')
        print('\t#                  3. Creditos                     #')
        print('\t#                  4. Sair                         #')
        print('\t#                                                  #')
        print('\t#==================================================#')
        print('\n')

    def menuConfiguracoes(self):
        # print("\033[H\033[J")
        print('\t#==================================================#')
        print('\t#=============# Plan Right or Perish #=============#')
        print('\t#==================================================#')
        print('\t#================# Configuracoes #=================#')
        print('\t#==================================================#')
        print('\t#                                                  #')
        print('\t#  1. Inserir Descricao de Projeto                 #')
        print('\t#  2. Inserir Modelos de Ciclo de Vida             #')
        print('\t#  3. Voltar                                       #')
        print('\t#                                                  #')
        print('\t#==================================================#')
        print('\t#==================================================#')
        print('\n')

    def menuCreditos(self):
        # print("\033[H\033[J")
        print('\t#==================================================#')
        print('\t#=============# Plan Right or Perish #=============#')
        print('\t#==================================================#')
        print('\t#===================# Creditos #===================#')
        print('\t#==================================================#')
        print('\t#                                                  #')
        print('\t#                   Lucas Rosa                     #')
        print('\t#                    Luiz Baroni                   #')
        print('\t#                 Gabriel Carraro                  #')
        print('\t#                                                  #')
        print('\t#  1. Voltar                                       #')
        print('\t#==================================================#')
        print('\n')

    def visualizaDescricao(self):
        proj = self.descRepo.get_random()
        # print("\033[H\033[J")
        print('\t#==================================================#')
        print('\t#=============# Plan Right or Perish #=============#')
        print('\t#==================================================#')
        print('\t#=============# '+proj['nome']+' #=============#')
        print('\t#==================================================#')
        print('\t#  '+proj['desc']+'  #')
        print('\t#  1. Proximo                                      #')
        print('\t#==================================================#')

    def menuProjeto(self):
        # print("\033[H\033[J")
        print('\t#==================================================#')
        print('\t#=============# Plan Right or Perish #=============#')
        print('\t#==================================================#')
        print('\t#====================# Projeto #===================#')
        print('\t#==================================================#')
        print('\t#                                                  #')
        print('\t#  1. Estabelecer Orcamento                        #')
        print('\t#  2. Estabelecer Cronograma                       #')
        print('\t#  3. Escolher Modelo de Ciclo de Vida             #')
        print('\t#  4. Iniciar Etapas                               #')
        print('\t#  5. Voltar                                       #')
        print('\t#                                                  #')
        print('\t#==================================================#')
        print('\t#==================================================#')
        print('\n')

    def estabeleceCronograma(self):
        # print("\033[H\033[J")
        print('\t#==================================================#')
        print('\t#=============# Plan Right or Perish #=============#')
        print('\t#==================================================#')
        print('\t#==================# Cronograma #==================#')
        print('\t#==================================================#')
        print('\t#                                                  #')
        print('\t#  1. Definir Cronograma do Projeto                #')
        print('\t#  2. Voltar                                       #')
        print('\t#                                                  #')
        print('\t#==================================================#')
        print('\t#==================================================#')
        print('\n')

    def imprimeModelos(self):
        # print("\033[H\033[J")
        print('\t#==================================================#')
        print('\t#=============# Plan Right or Perish #=============#')
        print('\t#==================================================#')
        print('\t#====================# Modelos #===================#')
        print('\t#==================================================#')
        print('\t#                                                  #')
        print('\t#  1. Modelo em Cascata                            #')
        print('\t#  2. Modelo Espiral                               #')
        print('\t#  3. Voltar                                       #')
        print('\t#                                                  #')
        print('\t#                                                  #')
        print('\t#==================================================#')
        print('\t#==================================================#')
        print('\n')

    def estabeleceOrcamento(self):
        # print("\033[H\033[J")
        print('\t#==================================================#')
        print('\t#=============# Plan Right or Perish #=============#')
        print('\t#==================================================#')
        print('\t#==================# Orcamento #===================#')
        print('\t#==================================================#')
        print('\t#                                                  #')
        print('\t#  1. Definir Orcamento do Projeto                 #')
        print('\t#  2. Voltar                                       #')
        print('\t#                                                  #')
        print('\t#==================================================#')
        print('\t#==================================================#')
        print('\n')

    def inicioEtapa(self):
        # print("\033[H\033[J")
        print('\t#==================================================#')
        print('\t#=============# Plan Right or Perish #=============#')
        print('\t#==================================================#')
        print('\t#====================# Etapa #=====================#')
        print('\t#==================================================#')
        print('\t#                                                  #')
        print('\t#  1. Definir Desenolvedores                       #')
        print('\t#  2. Definir Atividades da Etapa                  #')
        print('\t#  3. Comecar Etapa                                #')
        print('\t#                                                  #')
        print('\t#==================================================#')
        print('\t#==================================================#')
        print('\n')

    def defineAtividades(self):
        # print("\033[H\033[J")
        print('\t#==================================================#')
        print('\t#=============# Plan Right or Perish #=============#')
        print('\t#==================================================#')
        print('\t#=============# Atividades da Etapa #==============#')
        print('\t#==================================================#')
        print('\t#                                                  #')
        print('\t#  1. Criar Atividade da Etapa                     #')
        print('\t#  2. Voltar                                       #')
        print('\t#                                                  #')
        print('\t#==================================================#')
        print('\t#==================================================#')
        print('\n')

    def defineDesenvolvedores(self):
        # print("\033[H\033[J")
        print('\t#==================================================#')
        print('\t#=============# Plan Right or Perish #=============#')
        print('\t#==================================================#')
        print('\t#============# Definir Desenvolvedor #=============#')
        print('\t#==================================================#')
        print('\t#                                                  #')
        print('\t#  1. Contratar Desenolvedor                       #')
        print('\t#  2. Demitir Desenolvedor                         #')
        print('\t#  3. Voltar                                       #')
        print('\t#                                                  #')
        print('\t#==================================================#')
        print('\t#==================================================#')
        print('\n')

    def imprimeDesenvolvedores(self):
        # print("\033[H\033[J")
        print('\t#==================================================#')
        print('\t#=============# Plan Right or Perish #=============#')
        print('\t#==================================================#')
        print('\t#===================== Equipe =====================#')
        print('\t#==================================================#')
        for id, p in enumerate(self.controle.projeto.desenvolvedores):
            print("{} nome: {}\n\t cargo: {}\n\t salario: BCZ$ {:.2f} \n\t nivel: {}\n".format(id, p.nome, p.cargo.nome, float(p.salario),
                                                                                   p.cargo.nivel))

    def resumoDia(self, relatorio):
        # print("\033[H\033[J")
        print('\t#==================================================#')
        print('\t#=============# Plan Right or Perish #=============#')
        print('\t#==================================================#')
        print('\t#===============# Resumo do dia %d #===============#')
        print('\t#==================================================#')

        for id, relatorio in enumerate(relatorio):
            print("{} nome: {}\n\t relatorio:\n".format(id, relatorio["dev"].nome))
            for id, evento in enumerate(relatorio["relatorio"]):
                print("{} - {}".format(id, evento))
                

    def opcoes(self):
        print("Opcoes: \n\t1 - Definir desenvolvedores\n\t2 - Definir atividades\n\t3 - Finalizar dia\n\t4 - Comecar proxima etapa")

    #=======================================================================#
    #=======================================================================#

    def comecarEtapa(self):
        a=1
        self.resumoDia(self.controle.finaliza_dia())

        while a:
            self.opcoes()
            a=input("\n\t#=========# O que gostaria de fazer? #=============#\n\n")
            if a=="1": #Definir devs
                self.desenvolvedores()
            elif a=="2": #Definir ativs
                self.atividades()
            elif a == "3":#Finaliza dia
                self.resumoDia(self.controle.finaliza_dia())
            elif a == "4":#Nova etapa
                if self.controle.define_etapa():
                    return self.comecarEtapa()
                return 0

    def desenvolvedores(self):
        a=1
        while a:
            self.defineDesenvolvedores()
            a=input("\n\t#=========# O que gostaria de fazer? #=============#\n\n")
            if a=="1": #contrata
                self.imprimeDesenvolvedores()

                range_salario = (500, 5000)

                print("\n\t#========# Escolha variação de salário a ser pago \n"
                                "Desenvolvedores disponíveis disponiveis no mercado com salarios \n"
                                "entre {:.2f} BCZ$ {:.2f} BCZ$) ".format(range_salario[0], range_salario[1]))

                x = max(int(input("\n#========# Salário mínimo\n")), 500)

                y = min(int(input("\n#========# Salário máximo\n")), 5000)

                opcoes = self.controle.gera_desenvolvedores(self.gameRepo.cargos, (x,y), range_salario[1])

                for i, op in enumerate(opcoes):
                    print("\nDesenvolvedor {}: ".format(i))
                    print("\tNome: {}\n\tSalários: {}\n\tHablidades: ".format(op.nome, op.salario))
                    for hbl in op.habilidades:
                        print("\t\t{}: nivel {}".format(hbl.nome, hbl.nivel))

                desenvId = int(input("#========# Selecione o id do desenvolvedor desejado\n"))

                mensagem = "\n\t#========# Escolha o cargo: \n"
                for numero, cargo in self.gameRepo.cargos.items():
                    mensagem += "{} - {}\n".format(numero, cargo)
                cargo = self.gameRepo.cargos[input(mensagem)]

                self.controle.contrata_desenvolvedor(opcoes[desenvId], cargo)

            elif a=="2": #Demite
                self.imprimeDesenvolvedores()
                id_demitir = input("\n\t#========# Escolha o id do desenvolvedor a ser demitido \n")
                self.controle.demite_desenvolvedor(id_demitir)
                self.imprimeDesenvolvedores()


            elif a=="3": #volta
                return

    def atividades(self):
        a=1
        while a:
            self.defineAtividades()
            a=input("\n\t#=========# O que gostaria de fazer? #=============#\n\n")
            if a=="1": #lista de atividades
                self.imprimeDesenvolvedores()

                id_adicionar = int(input("\n\t#========# Escolha o id do desenvolvedor a receber nova atividade \n"))
                dev = self.controle.projeto.getDesenvolvedor(id_adicionar)

                descricao = input("\n\t#========# Descreva a atividade #========#\n\n")
                try:
                    dificuldade = int(input("\n\t#========# Defina a dificuldade da atividade #========#\n\n"))
                except:
                    print("Valor não permitido, definindo dificuldade 15")
                    dificuldade = 15

                self.controle.etapaAtual.criaAtividade(descricao, dificuldade, dev)
                print('Atividade criada: desc: {} \n\t dificuldade: {} '.format(descricao,dificuldade))

            elif a=="2": #volta
                return

    def etapa(self):
        a=1
        while a:
            self.inicioEtapa()
            self.controle.define_etapa()
            a=input("\n\t#=========# O que gostaria de fazer? #=============#\n\n")
            if a=="1": #define Desenvolvedores
                self.desenvolvedores()
            elif a=="2": #define atividades
                self.atividades()
            elif a=='3': #comecar
                return self.comecarEtapa()
            elif a=='4': #volta
                return

    def modelo(self):
        a=1
        while a:
            self.imprimeModelos()
            a = input("\n\t#======# Qual modelo voce deseja utilizar? #=======#\n\n")
            if a == 3:
                return
            self.controle.escolhe_modelo(a)
            a = False

    def orcamento(self):
        a=1
        while a:
            self.estabeleceOrcamento()
            a = input("\n\t#=========# O que gostaria de fazer? #=============#\n\n")
            if a=="1": #define o cronograma
                self.controle.estabelece_orcamento(input("\n\t#========# Qual o orçamento do projeto em BitCruzadosReais? #========#\n\n"))
                print('')
            elif a=="2": #volta
                return


    def cronograma(self):
        a=1
        while a:
            self.estabeleceCronograma()
            a = input("\n\t#=========# O que gostaria de fazer? #=============#\n\n")
            if a=="1": #define o cronograma
                self.controle.estabelece_cronograma(input("\n\t#========# Qual o cronograma do projeto em dias? #========#\n\n"))
                print('')
            elif a=="2": #volta
                return


    def projeto(self):
        a=1
        while a:
            self.menuProjeto()
            a = input("\n\t#=========# O que gostaria de fazer? #=============#\n\n")
            if a=="1": #Estabelece Orcamento
                self.orcamento()
            elif a=="2": #Estabelece Cronograma
                self.cronograma()
            elif a=="3": #Escolhe Modelo de Ciclo de Vida
                self.modelo()
            elif a=="4": #Iniciar Etapas
                return self.etapa()
            elif a=="5": #Voltar
                return

    def creditos(self):
        a=1
        while a:
            self.menuCreditos()
            a = input("\n\t#=========# O que gostaria de fazer? #=============#\n\n")
            if a=="1": #Voltar
                return

    def configuracoes(self):
        a=1
        while a:
            self.menuConfiguracoes()
            a = input("\n\t#=========# O que gostaria de fazer? #=============#\n\n")
            if a=="1":#Inserir descricao de projeto
                print('Insere projeto')
                nome = input("\n\t#======# Qual o nome do projeto a ser adicionado? #=======#\n\n")
                desc = input("\n\t#======# Descrição do projeto #=======#\n\n")
                self.descRepo.newDesc(nome, desc)

            elif a=="2":#Inserir modelos de ciclo de vida
                print('Insere modelos')

            elif a=="3": #Voltar
                return

            elif a !="":
                print("\n Not Valid Choice Try again")

    def inicia(self):
        a=1
        while a:
            self.visualizaDescricao()
            a = input("\n\t#=========# O que gostaria de fazer? #=============#\n\n")
            if a=="1": #Proximo
                return self.projeto()

    def __init__(self):
        #=======================================================================#
        #===========================MAIN========================================#
        ans=True
        self.descRepo = DescRepository()
        self.gameRepo = GameRepository()
        self.controle = Controle()
        while ans:
            self.menuInicial()
            ans=input("\n\t#=========# O que gostaria de fazer? #=============#\n\n")
            if ans=="1":#Iniciar Jogo
                if self.inicia() == 0:
                    print("PARABENS!!!!")
                else:
                    print("YOU PERISHED")

            elif ans=="2":#Configuracoes
                self.configuracoes()

            elif ans=="3": #Creditos
                self.creditos()

            elif ans=="4": #Sair
                print("\n\t#===================#  Adeus!  #===================#\n")
                break
            elif ans !="":
                print("\n Not Valid Choice Try again")


Interface()

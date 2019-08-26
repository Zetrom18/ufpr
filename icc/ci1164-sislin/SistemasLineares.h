#ifndef __SISLINEAR_H__
#define __SISLINEAR_H__

// Parâmetros para teste de convergência
#define MAXIT 100       // Número máximo de iterações antes de abortar os métodos iterativos
#define EPS 1.0e-4

#define COEF_MAX 32.0

typedef float real_t;   // Tipo de dados que pode ser alterado em tempo de compilação para float ou double

typedef struct {
  real_t *A;            // Coeficientes (acessar posição [i][j] com [i*n+j])
  real_t *b;            // Termos independentes
  unsigned int n;       // Tamanho do SL
} SistLinear_t;         // Estrutura para definição/armazenamento dos coeficientes, termos independentes e solução do Sistema Linear

typedef enum {
    comSolucao = 0,
    eqNula,
    eqProporcional,
    eqCombLinear,
    hilbert,
    diagDominante,
} tipoSistLinear_t;     // Lista para indicar o tipo de SL a ser gerado pela função inicializaSistLinear()

// Alocaçao e desalocação de memória
SistLinear_t* alocaSistLinear (unsigned int n);
void liberaSistLinear (SistLinear_t *SL);
void inicializaSistLinear (SistLinear_t *SL, tipoSistLinear_t tipo, real_t coef_max);

// Leitura e impressão de sistemas lineares
SistLinear_t *lerSistLinear ();
void prnSistLinear (SistLinear_t *SL);
void prnVetor (real_t *vet, unsigned int n);

// Calcula a normaL2 do resíduo
real_t normaL2Residuo(SistLinear_t *SL, real_t *x);

// Método da Eliminação de Gauss
int eliminacaoGauss (SistLinear_t *SL, real_t *x, int pivotamento);

// Método de Gauss-Jacobi
int gaussJacobi (SistLinear_t *SL, real_t *x, real_t erro);

// Método de Gauss-Seidel
int gaussSeidel (SistLinear_t *SL, real_t *x, real_t erro);

#endif // __SISLINEAR_H__


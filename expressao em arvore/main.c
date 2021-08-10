//====================================================================
///Integrantes:
///Ian Maeda,
///Joao Pedro C. Zanholo,
///Julia de Miranda Gomes,
///Rafael A. Dorta.
//====================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PILHA_FILA.h"
#define TAM 30

//====================================================================
/// Estrutura do no da arvore
typedef struct Arvore
{
    char info;
    struct Arvore *esq;
    struct Arvore *dir;
}Arv;
//====================================================================

//====================================================================
/// Estrutura que aponta para a raiz da arvore
typedef struct BaseArv
{
    Arv *raiz;
}BArv;
//====================================================================

//====================================================================
/// Cria a arvore
BArv *CriaArvore()
{
    BArv *aux;
    aux = (BArv*)malloc(sizeof(BArv));
    aux->raiz=NULL;
    return aux;
}
//====================================================================

//====================================================================
/// Checa a prioridade dos operadores
int Checa2(char op)
{
    if(op == '*' || op == '/')
        return 1;
    if(op == '+' || op == '-')
        return 0;
}
//====================================================================

//====================================================================
/// Checa se o caracter é operador
int Checa_op(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return 1;
    return 0;
}
//====================================================================

//====================================================================
/// Organiza a equacao digitada pelo usuario, para facilitar o uso da pilha ao inserir na arvore
void organiza(char strg_1[], char strg_2[])
{
	int i, j;
	char item;
	char x;

	Pilha *aux = CriaPilha();

	push(aux,'(');
	strcat(strg_1,")");

	i=0;
	j=0;

	for(i=0; i<strlen(strg_1); i++)
    {
        item = strg_1[i];
		if(item == '(')
            push(aux,item);
		else
        {
            if(item!= '+' && item != '-' && item != '*' && item != '/' && item != '(' && item != ')')
            {
                strg_2[j] = item;
                j++;
            }
            else
            {
                if(Checa_op(item) == 1)
                {
                    x = pop(aux);
                    while(Checa_op(x) == 1 && Checa2(x)>= Checa2(item))
                    {
                        strg_2[j] = x;
                        j++;
                        x = pop(aux);
                    }
                    push(aux,x);
                    push(aux,item);
                }
                else
                {
                    if(item == ')')
                    {
                        x = pop(aux);
                        while(x != '(')
                        {
                            strg_2[j] = x;
                            j++;
                            x = pop(aux);
                        }
                    }
                }
            }
		}
	}
	strg_2[j] = '\0';
}
//====================================================================

//====================================================================
/// Funcao auxiliar da insere_arvore. Tem a funcao de comparar os operandos com os operadores para separar, e assim montar a Arvore
Arv* aux_insere(Arv *no,char valor[])
{
    Pilha *aux;
    aux = CriaPilha();

    for(int i=0;valor[i]!= '\0';i++)
    {
        Arv *novo=(Arv*)malloc (sizeof(Arv));
        novo->info = valor[i];

        if(valor[i] != '+' && valor[i] != '-' && valor[i] != '*' && valor[i] != '/' )
        {
            novo->dir = NULL;
            novo->esq = NULL;
            push(aux,novo);
        }
        else
        {
            novo->dir = pop(aux);
            novo->esq = pop(aux);
            push(aux,novo);
        }
    }
    return pop(aux);
}
//====================================================================

//====================================================================
/// Funcao principal da insercao. Chama a funcao aux para cada caracter da equacao
void insere_arvore(BArv *base, char valor[])
{
    base->raiz=aux_insere(base->raiz,valor);
}
//====================================================================

//====================================================================
/// Funcao para contar quantos niveis tem a arvore
int altura(Arv* no)
{
    if (no==NULL)
        return 0;
    else
    {
        int alturaesq = altura(no->esq);
        int alturadir = altura(no->dir);

        if (alturaesq > alturadir)
            return(alturaesq+1);
        else
            return(alturadir+1);
    }
}
//====================================================================

//====================================================================
/// Percorre a arvore mandando os filhos da esquerda ou direita para a função imprime_nivel
void imprime_nivel_aux(Arv* no, int nivel)
{
    if (no == NULL)
        return;
    if (nivel == 1)
        printf("%c ", no->info);
    else
        if (nivel > 1)
        {
            imprime_nivel_aux(no->esq, nivel-1);
            imprime_nivel_aux(no->dir, nivel-1);
        }
}
//====================================================================

//====================================================================
/// Imprime as informações dos niveis de acordo com a arvore
void imprime_nivel(Arv* no)
{
    int h = altura(no);
    int i;
    for (i=1; i<=h; i++)
    {
        printf("Nivel %d :", i-1);
        imprime_nivel_aux(no, i);
        printf("\n");
    }
}
//====================================================================

int main()
{
    ///cria a arvore
    BArv *base=CriaArvore();;
    char exp[TAM],exp2[TAM];

    ///expressao que sera digitada pelo usuario sem espacos
    printf("Digite a express\306o (n\306o aperte espa\207os entre os caracteres): ");
    gets(exp);

    ///chama função organiza
    organiza(exp,exp2);

    ///chama a função insere
    insere_arvore(base,exp2);
    printf("\n\n\nArvore:\n\n");

    ///imprime os niveis da arvore
    imprime_nivel(base->raiz);

    return 0;
}

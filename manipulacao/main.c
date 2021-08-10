//João Zanholo 20039822
//Júlia Miranda 20052387
//Lais Lahoud 18091967
//Lucas Brito 20118154
//Rafael Dorta 20032256
#include <stdio.h>
#include <stdlib.h>

typedef struct Arvore{
    int info;
   struct Arvore *esq;
   struct Arvore *dir;
}Arv;

typedef struct BArv{
    Arv *raiz;
}BArv;

BArv *CriaArvore(){
    BArv *aux;
    aux = (BArv*)malloc(sizeof(BArv));
    aux->raiz = NULL;
    return aux;
}
//====================================================================

//====================================================================
int busca(Arv *raiz, int cod)
{
    if(raiz!=NULL)
    {
        if(raiz->info == cod)
            return 1;
        else
        {
            if(cod > raiz->info)
                return busca(raiz->dir, cod);
            else
                return busca(raiz->esq, cod);
        }
    }
    return 0;
}
//====================================================================

//====================================================================
Arv* aux_insere(Arv *no, int valor)
{
    int flag;
    Arv *Pai;
    Arv *novo= (Arv*)malloc(sizeof(Arv));
    novo->info=valor;
    novo->esq=NULL;
    novo->dir=NULL;
    if(no==NULL)
        return novo;

    else
    {
        Pai=no;
        flag=0;
        while(flag==0)
        {
            if(Pai->info < valor)
            {
                if(Pai->dir==NULL)
                {
                    Pai->dir=novo;
                    flag=1;
                }
                else
                    Pai=Pai->dir;
            }
            else
            {
                if(Pai->info > valor)
                {
                    if(Pai->esq==NULL)
                    {
                        Pai->esq=novo;
                        flag=1;
                    }
                    else
                        Pai=Pai->esq;

                }
            }
        }
    }
    return no;
}
//====================================================================

//====================================================================
void insere_arvore(BArv *base)
{
    int i=1, valor;
    while(i==1)
    {
        printf("Digite um n\243mero para inserir: ");
        scanf("%d", &valor);
        if(busca(base->raiz, valor)==0)
            base->raiz=aux_insere(base->raiz,valor);
        else
            printf("\nN\243mero j\240 foi inserido");
        printf("\nDeseja inserir mais um n\243mero? 1<SIM> 2<N\307O>: ");
        scanf("%d", &i);
    }
}
//====================================================================

//====================================================================
Arv* remover_aux(Arv *pai, int num)
{
    if(pai==NULL)
        printf("\n \n não encontrado na árvore");
    else
    {
        if(num > pai->info)
            pai->dir= remover_aux(pai->dir,num);
        else
        {
            if(num < pai->info)
                pai->esq = remover_aux(pai->esq,num);
            else /*achou o nó a ser removido*/
            {
                if(pai->dir==NULL && pai->esq==NULL) /* No sem filhos */
                {
                    free(pai);
                    pai=NULL;
                }
                else
                {
                    if (pai->esq==NULL) /*so tem filho da direita */
                    {
                        Arv *aux=pai;
                        pai = pai->dir;
                        free(aux);
                    }
                    else
                    {
                        if((pai->dir==NULL))/* so tem filho da esquerda */
                        {
                            Arv *aux=pai;
                            pai = pai->esq;
                            free(aux);
                        }
                        else /* tem os dois filhos */
                        {
                            Arv *aux;
                            aux = pai->esq;
                            while (aux->dir !=NULL)
                                aux=aux->dir;

                            pai->info =aux->info; /* troca as informações */
                            aux->info = num;
                            pai->esq = remover_aux(pai->esq,num);
                        }
                    }
                }
            }// achou o nó a ser removido
        }
    } //else do não estar vazio
    return pai;
}
//====================================================================

//====================================================================
BArv* remover (BArv *RAIZ, int num)
{
    Arv *aux=RAIZ->raiz;
    if(aux->info==num && aux->dir==NULL && aux->esq==NULL)
    {
        free(aux);
        free(RAIZ);
        return NULL;
    }
    RAIZ->raiz = remover_aux(RAIZ->raiz,num);
    return RAIZ;
}
//====================================================================

//====================================================================
int altura(Arv* no)
{
    int alturaesq = -1,alturadir = -1;

    if (no==NULL)
        return 0;
    else
    {
        alturaesq = altura(no->esq);
        alturadir = altura(no->dir);

        if (alturaesq > alturadir)
            return(alturaesq+1);
        else
            return(alturadir+1);
    }
}
//====================================================================

//====================================================================
void imprime_nivel_aux(Arv* no, int nivel)
{
    if (no == NULL)
        return;
    if (nivel == 1)
        printf("%d ", no->info);
    else
        if (nivel > 1)
        {
            imprime_nivel_aux(no->esq, nivel-1);
            imprime_nivel_aux(no->dir, nivel-1);
        }
}
//====================================================================

//====================================================================
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

//====================================================================
void InOder(Arv *no)
{
    Arv *pai=no;

    if(pai->esq!=NULL)
        InOder(pai->esq);

     printf("%d ",pai->info);

    if(pai->dir!=NULL)
        InOder(pai->dir);
}

//====================================================================

//====================================================================
void libera(Arv *raiz)
{
    if(raiz != NULL)
    {
        libera(raiz->esq);
        libera(raiz->dir);
        free(raiz);
    }
}
//====================================================================

//====================================================================
int main()
{
    int i=1, num;
    BArv *root;
    root=CriaArvore();
    int escolha1=0;
    do
    {
        system("cls");
        printf("    Menu principal\n");
        printf("========================\n");
        printf("1-Inserir n\243mero\n");
        printf("2-Remover n\243mero\n");
        printf("3-Verificar altura da \240rvore\n");
        printf("4-Mostrar \240rvore\n");
        printf("5-Impress\306o em ordem crescente\n");
        printf("6-Sair\n");
        printf("-> ");
        scanf("%d", &escolha1);
        switch (escolha1)
        {
            case 1: system("cls");
                    insere_arvore(root); break;

            case 2: system("cls");
                    while(i==1)
                    {
                        printf("\nDigite o n\243mero que deseja remover: ");
                        scanf("%d", &num);
                        remover(root, num);
                        printf("\nDeseja remover mais um n\243mero? 1<SIM> 2<N\307O> ");
                        scanf("%d", &i);
                    }
                    break;

            case 3: system("cls");
                    printf("\nAltura da \240rvore: %d\n", altura(root->raiz));
                    system("pause");
                    break;

            case 4: system("cls");
                    imprime_nivel(root->raiz);
                    system("pause");
                    break;

            case 5: system("cls");
                    printf("Impress\306o em ordem: ");
                    InOder(root->raiz);
                    printf("\n");
                    system("pause");
                    break;

            case 6: break;

            default: printf("\nOp\207\306o inv\240lida\n");
                     system("pause");
                     break;
        }
    }while(escolha1!=6);

    libera(root->raiz);
    return 0;
}

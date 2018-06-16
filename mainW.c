#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct element{
    float numb;
    int line;
    int cool;
    struct element *NEXT;
} position;

typedef struct{
    int nro_lin;
    int nro_col;
    position* first;
} matriz;

char be_sure(){
    char a;

    do{ printf("(s-Sim; e-Refazer opera��o; n-Encerrar opera��o.)\n");
        scanf("%c", &a);
        getchar();
        if(a!='s' && a!='S' && a!='e' && a!='E' && a!='n' && a!='N')
            printf("Escolha uma op��o v�lida.");
    }while(a!='s' && a!='S' && a!='e' && a!='E' && a!='n' && a!='N');

    return a;
}

matriz *create_m(){
    matriz *m;
    char sn;
    int line;
    int cool;

    do{ printf("Qual o numero de linhas que voc� quer na matriz? ");
        scanf("%d", &line);
        getchar();
        if(line<1)
            printf("Por favor, digite um n�mero v�lido\n");
    } while(line<1);

    do{ printf("Qual o n�mero de colunas que voc� quer na matriz? ");
        scanf("%d", &cool);
        getchar();
        if(cool<1)
            printf("Por favor, digite um n�mero v�lido\n");
    } while(cool<1);

    printf("Deseja criar uma matriz %dx%d?\n", line, cool);
    sn=be_sure();

    if(sn=='s' || sn=='S'){
        printf("Ok! Criarei sua matriz\n\n");
        m=(matriz*)malloc(sizeof(matriz));
        m->nro_lin=line-1;
        m->nro_col=cool-1;
        m->first=NULL;
        return m;
    }else if(sn=='e' || sn=='E'){
        system("cls");
        m=create_m();
        return m;
    }else{
        printf("Ok!\n");
        return NULL;
    }
}

int get_line(matriz m){
    int i;
    do{ printf("Indique a linha para a opera��o(0 a %d):\n", m.nro_lin);
        scanf("%d", &i);
        getchar();
        if(i<0 || i>m.nro_lin)
            printf("N�o existe essa linha.\n");
    } while(i<0 || i>m.nro_lin);
    return i;
}

int get_cool(matriz m){
    int j;
    do{ printf("Indique a coluna para a opera��o(0 a %d):\n", m.nro_col);
        scanf("%d", &j);
        getchar();
        if(j<0 || j>m.nro_col)
            printf("N�o existe essa coluna.\n");
    } while(j<0 || j>m.nro_col);
    return j;
}

position* check_cel(matriz m, int i, int j){
    position* p;

    for(p=m.first; ((*p).line!=i || (*p).cool!=j) && (*p).NEXT!=NULL; p=(*p).NEXT);
    if((*p).line==i && (*p).cool==j){
        return p;
    }else{
        return NULL;
    }

}

position* atribut_m(matriz m){
    position* p = NULL;
    int lp;
    int cp;
    float val;
    char certeza[3];

    do{ lp=get_line(m);
        cp=get_cool(m);
        printf("\nQuer atribuir um valor � c�lula %d x %d da matriz ?\n", lp , cp);
        certeza[0]=be_sure();
    } while(certeza[0]=='e');

    if(m.first!=NULL){
        if(check_cel(m, lp, cp)!=NULL){
            printf("J� foi atribuido um valor a essa c�lula\n");
            return NULL;
        }
    }

    if(certeza[0]=='s' || certeza[0]=='S'){
        do{ printf("\nDigite o valor que a c�lula vai receber: ");
            scanf("%f", &val);
            getchar();
            printf("\nQuer atribuir o valor de %.2f para a c�lula %d x %d da matriz?\n", val, lp, cp);
            certeza[1]=be_sure();
        } while(certeza[1]=='e' || certeza[1]=='E');
    }

    if(certeza[1]=='s'){
        p=(position*)malloc(sizeof(position));
        (*p).numb = val;
        (*p).line = lp;
        (*p).cool = cp;
        (*p).NEXT = NULL;
        printf("Inser��o completa.\n");
        (*cont)++;
    } else {
        printf("Ok, n�o ser� atribuido nenhum valor a essa c�lula.\n");
    }
    return p;
}

void change_value(matriz* m, int* cont){
    int i;
    int j;
    float val;
    position* p;
    position* aux;
    char sure;

    i=get_line(*m);
    j=get_cool(*m);

    for(p=m->first;(*p).NEXT!=NULL && ((*p).line!=i || (*p).cool!=j); p=(*p).NEXT);

    if((*p).line==i && (*p).cool==j){
        printf("Quer alterar o valor de %.2f na c�lula %dx%d?\n", (*p).numb, i, j);
        sure=be_sure();

        if(sure=='s' || sure=='S'){
            printf("Por qual valor quer substituir? \n");
            scanf("%f", &val);
            getchar();
            if(val!=0){
                (*p).numb=val;
            }else{
                for(aux=m->first; (*aux).NEXT!=NULL && (*aux).NEXT!=p; aux=(*aux).NEXT);
                if(p!=m->first && aux!=m->first){
                    (*aux).NEXT=(*p).NEXT;
                }
                if(p==m->first){
                    m->first=(*(m->first)).NEXT;
                }else if (aux==m->first){
                    (m->first)->NEXT=(*p).NEXT;
                }
            free(p);
            (*cont)--;
            }
        }else if(sure=='e' || sure=='E'){
            system("cls");
            change_value(m);
        }
    }else{
        printf("N�o h� nenhum valor condicionado a essa c�lula.");
    }
}

void get_value(matriz m){
    int i;
    int j;
    position* p;

    if(m.first==NULL){
        printf("N�o h� nenhum valor na matriz\n");
        return;
    }

    i=get_line(m);
    j=get_cool(m);

    if((p=check_cel(m, i, j))!=NULL){
        printf("O valor da c�lula %dx%d � %.2f\n", i, j, (*p).numb);
    }else{
        printf("O valor da c�lula %dx%d � 0.00\n", i, j);
    }
}

void line_sum(matriz m){
    position* p;
    float sum = 0;
    int i;

    i=get_line(m);

    for(p=m.first; p!=NULL; p=(*p).NEXT){
        if(((*p).line)==i){
            sum+=((*p).numb);
        }
    }
    printf("O valor da soma dos elementos da linha %d � %.2f\n", i, sum);
}

void cool_sum(matriz m){
    position* p;
    float sum = 0;
    int j;

    j=get_cool(m);

    for(p=m.first; p!=NULL; p=(*p).NEXT){
        if((*p).cool==j){
            sum+=(*p).numb;
        }
    }
    printf("O valor da soma dos elementos da coluna %d � %.2f\n", j, sum);
}

void print_m(matriz m){
    position *p;

    if(m.first!=NULL){
        for(p=m.first; p!=NULL; p=(*p).NEXT)
            printf("%dx%d   -   %.2f\n", (*p).line, (*p).cool, (*p).numb);
            printf("O restante das c�lulas tem o valor 0.00\n");
    }else{
        printf("\nTodos os valores s�o 0.00\n");
    }
}

int main(int argc, char const *argv[]) {
    matriz* m_pont;
    position* p_aux;
    char option;
    char aux;
    int t = 1;
    int mat;
    int cont = 0;
    position* p[cont];
    position* auxs;
    int auxn = 0;


    setlocale(LC_ALL, "Portuguese");

    printf("PROGRAMA PARA MANIPULA��O DE MATRIZES ESPARSAS\n");

    while(t){
        printf("\nQUE OPERA��O DESEJA FAZER?\n");
        printf("\na-Criar a matriz;                 \tb-Remover a matriz;");
        printf("\nc-Atribuir um valor a uma posi��o;\td-Modificar um valor de uma posi��o;");
        printf("\ne-Somar os valores de uma linha;  \tf-Somar os valores de uma coluna;");
        printf("\ng-Consultar uma posi��o;          \th-Imprimir todos os valores da matriz;");
        printf("\ni-Sair do programa.\n");
        scanf("%c", &option);
        getchar();
        system("cls");

        switch(option){
            case 'a': case 'A':
                if(mat==1){
                    printf("J� existe uma matriz criada.\nDeseja sobrescrever a atual?(s-sim, n-nao)\n");
                    aux=be_sure();

                    if(aux=='s' || aux=='S'){
                        free(m_pont);
                        if((m_pont=create_m())!=NULL){
                            printf("Sua nova matriz foi criada\n");
                        }else{
                            printf("Sua nova matriz nao foi criada e voc� perdeu a antiga.\n");
                        }
                    }else{
                        printf("Ok. A outra matriz vai ser mantida.\n");
                    }
                }else{                                                              //N�o h� nenhuma matriz.
                    if((m_pont=create_m())!=NULL){
                        mat=1;
                        printf("Sua matriz foi criada.\n");
                    }else{
                        printf("Sua matriz nao foi criada\n");
                    }
                }
                break;

            case 'b': case 'B':
                if(mat==1){
                    free(m_pont);
                    mat=0;
                    printf("Sua matriz foi removida.\n");
                }else{
                    printf("Nao h� nenhuma matriz criada\n");
                }
                break;

            case 'c': case 'C':
                if(mat==0){
                    printf("Nao h� nenhuma matriz para ser alterada\n");
                }else{
                    if((*m_pont).first==NULL){
                        (*m_pont).first=atribut_m(*m_pont, &cont);
                    }else{
                        for(p_aux=(*m_pont).first; (*p_aux).NEXT!=NULL; p_aux=(*p_aux).NEXT);
                        (*p_aux).NEXT=atribut_m(*m_pont, &cont);
                    }
                }
                break;

            case 'd': case 'D':
                if(mat==0){
                    printf("Nao h� nenhuma matriz criada\n");
                }else{
                    if((*m_pont).first!=NULL){
                        change_value(m_pont, & cont);
                    }else{
                        printf("Nao h� nenhum valor na matriz\n");
                    }
                }
                break;

            case 'e': case 'E':
                if(mat==0){
                    printf("Nao h� nenhuma matriz criada\n");
                }else{
                    line_sum(*m_pont);
                }
                break;

            case 'f': case 'F':
                if(mat==0){
                    printf("Nao h� nenhuma matriz criada\n");
                }else{
                    cool_sum(*m_pont);
                }
                break;

            case 'g': case 'G':
                if(mat==0){
                    printf("Nao h� nenhuma matriz criada\n");
                }else{
                    get_value(*m_pont);
                }
                break;

            case 'h': case 'H':
                if(mat==1){
                    print_m(*m_pont);
                }else{
                    printf("N�o h� nenhuma matriz ainda\n");
                }
                break;

            case 'i': case 'I':
                t = 0;
                break;

            default:
                printf("Digite uma op��o v�lida\n");
        }
    }
    if(mat==1){
        if((*m_pont).first!=NULL){
            for(auxs=(*m_pont).first; auxs!=NULL; auxs=(*auxs).NEXT){
                p[auxn]=auxs;
                auxn++;
            }

            for(auxn=0; auxn<cont; auxn++)
                free(p[auxn]);
        }
    free(m_pont);
    }

    return 0;
}

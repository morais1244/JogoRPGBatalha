#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define true 1;
#define false 0;

//dinamicidade


typedef struct{
    int vida;
    int poder;
    int mana;
    int habilidade;

} jogador;

typedef struct{
    int vida;
    int poder;

} status_in;

jogador p1;

status_in *enemy;


///////// 


void player(){

    // nosso jogador
    p1.vida = 1000;
    p1.poder = 50;
    p1.mana = 100;
    p1.habilidade = 100;

}

void gerar_inimigo(int x){
    // inimigo padrao
    enemy[x].vida = 100;
    enemy[x].poder = 50;
}

void inimigo(int *x){
    // definindo inimigo
    enemy = (status_in *)malloc((*x + 1)) * sizeof(status_in);

    // se n existir mais espaço
    if(enemy == false){
        printf("Erro: Não há mais memória para criar um inimigo");
        exit(true);
    }

    gerar_inimigo(*x);

    (*x)++;
}

int main(){
    //contador de batalhas
    int cont = 1;
    //contador de inimigos
    int x = 0;
    srand(time(false));
    inimigo(&x);
    player();
    int op, j, ataque, alvo;

    do{
        system("cls");
        do{
            printf("Sua mana atual é: %d \n", p1.mana);
            printf("(1) Ataque.\n");
            printf("(2) Habilidade.\n");
            scanf("%d",&op);
        } while( op < 1 || op > 2);
        system("cls");
        printf("Selecione o inimigo que quer atacar: \n");
        for ( i = 0; i < x; i++){
            if(enemy[i].vida > 0){
                printf("Inimigo (%d), Vida: %d\n",i,enemy[i].vida);
            }
        }
        scanf("%d",&alvo)
        system("cls");
        if(enemy[alvo].vida > 0){
            switch(op){
                case 1:
                    ataque = p1.poder;
                    printf("Dano tomado : % d\n", ataque);
                    Sleep(2000);
                    enemy[alvo].vida -= ataque;
                    printf("Vida do inimigo: %d, agora é: %d",alvo,enemy[alvo].vida);
                    Sleep(2000);
                    break;
                case 2:
                    if(p1.mana > 0){
                        ataque = p1.habilidade * (rand()%3);
                        p1.mana -= 40;
                        printf("Dano tomado : % d\n", ataque);
                        Sleep(2000);
                        enemy[alvo].vida -= ataque;
                        printf("Vida do inimigo: %d, agora é: %d",alvo,enemy[alvo].vida);
                        Sleep(2000);
                    }
                    else{
                        printf("Você não tem mana o suficiente\n");
                        Sleep(2000);

                    }
                    break;
            }
        }else{
            printf("Este já está morto\n");
            Sleep(2000);
        }
        printf("\n Turno do inimigo: \n");
        Sleep(2000);

        for(i = 0; i < x; i++){
            if(enemy[i].vida > 0){
                ataque = enemy[i].poder * (rand()%3);
                printf("O inimigo %d, me deu %d de dano\n",i,ataque);
                Sleep(2000);
                p1.vida -= ataque;
                printf("Sua vida atual é: %d\n", p1.vida);
                Sleep(2000);
            }
        }
        if((cont % 2) != 0){
            enemy = (status_in *)realloc(enemy,(x+1)* sizeof(status_in));
            if( enemy = false){
                printf("Erro: Não há mais memória para criar um inimigo");
            exit(true);
            }
            gerar_inimigo(x);
            x++;
        }
        cont++;
        p1.mana += 20;
        system("pause");

    }while(p1.vida>0);
    free(enemy);
    system("pause");
    return 0;
}
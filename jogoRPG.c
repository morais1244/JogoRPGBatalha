#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define true 1
#define false 0
//dinamicidade
void gotoxy(int x, int y)
{
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x-1, y-1});
}

void escondeCursor(int a)
{
    if (a == 0)
    {
        CONSOLE_CURSOR_INFO cursor = {1, FALSE};
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    } else
    {
        CONSOLE_CURSOR_INFO cursor = {1, TRUE};
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    }
}

void desenharHeroi(int posx, int posy)
{
    gotoxy(posx, posy);
    printf("O");
    gotoxy(posx-1, posy+1);
    printf("/");
    gotoxy(posx+1, posy+1);
    printf("\\");
    gotoxy(posx+2, posy+1);
    printf("|");
    gotoxy(posx, posy+1);
    printf("|");
    gotoxy(posx-1, posy+2);
    printf("/");
    gotoxy(posx+1, posy+2);
    printf("\\");

}

void desenharVilao(int posx, int posy)
{
    gotoxy(posx, posy);
    printf("W");
    gotoxy(posx-1, posy+1);
    printf("/");
    gotoxy(posx+1, posy+1);
    printf("\\");
    gotoxy(posx, posy+1);
    printf("|");
    gotoxy(posx-4, posy+1);
    printf("3--");
    gotoxy(posx-1, posy+2);
    printf("/");
    gotoxy(posx+1, posy+2);
    printf("\\");
}

void apagar(int posx, int posy)
{
    gotoxy(posx, posy);
    printf(" ");
    gotoxy(posx-1, posy+1);
    printf(" ");
    gotoxy(posx+1, posy+1);
    printf("  ");
    gotoxy(posx, posy+1);
    printf(" ");
    gotoxy(posx-1, posy+2);
    printf(" ");
    gotoxy(posx+1, posy+2);
    printf("  ");
}

void bolaFogo(int posx, int posy, int posxB, int posyB)
{

    for(int i = 0; i < 7; i++)
    {
        Sleep(400);

        gotoxy(posxB + i, posyB);
        printf("~");
        gotoxy(posxB + i, posyB+1);
        printf("~~O");
        gotoxy(posxB + i, posyB+2);
        printf("~");

    }
    
    apagar(posx, posy);

    Sleep(500);

    desenharVilao(posx, posy);
}

void atack(int posxH, int posyH, int posxV, int posyV, int quem)
{
    escondeCursor(0);
    if(quem)
    {
        for(int i = 0; i < posxV-4; i++)
        {
            Sleep(300);
            apagar((posxH+i)-1, posyH);
            desenharHeroi(posxH+i, posyH);
        }
            apagar(posxV, posyV);

            Sleep(500);

            desenharVilao(posxV, posyV);
    }  
    else 
    {
        for(int i = posxV; i > posxH+4; i--)
        {
            Sleep(300);
            apagar(i+1, posyV);
            desenharVilao(i, posyV);
        }
            apagar(posxH, posyH);

            Sleep(500);

            desenharHeroi(posxH, posyH);
    }    
}

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
    enemy = (status_in *)malloc((*x + 1) * sizeof (status_in));

    // se n existir mais espaço
    if(enemy == false){
        printf("Erro: Nao ha mais memoria para criar um inimigo");
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
            printf("Sua mana atual eh: %d \n", p1.mana);
            printf("(1) Ataque.\n");
            printf("(2) Habilidade.\n");
            scanf("%d",&op);
        } while( op < 1 || op > 2);
        system("cls");
        printf("Selecione o inimigo que quer atacar: \n");
        for (int i = 0; i < x; i++){
            if(enemy[i].vida > 0){
                printf("Inimigo (%d), Vida: %d\n",i,enemy[i].vida);
            }
        }
        scanf("%d",&alvo);
        system("cls");
        if(enemy[alvo].vida > 0){
            switch(op){
                case 1:
                    system("cls");
                    desenharHeroi(2, 10);
                    desenharVilao(12, 10);
                    atack(2, 10, 12, 10, 1);
                    system("cls");
                    ataque = p1.poder;
                    printf("Dano tomado : % d\n", ataque);
                    Sleep(2000);
                    enemy[alvo].vida -= ataque;
                    printf("Vida do inimigo: %d, agora eh: %d",alvo,enemy[alvo].vida);
                    Sleep(2000);
                    break;
                case 2:
                    if(p1.mana > 0){
                        system("cls");
                        desenharHeroi(2, 10);
                        desenharVilao(12, 10);
                        bolaFogo(12, 10, 4, 10);
                        system("cls");
                        ataque = p1.habilidade * (rand()%3);
                        p1.mana -= 40;
                        printf("Dano tomado : % d\n", ataque);
                        Sleep(2000);
                        enemy[alvo].vida -= ataque;
                        printf("Vida do inimigo: %d, agora eh: %d",alvo,enemy[alvo].vida);
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

        for(int i = 0; i < x; i++){
            if(enemy[i].vida > 0){
                system("cls");
                desenharHeroi(2, 10);
                desenharVilao(12, 10);
                atack(2, 10, 12, 10, 0);
                system("cls");
                ataque = enemy[i].poder * (rand()%3);
                printf("O inimigo %d, me deu %d de dano\n",i,ataque);
                Sleep(2000);
                p1.vida -= ataque;
                printf("Sua vida atual eh: %d\n", p1.vida);
                Sleep(2000);
            }
        }
        if((cont % 2) != 0){
            enemy = (status_in *)realloc(enemy,(x+1)* sizeof(status_in));
            if( enemy == false){
                printf("Erro: Nao ha mais memoria para criar um inimigo");
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
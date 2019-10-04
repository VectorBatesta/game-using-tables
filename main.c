#include <stdio.h>
#include <conio.h>
#include <time.h>

#define U_16 0x20000  //U-16 text mode, for the text blocks -> ignorar isso, serve apenas caso tenha caractere especial

typedef enum {CIMA, BAIXO, DIREITA, ESQUERDA} Dir;

int checkmovable(Dir dir, char table[20][40], int antesx, int antesy){ //portas lógicas para movimentação: para cima, para baixo, etc
    int depoisx = antesx;
    int depoisy = antesy;
    int moveu = 0;
    switch(dir){
        case CIMA:
            depoisy--;
            if(table[depoisy][depoisx] == 'X' || table[depoisy][depoisx] == 'K') //|| quer dizer OU, se quiser dizer E, só colocar && (...) se o player tentar mecher o personagem para um bloco[K] ou parede[X], a função retorna negativo
                depoisy = antesy;
            else
                moveu = 1;
            table[depoisy][depoisx] = '^';
            break;
        case ESQUERDA:
            depoisx--;
            if(table[depoisy][depoisx] == 'X' || table[depoisy][depoisx] == 'K')
                depoisx = antesx;
            else
                moveu = 1;
            table[depoisy][depoisx] = '<';
            break;
        case BAIXO:
            depoisy++;
            if(table[depoisy][depoisx] == 'X' || table[depoisy][depoisx] == 'K')
                depoisy = antesy;
            else
                moveu = 1;
            table[depoisy][depoisx] = 'V';
            break;
        case DIREITA:
            depoisx++;
            if(table[depoisy][depoisx] == 'X' || table[depoisy][depoisx] == 'K')
                depoisx = antesx;
            else
                moveu = 1;
            table[depoisy][depoisx] = '>';
            break;
        default:
            printf("problema na recebicao do dir");
            break;
    }
    if (moveu == 1){
        table[antesy][antesx] = '_';
        return 1;
    }
    return 0;
}

void shoot(Dir dir, char table[20][40], int coordx, int coordy){
    int shothit = 0;
    switch(dir){
        case CIMA: //^
            for(; coordy > 0; coordy--){
                if(table[coordy][coordx] == 'K'){
                    table[coordy][coordx] = '*';
                    return;
                }
                if(table[coordy][coordx] != '^')
                    table[coordy][coordx] = '*';
            }
            break;
        case BAIXO: //V
            for(; coordy < 19; coordy++){
                if(table[coordy][coordx] == 'K'){
                    table[coordy][coordx] = '*';
                    return;
                }
                if(table[coordy][coordx] != 'V')
                    table[coordy][coordx] = '*';
            }
            break;
        case DIREITA: //>
            for(; coordx < 39; coordx++){
                if(table[coordy][coordx] == 'K'){
                    table[coordy][coordx] = '*';
                    return;
                }
                if(table[coordy][coordx] != '>')
                    table[coordy][coordx] = '*';
            }
            break;
        case ESQUERDA: //<
            for(; coordx > 0; coordx--){
                if(table[coordy][coordx] == 'K'){
                    table[coordy][coordx] = '*';
                    return;
                }
                if(table[coordy][coordx] != '<')
                    table[coordy][coordx] = '*';
            }
            break;
        default:
            printf("problema no tiro");
            break;
    }
    return;
}






int main() {
    //int maxX;
    //int maxY;
    //malloc table[maxY][maxX];
    char table[20][40]; //inicialização da tabela do jogo, acima representação de dinâmico
    char mov; //valor do botão recebido do teclado
    Dir dir;

    int coordx = 1; //coordenada do personagem em X
    int coordy = 1; //coordenada do personagem em Y

    int varrepeat = 1; //para o laço de repetição do while
    int hithead = 0; //caso o player tente se mecher em um lugar que não consiga se mecher
    int shooteded = 0;

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 40; j++) {
            if(i == 0 || i == 19 || j == 0 || j == 39)
                table[i][j] = 'X'; //geração da tabela do jogo para ter paredes nas extremidades
            else
                table[i][j] = '_'; //lugar onde o player pode se mecher
        }
    }

    srand(time(NULL));
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 40; j++){
            if(table[i][j] == '_' && rand()%10 == 0) //aqui é gerado aleatoriamente vários blocos, que é K
                table[i][j] = 'K';
        }
    }

    table[coordy][coordx] = '>';



    while(varrepeat == 1){
        system("cls"); //limpa a tela

        if (hithead == 1) //caso não consiga se mecher = printa BONK
            printf("BONK\n");
        else if (shooteded == 1)
            printf("PEW\n");
        else
            printf("\n");
        hithead = 0;
        shooteded = 0;
        //o player é renderizado em ^ > V <

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 40; j++) {
                printf("%c", table[i][j]); //printa a tabela na tela
                srand(time(NULL));
                if(table[i][j] == '*' /*&& rand()%10 == 0*/)
                    table[i][j] = '_';
            }
            printf("\n");
        }

        printf("\ncoordx = %i\ncoordy = %i\n", coordx, coordy); //printa as coords do player na tela
        printf("\n|Q|W| ]\n"
               "|A S D|\n"
               "[SPACE to SHOOT]\n"
               "[Q to QUIT]\n");
        mov = getch(); //pega o movimento do player do teclado q ele digitar, recebe a letra q tbm caso o player queira sair do jogo

        switch(mov){
            case 'q':
                varrepeat = 0; //acaba com o laço de repetição maior
                break;
            case 'w':
                dir = CIMA;
                if(checkmovable(dir, table, coordx, coordy) == 0) //se não conseguir se mecher para [dir], variavel de não cosneguir se mecher é positiva
                    hithead = 1;
                else coordy--; //caso consiga se mecher, a variavel da respectiva coordenada é alterada / o personagem se meche
                break;
            case 's':
                dir = BAIXO;
                if(checkmovable(dir, table, coordx, coordy) == 0)
                    hithead = 1;
                else coordy++;
                break;
            case 'a':
                dir = ESQUERDA;
                if(checkmovable(dir, table, coordx, coordy) == 0)
                    hithead = 1;
                else coordx--;
                break;
            case 'd':
                dir = DIREITA;
                if(checkmovable(dir, table, coordx, coordy) == 0)
                    hithead = 1;
                else coordx++;
                break;
            case ' ':
                shoot(dir, table, coordx, coordy);
                shooteded = 1;
                break;
        }
    }

    printf("\n[[[[JOGO FECHADO]]]]\n(pressione algo para fechar)"); //caso o player digite 'Q' e saia do jogo
    return 0; //fim
}

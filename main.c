#include <stdio.h>
#include <conio.h>

#define U_16 0x20000  //U-16 text mode, for the text blocks -> ignorar isso, serve apenas caso tenha caractere especial

int checkmovable(char dir, char **table, int coordx, int coordy){ //portas lógicas para movimentação: para cima, para baixo, etc
    switch(dir){
        case 'c':
            printf("cccccccccccccccc");
            if(table[coordy - 1][coordx] == 'X' || table[coordy - 1][coordx] == 'K') //|| quer dizer OU, se quiser dizer E, só colocar && (...) se o player tentar mecher o personagem para um bloco[K] ou parede[X], a função retorna negativo
                return 0; // : não consegue se mecher
            else return 1; // : consegue se mecher
            break;
        case 'e':
                        printf("eeeeeeeeeeeeeeeee");
            if(table[coordy][coordx - 1] == 'X' || table[coordy][coordx - 1] == 'K')
                return 0;
            else return 1;
            break;
        case 'b':
                        printf("bbbbbbbbbbbbbbbbbb");
            if(table[coordy + 1][coordx] == 'X' || table[coordy + 1][coordx] == 'K')
                return 0;
            else return 1;
            break;
        case 'd':
                        printf("ddddddddddddd");
            if(table[coordy][coordx + 1] == 'X' || table[coordy][coordx + 1] == 'K')
                return 0;
            else return 1;
            break;
        default:
                        printf("fffffffffffffff");
            printf("problema na recebicao do dir");
            break;
    }
}

int main() {
    //int maxX;
    //int maxY;
    //char table[maxY][maxX];
    char table[20][40]; //inicialização da tabela do jogo, acima representação de dinâmico
    char mov; //valor do botão recebido do teclado

    int coordx = 1; //coordenada do personagem em X
    int coordy = 1; //coordenada do personagem em Y

    int varrepeat = 1; //para o laço de repetição do while
    int hithead = 0; //caso o player tente se mecher em um lugar que não consiga se mecher

    while(varrepeat == 1){
        system("cls"); //limpa a tela

        if (hithead == 1) //caso não consiga se mecher = printa BONK
            printf("BONK\n");

        hithead = 0;

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 40; j++) {
                if(i == 0 || i == 19 || j == 0 || j == 39)
                    table[i][j] = 'X'; //geração da tabela do jogo para ter paredes nas extremidades
                else
                    table[i][j] = '_'; //lugar onde o player pode se mecher
            }
        }

        for (int i = 0; i < 20; i++){
            for (int j = 0; j < 40; j++){
                if(table[i][j] == '_' && rand()%10 == 0) //aqui é gerado aleatoriamente vários blocos, que é K
                    table[i][j] = 'K';
            }
        }

        table[coordy][coordx] = 'O'; //o player é renderizado em O

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 40; j++) {
                printf("%c", table[i][j]); //printa a tabela na tela
            }
            printf("\n");
        }
        printf("\n");

        printf("\ncoordx = %i\ncoordy = %i\n", coordx, coordy); //printa as coords do player na tela

        printf("\n|_W_|\n"
               "|ASD|\n"
               "[Q TO QUIT]\n");
        mov = getch(); //pega o movimento do player do teclado q ele digitar, recebe a letra q tbm caso o player queira sair do jogo

        char dir; //variável da direção, só usado para a função
        switch(mov){
            case 'q':
                varrepeat = 0; //acaba com o laço de repetição maior
                break;
            case 'w':
                dir = 'c';
                if(checkmovable(dir, table, coordx, coordy) == 0) //se não conseguir se mecher para [dir], variavel de não cosneguir se mecher é positiva
                    hithead = 1;
                else coordy--; //caso consiga se mecher, a variavel da respectiva coordenada é alterada / o personagem se meche
                break;
            case 's':
                dir = 'b';
                if(checkmovable(dir, table, coordx, coordy) == 0)
                    hithead = 1;
                else coordy++;
                break;
            case 'a':
                dir = 'e';
                if(checkmovable(dir, table, coordx, coordy) == 0)
                    hithead = 1;
                else coordx--;
                break;
            case 'd':
                dir = 'd';
                if(checkmovable(dir, table, coordx, coordy) == 0)
                    hithead = 1;
                else coordx++;
                break;
        }
    }

    printf("\n[[[[JOGO FECHADO]]]]\n(pressione algo para fechar)\n"); //caso o player digite 'q' e saia do jogo
    getch(); //placeholder

    return 0; //fim
}

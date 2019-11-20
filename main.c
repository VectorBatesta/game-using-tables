#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

#define U_16 0x20000  //U-16 text mode, for the text blocks -> ignorar isso, serve apenas caso tenha caractere especial

typedef enum {CIMA, BAIXO, DIREITA, ESQUERDA} Dir;

int checkmovable(Dir dir, char table[20][40], int antesx, int antesy, int* pontos, int* vida){ //portas lógicas para movimentação: para cima, para baixo, etc
    int depoisx = antesx;
    int depoisy = antesy;
    int moveu = 0;
    switch(dir){
        case CIMA:
            depoisy--;
            if(table[depoisy][depoisx] == 'X' || table[depoisy][depoisx] == 'K') //|| quer dizer OU, se quiser dizer E, só colocar && (...) se o player tentar mecher o personagem para um bloco[K] ou parede[X], a função retorna negativo
                depoisy = antesy;
            else if(table[depoisy][depoisx] == 'E'){
                depoisy = antesy;
                (*vida)--;
                moveu = 2;
            }
            else
                moveu = 1;
            table[depoisy][depoisx] = '^';
            break;
        case ESQUERDA:
            depoisx--;
            if(table[depoisy][depoisx] == 'X' || table[depoisy][depoisx] == 'K')
                depoisx = antesx;
            else if(table[depoisy][depoisx] == 'E'){
                depoisx = antesx;
                (*vida)--;
                moveu = 2;
            }
            else
                moveu = 1;
            table[depoisy][depoisx] = '<';
            break;
        case BAIXO:
            depoisy++;
            if(table[depoisy][depoisx] == 'X' || table[depoisy][depoisx] == 'K')
                depoisy = antesy;
            else if(table[depoisy][depoisx] == 'E'){
                depoisy = antesy;
                (*vida)--;
                moveu = 2;
            }
            else
                moveu = 1;
            table[depoisy][depoisx] = 'V';
            break;
        case DIREITA:
            depoisx++;
            if(table[depoisy][depoisx] == 'X' || table[depoisy][depoisx] == 'K')
                depoisx = antesx;
            else if(table[depoisy][depoisx] == 'E'){
                depoisx = antesx;
                (*vida)--;
                moveu = 2;
            }
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
        (*pontos)--;
        return 1;
    }
    return 0;
}

void shoot(Dir dir, char table[20][40], int coordx, int coordy, int* pontos){
    int shothit = 0;
    switch(dir){
        case CIMA: //^
            for(; coordy > 0; coordy--){
                if(table[coordy][coordx] == 'K'){
                    table[coordy][coordx] = '*';
                    (*pontos)=(*pontos) + 3;
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
                    (*pontos)=(*pontos) + 3;
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
                    (*pontos)=(*pontos) + 3;
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
                    (*pontos)=(*pontos) + 3;
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
    return;        //o player é renderizado em ^ > V <
}

void printavida(int* vida, int maxvida){
    if(vida > maxvida)
        vida = maxvida;

    printf("\nVIDA [");
    for(int quantvida = vida; maxvida > 0; maxvida--){
        if (quantvida > 0)
            printf("O");
        else
            printf("_");
    }
    printf("]\n");
}

void gameover(){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
"\n  sSSSSs   .S_SSSs     .S_SsS_S.     sSSs          sSSs_sSSs     .S    S.     sSSs   .S_sSSs"
"\n d%%%%%%%%SP  .SS~SSSSS   .SS~S*S~SS.   d%%%%SP         d%%%%SP~YS%%%%b   .SS    SS.   d%%%%SP  .SS~YS%%%%b"
"\nd%%S'      S%%S   SSSS  S%%S `Y' S%%S  d%%S'          d%%S'     `S%%b  S%%S    S%%S  d%%S'    S%%S   `S%%b"
"\nS%%S       S%%S    S%%S  S%%S     S%%S  S%%S           S%%S       S%%S  S%%S    S%%S  S%%S     S%%S    S%%S"
"\nS&S       S%%S SSSS%%S  S%%S     S%%S  S&S           S&S       S&S  S&S    S%%S  S&S     S%%S    d*S"
"\nS&S       S&S  SSS%%S  S&S     S&S  S&S_Ss        S&S       S&S  S&S    S&S  S&S_Ss  S&S   .S*S"
"\nS&S       S&S    S&S  S&S     S&S  S&S~SP        S&S       S&S  S&S    S&S  S&S~SP  S&S_sdSSS"
"\nS&S sSSs  S&S    S&S  S&S     S&S  S&S           S&S       S&S  S&S    S&S  S&S     S&S~YSY%%b"
"\nS*b `S%%%%  S*S    S&S  S*S     S*S  S*b           S*b       d*S  S*b    S*S  S*b     S*S   `S%%b"
"\nS*S   S%%  S*S    S*S  S*S     S*S  S*S.          S*S.     .S*S  S*S.   S*S  S*S.    S*S    S%%S"
"\n SS_sSSS  S*S    S*S  S*S     S*S   SSSbs         SSSbs_sdSSS    SSSbs_S*S   SSSbs  S*S    S&S"
"\n  Y~YSSY  SSS    S*S  SSS     S*S    YSSP          YSSP~YSSY      YSSP~SSS    YSSP  S*S    SSS"
"\n                 SP           SP                                                    SP"
"\n                 Y            Y                                                     Y");
}

void menuprincipal(){
    
    
    
    
    
}




int main() {
    menuprincipal();
    
    //int maxX;
    //int maxY;
    //malloc table[maxY][maxX];
    char table[20][40]; //inicialização da tabela do jogo, acima representação de dinâmico
    char mov; //valor do botão recebido do teclado

    int maxvida;
    int vida;
    int escolhavida;

    Dir dir;

    int pontos = 0;

    int coordx = 1; //coordenada do personagem em X
    int coordy = 1; //coordenada do personagem em Y

    int varrepeat = 1; //para o laço de repetição do while
    int hithead = 0; //caso o player tente se mecher em um lugar que não consiga se mecher
    int shooteded = 0; //para saber se atirou ou não

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
            if(table[i][j] == '_' && rand()%100 == 0)
                table[i][j] = 'E';
        }
    }

    table[coordy][coordx] = '>'; //renderiza o player [quando o jogo é iniciado] olhando para direita

    printf("\nSelecione a dificuldade.\n1> Facil [5 vidas]\n2> Medio [4 vidas]\n3> Dificil [3 vidas]\n4> Impossivel [1hitkill]\n\nESCOLHA: ");
    scanf("%i", &escolhavida);
    switch(escolhavida){
        case 1:
            maxvida = 5;
            break;
        case 2:
            maxvida = 4;
            break;
        case 3:
            maxvida = 3;
            break;
        case 4:
            maxvida = 1;
            break;
        default:
            printf("\nproblema na escolha da dificuldade");
            return;
    }

    vida = maxvida;

    while(varrepeat == 1){
        system("cls"); //limpa a tela

        if (hithead == 1) //caso não consiga se mecher = printa BONK
            printf("BONK\n");
        else if (shooteded == 1) //caso atire = printa PEW
            printf("PEW\n");
        else //caso nada = apenas uma linha em branco para não ficar desproporcional a imagem
            printf("\n");
        hithead = 0; //após verificado tudo, reseta os parâmetros
        shooteded = 0;

        if (pontos < 0)
            pontos = 0;
        printf("/PONTOS: %i/\n", pontos);

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 40; j++) {
                printf("%c", table[i][j]); //printa a tabela na tela
                srand(time(NULL));
                if(table[i][j] == '*' /*& rand()%5 == 0 || rand()%5 == 1*/)
                    table[i][j] = '_';
            }
            printf("\n");
        }

        printf("coordenadas = %i, %i", coordx, coordy); //printa as coords do player na tela

        printavida(vida, maxvida);

        printf("\n|Q|W| ]\n"
               "|A S D|\n"
               "[SPACE to SHOOT]\n"
               "[Q to QUIT]\n"); //printa os controles
        mov = getch(); //pega o movimento do player do teclado q ele digitar, recebe a letra q tbm caso o player queira sair do jogo

        switch(mov){
            case 'q':
                varrepeat = 0; //acaba com o laço de repetição maior
                break;
            case 'w':
                dir = CIMA;
                if(checkmovable(dir, table, coordx, coordy, &pontos, &vida) == 0) //se não conseguir se mecher para [dir], variavel de não cosneguir se mecher é positiva
                    hithead = 1;
                else coordy--; //caso consiga se mecher, a variável da respectiva coordenada é alterada [o personagem se meche]
                break;
            case 's':
                dir = BAIXO;
                if(checkmovable(dir, table, coordx, coordy, &pontos, &vida) == 0)
                    hithead = 1;
                else coordy++;
                break;
            case 'a':
                dir = ESQUERDA;
                if(checkmovable(dir, table, coordx, coordy, &pontos, &vida) == 0)
                    hithead = 1;
                else coordx--;
                break;
            case 'd':
                dir = DIREITA;
                if(checkmovable(dir, table, coordx, coordy, &pontos, &vida) == 0)
                    hithead = 1;
                else coordx++;
                break;
            case ' ':
                shoot(dir, table, coordx, coordy, &pontos); //abre função para atirar na frente do player
                shooteded = 1; //após atirar, a variável de atirar é alterada [o personagem atira]
                break;
        }

        if(vida == 0){
            gameover();
            printf("\n\nYOU ARE DEAD!! [pressione algo para fechar o jogo]\n");
            getch();
            return 0;
        }
    }

    printf("\n[[[[JOGO FECHADO]]]]\n(pressione algo para fechar)"); //caso o player digite 'Q' e saia do jogo
    return 0; //fim
}

#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define U_16 0x20000  //U-16 text mode, for the text blocks -> ignorar isso, serve apenas caso tenha caractere especial

typedef enum {CIMA, BAIXO, DIREITA, ESQUERDA} Dir;

int checkmovable(Dir dir, char **table, int antesx, int antesy, int* pontos, int* vida, int *wongame){ //portas lógicas para movimentação: para cima, para baixo, etc
    int depoisx = antesx;
    int depoisy = antesy;
    int moveu = 0;
    switch(dir){
        case CIMA:
            depoisy--;
            if(table[depoisy][depoisx] == 'W')
                *wongame = 1;
            else if(table[depoisy][depoisx] == 'X' || table[depoisy][depoisx] == 'K') //|| quer dizer OU, se quiser dizer E, só colocar && (...) se o player tentar mecher o personagem para um bloco[K] ou parede[X], a função retorna negativo
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
            if(table[depoisy][depoisx] == 'W')
                *wongame = 1;
            else if(table[depoisy][depoisx] == 'X' || table[depoisy][depoisx] == 'K')
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
            if(table[depoisy][depoisx] == 'W')
                *wongame = 1;
            else if(table[depoisy][depoisx] == 'X' || table[depoisy][depoisx] == 'K')
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
            if(table[depoisy][depoisx] == 'W')
                *wongame = 1;
            else if(table[depoisy][depoisx] == 'X' || table[depoisy][depoisx] == 'K')
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

void shoot(Dir dir, char **table, int coordx, int coordy, int * pontos, int tamtabley, int tamtablex){
    switch(dir){
        case CIMA: //^
            for(; coordy > 0; coordy--){
                if(table[coordy][coordx] == 'K'){
                    table[coordy][coordx] = '*';
                    (*pontos)=(*pontos) + 3;
                    return;
                }
                if(table[coordy][coordx] == 'E'){
                    table[coordy][coordx] = '*';
                    (*pontos)=(*pontos) + 8;
                    return;
                }
                if(table[coordy][coordx] != '^')
                    table[coordy][coordx] = '*';
            }
            break;
        case BAIXO: //V
            for(; coordy < tamtabley-1; coordy++){
                if(table[coordy][coordx] == 'K'){
                    table[coordy][coordx] = '*';
                    (*pontos)=(*pontos) + 3;
                    return;
                }
                if(table[coordy][coordx] == 'E'){
                    table[coordy][coordx] = '*';
                    (*pontos)=(*pontos) + 8;
                    return;
                }
                if(table[coordy][coordx] != 'V')
                    table[coordy][coordx] = '*';
            }
            break;
        case DIREITA: //>
            for(; coordx < tamtablex-1; coordx++){
                if(table[coordy][coordx] == 'K'){
                    table[coordy][coordx] = '*';
                    (*pontos)=(*pontos) + 3;
                    return;
                }
                if(table[coordy][coordx] == 'E'){
                    table[coordy][coordx] = '*';
                    (*pontos)=(*pontos) + 8;
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
                if(table[coordy][coordx] == 'E'){
                    table[coordy][coordx] = '*';
                    (*pontos)=(*pontos) + 8;
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

void printavida(int *vida, int maxvida){
    if(*vida > maxvida)
        *vida = maxvida;

    printf("\nVIDA [");
    for(int quantvida = *vida; maxvida > 0; maxvida--){
        if (quantvida > 0){
            printf("O");
            quantvida--;
        }
        else
            printf("_");
    }
    printf("]\n");
}

void gameover(){
    for(int x=0; x<10; x++){
        printf("\n");
        Sleep(10);
    }

    printf("\n  sSSSSs   .S_SSSs     .S_SsS_S.     sSSs          sSSs_sSSs     .S    S.     sSSs   .S_sSSs");
    Sleep(10);
    printf("\n d%%%%%%%%SP  .SS~SSSSS   .SS~S*S~SS.   d%%%%SP         d%%%%SP~YS%%%%b   .SS    SS.   d%%%%SP  .SS~YS%%%%b");
    Sleep(10);
    printf("\nd%%S'      S%%S   SSSS  S%%S `Y' S%%S  d%%S'          d%%S'     `S%%b  S%%S    S%%S  d%%S'    S%%S   `S%%b");
    Sleep(10);
    printf("\nS%%S       S%%S    S%%S  S%%S     S%%S  S%%S           S%%S       S%%S  S%%S    S%%S  S%%S     S%%S    S%%S");
    Sleep(10);
    printf("\nS&S       S%%S SSSS%%S  S%%S     S%%S  S&S           S&S       S&S  S&S    S%%S  S&S     S%%S    d*S");
    Sleep(10);
    printf("\nS&S       S&S  SSS%%S  S&S     S&S  S&S_Ss        S&S       S&S  S&S    S&S  S&S_Ss  S&S   .S*S");
    Sleep(10);
    printf("\nS&S       S&S    S&S  S&S     S&S  S&S~SP        S&S       S&S  S&S    S&S  S&S~SP  S&S_sdSSS");
    Sleep(10);
    printf("\nS&S sSSs  S&S    S&S  S&S     S&S  S&S           S&S       S&S  S&S    S&S  S&S     S&S~YSY%%b");
    Sleep(10);
    printf("\nS*b `S%%%%  S*S    S&S  S*S     S*S  S*b           S*b       d*S  S*b    S*S  S*b     S*S   `S%%b");
    Sleep(10);
    printf("\nS*S   S%%  S*S    S*S  S*S     S*S  S*S.          S*S.     .S*S  S*S.   S*S  S*S.    S*S    S%%S");
    Sleep(10);
    printf("\n SS_sSSS  S*S    S*S  S*S     S*S   SSSbs         SSSbs_sdSSS    SSSbs_S*S   SSSbs  S*S    S&S");
    Sleep(10);
    printf("\n  Y~YSSY  SSS    S*S  SSS     S*S    YSSP          YSSP~YSSY      YSSP~SSS    YSSP  S*S    SSS");
    Sleep(10);
    printf("\n                 SP           SP                                                    SP");
    Sleep(10);
    printf("\n                 Y            Y                                                     Y");
    Sleep(10);
    printf("\n");
    Sleep(10);
}

void printacontroles(char mov){
    printf("\n|Q|W| ]\n"
             "|A S D|\n"
             "[SPACE to SHOOT]\n"
             "[Q to QUIT]\n"); //printa os controles
}

void printapontosecoords(int* pontos, int coordx, int coordy, int mododev){
    if (*pontos < 0)
        *pontos = 0;
    printf("/PONTOS: %i/\n", *pontos);
    if (mododev == 1)
        printf("coordenadas = %i, %i", coordx, coordy); //printa as coords do player na tela
}

int selecionadificuldade(int* maxvida, int* vida){
    int escolhavida;
    printf("\nSelecione a dificuldade.\n1> Facil [5 vidas]\n2> Medio [4 vidas]\n3> Dificil [3 vidas]\n4> Impossivel [1hitkill]\n\nESCOLHA: ");
    scanf("%i", &escolhavida);
    switch(escolhavida){
        case 1:
            *maxvida = 5;
            *vida = *maxvida;
            return 10;
            break;
        case 2:
            *maxvida = 4;
            *vida = *maxvida;
            return 9;
            break;
        case 3:
            *maxvida = 3;
            *vida = *maxvida;
            return 8;
            break;
        case 4:
            *maxvida = 1;
            *vida = *maxvida;
            return 7;
            break;
        default:
            printf("\nproblema na escolha da dificuldade");
            return;
    }
}

int reconheceplayer(char mov, int* varrepeat, Dir *dir, char **table, int* coordx, int* coordy, int* pontos, int* vida, int* hithead, int* shooteded, int *everything, int *wongame){
    switch(mov){
        case 'q':
            *varrepeat = 0; //acaba com o laço de repetição maior
            *everything = 0;
            break;
        case 'w':
            *dir = CIMA;
            if(checkmovable(*dir, table, *coordx, *coordy, &(*pontos), &(*vida), &(*wongame)) == 0) //se não conseguir se mecher para [dir], variavel de não cosneguir se mecher é positiva
                *hithead = 1;
            else (*coordy)--; //caso consiga se mecher, a variável da respectiva coordenada é alterada [o personagem se meche]
            break;
        case 's':
            *dir = BAIXO;
            if(checkmovable(*dir, table, *coordx, *coordy, &(*pontos), &(*vida), &(*wongame)) == 0)
                *hithead = 1;
            else (*coordy)++;
            break;
        case 'a':
            *dir = ESQUERDA;
            if(checkmovable(*dir, table, *coordx, *coordy, &(*pontos), &(*vida), &(*wongame)) == 0)
                *hithead = 1;
            else (*coordx)--;
            break;
        case 'd':
            *dir = DIREITA;
            if(checkmovable(*dir, table, *coordx, *coordy, &(*pontos), &(*vida), &(*wongame)) == 0)
                *hithead = 1;
            else (*coordx)++;
            break;
        case ' ':
            *shooteded = 1;
            return 7;
            break;
    }
}

int menuprincipal(int *mododev){
    int menu = 0;
    int seta = 1;
    int comeco = 1;
    char selecionne = 'a';
    
    if (animacaomenuprincipal() == 2)
        return 2;
    
    
    while (menu == 0){
        if (comeco == 1){
            printf("\n\n\n\b<<<<<<<<<<MENU PRINCIPAL>>>>>>>>>>\n\n");

            if(seta == 1)
                printf("<- ");
            else
                printf("   ");
            printf("START GAME");
            if(seta == 1)
                printf(" ->\n");
            else
                printf("   \n");

            if(seta == 2)
                printf("<- ");
            else
                printf("   ");
            printf("OPTIONS");
            if(seta == 2)
                printf(" ->\n");
            else
                printf("   \n");

            if(seta == 3)
                printf("<- ");
            else
                printf("   ");
            printf("QUIT GAME");
            if(seta == 3)
                printf(" ->\n");
            else
                printf("   \n");

            printf("\n"
                   "|------controles------|\n"
                   "| CIMA = W            |\n"
                   "| SELECIONAR = ESPACO |\n"
                   "| BAIXO = S           |\n"
                   "|---------------------|");
        }
        else{
            printf("\n\n\n\b<<<<<<<<<<OPCOES>>>>>>>>>>\n\n");
            printf("MODO DEV: ");
            if (*mododev == 1)
                printf("[X]");
            else if (*mododev == 0)
                printf("[ ]");
            
            printf("\n"
                   "|------controles------|\n"
                   "| SELECIONAR = ESPACO |\n"
                   "| SAIR = Q            |\n"
                   "|---------------------|");
        }
        ////////////////////////////////////
        
        selecionne = getch();
        
        if (selecionne == 'q'){
            if (comeco == 1)
                return 2;
            else
                comeco = 1;
        }
        else if (selecionne == 'w')
            if (seta == 1);
            else
                seta--;
        else if(selecionne == 's')
            if (seta == 3);
            else
                seta++;
        else if(selecionne == ' '){
            if (comeco == 1){
                switch(seta){
                    case 1:
                        menu = 1;
                        break;
                    case 2:
                        comeco = 0;
                        break;
                    case 3:
                        return 2;
                        break;
                }
            }
            else {
                if (*mododev == 1)
                    *mododev = 0;
                else if (*mododev == 0)
                    *mododev = 1;
            }
        }
        system("cls");
    }
}

int animacaomenuprincipal(){
    FILE * menu;
    menu = fopen("opening.txt", "r");
    
    if (menu == NULL){
        printf("erro na abertura da opening\n");
        getch();
        return 2;
    }
    
    char chari[100];
    fgets(chari, 100, menu);
    char fim[3] = "<>";
    for(; strcmp(chari, fim) != 0; fgets(chari, 100, menu)){
        Sleep(10);
        printf("%s", chari);
    }
    getch();
    system("cls");
}

int wongamew(int pontos){
    gameover();
    char nomeplayer[100];
    char pontoschar[10];
    printf("\n\nYOU WON!!!!!!!!!!!!!!!!!!!!!!!!!!1111!11!!!!11!!\n");
    printf("SEUS PONTOS: %i\nDigite seu nome: ", pontos);
    scanf("%s", nomeplayer);

    FILE * saveiro;
    saveiro = fopen("record.txt", "r+");

    itoa(pontos, pontoschar, 10);
    strcat(pontoschar, " pontos // nome: ");
    strcat(pontoschar, nomeplayer);

    for(int lacorepet = 1; lacorepet == 1;){
        int pontodalinha;
        fscanf(saveiro, "%i pontos // nome: ", &pontodalinha);
        fscanf(saveiro, "%s\n", NULL);
        if(pontodalinha > pontos){
            fputs(pontoschar, saveiro);
            lacorepet = 0;
        }
    }

    getch();
    return 10;
}










int main() {
    int mododev = 0;
    
    if (menuprincipal(&mododev) == 2)
        return 2;

    int wongame = 0;
    char **table; //inicialização da tabela do jogo
    char mov; //valor do botão recebido do teclado
    int maxvida; //quantidade de vida MÁXIMA
    int vida; //quantidade de vida ATUAL
    Dir dir = DIREITA; //inicialização do enum
    int pontos = 0; //pontos
    int coordx = 1; //coordenada do personagem em X
    int coordy = 1; //coordenada do personagem em Y
    int varrepeat = 1; //para o laço de repetição do while
    int hithead = 0; //caso o player tente se mecher em um lugar que não consiga se mecher
    int shooteded = 0; //para saber se atirou ou não

    int mapacoordx = 0; //inicialização do mapa em x=0
    int mapacoordy = 0; //inicialização do mapa em y=0
    char nomemapa[12]; //string para ser concatenada e ser lida para o arquivo
    char mapacoordxchar[2]; //mesmo q mapacoordx porem agora em char
    char mapacoordychar[2]; //mesmo q mapacoordy porem agora em char
    
    int tamtablex = 0; //inicialização da comprimento da tabela do jogo
    int tamtabley = 0; //inicialização do altura da tabela do jogo
    
    int dificuldade = selecionadificuldade(&maxvida, &vida);
    
    
    
    int everything = 1;
    while(everything == 1){
        itoa(mapacoordx, mapacoordxchar, 10);
        itoa(mapacoordy, mapacoordychar, 10);
        strcpy(nomemapa,"mapa");
        strcat(nomemapa,mapacoordychar);
        strcat(nomemapa,mapacoordxchar);
        strcat(nomemapa,".txt");
        
        FILE * mapa;
        mapa = fopen(nomemapa, "r");
        if (mapa == NULL){
            printf("erro na leitura do arquivo, string:%s\n", nomemapa);
            getch();
            return 2;
        }
        
        fscanf(mapa, "%i.%i\n", &tamtabley, &tamtablex);
    
    //    tamtablex = tamtabley = 0;
    //    char firstlinha[100];
    //    fgets(firstlinha, 100, mapa);
    //    tamtablex = strlen(firstlinha) - 1;
    //
    //    while(fgets(firstlinha, 100, mapa) != NULL){
    //        tamtabley++;
    //    }
    //    rewind(mapa);
    //    tamtabley++;

        table = (char**) malloc(tamtabley * sizeof(char*));
        for(int i=0; i < tamtabley; i++)
            table[i] = (char*) malloc(tamtablex+1 * sizeof(char));

        
        char linha[100];
        for(int i = 0; i < tamtabley; i++){
            fscanf(mapa, "%s", linha);
            for(int x = 0; x < tamtablex; x++)
                table[i][x] = linha[x];
            printf("\n");
        }

        srand(time(NULL));
        if (mapacoordx != 3 && mapacoordy != 2){
            for (int i = 0; i < tamtabley-1; i++){
                for (int j = 0; j < tamtablex-1; j++){
                    if(table[i][j] == '_' && rand()% dificuldade*2 == 0) //aqui é gerado aleatoriamente vários blocos, que é K 
                        table[i][j] = 'K';
                    if(table[i][j] == '_' && rand()% dificuldade == 0)
                        table[i][j] = 'E';
                }
            }
        }

        table[coordy][coordx] = '>'; //renderiza o player [quando o jogo é iniciado] olhando para direita
        
        varrepeat = 1;
        while(varrepeat == 1){
            if(vida == 0){
                gameover();
                char nomeplayer[100];
                char pontoschar[10];
                printf("\n\nYOU ARE DEAD!!\n");
                pontos = pontos - 100;
                printf("SEUS PONTOS: %i\nDigite seu nome: ", pontos);
                scanf("%s", nomeplayer);
                
                FILE * saveiro;
                saveiro = fopen("record.txt", "r+");
                
                itoa(pontos, pontoschar, 10);
                strcat(pontoschar, " pontos // nome: ");
                strcat(pontoschar, nomeplayer);
                
                for(int lacorepet = 1; lacorepet == 1;){
                    int pontodalinha;
                    fscanf(saveiro, "%i pontos // nome: ", &pontodalinha);
                    fscanf(saveiro, "%s\n", NULL);
                    if(pontodalinha > pontos){
                        fputs(pontoschar, saveiro);
                        lacorepet = 0;
                    }
                }
                
                getch();
                return 0;
            }

            system("cls"); //limpa a tela

            if (wongame == 1){
                if (wongamew(pontos) == 10)
                    return 0;
            }
            if (hithead == 1) //caso não consiga se mecher = printa BONK
                printf("BONK\n");
            else if (shooteded == 1) //caso atire = printa PEW
                printf("PEW\n");
            else //caso nada = apenas uma linha em branco para não ficar desproporcional a imagem
                printf("\n");
            hithead = 0; //após verificado tudo, reseta os parâmetros
            shooteded = 0;

            printapontosecoords(&pontos, coordx, coordy, mododev);

            for (int i = 0; i < tamtabley; i++) {
                printf("\n");
                for (int j = 0; j < tamtablex; j++) {
                    printf("%c", table[i][j]);
                    if(table[i][j] == '*' /*& rand()%5 == 0 || rand()%5 == 1*/)
                        table[i][j] = '_';
                }
            }

            printavida(&vida, maxvida);
            printacontroles(mov);
            mov = getch(); //pega o movimento do player do teclado q ele digitar, recebe a letra q tbm caso o player queira sair do jogo

            if (reconheceplayer(mov, &varrepeat, &dir, table, &coordx, &coordy, &pontos, &vida, &hithead, &shooteded, &everything, &wongame) == 7)
                shoot(dir, table, coordx, coordy, &pontos, tamtabley, tamtablex); //abre função para atirar na frente do player

            if (coordy == tamtabley-1 || coordy == 0 || coordx == tamtablex-1 || coordy == 0){
                varrepeat = 0;
                fclose(mapa);
                
                if (coordy > 5){
                    mapacoordy++;
                    coordy = 1;
                }
                else if (coordx > 5){
                    mapacoordx++;
                    coordx = 1;
                }
            }
            
        }
    }
    printf("\n[[[[JOGO FECHADO]]]]\n(pressione algo para fechar)"); //caso o player digite 'Q' e saia do jogo
    return 0; //fim
}

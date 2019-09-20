#include <stdio.h>
#include <conio.h>

#define U_16 0x20000            //U-16 text mode, for the text blocks

checkimmovable(char mov){
    if 
    
    
    
    
}



int main() {
    char table[20][40];
    int x = 1;
    char mov;

    int coordx = 1;
    int coordy = 1;

    int asdasd = 1;
    while(asdasd==1){
        system("cls");
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 40; j++) {
                table[i][j] = '_';
            }
        }

        table[coordy][coordx] = 'X';

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 40; j++) {
                printf("%c", table[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        printf("\ncoordx=%i\ncoordy=%i\n", coordx, coordy);

        printf("\n|_W_|\n"
               "|ASD|\n"
               "[Q TO QUIT]\n");
        mov = getch();

        char dir;
        switch(mov){
            case 'q':
                asdasd = 0;
                break;
            case 'w':
                dir = 'c';
                if(checkimmovable(dir) == 1)
                    printf("BONK");
                else coordy--;
                break;
            case 's':
                if(coordy == 19)
                    printf("BONK");
                else coordy++;
                break;
            case 'a':
                if(coordx == 0)
                    printf("BONK");
                else coordx--;
                break;
            case 'd':
                if(coordx == 39)
                    printf("BONK");
                else coordx++;
                break;
        }
    }
    
    printf("\n[[[[JOGO FECHADO]]]]\n(pressione algo para fechar)\n");
    getc();
    return 0;
}

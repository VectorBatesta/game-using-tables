#include <stdio.h>
#include <conio.h>

#define U_16 0x20000            //U-16 text mode, for the text blocks

int main() {
    char table[20][40];
    int x = 1;
    char mov;

    int coordx = 1;
    int coordy = 1;

    int asdasd = 1;
    while(asdasd==1){
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 40; j++) {
                table[i][j] = ' ';
            }
        }

        table[player[1]][coordx] = 'X';

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

        if (mov=='q')
            asdasd = 0;
        else if (mov=='w'){
            if(coordy == 0)
                printf("BONK");
            else coordy--;
        }
        else if(mov=='s'){
            if(coordy == 19)
                printf("BONK");
            else coordy++;
        }
        else if(mov=='a'){
            if(coordx == 0)
                printf("BONK");
            else coordx--;
        }
        else if(mov=='d'){
            if(coordx == 39)
                printf("BONK");
            else coordx++;
        }


        system("cls");
    }

    return 0;
}

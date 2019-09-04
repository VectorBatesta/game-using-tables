#include <stdio.h>
#include <curses.h>

#define U_16 0x20000            //U-16 text mode, for the text blocks

void direction(char mov, int *player){
    if (mov=='w')
        player[1]++;
    else if(mov=='s')
        player[1]--;
    else if(mov=='a')
        player[0]--;
    else if(mov=='d') 
        player[0]++;
}

int main() {
    char table[20][15];
    int x = 1;

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 40; j++) {
            table[i][j] = '0';
            printf("%c", table[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    char mov;

    while(x <= 2) {
        int player[1];
        player[0] = 0;
        player[1] = 0;

        table[player[0]][player[1]] = '0';

        printf("\n|_W_|\n"
               "|ASD|\n");
        mov = getch();
        direction(mov,player);

        table[player[0]][player[1]] = 'X';

        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 40; j++) {
                printf("%c", table[i][j]);
            }
            printf("\n");
        }

        printf("\n");
        x++;
    }

    return 0;
}

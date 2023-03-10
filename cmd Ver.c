#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void setting(int map[101][101], int inputcol, int inputrow)
{
    int row, col;
    
    
    for (row = 0; row < 1; row++)
    {
        for(col = 0; col < inputcol + 1; col++)
        {
            map[col][row] = (col + 14);
        }
    }
    for (col = 0; col < 1; col++)
    {
        for(row = 0; row < inputrow + 1; row++)
        {
            map[col][row] = (row + 14);
        }
    }

    for (row = 0; row < inputrow + 1; row++)
    {
        for (col = 0; col < inputcol + 1; col++)
        {
            if (map[col][row] == 10) // 선택되지 않은 좌표
            {
                printf("■ ");                
            }
            else if (map[col][row] == 9) // 지뢰 좌표, 커맨드 용으로는 ※ 사용
            {
                printf("※ ");
            }
            else if (map[col][row] == 0) //빈 칸
            {
                printf("□ "); 
            }
            else if (map[col][row] == 14) //빈 칸
            {
                printf("★ "); 
            }
            else if (map[col][row] >= 15) //빈 칸
            {
                printf("%2d ", (map[col][row] - 14)); 
            }
            else
            {
                printf("%2d ", map[col][row]); //숫자로 할 때는 빈 칸 숫자 빈 칸 으로
            }
        }
        printf("\n");
    }

}

void mine_counting(int map[101][101], int inputcol, int inputrow)
{
    int col, row;
    int mine_count;
    
    for(row = 1; row < inputrow + 1; row++)
    {
        for(col = 1; col < inputcol + 1; col++)
        {
            if(map[col][row] == 10)
            {
                mine_count = 0;
                map[col][row] = 0;

                if(row - 1 >= 1)
                {
                    if(col - 1 >= 1 && map[col - 1][row - 1] == 9)
                    {
                        mine_count++;
                    }
                    if(map[col][row - 1] == 9)
                    {
                        mine_count++;
                    }
                    if(col + 1 <= inputcol + 1 && map[col + 1][row - 1] == 9)
                    {
                        mine_count++;
                    }
                }
                if(row >= 1)
                {
                    if(col - 1 >= 1 && map[col - 1][row] == 9)
                    {
                        mine_count++;
                    }
                    if(col + 1 <= inputcol + 1&& map[col + 1][row] == 9)
                    {
                        mine_count++;
                    }
                }
                if(row + 1 <= inputrow + 1)
                {
                    if(col - 1 >= 1 && map[col - 1][row + 1] == 9)
                    {
                        mine_count++;
                    }
                    if(map[col][row + 1] == 9)
                    {
                        mine_count++;
                    }
                    if(col + 1 <= inputcol + 1 && map[col + 1][row + 1] == 9)
                    {
                        mine_count++;
                    }
                }

                map[col][row] = mine_count;
                
            }
            else
            {
                continue;
            }
        }
    }
}

int mine_around(int map[101][101], int inputcol, int inputrow, int col, int row)
{
    int mine_count;

    if(map[col][row] != 0)
    {
        mine_count = 0;

        if(row - 1 >= 1)
        {
            if(col - 1 >= 1 && map[col - 1][row - 1] == 9)
            {
                mine_count++;
            }
            if(map[col][row - 1] == 9)
            {
                mine_count++;
            }
            if(col + 1 <= inputcol + 1 && map[col + 1][row - 1] == 9)
            {
                mine_count++;
            }
        }
        if(row >= 1)
        {
            if(col - 1 >= 1 && map[col - 1][row] == 9)
            {
                 mine_count++;
            }
            if(col + 1 <= inputcol + 1 && map[col + 1][row] == 9)
            {
                mine_count++;
            }
        }
        if(row + 1 <= inputrow + 1)
        {
            if(col - 1 >= 1 && map[col - 1][row + 1] == 9)
            {
                mine_count++;
            }
            if(map[col][row + 1] == 9)
            {
                mine_count++;
            }
            if(col + 1 <= inputcol + 1 && map[col + 1][row + 1] == 9)
            {
                mine_count++;
            }
        }
                
    }

    return mine_count;
    
}


void zero_counting(int map[101][101],int check[101][101], int inputcol, int inputrow, int x, int y)
{
    int row, col;
    for (row = y - 1; row <= y + 1; row++)
    {
        for (col = x - 1; col <= x + 1; col++)
        {
            if(col >= 1 && col < inputcol + 1 && row >= 1 && row < inputrow + 1 && check[col][row] == 10)
            {
                check[col][row] = map[col][row];

                if(map[col][row] == 0)
                {
                    zero_counting(map, check, inputcol, inputrow, col, row);
                }
                else if(map[col][row] != 9 && mine_around(map, inputcol, inputrow, x, y) != 0)
                {
                    check[col][row] = map[col][row];
                }
                else if(map[col][row] == 9 && mine_around(map, inputcol, inputrow, x, y) == 0)
                {
                    zero_counting(map, check, inputcol, inputrow, col, row);
                }
            }
        }
    }
    
}


int mine_search(int check[101][101], int inputcol, int inputrow)
{
    int search = 0;
    for (int row = 1; row < inputrow + 1; row++)
    {
        for (int col = 1; col < inputcol + 1; col++)
        {
            if (check[col][row] != 10 && check[col][row] != 9)
            {
                search++;
            }
            else
            {
                continue;
            }
        }
    }

    return search;
}


int main()
{
    int row, col;
    int inputrow = 0;
    int inputcol = 0;
    int mine;
    int check[101][101];
    int map[101][101];
    int newgame = 1;
    char choice;
    srand(time(NULL));


        while(inputcol < 5 || inputrow <5 || inputcol > 50 || inputrow > 50)
        {
            printf("판의 크기를 설정해주세요[5*5 ~ 50*50] : ");
            scanf("%d*%d", &inputcol, &inputrow);
        }
        
        for (row = 1; row < inputrow + 1; row++)
        {
            for (col = 1; col < inputcol + 1; col++)
            {
                check[col][row] = 10;
                map[col][row] = 10;
            }
        }

        while(mine < (inputcol*inputrow)/10 || mine > 2*(inputcol*inputrow)/10)
        {
            printf("설정할 지뢰의 개수를 설정해주세요.\n(최소 개수 - %d / 최대 개수 - %d) : ", (inputcol*inputrow)/10, 2*(inputcol*inputrow)/10);
            scanf("%d", &mine);
        }

        int m, a, b;

        for (m = 0; m < mine; m++)
        {
            while(1)
            {
                a = (rand() % inputcol) + 1;
                b = (rand() % inputrow) + 1;
                if (map[a][b] == 9)
                    ;
                else
                {
                    map[a][b] = 9;
                    break;
                }
            }
        }

        mine_counting(map, inputcol, inputrow);

        int search = 0;
        int safe = (inputcol * inputrow - mine);

        while(5)
        {
            system("cls");
            setting(check, inputcol, inputrow);
            
            int x, y;
            printf("확인할 좌표를 입력해주세요.(x, y) : ");
            scanf("%d, %d", &x, &y);
            printf("\n");
            
            
            if(map[x][y] == 0)
            {
                check[x][y] = 0;
                zero_counting(map, check, inputcol, inputrow, x, y);                
            }
            else if(check[x][y] == 0)
            {
                continue;
            }
            else if(map[x][y] == 9)
            {
                printf("지뢰가 터져떠용 ㅠㅠ..\n");
                break;
            }
            else
            {
                check[x][y] = map[x][y];
            }
            if(mine_search(check, inputcol, inputrow) == safe)
            {
                printf("지뢰를 모두 찾아내는데에 성공하셨습니당!! 대단해!!\n");
                break;
            }
                        
        }

        printf("\n \n");

        setting(map, inputcol, inputrow);
        Sleep(3000);
        
        printf("\n");
        printf("게임을 새로 시작하시겠습니까? [ y / n ] : ");
           
        do
        {
            scanf(" %c", &choice);
            printf("\n");

            if(choice == 'y')
            {
                newgame = 1;
            }
            else if(choice == 'n')
            {
                newgame = 0;
            }
            else
            {
                printf("잘못 입력하셨습니다. 다시 입력하여 주십시오 : ");
                newgame = 2;
            }

        } while (newgame == 2);

        if (newgame == 1)
        {
            system("cls");
            return main();
        }

        
    return 0;

}


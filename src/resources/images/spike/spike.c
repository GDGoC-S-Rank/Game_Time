/*
#include "SDL.h"
#include "SDL_timer.h"
#include "SDL_image.h"
#include <stdio.h>

#pragma comment(lib, "SDL2_image.lib")

#define num 15

int checkCollision(SDL_Rect* rect1, SDL_Rect* rect2)
{
    return !(rect1->x + rect1->w < rect2->x || rect2->x + rect2->w < rect1->x ||
        rect1->y + rect1->h < rect2->y || rect2->y + rect2->h < rect1->y);
}

void check_jump(SDL_Rect* player_rect, SDL_Rect* hit_rect, int* jump, int* check)
{
    if (*jump == 1 && player_rect->y > hit_rect->y-130)
    {
        *check = 0;
        player_rect->y--;
        if (player_rect->y == hit_rect->y - 130)
            *jump = 0;
    }
    else if (*jump == 0)
    {
        if (checkCollision(player_rect, hit_rect))
        {
            player_rect->y = hit_rect->y - 35;
            *check = 1;
        }
        else
            player_rect->y++;
    }
}

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("sdl", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    //이미지 불러오기
    SDL_Surface* image[num];
    for (int i = 0; i < num; i++)
    {
        char filename[120];
        sprintf(filename, "spike_%d.png", i + 1);
        image[i] = IMG_Load(filename);
    }

    //텍스처로 만들기
    SDL_Texture* texture[num];
    for (int i = 0; i < num; i++)
        texture[i] = SDL_CreateTextureFromSurface(renderer, image[i]);

    //이미지 해제
    for (int i = 0; i < num; i++)
        SDL_FreeSurface(image[i]);

    //영역 지정
    SDL_Rect hitbox1 = { 0,0,453,22 };//bg1
    SDL_Rect hitbox2 = { 0,0,334,22 };//bg1
    SDL_Rect hitbox3 = { 475,0,172,14 };//천장

    SDL_Rect hitbox4 = { 0,122,339,14 };
    SDL_Rect hitbox5 = { 0,148,589,11 };
    SDL_Rect hitbox6 = { 0,169,143,11 };
    SDL_Rect hitbox7 = { 0,189,455,10 };

    SDL_Rect hitbox8 = { 0,337,950,11 };
    SDL_Rect hitbox9 = { 0,359,145,7 };

    SDL_Rect h1 = { 0,222,205,11};
    SDL_Rect h2 = { 0,242,32,9 };
    SDL_Rect h3 = { 0,258,267,10 };
    SDL_Rect h4 = { 0,279,286,8 };

    //위치 설정
    SDL_Rect bg1 = { 0,0,1500,720 };
    SDL_Rect bg2 = { 0,0,1500,720 };
    SDL_Rect bg3 = { 0,0,1500,720 };
    SDL_Rect bg4 = { 0,0,1500,720 };
    SDL_Rect hide1 = { 0,0,1500,720 };
    SDL_Rect hide2 = { 0,0,1500,720 };
    SDL_Rect player = { 0,503,36,35 };
    SDL_Rect player2 = { 0,438,36,35 };
    SDL_Rect player3 = { 0,368,36,35 };
    SDL_Rect player4 = { 0,577,36,35 };

    SDL_Rect spike = { 0,-310,1505,720 };
    SDL_Rect kill = { -700,0,1505,720 };
    SDL_Rect you = { 700,0,1505,720 };

    SDL_Rect rect1 = { -120,539,453,22 };
    SDL_Rect rect2 = { 438, 504,350,22 };
    SDL_Rect rect3 = { 778,439,334,22 };
    SDL_Rect rect4 = { 1118,474,453,22 };
    SDL_Rect rect5 = { 876, 318,172, 14 };//천장

    SDL_Rect rect6 = { 0,473,339,14};
    SDL_Rect rect7 = { 341,537,589,11};
    SDL_Rect rect8 = { 918,470,143,11 };
    SDL_Rect rect9 = { 1050,403,455,10 };

    SDL_Rect bit = { 935,515, 16,16};
    SDL_Rect bit2 = { 935,515, 16,16 };
    SDL_Rect bit3 = { 0,0, 1500,720 };
    SDL_Rect bit4 = { 0,0, 1500,720 };

    SDL_Rect r1 = { 0,404,205,11 };
    SDL_Rect r2 = { 335,337,32,9 };
    SDL_Rect r3 = { 401,371,32,9 };
    SDL_Rect r4 = { 569,303,32,9 };
    SDL_Rect r5 = { 636,337,32,9 };
    SDL_Rect r6 = { 706,371,32,9 };
    SDL_Rect r7 = { 841,439,267,10 };
    SDL_Rect r8 = { 1075,333,32,9 };//천장
    SDL_Rect r9 = { 1210,439,286,8 };

    SDL_Rect f1 = { 0,610,950,11 };
    SDL_Rect f2 = { 970,540,145,7 };
    SDL_Rect f3 = { 1108, 472,145,7 };
    SDL_Rect f4 = { 1245,404,145,7 };

    SDL_Event e;
    int quit = 0;
    int time = 0;
    int color = 0;
    int jump = 0;
    int check = 1;
    int move = 0;

    // 메인 루프
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = 1;
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_e)
                    quit = 1;
                if (e.key.keysym.sym == SDLK_SPACE)
                {
                    color = 1;
                    if(check == 1)
                        jump =1;
                }
            }
            else if (e.type == SDL_KEYUP)
            {
                if (e.key.keysym.sym == SDLK_SPACE)
                    color = 0;
            }
        }

        SDL_RenderClear(renderer);

        //조건
        if (player.x < 1280)
        {
            if (player.x < 100)
            {
                spike.y+=3;
                kill.x+=7;
                you.x-=7;
            }
            else if (player.x >= 150 && player.x < 250)
            {
                spike.y -= 5;
                kill.y += 5;
                you.y += 5;
            }

            SDL_RenderCopy(renderer, texture[4], NULL, &bg1); //bg1
            SDL_RenderCopy(renderer, texture[10], NULL, &player); //player
            SDL_RenderCopy(renderer, texture[1], NULL, &spike);
            SDL_RenderCopy(renderer, texture[2], NULL, &kill);
            SDL_RenderCopy(renderer, texture[3], NULL, &you);
            //SDL_RenderCopy(renderer, texture[12], &hitbox1, &rect1);
            //SDL_RenderCopy(renderer, texture[12], &hitbox2, &rect2); 
            //SDL_RenderCopy(renderer, texture[12], &hitbox1, &rect3); 
            //SDL_RenderCopy(renderer, texture[12], &hitbox1, &rect4); 
            //SDL_RenderCopy(renderer, texture[12], &hitbox3, &rect5); //천장

            player.x++;

            if (!(player.x % 6))
            {
                bg1.x--;
                rect1.x--;
                rect2.x--;
                rect3.x--;
                rect4.x--;
                rect5.x--;
            }

            if (player.x < 330)
                check_jump(&player, &rect1, &jump, &check);
            else if (player.x >= 330 && player.x < 650)
                check_jump(&player, &rect2, &jump, &check);
            else if (player.x >= 650 && player.x < 930)
            {
                check_jump(&player, &rect3, &jump, &check);
                if (checkCollision(&player, &rect5))
                {
                    player.y += 3;
                    jump = 0;
                }
            }
            else if (player.x >= 930 && player.x < 1280)
                check_jump(&player, &rect4, &jump, &check);
        }
        else if (player.x == 1280)
            move = 1;

        if (player2.x < 1280 && move == 1)
        {
            SDL_RenderCopy(renderer, texture[5], NULL, &bg2); //bg2
            SDL_RenderCopy(renderer, texture[10], NULL, &player2); //player2
            //SDL_RenderCopy(renderer, texture[12], &hitbox4, &rect6);
            //SDL_RenderCopy(renderer, texture[12], &hitbox5, &rect7);
            //SDL_RenderCopy(renderer, texture[12], &hitbox6, &rect8);
            //SDL_RenderCopy(renderer, texture[12], &hitbox7, &rect9);
            SDL_RenderCopy(renderer, texture[11], NULL, &bit);
            SDL_RenderCopy(renderer, texture[11], NULL, &bit2);
            SDL_RenderCopy(renderer, texture[14], NULL, &bit3);
            SDL_RenderCopy(renderer, texture[14], NULL, &bit4);
            SDL_RenderCopy(renderer, texture[8], NULL, &hide1);

            player2.x++;

            if (!(player2.x % 6))
            {
                bg2.x--;
                rect6.x--;
                rect7.x--;
                rect8.x--;
                rect9.x--;
                bit.x--;
                bit2.x--;
                bit3.x--;
                bit4.x--;
                hide1.x--;
                hide2.x--;
            }

            if (player2.x < 300)
            {
                bit.x -= 2;
                check_jump(&player2, &rect6, &jump, &check);
            }
            else if (player2.x >= 300 && player2.x < 780)
            {
                if (bit2.x > 255)
                    bit2.x -= 2;
                check_jump(&player2, &rect7, &jump, &check);
            }
            else if (player2.x >= 780 && player2.x < 930)
            {
                bit3.y--;
                check_jump(&player2, &rect8, &jump, &check);
            }

            else if (player2.x >= 930 && player2.x < 1280)
            {
                if (player2.x >= 1180 && player2.x < 1280)
                    bit4.y--;
                check_jump(&player2, &rect9, &jump, &check);
            }
        }
        else if(player2.x == 1280)
            move = 2;
        
        if (player3.x < 1280 && move == 2)
        {
            SDL_RenderCopy(renderer, texture[6], NULL, &bg3); //bg3
            SDL_RenderCopy(renderer, texture[10], NULL, &player3); //player3

            //SDL_RenderCopy(renderer, texture[12], &h1, &r1);
            //SDL_RenderCopy(renderer, texture[12], &h2, &r2);
            //SDL_RenderCopy(renderer, texture[12], &h2, &r3);
            //SDL_RenderCopy(renderer, texture[12], &h2, &r4);
            //SDL_RenderCopy(renderer, texture[12], &h2, &r5);
            //SDL_RenderCopy(renderer, texture[12], &h2, &r6);
            //SDL_RenderCopy(renderer, texture[12], &h2, &r8);//천장
            //SDL_RenderCopy(renderer, texture[12], &h3, &r7);
            //SDL_RenderCopy(renderer, texture[12], &h4, &r9);

            player3.x++;

            if (!(player3.x % 6))
            {
                bg3.x--;
                r1.x--;
                r2.x--;
                r3.x--;
                r4.x--;
                r5.x--;
                r6.x--;
                r7.x--;
                r8.x--;
                r9.x--;
            }

            if (player3.x < 250)
                check_jump(&player3, &r1, &jump, &check);
            else if (player3.x >= 250 && player3.x < 280)
                check_jump(&player3, &r2, &jump, &check);
            else if (player3.x >= 300 && player3.x < 480)
                check_jump(&player3, &r3, &jump, &check);
            else if (player3.x >= 480 && player3.x < 540)
                check_jump(&player3, &r4, &jump, &check);
            else if (player3.x >= 540 && player3.x < 600)
                check_jump(&player3, &r5, &jump, &check);
            else if (player3.x >= 600 && player3.x < 840)
                check_jump(&player3, &r6, &jump, &check);
            else if (player3.x >= 840 && player3.x < 1100)
                check_jump(&player3, &r7, &jump, &check);
            else if (player3.x >= 1100 && player3.x < 1280)
                check_jump(&player3, &r9, &jump, &check);
        }
        else if (player3.x == 1280)
            move = 3;

        if (player4.x < 1280 && move == 3)
        {
            SDL_RenderCopy(renderer, texture[7], NULL, &bg4); //bg4
            SDL_RenderCopy(renderer, texture[10], NULL, &player4); //player4
            
            //SDL_RenderCopy(renderer, texture[12], &hitbox8, &f1);
            //SDL_RenderCopy(renderer, texture[12], &hitbox9, &f2);
            //SDL_RenderCopy(renderer, texture[12], &hitbox9, &f3);
            //SDL_RenderCopy(renderer, texture[12], &hitbox9, &f4);

            player4.x++;

            if (!(player4.x % 6))
            {
                bg4.x--;
                f1.x--;
                f2.x--;
                f3.x--;
                f4.x--;
            }

            if (player4.x < 820)
                check_jump(&player4, &f1, &jump, &check);
            else if (player4.x >= 820 && player4.x < 970) 
                check_jump(&player4, &f2, &jump, &check);
            else if (player4.x >= 970 && player4.x < 1100)
                check_jump(&player4, &f3, &jump, &check);
            else if (player4.x >= 1100 && player4.x < 1280)
                check_jump(&player4, &f4, &jump, &check);
 
        }

        SDL_RenderCopy(renderer, texture[0], NULL, NULL);// 폰트박스
        if (color)
            SDL_RenderCopy(renderer, texture[13], NULL, NULL); //노란색 글자

        //printf("%d\n", player4.x);
        SDL_Delay(3);
        SDL_RenderPresent(renderer);
    }

    // 리소스 해제
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);

    IMG_Quit();
    SDL_Quit();
}
*/
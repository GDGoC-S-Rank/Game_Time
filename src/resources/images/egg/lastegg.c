
#include "SDL.h"
#include "SDL_timer.h"
#include "SDL_image.h"
#include <stdio.h>

#pragma comment(lib, "SDL2_image.lib")

#define num 8

void spike_collision(SDL_Rect* player, SDL_Rect* collide, int*count)
{
    if (collide->x < player->x - 30)
    {
        switch (*count)
        {
        case 1:
            collide->x= 1555;
            *count = 2;
            break;
        case 2:
            collide->x = 880;
            *count = 3;
            break;
        case 3:
            collide->x = 810;
            *count = 4;
            break;
        case 4:
            collide->x = 1360;
            *count = 5;
            break;
        case 5:
            collide->x = 2100;
            *count = 6;
            break;
        case 6:
            collide->x = 870;
            *count = 7;
            break;
        case 7:
            collide->x = 1220;
            break;
        }
    }
}

int collision_check(SDL_Rect* rect1, SDL_Rect* rect2)
{
    return !(rect1->x + rect1->w < rect2->x || rect2->x + rect2->w < rect1->x ||
        rect1->y + rect1->h < rect2->y || rect2->y + rect2->h < rect1->y);
}

void jump_check(SDL_Rect* player, int* jump, int n, int f)
{
    if (*jump == 1 && player->y > n)
        player->y--;
    else
        *jump = 0;

    if (*jump == 0 && player->y < f)
        player->y++;
}

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("sdl", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    //이미지,텍스처
    SDL_Surface* image[num];
    SDL_Texture* texture[num];
    for (int i = 0; i < num; i++)
    {
        char filename[200];
        sprintf(filename, "egg%d.png", i);
        image[i] = IMG_Load(filename);
        texture[i] = SDL_CreateTextureFromSurface(renderer, image[i]);
        SDL_FreeSurface(image[i]);
    }

    //영역지정
    SDL_Rect player_rect = { 649,321,38,77 };
    SDL_Rect player2_rect = { 655,411,21,39 };
    SDL_Rect playerjump_rect = { 754,322,42,77}; 
    SDL_Rect playerjump2_rect = { 734,411,25,39 };

    SDL_Rect floor_rect = { 65,180,50,20 };
    SDL_Rect redfloor_rect = { 12,428,67,15 };
    SDL_Rect redfloor_rect2 = { 98,428,134,20 }; //2칸
    SDL_Rect redfloor_rect3 = { 253,428, 202,20}; //3칸
    SDL_Rect bluefloor_rect = { 13,468,124,20 };//긴
    SDL_Rect bluefloor_rect2 = { 151,468,67,15 };//짧
    SDL_Rect egg_rect = {22,328,55,65 };
    SDL_Rect shrink_rect = { 597,147,132,145 };
    SDL_Rect iconbg_rect = { 221,161,179,146 };
    SDL_Rect laser_rect = { 438,152,157,157 };
    SDL_Rect shoot_rect = { 0,35,806,95};
    SDL_Rect title_rect = { 100,322,546,89 };

    SDL_Rect collide_rect = { 98,428,25,30 }; 
    SDL_Rect collide2_rect = { 13,468,25,30 };

    //위치지정
    SDL_Rect bg = { 0,0,1280,720 };
    SDL_Rect player = { 440,470,38,77 };
    SDL_Rect player2 = { 440,434,21,39 };
    SDL_Rect floor = { 430,540,50,20 };
    SDL_Rect egg = { 1968,147,55,65 };
    SDL_Rect egg2 = { 5741,197,55,65 };
    SDL_Rect shrink = { 906,-130,132,145 };
    SDL_Rect iconbg = { 904,124,179,146 };
    SDL_Rect icontime = { 904,124,179,146 };
    SDL_Rect laser = { 904,-150,157,157 };
    SDL_Rect box4 = { 7428, 338, 268,66 };
    SDL_Rect title = { 136,124,546,89 };

    SDL_Rect redfloor = { 955,474,67,15 };
    SDL_Rect redfloor2 = { 1763,474,67,15 };
    SDL_Rect redfloor3 = { 2167,474,67,15 };
    SDL_Rect redfloor4 = { 2907,474,134,20 };
    SDL_Rect redfloor5 = { 3447,474,202,20 };
    SDL_Rect redfloor6 = { 4528,474,67,15 };
    SDL_Rect redfloor7 = { 5741,474,67,15 };
    SDL_Rect redfloor8 = { 6551,474,67,15 };
    SDL_Rect redfloor9 = { 6686,474,67,15 };

    SDL_Rect bluefloor = {1297,410,124,20 }; //406
    SDL_Rect bluefloor2 = { 2572,410,67,15 };
    SDL_Rect bluefloor3 = { 4393,410,67,15 };
    SDL_Rect bluefloor4 = { 5005,410,124,20 };
    SDL_Rect bluefloor5 = { 5478,410,124,20 };
    SDL_Rect bluefloor6 = { 6415,410,67,15 };

    SDL_Rect spike = { 0,1,8692,720};
    SDL_Rect collide = { 1717,507,25,30 };
    SDL_Rect collide2 = { 3671,441,25,30 };

    SDL_Event e;
    int quit = 0;
    int color = 0;
    int color2 = 0;
    int jump = 0;
    int angle = 0;
    int height = 0;
    int height2 = 0;
    int use = 0;
    int n = 330;//수축했을 때 점프 높이
    int n2 = 330;
    int f = 470; //바닥에 떨어지는 정도
    int item = 0;
    int time = 0;
    int count = 1;
    Uint32 alpha = 255;

    SDL_SetTextureAlphaMod(texture[5], 0);

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

                else if (e.key.keysym.sym == SDLK_SPACE)
                {
                    color = 1;
                    jump = 1;
                }
                else if (e.key.keysym.sym == SDLK_UP)
                {
                    color2 = 1;
                    if(item ==1 || item ==2)
                        use = 1;
                }
            }
            else if (e.type == SDL_KEYUP)
            {
                if (e.key.keysym.sym == SDLK_SPACE)
                {
                    color = 0;
                }
                else if (e.key.keysym.sym == SDLK_UP)
                {
                    color2 = 0;
                }
            }
        }

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture[0], &iconbg_rect, &iconbg);
        SDL_RenderCopy(renderer, texture[5], NULL, &icontime);
        SDL_RenderCopy(renderer, texture[1], NULL, NULL);
        SDL_RenderCopy(renderer, texture[2], NULL, &spike);
        SDL_RenderCopy(renderer, texture[0], &shrink_rect, &shrink);
        SDL_RenderCopy(renderer, texture[0], &laser_rect, &laser);
        //SDL_RenderCopy(renderer, texture[0], &floor_rect, &floor);
        SDL_RenderCopy(renderer, texture[0], &egg_rect, &egg);
        SDL_RenderCopy(renderer, texture[0], &egg_rect, &egg2);
        SDL_RenderCopy(renderer, texture[0], &title_rect, &title);

        SDL_SetTextureAlphaMod(texture[6], alpha);
        SDL_RenderCopy(renderer, texture[6], NULL, &box4);

        SDL_Rect shoot = { player.x, player.y-7, 806, 95 };

        if (!(use))
        {
            f = 470;
            if (jump)
            {
                SDL_RenderCopyEx(renderer, texture[0], &playerjump_rect, &player, angle, NULL, SDL_FLIP_NONE);
                angle += 2;
            }
            else
                SDL_RenderCopy(renderer, texture[0], &player_rect, &player);

            if (collision_check(&player, &collide) || collision_check(&player, &collide2))
                quit = 1;

            jump_check(&player, &jump, n, f);
        }

        else
        {
            if (item == 1)
            {
                player.y = 470;
                f = 500;
                if (jump)
                {
                    SDL_RenderCopyEx(renderer, texture[0], &playerjump2_rect, &player2, angle, NULL, SDL_FLIP_NONE);
                    angle += 2;
                }
                else
                    SDL_RenderCopy(renderer, texture[0], &player2_rect, &player2);

                SDL_SetTextureAlphaMod(texture[5], 255);
                if (!(spike.x % 8) && icontime.y < 250)
                    icontime.y++;
                else if (icontime.y == 245)
                {
                    shrink.y = -130;
                    use = 0;
                }
                if (collision_check(&player2, &collide) || collision_check(&player2, &collide2))
                    quit = 1;
                if (collision_check(&player2, &redfloor4) || collision_check(&player2, &redfloor5))
                {
                    player2.y = 434;
                    n2 = 344;
                }
                if (collision_check(&player2, &floor))
                {
                    player2.y = 504;
                    n2 = 405;
                }
                jump_check(&player2, &jump, n2, f);
            }

            else if (item == 2)
            {
                time++;
                laser.y = -130;
                if (time >= 0 && time < 50)
                    SDL_RenderCopy(renderer, texture[0], &shoot_rect, &shoot);//player.y에 따라
                else
                    shoot.y = 800;

                if (collision_check(&shoot, &box4))
                    alpha = 0;

                if (collision_check(&player, &box4) && alpha ==255)//상자가 파괴되지 않았을 때 닿으면 나가기
                    quit = 1;

                f = 470;
                if (jump)
                {
                    SDL_RenderCopyEx(renderer, texture[0], &playerjump_rect, &player, angle, NULL, SDL_FLIP_NONE);
                    angle += 2;
                }
                else
                    SDL_RenderCopy(renderer, texture[0], &player_rect, &player);

                if (collision_check(&player, &collide) || collision_check(&player, &collide2))
                    quit = 1;

                jump_check(&player, &jump, n, f);
            }   
        }

        //노란색 글자
        if (color)
            SDL_RenderCopy(renderer, texture[4], NULL, NULL);
        if (color2)
            SDL_RenderCopy(renderer, texture[3], NULL, NULL);

        spike.x--;
        redfloor.x--;
        redfloor2.x--;//높이
        redfloor3.x--;
        redfloor4.x--;
        redfloor5.x--;
        redfloor6.x--;
        redfloor7.x--;
        redfloor8.x--;
        redfloor9.x--;//높이
        bluefloor.x--;
        bluefloor2.x--;
        bluefloor3.x--;
        bluefloor4.x--;
        bluefloor5.x--;
        bluefloor6.x--;
        egg.x--;
        egg2.x--;
        box4.x--;
        collide.x--;
        collide2.x--;

        if (collision_check(&player, &redfloor) || collision_check(&player, &redfloor3)
            || collision_check(&player, &redfloor7) || collision_check(&player, &redfloor8))
        {
            player.y = 402;
            n = 250;
        }
        if (collision_check(&player, &redfloor6))
        {
            player.y = 402;
            n = 340;
        }
        if (collision_check(&player, &bluefloor) || collision_check(&player, &bluefloor2) 
            || collision_check(&player, &bluefloor4) || collision_check(&player, &bluefloor5)
            || collision_check(&player, &bluefloor6) || collision_check(&player, &bluefloor3))
        {
            player.y = 334;
            n = 206;
        }
        if (collision_check(&player, &floor))
        {
            n = 330;
        }
        if (collision_check(&player, &redfloor2) || collision_check(&player, &redfloor9))
        {
            n = 140;
            jump = 1;
        }
        if (collision_check(&player, &egg))
        {
            item = 1;
            egg.y -= 400;
            shrink.y = 85;
        }
        if (collision_check(&player, &egg2))
        {
            item = 2;
            egg2.y -= 400;
            laser.y = 80;
        } 

        if (spike.x < 0 && spike.x >= -80)
        {
            title.x--;
        }
        else if (spike.x < -250 && spike.x >= -400)
        {
            title.y-=4;
        }
        if (spike.x < -3500 && spike.x >= -4000)
        {
            collide2.x = 625;
            collide2.y = 237;
        }
        else if (spike.x < -6100 && spike.x >= -6150)
        {
            collide2.x = 830;
            collide2.y = 237;
        }
        else if (spike.x < -8000 && spike.x >= -8050)
            SDL_RenderCopy(renderer, texture[7], NULL, NULL);
        else if (spike.x < -8200 && spike.x >= -8250)
            SDL_RenderCopy(renderer, texture[7], NULL, NULL);
        else if (spike.x < -8300 && spike.x >= -8350)
            SDL_RenderCopy(renderer, texture[7], NULL, NULL);
        else if (spike.x < -8400 && spike.x >= -8450)
            SDL_RenderCopy(renderer, texture[7], NULL, NULL);

        if (spike.x <= -7800)
        {
            collide.y = 900;
            collide2.y = 900;
            for (int i = 0; i < 7; i++)
                SDL_DestroyTexture(texture[i]);
        }

        spike_collision(&player, &collide, &count);
        //printf("%d\n", spike.x);

        SDL_Delay(1);
        SDL_RenderPresent(renderer);
    }

    IMG_Quit();
    SDL_Quit();
}

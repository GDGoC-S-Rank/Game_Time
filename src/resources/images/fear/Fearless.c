/*
#include "SDL.h"
#include "SDL_timer.h"
#include "SDL_image.h"
#include <stdio.h>

#pragma comment(lib, "SDL2_image.lib")

#define num 33

int collision_check(SDL_Rect* rect1, SDL_Rect* rect2)
{
    return (!(rect1->x + rect1->w < rect2->x || rect2->x + rect2->w < rect1->x)); //안 닿았을 때
}

void jump_check(SDL_Rect* player, int* jump)
{
    if (*jump == 1 && player->y > 295)
        player->y--;
    else
        *jump = 0;

    if (*jump == 0 && player->y <= 393)
        player->y++;
}

void move_check(SDL_Rect* move, SDL_Rect* target, int* move_x, int check)
{
    if (check)
    {
        switch (*move_x)
        {
        case 1:
            if (move->x > 775)
            {
                move->x -= 1;
                target->x -= 1;
            }
            else
                *move_x *= -1;
            break;

        case -1:
            if (move->x < 1082)
            {
                move->x += 1;
                target->x += 1;
            }
            else
                *move_x *= -1;
            break;

        case 0:
            break;

        }
    }
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
        sprintf(filename, "fear%d.png", i);
        image[i] = IMG_Load(filename);
        texture[i] = SDL_CreateTextureFromSurface(renderer, image[i]);
        SDL_FreeSurface(image[i]);
    }

    SDL_Rect rect = { 0,0,99,74 };
    SDL_Rect fade1 = { -1280,0,1280,720 };
    SDL_Rect fade2 = { 1280,0,1280,720 };
    SDL_Rect bg = { 0,0,7000,720 };
    SDL_Rect bg2 = { 0,0,7000,720 };
    SDL_Rect bg3 = { 0,0,7000,720 };
    SDL_Rect ghost = { 85,350,221,311 };
    SDL_Rect spike1 = { 1205,535,90,87 };
    SDL_Rect spike2 = { 1980,535,90,87 };
    SDL_Rect spike3 = { 2797,535,90,87 };
    SDL_Rect spike4 = { 3570,535,90,87 };
    SDL_Rect spike5 = { 4382,535,90,87 };
    SDL_Rect spike6 = { 5160,535,90,87 };
    SDL_Rect fox1 = { 1521,393,137,231 };
    SDL_Rect fox2 = { 4703,393,137,231 };
    SDL_Rect fox1_collide = { 1600,393,152, 22 };
    SDL_Rect fox2_collide = { 4773,393,152, 22 };
    SDL_Rect player = {550,393,156,230 };
    SDL_Rect player2 = { 557,357,156,260 }; //칼 위로 자세
    SDL_Rect sword_bar = { 635,230,519,124 };
    SDL_Rect sword_bar2 = { 635,230,519,124 };
    SDL_Rect move = { 1082,243,39,108 };
    SDL_Rect target = { 1082,278,39,39 };
    SDL_Rect font = { 628,135,547,55 };
    SDL_Rect collidebox1 = { 880,286,152,22 };
    SDL_Rect collidebox2 = { 943,285,29,22 };
    SDL_Rect sword = { 550,393,156,230 };
    SDL_Rect text = { 100,265,413,67 };

    SDL_Event e;
    int quit = 0;
    int color = 0;
    int color2 = 0;
    int jump = 0;
    int move_x = 1; //1이면 왼쪽 방향, -1이면 오른쪽 방향, 0이면 멈춤
    int check; //칼bar가 표시될 때
    int attack = 0;
    int collide = 0;
    int complete = 0;
    int time = 0;
    int glow = 0;
    Uint32 lastFrameTime = 0;
    Uint32 alpha = 255;
    Uint32 alpha2 = 255;
    int current_frame = 1;
    int current_frame_char = 3;

    SDL_SetTextureAlphaMod(texture[23], 0);
    SDL_SetTextureAlphaMod(texture[30], 0);

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
                    if(check)//칼bar가 표시되었을때만 위쪽을 눌렀을 때 공격가능하게 한다
                        attack = 1;
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

        //애니메이션(2프레임)
        Uint32 current_time = SDL_GetTicks();
        if (current_time - lastFrameTime > 200)
        {
            current_frame = (current_frame + 1) % 2;
            current_frame_char = (current_frame_char + 1) % 4;
            lastFrameTime = current_time;
        }

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture[0], NULL, NULL);
        SDL_RenderCopy(renderer, texture[1], NULL, &bg3);
        SDL_RenderCopy(renderer, texture[2], NULL, &bg2);
        SDL_RenderCopy(renderer, texture[3], NULL, &bg2);
        SDL_RenderCopy(renderer, texture[4], NULL, &bg);
        SDL_RenderCopy(renderer, texture[5], NULL, &bg);
        SDL_RenderCopy(renderer, texture[6], NULL, &bg);
        SDL_RenderCopy(renderer, texture[26], NULL, NULL);//fontbox

        SDL_SetTextureAlphaMod(texture[21], alpha);
        SDL_SetTextureAlphaMod(texture[24], alpha);
        SDL_SetTextureAlphaMod(texture[25], alpha);

        SDL_RenderCopy(renderer, texture[21], NULL, &sword_bar);
        SDL_RenderCopy(renderer, texture[30], NULL, &sword_bar2);
        SDL_RenderCopy(renderer, texture[22], NULL, &move);
        SDL_RenderCopy(renderer, texture[23], NULL, &target);

        //맞추기1
        if (bg.x <= 0 && bg.x >= -920)
        {
            if (alpha2 > 0 && bg.x<=-300)
                alpha2--;

            check = 1;
            //SDL_RenderCopy(renderer, texture[31], NULL, &collidebox1);//나중에 지워도 됌
            if (attack)
            {
                move_x = 0;
                SDL_SetTextureAlphaMod(texture[23], 255);//과녁
                SDL_SetTextureAlphaMod(texture[22], 0);

                if (collision_check(&move, &collidebox1))
                    complete = 1;
                else
                    complete = 0;
            }
        }
        //사라짐, 초기화
        else if (bg.x <= -800 && bg.x >= -1005)
        {
            alpha -= 3;
            SDL_SetTextureAlphaMod(texture[23], alpha);
        }
        else if (bg.x <= -1005 && bg.x >= -1200)
        {
            SDL_DestroyTexture(texture[21]);
            SDL_DestroyTexture(texture[24]);
            SDL_DestroyTexture(texture[25]);
            check = 0;
            attack = 0;
            target.x = 1082;
            move.x = 1082;
        }
        else if (bg.x <= -2900 && bg.x >= -2901)
        {
            SDL_SetTextureAlphaMod(texture[11], 255);//여우
            SDL_SetTextureAlphaMod(texture[12], 255);
            move_x = 1;
            complete = 0;
            time = 0;
        }
        //맞추기2
        else if (bg.x <= -3000 && bg.x >= -3920)
        {
            //SDL_RenderCopy(renderer, texture[32], NULL, &collidebox2);//나중에 지워도 됌
            check = 1;
            if(alpha < 255)
                alpha ++;
            SDL_SetTextureAlphaMod(texture[22], alpha);
            SDL_SetTextureAlphaMod(texture[30], alpha);

            if (attack)
            {
                move_x = 0;
                SDL_SetTextureAlphaMod(texture[23], 255);
                SDL_SetTextureAlphaMod(texture[22], 0);

                if (collision_check(&move, &collidebox2))
                    complete = 1;
                else
                    complete = 0;
            }
        }
        //사라짐
        else if (bg.x <= -4300 && bg.x >= -4384)
        {
            alpha -= 3;
            SDL_SetTextureAlphaMod(texture[23], alpha);
            SDL_SetTextureAlphaMod(texture[30], alpha);
        }

        //특정 시간 구간이 아닌 곳에서는 공격하지 않는다
        else
            check = 0;

        //여우 충돌했을 때 
        if (collision_check(&player, &fox1_collide) || collision_check(&player, &fox2_collide))
        {
            time++;
            if (complete)
            {
                if (time >= 0 && time <= 80)
                {
                    SDL_SetTextureAlphaMod(texture[20], 255);
                    SDL_RenderCopy(renderer, texture[20], NULL, &player2); //칼 위로 자세
                    SDL_RenderCopy(renderer, texture[13], NULL, &fox1); //잔상
                    SDL_RenderCopy(renderer, texture[13], NULL, &fox2); //잔상
                    SDL_SetTextureAlphaMod(texture[11], 0);//여우
                    SDL_SetTextureAlphaMod(texture[12], 0);
                    SDL_SetTextureAlphaMod(texture[14], 0);//걷는모션
                    SDL_SetTextureAlphaMod(texture[15], 0);
                    SDL_SetTextureAlphaMod(texture[16], 0);
                    SDL_SetTextureAlphaMod(texture[17], 0);
                }
                else
                {
                    SDL_SetTextureAlphaMod(texture[20], 0);
                    SDL_SetTextureAlphaMod(texture[14], 255);
                    SDL_SetTextureAlphaMod(texture[15], 255);
                    SDL_SetTextureAlphaMod(texture[16], 255);
                    SDL_SetTextureAlphaMod(texture[17], 255);
                } 
            }
            else
            {
                quit = 1;
                printf("collide");
            }
        }

        //4프레임 애니메이션
        switch (current_frame_char)
        {
        case 0:
            SDL_RenderCopy(renderer, texture[14], NULL, &player);
            if(glow)
                SDL_RenderCopy(renderer, texture[18], NULL, &player);
            break;
        case 1:
            SDL_RenderCopy(renderer, texture[15], NULL, &player);
            break;
        case 2:
            SDL_RenderCopy(renderer, texture[16], NULL, &player);
            if (glow)
                SDL_RenderCopy(renderer, texture[19], NULL, &player);
            break;
        case 3:
            SDL_RenderCopy(renderer, texture[17], NULL, &player);
            break;
        }
        
        //2프레임 애니메이션
        if (!(current_frame))
        {
            SDL_RenderCopy(renderer, texture[7], NULL, &ghost);
            SDL_RenderCopy(renderer, texture[9], NULL, &spike1);
            SDL_RenderCopy(renderer, texture[9], NULL, &spike2);
            SDL_RenderCopy(renderer, texture[9], NULL, &spike3);
            SDL_RenderCopy(renderer, texture[9], NULL, &spike4);
            SDL_RenderCopy(renderer, texture[9], NULL, &spike5);
            SDL_RenderCopy(renderer, texture[9], NULL, &spike6);
            SDL_RenderCopy(renderer, texture[11], NULL, &fox1);
            SDL_RenderCopy(renderer, texture[11], NULL, &fox2);
        }
        else
        {
            SDL_RenderCopy(renderer, texture[8], NULL, &ghost);
            SDL_RenderCopy(renderer, texture[10], NULL, &spike1);
            SDL_RenderCopy(renderer, texture[10], NULL, &spike2);
            SDL_RenderCopy(renderer, texture[10], NULL, &spike3);
            SDL_RenderCopy(renderer, texture[10], NULL, &spike4);
            SDL_RenderCopy(renderer, texture[10], NULL, &spike5);
            SDL_RenderCopy(renderer, texture[10], NULL, &spike6);
            SDL_RenderCopy(renderer, texture[12], NULL, &fox1);
            SDL_RenderCopy(renderer, texture[12], NULL, &fox2);
        }

        //노란색 글자
        if(color)
            SDL_RenderCopy(renderer, texture[27], NULL, NULL);
        if (color2)
            SDL_RenderCopy(renderer, texture[28], NULL, NULL);

        bg.x--;
        spike1.x--;
        spike2.x--;
        spike3.x--;
        spike4.x--;
        spike5.x--;
        spike6.x--;
        fox1.x--;
        fox2.x--;
        fox1_collide.x--;
        fox2_collide.x--;

        SDL_RenderCopy(renderer, texture[24], NULL, &font);
        SDL_SetTextureAlphaMod(texture[29], alpha2);
        SDL_RenderCopy(renderer, texture[29], NULL, &text);
        jump_check(&player, &jump);
        move_check(&move, &target, &move_x, check);

        if (!(bg.x % 2))
        {
            bg2.x--;
            SDL_RenderCopy(renderer, texture[25], NULL, &font);
        }
        if (!(bg.x % 4))
        {
            bg3.x--;
        }

        //배경 사라짐 효과
        if (bg.x <= -5300 && bg.x >= -5350)
        {
            fade1.x += 2;
            fade2.x -= 2;
        }
        else if (bg.x <= -5500 && bg.x >= -5550)
        {
            fade1.x += 4;
            fade2.x -= 4;
        }
        else if (bg.x <= -5700 && bg.x >= -5750)
        {
            fade1.x += 4;
            fade2.x -= 4;
        }
        else if (bg.x <= -5900 && bg.x >= -5950)
        {
            fade1.x += 4;
            fade2.x -= 4;
        }

        //칼 효과
        if (bg.x <= -600 && bg.x >= -900)
            glow = 1;
        else if (bg.x <= -3650 && bg.x >= -3950)
            glow = 1;
        else
            glow = 0;

        SDL_RenderCopy(renderer, texture[26], &rect, &fade1);
        SDL_RenderCopy(renderer, texture[26], &rect, &fade2);

        //여우 충돌 박스 : 지워도 가능
        //SDL_RenderCopy(renderer, texture[31], NULL, &fox1_collide);
        //SDL_RenderCopy(renderer, texture[31], NULL, &fox2_collide);

        SDL_Delay(1);
        //printf("%d\n", bg.x);
        //printf("%d\n", complete);
        SDL_RenderPresent(renderer);
    }

    IMG_Quit();
    SDL_Quit();
}
*/
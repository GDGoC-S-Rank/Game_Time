/*
#include "SDL.h"
#include "SDL_timer.h"
#include "SDL_image.h"
#include <stdio.h>

#pragma comment(lib, "SDL2_image.lib")

#define num 22
#define num2 4

int collisionCheck(SDL_Rect* rect1, SDL_Rect* rect2)
{
    return!(rect1->x + rect1->w < rect2->x || rect2->x + rect2->w < rect1->x
        || rect1->y + rect1->h < rect2->y || rect2->y + rect2->h < rect1->y);
}

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("sdl", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    //애니메이션 이미지 불러오기
    SDL_Surface* image[num2];
    for (int i = 0; i < num2; i++)
    {
        char filename[40];
        sprintf(filename, "exitchar%d.png", i + 1);
        image[i] = IMG_Load(filename);
    }

    //이미지 불러오기
    SDL_Surface* image2[num];
    for (int i = 0; i < num; i++)
    {
        char filename2[100];
        sprintf(filename2, "exit%d.png", i + 1);
        image2[i] = IMG_Load(filename2);
    }

    //주인공 텍스처 만들기
    SDL_Texture* animate_texture[num2];
    for (int i = 0; i < num2; i++)
        animate_texture[i] = SDL_CreateTextureFromSurface(renderer, image[i]);

    //이미지 텍스처 만들기
    SDL_Texture* texture[num];
    for (int i = 0; i < num; i++)
        texture[i] = SDL_CreateTextureFromSurface(renderer, image2[i]);

    //주인공 이미지 해제
    for (int i = 0; i < num2; i++)
        SDL_FreeSurface(image[i]);

    //이미지 해제
    for (int i = 0; i < num; i++)
        SDL_FreeSurface(image2[i]);

    //위치 설정
    SDL_Rect bg = { 0,0,11380,720 };
    SDL_Rect bg2 = { 0,0,11380,720 };
    SDL_Rect bg3 = { 0,0,11380,720 };
    SDL_Rect bg4 = { 0,0,11380,720 };

    SDL_Rect light1 = { 100,-200,150,1000 };
    SDL_Rect light2 = { 400,-200,150,1000 };
    SDL_Rect light3 = { 600,-200,150,1000 };
    SDL_Rect light4 = { 1000,-200,150,1000 };
    SDL_Rect character = { 440,370,27,40 };
    SDL_Rect floor = { 437,408,35,20 };
    SDL_Rect center = { 1972,0,34,720 };
    SDL_Rect spike = { 1755,36,465,465 };
    SDL_Rect center2 = { 9330,-30,34,720 };
    SDL_Rect spike2 = { 9113, 10,465,465 };
    SDL_Rect effect = { 345,0,215,720 };
    SDL_Rect effect_hitbox = { 3860,0,34,720 };
    SDL_Rect effect_hitbox2 = { 7440,0,34,720 };//효과
    SDL_Rect jump_floor = { 4623,464,35,20 };
    SDL_Rect exit = { 49,111,307,142 };
    SDL_Rect path = { 902,524,352,137 };
    SDL_Rect fade1= { -1280,0,1280,720 };
    SDL_Rect fade2 = { 1280,0,1500,720 };

    SDL_Rect n2 = { 3145,146,185,185};//2번
    SDL_Rect n1 = { 3337,100,245,245 };//1번
    SDL_Rect n3 = { 4775,300,255,255 };//3번
    SDL_Rect n4 = { 7030,400,245,245 };//1번
    SDL_Rect n5 = { 7798,126,300,300 };//3번
    SDL_Rect n6 = { 9967,79,245,245 };//1번
    SDL_Rect n7 = { 10396,60,245,245 };//1번

    SDL_Point point = { 75, 720 };
    SDL_Point point3 = { 0,71 };
    SDL_Point point4 = { 352,64 };

    SDL_Event e;
    int quit = 0;
    int color = 0;
    int jump = 0;
    int time = 0;
    int currentFrame = 3;//그래야 0부터, 처음 프레임부터 시작함
    Uint32 lastFrameTime = 0;
    int angle = 0;
    int angle2 = 0;
    int angle3 = 0;
    int move = 0;
    int a = 0;
    int a2 = 0;
    int v = 1;
    int text_angle = 0;
    int text_angle2 = 0;

    SDL_SetTextureAlphaMod(texture[6], 0);
    SDL_SetTextureAlphaMod(texture[20], 0);

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
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
            }
            else if (e.type == SDL_KEYUP)
            {
                if (e.key.keysym.sym == SDLK_SPACE)
                {
                    color = 0;
                    jump = 0;
                }
            }
        }

        //프레임 변경
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastFrameTime > 150) //0.15초(150)
        {
            currentFrame = (currentFrame + 1) % 4;
            lastFrameTime = currentTime;
        }

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture[21], NULL, &bg4);//풍경
        SDL_RenderCopy(renderer, texture[15], NULL, &bg);//가시
        SDL_RenderCopy(renderer, texture[4], NULL, &bg2);//별
        SDL_RenderCopy(renderer, texture[5], NULL, &bg);//별

        SDL_RenderCopyEx(renderer, texture[2], NULL, &exit, text_angle, &point3, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[3], NULL, &path, text_angle2, &point4, SDL_FLIP_NONE);

        SDL_RenderCopyEx(renderer, texture[12], NULL, &light1, a, &point, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[13], NULL, &light2, a2, &point, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[14], NULL, &light3, a, &point, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[17], NULL, &light4, a2, &point, SDL_FLIP_NONE);

        SDL_RenderCopyEx(renderer, texture[7], NULL, &spike, angle2, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[7], NULL, &spike2, angle3, NULL, SDL_FLIP_NONE);

        SDL_RenderCopyEx(renderer, texture[9], NULL, &n2, angle, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[10], NULL, &n1, angle, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[11], NULL, &n3, angle, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[10], NULL, &n4, angle, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[11], NULL, &n5, angle, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[10], NULL, &n6, angle, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[10], NULL, &n7, angle, NULL, SDL_FLIP_NONE);

        SDL_RenderCopy(renderer, texture[8], NULL, &center);
        SDL_RenderCopy(renderer, texture[8], NULL, &center2);

        SDL_RenderCopy(renderer, texture[18], NULL, &fade1);
        SDL_RenderCopy(renderer, texture[19], NULL, &fade2);

        SDL_RenderCopy(renderer, texture[0], NULL, NULL);
        if (color)
            SDL_RenderCopy(renderer, texture[1], NULL, NULL);
        SDL_RenderCopy(renderer, animate_texture[currentFrame], NULL, &character);

        SDL_RenderCopy(renderer, texture[6], NULL, &effect);
        SDL_RenderCopy(renderer, texture[20], NULL, &effect);

        //SDL_RenderCopy(renderer, texture[16], NULL, &floor);
        //SDL_RenderCopy(renderer, texture[16], NULL, &effect_hitbox2);

        //반복
        if (bg.x > -10000)
        {
            bg.x--;
            center.x--;
            spike.x--;
            center2.x--;
            spike2.x--;
            n1.x--;
            n2.x--;
            n3.x--;
            n4.x--;
            n5.x--;
            n6.x--;
            n7.x--;
            effect_hitbox.x--;
            effect_hitbox2.x--;
            jump_floor.x--;

            //불빛
            if (!(bg.x % 30))
            {
                if (v == 1)
                {
                    a++;
                    a2--;
                    if (a > 35)
                        v *= -1;
                }
                else
                {
                    a--;
                    a2++;
                    if (a < -35)
                        v *= -1;
                }
            }

            if (!(bg.x % 2))
            {
                bg2.x--;
                angle++;
            }
            if (!(bg.x % 5))
                bg4.x--;
            if (bg.x < -1300 && bg.x > -1480)
                angle2++;
            else if (bg.x < -8700 && bg.x > -8880)
                angle3++;
        }
        else
        {
            character.x++;
            floor.x++;
        }

        //바닥
        if (bg.x < -600 && bg.x > -700)
        {
            text_angle++;
            text_angle2--;
            if (bg.x < -650 && bg.x > -700)
            {
                exit.x-=3;
                path.x+=3;
            }
        }
        else if (bg.x < -590 && bg.x > -2050)
            floor.y = 475;
        else if (bg.x <= -2050 && bg.x > -2190)
            floor.y = 900;
        else if (bg.x <= -2190 && bg.x > -2400)//1
            floor.y = 441;
        else if (bg.x <= -2400 && bg.x > -2600)//2
            floor.y = 474;
        else if (bg.x <= -2600 && bg.x > -3000)//3
            floor.y = 508;
        else if (bg.x <= -3000 && bg.x > -3200)
            floor.y = 407;
        else if (bg.x <= -3300 && bg.x > -3400)
        {
            floor.y = 273;
            if (collisionCheck(&character, &effect_hitbox))
            {
                character.y = 500;
                SDL_SetTextureAlphaMod(texture[6], 255);
            }
        }
        else if (bg.x <= -3400 && bg.x > -3800)
        {
            if (bg.x <= -3470)
                SDL_SetTextureAlphaMod(texture[6], 0);
            floor.y = 542;
        }
        else if (bg.x <= -3800 && bg.x > -4000)
            floor.y = 900;
        else if (bg.x <= -4000 && bg.x > -4200)
        {
            floor.y = 475;
            if (collisionCheck(&character, &jump_floor))
                move = 1;
        }
        else if (bg.x <= -4200 && bg.x > -4500)
        {
            if (move && bg.x > -4428)
                character.y -= 2;
            floor.y = 900;
        }
        else if (bg.x <= -4500 && bg.x > -5400)
            floor.y = 544;
        else if (bg.x <= -5400 && bg.x > -5800)
            floor.y = 576;
        else if (bg.x <= -5800 && bg.x > -6000)
            floor.y = 900;
        else if (bg.x <= -6000 && bg.x > -6200)
            floor.y = 441;
        else if (bg.x <= -6200 && bg.x > -6400)
            floor.y = 900;
        else if (bg.x <= -6400 && bg.x > -6650)
            floor.y = 305;
        else if (bg.x <= -6650 && bg.x > -6800)
            floor.y = 900;
        else if (bg.x <= -6800 && bg.x > -7000)
        {
            floor.y = 341;
            if (collisionCheck(&character, &effect_hitbox2))
            {
                character.y = 590;
                SDL_SetTextureAlphaMod(texture[20], 255);
            }
        }
        else if (bg.x <= -7000 && bg.x > -7150)
        {
            if(bg.x < -7020)
                SDL_SetTextureAlphaMod(texture[20], 0);
            floor.y = 611;
        }
        else if (bg.x <= -7150 && bg.x > -7350)
            floor.y = 900;
        else if (bg.x <= -7350 && bg.x > -8000)
            floor.y = 509;
        else if (bg.x <= -8000 && bg.x > -8400)
            floor.y = 344;
        else if (bg.x <= -8400 && bg.x > -8500)
            floor.y = 900;
        else if (bg.x <= -8500 && bg.x > -10000)
            floor.y = 442;

        if (time > 10500 && time < 11040)
            fade1.x += 2;
        else if (time > 11040 && time < 11700)
            fade2.x -= 2;

        //점프
        if (jump)
            character.y--;
        else if (!(jump))
        {
            if (collisionCheck(&character, &floor))
                character.y = floor.y-40;
            else
                character.y++;
        }

        time++;
        //printf("%d\n", time);
        SDL_Delay(1);
        SDL_RenderPresent(renderer);
    }

    IMG_Quit();
    SDL_Quit();
}
*/
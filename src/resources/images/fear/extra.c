/*
#include "SDL.h"
#include "SDL_timer.h"
#include "SDL_image.h"
#include <stdio.h>

#pragma comment(lib, "SDL2_image.lib")

#define num 5

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

    //이미지 불러오기
    SDL_Surface* image[num];
    for (int i = 0; i < num; i++)
    {
        char filename[30];
        sprintf(filename, "extra%d.png", i + 1);
        image[i] = IMG_Load(filename);
    }

    //텍스처 만들기
    SDL_Texture* texture[num];
    for (int i = 0; i < num; i++)
        texture[i] = SDL_CreateTextureFromSurface(renderer, image[i]);

    //이미지 해제
    for (int i = 0; i < num; i++)
        SDL_FreeSurface(image[i]);

    //위치 설정
    SDL_Rect bg = { 0,0,1280,720 };
    SDL_Rect player1 = { 554,370,210,222 };
    SDL_Rect player2 = { 554,370,210,222 };
    SDL_Rect sword = { 553,-40,206,38 };
    SDL_Rect box = { 570,450,24,13 };

    SDL_Event e;
    int quit = 0;
    int check = 0;

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
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture[0], NULL, NULL);
        SDL_RenderCopy(renderer, texture[1], NULL, &player1);
        SDL_RenderCopy(renderer, texture[3], NULL, &sword);
        //SDL_RenderCopy(renderer, texture[4], NULL, &box);

        if (collisionCheck(&box, &sword))
        {
            check = 1;
            SDL_SetTextureAlphaMod(texture[1], 0);
            SDL_SetTextureAlphaMod(texture[3], 0);
        }
        
        if(check)
            SDL_RenderCopy(renderer, texture[2], NULL, &player2);

        sword.y++;
 
        SDL_Delay(1);
        SDL_RenderPresent(renderer);
    }

    IMG_Quit();
    SDL_Quit();
}
*/
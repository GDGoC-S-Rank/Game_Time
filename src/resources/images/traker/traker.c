/*
#include "SDL.h"
#include "SDL_timer.h"
#include "SDL_image.h"
#include <stdio.h>

#pragma comment(lib, "SDL2_image.lib")

#define num 9

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("sdl", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    //이미지 불러오기
    SDL_Surface* image[num];
    for (int i = 0; i < num; i++)
    {
        char filename[70];
        sprintf(filename, "traker%d.png", i + 1);
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
    SDL_Rect font = { 5, 7, 642, 103 };
    SDL_Rect player = { 647, 0, 88, 88 }; 
    SDL_Rect r1 = { 285, 149, 273, 268 };//다이아몬드 모양
    SDL_Rect c1 = { 0, 110, 71, 286 }; //기둥
    SDL_Rect rotate1 = { 605, 133, 75,76 }; //회전 중심
    SDL_Rect t1 = { 809, 0, 74, 725 }; //t모양 받침대
    SDL_Rect t3 = { 936, 0, 71, 890 }; //t모양 막대기
    SDL_Point center = { 321, 51 };
    
    //표시할 위치
    SDL_Rect font2 = { 1280, 310, 642, 103 };
    SDL_Rect bg = { 0, 0, 12500, 720 };
    SDL_Rect player2 = { 400, 350, 84, 84 }; //88 88
    SDL_Rect r2 = { 1150, 270, 273, 268 };//다이아몬드 모양
    SDL_Rect r3 = { 6277, 270, 273, 268 };
    SDL_Rect r4 = { 9045, 270, 273, 268 };

    SDL_Rect t2 = { 5638, 0, 74, 725 }; //t모양 받침대
    SDL_Rect t4 = { 5640, -120, 71, 890 }; //t모양 막대기
    SDL_Rect t5 = { 8335, 0, 74, 725 }; //t모양 받침대
    SDL_Rect t6 = { 8335, 50, 71, 890 }; //t모양 막대기
    SDL_Rect t7 = { 10989, 0, 74, 725 }; //t모양 받침대
    SDL_Rect t8 = { 10989, -120, 71, 890 }; //t모양 막대기

    SDL_Rect c2 = { 2723, 320, 71, 286 }; //기둥
    SDL_Rect c3 = { 7003, 190, 71, 286 }; //기둥
    SDL_Rect c4 = { 9710, 390, 71, 286 }; //기둥
    SDL_Rect rotate2 = { 4298, 354, 75,76 }; //회전 중심
    SDL_Rect rotate3 = { 3943, 15, 792,770 }; //회전
    SDL_Rect rotate4 = { 7801, 339, 75,76 }; //회전 중심
    SDL_Rect rotate5 = { 7445, 8, 792,770 }; //회전
    SDL_Rect rotate6 = { 10563, 353, 75,76 }; //회전 중심
    SDL_Rect rotate7 = { 10200, 8, 792,770 }; //회전
    SDL_Rect next = { 1280, 0, 1280, 330 }; //next
    SDL_Rect light = { -1280, 375, 1280,345 }; //light
    

    SDL_Event e;
    int quit = 0;
    int color = 0;
    int time = 0;
    float angle = 0;
    float angle2 = 0;
    float angle3 = 0;

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
                    color = 1;
            }
            else if (e.type == SDL_KEYUP)
            {
                if (e.key.keysym.sym == SDLK_SPACE)
                    color = 0;
            }
        }

        SDL_RenderClear(renderer);

        //그리기
        SDL_RenderCopy(renderer, texture[3], NULL, &bg);//맵
        SDL_RenderCopy(renderer, texture[5], NULL, NULL);//배경빛
        SDL_RenderCopyEx(renderer, texture[0], &font, &font2, angle3, &center, SDL_FLIP_NONE);
        SDL_RenderCopy(renderer, texture[0], &t3, &t4); //t모양 막대기
        SDL_RenderCopy(renderer, texture[0], &t1, &t2); //t모양 받침대
        SDL_RenderCopy(renderer, texture[0], &t3, &t6); 
        SDL_RenderCopy(renderer, texture[0], &t1, &t5); 
        SDL_RenderCopy(renderer, texture[0], &t3, &t8);
        SDL_RenderCopy(renderer, texture[0], &t1, &t7);
        SDL_RenderCopy(renderer, texture[1], NULL, NULL);//폰트박스
        
        if (color)
        {
            SDL_RenderCopy(renderer, texture[2], NULL, NULL);//노란글씨
            player2.y--;
        }
        else
            player2.y++;

        SDL_RenderCopyEx(renderer, texture[0], &player, &player2, angle, NULL, SDL_FLIP_NONE);//player
        SDL_RenderCopy(renderer, texture[0], &r1, &r2);//장애물1
        SDL_RenderCopy(renderer, texture[0], &r1, &r3);//장애물1
        SDL_RenderCopy(renderer, texture[0], &r1, &r4);//장애물1
        SDL_RenderCopy(renderer, texture[0], &c1, &c2);//기둥
        SDL_RenderCopy(renderer, texture[0], &c1, &c3);//기둥
        SDL_RenderCopy(renderer, texture[0], &c1, &c4);//기둥
        SDL_RenderCopyEx(renderer, texture[4], NULL, &rotate3, angle2, NULL, SDL_FLIP_NONE);//회전
        SDL_RenderCopy(renderer, texture[0], &rotate1, &rotate2);//회전 중심
        SDL_RenderCopyEx(renderer, texture[4], NULL, &rotate5, angle2, NULL, SDL_FLIP_NONE);//회전
        SDL_RenderCopy(renderer, texture[0], &rotate1, &rotate4);//회전 중심
        SDL_RenderCopyEx(renderer, texture[4], NULL, &rotate7, angle2, NULL, SDL_FLIP_NONE);//회전
        SDL_RenderCopy(renderer, texture[0], &rotate1, &rotate6);//회전 중심
        SDL_RenderCopy(renderer, texture[6], NULL, NULL);
        SDL_RenderCopy(renderer, texture[7], NULL, &next);
        SDL_RenderCopy(renderer, texture[8], NULL, &light);

        //계속 실행 
        time++;
        angle++;
        angle2 += 0.3;
        font2.x--;
        r2.x--;
        r3.x--;
        r4.x--;
        c2.x--;
        c3.x--;
        c4.x--;
        t2.x--;
        t4.x--;
        t5.x--;
        t6.x--;
        t7.x--;
        t8.x--;
        rotate2.x--;
        rotate3.x--;
        rotate4.x--;
        rotate5.x--;
        rotate6.x--;
        rotate7.x--;

        if (bg.x >= -11220)
        {
            bg.x--;

            if (bg.x > -200)
            {
                angle3 -= 0.7;
                font2.x -= 4;
            }
            else if (bg.x <= -200 && bg.x >= -350)
                angle3 -= 0.4;
            else if (bg.x < -350 && bg.x > -550)
            {
                angle3 -= 0.7;
                font2.x -= 4;
            }

            if (bg.x <-1470 && bg.x > -2200)
            {
                if (!(bg.x % 5))
                    c2.y--;
            }
            else if (bg.x <-4500 && bg.x > -5070)
            {
                if (!(bg.x % 5))
                    t4.y++;
                    
            }
            else if (bg.x <-6100 && bg.x > -6900)
            {
                if (!(bg.x % 5))
                    c3.y++;
            }
            else if (bg.x <-7500 && bg.x > -8300)
            {
                if (!(bg.x % 5))
                    t6.y--;
            }
            else if (bg.x <-8310 && bg.x > -9300)
            {
                if (!(bg.x % 5))
                    c4.y--;
            }
            else if (bg.x <-10185 && bg.x > -10950)
            {
                if (!(bg.x % 5))
                    t8.y++;
            }
        }

        if (bg.x< 0 && bg.x > -10400)
            SDL_SetTextureAlphaMod(texture[6], 0);

        else if(bg.x<= -10400 && bg.x > -10430)
            SDL_SetTextureAlphaMod(texture[6], 255);

        else if (bg.x<= -10430 && bg.x > -10470)
            SDL_SetTextureAlphaMod(texture[6], 0);

        else if (bg.x <= -10470 && bg.x > -10490)
            SDL_SetTextureAlphaMod(texture[6], 255);

        else if (bg.x <= -10490 && bg.x > -10530)
            SDL_SetTextureAlphaMod(texture[6], 0);

        else if (bg.x <= -10530 && bg.x > -10550)
            SDL_SetTextureAlphaMod(texture[6], 255);

        if (bg.x >= -10430)
        {
            if (player2.y <= 105 || player2.y >= 605)
                quit = 1;
        }
        if (time > 10716 && time < 10900)
            next.x -= 7;
        if (time >= 11100 && time < 11283)
            light.x += 7;


        SDL_RenderPresent(renderer);
        SDL_Delay(2);
    }

    // 리소스 해제
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);

    IMG_Quit();
    SDL_Quit();
}
*/
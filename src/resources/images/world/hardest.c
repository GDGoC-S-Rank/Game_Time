/*
#include "SDL.h"
#include "SDL_timer.h"
#include "SDL_image.h"
#include <stdio.h>

#pragma comment(lib, "SDL2_image.lib")

#define num 23
#define num2 7

//바닥 위치 이동 함수
int checkfloor(int*n, SDL_Rect*floor, SDL_Rect* floor2, int n2)
{
    if (n2 == 1)
    {
        switch (*n)
        {
        case 1:
            floor->x = 480;
            floor->y = 630;
            return 2;
            break;
        case 2:
            floor->x = 790;
            floor->y = 630;
            return 3;
            break;
        case 3:
            floor->x = 937;
            floor->y = 496;
            return 4;
            break;
        case 4:
            floor->x = 1690;
            floor->y = 496;
            return 5;
            break;
        case 5:
            floor2->x = 500;
            floor2->y = 628;
            return 6;
            break;
        }
    }
    if (n2 == 2)
    {
        switch (*n)
        {
        case 1:
            floor->x = 2075;
            floor->y = 294;
            return 2;
            break;  
        case 2:
            floor->x = 2860;
            floor->y = 147;
            return 3;
            break;
        }
    }

    if (n2 == 3)
    {
        switch (*n)
        {
        case 1:
            floor->x = 1250;
            floor->y = 567;
            return 2;
            break;
        case 2:
            floor->x = 840;
            return 3;
            break;
        case 3:
            floor->x = 1100;
            floor->y = 497;
            return 4;
            break;
        case 4:
            floor->x = 1377;
            floor->y = 428;
            return 5;
            break;   
        case 5:
            floor->x = 1723;
            floor->y = 377;
            return 6;
            break;
            
        }
    }
        
}


//충돌 검사 함수
int checkCollision(SDL_Rect* rect1, SDL_Rect* rect2)
{
    return !(rect1->x + rect1->w < rect2->x || rect2->x + rect2->w < rect1->x ||
                rect1->y + rect1->h < rect2->y || rect2->y + rect2->h < rect1->y);
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
        char filename[70];
        sprintf(filename, "h%d.png", i + 1);
        image[i] = IMG_Load(filename);
    }
    //바닥, 천장 이미지
    SDL_Surface* image2[num2];
    for (int i = 0; i < num2; i++)
    {
        char filename2[30];
        sprintf(filename2, "floor%d.png", i + 1);
        image2[i] = IMG_Load(filename2);
    }

    //텍스처로 만들기
    SDL_Texture* texture[num];
    for (int i = 0; i < num; i++)
        texture[i] = SDL_CreateTextureFromSurface(renderer, image[i]);
    SDL_Texture* floor_texture[num2];
    for (int i = 0; i < num2; i++)
        floor_texture[i] = SDL_CreateTextureFromSurface(renderer, image2[i]);

    //이미지 해제
    for (int i = 0; i < num; i++)
        SDL_FreeSurface(image[i]);
    for (int i = 0; i < num2; i++)
        SDL_FreeSurface(image2[i]);

    SDL_Rect bg = { 0, 0, 8700, 720 };
    SDL_Rect t1 = { -1280, 0, 1280, 720 };
    SDL_Rect t2 = { 1280, 0, 1280, 720 };
    SDL_Rect player = { 370, 310, 33, 33 };
    SDL_Rect floor = { -370, 429, 1079, 20 }; //연두색
    SDL_Rect floor2 = { 702, 494, 74, 22 }; //1칸
    SDL_Rect floor3 = { 634, 566, 207, 20 }; //3칸
    SDL_Rect floor4 = { 4760, 361, 680, 20 }; //중간 길이
    SDL_Rect floor5 = { 1995, 364, 302, 20 }; //4칸
    SDL_Rect up = {845, 339, 1005, 20 };
    SDL_Rect up2 = { 4460, 207, 302, 20 }; //4칸 천장
    SDL_Rect up3 = { 4760, 142, 600, 20 }; //노란색 천장
    SDL_Rect up4 = { 5300, 210, 2037, 20 }; //가장 긴

    SDL_Rect rect = { 927, 595, 304,34 };
    SDL_Rect rect2 = { 1063, 373, 34,34 };
    SDL_Rect rect3 = { 1340, 373, 37,241 };
    SDL_Rect rect4 = { 1340, 445, 38,109 };

    SDL_Rect rect5 = { 1800,275,196,196 }; 
    SDL_Rect rect6 = { 2435,343, 196,196 }; 
    SDL_Rect rect7 = { 2168,160,85, 220 };
    SDL_Rect rect8 = { 2168,400,85, 220 };
    SDL_Rect coin = { 1885, 354, 32,32 };
    SDL_Rect coin2 = { 2525, 424, 32,32 };
    SDL_Rect coin3 = { 6643, 260, 32,32 };
    SDL_Rect coin4 = { 7114, 457, 32,32 };

    SDL_Rect move1 = { 3810, 385, 149,34 };
    SDL_Rect move2 = { 3520, 385, 149,34 };
    SDL_Rect move3 = { 3520, 385, 149,34 };
    SDL_Rect move4 = { 3810, 385, 149, 34 };

    SDL_Rect m1 = { 4520, 455, 34,34 };
    SDL_Rect m2 = { 4573, 238, 34,34 };
    SDL_Rect m3 = { 4930, 320, 34,34 };
    SDL_Rect m4 = { 5285, 380, 784, 110 }; //좌우로 움직이는
    SDL_Rect hide = { 5050, 0, 1433, 720 };
    SDL_Rect hide2 = { 6323, 0, 1007, 720 };
    SDL_Rect m5 = { 6404, -177, 521, 529 };
    SDL_Rect m6 = { 6876, 394, 521, 529 };

    SDL_Rect r1 = { 7696, 197, 35, 108 }; //
    SDL_Rect r2 = { 7693, 395, 35, 108 }; //

    SDL_Rect r3 = { 7500, 390, 108, 35 };
    SDL_Rect r4 = { 7695, 390, 108, 35 };

    SDL_Rect r5 = { 7696, 514, 35, 108 };//아래쪽
    SDL_Rect r6 = { 7695, 320, 35, 108 };//아래쪽 

    SDL_Rect r7 = { 7623, 390, 108, 35 };//오른쪽
    SDL_Rect r8 = { 7815, 390, 108, 35 };// 다시 조정

    SDL_Point center = { 12, 108 };
    SDL_Point center2 = { 108, 12 };
    SDL_Point center3 = { 12,0 };
    SDL_Point center4 = { 0,12 };

    SDL_Event e;
    int quit = 0;
    int color = 0;
    int time = 0;
    int floor_dest = 1;
    int floor_dest2 = 1;
    int floor_dest3 = 1;
    int v = 1; //1이면 아래 방향, -1이면 위쪽 방향
    int v2 = 1; //1이면 오른쪽, -1이면 왼쪽
    float angle = 0;
    float angle2 = 0; //오른쪽 방향
    float angle3 = 0; //왼쪽 방향
    float angle4 = -60;
    float angle5 = -60;

    float a1 = 0;
    float a2 = 0;

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
        SDL_RenderCopy(renderer, texture[5], NULL, &bg); //bg
        SDL_RenderCopy(renderer, texture[3], NULL, &t1);
        SDL_RenderCopy(renderer, texture[4], NULL, &t2);

        SDL_RenderCopy(renderer, texture[10], NULL, &m4); //좌우 움직이는
        SDL_RenderCopy(renderer, texture[9], NULL, &hide);
        SDL_RenderCopyEx(renderer, texture[16], NULL, &m5, angle4, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[16], NULL, &m6, angle5, NULL, SDL_FLIP_NONE);
        SDL_RenderCopy(renderer, texture[20], NULL, &hide2);
        SDL_RenderCopy(renderer, texture[7], NULL, &coin3);
        SDL_RenderCopy(renderer, texture[7], NULL, &coin4);

        
        SDL_RenderCopy(renderer, floor_texture[0], NULL, &floor);
        SDL_RenderCopy(renderer, floor_texture[2], NULL, &floor2);
        SDL_RenderCopy(renderer, floor_texture[1], NULL, &floor3);
        SDL_RenderCopy(renderer, floor_texture[3], NULL, &floor4);
        SDL_RenderCopy(renderer, floor_texture[4], NULL, &floor5);
        SDL_RenderCopy(renderer, floor_texture[0], NULL, &up);
        SDL_RenderCopy(renderer, floor_texture[5], NULL, &up4);
        SDL_RenderCopy(renderer, floor_texture[6], NULL, &up3);  
        SDL_RenderCopy(renderer, texture[6], NULL, &player); //player
        SDL_RenderCopy(renderer, texture[2], NULL, NULL); //fontbox

        SDL_RenderCopy(renderer, texture[13], NULL, &rect);
        SDL_RenderCopy(renderer, texture[19], NULL, &rect2);
        SDL_RenderCopy(renderer, texture[14], NULL, &rect3);
        SDL_RenderCopy(renderer, texture[15], NULL, &rect4);

        SDL_RenderCopyEx(renderer, texture[12], NULL, &rect5, angle, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[12], NULL, &rect6, angle, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[8], NULL, &rect7, angle, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[8], NULL, &rect8, angle, NULL, SDL_FLIP_NONE);
        SDL_RenderCopy(renderer, texture[7], NULL, &coin);
        SDL_RenderCopy(renderer, texture[7], NULL, &coin2);

        SDL_RenderCopyEx(renderer, texture[11], NULL, &move1, angle2, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[11], NULL, &move2, angle2, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[11], NULL, &move3, angle3, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[11], NULL, &move4, angle3, NULL, SDL_FLIP_NONE);

        SDL_RenderCopy(renderer, texture[19], NULL, &m1);
        SDL_RenderCopy(renderer, texture[19], NULL, &m2);
        SDL_RenderCopy(renderer, texture[19], NULL, &m3);

        SDL_RenderCopyEx(renderer, texture[21], NULL, &r1, a1, &center, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[21], NULL, &r2, a1, &center, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[22], NULL, &r3, a1, &center2, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[22], NULL, &r4, a1, &center2, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, texture[21], NULL, &r5, a1, &center3, SDL_FLIP_VERTICAL);
        SDL_RenderCopyEx(renderer, texture[21], NULL, &r6, a1, &center3, SDL_FLIP_VERTICAL);
        SDL_RenderCopyEx(renderer, texture[22], NULL, &r7, a1, &center4, SDL_FLIP_HORIZONTAL);
        SDL_RenderCopyEx(renderer, texture[22], NULL, &r8, a1, &center4, SDL_FLIP_HORIZONTAL);


        if (checkCollision(&player,&floor))
            player.y = floor.y - 33;
        if (checkCollision(&player, &floor2))
            player.y = floor2.y - 33;
        if (checkCollision(&player, &floor3))
            player.y = floor3.y - 33;
        if (checkCollision(&player, &floor4))
            player.y = floor4.y - 33;
        if (checkCollision(&player, &floor5))
            player.y = floor5.y - 33;
        if (checkCollision(&player, &up))
            player.y = up.y + 21;
        if (checkCollision(&player, &up2))
            player.y = up2.y + 21;
        if (checkCollision(&player, &up3))
            player.y = up3.y + 21;
        if (checkCollision(&player, &up4))
            player.y = up4.y + 21;

        if (color)
        {
            SDL_RenderCopy(renderer, texture[0], NULL, NULL);
            player.y--;
        }
        else
            player.y++;

        if (floor.x + 1050 < player.x)
            floor_dest = checkfloor(&floor_dest, &floor, &floor4, 1);
        if (up.x + 1005 < player.x)
            floor_dest2 = checkfloor(&floor_dest2, &up, &floor5, 2);
        if (floor3.x + 207 < player.x)
            floor_dest3 = checkfloor(&floor_dest3, &floor3, &floor4, 3);
        
        //가로로 움직이는 장애물?
        if (time > 0 && time <= 323)
        {
            t1.x+=5;
            t2.x-=3;
        }
        else if (time > 500 && time <= 750)
        {
            t1.x -= 5;
            t2.x += 5;
        }
        else if (time > 780)
        {
            SDL_DestroyTexture(texture[3]);
            SDL_DestroyTexture(texture[4]);
        }
            

        if (time < 1430)
        {
            rect.x--;
            rect2.x--;
            rect3.x--;
            rect4.x--;

            if (bg.x > -170)
                rect3.x += 2;
            else if (bg.x <= -170 && bg.x > -515)
                rect3.x--;
            else if (bg.x <= -515 && bg.x > -855)
                rect3.x++;
            else if (bg.x <= -855 && bg.x > -1195)
                rect3.x--;

            if(bg.x < -145 && bg.x > -480)
                rect4.x++;
            else if (bg.x <= -480 && bg.x > -813)
                rect4.x--;
            else if (bg.x <= -813 && bg.x > -1140)
                rect4.x++;
            else if (bg.x <= -1140 && bg.x > -1583)
                rect4.x--;
        }
        else
        {
            SDL_DestroyTexture(texture[13]);
            SDL_DestroyTexture(texture[14]);
            SDL_DestroyTexture(texture[15]);
        }

        if (bg.x >= -7400)
        {
            bg.x--;
            t1.x--;
            t2.x--;
            floor.x--;
            floor2.x--;
            floor3.x--;
            floor4.x--;
            floor5.x--;
            up.x--;
            up2.x--;
            up3.x--;
            up4.x--;

            move1.x--;
            move2.x--;
            move3.x--;
            move4.x--;

            m1.x--;
            m2.x--;
            m3.x--;
            m4.x--;
            m5.x--;
            m6.x--;
            hide.x--;
            hide2.x--;
            coin3.x--;
            coin4.x--;

            r1.x--;
            r2.x--;
            r3.x--;
            r4.x--;
            r5.x--;
            r6.x--;
            r7.x--;
            r8.x--;

            if (bg.x<-3900 && bg.x > -4160)
            {
                floor5.x = 300;
                floor5.y = 207;
            }

            //위로 움직이는 장애물
            if (bg.x >= -1000)
            {
                if (v == 1)
                {
                    rect.y++;
                    rect2.y--;
                    if (rect.y >= 595)
                        v *= -1;
                }
                else
                {
                    rect.y--;
                    rect2.y++;
                    if (rect.y <= 375)
                        v *= -1;
                }
            }
            //넓은 공간 장면
            if (bg.x <= -600 && bg.x >= -3600)
            {
                angle += 0.25;
                coin.x--;
                coin2.x--;
                rect5.x--;
                rect6.x--;
                rect7.x--;
                rect8.x--;

                if (checkCollision(&player, &coin))
                    coin.y += 600;
                if (checkCollision(&player, &coin2))
                    coin2.y += 600;

                if (bg.x <= -3100)
                {
                    SDL_DestroyTexture(texture[12]);
                    SDL_DestroyTexture(texture[8]);
                }
            }

            if (bg.x <= -2700 && bg.x >= -4110) 
            {
                if (!(time % 3)) 
                {
                    if (angle2 < 90) 
                    {
                        move1.x--;
                        move1.y--;
                        move2.x++;
                        move2.y++;

                        angle2 += 0.63;
                    }
                    else if (angle2 >= 90 && angle2 < 180) 
                    {
                        move1.x--;
                        move1.y++;
                        move2.x++;
                        move2.y--;

                        angle2 += 0.63;
                    }

                    if (angle3 > -90) 
                    {
                        move3.x++;
                        move3.y--;
                        move4.x--;
                        move4.y++;

                        angle3 -= 0.63;
                    }
                    else if (angle3 <= -90 && angle3 > -180) 
                    {
                        move3.x++;
                        move3.y++;
                        move4.x--;
                        move4.y--;

                        angle3 -= 0.63;
                    }
                }
            }
            //대각선으로 이동하는
            if (bg.x <= -3600 && bg.x >= -4700) 
            {
                if (!(time % 2)) 
                {
                    if (v == -1) 
                    {
                        if (m1.y >= 305) 
                        {
                            m1.x--;
                            m1.y--;
                            m2.x++;
                            m2.y++;
                            m3.x--;
                            m3.y--;
                        }
                        else
                            v *= -1;
                    }
                    else 
                    {
                        if (m1.y <= 455) 
                        {
                            m1.x++;
                            m1.y++;
                            m2.x--;
                            m2.y--;
                            m3.x++;
                            m3.y++;
                        }
                        else
                            v *= -1;
                    }
                }
            }

            if (time > 4500 && time < 6000)
            {
                
              if (time > 4800 && time < 5000)
                  m4.x++;
              else if (time >= 5000 && time < 5250)
                  m4.x--;
              else if (time >= 5250 && time < 5700)
                  m4.x++;
            }
            
            if (bg.x <= -5500 && bg.x >= -7000)
            {
                angle4 += 0.1; //왼쪽
                angle5 -= 0.1; //오른쪽

                if (checkCollision(&player, &coin3))
                    coin3.y += 600;
                if (checkCollision(&player, &coin4))
                    coin4.y += 600;
            }

        }
        else
        {
            if(player.x < 700)
                player.x++;
            if (player.x >= 700)
                SDL_DestroyTexture(texture[6]);
        }

        if (time >= 6500 && time < 40000)
            a1 -= 0.3;

        SDL_Delay(2);
      //  printf("%d\n", bg.x);
     //   printf("%d\n", time);
        time++;
        SDL_RenderPresent(renderer);
        
    }

    // 리소스 해제
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);

    IMG_Quit();
    SDL_Quit();
}
*/
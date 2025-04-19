
#include "SDL.h"
#include "SDL_timer.h"
#include "SDL_image.h"
#include <stdio.h>

#pragma comment(lib, "SDL2_image.lib")

#define framespeed 100

typedef struct
{
    SDL_Texture* texture;
    SDL_Rect rect;
}Image;

int checkCollision(SDL_Rect* rect1, SDL_Rect* rect2)
{
    return !(rect1->x + rect1->w < rect2->x || rect2->x + rect2->w < rect1->x ||
        rect1->y + rect1->h < rect2->y || rect2->y + rect2->h < rect1->y);
}

void check_jump(SDL_Rect* player_rect, SDL_Rect* hit_rect, int*jump, int* height)
{
    if (*jump==1 && player_rect->y > *height-1)
    {
        player_rect->y--;
        if (player_rect->y == *height)
            *jump = 0;
    }
    else if (*jump == 0)
    {
        if (checkCollision(player_rect, hit_rect))
        {
            player_rect->y = hit_rect->y - 95;
        }
        else
        {
            player_rect->y++;
        }
    }
}


int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* win = SDL_CreateWindow("sdl", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 800, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* image1 = IMG_Load("fontbox.png");
    SDL_Surface* image2 = IMG_Load("hs_text.png");
    SDL_Surface* image3 = IMG_Load("hs_textL.png");
    SDL_Surface* image4 = IMG_Load("hs_textR.png");
    SDL_Surface* image5 = IMG_Load("bg_heart.png");
    SDL_Surface* image6 = IMG_Load("heart_bg.png");
    SDL_Surface* image7 = IMG_Load("star_bg.png");
    SDL_Surface* image8 = IMG_Load("bg_star.png");
    SDL_Surface* image9= IMG_Load("heartstar_title.png");
    SDL_Surface* image10 = IMG_Load("end.png");
    SDL_Surface* hit_image[6];
    SDL_Surface* frame[4];
    SDL_Surface* frame2[4];
    for (int i = 0; i < 4; i++)
    {
        char filename[20];
        sprintf(filename, "heart%d.png", i + 1);
        frame[i] = IMG_Load(filename);
        char filename2[20];
        sprintf(filename2, "S%d.png", i + 1);
        frame2[i] = IMG_Load(filename2);
    }
    for (int i = 0; i < 6; i++)
    {
        char name[20];
        sprintf(name, "hit%d.png", i + 1);
        hit_image[i] = IMG_Load(name);
    }

    Image fontbox, hs_text, hs_textL, hs_textR, bg_heart, hwall, swall, bg_star, texture_frame[4], texture_frame2[4], 
        texture_hit[6], dest, dest2, dest3, dest4, title, end, hit10, hit_h, hit_s, hit_h2, hit_s2;
    for (int i = 0; i < 4; i++)
    {
        texture_frame[i].texture = SDL_CreateTextureFromSurface(renderer, frame[i]);
        texture_frame2[i].texture = SDL_CreateTextureFromSurface(renderer, frame2[i]);
    }
    for (int i = 0; i < 6; i++)
    {
        texture_hit[i].texture = SDL_CreateTextureFromSurface(renderer, hit_image[i]);
    }
  
    fontbox.texture = SDL_CreateTextureFromSurface(renderer, image1);
    hs_text.texture = SDL_CreateTextureFromSurface(renderer, image2);
    hs_textL.texture = SDL_CreateTextureFromSurface(renderer, image3);
    hs_textR.texture = SDL_CreateTextureFromSurface(renderer, image4);
    bg_heart.texture = SDL_CreateTextureFromSurface(renderer, image5);
    bg_star.texture = SDL_CreateTextureFromSurface(renderer, image8);
    hwall.texture = SDL_CreateTextureFromSurface(renderer, image6);
    swall.texture = SDL_CreateTextureFromSurface(renderer, image7);
    title.texture = SDL_CreateTextureFromSurface(renderer, image9);
    end.texture = SDL_CreateTextureFromSurface(renderer, image10);

    SDL_FreeSurface(image1, image2, image3, image4, image5, image6, image7, image8, image9, image10);
    for (int i = 0; i < 4; i++)
    {
        SDL_FreeSurface(frame[i]);
        SDL_FreeSurface(frame2[i]);
    }
    for (int i = 0; i < 6; i++)
    {
        SDL_FreeSurface(hit_image[i]);
    }

    bg_heart.rect = (SDL_Rect){ 0,0,10500,720 };
    bg_star.rect = (SDL_Rect){ 0,0,10500,720 };
    hwall.rect = (SDL_Rect){ 0,-1350,2560,2160 };
    swall.rect = (SDL_Rect){ -1280,0,2560,2160 };
    dest.rect = (SDL_Rect){ 430,410,69,95 }; //캐릭터
    dest2.rect = (SDL_Rect){ 430,505,70,23 }; //하트 바닥
    dest3.rect = (SDL_Rect){ 430,900,70,23 }; //스타 바닥
    dest4.rect = (SDL_Rect){ 430,338,70,23 }; //머리부딪히는 달블럭
    title.rect = (SDL_Rect){ 0, 720,1280,720 };
    end.rect = (SDL_Rect){ 1280, 10,1600,800 };
    hit10.rect = (SDL_Rect){ 1180, 444,61,63 };//달
    hit_h.rect = (SDL_Rect){ 3280, 440,403,62 };//하트
    hit_s.rect = (SDL_Rect){ 2860, 440,403,62 };//스타
    hit_h2.rect = (SDL_Rect){ 4890, 240,63,258 };//하트
    hit_s2.rect = (SDL_Rect){ 5153, 240,63,258 };//스타

    SDL_Event e;
    int quit = 0;
    int color = 0;
    int color2 = 0;
    int time = 0;
    int change = 2; 
    int jump = 2;
    int lasttime = 0;
    int current_frame = 0;
    int height = 250;

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
                    jump = 1;
                }
                if (e.key.keysym.sym == SDLK_UP)
                {
                    color2 = 1;
                    change++;
                }
            }
            else if (e.type == SDL_KEYUP)
            {
                if (e.key.keysym.sym == SDLK_SPACE)
                {
                    color = 0;
                }
                if (e.key.keysym.sym == SDLK_UP)
                    color2 = 0;
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lasttime > framespeed)
        {
            current_frame = (current_frame + 1) % 4;
            lasttime = currentTime;
        }

        if (!(change % 2))
        {
            SDL_RenderCopy(renderer, hwall.texture, NULL, &hwall.rect);
            SDL_RenderCopy(renderer, bg_heart.texture, NULL, &bg_heart.rect);
            SDL_RenderCopy(renderer, texture_frame[current_frame].texture, NULL, &dest.rect);
            swall.rect.x = -1280;
            swall.rect.y = 0;
            check_jump(&dest.rect, &dest2.rect, &jump, &height); 
         // SDL_RenderCopy(renderer, texture_hit[0].texture, NULL, &dest2.rect);
        }
        else
        {
            SDL_RenderCopy(renderer, swall.texture, NULL, &swall.rect);
            SDL_RenderCopy(renderer, bg_star.texture, NULL, &bg_star.rect);
            SDL_RenderCopy(renderer, texture_frame2[current_frame].texture, NULL, &dest.rect);
            hwall.rect.x = 0;
            hwall.rect.y = -1350;
            check_jump(&dest.rect, &dest3.rect, &jump, &height);
           // SDL_RenderCopy(renderer, texture_hit[1].texture, NULL, &dest3.rect);
        }

        SDL_RenderCopy(renderer, fontbox.texture, NULL, NULL);
        SDL_RenderCopy(renderer, hs_text.texture, NULL, NULL);
        SDL_RenderCopy(renderer, title.texture, NULL, &title.rect);
      // SDL_RenderCopy(renderer, texture_hit[5].texture, NULL, &hit10.rect);
      // SDL_RenderCopy(renderer, texture_hit[4].texture, NULL, &hit_s.rect);
      // SDL_RenderCopy(renderer, texture_hit[3].texture, NULL, &hit_h.rect);
      // SDL_RenderCopy(renderer, texture_hit[4].texture, NULL, &hit_s2.rect);
      // SDL_RenderCopy(renderer, texture_hit[3].texture, NULL, &hit_h2.rect);

        if (color)
            SDL_RenderCopy(renderer, hs_textL.texture, NULL, NULL);
        if (color2)
            SDL_RenderCopy(renderer, hs_textR.texture, NULL, NULL);

        if (time < 9670)
        {
            bg_heart.rect.x--;
            bg_star.rect.x--;
            hit_h.rect.x--;
            hit_s.rect.x--;
            hit_h2.rect.x--;
            hit_s2.rect.x--;
            hit10.rect.x--;

            if (!(time % 2))
            {
                hwall.rect.x--;
                hwall.rect.y++;
                swall.rect.x++;
                swall.rect.y--;
            }
        }
        
        switch (change)
        {
        case 5:
        case 7:
        case 9:
        case 11:
            if (checkCollision(&dest.rect, &hit_s.rect) || checkCollision(&dest.rect, &hit_s2.rect))
                quit = 1;
            break;
       case 4:
       case 6:
       case 8:
       case 10:
           if (checkCollision(&dest.rect, &hit_h.rect) || checkCollision(&dest.rect, &hit_h2.rect))
               quit = 1;
           break;
        }
        if (checkCollision(&dest.rect, &hit10.rect))
            quit = 1;
            
        if (time >= 3200 && time < 3300)
            hit_s.rect = (SDL_Rect){ 430, 440,403, 62 };
        if (time >= 3300 && time < 3700)
            hit_h.rect = (SDL_Rect){ 623, 240,63,258 };

        if (time >= 3600 && time < 3900)
            hit_s.rect = (SDL_Rect){ 715, 240,63,258 };

        if (time >= 4800 && time < 4900)
            hit_h.rect = (SDL_Rect){ 550, 240,63,258 };

        if (time >= 4000 && time < 4100)
            hit10.rect = (SDL_Rect){ 1205, 444,61,63 };//달    

        if (time >= 5300 && time < 5600)
            hit_s.rect = (SDL_Rect){ 743, 523,63,60 };

        if (time >= 5100 && time < 5300)
            hit_h2.rect = (SDL_Rect){ 760, 372,63,60 };

        if (time >= 6200 && time < 6400)
            hit_s2.rect = (SDL_Rect){ 807, 236,63,258 };

        if (time >= 7400 && time < 7600)
            hit_h.rect = (SDL_Rect){ 860,423,63,142 };
        if (time >= 7800 && time < 8000)
            hit_h2.rect = (SDL_Rect){ 995,423,63,142 };

       // if (time > 5500)
       //     SDL_Delay(20);

        if (time >= 0 && time < 250)
            title.rect.y -= 3;
        if (time >= 600 && time < 800)
            title.rect.y -= 3;
        if (bg_star.rect.x == -1250)
            dest2.rect.y = 900;
        if (bg_star.rect.x == -1430)
            dest3.rect.y = 435;
        if (bg_star.rect.x == -1630)
            dest3.rect.y = 503;
        if (bg_star.rect.x == -1900)
            dest3.rect.y = 900;
        if (time >=1980 && time < 2200)
            dest2.rect.y = 572;
        if (time >= 2200 && time < 2230)
            dest2.rect.y = 900;

        if (time >= 2500 && time < 5400)
        {
            dest2.rect.y = 501;
            dest3.rect.y = 501;
        }
        if (time >= 5400 && time < 5900)
        {
            dest3.rect.y = 576;
            dest2.rect.y = 428;
        }

        if (time >= 5400 && time < 5830)
            height = 315;
        if (time >= 5830 && time < 5950)
            height = 170;

        if (time >= 6000 && time < 6200)
            dest2.rect.y = 900; 
        if (time >= 6200 && time < 6500)
            dest3.rect.y = 507;
        if (time >= 6500 && time < 6900)
            dest3.rect.y = 900;
        if (time >= 6900 && time < 7100)
        {
            dest3.rect.y = 497;
            height = 255;
        }

        if (time >= 7100 && time < 8800)
            dest3.rect.y = 900;

        if (time >= 7300 && time < 7420)
            dest2.rect.y = 424; 
        if (time >= 7420 && time < 9060)
            dest2.rect.y = 563;

        if(time >= 8800 && time < 9060)
            dest3.rect.y = 563;

        if (time >= 9060 && time < 9200)
            dest2.rect.y = 900;
        if (time >= 9270 && time < 9400)
        {
            dest2.rect.y = 490;
            dest3.rect.y = 490;
        }
        if (time >= 9600)
        {
            dest2.rect.y = 420;
            dest3.rect.y = 420;
        }

        if (time > 1800 && time < 2100)
        {
            //SDL_RenderCopy(renderer, texture_hit[2].texture, NULL, &dest4.rect);
            if (checkCollision(&dest.rect, &dest4.rect))
            {
                dest.rect.y += 3;
                jump = 0;
            }
        }
        if (time > 9800)
        {
            SDL_RenderCopy(renderer, end.texture, NULL, &end.rect);
            end.rect.x -= 5;
        }
        if (time > 10100)
        {
            SDL_DestroyTexture(fontbox.texture);
            SDL_DestroyTexture(hs_text.texture);
            SDL_DestroyTexture(hs_textL.texture);
            SDL_DestroyTexture(hs_textR.texture);
            SDL_DestroyTexture(bg_heart.texture);
            SDL_DestroyTexture(bg_star.texture);
            SDL_DestroyTexture(hwall.texture);
            SDL_DestroyTexture(swall.texture);
            SDL_DestroyTexture(title.texture);
            SDL_DestroyTexture(end.texture);              
            for (int i = 0; i < 4; i++)
            {
                SDL_DestroyTexture(texture_frame[i].texture);
                SDL_DestroyTexture(texture_frame2[i].texture);
            }
            for (int i = 0; i < 6; i++)
            {
                SDL_DestroyTexture(texture_hit[i].texture);
            }
        }  

        time++;
       // printf("%d\n", time);
       // printf("%d\n", hit_s.rect.x);
       // printf("%d\n", change);

        // 화면 업데이트
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(1);
    }

    // 리소스 해제
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}

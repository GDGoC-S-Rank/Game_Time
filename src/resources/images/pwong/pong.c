/*
#include "SDL.h"
#include "SDL_timer.h"
#include "SDL_image.h"
#include <stdio.h>

#pragma comment(lib, "SDL2_image.lib")

// 이미지 구조체
typedef struct {
    SDL_Texture* texture;
    SDL_Rect rect;
} Image;

//충돌 검사 함수
int checkCollision(SDL_Rect* rect1, SDL_Rect* rect2)
{
    return !(rect1->x + rect1->w < rect2->x || rect2->x + rect2->w < rect1->x ||
        rect1->y + rect1->h < rect2->y || rect2->y + rect2->h < rect1->y);
}

int main(void)
{
    // SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    //창 생성
    SDL_Window* win = SDL_CreateWindow("sdl", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 800, 0);

    // 화면 생성
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    //이미지 로딩
    SDL_Surface* img1 = IMG_Load("w1.png");
    SDL_Surface* img1_2 = IMG_Load("w2.png");
    SDL_Surface* img1_3 = IMG_Load("w3.png");
    SDL_Surface* img1_4 = IMG_Load("w4.png");
    SDL_Surface* img2 = IMG_Load("fontbox.png");
    SDL_Surface* img3 = IMG_Load("f1.png");
    SDL_Surface* img4 = IMG_Load("f3.png");
    SDL_Surface* img5 = IMG_Load("f4.png");
    SDL_Surface* img6 = IMG_Load("player2(1).png"); //파란색
    SDL_Surface* img7 = IMG_Load("ball.png");
    SDL_Surface* img8 = IMG_Load("player3.png");
    SDL_Surface* img9 = IMG_Load("text.png"); // pong 
    SDL_Surface* img10 = IMG_Load("smaller.png"); // smaller paddle
    SDL_Surface* img11 = IMG_Load("faster.png"); // faster ball

    Image stick, stick2, stick3, stick4, fontbox, font, Lfont, Rfont, player1, player2, player3, ball1, ball2, text, text2, text3;

    // 이미지를 텍스처로 변환
    stick.texture = SDL_CreateTextureFromSurface(renderer, img1);
    stick2.texture = SDL_CreateTextureFromSurface(renderer, img1_2);
    stick3.texture = SDL_CreateTextureFromSurface(renderer, img1_3);
    stick4.texture = SDL_CreateTextureFromSurface(renderer, img1_4);
    fontbox.texture = SDL_CreateTextureFromSurface(renderer, img2);
    font.texture = SDL_CreateTextureFromSurface(renderer, img3);
    Lfont.texture = SDL_CreateTextureFromSurface(renderer, img4);
    Rfont.texture = SDL_CreateTextureFromSurface(renderer, img5);
    player1.texture = SDL_CreateTextureFromSurface(renderer, img6);
    player2.texture = SDL_CreateTextureFromSurface(renderer, img6);
    player3.texture = SDL_CreateTextureFromSurface(renderer, img8);
    ball1.texture = SDL_CreateTextureFromSurface(renderer, img7);
    ball2.texture = SDL_CreateTextureFromSurface(renderer, img7);
    text.texture = SDL_CreateTextureFromSurface(renderer, img9);
    text2.texture = SDL_CreateTextureFromSurface(renderer, img10);
    text3.texture = SDL_CreateTextureFromSurface(renderer, img11);

    SDL_FreeSurface(img1, img2, img3, img4, img5, img6, img7, img1_2, img1_3, img1_4, img8, img9, img10, img11);

    // 초기 알파 값 설정
    Uint8 alpha = 255;
    Uint8 alpha2 = 255;
    Uint8 alpha3 = 255;

    // 이미지의 출력 위치 및 크기 정보
    player1.rect = (SDL_Rect){ 470, 730, 343, 28 };
    player2.rect = (SDL_Rect){ 470, 130, 343, 28 };
    player3.rect = (SDL_Rect){ 470, 730, 165, 28 };
    ball1.rect = (SDL_Rect){ 330, 120, 45, 45 };
    ball2.rect = (SDL_Rect){ 1000, 600, 45, 45 };

    SDL_Event e;
    int quit = 0;
    int color = 0; // 1이면 그리기, 0이면 안그림(흰색)
    int color2 = 0;
    int player2_xfac = 0;
    int ball1_xfac = -1;
    int ball1_yfac = 1;
    int ball2_xfac = 1;
    int ball2_yfac = -1;
    int time = 0;

    // 메인 루프
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_e)
                {
                    quit = 1;
                }
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    color = 1;  // 노랑으로 그리기
                }
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    color2 = 1;
                }
                if (e.key.keysym.sym == SDLK_z)
                {
                    player2_xfac = -1; //왼쪽
                }
                if (e.key.keysym.sym == SDLK_x)
                {
                    player2_xfac = 1; //오른쪽
                }
            }
            else if (e.type == SDL_KEYUP)
            {
                if (e.key.keysym.sym == SDLK_LEFT)
                {
                    color = 0;  // 왼쪽 키 뗌
                }
                if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    color2 = 0;
                }
                if (e.key.keysym.sym == SDLK_z)
                {
                    player2_xfac = 0;
                }
                if (e.key.keysym.sym == SDLK_x)
                {
                    player2_xfac = 0;
                }
            }
        }

        // 충돌 검사
        if (checkCollision(&player2.rect, &ball1.rect))
        {
            ball1_yfac *= -1;
        }
        if (checkCollision(&player2.rect, &ball2.rect))
        {
            ball2_yfac *= -1;
        }

        if (time < 2800)
        {
            if (checkCollision(&player1.rect, &ball1.rect))
            {
                ball1_yfac *= -1;
            }
            if (checkCollision(&player1.rect, &ball2.rect))
            {
                ball2_yfac *= -1;
            }
            if (color)
            {
                SDL_RenderCopy(renderer, Lfont.texture, NULL, NULL);
                if (player1.rect.x >= 208)
                {
                    player1.rect.x -= 2;
                }
            }
            if (color2)
            {
                SDL_RenderCopy(renderer, Rfont.texture, NULL, NULL);
                if (player1.rect.x <= 726)
                {
                    player1.rect.x += 2;
                }
            }
        }

        if (time >= 2800)
        {
            if (checkCollision(&player3.rect, &ball1.rect))
            {
                ball1_yfac *= -1;
            }
            if (checkCollision(&player3.rect, &ball2.rect))
            {
                ball2_yfac *= -1;
            }
        }

        // 화면 지우기
        SDL_RenderClear(renderer);

        // 텍스처를 화면에 그리기
        //파란색
        if (time < 1400)
        {
            // 텍스처에 알파 값 설정
            SDL_SetTextureAlphaMod(text.texture, alpha);
            SDL_RenderCopy(renderer, text.texture, NULL, NULL);
            SDL_RenderCopy(renderer, stick.texture, NULL, NULL);
            SDL_SetTextureColorMod(player1.texture, 0, 230, 255);
            SDL_SetTextureColorMod(player2.texture, 0, 230, 255);
            if (alpha > 0)
            {
                alpha -= 1;
            }
        }
        //초록색
        if (time >= 1400 && time <= 2800)
        {
            SDL_RenderCopy(renderer, stick2.texture, NULL, NULL);
            SDL_SetTextureColorMod(player1.texture, 0, 255, 0);
            SDL_SetTextureColorMod(player2.texture, 0, 255, 0);
            SDL_SetTextureColorMod(player3.texture, 255, 255, 0);
        }
        //노란색
        if (time >= 2800 && time <= 4200)
        {
            SDL_SetTextureAlphaMod(text2.texture, alpha2);
            SDL_RenderCopy(renderer, text2.texture, NULL, NULL);
            SDL_RenderCopy(renderer, stick3.texture, NULL, NULL);
            SDL_DestroyTexture(player1.texture);
            SDL_SetTextureColorMod(player2.texture, 255, 255, 0);
            SDL_RenderCopy(renderer, player3.texture, NULL, &player3.rect);
            if (alpha2 > 0)
            {
                alpha2 -= 1;
            }
        }
        //보라색
        if (time >= 4200)
        {
            SDL_SetTextureAlphaMod(text3.texture, alpha3);
            SDL_RenderCopy(renderer, text3.texture, NULL, NULL);
            SDL_RenderCopy(renderer, stick4.texture, NULL, NULL);
            SDL_SetTextureColorMod(player2.texture, 255, 0, 255);
            SDL_SetTextureColorMod(player3.texture, 255, 0, 255);
            SDL_RenderCopy(renderer, player3.texture, NULL, &player3.rect);
            if (alpha3 > 0)
            {
                alpha3 -= 1;
            }
        }
        SDL_RenderCopy(renderer, fontbox.texture, NULL, NULL);
        SDL_RenderCopy(renderer, font.texture, NULL, NULL);
        SDL_RenderCopy(renderer, player1.texture, NULL, &player1.rect);
        SDL_RenderCopy(renderer, player2.texture, NULL, &player2.rect);
        SDL_RenderCopy(renderer, ball1.texture, NULL, &ball1.rect);
        SDL_RenderCopy(renderer, ball1.texture, NULL, &ball2.rect);

        if (color)
        {
            SDL_RenderCopy(renderer, Lfont.texture, NULL, NULL);
            if (player3.rect.x >= 208)
            {
                player3.rect.x -= 2;
            }
        }
        if (color2)
        {
            SDL_RenderCopy(renderer, Rfont.texture, NULL, NULL);
            if (player3.rect.x <= 904)
            {
                player3.rect.x += 2;
            }
        }

        if (player2_xfac == -1)
        {
            if (player2.rect.x >= 208)
            {
                player2.rect.x -= 2;
            }
        }
        if (player2_xfac == 1)
        {
            if (player2.rect.x <= 726)
            {
                player2.rect.x += 2;
            }
        }

        if (time < 4200)
        {
            // 공의 방향
            if (ball1_xfac == -1)
            {
                ball1.rect.x -= 1;
                if (ball1.rect.x <= 200)
                {
                    ball1_xfac = 1;
                }
            }
            else
            {
                ball1.rect.x += 1;
                if (ball1.rect.x >= 1030)
                {
                    ball1_xfac = -1;
                }
            }

            if (ball1_yfac == 1)
            {
                ball1.rect.y += 1;
            }
            else
            {
                ball1.rect.y -= 1;
            }

            // 공2의 방향
            if (ball2_xfac == 1)
            {
                ball2.rect.x += 1;
                if (ball2.rect.x >= 1030)
                {
                    ball2_xfac = -1;
                }
            }
            else
            {
                ball2.rect.x -= 1;
                if (ball2.rect.x <= 200)
                {
                    ball2_xfac = 1;
                }
            }

            if (ball2_yfac == -1)
            {
                ball2.rect.y -= 1;
            }
            else
            {
                ball2.rect.y += 1;
            }
        }
        
        if (time >= 4200)
        {
            // 공의 방향
            if (ball1_xfac == -1)
            {
                ball1.rect.x -= 2;
                if (ball1.rect.x <= 200)
                {
                    ball1_xfac = 1;
                }
            }
            else
            {
                ball1.rect.x += 2;
                if (ball1.rect.x >= 1030)
                {
                    ball1_xfac = -1;
                }
            }

            if (ball1_yfac == 1)
            {
                ball1.rect.y += 2;
            }
            else
            {
                ball1.rect.y -= 2;
            }

            // 공2의 방향
            if (ball2_xfac == 1)
            {
                ball2.rect.x += 2;
                if (ball2.rect.x >= 1030)
                {
                    ball2_xfac = -1;
                }
            }
            else
            {
                ball2.rect.x -= 2;
                if (ball2.rect.x <= 200)
                {
                    ball2_xfac = 1;
                }
            }

            if (ball2_yfac == -1)
            {
                ball2.rect.y -= 2;
            }
            else
            {
                ball2.rect.y += 2;
            }
        }

        // 화면 업데이트
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
        time += 1;
    }

    // 리소스 해제
    SDL_DestroyTexture(stick.texture, stick2.texture, stick3.texture, stick4.texture,
        fontbox.texture, font.texture, Lfont.texture, Rfont.texture,
        player1.texture, player2.texture, player3.texture, ball1.texture, ball2.texture, text.texture, text2.texture, text3.texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);

    // SDL 및 이미지 라이브러리 종료
    IMG_Quit();
    SDL_Quit();

}
*/
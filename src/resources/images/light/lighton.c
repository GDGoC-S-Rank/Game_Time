/*
#include "SDL.h"
#include "SDL_timer.h"
#include "SDL_image.h"
#include <stdio.h>

#pragma comment(lib, "SDL2_image.lib")

#define num 12

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

    //�̹��� �ҷ�����
    SDL_Surface* image[num];
    for (int i = 0; i < num; i++)
    {
        char filename[60];
        sprintf(filename, "light_%d.png", i + 1);
        image[i] = IMG_Load(filename);
    }

    //�ؽ�ó�� �����
    SDL_Texture* texture[num];
    for (int i = 0; i < num; i++)
        texture[i] = SDL_CreateTextureFromSurface(renderer, image[i]);

    //�̹��� ����
    for (int i = 0; i < num; i++)
        SDL_FreeSurface(image[i]);

    //���� ����
    SDL_Rect rect1 = { 0,0,57,58};//������ ����
    SDL_Rect rect2 = { 60,0,57,58 };//������ ����
    SDL_Rect rect3 = { 180,0,57,58 };//���� ����
    SDL_Rect rect4 = { 120,0,57,58 };//�Ұܱ�
    SDL_Rect r1 = { 0,0,68,121};//1��(������, ó�� ����)
    SDL_Rect r2 = { 68,0,75,121 };//2��(����)  
    SDL_Rect r3 = { 211,0,70,121 };//3�� ����(���� ��)
    SDL_Rect r4 = { 143,0,60,121 };//4�� ����(������ ��)
    SDL_Rect r5 = { 282,0,70,121 };//�� �ѱ�

    //��ġ ����
    SDL_Rect choose_light = { 0,0, 1280,720 };
    SDL_Rect time_bar = { 0,0, 1280,720 };
    SDL_Rect slot_icon1 = { 882,217,57,58 };//1�� ����
    SDL_Rect slot_icon2 = { 985,217,57,58 };//2�� ����
    SDL_Rect slot_icon3 = { 1086,217,57,58 };//3�� ����
    SDL_Rect slot_icon4 = { 1187,217,57,58 };//4�� ����
    SDL_Rect slot_icon5 = { 933,352,57,58 };//5�� ����
    SDL_Rect slot_icon6 = { 1035,352,57,58 };//6�� ����
    SDL_Rect slot_icon7 = { 1136,352,57,58 };//7�� ����
    SDL_Rect light1 = { 0,0,1280,720 };
    SDL_Rect light2 = { -100,0,1280,720 };
    SDL_Rect robot = { 390,88,70,121 };//��ġ
    SDL_Rect block = { 510,270,74,15 };
    SDL_Rect block2 = { 273,320,74,15 };
    SDL_Rect block3 = { 441,360,74,15 };
    SDL_Rect fade = { 0,720,1280,720 };

    SDL_Event e;
    int quit = 0;
    int time = 0;
    int focus = 0;
    int choose = 0;
    int move_num = 0;
    int check = 0; //���� �߿��� 0�̾��ٰ� Ư�� �ð��� 1�� ��ȯ
    int check2 = 0; //���� �迭�� ���ڰ� �����Ǹ� 1�� ��ȯ�ϰ� �̰ʹ�� �ؽ�ó�� �ٲ۴�
    Uint8 alpha = 0;
    Uint8 alpha2 = 0;

    int*n[7]; //������ �׸���
    int move[7] = { 0 }; //������ �� ����
    int v[7] = {1,1,1,1,1,1,1};
    int v2 = 1;

    // ���� ����
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
                if (e.key.keysym.sym == SDLK_UP)
                {
                    if(choose<7)
                        choose += 1;
                }
                if (e.key.keysym.sym == SDLK_SPACE)
                {
                    focus += 1;
                    if (!(focus % 4))
                        choose_light.x = 0;
                    else
                        choose_light.x += 190;
                }
            }
        }

        SDL_RenderClear(renderer);

        //�׸���
        SDL_RenderCopy(renderer, texture[1], NULL, &choose_light);//���� ��
        SDL_RenderCopy(renderer, texture[5], NULL, &time_bar);//�ð� ��
        SDL_RenderCopy(renderer, texture[0], NULL, NULL);//��
        SDL_SetTextureAlphaMod(texture[2], alpha);
        SDL_SetTextureAlphaMod(texture[3], alpha2);
        SDL_RenderCopy(renderer, texture[2], NULL, &light1);//�� ���� 
        SDL_RenderCopy(renderer, texture[3], NULL, &light2);//�� �Ʒ���
        SDL_RenderCopy(renderer, texture[4], NULL, NULL);//����

        //SDL_RenderCopy(renderer, texture[8], NULL, &block);//������ ����
        //SDL_RenderCopy(renderer, texture[8], NULL, &block2);//������ ����
        //SDL_RenderCopy(renderer, texture[8], NULL, &block3);//������ ����

        if(!(time%22))
            SDL_RenderCopy(renderer, texture[11], NULL, NULL);
        if (time >= 6300)
            SDL_RenderCopy(renderer, texture[9], NULL, NULL);
        if (time <= 5500)
            SDL_RenderCopy(renderer, texture[6], &r1, &robot);//ó�� ����
        if (time >= 6450)
            SDL_RenderCopy(renderer, texture[6], &r1, &robot);//�� Ų �� ���

        //7�� ����
        if (choose <= 6)
        {
            if (!(focus % 4))
            {
                n[choose] = &rect1; //������ ���� ������
                move[choose] = 1;
            }
            else if (focus % 4 == 1)
            {
                n[choose] = &rect2; //���������� ȸ�� ������
                move[choose] = 2;
            }
            else if (focus % 4 == 2)
            {
                n[choose] = &rect3; //�������� ȸ�� ������
                move[choose] = 3;
            }
            else
            {
                n[choose] = &rect4; //�� �ѱ� ������
                move[choose] = 4;
            }
        }

        //�� ������ ���Կ� �׸���
        switch (choose)
        {
        case 7:
            SDL_RenderCopy(renderer, texture[7], n[6], &slot_icon7);
        case 6:
            SDL_RenderCopy(renderer, texture[7], n[5], &slot_icon6);
        case 5:
            SDL_RenderCopy(renderer, texture[7], n[4], &slot_icon5);
        case 4:
            SDL_RenderCopy(renderer, texture[7], n[3], &slot_icon4);
        case 3:
            SDL_RenderCopy(renderer, texture[7], n[2], &slot_icon3);
        case 2:
            SDL_RenderCopy(renderer, texture[7], n[1], &slot_icon2);
        case 1:
            SDL_RenderCopy(renderer, texture[7], n[0], &slot_icon1);
            break;
        }
        
        if (time >= 5500) //�ð��� �� �Ǿ��� ��
        {
            if (move[0] != 1 || move[1] != 2 || move[2] != 1 || move[3] != 1 || move[4] != 3
                || move[5] != 1 || move[6] != 4)
            {
                quit = 1;
                printf("�װ� �ƴ� ����");
            }
                
            if(time>=6000)
                alpha = 0;
            else
                alpha = 255;

            if (!(time % 150))
            {
                if(move_num<7)
                    move_num++;

                if (light1.x < 300)
                    light1.x += 101;

                else
                {
                    if(time>=6400)
                        alpha2 = 0;
                    else
                        alpha2 = 255;
                    if (light2.x < 300)
                        light2.x += 101;
                }
            }

            if (time >= 4300 && time <= 5500)
                check = 1;
            else
                check = 0;

            //������ ������ ���ڿ� ���� ���� ����
            if (check)
            {
                for (int i = 0; i < 7; i++)
                {
                    switch (move[i])
                    {
                    case 1:
                        v[i] = v2;
                        break;

                    case 2:
                        v2 += 1;
                        if(v2 == 5)
                            v2 = 1;
                        v[i] = v2;
                        break;

                    case 3:
                        v2 -= 1;
                        if (v2 == 0)
                            v2 = 4;
                        v[i] = v2;
                        break;

                    case 4:
                        v[i] = v2;
                    }
                }
            }

            //������ ���ڿ� ���� ���ڴ�� �����̱�(��ġ ����)
            switch (move[move_num])
            {
            case 1:
                if (v[move_num] == 1)
                {
                    SDL_RenderCopy(renderer, texture[6], &r1, &robot);//ó�� ����
                    if (checkCollision(&robot, &block))
                    {
                    }
                    if (checkCollision(&robot, &block3))
                    {
                    }
                    else if(!(time % 2))
                    {
                        robot.x += 3;
                        robot.y+=2;
                    }
                }
                else if (v[move_num] == 2)
                {
                    SDL_RenderCopy(renderer, texture[6], &r2, &robot);
                    if (checkCollision(&robot, &block2))
                    {
                    }
                    else
                    {
                        robot.x -= 2;
                        robot.y++;
                    }
                }
                break;
            case 2:
                if (v[move_num] == 1)
                    SDL_RenderCopy(renderer, texture[6], &r1, &robot);
                else if (v[move_num] == 2)
                    SDL_RenderCopy(renderer, texture[6], &r2, &robot);
                break;
            case 3:
                if (v[move_num] == 1)
                    SDL_RenderCopy(renderer, texture[6], &r1, &robot);
                else if (v[move_num] == 2)
                    SDL_RenderCopy(renderer, texture[6], &r2, &robot);
                break;
            case 4:
                if (v[move_num] == 1)
                    SDL_RenderCopy(renderer, texture[6], &r5, &robot);
                else if (v[move_num] == 2)
                    SDL_RenderCopy(renderer, texture[6], &r5, &robot);
                break;
            }
        }

        //��� ���� 
        time++;
        if (time_bar.x >= -370)
        {
            if (!(time%15))
                time_bar.x--;  
        }
        else
            SDL_DestroyTexture(texture[5]);

        if (time >= 6800)
        {
            SDL_RenderCopy(renderer, texture[10], NULL, &fade);
            if (fade.y > 0)
                fade.y -= 4;
            else
            {
                for (int i = 0; i < num; i++)
                    SDL_DestroyTexture(texture[i]);
            }
        }
                 
        //printf("%d\n", time);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }

    for (int i = 0; i < 7; i++)
    {
        printf("���� ");
        printf("%d\t", v[i]);
    }
    printf("\n");
    for (int i = 0; i < 7; i++)
    {
        printf("������ ���� ");
        printf("%d\t", move[i]);
    }
    // ���ҽ� ����
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);

    IMG_Quit();
    SDL_Quit();
}
*/
이동거리를 기준으로 했을 때

void Stage1::Update()
{
    //std::cout << cube3.pos.x <<" , " << cube3.pos.y << "\n";
    //std::cout << speed_drect.x <<" , " << speed_drect.y << "\n";
    //std::cout << angle << "\n";

    //1p alpha
    if (a > 15)
    {
        a -= 10;
    }

    //move
    if (cube1.pos.x < 1320)
    {
        cube1.pos.x += 10;

        if (Dintro_font1.y <= 88)
        {
            Dintro_font1.y += 10;
        }
    }

    else if (cube1.pos.x >= 1320)
    {
                if (cube2.pos.x > -200)
                {
                    cube2.pos.x -= 10;
                }

                else if (cube2.pos.x <= -200)
                {
                    if (cube3.pos.x < 1700)
                    {
                        cube3.pos.x += 10;
                    }

                    else if (cube3.pos.x >= 1700)
                    {
                        angle3 += 8;

                        Dintro_font1.y = 720;
                        Dintro_font2.y = 720;
                        Dintro_font3.y = 720;

                        SDL_DestroyTexture(bg);
                        SDL_DestroyTexture(bg2);
                        SDL_DestroyTexture(bg3);
                        SDL_DestroyTexture(bg4);
                        SDL_DestroyTexture(yfont);
                        SDL_DestroyTexture(space);
                        SDL_DestroyTexture(is);
                        SDL_DestroyTexture(key);

                        if (Dtitle1.y <= 252)
                            Dtitle1.y += 4;

                        else
                        {
                            if (Dtitle2.y <= 252)
                                Dtitle2.y += 4;

                            else
                            {
                                if (SDL_HasIntersection(&Dplayer3, &Dstar))
                                {
                                    speed = true;
                                    Dstar.y = 720;
                                }

                                if (speed)
                                {
                                    if (Dplayer3.x <= 2500)
                                    {
                                        Dplayer3.x += 23;
                                        speed_drect.x -= 40;
                                        speed_drect2.x -= 20;

                                        if (Dluck_font.y <= 255)
                                            Dluck_font.y += 5;
                                    }
                                }
                                else
                                    Dplayer3.x += 10;
                            }
                        }
                    }

                    if (Dintro_font3.y <= 516)
                    {
                        Dintro_font2.y += 40;
                        Dintro_font3.y += 10;
                    }
                }

                if (Dintro_font2.y <= 306)
                {
                    Dintro_font1.y += 37;
                    Dintro_font2.y += 10;
                }
    }

    // player
    if (cube1.jumping && angle <= 180)
    {
        angle += 6;
    }
    else { angle = 0; }

    if (cube2.jumping && angle2 >= -180)
    {
        angle2 -= 6;
    }
    else { angle2 = 0; }

    //font
    if (alpha > 0)
    {
        alpha -= 15;
    }
    else if (alpha2 > 0)
    {
        alpha2 -= 15;
    }
    else if (alpha3 > 0)
    {
        alpha3 -= 15;
    }

    cube1.Update(g_timestep_s);
    cube2.Update(g_timestep_s);
    cube3.Update(g_timestep_s);
}


SDL_DestroyTexture(tex);
SDL_DestroyTexture(speed1);
SDL_DestroyTexture(speed2);
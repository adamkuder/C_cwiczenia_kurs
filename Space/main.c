#include <stdio.h>
#include <stdlib.h>
#define SDL_MAIN_HANDLED
#define WINDOW_WIDTH (800)
#define WINDOW_HEIGHT (600)
#define SPEED (300)
#define DIFFICULTY_LEVEL (500) ///ERROR <48<HARD<500<EASY
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <unistd.h>
void swap(int *a, int *b)
{
   int t;

   t  = *b;
   *b = *a;
   *a = t;
}
int random(int min, int max)
{
    int tmp;
    if (max>=min)
        max-= min;
    else
    {
        tmp= min - max;
        min= max;
        max= tmp;
    }
    return max ? (rand() % max + min) : min;
}
int main(void)
{
    if ( SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        printf(" NIE DZIALA: %s \n",SDL_GetError());
        return 1;
    }
    SDL_Window* win = SDL_CreateWindow("hello",
                             SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED,
                             WINDOW_WIDTH,WINDOW_HEIGHT,0);
    if(!win)
    {
        printf("error creating window %s \n",SDL_GetError());
        SDL_Quit();
        return 1;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED |SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if(!rend)
    {
        printf("error creating rendered %s \n",SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    ///Zaladowanie obrazu

    SDL_Surface* surface = IMG_Load("lol.png");
    SDL_Surface* mob_surface = IMG_Load("mob.png");
    SDL_Surface* fire_surface = IMG_Load("fire.png");
    SDL_Surface* mob_fire_surface = IMG_Load("mob_fire.png");
    SDL_Surface* explo = IMG_Load("expl.png");
    if(!surface)
    {
        printf("error creating surface %s \n",SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    ///stworki
    SDL_Texture* mob1 = SDL_CreateTextureFromSurface(rend, mob_surface);
    SDL_FreeSurface(mob_surface);
    SDL_Texture* shoott = SDL_CreateTextureFromSurface(rend, fire_surface);
    SDL_FreeSurface(fire_surface);
    SDL_Texture* mob_shoot = SDL_CreateTextureFromSurface(rend, mob_fire_surface);
    SDL_FreeSurface(mob_fire_surface);
    SDL_Texture* expl= SDL_CreateTextureFromSurface(rend, explo);
    SDL_FreeSurface(explo);

    if(!tex)
    {
        printf("error creating texture %s \n",SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    //do poruszania sie naszego obrazu pole powierzchni
    SDL_Rect dest;
    SDL_QueryTexture(tex, NULL, NULL, &dest.w,&dest.h);
    dest.x = 0;
    dest.y = 0;

    float x_pos = WINDOW_WIDTH/2;
    float y_pos = WINDOW_HEIGHT-60;
    float x_vel = SPEED;
    int right=0,left=0,up=0,down=0,choice_option=0;
    SDL_Rect mob_dest[48];
    int j=0;
    int k=1;


    //tworzenie mobkow
    for(int i=0; i<=48; i++)
    {
        SDL_QueryTexture(mob1, NULL, NULL, &mob_dest[i].w,&mob_dest[i].h);
        j++;
        if(j==13)
        {
            k++;
            j=1;
        }
        mob_dest[i].x=40*j;
        mob_dest[i].y=50*k;
    }
    int move_mob=0, choice_mob=0, ekchem=0, shooting=0, active_shooting=0,shooting_mob=0,success_end=0,
    to_speed_mob=0, speed_mob=2, the_score=0,change_color_text=0,to_expl=-1,to_expl_count=0;
    char the_score_str[10]="0";
    SDL_Rect shoot_dest[10000];
    SDL_Rect mob_shoot_dest[10000];

    int destroyed[49];
    for(int j=0; j<=48; j++)
    {
        destroyed[j]=0;
    }

    //do score pobieranie czcionki i takie tam
    if(TTF_Init()==-1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    }
    TTF_Font* Sans = TTF_OpenFont("OpenSans-ExtraBold.ttf", 20);

    if(!Sans)
    {
        printf("error creating font %s \n",TTF_GetError());
    }
    SDL_Color Violet = {255, 0, 255};
    SDL_Color White = {255, 255, 255};

    SDL_Rect Message_rect[6];
    Message_rect[0].x = 10;
    Message_rect[0].y = 10;
    Message_rect[0].w = 40;
    Message_rect[0].h = 30;
    Message_rect[1].x = 60;
    Message_rect[1].y = 10;
    Message_rect[1].w = 20;
    Message_rect[1].h = 30;
    Message_rect[2].x = WINDOW_WIDTH/2-45;
    Message_rect[3].x = WINDOW_WIDTH/2-45;
    Message_rect[4].x = WINDOW_WIDTH/2-45;
    Message_rect[5].x = WINDOW_WIDTH/2-75;
    Message_rect[2].y = WINDOW_HEIGHT/2-60;
    Message_rect[3].y = WINDOW_HEIGHT/2;
    Message_rect[4].y = WINDOW_HEIGHT/2+60;
    Message_rect[5].y = WINDOW_HEIGHT/2;
    for(int i=2; i<=4; i++)
    {
            Message_rect[i].h=30;
            Message_rect[i].w=90;
    }
    Message_rect[5].h=60;
    Message_rect[5].w=190;



    char ch[15],position1[4],position2[4],position3[4];
    FILE *source, *target;
    int my_index_file=0;
    source = fopen("SCORE.txt", "r");
    while ((ch[my_index_file] = fgetc(source)) != EOF)
            {
                my_index_file++;
            }
    fclose(source);
    int postionos=0;
    int firs=0,sec=0,tri=0;
    for(int i=0; i<my_index_file; i++)
    {

        if(ch[i]!=' ')
        {
            if(ch[i]=='\n' )
            {
                postionos++;
            }
            else
            {
                if(postionos==0)
                {
                    position1[firs]=ch[i];
                    firs++;
                }
                else if(postionos==1)
                {
                    position2[sec]=ch[i];
                    sec++;
                }
                else if(postionos==2)
                {
                    position3[tri]=ch[i];
                    tri++;
                }
            }

        }
    }

    int koniec=99,close=0;
    while(!close)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {

            switch( event.type ){
                case SDL_QUIT:
                    close=1;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_UP:
                        change_color_text--;
                        break;
                    case SDL_SCANCODE_DOWN:
                        change_color_text++;
                        break;
                    case SDL_SCANCODE_SPACE:
                        choice_option=1;

                    }
                    break;
                    default:
                        break;
            }
        }
        if(change_color_text<0)
        {
            change_color_text=2;
        }
        if(change_color_text==1)
        {
            SDL_Surface* surfaceMessage2 = TTF_RenderText_Solid(Sans, "START", Violet);
            SDL_Surface* surfaceMessage3 = TTF_RenderText_Solid(Sans, "WYNIK", White);
            SDL_Surface* surfaceMessage4 = TTF_RenderText_Solid(Sans, "KONIEC", Violet);

            SDL_Texture* Message2 = SDL_CreateTextureFromSurface(rend, surfaceMessage2);
            SDL_Texture* Message3 = SDL_CreateTextureFromSurface(rend, surfaceMessage3);
            SDL_Texture* Message4 = SDL_CreateTextureFromSurface(rend, surfaceMessage4);

            SDL_RenderClear(rend);
            SDL_RenderCopy(rend, Message2, NULL, &Message_rect[2]);
            SDL_RenderCopy(rend, Message3, NULL, &Message_rect[3]);
            SDL_RenderCopy(rend, Message4, NULL, &Message_rect[4]);
        }
        else if(change_color_text==2)
        {
            SDL_Surface* surfaceMessage2 = TTF_RenderText_Solid(Sans, "START", Violet);
            SDL_Surface* surfaceMessage3 = TTF_RenderText_Solid(Sans, "WYNIK", Violet);
            SDL_Surface* surfaceMessage4 = TTF_RenderText_Solid(Sans, "KONIEC", White);

            SDL_Texture* Message2 = SDL_CreateTextureFromSurface(rend, surfaceMessage2);
            SDL_Texture* Message3 = SDL_CreateTextureFromSurface(rend, surfaceMessage3);
            SDL_Texture* Message4 = SDL_CreateTextureFromSurface(rend, surfaceMessage4);

            SDL_RenderClear(rend);
            SDL_RenderCopy(rend, Message2, NULL, &Message_rect[2]);
            SDL_RenderCopy(rend, Message3, NULL, &Message_rect[3]);
            SDL_RenderCopy(rend, Message4, NULL, &Message_rect[4]);
        }
        else
        {
            SDL_Surface* surfaceMessage2 = TTF_RenderText_Solid(Sans, "START", White);
            SDL_Surface* surfaceMessage3 = TTF_RenderText_Solid(Sans, "WYNIK", Violet);
            SDL_Surface* surfaceMessage4 = TTF_RenderText_Solid(Sans, "KONIEC", Violet);
            change_color_text=0;

            SDL_Texture* Message2 = SDL_CreateTextureFromSurface(rend, surfaceMessage2);
            SDL_Texture* Message3 = SDL_CreateTextureFromSurface(rend, surfaceMessage3);
            SDL_Texture* Message4 = SDL_CreateTextureFromSurface(rend, surfaceMessage4);

            SDL_RenderClear(rend);
            SDL_RenderCopy(rend, Message2, NULL, &Message_rect[2]);
            SDL_RenderCopy(rend, Message3, NULL, &Message_rect[3]);
            SDL_RenderCopy(rend, Message4, NULL, &Message_rect[4]);
        }
        if(choice_option==1)
        {
            choice_option=0;
            if(change_color_text==0)
            {

                k=1;
                j=0;
                for(int i=0; i<=47; i++)
                {
                    destroyed[i]=0;
                    j++;
                    if(j==13)
                    {
                    k++;
                    j=1;
                    }
                    mob_dest[i].x=40*j;
                    mob_dest[i].y=50*k;
                }
                koniec=0;
            }
            else if (change_color_text==1)
            {
                choice_option=2;
                SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "score ", Violet);
                SDL_Surface* surfaceMessage1 = TTF_RenderText_Solid(Sans, the_score_str, Violet);
                SDL_Surface* surfaceMessage7 = TTF_RenderText_Solid(Sans, position1, Violet);
                SDL_Surface* surfaceMessage8 = TTF_RenderText_Solid(Sans, position2, Violet);
                SDL_Surface* surfaceMessage9 = TTF_RenderText_Solid(Sans, position3, Violet);
                SDL_Texture* Message7 = SDL_CreateTextureFromSurface(rend, surfaceMessage7);
                SDL_Texture* Message8 = SDL_CreateTextureFromSurface(rend, surfaceMessage8);
                SDL_Texture* Message9 = SDL_CreateTextureFromSurface(rend, surfaceMessage9);
                SDL_Texture* Message = SDL_CreateTextureFromSurface(rend, surfaceMessage);
                SDL_Texture* Message1 = SDL_CreateTextureFromSurface(rend, surfaceMessage1);
                SDL_RenderClear(rend);
                SDL_RenderCopy(rend, Message, NULL, &Message_rect[0]);
                SDL_RenderCopy(rend, Message1, NULL, &Message_rect[1]);
                SDL_RenderCopy(rend, Message7, NULL, &Message_rect[2]);
                SDL_RenderCopy(rend, Message8, NULL, &Message_rect[3]);
                SDL_RenderCopy(rend, Message9, NULL, &Message_rect[4]);

            }
            else if (change_color_text==2)
            {
                close=1;
            }
        }

        SDL_RenderPresent(rend);
        if(choice_option==2)
        {
            SDL_Delay(5000);
            choice_option=0;
        }
        SDL_Delay(1000/60);




        while(!koniec)
        {
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "score ", Violet);
        SDL_Surface* surfaceMessage1 = TTF_RenderText_Solid(Sans, the_score_str, Violet);
        SDL_Surface* surfaceMessage5 = TTF_RenderText_Solid(Sans, "PORAZKA", Violet);
        SDL_Surface* surfaceMessage6 = TTF_RenderText_Solid(Sans, "ZWYCIESTWO", Violet);

        SDL_Texture* Message = SDL_CreateTextureFromSurface(rend, surfaceMessage);
        SDL_Texture* Message1 = SDL_CreateTextureFromSurface(rend, surfaceMessage1);
        SDL_Texture* Message5 = SDL_CreateTextureFromSurface(rend, surfaceMessage5);
        SDL_Texture* Message6 = SDL_CreateTextureFromSurface(rend, surfaceMessage6);


        if(move_mob==3)
        {
            //sprawdzanie z prawej strony kolizje mobkow
            if(choice_mob == 0)
            {
                for(int i=0; i<=47; i++)
                {

                    if(mob_dest[i].x>=WINDOW_WIDTH-30 && destroyed[i]==0)
                    {
                        choice_mob=1;
                        break;
                    }
                    else
                    {
                        choice_mob=0;
                    }
                }
            }
            //sprawdzanie z lewej strony kolizje mobkow
            if(choice_mob == 2)
            {
                for(int i=0; i<=47; i++)
                {

                    if(mob_dest[i].x<=2 &&destroyed[i]==0)
                    {
                        choice_mob=1;
                        break;
                    }
                    else
                    {
                        choice_mob=2;
                    }
                }
            }
            // poruszanie sie w prawo mobki
            if(choice_mob==0)
            {
                for(int i=0; i<=47; i++)
                {
                    mob_dest[i].x+=speed_mob;
                }
                move_mob=0;
            }
            //poruszanie sie w lewo mobki
            if(choice_mob==2)
            {
                for(int i=0; i<=48; i++)
                {
                    mob_dest[i].x-=speed_mob;
                }
                move_mob=0;
            }
            // w przypadku kolizji wszystko o troche nizej
            if(choice_mob==1)
            {
                for(int i=0; i<=48; i++)
                {
                    mob_dest[i].y+=20;
                }
                if(ekchem%2==0)
                {
                    ekchem++;
                   choice_mob=2;
                }
                else
                {choice_mob=0;ekchem++;}

                move_mob=0;
            }
            int losu=random(0,DIFFICULTY_LEVEL);
            //moobki strzelaja
            if (losu<47)
            {
                if(destroyed[losu]!=1)
                {
                    printf("wylosowany to %d, o x= %d i y= %d \n",losu,mob_dest[losu].y,mob_dest[losu].x);
                    SDL_QueryTexture(mob_shoot, NULL, NULL, &mob_shoot_dest[shooting_mob].w,&mob_shoot_dest[shooting_mob].h);
                    mob_shoot_dest[shooting_mob].y=mob_dest[losu].y+20;
                    mob_shoot_dest[shooting_mob].x=mob_dest[losu].x+5;
                    shooting_mob++;
                }

            }

        }
        move_mob++;

        //mob_dest[i].x+=1;
        //zamykanie na x

        while(SDL_PollEvent(&event))
        {

            switch( event.type ){
                case SDL_QUIT:
                    close=1;
                    koniec=1;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_RIGHT:
                        right=1;
                        break;
                    case SDL_SCANCODE_LEFT:
                        left=1;
                        break;
                    case SDL_SCANCODE_SPACE:
                        active_shooting=1;
                        break;
                    }
                    break;
                case SDL_KEYUP:
                    switch(event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_RIGHT:
                        right=0;
                        break;
                    case SDL_SCANCODE_LEFT:
                        left=0;
                        break;
                    }

                    default:
                        break;
            }
        }
        if(right==1)
        {

            if(x_pos>=WINDOW_WIDTH-48)
            {
                x_pos=WINDOW_WIDTH-48;
            }
            else{x_pos +=x_vel/50;}
        }
        if(left==1)
        {
            if(x_pos<=0)
            {
                x_pos=0;
            }
            else {x_pos -= x_vel/50;}
        }
        dest.y= (int) y_pos;
        dest.x= (int) x_pos;
        //strzelanie
        if(active_shooting==1)
        {
            shooting++;
            SDL_QueryTexture(shoott, NULL, NULL, &shoot_dest[shooting].w,&shoot_dest[shooting].h);

            active_shooting=0;
            shoot_dest[shooting].y=dest.y-20;
            shoot_dest[shooting].x=dest.x+14;
        }
        if(shooting>0)
        {
            for(int i=1; i<=shooting; i++)
            {
                shoot_dest[i].y-=3;
            }
        }
        if(shooting_mob>0)
        {
            for(int i=1; i<=shooting_mob; i++)
            {
                mob_shoot_dest[i].y+=3;
            }
        }

        //kolizja z strzalem
        for(int i=0; i<=48; i++)
        {
            for(int j=0; j<=shooting; j++){
                if(shoot_dest[j].y<mob_dest[i].y+mob_dest[i].h &&
               shoot_dest[j].y+shoot_dest[j].h>mob_dest[i].y &&
               shoot_dest[j].x<mob_dest[i].x+mob_dest[i].w &&
               shoot_dest[j].x+shoot_dest[j].w>mob_dest[i].x && destroyed[i]==0)
            {
                destroyed[i]=1;
                shoot_dest[j].y=-30;
                the_score++;
                to_expl=i;
            }
            }
        }

        //kolizja z playerem

        for(int j=0; j<=47; j++)
            {
            if(mob_dest[j].y<dest.y+dest.h &&
                mob_dest[j].y+mob_dest[j].h>dest.y &&
                mob_dest[j].x<dest.x+dest.w &&
                mob_dest[j].x+mob_dest[j].w>dest.x)
                {
                    koniec=1;
                }
            }

        //kolizja z strzalem moba

        for(int j=0; j<=shooting_mob; j++)
        {
        if(mob_shoot_dest[j].y<dest.y+dest.h &&
            mob_shoot_dest[j].y+mob_shoot_dest[j].h>dest.y &&
            mob_shoot_dest[j].x<dest.x+dest.w &&
            mob_shoot_dest[j].x+mob_shoot_dest[j].w>dest.x)
            {
                koniec=1;
            }

        }

        //score z int do char

        sprintf(the_score_str, " %d", the_score);
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, Message, NULL, &Message_rect[0]);
        SDL_RenderCopy(rend, Message1, NULL, &Message_rect[1]);


        if(shooting_mob>0)
        {
            for(int i=1; i<=shooting_mob; i++)
            {
                if(mob_shoot_dest[i].y<WINDOW_HEIGHT)
                {
                    SDL_RenderCopy(rend, mob_shoot, NULL, &mob_shoot_dest[i]);
                }
            }
        }


        if(shooting>0)
        {
        for(int i=1; i<=shooting; i++)
            {
                if(shoot_dest[i].y>0)
                {
                    SDL_RenderCopy(rend, shoott, NULL, &shoot_dest[i]);
                }

            }
        }
        success_end=2;
        to_speed_mob=0;
        for(int i=0; i<=47; i++)
        {
            if(destroyed[i]==0)
            {
                SDL_RenderCopy(rend, mob1, NULL, &mob_dest[i]);
                success_end=0;
            }
            else to_speed_mob++;

        }
        if(success_end==2)
        {
            koniec=2;
        }
        if(to_speed_mob>10)
        {
            move_mob=3;
            speed_mob=(int) to_speed_mob/8;
        }

        SDL_RenderCopy(rend, tex, NULL, &dest);

        if(to_expl!=-1)
        {
            SDL_RenderCopy(rend, expl, NULL, &mob_dest[to_expl]);
            if(to_expl_count==1)
            {
                to_expl=-1;
                to_expl_count=0;
            }
            else {to_expl_count++;}
        }


        SDL_RenderPresent(rend);

        SDL_Delay(1000/60);
        if(koniec==1)
        {
            SDL_Delay(2000);
            SDL_RenderClear(rend);
            SDL_RenderCopy(rend, Message5, NULL, &Message_rect[5]);
            SDL_RenderPresent(rend);
            SDL_Delay(2000);
            int pos1=atoi(position1);
            int pos2=atoi(position2);
            int pos3=atoi(position3);
            if(the_score>pos3)
            {
                swap(&the_score,&pos3);
                if(pos3>pos2)
                {
                    swap(&pos3,&pos2);
                    if(pos2>pos1)
                    {
                        swap(&pos1,&pos2);
                    }
                }
            }

            the_score=0;
            sprintf(position1, "%d", pos1);
            printf("post1 = %s ",position1);
            sprintf(position2, "%d", pos2);
            printf("post2 = %s ",position2);
            sprintf(position3, "%d", pos3);


        }
        if(koniec==2)
        {
            SDL_Delay(500);
            SDL_RenderClear(rend);
            SDL_RenderCopy(rend, Message6, NULL, &Message_rect[5]);
            SDL_RenderPresent(rend);
            SDL_Delay(2000);
        }
    }
    for(int i=0;i<=shooting_mob; i++)
    {
        mob_shoot_dest[i].y=0;
    }
    shooting=0;
    shooting_mob=0;
    }

    target = fopen("SCORE.txt", "w");
    for (int i = 0; position1[i]!='\0'; i++) fputc(position1[i], target);
    fputc('\n', target);
    for (int i = 0; position2[i]!='\0'; i++) fputc(position2[i], target);
    fputc('\n', target);
    for (int i = 0; position3[i]!='\0'; i++) fputc(position3[i], target);
    fclose(target);
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <math.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <fstream>
#include <MMsystem.h>

using namespace std;

#define width 1920
#define height 1055

bool EXIT, hidder, menu_pop_up, hover_mode, clear, draw_menu = 1, is_open = 0, change_bk, Loading_Done = 0, Menu_Exit, abord = 0, mute = 0, draww = 1;   // Daca e 1 iese din bucla / Daca e 1 ascunde liniile
int zoom_level = 4, x, y, hover_tab = 0, color = 2, menu_selector, background_selector = 1, menu_tab_selector, timer, font_color, start_Loading, file_memory[1000], load_position, language = 1;
char key = NULL, checkmark[] = "Backgrounds\\Place.jpg", name[15], load_name[11][15];

int nb_of_piese = 0, load_number[11];
int nb_of_wires = 0, load_wire_nb[11];
int matrice_tabla[400][400];

struct
{
    int x, y;
    int rotation;
    int tip;
    int on;
} piese[100], load_piese[11][100];

struct capat
{
    //0 daca nu e unit, 1 daca e unit cu stanga, 2 daca e unit cu dreapta
    int info;
    //pozitia in vector a elementului cu care e unit capatul curent
    int poz;
};

struct fire
{
    //pozitia in vectorul piese al celor doua piese ce vor fi unite
    int poz1, poz2;
    //1 daca e capat stanga, 2 daca e capat dreapta
    int info1, info2;
} wires[1000],load_wire[11][1000];


ifstream Input;
ofstream Output;

void End_screen()
{

    initwindow(500, 50, "Hope to see you again soon", width / 2 - 250, height / 2 - 20);
    settextstyle(8, 0, 15);
    setcolor(YELLOW);
    switch (language)
    {
    case 1:
        outtextxy(20, 12, "THANK YOU FOR YOUR TIME");
        break;
    case 2:
        settextstyle(8, 0, 14);
        outtextxy(20, 12, "MULTUMESC PENTRU TIMPUL ACORDAT");
        break;
    case 3:
        outtextxy(30, 12, "MERCI POUR VOTRE TEMPS ");
        break;
    }
    getch();

}

void bkcolor()
{
    switch (color)
    {
    case 1:
        setbkcolor(9);
        break;
    case 2:
        setbkcolor(4);
        break;
    case 3:
        setbkcolor(2);
        break;
    case 4:
        setbkcolor(14);
        break;
    case 5:
        setbkcolor(13);
        break;
    case 6:
        setbkcolor(15);
        break;
    }

}

void fontcolor()
{
    switch (color)
    {
    case 1:
        font_color = 10;
        break;
    case 2:
        font_color = 14;
        break;
    case 3:
        font_color = 13;
        break;
    case 4:
        font_color = 9;
        break;
    case 5:
        font_color = 11;
        break;
    case 6:
        font_color = 12;
        break;
    }
}

void Background_Image()
{
    char background[] = "Backgrounds\\loading.jpg";
    char background1[] = "Backgrounds\\bg1.jpg";
    char background2[] = "Backgrounds\\bg2.jpg";
    char background3[] = "Backgrounds\\bg3.jpg";
    char background4[] = "Backgrounds\\bg4.jpg";
    char background5[] = "Backgrounds\\bg5.jpg";
    char background6[] = "Backgrounds\\bg6.jpg";

    switch (background_selector)
    {
    case -1:
        readimagefile(background, 0, 0, 1920, 1055);
        break;    // importa background-ul
    case 1:
        readimagefile(background1, 0, 0, 1920, 1055);
        break;    // importa background-ul
    case 2:
        readimagefile(background2, 0, 0, 1920, 1055);
        break;   // importa background-ul
    case 3:
        readimagefile(background3, 0, 0, 1920, 1055);
        break;   // importa background-ul
    case 4:
        readimagefile(background4, 0, 0, 1920, 1055);
        break;   // importa background-ul
    case 5:
        readimagefile(background5, 0, 0, 1920, 1055);
        break;   // importa background-ul
    case 6:
        readimagefile(background6, 0, 0, 1920, 1055);
        break;   // importa background-ul
    }
}

void read()
{

    bkcolor();
    fontcolor();
    setcolor(font_color);
    char letter;
    int k = -1;
    settextstyle(8, 0, 14);

    switch (language)
    {
    case 1:
        outtextxy(1375, 217 + (load_position - 1) * 30, "NAME:");
        break;
    case 2:
        outtextxy(1375, 217 + (load_position - 1) * 30, "NUME:");
        break;
    case 3:
        outtextxy(1375, 217 + (load_position - 1) * 30, "NOM :");
        break;
    }
    while (letter != '\r' && letter != 27)
    {
        k++;
        letter = getch();
        if (letter != '\b')
            name[k] = letter;
        else
        {
            k--;
            name[k] = ' ';
            k--;
        }
        outtextxy(1450, 217 + (load_position - 1) * 30, name);
    }
    if (letter == 27)
    {
        abord = 1;
    }
    k++;
    letter = NULL;
    name[k] = letter;
    settextstyle(8, 0, 15);
    setbkcolor(BLACK);
    setcolor(15);
}

//////////////////////////LOADING_SCREEN/////////////////////////////

void Loading_Bar()
{
    line(width / 2 - 250, 300, width / 2 + 250, 300);
    line(width / 2 - 250, 400, width / 2 + 250, 400);
    line(width / 2 - 250, 401, width / 2 + 250, 401);
    line(width / 2 - 250, 300, width / 2 - 250, 400);
    line(width / 2 - 249, 300, width / 2 - 249, 400);
    line(width / 2 + 250, 300, width / 2 + 250, 400);
    line(width / 2 + 251, 300, width / 2 + 251, 400);

    for (int i = width / 2 - 240; i <= start_Loading; i = i + 7)
    {
        line(start_Loading, 310, start_Loading + 3, 390);
        line(start_Loading + 1, 310, start_Loading + 4, 390);
        line(start_Loading + 2, 310, start_Loading + 5, 390);
    }

    if (start_Loading < width / 2 + 234 && rand() % 2 + 1 == 1)
        start_Loading = start_Loading + 7;

    if (start_Loading >= width / 2 + 234)
        switch (language)
        {
        case 1:
            outtextxy(width / 2 - strlen("PRESS ANY KEY TO CONTINUE") * 10, 1000, "PRESS ANY KEY TO CONTINUE");
            break;
        case 2:
            outtextxy(width / 2 - strlen("APASATI ORICE BUTON PENTRU A CONTINUA") * 10, 1000, "APASATI ORICE BUTON PENTRU A CONTINUA");
            break;
        case 3:
            outtextxy(width / 2 - strlen("APPUYER SUR UNE TOUCHE POUR CONTINUER") * 10, 1000, "APPUYER SUR UNE TOUCHE POUR CONTINUER");
            break;
        }
    if (start_Loading >= width / 2 + 234 && kbhit())
        Loading_Done = 1;

}

void Loading_Screen_Eye()
{
    int n, x1 = width / 2, y1 = height / 2 + 200, x[101], y[101], x2[101], y2[101], j;
    float beta;

start:
    n = 4;
    while (n <= 100)
    {
        j = 0;
        beta = 2 * 3.14 / n;

        for (int i = 1; i <= n; i++)    // calculam punctele exterioare ale stelei
        {
            x[i] = x1 + 100 * cos(i * beta);
            y[i] = y1 + 100 * sin(i * beta);

            if (i % 2 == 1)
            {

                j++;
                x2[j] = (x1 + x[i]) / 2; // calculam punctele interioare ale stelei
                y2[j] = (y1 + y[i]) / 2;

            }
        }

        j = 1;

        ///////////////////////////

        circle(x1, y1, x2[1] * n / 500);


        for (int i = 2; i < n; i = i + 2)  // unim punctele exterioare cu cele interioare
        {
            line(x[i], y[i], x2[j], y2[j]);
            j++;
            line(x[i], y[i], x2[j], y2[j]);
        }

        line(x[n], y[n], x2[j], y2[j]);
        j = 1;
        line(x[n], y[n], x2[j], y2[j]);

        ///////////////////////////////

        delay(25);
        setcolor(0);

        j = 1;

        circle(x1, y1, x2[1] * n / 500);


        for (int i = 2; i < n; i = i + 2)  // unim punctele exterioare cu cele interioare
        {
            line(x[i], y[i], x2[j], y2[j]);
            j++;
            line(x[i], y[i], x2[j], y2[j]);
        }

        line(x[n], y[n], x2[j], y2[j]);
        j = 1;
        line(x[n], y[n], x2[j], y2[j]);

        setcolor(font_color);

        //////////////////////////////

        Loading_Bar();

        n = n + 4;
    }

    if (Loading_Done != 1)
        goto start;

}

void Loading_Screen_Star()
{
    int n, x1 = width / 2, y1 = height / 2 + 200, x[100], y[100], x2[100], y2[100], j = 0;
    float beta;

    n = 10;

    beta = 2 * 3.14 / n;
    for (float z = 1; z <= 2000 && Loading_Done != 1; z = z + 0.05)
    {
        j = 0;

        for (int i = 1; i <= n; i++)    // calculam punctele exterioare ale stelei
        {
            x[i] = x1 + 200 * cos(z + i * beta);
            y[i] = y1 + 200 * sin(z + i * beta);

            if (i % 2 == 1)
            {

                j++;
                x2[j] = (x1 + x[i]) / 2; // calculam punctele interioare ale stelei
                y2[j] = (y1 + y[i]) / 2;

            }
        }

        j = 1;

        for (int i = 2; i < n; i = i + 2)  // unim punctele exterioare cu cele interioare
        {
            line(x[i], y[i], x2[j], y2[j]);
            j++;
            line(x[i], y[i], x2[j], y2[j]);
        }

        line(x[n], y[n], x2[j], y2[j]);
        j = 1;
        line(x[n], y[n], x2[j], y2[j]);

        delay(40);

        setcolor(0);

        j = 1;

        for (int i = 2; i < n; i = i + 2)  // unim punctele exterioare cu cele interioare
        {
            line(x[i], y[i], x2[j], y2[j]);
            j++;
            line(x[i], y[i], x2[j], y2[j]);
        }

        line(x[n], y[n], x2[j], y2[j]);
        j = 1;
        line(x[n], y[n], x2[j], y2[j]);

        setcolor(font_color);

        Loading_Bar();
    }
}

void circle_maker(int i, int j)
{
    circle(width / 2, height / 2 + 200, i - j);
}

void Loading_Screen_Water()
{

    int n, x1 = width / 2, y1 = height / 2 + 200, x[101], y[101], x2[101], y2[101], j;
    float beta;

    n = 10;
    j = 0;
    beta = 2 * 3.14 / n;

    for (int i = 1; i <= n; i++)    // calculam punctele exterioare ale stelei
    {
        x[i] = x1 + 50 * cos(1 + i * beta);
        y[i] = y1 + 50 * sin(1 + i * beta);

        if (i % 2 == 1)
        {

            j++;
            x2[j] = (x1 + x[i]) / 2; // calculam punctele interioare ale stelei
            y2[j] = (y1 + y[i]) / 2;

        }
    }

creste:
    for (int i = 50; i <= 200 && Loading_Done != 1; i = i + 2)
    {

        if (i <= 90)
        {
            j = 1;

            for (int i = 2; i < n; i = i + 2)  // unim punctele exterioare cu cele interioare
            {
                line(x[i], y[i], x2[j], y2[j]);
                j++;
                line(x[i], y[i], x2[j], y2[j]);
            }

            line(x[n], y[n], x2[j], y2[j]);
            j = 1;
            line(x[n], y[n], x2[j], y2[j]);
        }
        circle_maker(i, 0);
        if (i >= 100)
            circle_maker(i, 50);
        if (i >= 150)
            circle_maker(i, 100);

        ////////////////////

        delay(25);
        setcolor(0);

        if (i <= 90)
        {
            j = 1;

            for (int i = 2; i < n; i = i + 2)  // unim punctele exterioare cu cele interioare
            {
                line(x[i], y[i], x2[j], y2[j]);
                j++;
                line(x[i], y[i], x2[j], y2[j]);
            }

            line(x[n], y[n], x2[j], y2[j]);
            j = 1;
            line(x[n], y[n], x2[j], y2[j]);
        }
        circle_maker(i, 0);
        if (i >= 100)
            circle_maker(i, 50);
        if (i >= 150)
            circle_maker(i, 100);

        setcolor(font_color);

        Loading_Bar();

        if (i == 200)goto scade;
    }

scade:
    for (int i = 200; i >= 50 && Loading_Done != 1; i = i - 2)
    {

        if (i <= 90)
        {
            j = 1;

            for (int i = 2; i < n; i = i + 2)  // unim punctele exterioare cu cele interioare
            {
                line(x[i], y[i], x2[j], y2[j]);
                j++;
                line(x[i], y[i], x2[j], y2[j]);
            }

            line(x[n], y[n], x2[j], y2[j]);
            j = 1;
            line(x[n], y[n], x2[j], y2[j]);
        }
        circle_maker(i, 0);
        if (i >= 100)
            circle_maker(i, 50);
        if (i >= 150)
            circle_maker(i, 100);

        /////////

        delay(25);
        setcolor(0);

        if (i <= 90)
        {
            j = 1;

            for (int i = 2; i < n; i = i + 2)  // unim punctele exterioare cu cele interioare
            {
                line(x[i], y[i], x2[j], y2[j]);
                j++;
                line(x[i], y[i], x2[j], y2[j]);
            }

            line(x[n], y[n], x2[j], y2[j]);
            j = 1;
            line(x[n], y[n], x2[j], y2[j]);
        }
        circle_maker(i, 0);
        if (i >= 100)
            circle_maker(i, 50);
        if (i >= 150)
            circle_maker(i, 100);

        setcolor(font_color);

        Loading_Bar();

        if (i == 50)goto creste;
    }

}

void Loading_Screen()
{
    int loading_screen_motif = rand() % 3 + 1;

    int loading_prev = background_selector;
    background_selector = -1;
    Background_Image();
    bkcolor();
    fontcolor();
    setcolor(font_color);

    char text1[200], text2[200], text3[200], text4[200], text5[200], text6[200], text7[200], text8[200], text9[200], text10[200];

    if (language == 1)
    {
        strcpy(text1, "You can use both your cursor and the number keys or the tab key to navigate the menu");
        strcpy(text2, "You can move parts on the table by left clicking them and then right clicking somewhere else");
        strcpy(text3, "You can clear the entire table by pressing r(reset) or from the help button");
        strcpy(text4, "You can hide the grid by pressing h(hide) or from the help button");
        strcpy(text5, "You can zoom-in/out using +/- or from the help button");
        strcpy(text6, "By changing the theme you change the color of the parts that are on the table as well");
        strcpy(text7, "You can have more parts on the table than you might first expect");
        strcpy(text8, "You can use the arrow keys to move the table");
        strcpy(text9, "Some themes work better together with specific backgrounds");
        strcpy(text10, "You have a maximum of 10 custom save slots that you can use at any time that can be named");
    }

    if (language == 2)
    {

        strcpy(text1, "Poti sa folosesti cursorul,tastele numerotate dar si tasta tab pentru a naviga meniul");
        strcpy(text2, "Poti muta piese pe tabla apasand click dreapta pe ele apoi click stanga altundeva");
        strcpy(text3, "Poti sterge piesele de pe tabla apasand r(reset) sau din butonul ajutor");
        strcpy(text4, "Poti ascunde grila apasand h(hide) sau din butonul ajutor");
        strcpy(text5, "Poti mari sau micsora piesele apasand +/- sau din butonul ajutor");
        strcpy(text6, "Schimband tema schimbati si culoarea pieselor de pe tabla");
        strcpy(text7, "Poti avea mult mai multe piese pe tabla decat ai crede in faza incipienta");
        strcpy(text8, "Poti folosi sagetile de pe tastatura pentru a muta piesele pe tabla");
        strcpy(text9, "Unele teme se contopesc mai bine cu anumite scene");
        strcpy(text10, "Poti avea 10 sloturi separate in care sa salezi circuitele");
    }

    else if (language == 3)
    {

        strcpy(text1, "Vous pouvez utiliser votre curseur et le numeriques de tabulation pour naviguer dans le menu");
        strcpy(text2, "Vous pouvez deplacer des pieces avec le bouton puis avec le bouton droit de la souris.");
        strcpy(text3, "Vous pouvez effacer toute la table en appuyant sur r(reset) ou depuis le bouton d�aide");
        strcpy(text4, "Vous pouvez masquer la grille en appuyant sur h(hide) ou depuis le bouton d'aide");
        strcpy(text5, "Vous pouvez faire un zoom avant/arrire en utilisant +/- ou depuis le bouton d'aide");
        strcpy(text6, "En changeant leth�me vous changez la couleur des parties qui sont sur la table ainsi");
        strcpy(text7, "Vous pouvez avoir plus de pieces sur la table que vous pourriez vous y attendre");
        strcpy(text8, "Vous pouvez utiliser les touches fleches pour deplacer la table");
        strcpy(text9, "Certains themes fonctionnent mieux avec des contextes specifiques");
        strcpy(text10, "Vous avez un maximum de 10 emplacements d'tout moment qui peut tre nomm�");
    }


    settextstyle(8, 0, 18);
    switch (language)
    {
    case 1:
        outtextxy(width / 2 - strlen("TIPS") * 16, 50, "TIPS");
        break;
    case 2:
        outtextxy(width / 2 - strlen("SFATURI") * 16, 50, "SFATURI");
        break;
    case 3:
        outtextxy(width / 2 - strlen("TRUCS") * 16, 50, "TRUCS");
        break;
    }
    settextstyle(8, 0, 15);

    switch (rand() % 10 + 1)
    {
    case 1:
        outtextxy(width / 2 - strlen(text1) * 10, 150, text1);
        break;
    case 2:
        outtextxy(width / 2 - strlen(text2) * 10, 150, text2);
        break;
    case 3:
        outtextxy(width / 2 - strlen(text3) * 10, 150, text3);
        break;
    case 4:
        outtextxy(width / 2 - strlen(text4) * 10, 150, text4);
        break;
    case 5:
        outtextxy(width / 2 - strlen(text5) * 10, 150, text5);
        break;
    case 6:
        outtextxy(width / 2 - strlen(text6) * 10, 150, text6);
        break;
    case 7:
        outtextxy(width / 2 - strlen(text7) * 10, 150, text7);
        break;
    case 8:
        outtextxy(width / 2 - strlen(text8) * 10, 150, text8);
        break;
    case 9:
        outtextxy(width / 2 - strlen(text9) * 10, 150, text9);
        break;
    case 10:
        outtextxy(width / 2 - strlen(text10) * 10, 150, text10);
        break;
    }

    start_Loading = width / 2 - 240;

    switch (loading_screen_motif)
    {
    case 1:
        Loading_Screen_Eye();
        break;
    case 2:
        Loading_Screen_Star();
        break;
    case 3:
        Loading_Screen_Water();
        break;
    }

    Loading_Done = 0;
    background_selector = loading_prev;

}

void Exit_Transition()
{
    for (int i = 0; i <= 600; i++)
    {
        circle(width / 2, height / 2 + 100, i);
        circle(width / 2, height / 2 + 100, 1200 - i);
    }
}

/////////////////////BASE CODE/////////////////////////////////

void Load_Read()
{
    Input.open("DATA.txt");

    for (int i = 1; i <= 10; i++)
    {
        Input >> load_name[i];
        Input >> load_number[i];

        for (int j = 1; j <= load_number[i]; j++)
        {
            Input >> load_piese[i][j].x;
            Input >> load_piese[i][j].y;
            Input >> load_piese[i][j].rotation;
            Input >> load_piese[i][j].tip;
        }
    }
    Input.close();

    Input.open("Fire.txt");

    for (int i = 1; i <= 10; i++)
    {
        Input >> load_wire_nb[i];

        for (int j = 1; j <= load_wire_nb[i]; j++)
        {
            Input >> load_wire[i][j].poz1;
            Input >> load_wire[i][j].poz2;
            Input >> load_wire[i][j].info1;
            Input >> load_wire[i][j].info2;
        }
    }
    Input.close();

}

void Initialization()
{
    Background_Image();
    settextstyle(8, 0, 15);
    Load_Read();
}

void Map()
{

    if (menu_pop_up || clear)
    {
        menu_pop_up = 0;
        clear = 0;
        draw_menu = 1;
        hover_mode = 0;
    }

    setcolor(BLACK);
    setlinestyle(0, 0, 1);

    if (!hidder)
    {
        for (int i = 0; i < 1800; i += zoom_level * 10)          // trage liniile verticale
            line(i, 0, i, 1055);

        for (int i = 0; i <= 1055; i += zoom_level * 10)         // trage liniile orizontale
            line(0, i, 1797, i);
    }
}

void reset()
{

    for (int i = 1; i <= nb_of_piese; i++)
        piese[i].tip = 0;

    nb_of_piese = 0;
    nb_of_wires = 0;
}

void Save()
{
    Output.open("DATA.txt");

    name[strlen(name) - 1] = NULL;
    strcpy(load_name[load_position], name);
    load_number[load_position] = nb_of_piese;

    for (int j = 1; j <= nb_of_piese; j++)
    {
        load_piese[load_position][j].x = piese[j].x;
        load_piese[load_position][j].y = piese[j].y;
        load_piese[load_position][j].rotation = piese[j].rotation;
        load_piese[load_position][j].tip = piese[j].tip;
    }

    for (int i = 1; i <= 10; i++)
    {
        Output << load_name[i] << " ";
        Output << load_number[i] << " ";
        for (int j = 1; j <= load_number[i]; j++)
            Output << load_piese[i][j].x << " " << load_piese[i][j].y << " " << load_piese[i][j].rotation << " " << load_piese[i][j].tip << " ";
        Output << endl;
    }

    Output.close();

    Output.open("Fire.txt");

    load_wire_nb[load_position] = nb_of_wires;

    for (int j = 1; j <= nb_of_wires; j++)
    {
        load_wire[load_position][j].poz1 = wires[j].poz1;
        load_wire[load_position][j].poz2 = wires[j].poz2;
        load_wire[load_position][j].info1 = wires[j].info1;
        load_wire[load_position][j].info2 = wires[j].info2;
    }

    for (int i = 1; i <= 10; i++)
    {
        Output << load_wire_nb[i] << " ";
        for (int j = 1; j <= load_wire_nb[i]; j++)
            Output << load_wire[i][j].poz1 << " " << load_wire[i][j].poz2 << " " << load_wire[i][j].info1 << " " << load_wire[i][j].info2 << " ";
        Output << endl;
    }

    Output.close();
}

void Load()
{
    nb_of_piese = load_number[load_position];
    for (int i = 1; i <= nb_of_piese; i++)
    {
        piese[i].x = load_piese[load_position][i].x;
        piese[i].y = load_piese[load_position][i].y;
        piese[i].rotation = load_piese[load_position][i].rotation;
        piese[i].tip = load_piese[load_position][i].tip;
    }

    nb_of_wires = load_wire_nb[load_position];
    for (int i = 1; i <= nb_of_wires; i++)
    {
        wires[i].poz1 = load_wire[load_position][i].poz1;
        wires[i].poz2 = load_wire[load_position][i].poz2;
        wires[i].info1 = load_wire[load_position][i].info1;
        wires[i].info2 = load_wire[load_position][i].info2;
    }
}

/////////////////////////MENU//////////////////////////////////

int Show_Button = 2, Show_Button_1 = 2, Show_Button_2 = 2, Show_Button_3 = 2;

void Start_Button_Maker(int y1, int y2, int color)
{
    int points[8];
    points[0] = width / 2 - 150;
    points[1] = y1;
    points[2] = width / 2 - 150;
    points[3] = y2;
    points[4] = width / 2 + 150;
    points[5] = y2;
    points[6] = width / 2 + 150;
    points[7] = y1;

    rectangle(width / 2 - 150, y1, width / 2 + 150, y2);

    setfillstyle(1, color);
    fillpoly(4, points);
}

void Load_menu_start()
{

    int points[8];
    points[0] = width / 2 + 190;
    points[1] = 560;
    points[2] = width / 2 + 190;
    points[3] = 865;
    points[4] = width / 2 + 360;
    points[5] = 865;
    points[6] = width / 2 + 360;
    points[7] = 560;

    rectangle(width / 2 + 190, 560, width / 2 + 360, 865);

    setfillstyle(1, CYAN);
    fillpoly(4, points);

    setcolor(WHITE);
    settextstyle(8, 0, 14);
    outtextxy(width / 2 + 200, 565, "0.        ");
    outtextxy(width / 2 + 245, 565, load_name[1]);
    outtextxy(width / 2 + 200, 595, "1.        ");
    outtextxy(width / 2 + 245, 595, load_name[2]);
    outtextxy(width / 2 + 200, 625, "2.        ");
    outtextxy(width / 2 + 245, 625, load_name[3]);
    outtextxy(width / 2 + 200, 655, "3.        ");
    outtextxy(width / 2 + 245, 655, load_name[4]);
    outtextxy(width / 2 + 200, 685, "4.        ");
    outtextxy(width / 2 + 245, 685, load_name[5]);
    outtextxy(width / 2 + 200, 715, "5.        ");
    outtextxy(width / 2 + 245, 715, load_name[6]);
    outtextxy(width / 2 + 200, 745, "6.        ");
    outtextxy(width / 2 + 245, 745, load_name[7]);
    outtextxy(width / 2 + 200, 775, "7.        ");
    outtextxy(width / 2 + 245, 775, load_name[8]);
    outtextxy(width / 2 + 200, 805, "8.        ");
    outtextxy(width / 2 + 245, 805, load_name[9]);
    outtextxy(width / 2 + 200, 835, "9.        ");
    outtextxy(width / 2 + 245, 835, load_name[10]);

    settextstyle(8, 0, 15);
}

void Language_menu_start()
{

    int points[8];
    points[0] = width / 2 + 190;
    points[1] = 652;
    points[2] = width / 2 + 190;
    points[3] = 750;
    points[4] = width / 2 + 360;
    points[5] = 750;
    points[6] = width / 2 + 360;
    points[7] = 652;

    rectangle(width / 2 + 190, 652, width / 2 + 360, 750);

    setfillstyle(1, CYAN);
    fillpoly(4, points);

    setcolor(WHITE);
    settextstyle(8, 0, 14);
    outtextxy(width / 2 + 200, 660, "1. ENGLISH");
    outtextxy(width / 2 + 200, 690, "2. ROMANA ");
    outtextxy(width / 2 + 200, 720, "3.FRANCAIS");

    settextstyle(8, 0, 15);
}

void Behind_menu()
{
    int points[8];
    points[0] = width / 2 - 180;
    points[1] = 370;
    points[2] = width / 2 - 180;
    points[3] = 800;
    points[4] = width / 2 + 180;
    points[5] = 800;
    points[6] = width / 2 + 180;
    points[7] = 370;

    rectangle(width / 2 - 180, 370, width / 2 + 180, 800);

    setfillstyle(1, BLACK);
    fillpoly(4, points);

    setcolor(WHITE);
    settextstyle(8, 0, 15);
}

void names()
{

    setcolor(0);
    //setbkcolor(1);
    for (int i = 1000; i <= 1080; i++)
        line(0, i, 1920, i);

    for (int i = 0; i <= 15; i++)
        line(0, i, 1920, i);

    for (int i = 0; i <= 15; i++)
    {
        line(i, 0, i, 1080);
        line(1920 - i, 0, 1920 - i, 1080);
    }

    setcolor(13);
    switch (language)
    {
    case 1:
        outtextxy(width / 2 - strlen("Project made by Rosca Alexandru-David and Tomescu Mircea-Andrei") * 10, 1012, "Project made by Rosca Alexandru-David and Tomescu Mircea-Andrei");
        break;
    case 2:
        outtextxy(width / 2 - strlen("Proiect facut de Rosca Alexandru-David si Tomescu Mircea-Andrei") * 10, 1012, "Proiect facut de Rosca Alexandru-David si Tomescu Mircea-Andrei");
        break;
    case 3:
        outtextxy(width / 2 - strlen("Projet realise par Rosca Alexandru-David et Tomescu Mircea-Andrei") * 10, 1012, "Projet realise par Rosca Alexandru-David et Tomescu Mircea-Andrei");
        break;
    }

    draww = 0;
}

void topper()
{
    settextstyle(8, 0, 18);
    setcolor(13);
    outtextxy(width / 2 - strlen("ELECTRON") * 20, 400, "ELECTRON");
    settextstyle(8, 0, 15);
}

int once = 1;
void Start_Menu()
{
    if (once)
    {
        Behind_menu();
        topper();
        once = 0;
    }

    int x, y;

    if (ismouseclick(WM_LBUTTONDOWN))
    {
        getmouseclick(WM_LBUTTONDOWN, x, y);

        if (x >= width / 2 - 150 && x <= width / 2 + 150 && y >= height / 2 - 25 && y <= height / 2 + 25)
        {
            if (!mute)
                PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
            Menu_Exit = 1;
            Loading_Screen();
            Background_Image();
        }
        else if (x >= width / 2 - 150 && x <= width / 2 + 150 && y >= height / 2 + 50 && y <= height / 2 + 100)
        {
            Load_menu_start();
            if (!mute)
                PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
            int selector = NULL;
            int next_step = 0;
            int good = 0;

            while (selector == NULL && !next_step)                    // cat timp nu am dat click/selectat o comanda
            {
                if (ismouseclick(WM_LBUTTONDOWN))                 // daca dam click
                {
                    getmouseclick(WM_LBUTTONDOWN, x, y);

                    if (x >= width / 2 + 200 && x <= width / 2 + 360 && y >= 565 && y <= 594)
                    {
                        if (!mute)
                            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                        load_position = 1;
                        good = 1;
                    }
                    else if (x >= width / 2 + 200 && x <= width / 2 + 360 && y >= 595 && y <= 624)
                    {
                        if (!mute)
                            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                        load_position = 2;
                        good = 1;
                    }
                    else if (x >= width / 2 + 200 && x <= width / 2 + 360 && y >= 625 && y <= 654)
                    {
                        if (!mute)
                            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                        load_position = 3;
                        good = 1;
                    }
                    else if (x >= width / 2 + 200 && x <= width / 2 + 360 && y >= 655 && y <= 684)
                    {
                        if (!mute)
                            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                        load_position = 4;
                        good = 1;
                    }
                    else if (x >= width / 2 + 200 && x <= width / 2 + 360 && y >= 685 && y <= 714)
                    {
                        if (!mute)
                            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                        load_position = 5;
                        good = 1;
                    }
                    else if (x >= width / 2 + 200 && x <= width / 2 + 360 && y >= 715 && y <= 744)
                    {
                        if (!mute)
                            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                        load_position = 6;
                        good = 1;
                    }
                    else if (x >= width / 2 + 200 && x <= width / 2 + 360 && y >= 745 && y <= 774)
                    {
                        if (!mute)
                            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                        load_position = 7;
                        good = 1;
                    }
                    else if (x >= width / 2 + 200 && x <= width / 2 + 360 && y >= 775 && y <= 804)
                    {
                        if (!mute)
                            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                        load_position = 8;
                        good = 1;
                    }
                    else if (x >= width / 2 + 200 && x <= width / 2 + 360 && y >= 805 && y <= 834)
                    {
                        if (!mute)
                            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                        load_position = 9;
                        good = 1;
                    }
                    else if (x >= width / 2 + 200 && x <= width / 2 + 360 && y >= 835 && y <= 864)
                    {
                        if (!mute)
                            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                        load_position = 10;
                        good = 1;
                    }

                    next_step = 1;
                }
                if (kbhit())                                      // daca dam o tasta
                    selector = getch();
            }

            if (next_step == 0)
                if (selector == '0')
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 1;
                    good = 1;
                }
                else if (selector == '1')
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 2;
                    good = 1;
                }
                else if (selector == '2')
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 3;
                    good = 1;
                }
                else if (selector == '3')
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 4;
                    good = 1;
                }
                else if (selector == '4')
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 5;
                    good = 1;
                }
                else if (selector == '5')
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 6;
                    good = 1;
                }
                else if (selector == '6')
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 7;
                    good = 1;
                }
                else if (selector == '7')
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 8;
                    good = 1;
                }
                else if (selector == '8')
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 9;
                    good = 1;
                }
                else if (selector == '9')
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 10;
                    good = 1;
                }


            Background_Image();
            next_step = 0;
            selector = NULL;

            if (good)
            {
                Load();
                Menu_Exit = 1;
                Loading_Screen();
            }
            Background_Image();

            int x1, y1;

            x1 = mousex();
            y1 = mousey();

            if (x1 >= width / 2 - 150 && x1 <= width / 2 + 150 && y1 >= height / 2 - 25 && y1 <= height / 2 + 25)
                Show_Button = 1;
            else
                Show_Button = 2;
            if (x1 >= width / 2 - 150 && x1 <= width / 2 + 150 && y1 >= height / 2 + 50 && y1 <= height / 2 + 100)
                Show_Button_1 = 1;
            else
                Show_Button_1 = 2;
            if (x1 >= width / 2 - 150 && x1 <= width / 2 + 150 && y1 >= height / 2 + 125 && y1 <= height / 2 + 175)
                Show_Button_2 = 1;
            else
                Show_Button_2 = 2;
            if (x1 >= width / 2 - 150 && x1 <= width / 2 + 150 && y1 >= height / 2 + 200 && y1 <= height / 2 + 250)
                Show_Button_3 = 1;
            else
                Show_Button_3 = 2;

            if (Menu_Exit == 0)
            {
                Behind_menu();
                topper();
            }
            draww = 1;

        }
        else if (x >= width / 2 - 150 && x <= width / 2 + 150 && y >= height / 2 + 125 && y <= height / 2 + 175)
        {
            Language_menu_start();
            if (!mute)
                PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
            int selector = NULL;
            int next_step = 0;
            int good = 0;

            while (selector == NULL && !next_step)                    // cat timp nu am dat click/selectat o comanda
            {
                if (ismouseclick(WM_LBUTTONDOWN))                 // daca dam click
                {
                    getmouseclick(WM_LBUTTONDOWN, x, y);

                    if (x >= width / 2 + 200 && x <= width / 2 + 360 && y >= 660 && y <= 690)
                    {
                        if (!mute)
                            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                        language = 1;
                    }
                    else if (x >= width / 2 + 200 && x <= width / 2 + 360 && y >= 691 && y <= 721)
                    {
                        if (!mute)
                            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                        language = 2;
                    }
                    else if (x >= width / 2 + 200 && x <= width / 2 + 360 && y >= 722 && y <= 752)
                    {
                        if (!mute)
                            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                        language = 3;
                    }


                    next_step = 1;
                }
                if (kbhit())                                      // daca dam o tasta
                    selector = getch();
            }

            if (next_step == 0)

                if (selector == '1')
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 2;
                    language = 1;
                }
                else if (selector == '2')
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    language = 2;
                }
                else if (selector == '3')
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    language = 3;
                }


            Background_Image();
            next_step = 0;
            selector = NULL;

            Background_Image();

            int x1, y1;

            x1 = mousex();
            y1 = mousey();

            if (x1 >= width / 2 - 150 && x1 <= width / 2 + 150 && y1 >= height / 2 - 25 && y1 <= height / 2 + 25)
                Show_Button = 1;
            else
                Show_Button = 2;
            if (x1 >= width / 2 - 150 && x1 <= width / 2 + 150 && y1 >= height / 2 + 50 && y1 <= height / 2 + 100)
                Show_Button_1 = 1;
            else
                Show_Button_1 = 2;
            if (x1 >= width / 2 - 150 && x1 <= width / 2 + 150 && y1 >= height / 2 + 125 && y1 <= height / 2 + 175)
                Show_Button_2 = 1;
            else
                Show_Button_2 = 2;
            if (x1 >= width / 2 - 150 && x1 <= width / 2 + 150 && y1 >= height / 2 + 200 && y1 <= height / 2 + 250)
                Show_Button_3 = 1;
            else
                Show_Button_3 = 2;

            if (Menu_Exit == 0)
            {
                Behind_menu();
                topper();
            }
            draww = 1;
        }
        else if (x >= width / 2 - 150 && x <= width / 2 + 150 && y >= height / 2 + 200 && y <= height / 2 + 250)
        {
            if (!mute)
                PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
            Menu_Exit = 1;
            Background_Image();
            key = 27;
            goto end;
        }

    }

    setcolor(13);

    if (Menu_Exit == 0)
    {

        if (draww)
        {
            names();
        }

        x = mousex();
        y = mousey();

        //////////////////////START BUTTON//////////////////////

        if (x >= width / 2 - 150 && x <= width / 2 + 150 && y >= height / 2 - 25 && y <= height / 2 + 25 && Show_Button == 1)
        {
            if (!mute)
                PlaySound("Sounds\\click.wav", NULL, SND_ASYNC);
            setcolor(13);
            setbkcolor(CYAN);
            Start_Button_Maker(height / 2 - 25, height / 2 + 25, 3);
            switch (language)
            {
            case 1:
                outtextxy(width / 2 - strlen("START") * 10, 510, "START");
                break;
            case 2:
                outtextxy(width / 2 - strlen("START") * 10, 510, "START");
                break;
            case 3:
                outtextxy(width / 2 - strlen("START") * 10, 510, "START");
                break;
            }
            setbkcolor(0);
            Show_Button = 2;
        }
        else if ((x < width / 2 - 150 || x > width / 2 + 150 || y < height / 2 - 25 || y > height / 2 + 25) && Show_Button == 2)
        {
            setbkcolor(0);
            setcolor(13);
            Start_Button_Maker(height / 2 - 25, height / 2 + 25, 0);
            switch (language)
            {
            case 1:
                outtextxy(width / 2 - strlen("START") * 10, 510, "START");
                break;
            case 2:
                outtextxy(width / 2 - strlen("START") * 10, 510, "START");
                break;
            case 3:
                outtextxy(width / 2 - strlen("START") * 10, 510, "START");
                break;
            }
            Show_Button = 1;
        }

        //////////////////////LOAD BUTTON//////////////////////

        if (x >= width / 2 - 150 && x <= width / 2 + 150 && y >= height / 2 + 50 && y <= height / 2 + 100 && Show_Button_1 == 1)
        {
            if (!mute)
                PlaySound("Sounds\\click.wav", NULL, SND_ASYNC);
            setcolor(13);
            setbkcolor(CYAN);
            Start_Button_Maker(height / 2 + 50, height / 2 + 100, 3);
            switch (language)
            {
            case 1:
                outtextxy(width / 2 - strlen("LOAD") * 10, 587, "LOAD");
                break;
            case 2:
                outtextxy(width / 2 - strlen("INCARCA") * 10, 587, "INCARCA");
                break;
            case 3:
                outtextxy(width / 2 - strlen("CHARGE") * 10, 587, "CHARGE");
                break;
            }
            setbkcolor(0);
            Show_Button_1 = 2;
        }
        else if ((x < width / 2 - 150 || x > width / 2 + 150 || y < height / 2 + 50 || y > height / 2 + 100) && Show_Button_1 == 2)
        {
            setbkcolor(0);
            setcolor(13);
            Start_Button_Maker(height / 2 + 50, height / 2 + 100, 0);
            switch (language)
            {
            case 1:
                outtextxy(width / 2 - strlen("LOAD") * 10, 587, "LOAD");
                break;
            case 2:
                outtextxy(width / 2 - strlen("INCARCA") * 10, 587, "INCARCA");
                break;
            case 3:
                outtextxy(width / 2 - strlen("CHARGE") * 10, 587, "CHARGE");
                break;
            }
            Show_Button_1 = 1;

        }

        //////////////////////LANGUAGE BUTTON//////////////////////

        if (x >= width / 2 - 150 && x <= width / 2 + 150 && y >= height / 2 + 125 && y <= height / 2 + 175 && Show_Button_2 == 1)
        {
            if (!mute)
                PlaySound("Sounds\\click.wav", NULL, SND_ASYNC);
            setcolor(13);
            setbkcolor(CYAN);
            Start_Button_Maker(height / 2 + 125, height / 2 + 175, 3);
            switch (language)
            {
            case 1:
                outtextxy(width / 2 - strlen("LANGUAGE") * 10, 664, "LANGUAGE");
                break;
            case 2:
                outtextxy(width / 2 - strlen("LIMBA") * 10, 664, "LIMBA");
                break;
            case 3:
                outtextxy(width / 2 - strlen("LANGUE") * 10, 664, "LANGUE");
                break;
            }
            setbkcolor(0);
            Show_Button_2 = 2;
        }
        else if ((x < width / 2 - 150 || x > width / 2 + 150 || y < height / 2 + 125 || y > height / 2 + 175) && Show_Button_2 == 2)
        {
            setbkcolor(0);
            setcolor(13);
            Start_Button_Maker(height / 2 + 125, height / 2 + 175, 0);
            switch (language)
            {
            case 1:
                outtextxy(width / 2 - strlen("LANGUAGE") * 10, 664, "LANGUAGE");
                break;
            case 2:
                outtextxy(width / 2 - strlen("LIMBA") * 10, 664, "LIMBA");
                break;
            case 3:
                outtextxy(width / 2 - strlen("LANGUE") * 10, 664, "LANGUE");
                break;
            }
            Show_Button_2 = 1;

        }
        //////////////////////EXIT BUTTON//////////////////////

        if (x >= width / 2 - 150 && x <= width / 2 + 150 && y >= height / 2 + 200 && y <= height / 2 + 250 && Show_Button_3 == 1)
        {
            if (!mute)
                PlaySound("Sounds\\click.wav", NULL, SND_ASYNC);
            setcolor(13);
            setbkcolor(CYAN);
            Start_Button_Maker(height / 2 + 200, height / 2 + 250, 3);
            switch (language)
            {
            case 1:
                outtextxy(width / 2 - strlen("EXIT") * 10, 741, "EXIT");
                break;
            case 2:
                outtextxy(width / 2 - strlen("IESI") * 10, 741, "IESI");
                break;
            case 3:
                outtextxy(width / 2 - strlen("LAISSER") * 10, 741, "LAISSER");
                break;
            }
            setbkcolor(0);
            Show_Button_3 = 2;
        }
        else if ((x < width / 2 - 150 || x > width / 2 + 150 || y < height / 2 + 200 || y > height / 2 + 250) && Show_Button_3 == 2)
        {
            setbkcolor(0);
            setcolor(13);
            Start_Button_Maker(height / 2 + 200, height / 2 + 250, 0);
            switch (language)
            {
            case 1:
                outtextxy(width / 2 - strlen("EXIT") * 10, 741, "EXIT");
                break;
            case 2:
                outtextxy(width / 2 - strlen("IESI") * 10, 741, "IESI");
                break;
            case 3:
                outtextxy(width / 2 - strlen("LAISSER") * 10, 741, "LAISSER");
                break;
            }
            Show_Button_3 = 1;

        }
    }
end:
    delay(1);
}

void Controls()
{

    if (kbhit() || key != NULL)
    {

        if (key == NULL)
            key = getch();

        switch (key)
        {

        case 27:                      // ESCAPE KEY
            EXIT = 1;
            break;

        case '+':                      // zoom - in
            if (zoom_level < 10)
            {
                zoom_level++;
                Background_Image();
            }
            break;

        case '-':                      // zoom - out
            if (zoom_level > 3)
            {
                zoom_level--;
                Background_Image();
            }
            break;

        case 'h':                      // load/unload the lines
            if (hidder)
                hidder = 0;
            else
            {
                hidder = 1;
                Background_Image();
            }
            break;

        case 72:
            for (int i = 1; i <= nb_of_piese; i++)
                piese[i].y++;                        // miscam mapa in jos

            Background_Image();
            break;
        case 80:
            for (int i = 1; i <= nb_of_piese; i++)
                piese[i].y--;                        // miscam mapa in sus

            Background_Image();
            break;

        case 77:
            for (int i = 1; i <= nb_of_piese; i++)
                piese[i].x--;                        // miscam mapa in dreapta

            Background_Image();
            break;

        case 75:
            for (int i = 1; i <= nb_of_piese; i++)
                piese[i].x++;                        // miscam mapa in stanga
            Background_Image();
            break;
        case 'r':
            reset();
            Background_Image();
            break;
        case 's':
            menu_selector = 5;
            break;
        case 'l':
            menu_selector = 6;
            break;
        case '1':
            menu_selector = 1;
            break;
        case '2':
            menu_selector = 2;
            break;
        case '3':
            menu_selector = 3;
            break;
        case '4':
            menu_selector = 4;
            break;
        case '5':
            menu_selector = 5;
            break;
        case '6':
            menu_selector = 6;
            break;
        case '7':
            menu_selector = 7;
            break;
        case '8':
            menu_selector = 8;
            break;
        case '9':
            menu_selector = 9;
            break;
        case '0':
            menu_selector = 10;
            break;
        case '`':
            menu_selector = 11;
            break;
        case '\t':
            if (menu_tab_selector == 0 || menu_tab_selector > 11 || timer > 1)
                menu_tab_selector = 1;
            else
                menu_tab_selector++;

            menu_selector = menu_tab_selector;
            timer = 0;
            break;
        }

        draw_menu = 1;
        key = NULL;
        timer++;
    }


}


/////////////////// CONECTAREA ///////////////////

struct nod
{
    int x,y,c;
    nod* urm;
};
struct stiva
{
    nod* prim;
};
void pop(stiva &stac)
{
    nod* prim=stac.prim;
    stac.prim=stac.prim->urm;
    delete prim;
}
void push(stiva &stac,int x,int y,int c)
{
    if(stac.prim==NULL)
    {
        stac.prim=new nod;
        stac.prim->x=x;
        stac.prim->y=y;
        stac.prim->c=c;
        stac.prim->urm=NULL;
    }
    else
    {
        nod* nod_nou=new nod;
        nod_nou->x=x;
        nod_nou->y=y;
        nod_nou->c=c;
        nod_nou->urm=stac.prim;
        stac.prim=nod_nou;
    }
}
int valid(short int v[][400],int val,int i,int j)
{

    if(i<0 or j<0 or i>=400 or j>=400)
        return 0;
    if(v[i][j]!=0)
    {
        if(v[i][j]==-15 or v[i][j]==-16 or v[i][j]==-17)
            if(val<v[i][j])
                return 1;
        return 0;
    }
    return 1;
}

void unire(short int v[][400],stiva &stac,int i,int j,int x2,int y2,int &stop)
{
    int di[]= {0,1,0,-1,0,1,0,-1};
    int dj[]= {1,0,-1,0,1,0,-1,0};
    int l9,c9,c=0;
    //push(stac,i,j,c);
    if(j<x2)
        c=0;
    else if(j>x2)
        c=2;
    else
    {
        if(i<y2)
            c=1;
        else if (i>y2)
            c=3;
    }
    push(stac,i,j,c);
    for(int k=0+c; k<=3+c and stop==0; k++)
    {
        l9=i+di[k];
        c9=j+dj[k];
        if(l9==y2 and c9==x2)
        {
            push(stac,l9,c9,c);
            //draw_line_first(c9,l9,0);
            //draw_line_first(c9,l9,c);
            stop=1;
            while(stac.prim!=NULL)
            {
                if(stac.prim->urm!=NULL)
                {
                    int y1=(stac.prim->y-100)* 10 * zoom_level + 5 * zoom_level;
                    int x1=(stac.prim->x-100)* 10 * zoom_level + 5 * zoom_level;
                    int y2=(stac.prim->urm->y-100)* 10 * zoom_level + 5 * zoom_level;
                    int x2=(stac.prim->urm->x-100)* 10 * zoom_level + 5 * zoom_level;
                    //f(stac.prim->y==stac.prim->urm->y)
                    if(y1<1800 and y2<1800)
                        line(y1,x1,y2,x2);
                }
                pop(stac);
            }
        }
        else if(valid(v,v[i][j]+1,l9,c9)==1)
        {
            v[l9][c9]=v[i][j]+1;
            push(stac,l9,c9,c);
            unire(v,stac,l9,c9,x2,y2,stop);
            if(stop!=1)
                pop(stac);
        }
    }
}

void copiemat(short int v[][400])
{
    for(int i=0; i<400; i++)
        for(int j=0; j<400; j++)
            v[i][j]=matrice_tabla[i][j];
}

void connectare(int x1,int y1,int x2,int y2)
{
    short int v[400][400];
    copiemat(v);
    int stop=0;
    stiva stac;
    stac.prim=NULL;
    v[y1][x1]=1;
    unire(v,stac,y1,x1,x2,y2,stop);
}




/////////////////// COMPONENTS ///////////////////
void draw_linie_stg(int x,int y,int rotation)
{
    x = x * 10 * zoom_level+5*zoom_level;
    y = y * 10 * zoom_level+5*zoom_level;

    int l=5*zoom_level;
    int di[]= {-1,0,1,0};
    int dj[]= {0,1,0,-1};
    line(x+2*l*di[rotation],y+2*l*dj[rotation],x+l*di[rotation],y+l*dj[rotation]);
}

void draw_linie_dr(int x,int y,int rotation)
{
    x = x * 10 * zoom_level + 5 * zoom_level;
    y = y * 10 * zoom_level + 5 * zoom_level;

    int l=5*zoom_level;
    int di[]= {1,0,-1,0};
    int dj[]= {0,-1,0,1};
    line(x+2*l*di[rotation],y+2*l*dj[rotation],x+l*di[rotation],y+l*dj[rotation]);
}
void draw_diode(int x, int y, int rotation)
{
    int l = 5 * zoom_level;
    int h = l * sqrt(3) / 2;
    struct colt_cord
    {
        int x, y;
    } colt[10];

    x = x * 10 * zoom_level + 5 * zoom_level;
    y = y * 10 * zoom_level + 5 * zoom_level;

    colt[1].x = x - 0.5 * h;
    colt[1].y = y - 0.5 * l;

    colt[2].x = x + 0.5 * h;
    colt[2].y = y;

    colt[3].x = x - 0.5 * h;
    colt[3].y = y + 0.5 * l;

    colt[4].x = colt[2].x + 3 * zoom_level;
    colt[4].y = colt[2].y;

    colt[5].x = (colt[1].x + colt[3].x) / 2 - 2.5 * zoom_level;
    colt[5].y = (colt[1].y + colt[3].y) / 2;

    colt[6].x = colt[2].x;
    colt[6].y = colt[2].y - 3 * zoom_level;

    colt[7].x = colt[2].x;
    colt[7].y = colt[2].y + 3 * zoom_level;

    int rotatie = 0;
    for (int i = 1; i <= rotation % 4; i++)
    {
        for (int j = 1; j <= 7; j++)
        {
            colt[j].x = colt[j].x - x;
            colt[j].y = colt[j].y - y;
            int aux = colt[j].x;
            colt[j].x = colt[j].y;
            colt[j].y = -1 * aux;
            colt[j].x = colt[j].x + x;
            colt[j].y = colt[j].y + y;
        }
    }

    //linie colturi 1-2
    line(colt[1].x, colt[1].y, colt[2].x, colt[2].y);
    //linie colturi 2-3
    line(colt[2].x, colt[2].y, colt[3].x, colt[3].y);
    //linie colturi 1-3
    line(colt[1].x, colt[1].y, colt[3].x, colt[3].y);
    //linia din capatul triunghiului
    line(colt[6].x, colt[6].y, colt[7].x, colt[7].y);
    //linia din capatul cu linia la 90 grade
    line(colt[2].x, colt[2].y, colt[4].x, colt[4].y);
    //linie din latura opusa liniei la 90 grade
    line((colt[1].x + colt[3].x) / 2, (colt[1].y + colt[3].y) / 2, colt[5].x, colt[5].y);
}


void draw_tranzistor(int x, int y, int rotation)
{
    int r = 3.5 * zoom_level;
    struct puncte
    {
        int x, y;
    } colt[9];

    x = x * 10 * zoom_level + 5 * zoom_level;
    y = y * 10 * zoom_level + 5 * zoom_level;

    //colt stg linie oblica stg
    colt[1].x = x;
    colt[1].y = y - 0.9 * r;

    //colt linii obl
    colt[2].x = x;
    colt[2].y = y + 0.9 * r;

    //colt dr linie obl dr
    colt[3].x = x - 0.4 * r;
    colt[3].y = y;

    colt[4].x = colt[3].x;
    colt[4].y = y - 0.86 * r;

    colt[5].x = colt[3].x;
    colt[5].y = y + 0.86 * r;

    colt[6].x = colt[3].x - r;
    colt[6].y = y;

    colt[7].x = x;
    colt[7].y = colt[1].y - 0.4 * r;

    colt[8].x = x;
    colt[8].y = colt[2].y + 0.5 * r;

    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 8; j++)
        {
            colt[j].x = colt[j].x - x;
            colt[j].y = colt[j].y - y;
            int aux = colt[j].x;
            colt[j].x = colt[j].y;
            colt[j].y = -1 * aux;
            colt[j].x = colt[j].x + x;
            colt[j].y = colt[j].y + y;
        }
    }


    for (int i = 1; i <= rotation % 4; i++)
    {
        for (int j = 1; j <= 8; j++)
        {
            colt[j].x = colt[j].x - x;
            colt[j].y = colt[j].y - y;
            int aux = colt[j].x;
            colt[j].x = colt[j].y;
            colt[j].y = -1 * aux;
            colt[j].x = colt[j].x + x;
            colt[j].y = colt[j].y + y;
        }
    }

    circle(x, y, r);
    line(colt[1].x, colt[1].y, colt[3].x, colt[3].y);
    line(colt[2].x, colt[2].y, colt[3].x, colt[3].y);
    line(colt[4].x, colt[4].y, colt[5].x, colt[5].y);
    line(colt[3].x, colt[3].y, colt[6].x, colt[6].y);
    line(colt[1].x, colt[1].y, colt[7].x, colt[7].y);
    line(colt[2].x, colt[2].y, colt[8].x, colt[8].y);
}

void draw_ampermetru(int x, int y, int rotation)
{
    struct punct
    {
        int x, y;
    } colt[15];
    int r = 3 * zoom_level;

    x = x * 10 * zoom_level + 5 * zoom_level;
    y = y * 10 * zoom_level + 5 * zoom_level;

    colt[1].x = x - 0.4 * r;
    colt[1].y = y + 0.6 * r;
    colt[2].x = x + 0.4 * r;
    colt[2].y = y + 0.6 * r;

    colt[3].x = x - 0.5 * r;
    colt[3].y = y + 0.82 * r;
    colt[4].x = x + 0.5 * r;
    colt[4].y = y - 0.82 * r;

    colt[5].x = x - r;
    colt[5].y = y;
    colt[6].x = colt[5].x - 0.6 * r;
    colt[6].y = y;

    colt[7].x = x + r;
    colt[7].y = y;
    colt[8].x = colt[7].x + 0.7 * r;
    colt[8].y = y;

    colt[9].x = x;
    colt[9].y = y - 0.5 * r;

    colt[10].x = x - 0.25 * r;
    colt[10].y = y + 0.17 * r;

    colt[11].x = x + 0.25 * r;
    colt[11].y = y + 0.17 * r;;

    for (int i = 1; i <= rotation % 4; i++)
    {
        for (int j = 3; j <= 8; j++)
        {
            colt[j].x = colt[j].x - x;
            colt[j].y = colt[j].y - y;
            int aux = colt[j].x;
            colt[j].x = colt[j].y;
            colt[j].y = -1 * aux;
            colt[j].x = colt[j].x + x;
            colt[j].y = colt[j].y + y;
        }
    }

    circle(x, y, r);

    line(colt[1].x, colt[1].y, colt[9].x, colt[9].y);
    line(colt[2].x, colt[2].y, colt[9].x, colt[9].y);
    line(colt[5].x, colt[5].y, colt[6].x, colt[6].y);
    line(colt[7].x, colt[7].y, colt[8].x, colt[8].y);
    line(colt[10].x, colt[10].y, colt[11].x, colt[11].y);
}

void draw_condenser(int x, int y, int rotation)
{
    struct punct
    {
        int x, y;
    } colt[20];
    int l = 3.5 * zoom_level;

    x = x * 10 * zoom_level + 5 * zoom_level;
    y = y * 10 * zoom_level + 5 * zoom_level;

    //colturi fir borna mare
    colt[1].x = x - 0.5 * l;
    colt[1].y = y;
    colt[2].x = colt[1].x - 0.9 * l;
    colt[2].y = y;

    //colturi fir borna mica
    colt[3].x = x + 0.5 * l;
    colt[3].y = y;
    colt[4].x = colt[3].x + 0.9 * l;
    colt[4].y = y;

    //colturi borna stanga
    colt[5].x = colt[1].x;
    colt[5].y = colt[1].y - 1.3 * l;
    colt[6].x = colt[1].x;
    colt[6].y = colt[1].y + 1.3 * l;

    //colturi borna dreapta
    colt[7].x = colt[3].x;
    colt[7].y = colt[3].y - 1.3 * l;
    colt[8].x = colt[3].x;
    colt[8].y = colt[3].y + 1.3 * l;

    for (int i = 1; i <= rotation % 4; i++)
    {
        for (int j = 1; j <= 8; j++)
        {
            colt[j].x = colt[j].x - x;
            colt[j].y = colt[j].y - y;
            int aux = colt[j].x;
            colt[j].x = colt[j].y;
            colt[j].y = -1 * aux;
            colt[j].x = colt[j].x + x;
            colt[j].y = colt[j].y + y;
        }
    }

    //circle(colt[10].x,colt[10].y,20);
    line(colt[1].x, colt[1].y, colt[2].x, colt[2].y);
    line(colt[3].x, colt[3].y, colt[4].x, colt[4].y);

    if (rotation % 4 == 0)
        for (int i = 0; i <= zoom_level; i++)
        {
            line(colt[5].x + i, colt[5].y, colt[6].x + i, colt[6].y);
            line(colt[7].x - i, colt[7].y, colt[8].x - i, colt[8].y);
        }
    else if (rotation % 4 == 1)
        for (int i = 0; i <= zoom_level; i++)
        {
            line(colt[5].x, colt[5].y - i, colt[6].x, colt[6].y - i);
            line(colt[7].x, colt[7].y + i, colt[8].x, colt[8].y + i);
        }
    else if (rotation % 4 == 2)
        for (int i = 0; i <= zoom_level; i++)
        {
            line(colt[5].x - i, colt[5].y, colt[6].x - i, colt[6].y);
            line(colt[7].x + i, colt[7].y, colt[8].x + i, colt[8].y);
        }
    else if (rotation % 4 == 3)
        for (int i = 0; i <= zoom_level; i++)
        {
            line(colt[5].x, colt[5].y + i, colt[6].x, colt[6].y + i);
            line(colt[7].x, colt[7].y - i, colt[8].x, colt[8].y - i);
        }
}

void draw_ground(int x, int y, int rotation)
{
    struct punct
    {
        int x, y;
    } colt[10];
    int l = zoom_level * 3.5;


    x = x * 10 * zoom_level + 5 * zoom_level;
    y = y * 10 * zoom_level + 5 * zoom_level;

    colt[1].x = x;
    colt[1].y = y + 5;

    colt[2].x = colt[1].x;
    colt[2].y = colt[1].y - 1.5 * l;

    colt[3].x = colt[1].x - l;
    colt[3].y = colt[1].y;

    colt[4].x = colt[1].x + l;
    colt[4].y = colt[1].y;

    colt[5].x = colt[1].x - 0.75 * l;
    colt[5].y = colt[1].y + 0.25 * l;

    colt[6].x = colt[1].x + 0.75 * l;
    colt[6].y = colt[1].y + 0.25 * l;

    colt[7].x = colt[1].x - 0.5 * l;
    colt[7].y = colt[1].y + 0.5 * l;

    colt[8].x = colt[1].x + 0.5 * l;
    colt[8].y = colt[1].y + 0.5 * l;

    for (int i = 1; i <= rotation % 4; i++)
    {
        for (int j = 1; j <= 8; j++)
        {
            colt[j].x = colt[j].x - x;
            colt[j].y = colt[j].y - y;
            int aux = colt[j].x;
            colt[j].x = colt[j].y;
            colt[j].y = -1 * aux;
            colt[j].x = colt[j].x + x;
            colt[j].y = colt[j].y + y;
        }
    }
    for (int i = 2; i <= 8; i = i + 2)
        line(colt[i].x, colt[i].y, colt[i - 1].x, colt[i - 1].y);

}

void draw_lamp(int x, int y, int rotation)
{
    struct punct
    {
        int x, y;
    } colt[10];
    int r = 2.5 * zoom_level;

    x = x * 10 * zoom_level + 5 * zoom_level;
    y = y * 10 * zoom_level + 5 * zoom_level;

    colt[1].x = x - 0.5 * r;
    colt[1].y = y - 0.82 * r;
    colt[2].x = x + 0.5 * r;
    colt[2].y = y + 0.82 * r;

    colt[3].x = x - 0.5 * r;
    colt[3].y = y + 0.82 * r;
    colt[4].x = x + 0.5 * r;
    colt[4].y = y - 0.82 * r;

    colt[5].x = x - r;
    colt[5].y = y;
    colt[6].x = colt[5].x - r;
    colt[6].y = y;

    colt[7].x = x + r;
    colt[7].y = y;
    colt[8].x = colt[7].x + r;
    colt[8].y = y;

    for (int i = 1; i <= rotation % 4; i++)
    {
        for (int j = 1; j <= 8; j++)
        {
            colt[j].x = colt[j].x - x;
            colt[j].y = colt[j].y - y;
            int aux = colt[j].x;
            colt[j].x = colt[j].y;
            colt[j].y = -1 * aux;
            colt[j].x = colt[j].x + x;
            colt[j].y = colt[j].y + y;
        }
    }

    circle(x, y, r);
    line(colt[1].x, colt[1].y, colt[2].x, colt[2].y);
    line(colt[3].x, colt[3].y, colt[4].x, colt[4].y);
    line(colt[5].x, colt[5].y, colt[6].x, colt[6].y);
    line(colt[7].x, colt[7].y, colt[8].x, colt[8].y);
}

void draw_potentiometer(int x, int y, int rotation)
{
    struct punct
    {
        int x, y;
    } colt[15];
    int l = zoom_level * 2;

    x = x * 10 * zoom_level + 5 * zoom_level;
    y = y * 10 * zoom_level + 5 * zoom_level;

    colt[1].x = x - 1.5 * l;
    colt[1].y = y - 0.5 * l;

    colt[2].x = x + 1.5 * l;
    colt[2].y = y - 0.5 * l;

    colt[3].x = x + 1.5 * l;
    colt[3].y = y + 0.5 * l;

    colt[4].x = x - 1.5 * l;
    colt[4].y = y + 0.5 * l;

    colt[5].x = (colt[1].x + colt[4].x) / 2;
    colt[5].y = y;

    colt[6].x = colt[5].x - l;
    colt[6].y = y;

    colt[7].x = (colt[2].x + colt[3].x) / 2;
    colt[7].y = y;

    colt[8].x = colt[7].x + l;
    colt[8].y = y;

    colt[9].x = x;
    colt[9].y = y - 0.5 * l;

    colt[10].x = colt[9].x - 0.2 * l;
    colt[10].y = colt[9].y - 0.2 * l;

    colt[11].x = colt[9].x + 0.2 * l;
    colt[11].y = colt[9].y - 0.2 * l;

    colt[12].x = colt[9].x;
    colt[12].y = colt[9].y - 1.8*l;

    for (int i = 1; i <= rotation % 4; i++)
    {
        for (int j = 1; j <= 13; j++)
        {
            colt[j].x = colt[j].x - x;
            colt[j].y = colt[j].y - y;
            int aux = colt[j].x;
            colt[j].x = colt[j].y;
            colt[j].y = -1 * aux;
            colt[j].x = colt[j].x + x;
            colt[j].y = colt[j].y + y;
        }
    }
    for (int i = 2; i <= 4; i++)
        line(colt[i].x, colt[i].y, colt[i - 1].x, colt[i - 1].y);

    line(colt[5].x, colt[5].y, colt[6].x, colt[6].y);
    line(colt[7].x, colt[7].y, colt[8].x, colt[8].y);
    line(colt[1].x, colt[1].y, colt[4].x, colt[4].y);
    line(colt[9].x, colt[9].y, colt[10].x, colt[10].y);
    line(colt[9].x, colt[9].y, colt[11].x, colt[11].y);
    line(colt[9].x, colt[9].y, colt[12].x, colt[12].y);
}

void draw_power_source(int x, int y, int rotation)
{
    struct punct
    {
        int x, y;
    } colt[20];
    int l = 2 * zoom_level;

    x = x * 10 * zoom_level + 5 * zoom_level;
    y = y * 10 * zoom_level + 5 * zoom_level;

    //colturi fir borna mare
    colt[1].x = x - 0.5 * l;
    colt[1].y = y;
    colt[2].x = colt[1].x - 2 * l;
    colt[2].y = y;

    //colturi fir borna mica
    colt[3].x = x + 0.5 * l;
    colt[3].y = y;
    colt[4].x = colt[3].x + 2 * l;
    colt[4].y = y;

    //colturi borna mare
    colt[5].x = colt[1].x;
    colt[5].y = colt[1].y - 1.5 * l;
    colt[6].x = colt[1].x;
    colt[6].y = colt[1].y + 1.5 * l;

    //colturi borna mica
    colt[7].x = colt[3].x;
    colt[7].y = colt[3].y - 0.5 * l;
    colt[8].x = colt[3].x;
    colt[8].y = colt[3].y + 0.5 * l;

    //colturi plus
    colt[9].x = colt[5].x - 0.2 * l;
    colt[9].y = colt[5].y;
    colt[10].x = colt[5].x - 0.6 * l;
    colt[10].y = colt[5].y;
    colt[11].x = colt[5].x - 0.4 * l;
    colt[11].y = colt[5].y - 0.18 * l;
    colt[12].x = colt[5].x - 0.4 * l;
    colt[12].y = colt[5].y + 0.18 * l;

    //colturi minus
    colt[13].x = colt[7].x + 0.2 * l;
    colt[13].y = colt[7].y;
    colt[14].x = colt[13].x + 0.4 * l;
    colt[14].y = colt[13].y;

    for (int i = 1; i <= rotation % 4; i++)
    {
        for (int j = 1; j <= 14; j++)
        {
            colt[j].x = colt[j].x - x;
            colt[j].y = colt[j].y - y;
            int aux = colt[j].x;
            colt[j].x = colt[j].y;
            colt[j].y = -1 * aux;
            colt[j].x = colt[j].x + x;
            colt[j].y = colt[j].y + y;
        }
    }

    //circle(colt[10].x,colt[10].y,20);
    line(colt[1].x, colt[1].y, colt[2].x, colt[2].y);
    line(colt[3].x, colt[3].y, colt[4].x, colt[4].y);
    line(colt[5].x, colt[5].y, colt[6].x, colt[6].y);
    line(colt[7].x, colt[7].y, colt[8].x, colt[8].y);
    line(colt[9].x, colt[9].y, colt[10].x, colt[10].y);
    line(colt[11].x, colt[11].y, colt[12].x, colt[12].y);
    line(colt[13].x, colt[13].y, colt[14].x, colt[14].y);
}

void draw_resistor(int x, int y, int rotation)
{
    struct punct
    {
        int x, y;
    } colt[10];
    int l = zoom_level * 2;

    x = x * 10 * zoom_level + 5 * zoom_level;
    y = y * 10 * zoom_level + 5 * zoom_level;

    colt[1].x = x - 1.5 * l;
    colt[1].y = y - 0.5 * l;

    colt[2].x = x + 1.5 * l;
    colt[2].y = y - 0.5 * l;

    colt[3].x = x + 1.5 * l;
    colt[3].y = y + 0.5 * l;

    colt[4].x = x - 1.5 * l;
    colt[4].y = y + 0.5 * l;

    colt[5].x = (colt[1].x + colt[4].x) / 2;
    colt[5].y = y;

    colt[6].x = colt[5].x - l;
    colt[6].y = y;

    colt[7].x = (colt[2].x + colt[3].x) / 2;
    colt[7].y = y;

    colt[8].x = colt[7].x + l;
    colt[8].y = y;

    for (int i = 1; i <= rotation % 4; i++)
    {
        for (int j = 1; j <= 8; j++)
        {
            colt[j].x = colt[j].x - x;
            colt[j].y = colt[j].y - y;
            int aux = colt[j].x;
            colt[j].x = colt[j].y;
            colt[j].y = -1 * aux;
            colt[j].x = colt[j].x + x;
            colt[j].y = colt[j].y + y;
        }
    }
    for (int i = 2; i <= 4; i++)
        line(colt[i].x, colt[i].y, colt[i - 1].x, colt[i - 1].y);

    line(colt[5].x, colt[5].y, colt[6].x, colt[6].y);
    line(colt[7].x, colt[7].y, colt[8].x, colt[8].y);
    line(colt[1].x, colt[1].y, colt[4].x, colt[4].y);
}

void draw_switch(int x, int y, int rotation,int stare)
{
    struct punct
    {
        int x, y;
    } colt[20];
    int l = 2 * zoom_level;

    x = x * 10 * zoom_level + 5 * zoom_level;
    y = y * 10 * zoom_level + 5 * zoom_level;
    if(stare==0)
    {
        //colturi fir borna mare
        colt[1].x = x - l;
        colt[1].y = y;
        colt[2].x = colt[1].x - 1.3 * l;
        colt[2].y = y;

        //colturi fir borna mica
        colt[3].x = x + 0.5 * l;
        colt[3].y = y;
        colt[4].x = colt[3].x + 2 * l;
        colt[4].y = y;

        colt[5].x = colt[1].x;
        colt[5].y = colt[1].y;

        colt[6].x = colt[3].x;
        colt[6].y = colt[3].y - 0.7 * l;

        for (int i = 1; i <= rotation % 4; i++)
        {
            for (int j = 1; j <= 6; j++)
            {
                colt[j].x = colt[j].x - x;
                colt[j].y = colt[j].y - y;
                int aux = colt[j].x;
                colt[j].x = colt[j].y;
                colt[j].y = -1 * aux;
                colt[j].x = colt[j].x + x;
                colt[j].y = colt[j].y + y;
            }
        }

        line(colt[1].x, colt[1].y, colt[2].x, colt[2].y);
        line(colt[3].x, colt[3].y, colt[4].x, colt[4].y);
        line(colt[5].x, colt[5].y, colt[6].x, colt[6].y);
    }
    else
    {
        l=5*zoom_level;

        //colturi fir borna mare
        colt[1].x = x;
        colt[1].y = y-2;
        colt[2].x = colt[1].x - l;
        colt[2].y = y-2;

        //colturi fir borna mica
        colt[3].x = x;
        colt[3].y = y-2;
        colt[4].x = colt[3].x+l;
        colt[4].y = y-2;

        for (int i = 1; i <= rotation % 4; i++)
        {
            for (int j = 1; j <= 4; j++)
            {
                colt[j].x = colt[j].x - x;
                colt[j].y = colt[j].y - y;
                int aux = colt[j].x;
                colt[j].x = colt[j].y;
                colt[j].y = -1 * aux;
                colt[j].x = colt[j].x + x;
                colt[j].y = colt[j].y + y;
            }
        }
        for(int i=0; i<=4; i++)
        {
            line(colt[1].x, colt[1].y+i, colt[2].x, colt[2].y+i);
            line(colt[3].x, colt[3].y+i, colt[4].x, colt[4].y+i);
        }
    }
}

void draw_voltmetru(int x, int y, int rotation)
{
    struct punct
    {
        int x, y;
    } colt[10];
    int r = 2.5 * zoom_level;

    x = x * 10 * zoom_level + 5 * zoom_level;
    y = y * 10 * zoom_level + 5 * zoom_level;

    colt[1].x = x - 0.4 * r;
    colt[1].y = y - 0.6 * r;
    colt[2].x = x + 0.4 * r;
    colt[2].y = y - 0.6 * r;

    colt[3].x = x - 0.5 * r;
    colt[3].y = y + 0.82 * r;
    colt[4].x = x + 0.5 * r;
    colt[4].y = y - 0.82 * r;

    colt[5].x = x - 0.9 * r;
    colt[5].y = y;
    colt[6].x = colt[5].x - r;
    colt[6].y = y;

    colt[7].x = x + r;
    colt[7].y = y;
    colt[8].x = colt[7].x + r;
    colt[8].y = y;

    colt[9].x = x;
    colt[9].y = y + 0.5 * r;

    for (int i = 1; i <= rotation % 4; i++)
    {
        for (int j = 3; j <= 8; j++)
        {
            colt[j].x = colt[j].x - x;
            colt[j].y = colt[j].y - y;
            int aux = colt[j].x;
            colt[j].x = colt[j].y;
            colt[j].y = -1 * aux;
            colt[j].x = colt[j].x + x;
            colt[j].y = colt[j].y + y;
        }
    }

    circle(x, y, r);

    line(colt[1].x, colt[1].y, colt[9].x, colt[9].y);
    line(colt[2].x, colt[2].y, colt[9].x, colt[9].y);
    line(colt[5].x, colt[5].y, colt[6].x, colt[6].y);
    line(colt[7].x, colt[7].y, colt[8].x, colt[8].y);
}


//am facut fisier cu functiile de desenare

/////////////////// LIST OF BUTTONS ///////////////////

void Help_button()
{
    setcolor(font_color);

    line(1800, 1005, 1920, 1005);
    line(1800, 1054, 1920, 1054);
    line(1917, 1005, 1917, 1055);
    line(1800, 1005, 1800, 1055);

    switch (language)
    {
    case 1:
        outtextxy(1820, 1015, "HELP");
        break;
    case 2:
        outtextxy(1810, 1015, "AJUTA");
        break;
    case 3:
        outtextxy(1820, 1015, "AIDE");
        break;
    }

    setcolor(BLACK);

}

void Exit_Button()
{
    setcolor(font_color);

    for (int k = 2; k <= 5; k++)
        line(1800, k, 1920, k);
    line(1800, 54, 1920, 54);
    line(1917, 5, 1917, 54);
    line(1800, 5, 1800, 54);

    switch (language)
    {
    case 1:
        outtextxy(1820, 15, "EXIT");
        break;
    case 2:
        outtextxy(1820, 15, "IESI");
        break;
    case 3:
        outtextxy(1820, 15, "QUIT");
        break;
    }


    setcolor(BLACK);

}

void Theme_Button()
{
    setcolor(font_color);

    line(1800, 56, 1920, 56);
    line(1800, 105, 1920, 105);
    line(1917, 56, 1917, 105);
    line(1800, 56, 1800, 105);

    switch (language)
    {
    case 1:
        outtextxy(1810, 66, "THEME");
        break;
    case 2:
        outtextxy(1820, 66, "TEMA");
        break;
    case 3:
        outtextxy(1810, 66, "THEME");
        break;
    }
    setcolor(BLACK);
}

void Background_Button()
{
    font_color=8;
    setcolor(font_color);

    line(1800, 107, 1920, 107);
    line(1800, 156, 1920, 156);
    line(1917, 107, 1917, 156);
    line(1800, 107, 1800, 156);

    switch (language)
    {
    case 1:
        outtextxy(1810, 117, "SCENE");
        break;
    case 2:
        outtextxy(1810, 117, "SCENA");
        break;
    case 3:
        outtextxy(1810, 117, "SCENE");
        break;
    }
    setcolor(BLACK);
}

void Parts_Button()
{
    setcolor(font_color);

    line(1800, 158, 1920, 158);
    line(1800, 207, 1920, 207);
    line(1917, 158, 1917, 207);
    line(1800, 158, 1800, 207);

    switch (language)
    {
    case 1:
        outtextxy(1810, 168, "PARTS");
        break;
    case 2:
        outtextxy(1810, 168, "PIESE");
        break;
    case 3:
        outtextxy(1810, 168, "PIECE");
        break;
    }
    setcolor(BLACK);
}

void Save_Button()
{
    setcolor(font_color);

    line(1800, 209, 1920, 209);
    line(1800, 258, 1920, 258);
    line(1917, 209, 1917, 258);
    line(1800, 209, 1800, 258);

    switch (language)
    {
    case 1:
        outtextxy(1820, 219, "SAVE");
        break;
    case 2:
        outtextxy(1810, 219, "SCRIE");
        break;
    case 3:
        outtextxy(1810, 219, "SAUVE");
        break;
    }
    setcolor(BLACK);
}

void Load_Button()
{
    setcolor(font_color);

    line(1800, 260, 1920, 260);
    line(1800, 309, 1920, 309);
    line(1917, 260, 1917, 309);
    line(1800, 260, 1800, 309);

    switch (language)
    {
    case 1:
        outtextxy(1820, 270, "LOAD");
        break;
    case 2:
        outtextxy(1810, 270, "CAUTA");
        break;
    case 3:
        outtextxy(1810, 270, "CHARG");
        break;
    }
    setcolor(BLACK);
}

void Mute_Button()
{
    setcolor(font_color);

    line(1800, 311, 1920, 311);
    line(1800, 360, 1920, 360);
    line(1917, 311, 1917, 360);
    line(1800, 311, 1800, 360);

    switch (language)
    {
    case 1:
        outtextxy(1820, 321, "MUTE");
        break;
    case 2:
        outtextxy(1820, 321, "MUTE");
        break;
    case 3:
        outtextxy(1810, 321, "MUTER");
        break;
    }
    setcolor(BLACK);
}

void Hide_Button()
{
    setcolor(font_color);

    line(1800, 362, 1920, 362);
    line(1800, 411, 1920, 411);
    line(1917, 362, 1917, 411);
    line(1800, 362, 1800, 411);

    switch (language)
    {
    case 1:
        outtextxy(1820, 372, "GRID");
        break;
    case 2:
        outtextxy(1810, 372, "GRILA");
        break;
    case 3:
        outtextxy(1810, 372, "GRILE");
        break;
    }
    setcolor(BLACK);
}

void Zoom_Button()
{
    setcolor(font_color);

    line(1800, 413, 1920, 413);
    line(1800, 462, 1920, 462);
    line(1917, 413, 1917, 462);
    line(1800, 413, 1800, 463);

    switch (language)
    {
    case 1:
        outtextxy(1820, 423, "ZOOM");
        break;
    case 2:
        outtextxy(1820, 423, "ZOOM");
        break;
    case 3:
        outtextxy(1820, 423, "ZOOM");
        break;
    }
    setcolor(BLACK);
}

void Language_Button()
{
    setcolor(font_color);

    line(1800, 464, 1920, 464);
    line(1800, 513, 1920, 513);
    line(1917, 464, 1917, 513);
    line(1800, 464, 1800, 513);

    switch (language)
    {
    case 1:
        outtextxy(1820, 474, "LANG");
        break;
    case 2:
        outtextxy(1810, 474, "LIMBA");
        break;
    case 3:
        outtextxy(1820, 474, "LANG");
        break;
    }
    setcolor(BLACK);
}

/////////////////// BUTTON MENU ///////////////////

void Help_menu()
{
    setcolor(WHITE);
    settextstyle(8, 0, 13);
    switch (language)
    {
    case 1:
        outtextxy(1592, 878, "1. s : Save      ");
        outtextxy(1592, 900, "2. l : Load      ");
        outtextxy(1592, 922, "3. r : Reset     ");
        outtextxy(1592, 944, "4. + : Zoom-in   ");
        outtextxy(1592, 966, "5. - : Zoom-out  ");
        outtextxy(1592, 988, "6. h : Hide map  ");
        outtextxy(1592, 1010, "7. Escape : Exit ");
        outtextxy(1592, 1032, "Arrows : Movement");
        break;
    case 2:
        outtextxy(1592, 878, "1. s : Salveaza  ");
        outtextxy(1592, 900, "2. l : Incarca   ");
        outtextxy(1592, 922, "3. r : Reseteaza ");
        outtextxy(1592, 944, "4. + : Mareste   ");
        outtextxy(1592, 966, "5. - : Micsoreaza");
        outtextxy(1592, 988, "6. h : Ascunde   ");
        outtextxy(1592, 1010, "7. Escape : Iesi ");
        outtextxy(1592, 1032, "Sageti : Miscare ");
        break;
    case 3:
        outtextxy(1592, 878, "1. s : Sauver    ");
        outtextxy(1592, 900, "2. l : Charge    ");
        outtextxy(1592, 922, "3. r : Reset     ");
        outtextxy(1592, 944, "4. + : Zoom-in   ");
        outtextxy(1592, 966, "5. - : Zoom-out  ");
        outtextxy(1592, 988, "6. h : Cacher    ");
        outtextxy(1592, 1010, "7. Escape : Quit ");
        outtextxy(1592, 1032, "Fleche : Movement");
        break;
    }
    settextstyle(8, 0, 15);
}

void Exit_menu()
{
    setcolor(WHITE);
    settextstyle(8, 0, 14);
    switch (language)
    {
    case 1:
        outtextxy(1705, 10, "1. YES");
        outtextxy(1705, 40, "2. NO ");
        break;
    case 2:
        outtextxy(1705, 10, "1. DA ");
        outtextxy(1705, 40, "2. NU ");
        break;
    case 3:
        outtextxy(1705, 10, "1. OUI");
        outtextxy(1705, 40, "2. NON");
        break;
    }
    settextstyle(8, 0, 15);
}

void Theme_menu()
{
    setcolor(WHITE);
    settextstyle(8, 0, 14);
    switch (language)
    {
    case 1:
        outtextxy(1660, 70, "1. BLUE  ");
        outtextxy(1660, 100, "2. RED   ");
        outtextxy(1660, 130, "3. GREEN ");
        outtextxy(1660, 160, "4. YELLOW");
        outtextxy(1660, 190, "5. PINK  ");
        outtextxy(1660, 220, "6. WHITE ");
        break;
    case 2:
        outtextxy(1660, 70, "1. CYAN  ");
        outtextxy(1660, 100, "2. ROSU  ");
        outtextxy(1660, 130, "3. VERDE ");
        outtextxy(1660, 160, "4. GALBEN");
        outtextxy(1660, 190, "5. ROZ   ");
        outtextxy(1660, 220, "6. ALB   ");
        break;
    case 3:
        outtextxy(1660, 70, "1. BLEU  ");
        outtextxy(1660, 100, "2. ROUGE ");
        outtextxy(1660, 130, "3. VERT  ");
        outtextxy(1660, 160, "4. JAUNE ");
        outtextxy(1660, 190, "5. ROSE  ");
        outtextxy(1660, 220, "6. BLANC ");
        break;
    }
    settextstyle(8, 0, 15);
}

void Background_menu()
{
    setcolor(WHITE);
    settextstyle(8, 0, 14);
    outtextxy(1630, 113, "1. AKSHAN  ");
    outtextxy(1630, 143, "2. DIANA   ");
    outtextxy(1630, 173, "3. EVELYNN ");
    outtextxy(1630, 203, "4. PYKE    ");
    outtextxy(1630, 233, "5. AKSHAN  ");
    outtextxy(1630, 263, "6. AATROX  ");
    settextstyle(8, 0, 15);
}

void Parts_menu()
{
    setcolor(WHITE);
    settextstyle(8, 0, 14);
    switch (language)
    {
    case 1:
        outtextxy(1540, 158, "1.  TRANSISTOR   ");
        outtextxy(1540, 188, "2.  DIODE        ");
        outtextxy(1540, 218, "3.  AMPERMETER   ");
        outtextxy(1540, 248, "4.  CAPACITOR    ");
        outtextxy(1540, 278, "5.  GROUND       ");
        outtextxy(1540, 308, "6.  CONSUMER     ");
        outtextxy(1540, 338, "7.  POTENTIOMETER");
        outtextxy(1540, 368, "8.  POWER SUPPLY ");
        outtextxy(1540, 398, "9.  SWITCH       ");
        outtextxy(1540, 428, "0.  VOLTMETER    ");
        outtextxy(1540, 458, "-.  RESISTOR     ");
        break;
    case 2:
        outtextxy(1540, 158, "1.  TRANZISTOR   ");
        outtextxy(1540, 188, "2.  DIODA        ");
        outtextxy(1540, 218, "3.  AMPERMETRU   ");
        outtextxy(1540, 248, "4.  CAPACITOR    ");
        outtextxy(1540, 278, "5.  IMPAMANTARE  ");
        outtextxy(1540, 308, "6.  CONSUMATOR   ");
        outtextxy(1540, 338, "7.  POTENTIOMETRU");
        outtextxy(1540, 368, "8.  SURSA ENERGIE");
        outtextxy(1540, 398, "9.  INTRERUPATOR ");
        outtextxy(1540, 428, "0.  VOLTMETRU    ");
        outtextxy(1540, 458, "-.  REZISTOR     ");
        break;
    case 3:
        outtextxy(1540, 158, "1.  TRANSISTOR   ");
        outtextxy(1540, 188, "2.  DIODE        ");
        outtextxy(1540, 218, "3.  AMPEREMETRE  ");
        outtextxy(1540, 248, "4.  CONDENSATEUR ");
        outtextxy(1540, 278, "5.  MASSSE       ");
        outtextxy(1540, 308, "6.  CONSOMMATEUR ");
        outtextxy(1540, 338, "7.  POTENTIOMETRE");
        outtextxy(1540, 368, "8.  ALIMENTATION ");
        outtextxy(1540, 398, "9.  COMMUTATEUR  ");
        outtextxy(1540, 428, "0.  VOLTMETRE    ");
        outtextxy(1540, 458, "-.  RESISTANCE   ");
        break;
    }

    settextstyle(8, 0, 15);
}

void Save_menu()
{
    setcolor(WHITE);
    settextstyle(8, 0, 14);
    outtextxy(1645, 215, "0.        ");
    outtextxy(1690, 215, load_name[1]);
    outtextxy(1645, 245, "1.        ");
    outtextxy(1690, 245, load_name[2]);
    outtextxy(1645, 275, "2.        ");
    outtextxy(1690, 275, load_name[3]);
    outtextxy(1645, 305, "3.        ");
    outtextxy(1690, 305, load_name[4]);
    outtextxy(1645, 335, "4.        ");
    outtextxy(1690, 335, load_name[5]);
    outtextxy(1645, 365, "5.        ");
    outtextxy(1690, 365, load_name[6]);
    outtextxy(1645, 395, "6.        ");
    outtextxy(1690, 395, load_name[7]);
    outtextxy(1645, 425, "7.        ");
    outtextxy(1690, 425, load_name[8]);
    outtextxy(1645, 455, "8.        ");
    outtextxy(1690, 455, load_name[9]);
    outtextxy(1645, 485, "9.        ");
    outtextxy(1690, 485, load_name[10]);

    settextstyle(8, 0, 15);
}

void Load_menu()
{
    setcolor(WHITE);
    settextstyle(8, 0, 14);
    outtextxy(1645, 265, "0.        ");
    outtextxy(1690, 265, load_name[1]);
    outtextxy(1645, 295, "1.        ");
    outtextxy(1690, 295, load_name[2]);
    outtextxy(1645, 325, "2.        ");
    outtextxy(1690, 325, load_name[3]);
    outtextxy(1645, 355, "3.        ");
    outtextxy(1690, 355, load_name[4]);
    outtextxy(1645, 385, "4.        ");
    outtextxy(1690, 385, load_name[5]);
    outtextxy(1645, 415, "5.        ");
    outtextxy(1690, 415, load_name[6]);
    outtextxy(1645, 445, "6.        ");
    outtextxy(1690, 445, load_name[7]);
    outtextxy(1645, 475, "7.        ");
    outtextxy(1690, 475, load_name[8]);
    outtextxy(1645, 505, "8.        ");
    outtextxy(1690, 505, load_name[9]);
    outtextxy(1645, 535, "9.        ");
    outtextxy(1690, 535, load_name[10]);

    settextstyle(8, 0, 15);
}

void Mute_menu()
{
    setcolor(WHITE);
    settextstyle(8, 0, 14);
    switch (language)
    {
    case 1:
        outtextxy(1630, 317, "1.MUTED    ");
        outtextxy(1630, 347, "2.NOT MUTED");
        break;
    case 2:
        outtextxy(1630, 317, "1.SILENTIOS");
        outtextxy(1630, 347, "2.SUNET    ");
        break;
    case 3:
        outtextxy(1630, 317, "1.COUPE    ");
        outtextxy(1630, 347, "2.NOT COUPE");
        break;
    }

    settextstyle(8, 0, 15);
}

void Hide_menu()
{
    setcolor(WHITE);
    settextstyle(8, 0, 14);
    switch (language)
    {
    case 1:
        outtextxy(1675, 367, "1. HIDE ");
        outtextxy(1675, 397, "2. SHOW ");
        break;
    case 2:
        outtextxy(1675, 367, "1.ASCUND");
        outtextxy(1675, 397, "2. ARATA");
        break;
    case 3:
        outtextxy(1675, 367, "1.CACHER");
        outtextxy(1675, 397, "2.MONTRE");
        break;
    }

    settextstyle(8, 0, 15);
}

void Zoom_menu()
{
    setcolor(WHITE);
    settextstyle(8, 0, 14);

    switch (language)
    {
    case 1:
        outtextxy(1615, 418, "1. ZOOM-IN  ");
        outtextxy(1615, 448, "2. ZOOM-OUT ");
        break;
    case 2:
        outtextxy(1615, 418, "1. MARESTE  ");
        outtextxy(1615, 448, "2.MICSOREAZA");
        break;
    case 3:
        outtextxy(1615, 418, "1. ZOOM-IN  ");
        outtextxy(1615, 448, "2. ZOOM-OUT ");
        break;
    }

    settextstyle(8, 0, 15);
}

void Language_menu()
{
    setcolor(WHITE);
    settextstyle(8, 0, 14);

    outtextxy(1630, 469, "1. ENGLISH ");
    outtextxy(1630, 499, "2. ROMANA  ");
    outtextxy(1630, 529, "3. FRANCAIS");

    settextstyle(8, 0, 15);
}

void Individual_part_menu(int x1, int y1, int type)
{
    setcolor(WHITE);
    settextstyle(8, 0, 13);
    switch (language)
    {
    case 1:
        outtextxy(x1 + 5, y1 + 5, "1. CONNECT");
        outtextxy(x1 + 5, y1 + 30, "2. ROTATE ");
        outtextxy(x1 + 5, y1 + 55, "3. REMOVE ");
        outtextxy(x1 + 5, y1 + 80, "4.DEL WIRE");
        if(type == 9)
            outtextxy(x1 + 5, y1 + 105,"5. ON/OFF ");
        break;
    case 2:
        outtextxy(x1 + 5, y1 + 5, "1. LEAGA  ");
        outtextxy(x1 + 5, y1 + 30, "2. ROTESTE");
        outtextxy(x1 + 5, y1 + 55, "3. STERGE ");
        outtextxy(x1 + 5, y1 + 80, "4.TAIE FIR");
        if(type == 9)
            outtextxy(x1 + 5, y1 + 105,"5. ON/OFF ");
        break;
    case 3:
        outtextxy(x1 + 5, y1 + 5, "1. RELIER ");
        outtextxy(x1 + 5, y1 + 30, "2. TOURNER");
        outtextxy(x1 + 5, y1 + 55, "3. RETIER ");
        outtextxy(x1 + 5, y1 + 80, "4.DEL WIRE");
        if(type == 9)
            outtextxy(x1 + 5, y1 + 105,"5. ON/OFF ");
        break;
    }
    settextstyle(8, 0, 15);
}

/////////////////// MENU BAR (RIGHT SIDE BAR) ///////////////////

void Menu()
{
    setlinestyle(0, 0, 2);        // Makes the outline of the menu boxes thicker

    if (draw_menu)   // daca nu dam hover peste un buton si trebuie sa desenam meniul
    {
        int p[8];
        setfillstyle(SOLID_FILL, BLACK);
        p[0] = 1800;
        p[1] = 0;
        p[2] = 1800;
        p[3] = 1055;
        p[4] = 1920;
        p[5] = 1055;
        p[6] = 1920;
        p[7] = 0;
        fillpoly(4, p);
        draw_menu = 0;
    }


    setcolor(WHITE);
    line(1800, 514, 1800, 1004);
    //line(1917, 514, 1917, 1004);


    if (hover_tab == 2)
    {
        bkcolor();
        fontcolor();
    }
    else
        font_color = 15;

    Exit_Button();
    setbkcolor(0);

    ///////////////////

    if (hover_tab == 3)
    {
        bkcolor();
        fontcolor();
    }
    else
        font_color = 15;

    Theme_Button();
    setbkcolor(0);

    ///////////////////

    if (hover_tab == 4)
    {
        bkcolor();
        fontcolor();
    }
    else
        font_color = 15;

    Background_Button();
    setbkcolor(0);

    ///////////////////

    if (hover_tab == 5)
    {
        bkcolor();
        fontcolor();
    }
    else
        font_color = 15;

    Parts_Button();
    setbkcolor(0);

    ///////////////////

    if (hover_tab == 6)
    {
        bkcolor();
        fontcolor();
    }
    else
        font_color = 15;

    Save_Button();
    setbkcolor(0);

    ///////////////////

    if (hover_tab == 7)
    {
        bkcolor();
        fontcolor();
    }
    else
        font_color = 15;

    Load_Button();
    setbkcolor(0);

    ///////////////////

    if (hover_tab == 8)
    {
        bkcolor();
        fontcolor();
    }
    else
        font_color = 15;

    Mute_Button();
    setbkcolor(0);

    ///////////////////

    if (hover_tab == 9)
    {
        bkcolor();
        fontcolor();
    }
    else
        font_color = 15;

    Hide_Button();
    setbkcolor(0);

    ///////////////////

    if (hover_tab == 10)
    {
        bkcolor();
        fontcolor();
    }
    else
        font_color = 15;

    Zoom_Button();
    setbkcolor(0);

    ///////////////////

    if (hover_tab == 11)
    {
        bkcolor();
        fontcolor();
    }
    else
        font_color = 15;

    Language_Button();
    setbkcolor(0);

    ///////////////////

    if (hover_tab == 1)
    {
        bkcolor();
        fontcolor();
    }
    else
        font_color = 15;

    Help_button();
    setbkcolor(0);

}

/////////////////// Pop-up Menu Maker ///////////////////

void Menu_maker(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    int points[8];
    switch (color)
    {
    case 1:
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        break;
    case 2:
        setfillstyle(SOLID_FILL, RED);
        break;
    case 3:
        setfillstyle(SOLID_FILL, GREEN);
        break;
    case 4:
        setfillstyle(SOLID_FILL, YELLOW);
        break;
    case 5:
        setfillstyle(SOLID_FILL, LIGHTMAGENTA);
        break;
    case 6:
        setfillstyle(SOLID_FILL, WHITE);
        break;
    }
    points[0] = x1;
    points[1] = y1;
    points[2] = x2;
    points[3] = y2;
    points[4] = x3;
    points[5] = y3;
    points[6] = x4;
    points[7] = y4;
    fillpoly(4, points);
    rectangle(x1, y1, x3, y3);
}

/////////////////// LOGIC FOR BUTTONS ///////////////////

void Logic()
{
    int x, y;
    bool next_step = 0, help_exit = 0;
    char selector = NULL;

    /////////////////// LOGIC FOR PRESSES ///////////////////

    getmouseclick(WM_LBUTTONDOWN, x, y);

    if ((x >= 1800 && x <= 1920 && y >= 1005 && y <= 1055 || menu_selector == 11) && !is_open)         // HELP BUTTON PRESS
    {
        if (!mute)
            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
        Menu_maker(1587, 874, 1587, 1055, 1800, 1055, 1800, 874);
        menu_pop_up = 1;                                         // Arata faptul ca avem un nou meniu aparut
        is_open = 1;
        setbkcolor(0);
        Help_menu();
        menu_selector = 0;

        while (selector == NULL && !next_step)                    // cat timp nu am dat click/selectat o comanda
        {
            if (ismouseclick(WM_LBUTTONDOWN))                 // daca dam click
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                if (x >= 1590 && x <= 1800 && y >= 878 && y <= 900)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    key = 's';
                }
                else if (x >= 1590 && x <= 1800 && y >= 900 && y <= 922)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    key = 'l';
                }
                else if (x >= 1590 && x <= 1800 && y >= 922 && y <= 944)
                {
                    key = 'r';
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }
                else if (x >= 1590 && x <= 1800 && y >= 944 && y <= 966)
                {
                    key = '+';
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }
                else if (x >= 1592 && x <= 1800 && y >= 966 && y <= 988)
                {
                    key = '-';
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }
                else if (x >= 1592 && x <= 1800 && y >= 988 && y <= 1010)
                {
                    key = 'h';
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }
                else if (x >= 1592 && x <= 1800 && y >= 1010 && y <= 1032)
                {
                    help_exit = 1;
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }

                next_step = 1;
            }
            if (kbhit())                                      // daca dam o tasta
            {
                selector = getch();
                if (!mute)
                    PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
            }
        }

        if (next_step == 0)
            if (selector == '1')selector = 's';
            else if (selector == '2')selector = 'l';
            else if (selector == '3')selector = 'r';
            else if (selector == '4')selector = '+';
            else if (selector == '5')selector = '-';
            else if (selector == '6')selector = 'h';
            else if (selector == '7')help_exit = 1;

        if (selector != 27 && selector != NULL)
            key = selector;
        next_step = 0;
        selector = NULL;
        if (help_exit == 0) Background_Image();
    }

    if ((x >= 1800 && x <= 1920 && y >= 5 && y <= 55 || menu_selector == 1) && !is_open || help_exit) // EXIT BUTTON PRESS
    {
        if (!mute)
            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
        Menu_maker(1700, 5, 1700, 70, 1800, 70, 1800, 5);
        menu_pop_up = 1;                                         // Arata faptul ca avem un nou meniu aparut
        is_open = 1;
        setbkcolor(0);
        Exit_menu();
        help_exit = 0;
        menu_selector = 0;

        while (selector == NULL && !next_step)                    // cat timp nu am dat click/selectat o comanda
        {
            if (ismouseclick(WM_LBUTTONDOWN))                 // daca dam click
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                if (x >= 1700 && x <= 1800 && y >= 10 && y <= 40)
                {
                    key = 27;
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }
                else
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }

                next_step = 1;
            }
            if (kbhit())                                      // daca dam o tasta
            {
                selector = getch();
                if (!mute)
                    PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
            }
        }

        if (next_step == 0)
            if (selector == '1')key = 27;

        next_step = 0;
        selector = NULL;
        Background_Image();

    }
    else if ((x >= 1800 && x <= 1920 && y >= 56 && y <= 106 || menu_selector == 2) && !is_open)  // THEME BUTTON PRESS
    {
        if (!mute)
            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
        Menu_maker(1655, 65, 1655, 248, 1800, 248, 1800, 65);
        menu_pop_up = 1;                                         // Arata faptul ca avem un nou meniu aparut
        is_open = 1;
        setbkcolor(0);
        Theme_menu();
        menu_selector = 0;

        while (selector == NULL && !next_step)                    // cat timp nu am dat click/selectat o comanda
        {
            if (ismouseclick(WM_LBUTTONDOWN))                 // daca dam click
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                if (x >= 1655 && x <= 1800 && y >= 70 && y <= 99)
                {
                    color = 1;
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }
                else if (x >= 1655 && x <= 1800 && y >= 100 && y <= 129)
                {
                    color = 2;
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }
                else if (x >= 1655 && x <= 1800 && y >= 130 && y <= 159)
                {
                    color = 3;
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }
                else if (x >= 1655 && x <= 1800 && y >= 160 && y <= 189)
                {
                    color = 4;
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }
                else if (x >= 1655 && x <= 1800 && y >= 190 && y <= 219)
                {
                    color = 5;
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }
                else if (x >= 1655 && x <= 1800 && y >= 220 && y <= 249)
                {
                    color = 6;
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }

                next_step = 1;
            }
            if (kbhit())                                      // daca dam o tasta
            {
                selector = getch();
                if (!mute)
                    PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
            }
        }

        if (next_step == 0)
            if (selector == '1')color = 1;
            else if (selector == '2')color = 2;
            else if (selector == '3')color = 3;
            else if (selector == '4')color = 4;
            else if (selector == '5')color = 5;
            else if (selector == '6')color = 6;

        next_step = 0;
        selector = NULL;
        Background_Image();

    }
    else if ((x >= 1800 && x <= 1920 && y >= 107 && y <= 157 || menu_selector == 3) && !is_open)  // BACKGROUND BUTTON PRESS
    {
        if (!mute)
            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
        Menu_maker(1620, 107, 1620, 293, 1800, 293, 1800, 107);
        menu_pop_up = 1;                                         // Arata faptul ca avem un nou meniu aparut
        is_open = 1;
        setbkcolor(0);
        Background_menu();
        menu_selector = 0;

        while (selector == NULL && !next_step)                    // cat timp nu am dat click/selectat o comanda
        {
            if (ismouseclick(WM_LBUTTONDOWN))                 // daca dam click
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                if (x >= 1655 && x <= 1800 && y >= 113 && y <= 142)
                {
                    background_selector = 1;
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }
                else if (x >= 1655 && x <= 1800 && y >= 143 && y <= 172)
                {
                    background_selector = 2;
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }
                else if (x >= 1655 && x <= 1800 && y >= 173 && y <= 202)
                {
                    background_selector = 3;
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }
                else if (x >= 1655 && x <= 1800 && y >= 203 && y <= 232)
                {
                    background_selector = 4;
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }
                else if (x >= 1655 && x <= 1800 && y >= 233 && y <= 262)
                {
                    background_selector = 5;
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }
                else if (x >= 1655 && x <= 1800 && y >= 263 && y <= 293)
                {
                    background_selector = 6;
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }

                next_step = 1;
            }
            if (kbhit())                                      // daca dam o tasta
            {
                selector = getch();
                if (!mute)
                    PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
            }
        }

        if (next_step == 0)
            if (selector == '1')background_selector = 1;
            else if (selector == '2')background_selector = 2;
            else if (selector == '3')background_selector = 3;
            else if (selector == '4')background_selector = 4;
            else if (selector == '5')background_selector = 5;
            else if (selector == '6')background_selector = 6;

        Background_Image();
        next_step = 0;
        selector = NULL;

    }
    else if ((x >= 1800 && x <= 1920 && y >= 209 && y <= 259 || menu_selector == 5) && !is_open)  // SAVE BUTTON PRESS
    {
        if (!mute)
            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
        Menu_maker(1640, 209, 1640, 515, 1800, 515, 1800, 209);
        menu_pop_up = 1;                                         // Arata faptul ca avem un nou meniu aparut
        is_open = 1;
        setbkcolor(0);
        Save_menu();
        menu_selector = 0;
        int good = 0;

        while (selector == NULL && !next_step)                    // cat timp nu am dat click/selectat o comanda
        {
            if (ismouseclick(WM_LBUTTONDOWN))                 // daca dam click
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);

                if (x >= 1640 && x <= 1800 && y >= 215 && y <= 245)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 1;
                    readimagefile(checkmark, 1667, 215, 1687, 235);
                    good = 1;
                }
                else if (x >= 1640 && x <= 1800 && y >= 246 && y <= 275)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 2;
                    readimagefile(checkmark, 1667, 246, 1687, 266);
                    good = 1;
                }
                else if (x >= 1640 && x <= 1800 && y >= 276 && y <= 305)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 3;
                    readimagefile(checkmark, 1667, 276, 1687, 296);
                    good = 1;
                }
                else if (x >= 1640 && x <= 1800 && y >= 306 && y <= 335)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 4;
                    readimagefile(checkmark, 1667, 306, 1687, 326);
                    good = 1;
                }
                else if (x >= 1640 && x <= 1800 && y >= 336 && y <= 365)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 5;
                    readimagefile(checkmark, 1667, 336, 1687, 356);
                    good = 1;
                }
                else if (x >= 1640 && x <= 1800 && y >= 366 && y <= 395)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 6;
                    readimagefile(checkmark, 1667, 366, 1687, 386);
                    good = 1;
                }
                else if (x >= 1640 && x <= 1800 && y >= 396 && y <= 425)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 7;
                    readimagefile(checkmark, 1667, 396, 1687, 416);
                    good = 1;
                }
                else if (x >= 1640 && x <= 1800 && y >= 426 && y <= 455)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 8;
                    readimagefile(checkmark, 1667, 426, 1687, 446);
                    good = 1;
                }
                else if (x >= 1640 && x <= 1800 && y >= 456 && y <= 485)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 9;
                    readimagefile(checkmark, 1667, 456, 1687, 476);
                    good = 1;
                }
                else if (x >= 1640 && x <= 1800 && y >= 486 && y <= 515)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 10;
                    readimagefile(checkmark, 1667, 486, 1687, 506);
                    good = 1;
                }

                next_step = 1;
            }
            if (kbhit())                                      // daca dam o tasta
            {
                selector = getch();
                if (!mute)
                    PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
            }
        }

        if (next_step == 0)
            if (selector == '0')
            {
                load_position = 1;
                good = 1;
            }
            else if (selector == '1')
            {
                load_position = 2;
                good = 1;
            }
            else if (selector == '2')
            {
                load_position = 3;
                good = 1;
            }
            else if (selector == '3')
            {
                load_position = 4;
                good = 1;
            }
            else if (selector == '4')
            {
                load_position = 5;
                good = 1;
            }
            else if (selector == '5')
            {
                load_position = 6;
                good = 1;
            }
            else if (selector == '6')
            {
                load_position = 7;
                good = 1;
            }
            else if (selector == '7')
            {
                load_position = 8;
                good = 1;
            }
            else if (selector == '8')
            {
                load_position = 9;
                good = 1;
            }
            else if (selector == '9')
            {
                load_position = 10;
                good = 1;
            }

        if (good)
        {
            Menu_maker(1370, 209 + (load_position - 1) * 30, 1370, 250 + (load_position - 1) * 30, 1640, 250 + (load_position - 1) * 30, 1640, 209 + (load_position - 1) * 30);
            read();
            if (abord == 0)
                Save();
            abord = 0;
            for (int i = 0; i < strlen(name); i++)
                name[i] = ' ';
        }

        Background_Image();
        next_step = 0;
        selector = NULL;

    }
    else if ((x >= 1800 && x <= 1920 && y >= 260 && y <= 310 || menu_selector == 6) && !is_open)  // LOAD BUTTON PRESS
    {
        if (!mute)
            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
        Menu_maker(1640, 260, 1640, 565, 1800, 565, 1800, 260);
        menu_pop_up = 1;                                         // Arata faptul ca avem un nou meniu aparut
        is_open = 1;
        setbkcolor(0);
        Load_menu();
        menu_selector = 0;
        int good = 0;

        while (selector == NULL && !next_step)                    // cat timp nu am dat click/selectat o comanda
        {
            if (ismouseclick(WM_LBUTTONDOWN))                 // daca dam click
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);

                if (x >= 1640 && x <= 1800 && y >= 265 && y <= 295)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 1;
                    good = 1;
                }
                else if (x >= 1640 && x <= 1800 && y >= 296 && y <= 325)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 2;
                    good = 1;
                }
                else if (x >= 1640 && x <= 1800 && y >= 326 && y <= 355)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 3;
                    good = 1;
                }
                else if (x >= 1640 && x <= 1800 && y >= 356 && y <= 385)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 4;
                    good = 1;
                }
                else if (x >= 1640 && x <= 1800 && y >= 386 && y <= 415)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 5;
                    good = 1;
                }
                else if (x >= 1640 && x <= 1800 && y >= 416 && y <= 445)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 6;
                    good = 1;
                }
                else if (x >= 1640 && x <= 1800 && y >= 446 && y <= 475)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 7;
                    good = 1;
                }
                else if (x >= 1640 && x <= 1800 && y >= 476 && y <= 505)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 8;
                    good = 1;
                }
                else if (x >= 1640 && x <= 1800 && y >= 506 && y <= 535)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 9;
                    good = 1;
                }
                else if (x >= 1640 && x <= 1800 && y >= 536 && y <= 565)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    load_position = 10;
                    good = 1;
                }

                next_step = 1;
            }
            if (kbhit())                                      // daca dam o tasta
            {
                selector = getch();
                if (!mute)
                    PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
            }
        }

        if (next_step == 0)
            if (selector == '0')
            {
                load_position = 1;
                good = 1;
            }
            else if (selector == '1')
            {
                load_position = 2;
                good = 1;
            }
            else if (selector == '2')
            {
                load_position = 3;
                good = 1;
            }
            else if (selector == '3')
            {
                load_position = 4;
                good = 1;
            }
            else if (selector == '4')
            {
                load_position = 5;
                good = 1;
            }
            else if (selector == '5')
            {
                load_position = 6;
                good = 1;
            }
            else if (selector == '6')
            {
                load_position = 7;
                good = 1;
            }
            else if (selector == '7')
            {
                load_position = 8;
                good = 1;
            }
            else if (selector == '8')
            {
                load_position = 9;
                good = 1;
            }
            else if (selector == '9')
            {
                load_position = 10;
                good = 1;
            }

        if (good)
        {
            Loading_Screen();
            Load();
        }
        Background_Image();
        next_step = 0;
        selector = NULL;

    }
    else if ((x >= 1800 && x <= 1920 && y >= 158 && y <= 208 || menu_selector == 4) && !is_open)  // PARTS BUTTON PRESS
    {
        if (!mute)
            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
        Menu_maker(1535, 152, 1535, 488, 1800, 488, 1800, 152);
        menu_pop_up = 1;                                         // Arata faptul ca avem un nou meniu aparut
        is_open = 1;
        setbkcolor(0);
        Parts_menu();
        menu_selector = 0;
        int tipul_piesei = 0, x1 = -1, y1 = -1;

        while (selector == NULL && !next_step)                    // cat timp nu am dat click/selectat o comanda
        {
            if (ismouseclick(WM_LBUTTONDOWN))                 // daca dam click
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                if (x >= 1535 && x <= 1800 && y >= 158 && y <= 187)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    tipul_piesei = 1;
                    readimagefile(checkmark, 1570, 160, 1590, 180);
                }
                else if (x >= 1535 && x <= 1800 && y >= 188 && y <= 217)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    tipul_piesei = 2;
                    readimagefile(checkmark, 1570, 190, 1590, 210);
                }
                else if (x >= 1535 && x <= 1800 && y >= 218 && y <= 247)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    tipul_piesei = 3;
                    readimagefile(checkmark, 1570, 220, 1590, 240);
                }
                else if (x >= 1535 && x <= 1800 && y >= 248 && y <= 277)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    tipul_piesei = 4;
                    readimagefile(checkmark, 1570, 250, 1590, 270);
                }
                else if (x >= 1535 && x <= 1800 && y >= 278 && y <= 307)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    tipul_piesei = 5;
                    readimagefile(checkmark, 1570, 280, 1590, 300);
                }
                else if (x >= 1535 && x <= 1800 && y >= 308 && y <= 337)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    tipul_piesei = 6;
                    readimagefile(checkmark, 1570, 310, 1590, 330);
                }
                else if (x >= 1535 && x <= 1800 && y >= 338 && y <= 367)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    tipul_piesei = 7;
                    readimagefile(checkmark, 1570, 340, 1590, 360);
                }
                else if (x >= 1535 && x <= 1800 && y >= 368 && y <= 397)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    tipul_piesei = 8;
                    readimagefile(checkmark, 1570, 370, 1590, 390);
                }
                else if (x >= 1535 && x <= 1800 && y >= 398 && y <= 427)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    tipul_piesei = 9;
                    readimagefile(checkmark, 1570, 400, 1590, 420);
                }
                else if (x >= 1535 && x <= 1800 && y >= 428 && y <= 457)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    tipul_piesei = 10;
                    readimagefile(checkmark, 1570, 430, 1590, 450);
                }
                else if (x >= 1535 && x <= 1800 && y >= 458 && y <= 487)
                {
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    tipul_piesei = 11;
                    readimagefile(checkmark, 1570, 460, 1590, 480);
                }
                next_step = 1;
            }
            if (kbhit())                                      // daca dam o tasta
            {
                selector = getch();
                if (!mute)
                    PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
            }
        }

        if (next_step == 0)
            switch (selector)
            {
            case '1':
                tipul_piesei = 1;
                readimagefile(checkmark, 1570, 160, 1590, 180);
                break;
            case '2':
                tipul_piesei = 2;
                readimagefile(checkmark, 1570, 190, 1590, 210);
                break;
            case '3':
                tipul_piesei = 3;
                readimagefile(checkmark, 1570, 220, 1590, 240);
                break;
            case '4':
                tipul_piesei = 4;
                readimagefile(checkmark, 1570, 250, 1590, 270);
                break;
            case '5':
                tipul_piesei = 5;
                readimagefile(checkmark, 1570, 280, 1590, 300);
                break;
            case '6':
                tipul_piesei = 6;
                readimagefile(checkmark, 1570, 310, 1590, 330);
                break;
            case '7':
                tipul_piesei = 7;
                readimagefile(checkmark, 1570, 340, 1590, 360);
                break;
            case '8':
                tipul_piesei = 8;
                readimagefile(checkmark, 1570, 370, 1590, 390);
                break;
            case '9':
                tipul_piesei = 9;
                readimagefile(checkmark, 1570, 400, 1590, 420);
                break;
            case '0':
                tipul_piesei = 10;
                readimagefile(checkmark, 1570, 430, 1590, 450);
                break;
            case '-':
                tipul_piesei = 11;
                readimagefile(checkmark, 1570, 460, 1590, 480);
                break;
            default:
                selector = '\t';
            }
        if ((next_step == 1 && tipul_piesei != 0) || (selector != NULL && selector != '\t'))
        {
            while (x1 == -1 && y1 == -1)
                getmouseclick(WM_LBUTTONDOWN, x1, y1);

            int OK = 1;

            for (int i = 1; i <= nb_of_piese; i++)
                if (piese[i].x == x1 / (zoom_level * 10) && piese[i].y == y1 / (zoom_level * 10))OK = 0;  // verifica daca se afla deja o piesa pe tabla in locul respectiv(x,y)

            if (x1 < 1800 && OK == 1)
            {
                nb_of_piese++;
                piese[nb_of_piese].x = x1 / (zoom_level * 10);
                piese[nb_of_piese].y = y1 / (zoom_level * 10);
                piese[nb_of_piese].rotation = 0;
                piese[nb_of_piese].tip = tipul_piesei;

                matrice_tabla[100+piese[nb_of_piese].y][100+piese[nb_of_piese].x]=-1*piese[nb_of_piese].tip;

                if(tipul_piesei == 9)
                    piese[nb_of_piese].on = 0;
            }
        }

        next_step = 0;
        selector = NULL;
        Background_Image();

    }
    else if ((x >= 1800 && x <= 1920 && y >= 311 && y <= 361 || menu_selector == 7) && !is_open)  // MUTE BUTTON PRESS
    {
        if (!mute)
            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
        Menu_maker(1625, 311, 1625, 375, 1800, 375, 1800, 311);
        menu_pop_up = 1;                                         // Arata faptul ca avem un nou meniu aparut
        is_open = 1;
        setbkcolor(0);
        Mute_menu();
        menu_selector = 0;

        while (selector == NULL && !next_step)                    // cat timp nu am dat click/selectat o comanda
        {
            if (ismouseclick(WM_LBUTTONDOWN))                 // daca dam click
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                if (x >= 1625 && x <= 1800 && y >= 311 && y <= 341)
                {
                    mute = 1;
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }
                else if (x >= 1625 && x <= 1800 && y >= 342 && y <= 372)
                {
                    mute = 0;
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }

                next_step = 1;
            }
            if (kbhit())                                      // daca dam o tasta
            {
                selector = getch();
                if (!mute)
                    PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
            }
        }

        if (next_step == 0)
            if (selector == '1')mute = 1;
            else if (selector == '2')mute = 0;

        Background_Image();
        next_step = 0;
        selector = NULL;

    }
    else if ((x >= 1800 && x <= 1920 && y >= 362 && y <= 412 || menu_selector == 8) && !is_open)  // HIDE BUTTON PRESS
    {
        if (!mute)
            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
        Menu_maker(1670, 362, 1670, 426, 1800, 426, 1800, 362);
        menu_pop_up = 1;                                         // Arata faptul ca avem un nou meniu aparut
        is_open = 1;
        setbkcolor(0);
        Hide_menu();
        menu_selector = 0;

        while (selector == NULL && !next_step)                    // cat timp nu am dat click/selectat o comanda
        {
            if (ismouseclick(WM_LBUTTONDOWN))                 // daca dam click
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                if (x >= 1670 && x <= 1800 && y >= 362 && y <= 392)
                {
                    hidder = 1;
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }
                else if (x >= 1670 && x <= 1800 && y >= 393 && y <= 423)
                {
                    hidder = 0;
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }

                next_step = 1;
            }
            if (kbhit())                                      // daca dam o tasta
            {
                selector = getch();
                if (!mute)
                    PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
            }
        }

        if (next_step == 0)
            if (selector == '1')hidder = 1;
            else if (selector == '2')hidder = 0;

        Background_Image();
        next_step = 0;
        selector = NULL;

    }
    else if ((x >= 1800 && x <= 1920 && y >= 413 && y <= 463 || menu_selector == 9) && !is_open)  // ZOOM BUTTON PRESS
    {
        if (!mute)
            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
        Menu_maker(1610, 413, 1610, 476, 1800, 476, 1800, 413);
        menu_pop_up = 1;                                         // Arata faptul ca avem un nou meniu aparut
        is_open = 1;
        setbkcolor(0);
        Zoom_menu();
        menu_selector = 0;

        while (selector == NULL && !next_step)                    // cat timp nu am dat click/selectat o comanda
        {
            if (ismouseclick(WM_LBUTTONDOWN))                 // daca dam click
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                if (x >= 1610 && x <= 1800 && y >= 413 && y <= 443)
                {
                    key = '+';
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }
                else if (x >= 1610 && x <= 1800 && y >= 444 && y <= 474)
                {
                    key = '-';
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }

                next_step = 1;
            }
            if (kbhit())                                      // daca dam o tasta
            {
                selector = getch();
                if (!mute)
                    PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
            }
        }

        if (next_step == 0)
            if (selector == '1')key = '+';
            else if (selector == '2')key = '-';

        Background_Image();
        next_step = 0;
        selector = NULL;

    }
    else if ((x >= 1800 && x <= 1920 && y >= 464 && y <= 514 || menu_selector == 10) && !is_open)  // LANGUAGE BUTTON PRESS
    {
        if (!mute)
            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
        Menu_maker(1625, 464, 1625, 557, 1800, 557, 1800, 464);
        menu_pop_up = 1;                                         // Arata faptul ca avem un nou meniu aparut
        is_open = 1;
        setbkcolor(0);
        Language_menu();
        menu_selector = 0;

        while (selector == NULL && !next_step)                    // cat timp nu am dat click/selectat o comanda
        {
            if (ismouseclick(WM_LBUTTONDOWN))                 // daca dam click
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                if (x >= 1625 && x <= 1800 && y >= 464 && y <= 494)
                {
                    language = 1;
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }
                else if (x >= 1625 && x <= 1800 && y >= 495 && y <= 525)
                {
                    language = 2;
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }
                else if (x >= 1625 && x <= 1800 && y >= 526 && y <= 556)
                {
                    language = 3;
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                }


                next_step = 1;
            }
            if (kbhit())                                      // daca dam o tasta
            {
                selector = getch();
                if (!mute)
                    PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
            }
        }

        if (next_step == 0)
            if (selector == '1')language = 1;
            else if (selector == '2')language = 2;
            else if (selector == '3')language = 3;

        Background_Image();
        next_step = 0;
        selector = NULL;

    }
    else if (x > 0 && x < 1800)  // INDIVIDUAL PART BUTTON PRESS
    {
        if (!mute)
            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
        int OK = 0, i;

        for (i = 1; i <= nb_of_piese && OK == 0; i++)
            if (piese[i].x == x / (zoom_level * 10) && piese[i].y == y / (zoom_level * 10))OK = 1;

        if (OK == 1)
        {
            int x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6=-1, y6=-1;

            if (x <= 1630)
            {
                x1 = ((x / (zoom_level * 10) + 1) * (zoom_level * 10));
                x2 = ((x / (zoom_level * 10) + 1) * (zoom_level * 10));
                x3 = ((x / (zoom_level * 10) + 1) * (zoom_level * 10)) + 130;
                x4 = ((x / (zoom_level * 10) + 1) * (zoom_level * 10)) + 130;
            }
            else
            {
                x1 = ((x / (zoom_level * 10)) * (zoom_level * 10)) - 130;
                x2 = ((x / (zoom_level * 10)) * (zoom_level * 10)) - 130;
                x3 = ((x / (zoom_level * 10)) * (zoom_level * 10));
                x4 = ((x / (zoom_level * 10)) * (zoom_level * 10));
            }
            if (y <= 1000)
            {
                y1 = (y / (zoom_level * 10) * (zoom_level * 10));
                if(piese[i - 1].tip == 9)
                {
                    y2 = (y / (zoom_level * 10) * (zoom_level * 10)) + 130;
                    y3 = (y / (zoom_level * 10) * (zoom_level * 10)) + 130;
                }
                else
                {
                    y2 = (y / (zoom_level * 10) * (zoom_level * 10)) + 105;
                    y3 = (y / (zoom_level * 10) * (zoom_level * 10)) + 105;
                }
                y4 = (y / (zoom_level * 10) * (zoom_level * 10));
            }
            else
            {
                if(piese[i - 1].tip == 9)
                    y1 = ((y / (zoom_level * 10) + 1) * (zoom_level * 10)) - 130;
                else
                    y1 = ((y / (zoom_level * 10) + 1) * (zoom_level * 10)) - 105;
                y2 = ((y / (zoom_level * 10) + 1) * (zoom_level * 10));
                y3 = ((y / (zoom_level * 10) + 1) * (zoom_level * 10));
                if(piese[i - 1].tip == 9)
                    y4 = ((y / (zoom_level * 10) + 1) * (zoom_level * 10)) - 130;
                else
                    y4 = ((y / (zoom_level * 10) + 1) * (zoom_level * 10)) - 105;
            }
            Menu_maker(x1, y1, x2, y2, x3, y3, x4, y4);
            setbkcolor(0);
            Individual_part_menu(x1, y1, piese[i - 1].tip);

            menu_pop_up = 1;                                         // Arata faptul ca avem un nou meniu aparut
            is_open = 1;

            while (selector == NULL && !next_step)                    // cat timp nu am dat click/selectat o comanda
            {
                if (ismouseclick(WM_LBUTTONDOWN))                 // daca dam click
                {
                    getmouseclick(WM_LBUTTONDOWN, x5, y5);
                    if (x5 >= x1 && x5 <= x4 && y5 >= y1 + 5 && y5 <= y1 + 30)
                    {

                        int ok=0;
                        while(ok==0 and x6==-1 and y6==-1)
                        {
                            getmouseclick(WM_LBUTTONDOWN, x6, y6);
                        }

                        int is_piese=0;
                        for(int k=1; k<=nb_of_piese; k++)
                            if(piese[k].x==(x6/(zoom_level*10)) and piese[k].y==(y6/(zoom_level*10)))
                                is_piese=k;
                        if(is_piese)
                        {
                            ///////////////////////////colturi piesa de la care tragem firele/////////////////////

                            //colt stanga sus
                            int x7=x / (zoom_level * 10)*(zoom_level*10);
                            int y7=y / (zoom_level * 10)*(zoom_level*10);
                            //colt stanga jos
                            int x8=x / (zoom_level * 10)*(zoom_level*10);
                            int y8=y / (zoom_level * 10)*(zoom_level*10)+10*zoom_level;
                            //colt dreapta jos
                            int x9=x / (zoom_level * 10)*(zoom_level*10)+10*zoom_level;
                            int y9=y / (zoom_level * 10)*(zoom_level*10)+10*zoom_level;
                            //colt dreapta sus
                            int x10=x / (zoom_level * 10)*(zoom_level*10)+10*zoom_level;
                            int y10=y / (zoom_level * 10)*(zoom_level*10);

                            //////////// vedem in care parte a piesei am dat click//////////////
                            bool st1=0;
                            bool dr1=0;
                            bool sus1=0;
                            if(piese[i-1].rotation==0)
                            {
                                if(piese[i-1].tip==1 or piese[i-1].tip==7)
                                {
                                    if(y>=y7 and y<=((y7+y8)/2))
                                        sus1=1;
                                    else if(x>=x7 and x<=((x7+x10)/2))
                                        st1=1;
                                    else if(x>=((x7+x10)/2) and x<=x10)
                                        dr1=1;
                                }
                                else if(piese[i-1].tip==5)
                                    sus1=1;
                                else
                                {
                                    if(x>=x7 and x<=((x7+x10)/2))
                                        st1=1;
                                    else if(x>=((x7+x10)/2) and x<=x10)
                                        dr1=1;
                                }
                            }
                            else if(piese[i-1].rotation==1)
                            {

                                if(piese[i-1].tip==1 or piese[i-1].tip==7)
                                {
                                    if(x>=x8 and x<=((x7+x10)/2))
                                        sus1=1;
                                    else if(y<=y8 and y>=((y7+y8)/2))
                                        st1=1;
                                    else if(y<=((y7+y8)/2) and y>=y7)
                                        dr1=1;
                                }
                                else if(piese[i-1].tip==5)
                                    sus1=1;
                                else
                                {
                                    if(y<=y8 and y>=((y7+y8)/2))
                                        dr1=1;
                                    else if(y<=((y7+y8)/2) and y>=y7)
                                        st1=1;
                                }
                            }
                            else if(piese[i-1].rotation==2)
                            {
                                if(piese[i-1].tip==1 or piese[i-1].tip==7)
                                {
                                    if(y<=y8 and y>=((y7+y8)/2))
                                        sus1=1;
                                    else if(x<=x10 and x>=((x7+x10)/2))
                                        st1=1;
                                    else if(x<=((x7+x10)/2) and x>=x7)
                                        dr1=1;
                                }
                                else if(piese[i-1].tip==5)
                                    sus1=1;
                                else
                                {
                                    if(x<=x10 and x>=((x7+x10)/2))
                                        st1=1;
                                    else if(x<=((x7+x10)/2) and x>=x7)
                                        dr1=1;
                                }
                            }
                            else if(piese[i-1].rotation==3)
                            {
                                if(piese[i-1].tip==1 or piese[i-1].tip==7)
                                {
                                    if(x<=x10 and x>=((x7+x10)/2))
                                        sus1=1;
                                    else if(y>=y7 and y<=((y7+y8)/2))
                                        st1=1;
                                    else if(y>=((y7+y8)/2) and y<=y8)
                                        dr1=1;
                                }
                                else if(piese[i-1].tip==5)
                                    sus1=1;
                                else
                                {
                                    if(y>=y7 and y<=((y7+y8)/2))
                                        st1=1;
                                    else if(y>=((y7+y8)/2) and y<=y8)
                                        dr1=1;
                                }
                            }

                            ///////////////////////////colturi piesa la care tragem firele/////////////////////
                            int x11=x6 / (zoom_level*10) *(zoom_level*10);
                            int y11=y6 / (zoom_level*10) *(zoom_level*10);
                            //colt stanga jos
                            int x12=x6 / (zoom_level*10) *(zoom_level*10);
                            int y12=y6 / (zoom_level*10) *(zoom_level*10)+10*zoom_level;
                            //colt dreapta jos
                            int x13=x6 / (zoom_level*10) *(zoom_level*10)+10*zoom_level;
                            int y13=y6 / (zoom_level*10) *(zoom_level*10)+10*zoom_level;
                            //colt dreapta sus
                            int x14=x6 / (zoom_level*10) *(zoom_level*10)+10*zoom_level;
                            int y14=y6 / (zoom_level*10) *(zoom_level*10);

                            //cout<<x11<<' '<<y11<<endl<<x12<<' '<<y12<<endl<<x13<<' '<<y13<<endl<<x14<<' '<<y14<<endl;
                            //////////// vedem in care parte a piesei am dat click//////////////
                            bool st2=0;
                            bool dr2=0;
                            bool sus2=0;
                            if(piese[is_piese].rotation==0)
                            {
                                if(piese[is_piese].tip==1 or piese[is_piese].tip==7)
                                {
                                    if(y6>=y11 and y6<=((y11+y12)/2))
                                        sus2=1;
                                    else if(x6>=x11 and x6<=((x11+x14)/2))
                                        st2=1;
                                    else if((x6>=(x11+x14)/2) and x6<=x14)
                                        dr2=1;
                                }
                                else if(piese[is_piese].tip==5)
                                    sus2=1;
                                else
                                {
                                    if(x6>=x11 and x6<=((x11+x14)/2))
                                        st2=1;
                                    else if((x6>=(x11+x14)/2) and x6<=x14)
                                        dr2=1;
                                }
                            }
                            else if(piese[is_piese].rotation==1)
                            {
                                if(piese[is_piese].tip==1 or piese[is_piese].tip==7)
                                {
                                    if(x6>=x11 and x6<=((x11+x14)/2))
                                        sus2=1;
                                    else if(y6<=y12 and y6>=((y11+y12)/2))
                                        st2=1;
                                    else if(y6<=((y11+y12)/2) and y6>=y11)
                                        dr2=1;
                                }
                                else if(piese[is_piese].tip==5)
                                    sus2=1;
                                else
                                {
                                    if(y6<=y12 and y6>=((y11+y12)/2))
                                        dr2=1;
                                    else if(y6<=((y11+y12)/2) and y6>=y11)
                                        st2=1;
                                }
                            }
                            else if(piese[is_piese].rotation==2)
                            {
                                if(piese[is_piese].tip==1 or piese[is_piese].tip==7)
                                {
                                    if(y6<=y12 and y6>=((y11+y12)/2))
                                        sus2=1;
                                    else if(x6<=x14 and x6>=((x11+x14)/2))
                                        st2=1;
                                    else if(x6<=((x11+x14)/2) and x6>=x11)
                                        dr2=1;
                                }
                                else if(piese[is_piese].tip==5)
                                    sus2=1;
                                else
                                {
                                    if(x6<=x14 and x6>=((x11+x14)/2))
                                        st2=1;
                                    else if(x6<=((x11+x14)/2) and x6>=x11)
                                        dr2=1;
                                }
                            }
                            else if(piese[is_piese].rotation==3)
                            {
                                if(piese[is_piese].tip==1 or piese[is_piese].tip==7)
                                {
                                    if(x6<=x14 and x6>=((x11+x14)/2))
                                        sus2=1;
                                    else if(y6>=y11 and y6<=((y11+y12)/2))
                                        st2=1;
                                    else if(y6>=((y11+y12)/2) and y6<=y12)
                                        dr2=1;
                                }
                                else if(piese[is_piese].tip==5)
                                    sus2=1;
                                else
                                {
                                    if(y6>=y11 and y6<=((y11+y12)/2))
                                        st2=1;
                                    else if(y6>=((y11+y12)/2) and y6<=y12)
                                        dr2=1;
                                }
                            }

                            ///////////////////////

                            int val1;
                            if(sus1==1)
                                val1=3;
                            else if(dr1==1)
                                val1=2;
                            else if(st1==1)
                                val1=1;

                            int ok1=1;

                            for(int j=1; j<=nb_of_wires; j++)
                            {
                                if(wires[j].poz1==i-1)
                                {
                                    if(wires[j].info1==val1)
                                    {
                                        ok1=0;
                                    }
                                }
                                else if(wires[j].poz2==i-1)
                                    if(wires[j].info2==val1)
                                    {
                                        ok1=0;
                                    }
                            }

                            int val2;
                            if(sus2==1)
                                val2=3;
                            else if(dr2==1)
                                val2=2;
                            else if(st2==1)
                                val2=1;

                            int ok2=1;

                            for(int j=1; j<=nb_of_wires; j++)
                            {
                                if(wires[j].poz1==is_piese)
                                {
                                    if(wires[j].info1==val2)
                                    {
                                        ok2=0;
                                    }
                                }
                                else if(wires[j].poz2==is_piese)
                                    if(wires[j].info2==val2)
                                    {
                                        ok2=0;
                                    }
                            }

                            ///////////////////////
                            if(ok1==1 and ok2==1)
                            {
                                wires[++nb_of_wires].poz1= i-1;
                                wires[nb_of_wires].poz2= is_piese;


                                if(sus1==1)
                                {
                                    wires[nb_of_wires].info1=3;
                                }
                                else if(st1==1)
                                {
                                    wires[nb_of_wires].info1=1;
                                }
                                else if(dr1==1)
                                {
                                    wires[nb_of_wires].info1=2;
                                }



                                if(sus2==1)
                                {
                                    wires[nb_of_wires].info2=3;
                                }
                                else if(st2==1)
                                {
                                    wires[nb_of_wires].info2=1;
                                }
                                else
                                {
                                    wires[nb_of_wires].info2=2;
                                }
                            }
                        }
                    }
                    else if (x5 >= x1 && x5 <= x4 && y5 >= y1 + 31 && y5 <= y1 + 56)
                    {
                        if (!mute)
                            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);

                        piese[i - 1].rotation++;
                        if (piese[i - 1].rotation == 4)
                            piese[i - 1].rotation = 0;
                    }
                    else if (x5 >= x1 && x5 <= x4 && y5 >= y1 + 57 && y5 <= y1 + 82)
                    {
                        if (!mute)
                            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);

                        for(int j=1; j<=nb_of_wires; j++)
                            if(wires[j].poz1==i-1 or wires[j].poz2==i-1)
                            {
                                for(int k=j; k<nb_of_wires; k++)
                                    wires[k]=wires[k+1];
                                nb_of_wires--;
                                j--;
                            }
                        for(int j=1; j<=nb_of_wires; j++)
                        {
                            if(wires[j].poz1>=i-1)
                                wires[j].poz1--;
                            if(wires[j].poz2>=i-1)
                                wires[j].poz2--;
                        }

                        for(int j = i ; i <= nb_of_piese ; i++)
                            piese[i - 1] = piese[i];

                        nb_of_piese--;
                    }
                    else if (x5 >= x1 && x5 <= x4 && y5 >= y1 + 83 && y5 <= y1 + 108)         //    BUTON STERGERE FIRE
                    {
                        //cout<<"DA";
                        if (!mute)
                            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                        /////////////

                        //colt stanga sus
                        int x7=x / (zoom_level * 10)*(zoom_level*10);
                        int y7=y / (zoom_level * 10)*(zoom_level*10);
                        //colt stanga jos
                        int x8=x / (zoom_level * 10)*(zoom_level*10);
                        int y8=y / (zoom_level * 10)*(zoom_level*10)+10*zoom_level;
                        //colt dreapta jos
                        int x9=x / (zoom_level * 10)*(zoom_level*10)+10*zoom_level;
                        int y9=y / (zoom_level * 10)*(zoom_level*10)+10*zoom_level;
                        //colt dreapta sus
                        int x10=x / (zoom_level * 10)*(zoom_level*10)+10*zoom_level;
                        int y10=y / (zoom_level * 10)*(zoom_level*10);

                        //////////// vedem in care parte a piesei am dat click//////////////
                        bool st1=0;
                        bool dr1=0;
                        bool sus1=0;
                        if(piese[i-1].rotation==0)
                        {
                            if(piese[i-1].tip==1 or piese[i-1].tip==7)
                            {
                                if(y>=y7 and y<=((y7+y8)/2))
                                    sus1=1;
                                else if(x>=x7 and x<=((x7+x10)/2))
                                    st1=1;
                                else if(x>=((x7+x10)/2) and x<=x10)
                                    dr1=1;
                            }
                            else if(piese[i-1].tip==5)
                                sus1=1;
                            else
                            {
                                if(x>=x7 and x<=((x7+x10)/2))
                                    st1=1;
                                else if(x>=((x7+x10)/2) and x<=x10)
                                    dr1=1;
                            }
                        }
                        else if(piese[i-1].rotation==1)
                        {

                            if(piese[i-1].tip==1 or piese[i-1].tip==7)
                            {
                                if(x>=x8 and x<=((x7+x10)/2))
                                    sus1=1;
                                else if(y<=y8 and y>=((y7+y8)/2))
                                    st1=1;
                                else if(y<=((y7+y8)/2) and y>=y7)
                                    dr1=1;
                            }
                            else if(piese[i-1].tip==5)
                                sus1=1;
                            else
                            {
                                if(y<=y8 and y>=((y7+y8)/2))
                                    dr1=1;
                                else if(y<=((y7+y8)/2) and y>=y7)
                                    st1=1;
                            }
                        }
                        else if(piese[i-1].rotation==2)
                        {
                            if(piese[i-1].tip==1 or piese[i-1].tip==7)
                            {
                                if(y<=y8 and y>=((y7+y8)/2))
                                    sus1=1;
                                else if(x<=x10 and x>=((x7+x10)/2))
                                    st1=1;
                                else if(x<=((x7+x10)/2) and x>=x7)
                                    dr1=1;
                            }
                            else if(piese[i-1].tip==5)
                                sus1=1;
                            else
                            {
                                if(x<=x10 and x>=((x7+x10)/2))
                                    st1=1;
                                else if(x<=((x7+x10)/2) and x>=x7)
                                    dr1=1;
                            }
                        }
                        else if(piese[i-1].rotation==3)
                        {
                            if(piese[i-1].tip==1 or piese[i-1].tip==7)
                            {
                                if(x<=x10 and x>=((x7+x10)/2))
                                    sus1=1;
                                else if(y>=y7 and y<=((y7+y8)/2))
                                    st1=1;
                                else if(y>=((y7+y8)/2) and y<=y8)
                                    dr1=1;
                            }
                            else if(piese[i-1].tip==5)
                                sus1=1;
                            else
                            {
                                if(y>=y7 and y<=((y7+y8)/2))
                                    st1=1;
                                else if(y>=((y7+y8)/2) and y<=y8)
                                    dr1=1;
                            }
                        }

                        int val;
                        if(sus1==1)
                            val=3;
                        else if(dr1==1)
                            val=2;
                        else if(st1==1)
                            val=1;

                        //cout<<val;
                        /////stergerea

                        for(int j=1; j<=nb_of_wires; j++)
                        {
                            if(wires[j].poz1==i-1)
                            {
                                if(wires[j].info1==val)
                                {
                                    for(int k=j+1; k<=nb_of_wires; k++)
                                        wires[k-1]=wires[k];
                                    nb_of_wires--;
                                    j--;
                                }
                            }
                            else if(wires[j].poz2==i-1)
                                if(wires[j].info2==val)
                                {
                                    for(int k=j+1; k<=nb_of_wires; k++)
                                        wires[k-1]=wires[k];
                                    nb_of_wires--;
                                    j--;
                                }
                        }
                    }
                    else if(x5 >= x1 && x5 <= x4 && y5 >= y1 + 109 && y5 <= y1 + 134)
                        {

                    if(piese[i - 1].on == 1)piese[i - 1].on = 0;
                    else piese[i - 1].on = 1;

                    }

                    next_step = 1;
                }
                if (kbhit())                                      // daca dam o tasta
                    selector = getch();
            }

            if (next_step == 0)
                if (selector == '1');
            {

                getmouseclick(WM_LBUTTONDOWN, x5, y5);
                if (x5 >= x1 && x5 <= x4 && y5 >= y1 + 5 && y5 <= y1 + 30)
                {
                    int ok=0;
                    while(ok==0 and x6==-1 and y6==-1)
                    {
                        getmouseclick(WM_LBUTTONDOWN, x6, y6);
                    }

                    int is_piese=0;
                    for(int k=1; k<=nb_of_piese; k++)
                        if(piese[k].x==(x6/(zoom_level*10)) and piese[k].y==(y6/(zoom_level*10)))
                            is_piese=k;
                    if(is_piese)
                    {
                        ///////////////////////////colturi piesa de la care tragem firele/////////////////////

                        //colt stanga sus
                        int x7=x / (zoom_level * 10)*(zoom_level*10);
                        int y7=y / (zoom_level * 10)*(zoom_level*10);
                        //colt stanga jos
                        int x8=x / (zoom_level * 10)*(zoom_level*10);
                        int y8=y / (zoom_level * 10)*(zoom_level*10)+10*zoom_level;
                        //colt dreapta jos
                        int x9=x / (zoom_level * 10)*(zoom_level*10)+10*zoom_level;
                        int y9=y / (zoom_level * 10)*(zoom_level*10)+10*zoom_level;
                        //colt dreapta sus
                        int x10=x / (zoom_level * 10)*(zoom_level*10)+10*zoom_level;
                        int y10=y / (zoom_level * 10)*(zoom_level*10);

                        //////////// vedem in care parte a piesei am dat click//////////////
                        bool st1=0;
                        bool dr1=0;
                        bool sus1=0;
                        if(piese[i-1].rotation==0)
                        {
                            if(piese[i-1].tip==1 or piese[i-1].tip==7)
                            {
                                if(y>=y7 and y<=((y7+y8)/2))
                                    sus1=1;
                                else if(x>=x7 and x<=((x7+x10)/2))
                                    st1=1;
                                else if(x>=((x7+x10)/2) and x<=x10)
                                    dr1=1;
                            }
                            else if(piese[i-1].tip==5)
                                sus1=1;
                            else
                            {
                                if(x>=x7 and x<=((x7+x10)/2))
                                    st1=1;
                                else if(x>=((x7+x10)/2) and x<=x10)
                                    dr1=1;
                            }
                        }
                        else if(piese[i-1].rotation==1)
                        {

                            if(piese[i-1].tip==1 or piese[i-1].tip==7)
                            {
                                if(x>=x8 and x<=((x7+x10)/2))
                                    sus1=1;
                                else if(y<=y8 and y>=((y7+y8)/2))
                                    st1=1;
                                else if(y<=((y7+y8)/2) and y>=y7)
                                    dr1=1;
                            }
                            else if(piese[i-1].tip==5)
                                sus1=1;
                            else
                            {
                                if(y<=y8 and y>=((y7+y8)/2))
                                    dr1=1;
                                else if(y<=((y7+y8)/2) and y>=y7)
                                    st1=1;
                            }
                        }
                        else if(piese[i-1].rotation==2)
                        {
                            if(piese[i-1].tip==1 or piese[i-1].tip==7)
                            {
                                if(y<=y8 and y>=((y7+y8)/2))
                                    sus1=1;
                                else if(x<=x10 and x>=((x7+x10)/2))
                                    st1=1;
                                else if(x<=((x7+x10)/2) and x>=x7)
                                    dr1=1;
                            }
                            else if(piese[i-1].tip==5)
                                sus1=1;
                            else
                            {
                                if(x<=x10 and x>=((x7+x10)/2))
                                    st1=1;
                                else if(x<=((x7+x10)/2) and x>=x7)
                                    dr1=1;
                            }
                        }
                        else if(piese[i-1].rotation==3)
                        {
                            if(piese[i-1].tip==1 or piese[i-1].tip==7)
                            {
                                if(x<=x10 and x>=((x7+x10)/2))
                                    sus1=1;
                                else if(y>=y7 and y<=((y7+y8)/2))
                                    st1=1;
                                else if(y>=((y7+y8)/2) and y<=y8)
                                    dr1=1;
                            }
                            else if(piese[i-1].tip==5)
                                sus1=1;
                            else
                            {
                                if(y>=y7 and y<=((y7+y8)/2))
                                    st1=1;
                                else if(y>=((y7+y8)/2) and y<=y8)
                                    dr1=1;
                            }
                        }

                        ///////////////////////////colturi piesa la care tragem firele/////////////////////
                        int x11=x6 / (zoom_level*10) *(zoom_level*10);
                        int y11=y6 / (zoom_level*10) *(zoom_level*10);
                        //colt stanga jos
                        int x12=x6 / (zoom_level*10) *(zoom_level*10);
                        int y12=y6 / (zoom_level*10) *(zoom_level*10)+10*zoom_level;
                        //colt dreapta jos
                        int x13=x6 / (zoom_level*10) *(zoom_level*10)+10*zoom_level;
                        int y13=y6 / (zoom_level*10) *(zoom_level*10)+10*zoom_level;
                        //colt dreapta sus
                        int x14=x6 / (zoom_level*10) *(zoom_level*10)+10*zoom_level;
                        int y14=y6 / (zoom_level*10) *(zoom_level*10);

                        //cout<<x11<<' '<<y11<<endl<<x12<<' '<<y12<<endl<<x13<<' '<<y13<<endl<<x14<<' '<<y14<<endl;
                        //////////// vedem in care parte a piesei am dat click//////////////
                        bool st2=0;
                        bool dr2=0;
                        bool sus2=0;
                        if(piese[is_piese].rotation==0)
                        {
                            if(piese[is_piese].tip==1 or piese[is_piese].tip==7)
                            {
                                if(y6>=y11 and y6<=((y11+y12)/2))
                                    sus2=1;
                                else if(x6>=x11 and x6<=((x11+x14)/2))
                                    st2=1;
                                else if((x6>=(x11+x14)/2) and x6<=x14)
                                    dr2=1;
                            }
                            else if(piese[is_piese].tip==5)
                                sus2=1;
                            else
                            {
                                if(x6>=x11 and x6<=((x11+x14)/2))
                                    st2=1;
                                else if((x6>=(x11+x14)/2) and x6<=x14)
                                    dr2=1;
                            }
                        }
                        else if(piese[is_piese].rotation==1)
                        {
                            if(piese[is_piese].tip==1 or piese[is_piese].tip==7)
                            {
                                if(x6>=x11 and x6<=((x11+x14)/2))
                                    sus2=1;
                                else if(y6<=y12 and y6>=((y11+y12)/2))
                                    dr2=1;
                                else if(y6<=((y11+y12)/2) and y6>=y11)
                                    st2=1;
                            }
                            else if(piese[is_piese].tip==5)
                                sus2=1;
                            else
                            {
                                if(y6<=y12 and y6>=((y11+y12)/2))
                                    dr2=1;
                                else if(y6<=((y11+y12)/2) and y6>=y11)
                                    st2=1;
                            }
                        }
                        else if(piese[is_piese].rotation==2)
                        {
                            if(piese[is_piese].tip==1 or piese[is_piese].tip==7)
                            {
                                if(y6<=y12 and y6>=((y11+y12)/2))
                                    sus2=1;
                                else if(x6<=x14 and x6>=((x11+x14)/2))
                                    st2=1;
                                else if(x6<=((x11+x14)/2) and x6>=x11)
                                    dr2=1;
                            }
                            else if(piese[is_piese].tip==5)
                                sus2=1;
                            else
                            {
                                if(x6<=x14 and x6>=((x11+x14)/2))
                                    st2=1;
                                else if(x6<=((x11+x14)/2) and x6>=x11)
                                    dr2=1;
                            }
                        }
                        else if(piese[is_piese].rotation==3)
                        {
                            if(piese[is_piese].tip==1 or piese[is_piese].tip==7)
                            {
                                if(x6<=x14 and x6>=((x11+x14)/2))
                                    sus2=1;
                                else if(y6>=y11 and y6<=((y11+y12)/2))
                                    st2=1;
                                else if(y6>=((y11+y12)/2) and y6<=y12)
                                    dr2=1;
                            }
                            else if(piese[is_piese].tip==5)
                                sus2=1;
                            else
                            {
                                if(y6>=y11 and y6<=((y11+y12)/2))
                                    st2=1;
                                else if(y6>=((y11+y12)/2) and y6<=y12)
                                    dr2=1;
                            }
                        }

                        int val1;
                        if(sus1==1)
                            val1=3;
                        else if(dr1==1)
                            val1=2;
                        else if(st1==1)
                            val1=1;

                        int ok1=1;

                        for(int j=1; j<=nb_of_wires; j++)
                        {
                            if(wires[j].poz1==i-1)
                            {
                                if(wires[j].info1==val1)
                                {
                                    ok1=0;
                                }
                            }
                            else if(wires[j].poz2==i-1)
                                if(wires[j].info2==val1)
                                {
                                    ok1=0;
                                }
                        }

                        int val2;
                        if(sus2==1)
                            val2=3;
                        else if(dr2==1)
                            val2=2;
                        else if(st2==1)
                            val2=1;

                        int ok2=1;

                        for(int j=1; j<=nb_of_wires; j++)
                        {
                            if(wires[j].poz1==is_piese)
                            {
                                if(wires[j].info1==val2)
                                {
                                    ok2=0;
                                }
                            }
                            else if(wires[j].poz2==is_piese)
                                if(wires[j].info2==val2)
                                {
                                    ok2=0;
                                }
                        }

                        ///////////////////////
                        if(ok1==1 and ok2==1)
                        {
                            wires[++nb_of_wires].poz1= i-1;
                            wires[nb_of_wires].poz2= is_piese;


                            if(sus1==1)
                            {
                                wires[nb_of_wires].info1=3;
                            }
                            else if(st1==1)
                            {
                                wires[nb_of_wires].info1=1;
                            }
                            else if(dr1==1)
                            {
                                wires[nb_of_wires].info1=2;
                            }



                            if(sus2==1)
                            {
                                wires[nb_of_wires].info2=3;
                            }
                            else if(st2==1)
                            {
                                wires[nb_of_wires].info2=1;
                            }
                            else
                            {
                                wires[nb_of_wires].info2=2;
                            }
                        }
                    }
                }
                else if (selector == '2')
                {
                    piese[i - 1].rotation++;
                    if (piese[i - 1].rotation == 4)
                        piese[i - 1].rotation = 0;
                }
                else if (selector == '3')
                {
                    for(int j=1; j<=nb_of_wires; j++)
                        if(wires[j].poz1==i-1 or wires[j].poz2==i-1)
                        {
                            for(int k=j; k<nb_of_wires; k++)
                                wires[k]=wires[k+1];
                            nb_of_wires--;
                            j--;
                        }
                    for(int j=1; j<=nb_of_wires; j++)
                    {
                        if(wires[j].poz1>=i-1)
                            wires[j].poz1--;
                        if(wires[j].poz2>=i-1)
                            wires[j].poz2--;
                    }

                    for(int j = i ; i <= nb_of_piese ; i++)
                        piese[i - 1] = piese[i];

                    nb_of_piese--;
                }
                else if (selector == '4')
                {
                    //cout<<"DA";
                    if (!mute)
                        PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
                    /////////////

                    //colt stanga sus
                    int x7=x / (zoom_level * 10)*(zoom_level*10);
                    int y7=y / (zoom_level * 10)*(zoom_level*10);
                    //colt stanga jos
                    int x8=x / (zoom_level * 10)*(zoom_level*10);
                    int y8=y / (zoom_level * 10)*(zoom_level*10)+10*zoom_level;
                    //colt dreapta jos
                    int x9=x / (zoom_level * 10)*(zoom_level*10)+10*zoom_level;
                    int y9=y / (zoom_level * 10)*(zoom_level*10)+10*zoom_level;
                    //colt dreapta sus
                    int x10=x / (zoom_level * 10)*(zoom_level*10)+10*zoom_level;
                    int y10=y / (zoom_level * 10)*(zoom_level*10);

                    //////////// vedem in care parte a piesei am dat click//////////////
                    bool st1=0;
                    bool dr1=0;
                    bool sus1=0;
                    if(piese[i-1].rotation==0)
                    {
                        if(piese[i-1].tip==1 or piese[i-1].tip==7)
                        {
                            if(y>=y7 and y<=((y7+y8)/2))
                                sus1=1;
                            else if(x>=x7 and x<=((x7+x10)/2))
                                st1=1;
                            else if(x>=((x7+x10)/2) and x<=x10)
                                dr1=1;
                        }
                        else if(piese[i-1].tip==5)
                            sus1=1;
                        else
                        {
                            if(x>=x7 and x<=((x7+x10)/2))
                                st1=1;
                            else if(x>=((x7+x10)/2) and x<=x10)
                                dr1=1;
                        }
                    }
                    else if(piese[i-1].rotation==1)
                    {

                        if(piese[i-1].tip==1 or piese[i-1].tip==7)
                        {
                            if(x>=x8 and x<=((x7+x10)/2))
                                sus1=1;
                            else if(y<=y8 and y>=((y7+y8)/2))
                                st1=1;
                            else if(y<=((y7+y8)/2) and y>=y7)
                                dr1=1;
                        }
                        else if(piese[i-1].tip==5)
                            sus1=1;
                        else
                        {
                            if(y<=y8 and y>=((y7+y8)/2))
                                dr1=1;
                            else if(y<=((y7+y8)/2) and y>=y7)
                                st1=1;
                        }
                    }
                    else if(piese[i-1].rotation==2)
                    {
                        if(piese[i-1].tip==1 or piese[i-1].tip==7)
                        {
                            if(y<=y8 and y>=((y7+y8)/2))
                                sus1=1;
                            else if(x<=x10 and x>=((x7+x10)/2))
                                st1=1;
                            else if(x<=((x7+x10)/2) and x>=x7)
                                dr1=1;
                        }
                        else if(piese[i-1].tip==5)
                            sus1=1;
                        else
                        {
                            if(x<=x10 and x>=((x7+x10)/2))
                                st1=1;
                            else if(x<=((x7+x10)/2) and x>=x7)
                                dr1=1;
                        }
                    }
                    else if(piese[i-1].rotation==3)
                    {
                        if(piese[i-1].tip==1 or piese[i-1].tip==7)
                        {
                            if(x<=x10 and x>=((x7+x10)/2))
                                sus1=1;
                            else if(y>=y7 and y<=((y7+y8)/2))
                                st1=1;
                            else if(y>=((y7+y8)/2) and y<=y8)
                                dr1=1;
                        }
                        else if(piese[i-1].tip==5)
                            sus1=1;
                        else
                        {
                            if(y>=y7 and y<=((y7+y8)/2))
                                st1=1;
                            else if(y>=((y7+y8)/2) and y<=y8)
                                dr1=1;
                        }
                    }

                    int val;
                    if(sus1==1)
                        val=3;
                    else if(dr1==1)
                        val=2;
                    else if(st1==1)
                        val=1;

                    //cout<<val;
                    /////stergerea

                    for(int j=1; j<=nb_of_wires; j++)
                    {
                        if(wires[j].poz1==i-1)
                        {
                            if(wires[j].info1==val)
                            {
                                for(int k=j+1; k<=nb_of_wires; k++)
                                    wires[k-1]=wires[k];
                                nb_of_wires--;
                                j--;
                            }
                        }
                        else if(wires[j].poz2==i-1)
                            if(wires[j].info2==val)
                            {
                                for(int k=j+1; k<=nb_of_wires; k++)
                                    wires[k-1]=wires[k];
                                nb_of_wires--;
                                j--;
                            }
                    }

                }
                else if(selector == '5')
                {

                    if(piese[i - 1].on == 1)piese[i - 1].on = 0;
                    else piese[i - 1].on = 1;

                }

                Background_Image();
                next_step = 0;
                selector = NULL;

            }
        }
    }
    else
        is_open = 0;

    /////////////////// LOGIC FOR PRESSES 2 ///////////////////

    getmouseclick(WM_RBUTTONDOWN, x, y);

    if (x > 0 && x < 1800)  // MOVE THE PARTS ON THE TABLE
    {
        if (!mute)
            PlaySound("Sounds\\apas.wav", NULL, SND_ASYNC);
        int OK = 0, x1 = -1, y1 = -1, i;

        for (i = 1; i <= nb_of_piese && OK == 0; i++)
            if (piese[i].x == x / (zoom_level * 10) && piese[i].y == y / (zoom_level * 10))
            {
                OK = 1;
                readimagefile(checkmark, x / (zoom_level * 10) * (zoom_level * 10) + 2 * zoom_level, y / (zoom_level * 10) * (zoom_level * 10) + 2 * zoom_level, x / (zoom_level * 10) * (zoom_level * 10) + 8 * zoom_level, y / (zoom_level * 10) * (zoom_level * 10) + 8 * zoom_level);
            }
        if (OK == 1)
        {
            while (x1 == -1 && y1 == -1)
                getmouseclick(WM_LBUTTONDOWN, x1, y1);

            int OK1 = 1;

            for (int j = 1; j <= nb_of_piese; j++)
                if (piese[j].x == x1 / (zoom_level * 10) && piese[j].y == y1 / (zoom_level * 10))OK1 = 0;  // verifica daca se afla deja o piesa pe tabla in locul respectiv

            if (x1 < 1800 && OK1 == 1)
            {
                piese[i - 1].x = x1 / (zoom_level * 10);
                piese[i - 1].y = y1 / (zoom_level * 10);
            }
            Background_Image();
            draw_menu = 1;
        }
    }

    /////////////////// LOGIC FOR HOVERS ///////////////////

    x = mousex();
    y = mousey();

    if (x >= 1800 && x <= 1920 && y >= 1005 && y <= 1055 && (hover_tab == 1 || hover_tab == 0))              //HELP HOVER
    {
        change_bk = 1;
        if (!hover_mode)
        {
            if (!mute)
                PlaySound("Sounds\\click.wav", NULL, SND_ASYNC);
            Menu_maker(1800, 1005, 1800, 1055, 1920, 1055, 1920, 1005);      // coloram butonul
            outtextxy(1820, 1015, "HELP");                              // textul de pe buton
            hover_mode = 1;                                           // stergem dupa ce nu mai dam hover
            hover_tab = 1;
        }

    }
    else if (x >= 1800 && x <= 1920 && y >= 5 && y <= 55 && (hover_tab == 2 || hover_tab == 0))              //EXIT HOVER
    {

        if (!hover_mode)
        {
            if (!mute)
                PlaySound("Sounds\\click.wav", NULL, SND_ASYNC);
            Menu_maker(1800, 5, 1800, 55, 1920, 55, 1920, 5);                // coloram butonul
            outtextxy(1820, 15, "EXIT");                                // textul de pe buton
            hover_mode = 1;                                           // stergem dupa ce nu mai dam hover
            hover_tab = 2;
        }

    }
    else if (x >= 1800 && x <= 1920 && y >= 56 && y <= 106 && (hover_tab == 3 || hover_tab == 0))              //THEME HOVER
    {
        if (!hover_mode)
        {
            if (!mute)
                PlaySound("Sounds\\click.wav", NULL, SND_ASYNC);
            Menu_maker(1800, 56, 1800, 106, 1920, 106, 1920, 56);                // coloram butonul
            outtextxy(1820, 15, "THEME");                                // textul de pe buton
            hover_mode = 1;                                           // stergem dupa ce nu mai dam hover
            hover_tab = 3;
        }

    }
    else if (x >= 1800 && x <= 1920 && y >= 107 && y <= 157 && (hover_tab == 4 || hover_tab == 0))              //THEME HOVER
    {
        if (!hover_mode)
        {
            if (!mute)
                PlaySound("Sounds\\click.wav", NULL, SND_ASYNC);
            Menu_maker(1800, 107, 1800, 157, 1920, 157, 1920, 107);                // coloram butonul
            outtextxy(1820, 15, "BACKGROUND");                                // textul de pe buton
            hover_mode = 1;                                           // stergem dupa ce nu mai dam hover
            hover_tab = 4;
        }

    }
    else if (x >= 1800 && x <= 1920 && y >= 158 && y <= 208 && (hover_tab == 5 || hover_tab == 0))              //PARTS HOVER
    {
        if (!hover_mode)
        {
            if (!mute)
                PlaySound("Sounds\\click.wav", NULL, SND_ASYNC);
            Menu_maker(1800, 158, 1800, 208, 1920, 208, 1920, 158);                // coloram butonul
            outtextxy(1820, 15, "PARTS");                                // textul de pe buton
            hover_mode = 1;                                           // stergem dupa ce nu mai dam hover
            hover_tab = 5;
        }

    }
    else if (x >= 1800 && x <= 1920 && y >= 209 && y <= 259 && (hover_tab == 6 || hover_tab == 0))              //SAVE HOVER
    {
        if (!hover_mode)
        {
            if (!mute)
                PlaySound("Sounds\\click.wav", NULL, SND_ASYNC);
            Menu_maker(1800, 209, 1800, 259, 1920, 259, 1920, 209);                // coloram butonul
            outtextxy(1820, 15, "SAVE");                                // textul de pe buton
            hover_mode = 1;                                           // stergem dupa ce nu mai dam hover
            hover_tab = 6;
        }

    }
    else if (x >= 1800 && x <= 1920 && y >= 260 && y <= 310 && (hover_tab == 7 || hover_tab == 0))              //LOAD HOVER
    {
        if (!hover_mode)
        {
            if (!mute)
                PlaySound("Sounds\\click.wav", NULL, SND_ASYNC);
            Menu_maker(1800, 260, 1800, 310, 1920, 310, 1920, 260);                // coloram butonul
            outtextxy(1820, 15, "LOAD");                                // textul de pe buton
            hover_mode = 1;                                           // stergem dupa ce nu mai dam hover
            hover_tab = 7;
        }

    }
    else if (x >= 1800 && x <= 1920 && y >= 311 && y <= 361 && (hover_tab == 8 || hover_tab == 0))              //MUTE HOVER
    {
        if (!hover_mode)
        {
            if (!mute)
                PlaySound("Sounds\\click.wav", NULL, SND_ASYNC);
            Menu_maker(1800, 311, 1800, 361, 1920, 361, 1920, 311);                // coloram butonul
            outtextxy(1820, 15, "MUTE");                                // textul de pe buton
            hover_mode = 1;                                           // stergem dupa ce nu mai dam hover
            hover_tab = 8;
        }

    }
    else if (x >= 1800 && x <= 1920 && y >= 362 && y <= 412 && (hover_tab == 9 || hover_tab == 0))              //HIDE HOVER
    {
        if (!hover_mode)
        {
            if (!mute)
                PlaySound("Sounds\\click.wav", NULL, SND_ASYNC);
            Menu_maker(1800, 362, 1800, 412, 1920, 412, 1920, 362);                // coloram butonul
            outtextxy(1820, 15, "HIDE");                                // textul de pe buton
            hover_mode = 1;                                           // stergem dupa ce nu mai dam hover
            hover_tab = 9;
        }

    }
    else if (x >= 1800 && x <= 1920 && y >= 413 && y <= 463 && (hover_tab == 10 || hover_tab == 0))              //ZOOM HOVER
    {
        if (!hover_mode)
        {
            if (!mute)
                PlaySound("Sounds\\click.wav", NULL, SND_ASYNC);
            Menu_maker(1800, 413, 1800, 463, 1920, 463, 1920, 413);                // coloram butonul
            outtextxy(1820, 15, "ZOOM");                                // textul de pe buton
            hover_mode = 1;                                           // stergem dupa ce nu mai dam hover
            hover_tab = 10;
        }

    }
    else if (x >= 1800 && x <= 1920 && y >= 464 && y <= 514 && (hover_tab == 11 || hover_tab == 0))              //LANGUAGE HOVER
    {
        if (!hover_mode)
        {
            if (!mute)
                PlaySound("Sounds\\click.wav", NULL, SND_ASYNC);
            Menu_maker(1800, 464, 1800, 514, 1920, 514, 1920, 464);                // coloram butonul
            outtextxy(1820, 15, "LANG");                                // textul de pe buton
            hover_mode = 1;                                           // stergem dupa ce nu mai dam hover
            hover_tab = 11;
        }

    }
    else if (hover_mode)
    {
        clear = 1;
        hover_mode = 0;
        draw_menu = 1;
        hover_tab = 0;
        setbkcolor(0);
    }
}

/////////////////// DISPLAY ///////////////////
void matrice()
{
    for(int i=0; i<400; i++)
        for(int j=0; j<400; j++)
            matrice_tabla[i][j]=0;
    for(int i=1; i<=nb_of_piese; i++)
        matrice_tabla[100+piese[i].y][100+piese[i].x]=-1*piese[i].tip;
}
void Display()
{
    switch (color)
    {
    case 1:
        setcolor(BLUE);
        break;
    case 2:
        setcolor(RED);
        break;
    case 3:
        setcolor(LIGHTGREEN);
        break;
    case 4:
        setcolor(YELLOW);
        break;
    case 5:
        setcolor(LIGHTMAGENTA);
        break;
    case 6:
        setcolor(WHITE);
        break;
    }

    for (int i = 1; i <= nb_of_piese; i++)
    {
        if (piese[i].x * 10 * zoom_level < 1800)
            if (zoom_level == 7 && piese[i].x * 10 * zoom_level < 1700 || zoom_level == 8 && piese[i].x * 10 * zoom_level < 1700 || zoom_level < 7 || zoom_level > 8)
                switch (piese[i].tip)
                {
                case 1:
                    draw_tranzistor(piese[i].x, piese[i].y, piese[i].rotation);
                    break;
                case 2:
                    draw_diode(piese[i].x, piese[i].y, piese[i].rotation);
                    break;
                case 3:
                    draw_ampermetru(piese[i].x, piese[i].y, piese[i].rotation);
                    break;
                case 4:
                    draw_condenser(piese[i].x, piese[i].y, piese[i].rotation);
                    break;
                case 5:
                    draw_ground(piese[i].x, piese[i].y, piese[i].rotation);
                    break;
                case 6:
                    draw_lamp(piese[i].x, piese[i].y, piese[i].rotation);
                    break;
                case 7:
                    draw_potentiometer(piese[i].x, piese[i].y, piese[i].rotation);
                    break;
                case 8:
                    draw_power_source(piese[i].x, piese[i].y, piese[i].rotation);
                    break;
                case 9:
                    draw_switch(piese[i].x, piese[i].y, piese[i].rotation,piese[i].on);
                    break;
                case 10:
                    draw_voltmetru(piese[i].x, piese[i].y, piese[i].rotation);
                    break;
                case 11:
                    draw_resistor(piese[i].x, piese[i].y, piese[i].rotation);
                    break;
                }
        //matrice_tabla[100+piese[i].y][100+piese[i].x]=-1*piese[i].tip;
    }

    matrice();

    int di[]= {0,-1,0,1};
    int dj[]= {1,0,-1,0};

    int disus[]= {-1,0,1,0};
    int djsus[]= {0,-1,0,1};
    for(int i=1; i<=nb_of_wires; i++)
    {
        int x1,y1;
        if(wires[i].info1==3)
        {
            x1=100+piese[wires[i].poz1].x+djsus[piese[wires[i].poz1].rotation];
            y1=100+piese[wires[i].poz1].y+disus[piese[wires[i].poz1].rotation];
            if(((x1-100)*10*zoom_level)<1800)
                draw_linie_stg(piese[wires[i].poz1].x,piese[wires[i].poz1].y,(piese[wires[i].poz1].rotation+3)%4);
        }
        else if(wires[i].info1==2)
        {
            x1=100+piese[wires[i].poz1].x+dj[piese[wires[i].poz1].rotation];
            y1=100+piese[wires[i].poz1].y+di[piese[wires[i].poz1].rotation];
            if(((x1-100)*10*zoom_level)<1800)
                draw_linie_dr(piese[wires[i].poz1].x,piese[wires[i].poz1].y,piese[wires[i].poz1].rotation);
        }
        else
        {
            x1=100+piese[wires[i].poz1].x-dj[piese[wires[i].poz1].rotation];
            y1=100+piese[wires[i].poz1].y-di[piese[wires[i].poz1].rotation];
            if(((x1-100)*10*zoom_level)<1800)
                draw_linie_stg(piese[wires[i].poz1].x,piese[wires[i].poz1].y,piese[wires[i].poz1].rotation);
        }

        int x2,y2;


        if(wires[i].info2==3)
        {
            x2=100+piese[wires[i].poz2].x+djsus[piese[wires[i].poz2].rotation];
            y2=100+piese[wires[i].poz2].y+disus[piese[wires[i].poz2].rotation];
            if(((x2-100)*10*zoom_level)<1800)
                draw_linie_stg(piese[wires[i].poz2].x,piese[wires[i].poz2].y,(piese[wires[i].poz2].rotation+3)%4);
        }
        else if(wires[i].info2==2)
        {
            x2=100+piese[wires[i].poz2].x+dj[piese[wires[i].poz2].rotation];
            y2=100+piese[wires[i].poz2].y+di[piese[wires[i].poz2].rotation];
            if(((x2-100)*10*zoom_level)<1800)
                draw_linie_dr(piese[wires[i].poz2].x,piese[wires[i].poz2].y,piese[wires[i].poz2].rotation);
        }
        else
        {
            x2=100+piese[wires[i].poz2].x-dj[piese[wires[i].poz2].rotation];
            y2=100+piese[wires[i].poz2].y-di[piese[wires[i].poz2].rotation];
            if(((x2-100)*10*zoom_level)<1800)
                draw_linie_stg(piese[wires[i].poz2].x,piese[wires[i].poz2].y,piese[wires[i].poz2].rotation);
        }
        //if(((x1-100)*10*zoom_level)< 1800 and ((x2-100)*10*zoom_level)< 1800)
        connectare(x1,y1,x2,y2);
    }
    setcolor(BLACK);
}

int main()
{
    srand((unsigned)time(0));
    initwindow(width, height, "Electron");
    Initialization();


    while (!Menu_Exit)
    {
        Start_Menu();
    }

    while (!EXIT)
    {

        Display();
        Map();
        Controls();
        Menu();
        Logic();

        Sleep(1);      // 16 ms = 1000/60 (1000 ms = 1 sec).... 60 FPS
    }
    Exit_Transition();
    End_screen();
}

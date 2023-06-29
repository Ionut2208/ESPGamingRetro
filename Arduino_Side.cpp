#include <MCUFRIEND_kbv.h>
#include "TouchScreen.h"
#include <EEPROM.h>

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GOLD    0xEA8B02
#define GRAY  0xCCCCFF
#define L_YELLOW 0xCCCC00
#define PURPLE 0xCC0099

#define XP 7
#define YP A2
#define XM A1
#define YM 6

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint p;

String dateSerial;

struct profil
{
    char username[10], parola[15];
    int Level = 1, XPLevel = 0;
    int HighScoreWordle = 0, HighScoreGuess = 0, HighScoreArrow = 0;
    int username_len = 0, password_len = 0;

} user[4];

void(*resetFunc) (void) = 0;


int ic = 0, jc = -1;
String cuvant;
char input[6];
String cuvinte[100];
int indCuv;
struct patrate
{
    int x, y, l, c;
    char litera;
} grid[5][5];


void initCuvinte()
{
    cuvinte[0] = "ABATE";
    cuvinte[1] = "ACASA";
    cuvinte[2] = "ACEST";
    cuvinte[3] = "ALEGE";
    cuvinte[4] = "BALTA";
    cuvinte[5] = "BRUSC";
    cuvinte[6] = "BUTON";
    cuvinte[7] = "BILET";
    cuvinte[8] = "CAFEA";
    cuvinte[9] = "CAIET";
    cuvinte[10] = "CAUZA";
    cuvinte[11] = "COPIL";
    cuvinte[12] = "DULCE";
    cuvinte[13] = "DIVIN";
    cuvinte[14] = "DRONA";
    cuvinte[15] = "DOLAR";
    cuvinte[16] = "ECRAN";
    cuvinte[17] = "EFECT";
    cuvinte[18] = "EFORT";
    cuvinte[19] = "EROIC";
    cuvinte[20] = "FAIMA";
    cuvinte[21] = "FAPTA";
    cuvinte[22] = "FARSA";
    cuvinte[23] = "FIZIC";
    cuvinte[24] = "GARDA";
    cuvinte[25] = "GARAJ";
    cuvinte[26] = "GAZDA";
    cuvinte[27] = "GENIU";
    cuvinte[28] = "HAINE";
    cuvinte[29] = "HAITA";
    cuvinte[30] = "HOTAR";
    cuvinte[31] = "HARTA";
    cuvinte[32] = "IDEAL";
    cuvinte[33] = "IDILA";
    cuvinte[34] = "IERTA";
    cuvinte[35] = "IMENS";
    cuvinte[36] = "JEFUI";
    cuvinte[37] = "JELEU";
    cuvinte[38] = "JOACA";
    cuvinte[39] = "JURAT";
    cuvinte[40] = "LACOM";
    cuvinte[41] = "LALEA";
    cuvinte[42] = "LOGIC";
    cuvinte[43] = "LOIAL";
    cuvinte[44] = "MAGIC";
    cuvinte[45] = "MAGIE";
    cuvinte[46] = "MATUR";
    cuvinte[47] = "MENAJ";
    cuvinte[48] = "NATAL";
    cuvinte[49] = "NICIO";
    cuvinte[50] = "NEGRU";
    cuvinte[51] = "OASTE";
    cuvinte[52] = "OBOSI";
    cuvinte[53] = "ORDIN";
    cuvinte[54] = "ORICE";
    cuvinte[55] = "PALAT";
    cuvinte[56] = "PALMA";
    cuvinte[57] = "PANOU";
    cuvinte[58] = "PICTA";
    cuvinte[59] = "REGLA";
    cuvinte[60] = "ROATA";
    cuvinte[61] = "ROBOT";
    cuvinte[62] = "ROSTI";
    cuvinte[63] = "SALUT";
    cuvinte[64] = "SCARA";
    cuvinte[65] = "SEVER";
    cuvinte[66] = "SFERA";
    cuvinte[67] = "TABEL";
    cuvinte[68] = "TIPIC";
    cuvinte[69] = "TRUPA";
    cuvinte[70] = "TRUDA";
    cuvinte[71] = "UMBRA";
    cuvinte[72] = "UNGHI";
    cuvinte[73] = "URBAN";
    cuvinte[74] = "UMPLE";
    cuvinte[75] = "VAGON";
    cuvinte[76] = "VALET";
    cuvinte[77] = "VALID";
    cuvinte[78] = "VENIN";
    cuvinte[79] = "ZADAR";
    cuvinte[80] = "ZARVA";
    cuvinte[81] = "ZEFIR";
    cuvinte[82] = "ZEBRA";
    cuvinte[83] = "ZODIE";
    cuvinte[84] = "VECIN";
    cuvinte[85] = "VESEL";
    cuvinte[86] = "TEAMA";
    cuvinte[87] = "TABLA";
    cuvinte[88] = "VECHI";
    cuvinte[89] = "VIFOR";
    cuvinte[90] = "SOLAR";
    cuvinte[91] = "SENIN";
    cuvinte[92] = "TIGRU";
    cuvinte[93] = "CREMA";
    cuvinte[94] = "CROIT";
    cuvinte[95] = "PROST";
    cuvinte[96] = "PITIT";
    cuvinte[97] = "RIGLA";
    cuvinte[98] = "DOCIL";
    cuvinte[99] = "FORJA";

}

void tastWordle(int slot)
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    tft.fillRect(0, 215, 239, 110, BLACK);
    tft.drawRect(5, 220, 185, 100, YELLOW);
    tft.setCursor(10, 230);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.println("QWERTYUIOP");
    tft.setCursor(20, 260);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.println("ASDFGHJKL");
    tft.setCursor(30, 290);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.println("ZXCVBNM");
    tft.fillRect(195, 280, 40, 30, GRAY);
    tft.setCursor(200, 285);
    tft.setTextColor(GREEN);
    tft.setTextSize(3);
    tft.print("OK");
    tft.fillRect(195, 245, 40, 30, GRAY);
    tft.setCursor(200, 250);
    tft.setTextColor(RED);
    tft.setTextSize(3);
    tft.print("<-");
    getTasteWordle(slot);
}


void displayCharPlay(char c)
{
    if (jc < 4)
    {
        pinMode(A1, OUTPUT);
        pinMode(A2, OUTPUT);
        jc++;
        tft.setCursor(grid[ic][jc].x + 10, grid[ic][jc].y + 7);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print(c);
        input[jc] = c;
    }

}

void check_word(int slot)
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    int fr[5] = { 0 };
    for (int i = 0; i < 5; i++)
    {

        if (cuvant[i] == input[i])
        {
            tft.fillRect(grid[ic][i].x, grid[ic][i].y, 35, 35, GREEN);
            tft.setCursor(grid[ic][i].x + 10, grid[ic][i].y + 7);
            tft.setTextSize(3);
            tft.setTextColor(WHITE);
            tft.print(input[i]);

        }
        else
        {
            int gasit = 0;
            for (int j = 0; j < 5; j++)
                if (cuvant[j] == input[i] && input[j] != cuvant[j] && fr[j] == 0)
                {
                    gasit = 1;
                    fr[j] = 1;
                    break;
                }
            if (gasit == 1)
            {
                tft.fillRect(grid[ic][i].x, grid[ic][i].y, 35, 35, YELLOW);

            }

            else
            {
                tft.fillRect(grid[ic][i].x, grid[ic][i].y, 35, 35, GRAY);

            }

            tft.setCursor(grid[ic][i].x + 10, grid[ic][i].y + 7);
            tft.setTextSize(3);
            tft.setTextColor(WHITE);
            tft.print(input[i]);
        }
    }
    int gasit = 1;
    for (int i = 0; i < 5; i++)
    {
        if (cuvant[i] != input[i])
        {
            gasit = 0;
            break;
        }
    }
    if (gasit == 1)
    {
        int score = 5 - ic;
        dateSerial += score;
        tft.fillRect(15, 10, 240, 100, GREEN);
        tft.setCursor(25, 20);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("Ai castigat!");
        delay(2000);
        profil var;
        int loc = 4;
        if (slot == 2)
            loc += sizeof(var);
        else if (slot == 3)
            loc += 2 * sizeof(var);
        EEPROM.get(loc, var);
        if (score > var.HighScoreWordle)
        {
            var.HighScoreWordle = score;
            EEPROM.put(loc, var);
            pinMode(A1, OUTPUT);
            pinMode(A2, OUTPUT);
            tft.setCursor(10, 100);
            tft.setTextSize(2);
            tft.setTextColor(RED);
            tft.print("(High Score nou)");
        }
        EEPROM.get(loc, var);
        Serial1.println(dateSerial);
        EcranProfil(slot);

    }
    ic++;
    jc = -1;

    if (ic == 5)
    {
        tft.fillRect(15, 10, 240, 100, RED);
        tft.setCursor(25, 20);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.print("Ai pierdut!");
        tft.setCursor(25, 50);
        tft.print(cuvant);
        delay(2000);
        EcranProfil(slot);
    }
}

void getTasteWordle(int slot)
{
    while (1)
    {
        TSPoint p = ts.getPoint();
        if (p.z > ts.pressureThreshhold)
        {
            if (p.x >= 790 && p.x <= 900 && p.y >= 750 && p.y <= 815)
            {
                if (jc >= 0)
                {
                    pinMode(A1, OUTPUT);
                    pinMode(A2, OUTPUT);
                    tft.fillRect(grid[ic][jc].x, grid[ic][jc].y, 35, 35, BLACK);
                    jc--;
                }

            }
            else if (p.x >= 790 && p.x <= 900 && p.y >= 845 && p.y <= 910)
            {
                check_word(slot);
            }
            else if (p.y >= 720 && p.y <= 780)
            {
                if (p.x >= 190 && p.x <= 240)
                    displayCharPlay('Q');
                else if (p.x >= 245 && p.x <= 295)
                    displayCharPlay('W');
                else if (p.x >= 300 && p.x <= 350)
                    displayCharPlay('E');
                else if (p.x >= 355 && p.x <= 405)
                    displayCharPlay('R');
                else if (p.x >= 410 && p.x <= 460)
                    displayCharPlay('T');
                else if (p.x >= 465 && p.x <= 515)
                    displayCharPlay('Y');
                else if (p.x >= 520 && p.x <= 570)
                    displayCharPlay('U');
                else if (p.x >= 575 && p.x <= 625)
                    displayCharPlay('I');
                else if (p.x >= 630 && p.x <= 680)
                    displayCharPlay('O');
                else if (p.x >= 685 && p.x <= 735)
                    displayCharPlay('P');

            }
            else if (p.y >= 790 && p.y <= 850)
            {
                if (p.x >= 220 && p.x <= 270)
                    displayCharPlay('A');
                else if (p.x >= 275 && p.x <= 325)
                    displayCharPlay('S');
                else if (p.x >= 330 && p.x <= 380)
                    displayCharPlay('D');
                else if (p.x >= 385 && p.x <= 435)
                    displayCharPlay('F');
                else if (p.x >= 440 && p.x <= 490)
                    displayCharPlay('G');
                else if (p.x >= 495 && p.x <= 545)
                    displayCharPlay('H');
                else if (p.x >= 550 && p.x <= 600)
                    displayCharPlay('J');
                else if (p.x >= 605 && p.x <= 655)
                    displayCharPlay('K');
                else if (p.x >= 660 && p.x <= 710)
                    displayCharPlay('L');
            }
            else if (p.y >= 860 && p.y <= 920)
            {
                if (p.x >= 250 && p.x <= 300)
                    displayCharPlay('Z');
                else if (p.x >= 305 && p.x <= 355)
                    displayCharPlay('X');
                else if (p.x >= 360 && p.x <= 410)
                    displayCharPlay('C');
                else if (p.x >= 415 && p.x <= 465)
                    displayCharPlay('V');
                else if (p.x >= 470 && p.x <= 520)
                    displayCharPlay('B');
                else if (p.x >= 525 && p.x <= 575)
                    displayCharPlay('N');
                else if (p.x >= 580 && p.x <= 630)
                    displayCharPlay('M');
            }
        }
        delay(300);
    }
}

void StartWordle(int slot)
{
    randomSeed(analogRead(A8));
    int indCuv = random(100);
    cuvant = cuvinte[indCuv];
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    tft.fillScreen(WHITE);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
        {
            int x = j * 40 + 20;
            int l = 35;
            int y = 40 * i + 5;
            int c = BLACK;
            grid[i][j].x = x;
            grid[i][j].y = y;
            grid[i][j].l = l;
            grid[i][j].c = c;
            tft.fillRect(x, y, l, l, c);
        }
    tastWordle(slot);
}

void IntroWordle(int slot)
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    tft.fillScreen(BLACK);
    tft.setCursor(50, 20);
    tft.setTextColor(GOLD);
    tft.setTextSize(4);
    tft.print("WORDLE");
    tft.fillRect(15, 80, 50, 50, GRAY);
    tft.setCursor(75, 90);
    tft.setTextColor(GRAY);
    tft.setTextSize(2);
    tft.print("Nu exista          in cuvant");
    tft.setCursor(30, 90);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.print("A");
    tft.fillRect(15, 140, 50, 50, YELLOW);
    tft.setCursor(75, 150);
    tft.setTextColor(YELLOW);
    tft.setTextSize(2);
    tft.print("Exista in          alta pozitie");
    tft.setCursor(30, 150);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.print("A");
    tft.fillRect(15, 200, 50, 50, GREEN);
    tft.setCursor(75, 210);
    tft.setTextColor(GREEN);
    tft.setTextSize(2);
    tft.print("Se afla            la locul ei");
    tft.setCursor(30, 210);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.print("A");
    tft.fillRect(60, 260, 120, 50, RED);
    tft.setCursor(62, 270);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.print("START");

    while (1)
    {
        TSPoint p = ts.getPoint();
        if (p.z > ts.pressureThreshhold) {
            if (p.x >= 335 && p.x <= 740 && p.y >= 790 && p.y <= 905)
            {
                initCuvinte();
                StartWordle(slot);
                break;
            }
        }
    }

}


void resetare()
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);

    tft.fillRect(0, 40, 239, 130, RED);
    tft.setCursor(5, 45);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print("Este necesara      repornirea pentru  salvarea/stergerea profilului");

    tft.fillRect(85, 135, 70, 30, GRAY);
    tft.setCursor(107, 143);
    tft.setTextSize(2);
    tft.setTextColor(BLUE);
    tft.print("OK");

    while (1)
    {
        TSPoint p = ts.getPoint();

        // we have some minimum pressure we consider 'valid'
        // pressure of 0 means no pressing!
        if (p.z > ts.pressureThreshhold) {
            if (p.x >= 420 && p.x <= 650 && p.y >= 490 && p.y <= 555)
            {
                pinMode(A1, OUTPUT);
                pinMode(A2, OUTPUT);
                tft.fillRect(0, 40, 239, 130, RED);
                tft.setCursor(5, 45);
                tft.setTextSize(2);
                tft.setTextColor(WHITE);
                tft.print("Repornire in ");
                for (int i = 5; i >= 1; i--)
                {
                    tft.setCursor(170, 45);
                    tft.print(i);
                    delay(1000);
                    tft.fillRect(165, 40, 20, 20, RED);

                }
                resetFunc();
                break;
            }
        }

    }

}

void localOrWeb(int mod)
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);

    tft.fillScreen(BLUE);

    tft.fillRect(0, 0, 60, 20, RED);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setCursor(5, 5);
    tft.print("BACK");

    tft.fillRect(0, 40, 60, 60, GRAY);

    tft.setCursor(75, 65);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print("Prin ecran");

    tft.fillRect(0, 120, 60, 60, GRAY);
    tft.setCursor(70, 145);
    tft.print("Prin server");

    while (1)
    {
        TSPoint p = ts.getPoint();
        if (p.z > ts.pressureThreshhold)
        {
            if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
            {
                MainMenu();
                break;
            }
            else if (p.x >= 160 && p.x <= 325)
            {
                if (p.y >= 260 && p.y <= 390)
                {
                    if (mod == 1)
                        MeniuAdaugaProfil();
                    else if (mod == 2)
                        MeniuIncarcaProfil();
                    else if (mod == 3)
                        MeniuStergeProfil();
                    break;
                }
                else if (p.y >= 445 && p.y <= 575)
                {
                    if (mod == 1)
                        WebAdauga();
                    else if (mod == 2)
                        WebIncarca();
                    else if (mod == 3)
                        WebSterge();
                    break;
                }
            }
        }
        delay(300);
    }


}

void WebAdauga()
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    tft.fillScreen(BLUE);
    tft.setCursor(5, 5);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("Intra intr-un      browser web pe     192.168.24.55, da  click pe butonul   \"Adauga profil\",   selecteaza un slot gol apoi introdu unusername si        o parola.");
    String query = "";
    while (query == "")
    {
        tft.fillRect(5, 245, 240, 70, BLUE);
        tft.setCursor(5, 245);
        tft.print("Se asteapta");
        delay(1000);
        tft.setCursor(5, 245);
        tft.print("Se asteapta.");
        delay(1000);
        tft.setCursor(5, 245);
        tft.print("Se asteapta..");
        delay(1000);
        tft.setCursor(5, 245);
        tft.print("Se asteapta...");
        delay(1000);
        query = Serial1.readString();
    }
    char queryc[105];
    query.toCharArray(queryc, sizeof(queryc));
    char* tip = strtok(queryc, " ");
    char* username = strtok(NULL, " ");
    char* password = strtok(NULL, " ");
    if (strcmp(tip, "REGISTER1") == 0)
    {
        strcpy(user[0].username, username);
        strcpy(user[0].parola, password);
        EEPROM.put(4, user[0]);
        EEPROM.update(0, 1);
    }
    else if (strcmp(tip, "REGISTER2") == 0)
    {
        strcpy(user[1].username, username);
        strcpy(user[1].parola, password);
        int loc = 4;
        loc += sizeof(user[0]);
        EEPROM.put(loc, user[1]);
        EEPROM.update(1, 1);
    }
    else if (strcmp(tip, "REGISTER3") == 0)
    {
        strcpy(user[2].username, username);
        strcpy(user[2].parola, password);
        int loc = 4;
        loc += sizeof(user[0]);
        loc += sizeof(user[1]);
        EEPROM.put(loc, user[2]);
        EEPROM.update(2, 1);
    }
    resetare();
}

void WebIncarca()
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    tft.fillScreen(BLUE);
    tft.setCursor(5, 5);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("Intra intr-un      browser web pe     192.168.24.55, da  click pe butonul   \"Incarca profil\",  selecteaza slot-ul cu profilul dorit  apoi introdu parola");
    String query = "";
    while (query == "")
    {
        tft.fillRect(5, 245, 240, 70, BLUE);
        tft.setCursor(5, 245);
        tft.print("Se asteapta");
        delay(1000);
        tft.setCursor(5, 245);
        tft.print("Se asteapta.");
        delay(1000);
        tft.setCursor(5, 245);
        tft.print("Se asteapta..");
        delay(1000);
        tft.setCursor(5, 245);
        tft.print("Se asteapta...");
        delay(1000);
        query = Serial1.readString();
    }
    Serial.println(query);
    if (query.indexOf("LOGIN1") != -1)
    {
        Serial.println("DA LOGIN1");
        EcranProfil(1);
    }

    else if (query.indexOf("LOGIN2") != -1)
    {
        Serial.println("DA LOGIN2");
        EcranProfil(2);
    }
    else if (query.indexOf("LOGIN3") != -1)
    {
        Serial.println("DA LOGIN3");
        EcranProfil(3);
    }


}

void WebSterge()
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    tft.fillScreen(BLUE);
    tft.setCursor(5, 5);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("Intra intr-un      browser web pe     192.168.24.55, da  click pe butonul   \"Sterge profil\",   selecteaza slot-ul cu profilul dorit  apoi introdu parola");
    String query = "";
    while (query == "")
    {
        tft.fillRect(5, 245, 240, 70, BLUE);
        tft.setCursor(5, 245);
        tft.print("Se asteapta");
        delay(1000);
        tft.setCursor(5, 245);
        tft.print("Se asteapta.");
        delay(1000);
        tft.setCursor(5, 245);
        tft.print("Se asteapta..");
        delay(1000);
        tft.setCursor(5, 245);
        tft.print("Se asteapta...");
        delay(1000);
        query = Serial1.readString();
    }

    if (query.indexOf("DELETE1") != -1)
    {
        DeleteProfile(1);
    }

    else if (query.indexOf("DELETE2") != -1)
    {
        DeleteProfile(2);
    }
    else if (query.indexOf("DELETE3") != -1)
    {
        DeleteProfile(3);
    }
}

void transmiteDate()
{
    String dateLogare = "";
    if (EEPROM.read(0) == 0)
    {
        tft.setCursor(60, 70);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        dateLogare += "EMPTY EMPTY ";
    }
    else
    {

        profil var;
        EEPROM.get(4, var);
        tft.setCursor(60, 70);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        dateLogare += var.username;
        dateLogare += " ";
        dateLogare += var.parola;
        dateLogare += " ";

    }

    if (EEPROM.read(1) == 0)
    {
        tft.setCursor(60, 160);
        tft.print("(slot gol)");
        dateLogare += "EMPTY EMPTY ";
    }
    else
    {

        profil var;
        int location = 4;
        location += sizeof(var);
        EEPROM.get(location, var);
        tft.setCursor(60, 160);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        dateLogare += var.username;
        dateLogare += " ";
        dateLogare += var.parola;
        dateLogare += " ";
    }

    if (EEPROM.read(2) == 0)
    {
        tft.setCursor(60, 250);
        dateLogare += "EMPTY EMPTY ";
    }
    else
    {

        profil var;
        int location = 4;
        location += 2 * sizeof(var);
        EEPROM.get(location, var);
        tft.setCursor(60, 250);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        dateLogare += var.username;
        dateLogare += " ";
        dateLogare += var.parola;
        dateLogare += " ";
    }
    /**for(int i = 0; i < dateLogare.length(); i++)
      {
        Serial.print(i);
        Serial.print(": ");
        Serial.print(dateLogare[i]);
        Serial.print('\n');
      } **/
    Serial1.println(dateLogare);
}

void MainMenu()
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);

    tft.fillScreen(BLUE);

    tft.fillRect(0, 0, 60, 20, RED);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setCursor(5, 5);
    tft.print("BACK");

    tft.fillRect(0, 40, 60, 60, GRAY);
    tft.fillRect(25, 50, 10, 40, BLACK);
    tft.fillRect(10, 65, 40, 10, BLACK);

    tft.setCursor(75, 65);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print("Adauga profil");

    tft.fillRect(0, 120, 60, 60, GRAY);
    tft.fillRect(10, 145, 20, 10, BLACK);
    tft.fillTriangle(30, 135, 30, 165, 50, 150, BLACK);
    tft.setCursor(70, 145);
    tft.print("Incarca profil");

    tft.fillRect(0, 200, 60, 60, GRAY);
    int x1 = 5, y1 = 210, x2 = 50, y2 = 250;
    for (int i = 1; i <= 7; i++)
        tft.drawLine(x1++, y1, x2++, y2, BLACK);
    x1 = 50;
    y1 = 210;
    x2 = 5;
    y2 = 250;
    for (int i = 1; i <= 7; i++)
        tft.drawLine(x1++, y1, x2++, y2, BLACK);
    tft.setCursor(75, 225);
    tft.print("Sterge profil");

    getTastePlay();
}

void getTastePlay()
{
    while (1)
    {
        TSPoint p = ts.getPoint();
        if (p.z > ts.pressureThreshhold)
        {
            if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
            {
                MainMenu();
                break;
            }
            else if (p.x >= 160 && p.x <= 325)
            {
                if (p.y >= 260 && p.y <= 390)
                {
                    localOrWeb(1);
                    //MeniuAdaugaProfil();
                    break;
                }
                else if (p.y >= 445 && p.y <= 575)
                {
                    localOrWeb(2);
                    //MeniuIncarcaProfil();
                    break;
                }
                else if (p.y >= 630 && p.y <= 760)
                {
                    localOrWeb(3);
                    //MeniuStergeProfil();
                    break;
                }
            }
        }
        delay(300);
    }
}

void MeniuAdaugaProfil()
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);

    tft.fillScreen(BLUE);

    tft.fillRect(0, 0, 60, 20, RED);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setCursor(5, 5);
    tft.print("BACK");

    tft.drawRect(0, 40, 240, 80, YELLOW);
    tft.drawRect(0, 130, 240, 80, YELLOW);
    tft.drawRect(0, 220, 240, 80, YELLOW);

    if (EEPROM.read(0) == 0)
    {
        tft.setCursor(60, 70);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print("(slot gol)");
    }
    else
    {

        profil var;
        EEPROM.get(4, var);
        tft.setCursor(60, 70);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print(var.username);

    }

    if (EEPROM.read(1) == 0)
    {
        tft.setCursor(60, 160);
        tft.print("(slot gol)");
    }
    else
    {

        profil var;
        int location = 4;
        location += sizeof(var);
        EEPROM.get(location, var);
        tft.setCursor(60, 160);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print(var.username);
    }

    if (EEPROM.read(2) == 0)
    {
        tft.setCursor(60, 250);
        tft.print("(slot gol)");
    }
    else
    {

        profil var;
        int location = 4;
        location += 2 * sizeof(var);
        EEPROM.get(location, var);
        tft.setCursor(60, 250);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print(var.username);
    }
    GetTasteMeniuAdd();
}

void MeniuIncarcaProfil()
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);

    tft.fillScreen(BLUE);

    tft.fillRect(0, 0, 60, 20, RED);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setCursor(5, 5);
    tft.print("BACK");

    tft.drawRect(0, 40, 240, 80, YELLOW);
    tft.drawRect(0, 130, 240, 80, YELLOW);
    tft.drawRect(0, 220, 240, 80, YELLOW);

    if (EEPROM.read(0) == 0)
    {
        tft.setCursor(60, 70);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print("(slot gol)");
    }
    else
    {

        profil var;
        EEPROM.get(4, var);
        tft.setCursor(60, 70);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print(var.username);

    }

    if (EEPROM.read(1) == 0)
    {
        tft.setCursor(60, 160);
        tft.print("(slot gol)");
    }
    else
    {

        profil var;
        int location = 4;
        location += sizeof(var);
        EEPROM.get(location, var);
        tft.setCursor(60, 160);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print(var.username);
    }

    if (EEPROM.read(2) == 0)
    {
        tft.setCursor(60, 250);
        tft.print("(slot gol)");
    }
    else
    {

        profil var;
        int location = 4;
        location += 2 * sizeof(var);
        EEPROM.get(location, var);
        tft.setCursor(60, 250);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print(var.username);
    }
    GetTasteMeniuLoad();
}

void MeniuStergeProfil()
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);

    tft.fillScreen(BLUE);

    tft.fillRect(0, 0, 60, 20, RED);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setCursor(5, 5);
    tft.print("BACK");

    tft.drawRect(0, 40, 240, 80, YELLOW);
    tft.drawRect(0, 130, 240, 80, YELLOW);
    tft.drawRect(0, 220, 240, 80, YELLOW);

    if (EEPROM.read(0) == 0)
    {
        tft.setCursor(60, 70);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print("(slot gol)");
    }
    else
    {

        profil var;
        EEPROM.get(4, var);
        tft.setCursor(60, 70);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print(var.username);

    }

    if (EEPROM.read(1) == 0)
    {
        tft.setCursor(60, 160);
        tft.print("(slot gol)");
    }
    else
    {

        profil var;
        int location = 4;
        location += sizeof(var);
        EEPROM.get(location, var);
        tft.setCursor(60, 160);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print(var.username);
    }

    if (EEPROM.read(2) == 0)
    {
        tft.setCursor(60, 250);
        tft.print("(slot gol)");
    }
    else
    {

        profil var;
        int location = 4;
        location += 2 * sizeof(var);
        EEPROM.get(location, var);
        tft.setCursor(60, 250);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print(var.username);
    }
    GetTasteMeniuDelete();
}

void GetTasteMeniuAdd()
{

    while (1)
    {
        TSPoint p = ts.getPoint();
        if (p.z > ts.pressureThreshhold)
        {

            if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
            {
                MainMenu();
                break;
            }
            else if (p.x >= 160 && p.x <= 925)
            {
                if (p.y >= 250 && p.y <= 440)
                {
                    if (EEPROM.read(0) == 1)
                    {
                        pinMode(A1, OUTPUT);
                        pinMode(A2, OUTPUT);

                        tft.fillRect(0, 100, 239, 100, YELLOW);
                        tft.setTextSize(2);
                        tft.setTextColor(BLACK);
                        tft.setCursor(5, 110);
                        tft.print("Profilul aflat pe  slot va fi sters.  Continuati?");
                        tft.fillRect(20, 165, 60, 30, BLACK);
                        tft.fillRect(160, 165, 60, 30, BLACK);
                        tft.setCursor(35, 173);
                        tft.setTextColor(WHITE);
                        tft.print("DA");
                        tft.setCursor(175, 173);
                        tft.print("NU");
                        while (1)
                        {
                            TSPoint p = ts.getPoint();
                            if (p.z > ts.pressureThreshhold)
                            {

                                if (p.y >= 555 && p.y <= 630)
                                {
                                    if (p.x >= 215 && p.x <= 390)
                                    {
                                        for (int i = 0; i < user[0].username_len; i++)
                                            user[0].username[i] = 0;
                                        for (int i = 0; i < user[0].password_len; i++)
                                            user[0].parola[i] = 0;
                                        user[0].username_len = 0;
                                        user[0].password_len = 0;
                                        CreateProfile(1);
                                        break;
                                    }
                                    else if (p.x >= 660 && p.x <= 845)
                                    {
                                        MeniuAdaugaProfil();
                                        break;
                                    }
                                }

                            }
                        }
                    }
                    else
                    {
                        CreateProfile(1);
                        break;
                    }
                }
                else if (p.y >= 470 && p.y <= 660)
                {
                    if (EEPROM.read(1) == 1)
                    {
                        pinMode(A1, OUTPUT);
                        pinMode(A2, OUTPUT);

                        tft.fillRect(0, 100, 239, 100, YELLOW);
                        tft.setTextSize(2);
                        tft.setTextColor(BLACK);
                        tft.setCursor(5, 110);
                        tft.print("Slot-ul nu este gol, iar profilul aflat pe slot va fi sters. Continuati?");
                        tft.fillRect(20, 165, 60, 30, BLACK);
                        tft.fillRect(160, 165, 60, 30, BLACK);
                        tft.setCursor(35, 173);
                        tft.setTextColor(WHITE);
                        tft.print("DA");
                        tft.setCursor(175, 173);
                        tft.print("NU");
                        while (1)
                        {
                            TSPoint p = ts.getPoint();
                            if (p.z > ts.pressureThreshhold)
                            {

                                if (p.y >= 555 && p.y <= 630)
                                {
                                    if (p.x >= 215 && p.x <= 390)
                                    {
                                        CreateProfile(2);
                                        break;
                                    }
                                    else if (p.x >= 660 && p.x <= 845)
                                    {
                                        MeniuAdaugaProfil();
                                        break;
                                    }
                                }

                            }
                        }
                    }
                    else
                    {
                        CreateProfile(2);
                        break;
                    }
                }
                else if (p.y >= 690 && p.y <= 880)
                {
                    if (EEPROM.read(2) == 1)
                    {
                        pinMode(A1, OUTPUT);
                        pinMode(A2, OUTPUT);

                        tft.fillRect(0, 100, 239, 100, YELLOW);
                        tft.setTextSize(2);
                        tft.setTextColor(BLACK);
                        tft.setCursor(5, 110);
                        tft.print("Slot-ul nu este gol, iar profilul aflat pe slot va fi sters. Continuati?");
                        tft.fillRect(20, 165, 60, 30, BLACK);
                        tft.fillRect(160, 165, 60, 30, BLACK);
                        tft.setCursor(35, 173);
                        tft.setTextColor(WHITE);
                        tft.print("DA");
                        tft.setCursor(175, 173);
                        tft.print("NU");
                        while (1)
                        {
                            TSPoint p = ts.getPoint();
                            if (p.z > ts.pressureThreshhold)
                            {

                                if (p.y >= 555 && p.y <= 630)
                                {
                                    if (p.x >= 215 && p.x <= 390)
                                    {
                                        CreateProfile(3);
                                        break;
                                    }
                                    else if (p.x >= 660 && p.x <= 845)
                                    {
                                        MeniuAdaugaProfil();
                                        break;
                                    }
                                }

                            }
                        }
                    }
                    else
                    {
                        CreateProfile(3);
                        break;
                    }
                }
            }
        }
        delay(300);
    }
}

void CreateProfile(int slot)
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);



    tft.fillScreen(BLUE);
    tft.fillRect(0, 0, 60, 20, RED);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setCursor(5, 5);
    tft.print("BACK");
    tft.setCursor(0, 30);
    tft.setTextSize(2);
    tft.print("Username");
    tft.fillRect(0, 50, 240, 30, WHITE);
    tft.setCursor(0, 115);
    tft.print("Parola");
    tft.fillRect(0, 135, 240, 30, WHITE);
    TastLitereProfil();
    GetTasteNewProfile(slot);


}

void TastLitereProfil()
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    tft.fillRect(0, 170, 239, 150, BLUE);
    tft.drawRect(5, 185, 185, 120, YELLOW);
    tft.setCursor(10, 190);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.println("QWERTYUIOP");
    tft.setCursor(20, 220);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.println("ASDFGHJKL");
    tft.setCursor(30, 250);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.println("ZXCVBNM");
    tft.fillRect(195, 280, 40, 30, GRAY);
    tft.setCursor(200, 285);
    tft.setTextColor(GREEN);
    tft.setTextSize(3);
    tft.print("OK");
    tft.fillRect(195, 200, 40, 30, GRAY);
    tft.setCursor(200, 205);
    tft.setTextColor(RED);
    tft.setTextSize(3);
    tft.print("<-");
    tft.fillRect(195, 240, 40, 30, GRAY);
    tft.setCursor(200, 245);
    tft.setTextColor(MAGENTA);
    tft.setTextSize(3);
    tft.print("?1");
    tft.setCursor(50, 280);
    tft.setTextColor(BLACK);
    tft.setTextSize(3);
    tft.print("SPACE");
    tft.drawRect(45, 275, 100, 30, YELLOW);

    tft.fillRect(0, 0, 60, 20, RED);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setCursor(5, 5);
    tft.print("BACK");

    tft.setTextSize(2);

}

void TastCifProfil()
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    tft.fillRect(0, 170, 239, 150, BLUE);
    tft.drawRect(5, 185, 185, 120, YELLOW);
    tft.setCursor(10, 190);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.println("1234567890");
    tft.setCursor(10, 220);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.println("@.$_&-+()/");
    tft.setCursor(10, 250);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.println("<*':;!?=%>");
    tft.setCursor(10, 280);
    tft.print(',');
    tft.setCursor(150, 280);
    tft.print('\"');
    tft.fillRect(195, 280, 40, 30, GRAY);
    tft.setCursor(200, 285);
    tft.setTextColor(GREEN);
    tft.setTextSize(3);
    tft.print("OK");
    tft.fillRect(195, 200, 40, 30, GRAY);
    tft.setCursor(200, 205);
    tft.setTextColor(RED);
    tft.setTextSize(3);
    tft.print("<-");
    tft.fillRect(195, 240, 40, 30, GRAY);
    tft.setCursor(200, 245);
    tft.setTextColor(MAGENTA);
    tft.setTextSize(3);
    tft.print("AB");
    tft.setCursor(52, 280);
    tft.setTextColor(BLACK);
    tft.setTextSize(3);
    tft.print("SPACE");
    tft.drawRect(45, 275, 100, 30, YELLOW);

    tft.setTextSize(2);
}

void chenar(bool isPassword)
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    if (!isPassword)
    {
        tft.fillRect(0, 25, 100, 25, BLACK);
        tft.setCursor(0, 30);
        tft.setTextColor(WHITE);
        tft.print("Username");
    }
    else
    {
        tft.fillRect(0, 110, 100, 25, BLACK);
        tft.setCursor(0, 115);
        tft.setTextColor(WHITE);
        tft.print("Parola");
        tft.fillRect(0, 25, 100, 25, BLUE);
        tft.setCursor(0, 30);
        tft.setTextColor(WHITE);
        tft.print("Username");
    }
}

void textboxPass()
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);

    tft.fillRect(0, 135, 240, 30, WHITE);
}

void textboxUser()
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);

    tft.fillRect(0, 50, 240, 30, WHITE);
}

void afisareSirProfil(int slot, bool isPassword)
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    tft.setTextColor(BLACK);
    tft.setTextSize(2);

    if (isPassword)
    {
        tft.setCursor(5, 143);
        for (int i = 0; i < user[slot - 1].password_len - 1; i++)
            tft.print('*');
        tft.print(user[slot - 1].parola[user[slot - 1].password_len - 1]);
        delay(500);
        textboxPass();
        tft.setCursor(5, 143);
        for (int i = 0; i < user[slot - 1].password_len; i++)
            tft.print('*');

    }
    else
    {
        tft.setCursor(5, 57);
        for (int i = 0; i < user[slot - 1].username_len; i++)
            tft.print(user[slot - 1].username[i]);
    }
}

void displayUserAndPass(int slot, char c, bool isPassword)
{
    if (isPassword)
        user[slot - 1].parola[user[slot - 1].password_len++] = c;
    else
        user[slot - 1].username[user[slot - 1].username_len++] = c;
    afisareSirProfil(slot, isPassword);
}

void GetTasteNewProfile(int slot)
{
    int mode = 1;
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    bool isPassword = false;
    chenar(isPassword);
    while (1)
    {

        TSPoint p = ts.getPoint();

        // we have some minimum pressure we consider 'valid'
        // pressure of 0 means no pressing!
        if (p.z > ts.pressureThreshhold) {

            if (mode == 1)
            {
                if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
                {

                    if (isPassword)
                    {
                        textboxPass();
                        user[slot - 1].password_len--;
                        user[slot - 1].parola[user[slot - 1].password_len] = 0;
                        pinMode(A1, OUTPUT);
                        pinMode(A2, OUTPUT);
                        tft.setCursor(5, 143);
                        for (int i = 0; i < user[slot - 1].password_len; i++)
                            tft.print('*');
                    }
                    else
                    {
                        textboxUser();
                        user[slot - 1].username_len--;
                        user[slot - 1].username[user[slot - 1].username_len] = 0;
                        afisareSirProfil(slot, isPassword);
                    }
                }
                else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
                {
                    if (!isPassword)
                    {
                        isPassword = true;
                        chenar(isPassword);

                    }
                    else
                    {
                        if (slot == 1)
                        {
                            EEPROM.put(4, user[0]);
                            EEPROM.update(0, 1);
                        }
                        else if (slot == 2)
                        {
                            int loc = 4;
                            loc += sizeof(user[0]);
                            EEPROM.put(loc, user[1]);
                            EEPROM.update(1, 1);
                        }
                        else if (slot == 3)
                        {
                            int loc = 4;
                            loc += sizeof(user[0]);
                            loc += sizeof(user[1]);
                            EEPROM.put(loc, user[2]);
                            EEPROM.update(2, 1);
                        }
                        resetare();
                        break;
                    }
                }

                else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
                {
                    mode = 2;

                    TastCifProfil();

                }
                else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
                    displayUserAndPass(slot, ' ', isPassword);
                else if (p.y >= 600 && p.y <= 660)
                {
                    if (p.x >= 190 && p.x <= 240)
                        displayUserAndPass(slot, 'Q', isPassword);
                    else if (p.x >= 245 && p.x <= 295)
                        displayUserAndPass(slot, 'W', isPassword);
                    else if (p.x >= 300 && p.x <= 350)
                        displayUserAndPass(slot, 'E', isPassword);
                    else if (p.x >= 355 && p.x <= 405)
                        displayUserAndPass(slot, 'R', isPassword);
                    else if (p.x >= 410 && p.x <= 460)
                        displayUserAndPass(slot, 'T', isPassword);
                    else if (p.x >= 465 && p.x <= 515)
                        displayUserAndPass(slot, 'Y', isPassword);
                    else if (p.x >= 520 && p.x <= 570)
                        displayUserAndPass(slot, 'U', isPassword);
                    else if (p.x >= 575 && p.x <= 625)
                        displayUserAndPass(slot, 'I', isPassword);
                    else if (p.x >= 630 && p.x <= 680)
                        displayUserAndPass(slot, 'O', isPassword);
                    else if (p.x >= 685 && p.x <= 735)
                        displayUserAndPass(slot, 'P', isPassword);

                }
                else if (p.y >= 670 && p.y <= 730)
                {
                    if (p.x >= 220 && p.x <= 270)
                        displayUserAndPass(slot, 'A', isPassword);
                    else if (p.x >= 275 && p.x <= 325)
                        displayUserAndPass(slot, 'S', isPassword);
                    else if (p.x >= 330 && p.x <= 380)
                        displayUserAndPass(slot, 'D', isPassword);
                    else if (p.x >= 385 && p.x <= 435)
                        displayUserAndPass(slot, 'F', isPassword);
                    else if (p.x >= 440 && p.x <= 490)
                        displayUserAndPass(slot, 'G', isPassword);
                    else if (p.x >= 495 && p.x <= 545)
                        displayUserAndPass(slot, 'H', isPassword);
                    else if (p.x >= 550 && p.x <= 600)
                        displayUserAndPass(slot, 'J', isPassword);
                    else if (p.x >= 605 && p.x <= 655)
                        displayUserAndPass(slot, 'K', isPassword);
                    else if (p.x >= 660 && p.x <= 710)
                        displayUserAndPass(slot, 'L', isPassword);
                }
                else if (p.y >= 740 && p.y <= 800)
                {
                    if (p.x >= 250 && p.x <= 300)
                        displayUserAndPass(slot, 'Z', isPassword);
                    else if (p.x >= 305 && p.x <= 355)
                        displayUserAndPass(slot, 'X', isPassword);
                    else if (p.x >= 360 && p.x <= 410)
                        displayUserAndPass(slot, 'C', isPassword);
                    else if (p.x >= 415 && p.x <= 465)
                        displayUserAndPass(slot, 'V', isPassword);
                    else if (p.x >= 470 && p.x <= 520)
                        displayUserAndPass(slot, 'B', isPassword);
                    else if (p.x >= 525 && p.x <= 575)
                        displayUserAndPass(slot, 'N', isPassword);
                    else if (p.x >= 580 && p.x <= 630)
                        displayUserAndPass(slot, 'M', isPassword);
                }

            }
            else
            {
                if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
                {
                    if (isPassword)
                    {
                        textboxPass();
                        user[slot - 1].password_len--;
                        user[slot - 1].parola[user[slot - 1].password_len] = 0;
                        pinMode(A1, OUTPUT);
                        pinMode(A2, OUTPUT);
                        tft.setCursor(5, 143);
                        for (int i = 0; i < user[slot - 1].password_len; i++)
                            tft.print('*');
                    }
                    else
                    {
                        textboxUser();
                        user[slot - 1].username_len--;
                        user[slot - 1].username[user[slot - 1].username_len] = 0;
                        afisareSirProfil(slot, isPassword);
                    }
                }
                else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
                {
                    if (!isPassword)
                    {
                        isPassword = true;
                    }
                    else
                    {
                        if (slot == 1)
                        {
                            EEPROM.put(4, user[0]);
                            EEPROM.update(0, 1);
                        }
                        else if (slot == 2)
                        {
                            int loc = 4;
                            loc += sizeof(user[0]);
                            EEPROM.put(loc, user[1]);
                            EEPROM.update(1, 1);
                        }
                        else if (slot == 3)
                        {
                            int loc = 4;
                            loc += sizeof(user[0]);
                            loc += sizeof(user[1]);
                            EEPROM.put(loc, user[2]);
                            EEPROM.update(2, 1);
                        }
                        resetare();
                        break;
                    }
                }
                else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
                {
                    mode = 1;
                    TastLitereProfil();
                }
                else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
                    displayUserAndPass(slot, ' ', isPassword);
                else if (p.y >= 600 && p.y <= 660)
                {
                    if (p.x >= 190 && p.x <= 240)
                        displayUserAndPass(slot, '1', isPassword);
                    else if (p.x >= 245 && p.x <= 295)
                        displayUserAndPass(slot, '2', isPassword);
                    else if (p.x >= 300 && p.x <= 350)
                        displayUserAndPass(slot, '3', isPassword);
                    else if (p.x >= 355 && p.x <= 405)
                        displayUserAndPass(slot, '4', isPassword);
                    else if (p.x >= 410 && p.x <= 460)
                        displayUserAndPass(slot, '5', isPassword);
                    else if (p.x >= 465 && p.x <= 515)
                        displayUserAndPass(slot, '6', isPassword);
                    else if (p.x >= 520 && p.x <= 570)
                        displayUserAndPass(slot, '7', isPassword);
                    else if (p.x >= 575 && p.x <= 625)
                        displayUserAndPass(slot, '8', isPassword);
                    else if (p.x >= 630 && p.x <= 680)
                        displayUserAndPass(slot, '9', isPassword);
                    else if (p.x >= 685 && p.x <= 735)
                        displayUserAndPass(slot, '0', isPassword);

                }
                else if (p.y >= 670 && p.y <= 730)
                {
                    if (p.x >= 190 && p.x <= 240)
                        displayUserAndPass(slot, '@', isPassword);
                    else if (p.x >= 245 && p.x <= 295)
                        displayUserAndPass(slot, '.', isPassword);
                    else if (p.x >= 300 && p.x <= 350)
                        displayUserAndPass(slot, '$', isPassword);
                    else if (p.x >= 355 && p.x <= 405)
                        displayUserAndPass(slot, '_', isPassword);
                    else if (p.x >= 410 && p.x <= 460)
                        displayUserAndPass(slot, '&', isPassword);
                    else if (p.x >= 465 && p.x <= 515)
                        displayUserAndPass(slot, '-', isPassword);
                    else if (p.x >= 520 && p.x <= 570)
                        displayUserAndPass(slot, '+', isPassword);
                    else if (p.x >= 575 && p.x <= 625)
                        displayUserAndPass(slot, '(', isPassword);
                    else if (p.x >= 630 && p.x <= 680)
                        displayUserAndPass(slot, ')', isPassword);
                    else if (p.x >= 685 && p.x <= 735)
                        displayUserAndPass(slot, '/', isPassword);

                }
                else if (p.y >= 740 && p.y <= 800)
                {
                    if (p.x >= 190 && p.x <= 240)
                        displayUserAndPass(slot, '<', isPassword);
                    else if (p.x >= 245 && p.x <= 295)
                        displayUserAndPass(slot, '*', isPassword);
                    else if (p.x >= 300 && p.x <= 350)
                        displayUserAndPass(slot, '\'', isPassword);
                    else if (p.x >= 355 && p.x <= 405)
                        displayUserAndPass(slot, ':', isPassword);
                    else if (p.x >= 410 && p.x <= 460)
                        displayUserAndPass(slot, ';', isPassword);
                    else if (p.x >= 465 && p.x <= 515)
                        displayUserAndPass(slot, '!', isPassword);
                    else if (p.x >= 520 && p.x <= 570)
                        displayUserAndPass(slot, '?', isPassword);
                    else if (p.x >= 575 && p.x <= 625)
                        displayUserAndPass(slot, '=', isPassword);
                    else if (p.x >= 630 && p.x <= 680)
                        displayUserAndPass(slot, '%', isPassword);
                    else if (p.x >= 685 && p.x <= 735)
                        displayUserAndPass(slot, '>', isPassword);
                }
                else if (p.y >= 810 && p.y <= 870)
                {
                    if (p.x >= 190 && p.x <= 240)
                        displayUserAndPass(slot, ',', isPassword);
                    else if (p.x >= 630 && p.x <= 680)
                    {
                        displayUserAndPass(slot, '\"', isPassword);
                    }
                }

            }
            if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
            {
                MeniuAdaugaProfil();
                break;
            }
        }
        delay(200);
    }
}

void GetTasteMeniuLoad()
{
    while (1)
    {
        TSPoint p = ts.getPoint();
        if (p.z > ts.pressureThreshhold)
        {

            if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
            {
                MainMenu();
                break;
            }
            else if (p.x >= 160 && p.x <= 925)
            {
                if (p.y >= 250 && p.y <= 440)
                {
                    getPassword(1, 1);
                    break;
                }
                else if (p.y >= 470 && p.y <= 660)
                {
                    getPassword(2, 1);
                    break;
                }
                else if (p.y >= 690 && p.y <= 880)
                {
                    getPassword(3, 1);
                    break;
                }
            }
        }
        delay(300);
    }
}

void mesaj_slot_gol_load(int slot)
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);

    tft.fillRect(0, 100, 239, 100, YELLOW);
    tft.setTextSize(2);
    tft.setTextColor(BLACK);
    tft.setCursor(5, 110);
    tft.print("Slot-ul selectat   este gol!");
    tft.fillRect(85, 165, 60, 30, BLACK);
    tft.setCursor(100, 173);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print("OK");

    while (1)
    {
        TSPoint p = ts.getPoint();
        if (p.z > ts.pressureThreshhold)
        {

            if (p.y >= 555 && p.y <= 630 && p.x >= 425 && p.y <= 610)
            {
                MeniuIncarcaProfil();
                break;
            }
        }
    }
}

void mesaj_stergere(int slot)
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);

    tft.fillRect(0, 100, 239, 100, YELLOW);
    tft.setTextSize(2);
    tft.setTextColor(BLACK);
    tft.setCursor(5, 110);
    if (EEPROM.read(slot - 1) == 0)
    {
        tft.print("Slot-ul selectat   este gol!");
        tft.fillRect(85, 165, 60, 30, BLACK);
        tft.setCursor(100, 173);
        tft.setTextSize(2);
        tft.setTextColor(WHITE);
        tft.print("OK");

        while (1)
        {
            TSPoint p = ts.getPoint();
            if (p.z > ts.pressureThreshhold)
            {

                if (p.y >= 555 && p.y <= 630 && p.x >= 425 && p.y <= 610)
                {
                    MeniuStergeProfil();
                    break;
                }
            }
        }
    }
    else
    {
        tft.print("Doriti sa stergeti profilul");
        profil var;
        if (slot == 1)
        {
            EEPROM.get(4, var);
            tft.print('\n');
            tft.setTextColor(RED);
            tft.print("      ");
            tft.print(var.username);
            tft.setTextColor(BLACK);
            tft.print("?");
        }
        else if (slot == 2)
        {
            int loc = 4;
            loc += sizeof(var);
            EEPROM.get(loc, var);
            tft.print('\n');
            tft.setTextColor(RED);
            tft.print("      ");
            tft.print(var.username);
            tft.setTextColor(BLACK);
            tft.print("?");
        }
        else if (slot == 3)
        {
            int loc = 4;
            loc += 2 * sizeof(var);
            EEPROM.get(loc, var);
            tft.print('\n');
            tft.setTextColor(RED);
            tft.print("      ");
            tft.print(var.username);
            tft.setTextColor(BLACK);
            tft.print("?");
        }
        tft.fillRect(20, 165, 60, 30, BLACK);
        tft.fillRect(160, 165, 60, 30, BLACK);
        tft.setCursor(35, 173);
        tft.setTextColor(WHITE);
        tft.print("DA");
        tft.setCursor(175, 173);
        tft.print("NU");
        while (1)
        {
            TSPoint p = ts.getPoint();
            if (p.z > ts.pressureThreshhold)
            {

                if (p.y >= 555 && p.y <= 630)
                {
                    if (p.x >= 215 && p.x <= 390)
                    {
                        getPassword(slot, 2);
                        break;
                    }
                    else if (p.x >= 660 && p.x <= 845)
                    {
                        MeniuStergeProfil();
                        break;
                    }
                }

            }
        }
    }
}

void DeleteProfile(int slot)
{
    int marime = sizeof(user[0]), loc = 4;
    if (slot == 1)
    {
        EEPROM.update(0, 0);
    }
    else if (slot == 2)
    {
        EEPROM.update(1, 0);
        loc += marime;
    }
    else if (slot == 3)
    {
        EEPROM.update(2, 0);
        loc += 2 * marime;
    }
    for (int i = loc; i < EEPROM.length() && marime; i++, marime--)
        EEPROM.update(i, 0);
    resetare();
}

void ParolaGresita(int slot, int mod)
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);

    tft.fillRect(0, 100, 239, 100, YELLOW);
    tft.setTextSize(2);
    tft.setTextColor(BLACK);
    tft.setCursor(5, 110);
    tft.print("Parola introdusa este gresita!");
    tft.fillRect(85, 165, 60, 30, BLACK);
    tft.setCursor(100, 173);
    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.print("OK");

    while (1)
    {
        TSPoint p = ts.getPoint();
        if (p.z > ts.pressureThreshhold)
        {

            if (p.y >= 555 && p.y <= 630 && p.x >= 425 && p.y <= 610)
            {
                getPassword(slot, mod);
                break;
            }
        }
    }
}


void GetTasteIntroducereParola(int slot, int mod)
{
    int mode = 1;
    for (int i = 0; i < user[3].password_len; i++)
        user[3].parola[i] = 0;
    user[3].password_len = 0;
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    bool isPassword = true;
    chenar(isPassword);
    while (1)
    {

        TSPoint p = ts.getPoint();

        // we have some minimum pressure we consider 'valid'
        // pressure of 0 means no pressing!
        if (p.z > ts.pressureThreshhold) {

            if (mode == 1)
            {
                if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
                {
                    textboxPass();
                    user[3].password_len--;
                    user[3].parola[user[3].password_len] = 0;
                    pinMode(A1, OUTPUT);
                    pinMode(A2, OUTPUT);
                    tft.setCursor(5, 143);
                    for (int i = 0; i < user[3].password_len; i++)
                        tft.print('*');
                }
                else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
                {
                    profil var;
                    int loc = 4;
                    if (slot == 2)
                        loc += sizeof(var);
                    else if (slot == 3)
                        loc += 2 * sizeof(var);
                    EEPROM.get(loc, var);

                    if (strcmp(user[3].parola, var.parola) == 0)
                    {
                        if (mod == 1)
                            EcranProfil(slot);
                        else
                            DeleteProfile(slot);
                        break;
                    }
                    else
                    {
                        ParolaGresita(slot, mod);
                        break;
                    }
                }

                else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
                {
                    mode = 2;

                    TastCifProfil();

                }
                else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
                    displayUserAndPass(4, ' ', isPassword);
                else if (p.y >= 600 && p.y <= 660)
                {
                    if (p.x >= 190 && p.x <= 240)
                        displayUserAndPass(4, 'Q', isPassword);
                    else if (p.x >= 245 && p.x <= 295)
                        displayUserAndPass(4, 'W', isPassword);
                    else if (p.x >= 300 && p.x <= 350)
                        displayUserAndPass(4, 'E', isPassword);
                    else if (p.x >= 355 && p.x <= 405)
                        displayUserAndPass(4, 'R', isPassword);
                    else if (p.x >= 410 && p.x <= 460)
                        displayUserAndPass(4, 'T', isPassword);
                    else if (p.x >= 465 && p.x <= 515)
                        displayUserAndPass(4, 'Y', isPassword);
                    else if (p.x >= 520 && p.x <= 570)
                        displayUserAndPass(4, 'U', isPassword);
                    else if (p.x >= 575 && p.x <= 625)
                        displayUserAndPass(4, 'I', isPassword);
                    else if (p.x >= 630 && p.x <= 680)
                        displayUserAndPass(4, 'O', isPassword);
                    else if (p.x >= 685 && p.x <= 735)
                        displayUserAndPass(4, 'P', isPassword);

                }
                else if (p.y >= 670 && p.y <= 730)
                {
                    if (p.x >= 220 && p.x <= 270)
                        displayUserAndPass(4, 'A', isPassword);
                    else if (p.x >= 275 && p.x <= 325)
                        displayUserAndPass(4, 'S', isPassword);
                    else if (p.x >= 330 && p.x <= 380)
                        displayUserAndPass(4, 'D', isPassword);
                    else if (p.x >= 385 && p.x <= 435)
                        displayUserAndPass(4, 'F', isPassword);
                    else if (p.x >= 440 && p.x <= 490)
                        displayUserAndPass(4, 'G', isPassword);
                    else if (p.x >= 495 && p.x <= 545)
                        displayUserAndPass(4, 'H', isPassword);
                    else if (p.x >= 550 && p.x <= 600)
                        displayUserAndPass(4, 'J', isPassword);
                    else if (p.x >= 605 && p.x <= 655)
                        displayUserAndPass(4, 'K', isPassword);
                    else if (p.x >= 660 && p.x <= 710)
                        displayUserAndPass(4, 'L', isPassword);
                }
                else if (p.y >= 740 && p.y <= 800)
                {
                    if (p.x >= 250 && p.x <= 300)
                        displayUserAndPass(4, 'Z', isPassword);
                    else if (p.x >= 305 && p.x <= 355)
                        displayUserAndPass(4, 'X', isPassword);
                    else if (p.x >= 360 && p.x <= 410)
                        displayUserAndPass(4, 'C', isPassword);
                    else if (p.x >= 415 && p.x <= 465)
                        displayUserAndPass(4, 'V', isPassword);
                    else if (p.x >= 470 && p.x <= 520)
                        displayUserAndPass(4, 'B', isPassword);
                    else if (p.x >= 525 && p.x <= 575)
                        displayUserAndPass(4, 'N', isPassword);
                    else if (p.x >= 580 && p.x <= 630)
                        displayUserAndPass(4, 'M', isPassword);
                }

            }
            else
            {
                if (p.x >= 750 && p.x <= 885 && p.y >= 650 && p.y <= 720)
                {
                    textboxPass();
                    user[3].password_len--;
                    user[3].parola[user[3].password_len] = 0;
                    pinMode(A1, OUTPUT);
                    pinMode(A2, OUTPUT);
                    tft.setCursor(5, 143);
                    for (int i = 0; i < user[3].password_len; i++)
                        tft.print('*');
                }
                else if (p.x >= 775 && p.x <= 890 && p.y >= 830 && p.y <= 905)
                {
                    profil var;
                    int loc = 4;
                    if (slot == 2)
                        loc += sizeof(var);
                    else if (slot == 3)
                        loc += 2 * sizeof(var);
                    EEPROM.get(loc, var);
                    if (strcmp(user[3].parola, var.parola) == 0)
                    {
                        if (mod == 1)
                            EcranProfil(slot);
                        else
                            DeleteProfile(slot);
                        break;
                    }
                    else
                    {
                        ParolaGresita(slot, mod);
                        break;
                    }
                }
                else if (p.x >= 770 && p.x <= 895 && p.y >= 745 && p.y <= 805)
                {
                    mode = 1;
                    TastLitereProfil();
                }
                else if (p.x >= 280 && p.x <= 595 && p.y >= 830 && p.y <= 895)
                    displayUserAndPass(4, ' ', isPassword);
                else if (p.y >= 600 && p.y <= 660)
                {
                    if (p.x >= 190 && p.x <= 240)
                        displayUserAndPass(4, '1', isPassword);
                    else if (p.x >= 245 && p.x <= 295)
                        displayUserAndPass(4, '2', isPassword);
                    else if (p.x >= 300 && p.x <= 350)
                        displayUserAndPass(4, '3', isPassword);
                    else if (p.x >= 355 && p.x <= 405)
                        displayUserAndPass(4, '4', isPassword);
                    else if (p.x >= 410 && p.x <= 460)
                        displayUserAndPass(4, '5', isPassword);
                    else if (p.x >= 465 && p.x <= 515)
                        displayUserAndPass(4, '6', isPassword);
                    else if (p.x >= 520 && p.x <= 570)
                        displayUserAndPass(4, '7', isPassword);
                    else if (p.x >= 575 && p.x <= 625)
                        displayUserAndPass(4, '8', isPassword);
                    else if (p.x >= 630 && p.x <= 680)
                        displayUserAndPass(4, '9', isPassword);
                    else if (p.x >= 685 && p.x <= 735)
                        displayUserAndPass(4, '0', isPassword);

                }
                else if (p.y >= 670 && p.y <= 730)
                {
                    if (p.x >= 190 && p.x <= 240)
                        displayUserAndPass(4, '@', isPassword);
                    else if (p.x >= 245 && p.x <= 295)
                        displayUserAndPass(4, '.', isPassword);
                    else if (p.x >= 300 && p.x <= 350)
                        displayUserAndPass(4, '$', isPassword);
                    else if (p.x >= 355 && p.x <= 405)
                        displayUserAndPass(4, '_', isPassword);
                    else if (p.x >= 410 && p.x <= 460)
                        displayUserAndPass(4, '&', isPassword);
                    else if (p.x >= 465 && p.x <= 515)
                        displayUserAndPass(4, '-', isPassword);
                    else if (p.x >= 520 && p.x <= 570)
                        displayUserAndPass(4, '+', isPassword);
                    else if (p.x >= 575 && p.x <= 625)
                        displayUserAndPass(4, '(', isPassword);
                    else if (p.x >= 630 && p.x <= 680)
                        displayUserAndPass(4, ')', isPassword);
                    else if (p.x >= 685 && p.x <= 735)
                        displayUserAndPass(4, '/', isPassword);

                }
                else if (p.y >= 740 && p.y <= 800)
                {
                    if (p.x >= 190 && p.x <= 240)
                        displayUserAndPass(4, '<', isPassword);
                    else if (p.x >= 245 && p.x <= 295)
                        displayUserAndPass(4, '*', isPassword);
                    else if (p.x >= 300 && p.x <= 350)
                        displayUserAndPass(4, '\'', isPassword);
                    else if (p.x >= 355 && p.x <= 405)
                        displayUserAndPass(4, ':', isPassword);
                    else if (p.x >= 410 && p.x <= 460)
                        displayUserAndPass(4, ';', isPassword);
                    else if (p.x >= 465 && p.x <= 515)
                        displayUserAndPass(4, '!', isPassword);
                    else if (p.x >= 520 && p.x <= 570)
                        displayUserAndPass(4, '?', isPassword);
                    else if (p.x >= 575 && p.x <= 625)
                        displayUserAndPass(4, '=', isPassword);
                    else if (p.x >= 630 && p.x <= 680)
                        displayUserAndPass(4, '%', isPassword);
                    else if (p.x >= 685 && p.x <= 735)
                        displayUserAndPass(4, '>', isPassword);
                }
                else if (p.y >= 810 && p.y <= 870)
                {
                    if (p.x >= 190 && p.x <= 240)
                        displayUserAndPass(4, ',', isPassword);
                    else if (p.x >= 630 && p.x <= 680)
                    {
                        displayUserAndPass(4, '\"', isPassword);
                    }
                }

            }
            if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
            {
                MeniuAdaugaProfil();
                break;
            }
        }
        delay(200);
    }
}

void MenuChooseGame(int slot)
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);

    tft.fillScreen(BLUE);
    tft.fillRect(0, 0, 60, 20, RED);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setCursor(5, 5);
    tft.print("BACK");

    tft.fillRect(60, 35, 120, 60, BLACK);
    tft.setCursor(67, 55);
    tft.setTextSize(3);
    tft.setTextColor(YELLOW);
    tft.print("WORDLE");

    tft.fillRect(60, 120, 120, 60, BLACK);
    tft.setCursor(67, 140);
    tft.setTextSize(3);
    tft.setTextColor(YELLOW);
    tft.print("X si 0");

    tft.fillRect(60, 205, 120, 60, BLACK);
    tft.setCursor(67, 215);
    tft.setTextSize(2);
    tft.setTextColor(YELLOW);
    tft.print("  Space             Invaders");

    while (1)
    {
        TSPoint p = ts.getPoint();
        if (p.z > ts.pressureThreshhold)
        {

            if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
            {
                EcranProfil(slot);
                break;
            }
            else if (p.x >= 335 && p.x <= 715)
            {
                if (p.y >= 230 && p.y <= 360)
                {
                    IntroWordle(slot);
                    break;
                }
                else if (p.y >= 435 && p.y <= 590)
                {
                    IntroX0(slot);
                    break;
                }
                else if (p.y >= 640 && p.y <= 770)
                {
                    IntroSpaceInvaders(slot);
                    break;
                }
            }
        }
    }
}

void EcranProfil(int slot)
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    Serial.print("Slot ");
    Serial.print(slot);
    tft.fillScreen(YELLOW);
    tft.fillRect(0, 0, 60, 20, RED);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setCursor(5, 5);
    tft.print("BACK");

    profil var;
    int loc = 4;
    if (slot == 2)
        loc = 43;
    else if (slot == 3)
        loc = 82;
    EEPROM.get(loc, var);

    tft.fillRect(0, 35, 239, 60, BLUE);
    tft.fillRect(50, 130, 130, 60, RED);

    tft.setCursor(0, 40);
    tft.setTextColor(RED);
    tft.print("Profil: ");
    tft.print(var.username);
    dateSerial += var.username;
    tft.print("\nLevel: ");
    tft.print(var.Level);
    tft.print("\nXP:");
    tft.print(var.XPLevel);
    tft.print('/');
    tft.print(50 + (var.Level - 1) * 5);

    tft.setCursor(76, 148);
    tft.setTextColor(BLUE);
    tft.setTextSize(3);
    tft.print("PLAY");

    while (1)
    {
        TSPoint p = ts.getPoint();
        if (p.z > ts.pressureThreshhold)
        {
            if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
            {
                MainMenu();
                break;
            }
            else if (p.y >= 460 && p.y <= 610 && p.x >= 310 && p.x <= 720)
            {
                MenuChooseGame(slot);
                break;
            }
        }
    }
}

void getPassword(int slot, int mod) ///mod = 1 - load, mod = 2 - sterge
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    if (EEPROM.read(slot - 1) == 0)
        mesaj_slot_gol_load(slot);
    else
    {

        tft.fillScreen(BLUE);
        tft.fillRect(0, 0, 60, 20, RED);
        tft.setTextColor(WHITE);
        tft.setTextSize(2);
        tft.setCursor(5, 5);
        tft.print("BACK");
        tft.setCursor(0, 30);
        tft.setTextSize(2);
        tft.print("Username");
        tft.fillRect(0, 50, 240, 30, WHITE);
        tft.setCursor(0, 115);
        tft.print("Parola");
        tft.fillRect(0, 135, 240, 30, WHITE);

        tft.setCursor(5, 57);
        tft.setTextSize(2);
        tft.setTextColor(BLACK);
        profil var;
        int loc = 4;
        if (slot == 2)
            loc += sizeof(var);
        else if (slot == 3)
            loc += 2 * sizeof(var);

        tft.print(EEPROM.get(loc, var.username));

        TastLitereProfil();
        GetTasteIntroducereParola(slot, mod);
    }

}

void GetTasteMeniuDelete()
{
    while (1)
    {
        TSPoint p = ts.getPoint();
        if (p.z > ts.pressureThreshhold)
        {

            if (p.x >= 145 && p.x <= 330 && p.y >= 150 && p.y <= 250)
            {
                MainMenu();
                break;
            }
            else if (p.x >= 160 && p.x <= 925)
            {
                if (p.y >= 250 && p.y <= 440)
                {
                    mesaj_stergere(1);
                    break;
                }
                else if (p.y >= 470 && p.y <= 660)
                {
                    mesaj_stergere(2);
                    break;
                }
                else if (p.y >= 690 && p.y <= 880)
                {
                    mesaj_stergere(3);
                    break;
                }
            }
        }
        delay(300);
    }
}

void Intro()
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    transmiteDate();
    tft.fillRect(0, 0, 239, 300, RED);
    tft.setCursor(0, 301);
    tft.setTextColor(L_YELLOW);
    tft.setTextSize(1);
    tft.print("ESPGamingRetro");
    tft.setCursor(0, 310);
    tft.setTextColor(L_YELLOW);
    tft.setTextSize(1);
    tft.print("Ionut Bene,Robert Cozma,Andrei Patrascu");
    tft.setCursor(40, 20);
    tft.setTextColor(BLUE);
    tft.setTextSize(4);
    tft.print("WELCOME");
    delay(1200);
    tft.setCursor(100, 70);
    tft.setTextColor(GREEN);
    tft.setTextSize(4);
    tft.print("TO");
    delay(1200);
    tft.setCursor(40, 120);
    tft.setTextColor(BLUE);
    tft.setTextSize(3);
    tft.print("ESPGaming");
    delay(1500);
    tft.setCursor(80, 150);
    tft.setTextColor(GREEN);
    tft.setTextSize(3);
    tft.print("Retro");
    delay(3000);
    tft.setCursor(0, 265);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("Press anywhere to  continue...");
    while (1)
    {
        p = ts.getPoint();
        if (p.z > ts.pressureThreshhold)
        {
            MainMenu();
            break;
        }
    }
}

int rowCounter = 0; // row counter
int columnCounter = 0; // column counter
int foundColumn = 0;
boolean foundCol = false;
int keyValue = 0;
int noKey = 0;
boolean readKey = false;
int debounce = 300; // set this to the lowest value that gives the best result
const int row1 = 22;
const int row2 = 23;
const int row3 = 24;
const int row4 = 25;
const int colA = 28;
const int colB = 29;
const int colC = 30;
const int colD = 31;
const int ledPin = 13; // onboard LED

int modX0 = 1; ///1 - x, 2 - 0
char frX0[4][4];

void scanRow() {
    for (int j = row1; j < (row4 + 1); j++) {
        digitalWrite(j, HIGH);
    }
    digitalWrite(rowCounter, LOW); // switch on one row
}
void readColumn() {
    foundColumn = digitalRead(columnCounter);
    if (foundColumn == 0) {
        foundCol = true;
    }
    else {
        foundCol = false;
        noKey = noKey + 1; // counter for number of empty columns
    }
}

int verifWin()
{
    if ((frX0[0][0] == 'X' && frX0[0][1] == 'X' && frX0[0][2] == 'X' && frX0[0][3] == 'X') ||
        (frX0[1][0] == 'X' && frX0[1][1] == 'X' && frX0[1][2] == 'X' && frX0[1][3] == 'X') ||
        (frX0[2][0] == 'X' && frX0[2][1] == 'X' && frX0[2][2] == 'X' && frX0[2][3] == 'X') ||
        (frX0[3][0] == 'X' && frX0[3][1] == 'X' && frX0[3][2] == 'X' && frX0[3][3] == 'X') ||
        (frX0[0][0] == 'X' && frX0[1][0] == 'X' && frX0[2][0] == 'X' && frX0[3][0] == 'X') ||
        (frX0[0][1] == 'X' && frX0[1][1] == 'X' && frX0[2][1] == 'X' && frX0[3][1] == 'X') ||
        (frX0[0][2] == 'X' && frX0[1][2] == 'X' && frX0[2][2] == 'X' && frX0[3][2] == 'X') ||
        (frX0[0][3] == 'X' && frX0[1][3] == 'X' && frX0[2][3] == 'X' && frX0[3][3] == 'X') ||
        (frX0[0][0] == 'X' && frX0[1][1] == 'X' && frX0[2][2] == 'X' && frX0[3][3] == 'X') ||
        (frX0[0][3] == 'X' && frX0[1][2] == 'X' && frX0[2][1] == 'X' && frX0[3][0] == 'X'))
        return 1;

    if ((frX0[0][0] == '0' && frX0[0][1] == '0' && frX0[0][2] == '0' && frX0[0][3] == '0') ||
        (frX0[1][0] == '0' && frX0[1][1] == '0' && frX0[1][2] == '0' && frX0[1][3] == '0') ||
        (frX0[2][0] == '0' && frX0[2][1] == '0' && frX0[2][2] == '0' && frX0[2][3] == '0') ||
        (frX0[3][0] == '0' && frX0[3][1] == '0' && frX0[3][2] == '0' && frX0[3][3] == '0') ||
        (frX0[0][0] == '0' && frX0[1][0] == '0' && frX0[2][0] == '0' && frX0[3][0] == '0') ||
        (frX0[0][1] == '0' && frX0[1][1] == '0' && frX0[2][1] == '0' && frX0[3][1] == '0') ||
        (frX0[0][2] == '0' && frX0[1][2] == '0' && frX0[2][2] == '0' && frX0[3][2] == '0') ||
        (frX0[0][3] == '0' && frX0[1][3] == '0' && frX0[2][3] == '0' && frX0[3][3] == '0') ||
        (frX0[0][0] == '0' && frX0[1][1] == '0' && frX0[2][2] == '0' && frX0[3][3] == '0') ||
        (frX0[0][3] == '0' && frX0[1][2] == '0' && frX0[2][1] == '0' && frX0[3][0] == '0'))
        return 2;

    int okfull = 1;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (frX0[i][j] == 0)
            {
                okfull = 0;
                break;
            }
    if (okfull == 1)
        return 3;
    return 0;
}

void Win(int x, int slot)
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    tft.fillRect(0, 0, 240, 270, GREEN);
    tft.setCursor(15, 200);
    tft.setTextSize(3);
    tft.setTextColor(WHITE);
    if (x == 1)
        tft.print("X a castigat");
    else if (x == 2)
        tft.print("0 a castigat");
    else
        tft.print("Egalitate");

    delay(5000);
    MenuChooseGame(slot);
}


void XSi0(int slot)
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);

    tft.fillScreen(BLACK);
    tft.drawRect(15, 50, 50, 50, WHITE);
    tft.drawRect(65, 50, 50, 50, WHITE);
    tft.drawRect(115, 50, 50, 50, WHITE);
    tft.drawRect(165, 50, 50, 50, WHITE);
    tft.drawRect(15, 100, 50, 50, WHITE);
    tft.drawRect(65, 100, 50, 50, WHITE);
    tft.drawRect(115, 100, 50, 50, WHITE);
    tft.drawRect(165, 100, 50, 50, WHITE);
    tft.drawRect(15, 150, 50, 50, WHITE);
    tft.drawRect(65, 150, 50, 50, WHITE);
    tft.drawRect(115, 150, 50, 50, WHITE);
    tft.drawRect(165, 150, 50, 50, WHITE);
    tft.drawRect(15, 200, 50, 50, WHITE);
    tft.drawRect(65, 200, 50, 50, WHITE);
    tft.drawRect(115, 200, 50, 50, WHITE);
    tft.drawRect(165, 200, 50, 50, WHITE);

    pinMode(row1, OUTPUT);
    pinMode(row2, OUTPUT);
    pinMode(row3, OUTPUT);
    pinMode(row4, OUTPUT);
    pinMode(colA, INPUT_PULLUP);
    pinMode(colB, INPUT_PULLUP);
    pinMode(colC, INPUT_PULLUP);
    pinMode(colD, INPUT_PULLUP);
    //
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    int won = 0;

    while (won == 0)
    {
        if (noKey == 16) { // no keys were pressed
            readKey = true; // keyboard is ready to accept a new keypress
        }
        noKey = 0;
        for (rowCounter = row1; rowCounter < (row4 + 1); rowCounter++) {
            scanRow(); // switch on one row at a time
            for (columnCounter = colA; columnCounter < colD + 1; columnCounter++) {
                readColumn(); // read the switch pressed
                if (foundCol == true) {
                    keyValue = (rowCounter - row1) + 4 * (columnCounter - colA);
                }
            }
        }
        tft.setTextSize(4);
        tft.setTextColor(GREEN);
        if (readKey == true && noKey == 15) { // a key has been pressed
            switch (keyValue)
            {
            case 3:
                tft.setCursor(30, 60);
                if (modX0 == 1 && frX0[0][0] == 0)
                {
                    tft.print("X");
                    frX0[0][0] = 'X';
                    modX0 = 2;
                }
                else if (modX0 == 2 && frX0[0][0] == 0)
                {
                    tft.setTextColor(RED);
                    tft.print("0");
                    frX0[0][0] = '0';
                    modX0 = 1;
                }
                if (verifWin() != 0)
                {
                    won = 1;
                    Win(verifWin(), slot);
                }
                break;
            case 7:
                tft.setCursor(80, 60);
                if (modX0 == 1 && frX0[0][1] == 0)
                {
                    tft.print("X");
                    frX0[0][1] = 'X';
                    modX0 = 2;
                }
                else if (modX0 == 2 && frX0[0][1] == 0)
                {
                    tft.setTextColor(RED);
                    tft.print("0");
                    frX0[0][1] = '0';
                    modX0 = 1;
                }
                if (verifWin() != 0)
                {
                    won = 1;
                    Win(verifWin(), slot);
                }
                break;
            case 11:
                tft.setCursor(130, 60);
                if (modX0 == 1 && frX0[0][2] == 0)
                {
                    tft.print("X");
                    frX0[0][2] = 'X';
                    modX0 = 2;
                }
                else if (modX0 == 2 && frX0[0][2] == 0)
                {
                    tft.setTextColor(RED);
                    tft.print("0");
                    frX0[0][2] = '0';
                    modX0 = 1;
                }
                if (verifWin() != 0)
                {
                    won = 1;
                    Win(verifWin(), slot);
                }
                break;
            case 15:
                tft.setCursor(180, 60);
                if (modX0 == 1 && frX0[0][3] == 0)
                {
                    tft.print("X");
                    frX0[0][3] = 'X';
                    modX0 = 2;
                }
                else if (modX0 == 2 && frX0[0][3] == 0)
                {
                    tft.setTextColor(RED);
                    tft.print("0");
                    frX0[0][3] = '0';
                    modX0 = 1;
                }
                if (verifWin() != 0)
                {
                    won = 1;
                    Win(verifWin(), slot);
                }
                break;
            case 2:
                tft.setCursor(30, 110);
                if (modX0 == 1 && frX0[1][0] == 0)
                {
                    tft.print("X");
                    frX0[1][0] = 'X';
                    modX0 = 2;
                }
                else if (modX0 == 2 && frX0[1][0] == 0)
                {
                    tft.setTextColor(RED);
                    tft.print("0");
                    frX0[1][0] = '0';
                    modX0 = 1;
                }
                if (verifWin() != 0)
                {
                    won = 1;
                    Win(verifWin(), slot);
                }
                break;
            case 6:
                tft.setCursor(80, 110);
                if (modX0 == 1 && frX0[1][1] == 0)
                {
                    tft.print("X");
                    frX0[1][1] = 'X';
                    modX0 = 2;
                }
                else if (modX0 == 2 && frX0[1][1] == 0)
                {
                    tft.setTextColor(RED);
                    tft.print("0");
                    frX0[1][1] = '0';
                    modX0 = 1;
                }
                if (verifWin() != 0)
                {
                    won = 1;
                    Win(verifWin(), slot);
                }
                break;
            case 10:
                tft.setCursor(130, 110);
                if (modX0 == 1 && frX0[1][2] == 0)
                {
                    tft.print("X");
                    frX0[1][2] = 'X';
                    modX0 = 2;
                }
                else if (modX0 == 2 && frX0[1][2] == 0)
                {
                    tft.setTextColor(RED);
                    tft.print("0");
                    frX0[1][2] = '0';
                    modX0 = 1;
                }
                if (verifWin() != 0)
                {
                    won = 1;
                    Win(verifWin(), slot);
                }
                break;
            case 14:
                tft.setCursor(180, 110);
                if (modX0 == 1 && frX0[1][3] == 0)
                {
                    tft.print("X");
                    frX0[1][3] = 'X';
                    modX0 = 2;
                }
                else if (modX0 == 2 && frX0[1][3] == 0)
                {
                    tft.setTextColor(RED);
                    tft.print("0");
                    frX0[1][3] = '0';
                    modX0 = 1;
                }
                if (verifWin() != 0)
                {
                    won = 1;
                    Win(verifWin(), slot);
                }
                break;
            case 1:
                tft.setCursor(30, 160);
                if (modX0 == 1 && frX0[2][0] == 0)
                {
                    tft.print("X");
                    frX0[2][0] = 'X';
                    modX0 = 2;
                }
                else if (modX0 == 2 && frX0[2][0] == 0)
                {
                    tft.setTextColor(RED);
                    tft.print("0");
                    frX0[2][0] = '0';
                    modX0 = 1;
                }
                if (verifWin() != 0)
                {
                    won = 1;
                    Win(verifWin(), slot);
                }
                break;
            case 5:
                tft.setCursor(80, 160);
                if (modX0 == 1 && frX0[2][1] == 0)
                {
                    tft.print("X");
                    frX0[2][1] = 'X';
                    modX0 = 2;
                }
                else if (modX0 == 2 && frX0[2][1] == 0)
                {
                    tft.setTextColor(RED);
                    tft.print("0");
                    frX0[2][1] = '0';
                    modX0 = 1;
                }
                if (verifWin() != 0)
                {
                    won = 1;
                    Win(verifWin(), slot);
                }
                break;
            case 9:
                tft.setCursor(130, 160);
                if (modX0 == 1 && frX0[2][2] == 0)
                {
                    tft.print("X");
                    frX0[2][2] = 'X';
                    modX0 = 2;
                }
                else if (modX0 == 2 && frX0[2][2] == 0)
                {
                    tft.setTextColor(RED);
                    tft.print("0");
                    frX0[2][2] = '0';
                    modX0 = 1;
                }
                if (verifWin() != 0)
                {
                    won = 1;
                    Win(verifWin(), slot);
                }
                break;
            case 13:
                tft.setCursor(180, 160);
                if (modX0 == 1 && frX0[2][3] == 0)
                {
                    tft.print("X");
                    frX0[2][3] = 'X';
                    modX0 = 2;
                }
                else if (modX0 == 2 && frX0[2][3] == 0)
                {
                    tft.setTextColor(RED);
                    tft.print("0");
                    frX0[2][3] = '0';
                    modX0 = 1;
                }
                if (verifWin() != 0)
                {
                    won = 1;
                    Win(verifWin(), slot);
                }
                break;
            case 0:
                tft.setCursor(30, 210);
                if (modX0 == 1 && frX0[3][0] == 0)
                {
                    tft.print("X");
                    frX0[3][0] = 'X';
                    modX0 = 2;
                }
                else if (modX0 == 2 && frX0[3][0] == 0)
                {
                    tft.setTextColor(RED);
                    tft.print("0");
                    frX0[3][0] = '0';
                    modX0 = 1;
                }
                if (verifWin() != 0)
                {
                    won = 1;
                    Win(verifWin(), slot);
                }
                break;
            case 4:
                tft.setCursor(80, 210);
                if (modX0 == 1 && frX0[3][1] == 0)
                {
                    tft.print("X");
                    frX0[3][1] = 'X';
                    modX0 = 2;
                }
                else if (modX0 == 2 && frX0[3][1] == 0)
                {
                    tft.setTextColor(RED);
                    tft.print("0");
                    frX0[3][1] = '0';
                    modX0 = 1;
                }
                if (verifWin() != 0)
                {
                    won = 1;
                    Win(verifWin(), slot);
                }
                break;
            case 8:
                tft.setCursor(130, 210);
                if (modX0 == 1 && frX0[3][2] == 0)
                {
                    tft.print("X");
                    frX0[3][2] = 'X';
                    modX0 = 2;
                }
                else if (modX0 == 2 && frX0[3][2] == 0)
                {
                    tft.setTextColor(RED);
                    tft.print("0");
                    frX0[3][2] = '0';
                    modX0 = 1;
                }
                if (verifWin() != 0)
                {
                    won = 1;
                    Win(verifWin(), slot);
                }
                break;
            case 12:
                tft.setCursor(180, 210);
                if (modX0 == 1 && frX0[3][3] == 0)
                {
                    tft.print("X");
                    frX0[3][3] = 'X';
                    modX0 = 2;
                }
                else if (modX0 == 2 && frX0[3][3] == 0)
                {
                    tft.setTextColor(RED);
                    tft.print("0");
                    frX0[3][3] = '0';
                    modX0 = 1;
                }
                if (verifWin() != 0)
                {
                    won = 1;
                    Win(verifWin(), slot);
                }
                break;

            }

            readKey = false; // rest the flag
            delay(debounce); // debounce
        }
    }
}
void IntroX0(int slot)
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    tft.fillScreen(BLACK);
    tft.setCursor(50, 20);
    tft.setTextColor(GOLD);
    tft.setTextSize(4);
    tft.print("X si 0");

    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setCursor(10, 100);
    tft.print("Va incepe jucatorulcu X. Pentru a pune intr-o anumita    pozitie, apasa     butonul echivalent de pe matricea de  butoane");

    tft.fillRect(60, 260, 120, 50, RED);
    tft.setCursor(62, 270);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.print("START");
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            frX0[i][j] = 0;

    while (1)
    {
        TSPoint p = ts.getPoint();
        if (p.z > ts.pressureThreshhold) {
            if (p.x >= 335 && p.x <= 740 && p.y >= 790 && p.y <= 905)
            {

                XSi0(slot);
                break;
            }
        }
    }

}

struct punct
{
    int x, y;
}obst[20];

int obstacol = 0;

void drawShip(int x)
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);

    tft.fillRect(x, 230, 30, 20, RED);
    tft.fillRect(x + 5, 220, 20, 10, RED);
}

void drawObstacle(int x, int y)
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    tft.fillRect(x, y, 20, 10, BLUE);
    obst[obstacol].x = x;
    obst[obstacol].y = y;
    obstacol++;
}

void IntroSpaceInvaders(int slot)
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    tft.fillScreen(BLACK);
    tft.setCursor(50, 20);
    tft.setTextColor(GOLD);
    tft.setTextSize(3);
    tft.print("SPACE      INVADERS");

    tft.setTextSize(2);
    tft.setTextColor(WHITE);
    tft.setCursor(0, 80);
    tft.print("Scopul jocului estesa lovesti toate   obstacolele,       pozitionand nava cusagetile de pe     ecran. Se primesc  puncte bonus daca  sunt distruse mai  multe obstacole cu aceeasi lovitura.");

    tft.fillRect(60, 260, 120, 50, RED);
    tft.setCursor(62, 270);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.print("START");

    while (1)
    {
        TSPoint p = ts.getPoint();
        if (p.z > ts.pressureThreshhold) {
            if (p.x >= 335 && p.x <= 740 && p.y >= 790 && p.y <= 905)
            {
                SpaceInvaders(slot);
                break;
            }
        }
    }
}

int destroyed = 0;
int scor = 0;

void drawGlont(int x, int y, int slot)
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    int dl = 0;
    while (1)
    {
        tft.fillRect(x + 7, y, 10, 20, YELLOW);
        delay(100);
        tft.fillRect(x + 7, y, 10, 20, BLACK);
        for (int i = 0; i < 10; i++)
            if (((x + 7 >= obst[i].x && x + 7 <= obst[i].x + 20) || (x + 17 >= obst[i].x && x + 17 <= obst[i].x + 20)) && y >= obst[i].y && y <= obst[i].y + 10)
            {
                tft.fillRect(obst[i].x, obst[i].y, 20, 10, BLACK);
                tft.fillRect(70, 5, 30, 20, BLACK);
                scor += 10;
                dl++;
                Serial.println(i);
                tft.setTextSize(2);
                tft.setCursor(70, 5);
                tft.print(scor);
                destroyed++;
                obst[i].x = 100000;
                obst[i].y = 100000;
            }
        tft.setCursor(5, 5);
        tft.print("Scor: ");
        tft.setCursor(70, 5);
        tft.print(scor);
        y -= 10;
        if (y < 0)
            break;
    }
    if (dl > 1)
    {
        scor += dl * 10;
        tft.fillRect(70, 5, 30, 20, BLACK);
        tft.setCursor(5, 5);
        tft.print("Scor: ");
        tft.setCursor(70, 5);
        tft.print(scor);
    }


    if (destroyed >= 10)
    {
        pinMode(A1, OUTPUT);
        pinMode(A2, OUTPUT);
        tft.fillScreen(GREEN);
        tft.setCursor(10, 150);
        tft.setTextSize(3);
        tft.print("Scor: ");
        tft.print(scor);
        delay(5000);
        EcranProfil(slot);
    }

}

void SpaceInvaders(int slot)
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    scor = 0;
    tft.fillScreen(BLACK);
    tft.fillRect(0, 270, 240, 50, RED);
    tft.fillRect(60, 280, 30, 30, WHITE);
    tft.setTextColor(BLACK);
    tft.setTextSize(3);
    tft.setCursor(65, 285);
    tft.print("<");
    tft.fillRect(105, 280, 30, 30, WHITE);
    tft.fillRect(150, 280, 30, 30, WHITE);
    tft.setCursor(155, 285);
    tft.print(">");
    tft.setCursor(5, 5);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("Scor: ");
    tft.setCursor(70, 5);
    tft.print(scor);
    int x = 100;
    drawShip(x);
    for (int i = 0; i < 10; i++)
    {
        randomSeed(analogRead(A14));
        int x = random(0, 200);
        int y = random(40, 150);

        drawObstacle(x, y);
    }

    while (1)
    {

        TSPoint p = ts.getPoint();
        if (p.z > ts.pressureThreshhold)
        {

            if (p.y >= 850 && p.y <= 910)
            {
                if (p.x >= 380 && p.x <= 455)
                {
                    pinMode(A1, OUTPUT);
                    pinMode(A2, OUTPUT);
                    tft.fillRect(0, 220, 240, 50, BLACK);
                    x -= 10;
                    drawShip(x);
                }
                else if (p.x >= 635 && p.x <= 725)
                {
                    pinMode(A1, OUTPUT);
                    pinMode(A2, OUTPUT);
                    tft.fillRect(0, 220, 240, 50, BLACK);
                    x += 10;
                    drawShip(x);
                }
                else if (p.x >= 480 && p.x <= 590)
                {
                    drawGlont(x, 195, slot);
                }
            }

        }
        delay(100);
    }
}

void setup() {
    tft.reset();
    tft.begin(0xE300);
    tft.fillScreen(BLACK);
    tft.setRotation(4);
    Serial.begin(9600);
    Serial1.begin(9600);
    Intro();

}

void loop() {
    // put your main code here, to run repeatedly:

}
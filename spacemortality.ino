
#include <Arduboy2.h>
#include <stdlib.h>

#define NUMBERSTARS 255
#define SCREENWIDTH 128
#define SCREENHEIGHT 64

#define NUMWARPEFFECTFRAMES 240
#define NUMPLANETSURFACEPOINTS 25

#define SHIPXPOS (SCREENWIDTH / 2) + 16
#define SHIPYPOS (SCREENHEIGHT / 2) - 8



#define NUMGRASSPTS 24

#define NUMTREES 1

#define NUMTTILES 7

Arduboy2 arduboy;


Sprites sprite;


// ship
unsigned char const ship[] PROGMEM =
{
  32, 32,
  // 0
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xdf, 0xf0, 0xfc, 0xff, 0xff, 
  0xff, 0xfc, 0xf0, 0xdf, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xc0, 
  0xf0, 0xfc, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x3f, 
  0x3f, 0x3f, 0x3f, 0xff, 0xff, 0xfc, 0xf0, 0xc0, 
  0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};




unsigned char const tree[] PROGMEM =
{
  16, 16,
  // 0
  0x00, 0x00, 0x00, 0x00, 0xf8, 0x80, 0x80, 0xe0, 
  0x38, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 
  0x7f, 0x08, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00, 
};





unsigned char ttile[] = {

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};




uint8_t ttilex[NUMTTILES];
uint8_t ttiley[NUMTTILES];


uint8_t numwarpcrystals;



// Person
unsigned char const person[] PROGMEM =
{
  16, 16,
  // 0
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xa0, 
  0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x05, 
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  // 1
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
  0xb0, 0xe0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x03, 
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  // 2
  0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x80, 
  0x80, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 
  0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
  // 3
  0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xe0, 0xb0, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x03, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 
  // 4
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 
  0xa0, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
  0x05, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  // 5
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
  0xc0, 0x60, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x07, 0x0d, 
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  // 6
  0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 
  0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x01, 
  0x01, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
  // 7
  0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0xc0, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0x0d, 0x07, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 
};




unsigned char const warpcrystals[] PROGMEM =
{
  16, 16,
  // 0
  0x00, 0x00, 0x80, 0x80, 0x60, 0x80, 0x80, 0x00, 
  0xe0, 0xc0, 0x40, 0xb0, 0x40, 0x40, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0x19, 0x0b, 0x03, 
  0x1c, 0x0c, 0x13, 0x3b, 0x11, 0x00, 0x00, 0x00, 
};



// x y coordinates for croshair
// note to save room we'll also 
// use this for the person when exporing planets
int8_t linex = SCREENWIDTH / 2;
int8_t liney = SCREENHEIGHT  / 2;

uint8_t xstarcoords[NUMBERSTARS];
uint8_t ystarcoords[NUMBERSTARS];


uint8_t grasstexturex[NUMGRASSPTS];
uint8_t grasstexturey[NUMGRASSPTS];


uint8_t ttcoordsx[NUMTREES];
uint8_t ttcoordsy[NUMTREES];

// distance from landing site
int16_t lsdistx;
int16_t lsdisty;

bool iswarp = false;
bool isonplanet = false;

bool terriangenerated = false;

bool gameover = false;

unsigned int prevseed = 0;
unsigned int prevseedbackup = 0;

uint8_t personspriteidx = 0;

bool canwarp = true;

// radius of 80 or larger means none type.
typedef struct {

    uint8_t radius;
    uint8_t x;
    uint8_t y;

} Planet;


Planet currplanet = {80, 0, 0};


uint8_t planetsurftextx[NUMPLANETSURFACEPOINTS];
uint8_t planetsurftexty[NUMPLANETSURFACEPOINTS];

void planets(void)
{

    uint8_t isthereplanet = (rand() % 3);

    uint8_t used = 0;

    if (isthereplanet == 1) {

        currplanet = {(rand() % 8) + 3, rand() % SCREENWIDTH, rand() % SCREENHEIGHT};

        uint8_t tlcx = currplanet.x - (currplanet.radius);
        uint8_t brcy = currplanet.y - (currplanet.radius);

        while (used < NUMPLANETSURFACEPOINTS) {

             uint8_t xpos = tlcx + rand() % (currplanet.x + (currplanet.radius * 2));
             uint8_t ypos = brcy + rand() % (currplanet.y + (currplanet.radius * 2));

            if (distance(currplanet.x, currplanet.y, xpos, ypos) < (float)currplanet.radius) {

                planetsurftextx[used] = xpos;
                planetsurftexty[used] = ypos;
                used++;

            }

        }

    } else {

        currplanet = {80, 0, 0};

    }

    

}

void newStars(void)
{

    for (int i = 0; i < NUMBERSTARS; i++) {


        xstarcoords[i] = rand() % SCREENWIDTH;
        ystarcoords[i] = rand() % SCREENHEIGHT;

    }

}



void setup()
{

    arduboy.begin();
    arduboy.setFrameRate(60);

    srand(0);

    newStars();

    numwarpcrystals = 8;

}



void drawStars(void)
{


    for (int i = 0; i < NUMBERSTARS; i++) {


        uint8_t x = xstarcoords[i];
        uint8_t y = ystarcoords[i];


        arduboy.drawPixel(x, y, WHITE);

    }

}




void warpEffect(void)
{

    for (int i = 0; i < NUMWARPEFFECTFRAMES; i++) {

        arduboy.clear();

        for (int c = 0; c < 10; c++) {

            uint8_t xrandom = rand() % SCREENWIDTH;
            uint8_t yrandom = rand() % SCREENHEIGHT;


     
            arduboy.drawLine(xrandom, yrandom, linex, liney, WHITE);
            
            xrandom = rand() % SCREENWIDTH;
            yrandom = rand() % SCREENHEIGHT;

            arduboy.drawLine(xrandom, yrandom, linex, liney, BLACK);

            
        }

        arduboy.display();

    }

}



void crosshair(void)
{

    // horizontal
    arduboy.drawLine(0, liney, 127, liney, WHITE);

    // vertical
    arduboy.drawLine(linex, 0, linex, 63, WHITE);


    if (arduboy.pressed(LEFT_BUTTON) && (linex - 1) >= 0) {

        linex -= 1;

    } 


    if (arduboy.pressed(RIGHT_BUTTON) && (linex + 1) <= 126) {

        linex += 1;

    }


    if (arduboy.pressed(UP_BUTTON) && (liney - 1) >= 0) {

        liney -= 1;

    }


    if (arduboy.pressed(DOWN_BUTTON) && (liney + 1) <= 63) {

        liney += 1;

    }



}



void randomttile(void)
{

    uint8_t bits = 0;

    for (int i = 0; i < 32; i++) {

        for (int j = 0; j < 8; j++) {

            bits = 0;

            if (rand() % 2 == 0) {

                bits |= (1 << (rand() % 8));

            }

        }

        ttile[i] = bits;

    }

}



void randomttilecoords(void)
{


    for (int i = 0; i < NUMTTILES; i++) {

        ttilex[i] = rand() % SCREENWIDTH;
        ttiley[i] = rand() % SCREENHEIGHT;

    }

}



void randomGrassTexture(void)
{


    for (int i = 0; i < NUMGRASSPTS; i++) {

        grasstexturex[i] = rand() % SCREENWIDTH;
        grasstexturey[i] = rand() % SCREENHEIGHT;

    }


}



void randTerrainPlacement(void)
{

    for (int i = 0; i < NUMTREES; i++) {

        ttcoordsx[i] = rand() % SCREENWIDTH;
        ttcoordsy[i] = rand() % SCREENHEIGHT;

    }

}




void randomPlanetTerrain(void)
{

    randTerrainPlacement();

}



float distance(uint8_t sx, uint8_t sy, uint8_t dx, uint8_t dy)
{

    float fsx = (float)sx;
    float fsy = (float)sy;
    float fdx = (float)dx;
    float fdy = (float)dy;

    float ycomponent = (dy - sy) * (dy - sy);
    float xcomponent = (dx - sx) * (dx - sx);

    return sqrt(ycomponent + xcomponent);

}



bool leftclamp(uint8_t* coord)
{


    if (*coord - 1 >= 0) {

        *coord = *coord - 1;

    }

    if (*coord == 0) {

        return true;

    }


    return false;

}



bool downclamp(uint8_t* coord)
{


    if (*coord - 1 >= 0) {

        *coord = *coord - 1;

    }


    if (*coord == 0) {

        return true;

    }


    return false;

}


bool rightclamp(uint8_t* coord)
{

    if (*coord + 1 <= 126) {

        *coord = *coord + 1;

    }


    if (*coord == 126) {

        return true;

    }


    return false;

}


bool upclamp(uint8_t* coord)
{


    if (*coord + 1 <= 63) {

        *coord = *coord + 1;

    }

    if (*coord == 63) {

        return true;

    }


    return false;

}




void inSpace(void)
{

        drawStars();

        if (currplanet.radius < 80) {

        arduboy.fillCircle(currplanet.x, currplanet.y, currplanet.radius, WHITE);

        int amount = currplanet.radius * currplanet.radius;

        for (int i = 0; i < NUMPLANETSURFACEPOINTS; i++) {

           arduboy.drawPixel(planetsurftextx[i], planetsurftexty[i], BLACK);

        }

        if (distance(currplanet.x, currplanet.y, (uint8_t)linex, (uint8_t)liney) <= (float)(currplanet.radius) &&
            (currplanet.radius < 80)) {

            arduboy.digitalWriteRGB(RGB_ON, RGB_OFF, RGB_OFF);

            canwarp = false;

        } else {

            arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);

            canwarp = true;

        }  

    }


    arduboy.setCursor(0, 0);
    arduboy.print("Warp core: ");
    arduboy.setCursor(60, 0);
    arduboy.print(numwarpcrystals);


}



void initWarp(void)
{

    iswarp = true;

    srand(linex + liney + prevseed);
    prevseed = rand();   


}



void warp(void)
{

    warpEffect();
    iswarp = false;

    newStars();

    planets();

}



void initLandingParty(void)
{

    // landing party
    // landing party initialization should go here

    // we get the seed and back it up.
    prevseedbackup = prevseed;

    // we generate a new seed which has products of prime numbers added to it
    prevseed = rand();

    isonplanet = true;



    // e.g no planets.
    currplanet = {255, 0, 0};

    linex = SCREENWIDTH / 2;
    liney = SCREENHEIGHT / 2;

}




void onPlanet(void)
{

    bool isnearship = false;

    if (!(terriangenerated)) {

        lsdistx = 0;
        lsdisty = 0;

        randomttile();

        randomttilecoords();

        randomGrassTexture();
        randomPlanetTerrain();
        terriangenerated = true;

        arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);

        arduboy.invert(true);

    }



    for (uint8_t j = 0; j < NUMGRASSPTS; j++) {

        arduboy.drawPixel(grasstexturex[j], grasstexturey[j], WHITE);

    }


    // draw terrian tiles
    for (uint8_t i = 0; i < NUMTREES; i++) {

        sprite.drawSelfMasked(ttcoordsx[i], ttcoordsy[i], tree, 0);

    }


    // draw terrian tiles
    for (uint8_t i = 0; i < NUMTTILES; i++) {

        uint8_t xt = ttilex[i];
        uint8_t yt = ttiley[i];

        for (uint8_t z = 0; z < 32; z++) {

            uint8_t curtile = ttile[z];

            for (uint8_t c = 0; c < 8; c++) {

                if ((1 << c) & (curtile)) {

                    arduboy.drawPixel(xt + (z % 8), yt + c, WHITE);

                }

            }

        }

    }


    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;


    if (arduboy.pressed(LEFT_BUTTON) && arduboy.pressed(UP_BUTTON)) {

        personspriteidx = 1;

        left = leftclamp(&linex);
        down = downclamp(&liney);

    } else if (arduboy.pressed(LEFT_BUTTON) && arduboy.pressed(DOWN_BUTTON)) {

        personspriteidx = 7;

        left = leftclamp(&linex);
        up = upclamp(&liney);
    
    } else if (arduboy.pressed(UP_BUTTON) && arduboy.pressed(RIGHT_BUTTON)) {

        personspriteidx = 3;

        down = downclamp(&liney);
        right = rightclamp(&linex);

    } else if (arduboy.pressed(DOWN_BUTTON) && arduboy.pressed(RIGHT_BUTTON)) {

        personspriteidx = 5;

        up = upclamp(&liney);
        right = rightclamp(&linex);
    
    } else if (arduboy.pressed(LEFT_BUTTON)) {

        personspriteidx = 0;

        left = leftclamp(&linex);

    } else if (arduboy.pressed(RIGHT_BUTTON)) {

        personspriteidx = 4;

        right = rightclamp(&linex);

    } else if (arduboy.pressed(UP_BUTTON)) {

        personspriteidx = 2;

        down = downclamp(&liney);

    } else if (arduboy.pressed(DOWN_BUTTON)) {

        personspriteidx = 6;

        up = upclamp(&liney);

    }


    if (left) {
        // inverse must be done for right
        lsdistx -= 1;

        linex = 120;

        if (lsdistx == 0 && lsdisty == 0) {

            srand(prevseed);

        }
        
        randomttilecoords();

        randomGrassTexture();
        randomPlanetTerrain();


    } else if (right) {

        lsdistx += 1;

        linex = 10;

        if (lsdistx == 0 && lsdisty == 0) {

            srand(prevseed);

        }

        randomttilecoords();

        randomGrassTexture();
        randomPlanetTerrain();

    } else if (up) {

        lsdisty += 1;

        liney = 10;

        if (lsdistx == 0 && lsdisty == 0) {

            srand(prevseed);

        }

        randomttilecoords();

        randomGrassTexture();
        randomPlanetTerrain();

    } else if (down) {

        lsdisty -= 1;

        liney = 50;

        if (lsdistx == 0 && lsdisty == 0) {

            srand(prevseed);

        }

        randomttilecoords();

        randomGrassTexture();
        randomPlanetTerrain();

    }


    sprite.drawSelfMasked(linex - 8, liney - 8, person, personspriteidx);

    if (lsdisty == 0 && lsdistx == 0) {

        sprite.drawSelfMasked(SHIPXPOS, SHIPYPOS, ship, 0);

        if (distance((float)linex, (float)liney, (float)SHIPXPOS + 16, (float)SHIPYPOS + 16) < 7.0 && numwarpcrystals > 0) {

            isnearship = true;

            arduboy.digitalWriteRGB(RGB_OFF, RGB_ON, RGB_OFF);

        } else {

            arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);

        }

    }

    if (isnearship && arduboy.pressed(A_BUTTON)) {

        arduboy.invert(false);

        iswarp = true;
        canwarp = true;
        isonplanet = false;

        arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);

        srand(prevseedbackup);
    }

}



void loop()
{


    if (!arduboy.nextFrame()) {
        

        return ;

    }

    arduboy.clear();

    if (!(isonplanet) && !(gameover)) {

        inSpace();    

    }


    arduboy.pollButtons();


    if (!(gameover)) {


            // warpdrive
        if (arduboy.justPressed(A_BUTTON) && (!(iswarp)) && (!(isonplanet))) {


            if (canwarp && numwarpcrystals > 0) {

                numwarpcrystals--;

                initWarp();

            } else if (numwarpcrystals >= 0 && (!canwarp) && currplanet.radius < 80) {

                terriangenerated = false;
                initLandingParty();

            } else {

                if (currplanet.radius >= 80) {

                    gameover = true;

                }

            }

        }


        if (!(iswarp) && (!(isonplanet)) && !(gameover)) {

            crosshair();

        } else if (iswarp && !(gameover)) {

            warp();

            return ;

        } else if (!(gameover)) {

            // landing party stuff here
            onPlanet();
        }


        if (!(isonplanet) && !(gameover)) {

            arduboy.setCursor(90, 56);
            arduboy.print(linex);

            arduboy.setCursor(110, 56);
            arduboy.print(liney);

        } else if (!gameover) {

            arduboy.setCursor(0, 56);
            arduboy.print(lsdistx);

            arduboy.setCursor(15, 56);
            arduboy.print(lsdisty);

        }

    } else {

        arduboy.clear();

        arduboy.print("Game Over");

    }

    
    arduboy.display();

}




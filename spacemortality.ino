
#include <Arduboy2.h>
#include <stdlib.h>

#define NUMBERSTARS 100
#define SCREENWIDTH 128
#define SCREENHEIGHT 64

#define NUMWARPEFFECTFRAMES 240
#define NUMPLANETSURFACEPOINTS 25

#define SHIPXPOS (SCREENWIDTH / 2) - 16
#define SHIPYPOS (SCREENHEIGHT / 2) - 16


#define NUMTREES 2
#define NUMTILEBYTES 4

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




uint8_t protree[] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};






unsigned char ttile[] = {

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};



uint8_t ttilecoords[NUMTILEBYTES];

uint8_t numwarpcrystals;
uint8_t numammo = 0;


// person
unsigned char const person[] PROGMEM =
{
  8, 8,
  // 0
  0x00, 0x00, 0x00, 0x99, 0xff, 0x00, 0x00, 0x00, 
  // 1
  0x00, 0x20, 0x40, 0x30, 0x18, 0x0a, 0x04, 0x00, 
  // 2
  0x18, 0x10, 0x10, 0x18, 0x18, 0x10, 0x10, 0x18, 
  // 3
  0x00, 0x04, 0x0a, 0x18, 0x30, 0x40, 0x20, 0x00, 
  // 4
  0x00, 0x00, 0x00, 0xff, 0x99, 0x00, 0x00, 0x00, 
  // 5
  0x00, 0x20, 0x50, 0x18, 0x0c, 0x02, 0x04, 0x00, 
  // 6
  0x18, 0x08, 0x08, 0x18, 0x18, 0x08, 0x08, 0x18, 
  // 7
  0x00, 0x04, 0x02, 0x0c, 0x18, 0x50, 0x20, 0x00, 
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




// ammo
unsigned char const ammosprite[] PROGMEM =
{
  16, 16,
  // 0
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 
  0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 
  0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 

};






// x y coordinates for croshair
// note to save room we'll also 
// use this for the person when exporing planets
int8_t linex = SCREENWIDTH / 2;
int8_t liney = SCREENHEIGHT  / 2;

uint8_t xstarcoords[NUMBERSTARS];
uint8_t ystarcoords[NUMBERSTARS];

uint8_t ttcoordsx[NUMTREES];
uint8_t ttcoordsy[NUMTREES];

// distance from landing site
int16_t lsdistx;
int16_t lsdisty;

bool iswarp = false;
bool isonplanet = false;
bool firedshot = false;

bool terriangenerated = false;

bool itemcollected = false;

bool gameover = false;

unsigned int prevseed = 0;
unsigned int prevseedbackup = 0;

uint8_t personspriteidx = 0;

bool canwarp = true;
bool statusscreen = false;

// radius of 80 or larger means none type.
typedef struct {

    uint8_t radius;
    uint8_t x;
    uint8_t y;

    bool habitable;

} Planet;


// if not ammo, it's warp crystals.
bool isammo = false;
uint8_t itemcoordsxy[2];
int8_t  itemmapcoords[2];

Planet currplanet = {80, 0, 0, false};


uint8_t planetsurftextx[NUMPLANETSURFACEPOINTS];
uint8_t planetsurftexty[NUMPLANETSURFACEPOINTS];

void planets(void)
{

    uint8_t isthereplanet = (rand() % 2);

    uint8_t used = 0;

    if (isthereplanet == 1) {

        currplanet = {(rand() % 8) + 3, rand() % SCREENWIDTH, rand() % SCREENHEIGHT, false};

        if (rand() % 2 == 0) {

            currplanet.habitable = true;

        }

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

        currplanet = {80, 0, 0, false};

    }

}


void proceduraltrees(void)
{

    
    uint8_t xpos = 0;
    uint8_t ypos = 0;


    for (int i = 0; i < 32; i++) {

        protree[i] = 0x00;

    }


    for (int b = 0; b < 3; b++) {

        xpos = 8;
        ypos = 15;

        for (int i = 0; i < 10; i++) {

            if (rand() % 3 == 0) {

                if ((xpos - 1) < xpos) {

                    xpos--;

                }

            } else if (rand() % 3 == 1) {

                if ((xpos + 1) > xpos) {

                    xpos++;

                }

            }

            uint8_t bitindex = ypos * 16 + xpos;
            uint8_t byteindex =  bitindex / 8;

            protree[byteindex] |= (1 << (bitindex % 8));

            ypos--;

        }

    }

}




void placeItem(void)
{


    // position on screen
    itemcoordsxy[0] = SCREENWIDTH / 2;
    itemcoordsxy[1] = SCREENHEIGHT / 2;

    if (rand() % 2 == 0) {

        isammo = true;

    } else {

        isammo = false;

    }

    // position on planet
    int8_t xpos = 0;
    int8_t ypos = 0;

    while (xpos == 0 && ypos == 0) {

        xpos = (rand() % 10) * (1 - (2 * (rand() % 2)));
        ypos = (rand() % 10) * (1 - (2 * (rand() % 2)));

    }


    itemmapcoords[0] = xpos;
    itemmapcoords[1] = ypos;

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
    numammo = 16;

    arduboy.invert(false);

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
    arduboy.drawLine(linex - 4, liney, linex + 4, liney, WHITE);

    // vertical
    arduboy.drawLine(linex, liney - 4, linex, liney + 4, WHITE);


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



    if (arduboy.justPressed(B_BUTTON) && numammo > 0) {

        arduboy.drawLine(0, 0, linex, liney, WHITE);
        arduboy.drawLine(128, 0, linex, liney, WHITE);
        arduboy.drawLine(0, 64, linex, liney, WHITE);
        arduboy.drawLine(128, 64, linex, liney, WHITE);

        firedshot = true;

        numammo--;

    } else if (arduboy.justReleased(B_BUTTON)) {

        firedshot = false;

    }


}



void randomttile(void)
{

    uint8_t bits = 0;

    for (int i = 0; i < 32; i++) {

        bits = 0;

        for (int j = 0; j < 8; j++) {

            if (rand() % 64 == 0) {

                bits |= (1 << (rand() % 8));

            }

        }

        ttile[i] = bits;

    }

}




void statusReport(void)
{

    arduboy.clear();
    arduboy.invert(false);

    arduboy.setCursor(0, 0);
    arduboy.print("Warp: ");
    arduboy.setCursor(40, 0);
    arduboy.print(numwarpcrystals);

    arduboy.setCursor(0, 8);
    arduboy.print("Ammo: ");
    arduboy.setCursor(40, 8);
    arduboy.print(numammo);

    arduboy.setCursor(0, 16);
    arduboy.print("Return to ship");

    arduboy.setCursor(0, 24);
    arduboy.print("Press B");

    if (arduboy.justPressed(B_BUTTON)) {

        arduboy.invert(true);
        statusscreen = false;

    }


}




void randomttilecoords(void)
{


    for (int i = 0; i < NUMTILEBYTES; i++) {

        ttilecoords[i] = (rand() % 256);

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

            if (!(currplanet.habitable)) {

                arduboy.setCursor(0, 56);
                arduboy.print("uninhabitable");

            }

        } else {

            arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);

            canwarp = true;

        } 

    }


    if ((!canwarp) && firedshot) {

        currplanet.radius = 80;
        currplanet.x = 0;
        currplanet.y = 0;

        arduboy.fillScreen(WHITE);

        arduboy.display();

        arduboy.delayShort(500);

        canwarp = true;

        firedshot = false;

        arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);


    }


    arduboy.setCursor(0, 0);
    arduboy.print("Warp: ");
    arduboy.setCursor(35, 0);
    arduboy.print(numwarpcrystals);

    arduboy.setCursor(60, 0);
    arduboy.print("Ammo: ");
    arduboy.setCursor(95, 0);
    arduboy.print(numammo);


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
    liney = (SCREENHEIGHT / 2) - 16;

}


void onPlanet(void)
{

    bool isnearship = false;

    if (!(terriangenerated)) {

        lsdistx = 0;
        lsdisty = 0;

        randomttile();

        placeItem();

        itemcollected = false;

        randomttilecoords();

        proceduraltrees();

        randomPlanetTerrain();
        terriangenerated = true;

        arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);

        arduboy.invert(true);

    }



    // draw terrian tiles
    for (uint8_t i = 0; i < NUMTREES; i++) {


        uint8_t txc = ttcoordsx[i];
        uint8_t tyc = ttcoordsy[i];


        int xx = 0;
        int yy = 0;

        for (int b = 0; b < 32; b++) {

            uint8_t artbyte = protree[b];

            for (int i = 0; i < 8; i++) {

                if ((1 << i) & artbyte) {

                    arduboy.drawPixel(txc + (xx), tyc + (yy), WHITE);

                }

                if (xx >= 16) {

                    yy++;
                    xx = 0;

                }

                xx++;

            }

        }

    }


    // // draw terrian tiles
    uint8_t xx = 0;
    uint8_t yy = 0;

    // 8 tiles x
    // 4 tiles y

    for (uint8_t b = 0; b < NUMTILEBYTES; b++) {

        uint8_t currtbyte = ttilecoords[b];

        for (uint8_t c = 0; c < 8; c++) {

            uint8_t basex = c * 16;
            uint8_t basey = b * 16;

            uint8_t byteidx = 0;

            uint8_t count = 0;

            uint8_t pixelsbyte = 0;

            if ((1 << c) & (currtbyte)) {

                for (int hoz = 0; hoz < 16; hoz++) {

                    for (int vert = 0; vert < 16; vert++) {

                        if (count % 8 == 0) {

                            pixelsbyte = ttile[byteidx++];

                        }

                        if ((1 << (count % 8)) & (pixelsbyte)) {

                            arduboy.drawPixel(basex + hoz, basey + vert, WHITE);

                        }

                        count++;

                    }

                }

            }

        }

    }


    if (!(itemcollected)) {

            arduboy.setCursor(0,0);
            arduboy.print("Item at: ");
            arduboy.setCursor(50, 0);

            int8_t xloc = itemmapcoords[0];
            int8_t yloc = itemmapcoords[1];

            arduboy.print(xloc);
            arduboy.setCursor(65, 0);
            arduboy.print(yloc);

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

        randomPlanetTerrain();


    } else if (right) {

        lsdistx += 1;

        linex = 10;

        if (lsdistx == 0 && lsdisty == 0) {

            srand(prevseed);

        }

        randomttilecoords();

        randomPlanetTerrain();

    } else if (up) {

        lsdisty += 1;

        liney = 10;

        if (lsdistx == 0 && lsdisty == 0) {

            srand(prevseed);

        }

        randomttilecoords();

        randomPlanetTerrain();

    } else if (down) {

        lsdisty -= 1;

        liney = 50;

        if (lsdistx == 0 && lsdisty == 0) {

            srand(prevseed);

        }

        randomttilecoords();

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

    } else if (lsdistx == itemmapcoords[0] && lsdisty == itemmapcoords[1]) { 

        if (!(itemcollected)) {

                uint8_t offset = 8;

                sprite.drawSelfMasked(itemcoordsxy[0] - offset, itemcoordsxy[1] - offset, (isammo) ? ammosprite : warpcrystals, 0);

                if (distance((float)linex, 
                             (float)liney, 
                             (float)(itemcoordsxy[0] - offset  + 8), 
                             (float)(itemcoordsxy[1] - offset) + 8) < 5.0) {

                    (isammo) ? numammo += 4 : numwarpcrystals += 4;

                    itemcollected = true;
                    statusscreen = true;

                    arduboy.setCursor(0, 0);
                    arduboy.print((isammo) ? "+1 Ammo" : "+1 Warp");

                }

        }



    }

    if (isnearship && arduboy.pressed(A_BUTTON)) {

        arduboy.invert(false);

        iswarp = true;
        canwarp = true;
        isonplanet = false;

        numwarpcrystals--;

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

    if (!(isonplanet) && !(gameover) && !(statusscreen)) {

        inSpace();    

    }


    arduboy.pollButtons();


    if (!(gameover) && !(statusscreen)) {


            // warpdrive
        if (arduboy.justPressed(A_BUTTON) && (!(iswarp)) && (!(isonplanet))) {


            if (canwarp && numwarpcrystals > 0) {

                numwarpcrystals--;

                initWarp();

            } else if (numwarpcrystals >= 0 && (!canwarp) && currplanet.radius < 80) {

                if (currplanet.habitable) {

                    terriangenerated = false;
                    initLandingParty();

                } 
                

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

            arduboy.setCursor(20, 56);
            arduboy.print(lsdisty);

        }

    } else if (!(statusscreen)) {

        arduboy.clear();

        arduboy.print("Game Over");

    } else {

        statusReport();
    }

    
    arduboy.display();

}




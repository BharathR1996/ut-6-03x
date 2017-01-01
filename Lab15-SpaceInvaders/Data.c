//****************************************************************************
//
// UTAustinX: UT.6.03x Embedded Systems - Shape the World
// Lab 15: SpaceInvaders
//
// File Name: Images.c
//
// Description: Contain all images data and their sizes
//
// Compatibility: EK-TM4C123GXL
//
// Phi Luu
// Portland, Oregon, United States
// Created May 20, 2016
// Updated December 31, 2016
//
//****************************************************************************

#include "Data.h"
#include "Nokia5110.h"

// Game data
const unsigned char *EnemyFrameA[3] = {
    SmallEnemy30PointA,     // 30 points, frame A
    SmallEnemy20PointA,     // 20 points, frame A
    SmallEnemy10PointA      // 10 points, frame A
};
const unsigned char *EnemyFrameB[3] = {
    SmallEnemy30PointB,     // 30 points, frame B
    SmallEnemy20PointB,     // 20 points, frame B
    SmallEnemy10PointB      // 10 points, frame B
};
const unsigned short EnemyScore[3] = {
    30,
    20,
    10
};
typedef struct State Thing;
Thing Ship;
Thing Bunker;
Thing Enemy[MAXENEMY];
Thing Mothership;
Thing Missile[MAXMISSILE];
Thing Laser[MAXLASER];
unsigned char nMissile;
unsigned char nLaser;
//---
// Initialize ship, bunker, enemy, mothership, missile, and laser
//---
void Init_Thing(void) {
    unsigned char i;

    // ship
    Ship.name = "ship";
    Ship.width = SHIPW;
    Ship.height = SHIPH;
    Ship.x = (SCREENW - SHIPW) / 2;     // center alignment
    Ship.y = (SCREENH - 1);             // bottom screen
    Ship.life = 3;                      // player has maximum 3 lives
    Ship.score = 0;                     // player's score
    Ship.frame = 0;                     // first frame
    Ship.image[0] = PlayerShip0;        // undamaged
    Ship.image[1] = PlayerShip1;        // moderate generic damaged
    Ship.image[2] = PlayerShip2;        // heavy generic damaged
    Ship.explode[0] = BigExplosion0;
    Ship.explode[1] = BigExplosion1;
    Ship.blank = PlayerShip3;
    // bunker
    Bunker.name = "bunker";
    Bunker.width = BUNKERW;
    Bunker.height = BUNKERH;
    Bunker.x = (SCREENW - BUNKERW) / 2; // center alignment
    Bunker.y = SCREENH - SHIPH - 1;     // right above player's ship
    Bunker.life = 3;                    // bunker tolerates maximum 3 lasers
    Bunker.frame = 0;                   // first frame
    Bunker.image[0] = Bunker0;          // undamaged
    Bunker.image[1] = Bunker1;          // moderate generic damaged
    Bunker.image[2] = Bunker2;          // heavy generic damaged
    Bunker.explode[0] = Bunker3;
    // enemy
    for (i = 0; i < MAXENEMY; i++) {
        Enemy[i].name = "enemy";
        Enemy[i].width = ENEMYW;
        Enemy[i].height = ENEMYH;
        Enemy[i].x = ENEMYW * i;                // equally distant row
        Enemy[i].y = ENEMYH - 1;                // top screen
        Enemy[i].life = 1;                      // one shot one kill
        Enemy[i].score = EnemyScore[i % 3];     // score by killing enemy
        Enemy[i].frame = 0;                     // first frame
        Enemy[i].image[0] = EnemyFrameA[i % 3]; // frame 1
        Enemy[i].image[1] = EnemyFrameB[i % 3]; // frame 2
        Enemy[i].explode[0] = SmallExplosion0;
        Enemy[i].explode[1] = SmallExplosion1;
        Enemy[i].blank = SmallEnemyMoved;
    }
    // mothership
    Mothership.name = "mothership";
    Mothership.width = MOTHERSHIPW;
    Mothership.height = MOTHERSHIPH;
    Mothership.x = (SCREENW - MOTHERSHIPW) / 2;     // center alignment
    Mothership.y = MOTHERSHIPH - 1;                 // top screen
    Mothership.life = 3;                            // 3 shots to kill
    Mothership.score = MOTHERSHIPSCORE;
    Mothership.frame = 0;                           // first frame
    Mothership.image[0] = SmallEnemyBonus0;
    Mothership.image[1] = SmallEnemyBonus1;
    Mothership.image[2] = SmallEnemyBonus2;
    Mothership.explode[0] = SmallExplosion0;
    Mothership.explode[1] = SmallExplosion1;
    Mothership.blank = SmallEnemyBonusMoved;
    // laser
    nLaser = 0;                                   // no laser
    for (i = 0; i < MAXLASER; i++) {
        Laser[i].name = "laser";
        Laser[i].width = LASERW;
        Laser[i].height = LASERH;
        Laser[i].life = 0;                        // no life until being fired
        Laser[i].frame = 0;
        Laser[i].image[0] = Laser0;
        Laser[i].explode[0] = Laser1;
        Laser[i].blank = Laser1;
    }
    // missile
    nMissile = 0;                                 // no missile
    for (i = 0; i < MAXMISSILE; i++) {
        Missile[i].name = "missile";
        Missile[i].width = MISSILEW;
        Missile[i].height = MISSILEH;
        Missile[i].life = 0;                      // no life until being fired
        Missile[i].frame = 0;
        Missile[i].image[0] = Missile0;
        Missile[i].image[1] = Missile1;
        Missile[i].explode[0] = Missile2;
        Missile[i].blank = Missile2;
    }
}

// Image data
// enemy ship that arm and mouths are closed
// width = 16 x height = 10
const unsigned char SmallEnemy30PointA[] = {
    0x42, 0x4D, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0A, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0xF0,
    0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00,
    0x0F, 0x0F, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x0F, 0xF0, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// enemy ship that arms and mouth are open
// width = 16 x height = 10
const unsigned char SmallEnemy30PointB[] = {
    0x42, 0x4D, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0A, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0xF0,
    0xF0, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00,
    0x0F, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x0F, 0xF0, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// enemy ship that arms are together
// width = 16 x height = 10
const unsigned char SmallEnemy20PointA[] = {
    0x42, 0x4D, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0A, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0x0F, 0xF0, 0x0F, 0xF0, 0x0F, 0xF0, 0x00, 0x00, 0x00,
    0xFF, 0xF0, 0x0F, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0x00, 0x00, 0xFF, 0xF0, 0x0F, 0xF0, 0x0F, 0xFF, 0x00, 0x00, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF,
    0xF0, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// enemy ship that arms are apart
// width = 16 x height = 10
const unsigned char SmallEnemy20PointB[] = {
    0x42, 0x4D, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0A, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00,
    0x0F, 0xF0, 0x00, 0x0F, 0xF0, 0x0F, 0xF0, 0x0F, 0xF0, 0x00, 0x00, 0x00,
    0xFF, 0xF0, 0x0F, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0x00, 0x00, 0xFF, 0xF0, 0x0F, 0xF0, 0x0F, 0xFF, 0x00, 0x00, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF,
    0xF0, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// enemy ship that arms are down
// width = 16 x height = 10
const unsigned char SmallEnemy10PointA[] = {
    0x42, 0x4D, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0A, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x0F, 0xF0,
    0x00, 0x00, 0x00, 0xF0, 0xF0, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0x00, 0x00, 0x0F, 0xF0, 0xFF, 0xFF, 0x0F, 0xF0, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0xF0,
    0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// enemy ship that arms are up
// width = 16 x height = 10
const unsigned char SmallEnemy10PointB[] = {
    0x42, 0x4D, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0A, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00,
    0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x0F,
    0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0x00, 0x00, 0xFF, 0xF0, 0xFF, 0xFF, 0x0F, 0xFF, 0x00, 0x00, 0xF0,
    0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0xF0, 0x0F, 0x00, 0x00, 0xF0,
    0x0F, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// blank space used to cover an enemy that is moved
const unsigned char SmallEnemyMoved[] = {
    0x42, 0x4D, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0A, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// the player's ship (undamaged)
// width = 18 x height = 8
const unsigned char PlayerShip0[] = {
    0x42, 0x4D, 0xD6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x08, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00,
    0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xAA,
    0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA,
    0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA,
    0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A,
    0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0A, 0xAA, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0A, 0xAA, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// the player's ship (moderate generic damage)
// width = 18 x height = 8
const unsigned char PlayerShip1[] = {
    0x42, 0x4D, 0xD6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x08, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00,
    0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xAA,
    0xAA, 0xAA, 0xAA, 0xAA, 0x0A, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA,
    0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0,
    0xAA, 0xAA, 0xAA, 0xA0, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xAA, 0xAA, 0xAA, 0xAA, 0xA0, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0A, 0xAA, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0A, 0xAA, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// the player's ship (heavy generic damage)
// width = 18 x height = 8
const unsigned char PlayerShip2[] ={
    0x42, 0x4D, 0xD6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x08, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00,
    0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x0A,
    0xAA, 0x0A, 0xA0, 0x00, 0x0A, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A,
    0xA0, 0xA0, 0x0A, 0x00, 0x0A, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0,
    0x0A, 0x0A, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xAA, 0xAA, 0xA0, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0A, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0A, 0xAA, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// blank space used to cover a ship that is moved
// width = 18 x height = 8
const unsigned char PlayerShip3[] = {
    0x42, 0x4D, 0xD6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x08, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00,
    0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// small, fast bonus enemy that occasionally appears
// after enough enemies have been killed to make a room for it
// width = 20 x height = 7
const unsigned char SmallEnemyBonus0[] = {
    0x42, 0x4D, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x07, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x54, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x0F, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xF0, 0x0F, 0xF0, 0x0F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x0F,
    0xF0, 0xFF, 0x0F, 0xF0, 0xFF, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// small, fast bonus enemy that occasionally appears
// after enough enemies have been killed to make a room for it
// (moderate generic damaged)
// width = 20 x height = 7
const unsigned char SmallEnemyBonus1[] = {
    0x42, 0x4D, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x07, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x54, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x0F, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xF0, 0x00, 0x0F, 0x00, 0x0F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
    0xFF, 0xF0, 0xFF, 0x0F, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x0F,
    0xF0, 0xF0, 0x0F, 0xF0, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0F, 0xFF, 0xF0, 0x00, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// small, fast bonus enemy that occasionally appears
// after enough enemies have been killed to make a room for it
// (heavy generic damaged)
// width = 20 x height = 7
const unsigned char SmallEnemyBonus2[] = {
    0x42, 0x4D, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x07, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x54, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xF0, 0x00, 0x0F, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F,
    0x0F, 0xF0, 0xFF, 0x0F, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x0F,
    0x00, 0xF0, 0x0F, 0xF0, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0F, 0x0F, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xFF, 0xF0, 0x00, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0F, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

const unsigned char SmallEnemyBonusMoved[] = {
    0x42, 0x4D, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x07, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x54, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// small shield floating in space to cover the player's (undamaged)
// width = 18 x height = 5
const unsigned char Bunker0[] = {
    0x42, 0x4D, 0xB2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x05, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00,
    0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xAA, 0xAA,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0xAA, 0xAA,
    0xA0, 0x00, 0x00, 0x00, 0x0A, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0xAA, 0xAA,
    0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x0A, 0xAA,
    0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0, 0x00, 0x00, 0x00, 0x00, 0xAA,
    0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// small shield floating in space to cover the player's ship
// (moderate generic damage)
// width = 18 x height = 5
const unsigned char Bunker1[] = {
    0x42, 0x4D, 0xB2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x05, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00,
    0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xAA, 0xAA,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0xAA, 0xAA,
    0xA0, 0x00, 0x00, 0x00, 0x0A, 0xAA, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x0A,
    0xAA, 0xAA, 0xAA, 0xAA, 0xA0, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x0A, 0xAA,
    0x0A, 0xA0, 0xA0, 0xAA, 0xAA, 0xA0, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xA0, 0xA0, 0x00, 0x0A, 0x0A, 0x0A, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// small shield floating in space to cover the player's ship
// (heavy generic damage)
// width = 18 x height = 5
const unsigned char Bunker2[] = {
    0x42, 0x4D, 0xB2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x05, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00,
    0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x0A, 0x0A,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xAA, 0x00, 0x00, 0x00, 0xAA, 0x0A,
    0xA0, 0x00, 0x00, 0x00, 0x0A, 0xAA, 0x0A, 0x00, 0x00, 0x00, 0x0A, 0x0A,
    0x0A, 0xA0, 0xAA, 0xA0, 0xA0, 0xA0, 0xA0, 0x00, 0x00, 0x00, 0x00, 0xAA,
    0x0A, 0x00, 0xA0, 0xA0, 0xA0, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xA0, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// blank space used to cover a bunker that is destroyed
// width = 18 x height = 5
const unsigned char Bunker3[] = {
    0x42, 0x4D, 0xB2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x05, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00,
    0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// large explosion that can be used upon the demise of the player's ship
// (first frame)
// width = 18 x height = 8
const unsigned char BigExplosion0[] = {
    0x42, 0x4D, 0xD6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x08, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x0A, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90,
    0x00, 0x90, 0xB0, 0x0A, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B,
    0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0xA0,
    0x00, 0xE0, 0x00, 0x00, 0x90, 0x90, 0x9A, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xA0, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90,
    0x00, 0x00, 0xA0, 0x00, 0x00, 0xAE, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00,
    0x00, 0xE0, 0x0A, 0x0A, 0x00, 0x00, 0xB0, 0x00, 0x00, 0x00, 0xA0, 0x00,
    0x09, 0x00, 0x00, 0x00, 0x90, 0x00, 0x0A, 0x00, 0x00, 0x00, 0xFF
};

// large explosion that can be used upon the demise of the player's ship
// (second frame)
// width = 18 x height = 8
const unsigned char BigExplosion1[] = {
    0x42, 0x4D, 0xD6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x08, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x0E, 0x00,
    0x09, 0x00, 0x09, 0x00, 0xB0, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA9, 0x00,
    0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0E, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0xE0, 0x00,
    0x0A, 0x00, 0x90, 0x00, 0xB0, 0x00, 0x09, 0x00, 0x00, 0x00, 0xFF
};

// small explosion best used for the demise of a sprite or a mothership
// (first frame)
// width = 16 x height = 10
const unsigned char SmallExplosion0[] = {
    0x42, 0x4D, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0A, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x0F, 0x00, 0x0F, 0x00,
    0xF0, 0x00, 0x00, 0x0F, 0x00, 0xF0, 0xF0, 0x0F, 0x00, 0x00, 0x00, 0x00,
    0xF0, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x0F,
    0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0x00, 0xF0, 0xF0, 0x00,
    0xF0, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// blank space following the small explosion for the demise of
// a sprite or a mothership
// (second frame)
// width = 16 x height = 10
const unsigned char SmallExplosion1[] = {
    0x42, 0x4D, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0A, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// a missile in flight (left skewed)
// width = 4 x height = 9
const unsigned char Missile0[] = {
    0x42, 0x4D, 0x9A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x09, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x0F, 0x00,
    0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0xF0, 0x00,
    0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// a missile in flight (right skewed)
// width = 4 x height = 9
const unsigned char Missile1[] = {
    0x42, 0x4D, 0x9A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x09, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0xF0,
    0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x0F,
    0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// blank space to cover a missile after it hits something
// width = 4 x height = 9
const unsigned char Missile2[] = {
    0x42, 0x4D, 0x9A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x09, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// a laser burst in flight
// width = 2 x height = 9
const unsigned char Laser0[] = {
    0x42, 0x4D, 0x9A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x09, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x99, 0x00, 0x00, 0x00, 0xBB, 0x00, 0x00, 0x00, 0xAA, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

// blank space to cover a laser after it hits something
// width = 2 x height = 9
const unsigned char Laser1[] = {
    0x42, 0x4D, 0x9A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00,
    0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x09, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80,
    0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};


//**********Sound Data**********
// shoot.wav converted to array
const unsigned char shoot[SHOOTSIZE] = {
    8, 6, 6, 10, 13, 8, 2, 7, 13, 7, 3, 6, 9, 14, 10, 4, 5, 10, 12, 6, 5, 8,
    13, 8, 3, 6, 8, 13, 10, 5, 5, 8, 12, 7, 4, 8, 13, 9, 4, 7, 9, 11, 7, 3, 8,
    13, 8, 5, 7, 13, 15, 6, 3, 5, 10, 7, 2, 5, 9, 13, 12, 12, 12, 7, 6, 1, 0,
    5, 10, 7, 8, 15, 15, 15, 7, 0, 0, 0, 0, 0, 6, 15, 15, 15, 15, 15, 12, 0,
    0, 0, 1, 11, 10, 9, 15, 15, 15, 11, 2, 0, 0, 1, 0, 4, 10, 15, 15, 15, 15,
    15, 4, 0, 0, 3, 4, 3, 8, 13, 15, 15, 15, 9, 3, 1, 0, 0, 1, 9, 13, 13, 15,
    15, 15, 13, 0, 0, 0, 1, 1, 2, 8, 15, 15, 15, 15, 15, 9, 0, 0, 0, 5, 4, 5,
    11, 15, 15, 15, 15, 9, 3, 0, 0, 1, 7, 5, 8, 13, 15, 15, 15, 9, 4, 0, 0, 0,
    0, 9, 10, 10, 14, 15, 15, 15, 5, 0, 0, 0, 0, 0, 5, 13, 14, 14, 15, 15, 15,
    7, 0, 0, 0, 5, 4, 3, 8, 13, 15, 15, 15, 14, 7, 3, 0, 0, 0, 7, 8, 6, 12,
    15, 15, 15, 14, 9, 5, 0, 0, 0, 6, 6, 6, 11, 15, 15, 15, 15, 12, 7, 0, 0,
    0, 3, 8, 7, 8, 14, 15, 15, 15, 15, 6, 3, 0, 0, 0, 1, 8, 13, 10, 12, 15,
    15, 15, 12, 1, 0, 0, 0, 0, 3, 10, 13, 12, 13, 15, 15, 15, 9, 5, 1, 0, 0,
    0, 7, 9, 7, 11, 15, 15, 15, 15, 13, 8, 0, 0, 0, 2, 5, 5, 8, 13, 15, 15,
    15, 15, 15, 8, 0, 0, 0, 2, 2, 2, 7, 12, 15, 15, 15, 15, 15, 14, 2, 0, 0,
    0, 3, 3, 4, 8, 13, 15, 15, 15, 15, 15, 14, 2, 0, 0, 0, 1, 2, 6, 11, 15,
    14, 14, 15, 15, 15, 9, 2, 0, 0, 0, 0, 1, 6, 12, 12, 11, 15, 15, 15, 15,
    13, 3, 0, 0, 0, 0, 0, 4, 9, 15, 12, 12, 15, 15, 15, 15, 9, 3, 0, 0, 0, 0,
    2, 7, 13, 10, 10, 14, 15, 15, 15, 13, 9, 4, 1, 0, 0, 0, 6, 8, 7, 10, 11,
    15, 15, 15, 14, 15, 14, 5, 0, 0, 0, 0, 1, 3, 8, 13, 13, 11, 15, 15, 15,
    14, 13, 9, 5, 0, 0, 0, 0, 6, 7, 7, 11, 14, 13, 13, 15, 15, 15, 13, 7, 3,
    1, 0, 0, 0, 6, 6, 7, 10, 13, 15, 15, 14, 15, 15, 14, 9, 4, 1, 0, 0, 0, 3,
    6, 7, 9, 12, 14, 12, 14, 15, 15, 15, 11, 9, 5, 1, 0, 0, 0, 4, 5, 7, 10,
    12, 15, 13, 13, 15, 15, 15, 13, 9, 4, 2, 0, 0, 0, 1, 6, 7, 9, 11, 13, 15,
    14, 13, 15, 15, 15, 12, 7, 2, 0, 0, 0, 0, 2, 8, 8, 9, 11, 12, 14, 15, 14,
    13, 15, 15, 14, 9, 3, 0, 0, 0, 0, 0, 4, 10, 11, 10, 11, 11, 13, 15, 14,
    13, 14, 15, 13, 8, 3, 1, 0, 0, 0, 0, 5, 10, 10, 10, 11, 13, 14, 12, 12,
    14, 15, 15, 12, 9, 7, 3, 0, 0, 0, 1, 4, 5, 8, 10, 13, 13, 11, 10, 12, 15,
    14, 13, 13, 13, 13, 7, 1, 0, 0, 0, 0, 1, 6, 10, 11, 10, 11, 12, 14, 11,
    11, 13, 13, 15, 13, 11, 10, 7, 4, 0, 0, 0, 0, 1, 3, 7, 10, 13, 13, 11, 10,
    11, 13, 12, 11, 12, 14, 13, 11, 9, 5, 3, 0, 0, 0, 0, 3, 5, 7, 10, 11, 13,
    12, 10, 11, 12, 12, 11, 12, 13, 14, 11, 9, 8, 6, 4, 0, 0, 0, 0, 4, 6, 7,
    10, 12, 12, 11, 10, 11, 12, 11, 10, 12, 12, 13, 13, 10, 10, 9, 6, 2, 0, 0,
    0, 0, 1, 4, 7, 10, 13, 12, 11, 11, 12, 10, 9, 10, 11, 13, 12, 11, 11, 12,
    10, 8, 6, 4, 2, 0, 0, 0, 2, 5, 7, 8, 10, 12, 13, 11, 11, 11, 11, 11, 9,
    10, 11, 13, 11, 10, 11, 11, 11, 8, 5, 3, 2, 1, 0, 0, 1, 4, 8, 9, 9, 11,
    11, 12, 12, 10, 10, 10, 11, 9, 9, 10, 12, 12, 11, 10, 10, 11, 9, 7, 5, 4,
    1, 0, 0, 2, 3, 3, 5, 8, 11, 11, 11, 11, 12, 11, 10, 9, 10, 10, 9, 8, 9,
    11, 12, 11, 10, 10, 10, 10, 8, 7, 6, 4, 1, 0, 1, 1, 3, 4, 5, 7, 9, 11, 12,
    12, 11, 11, 11, 11, 10, 9, 9, 9, 9, 8, 9, 10, 11, 11, 10, 10, 9, 9, 9, 8,
    7, 6, 3, 3, 2, 1, 2, 3, 4, 5, 6, 8, 9, 11, 12, 11, 11, 11, 11, 10, 9, 9,
    9, 9, 9, 8, 8, 9, 9, 10, 10, 10, 11, 9, 9, 9, 8, 9, 7, 7, 6, 5, 3, 2, 2,
    3, 3, 4, 5, 6, 7, 9, 10, 10, 11, 11, 11, 11, 10, 10, 10, 10, 9, 9, 9, 9,
    8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 9, 9, 8, 9, 8, 7, 7, 7, 7, 6, 4, 3, 3, 3,
    3, 4, 4, 5, 7, 7, 7, 9, 10, 11, 11, 11, 11, 11, 10, 10, 10, 10, 10, 9, 9,
    9, 9, 9, 8, 8, 8, 9, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 7, 7, 7,
    8, 7, 5, 3, 1, 0, 0, 3, 6, 9, 10, 13, 15, 15, 11, 5, 4, 3, 7, 14, 13, 5,
    4, 4, 7, 15, 13, 5, 4, 4, 8, 15, 13, 5, 4, 4, 7, 15, 13, 5, 4, 4, 7, 15,
    13, 5, 4, 4, 7, 15, 13, 5, 4, 4, 6, 15, 14, 5, 4, 4, 6, 15, 14, 5, 3, 4,
    6, 14, 15, 6, 3, 4, 5, 13, 15, 7, 3, 3, 5, 11, 15, 9, 3, 4, 4, 10, 15, 10,
    3, 3, 4, 9, 15, 12, 4, 3, 3, 7, 15, 13, 5, 3, 3, 6, 15, 15, 6, 3, 3, 5,
    13, 15, 8, 3, 4, 4, 10, 15, 11, 3, 3, 3, 8, 15, 13, 4, 3, 3, 6, 15, 15, 6,
    3, 4, 5, 12, 15, 9, 3, 3, 3, 9, 15, 13, 4, 3, 3, 6, 15, 15, 6, 3, 3, 4,
    12, 15, 10, 3, 3, 4, 8, 15, 13, 4, 3, 3, 6, 14, 15, 7, 3, 3, 4, 10, 15,
    12, 3, 3, 3, 6, 15, 15, 6, 3, 3, 4, 11, 15, 11, 3, 3, 3, 7, 15, 15, 5, 3,
    3, 5, 11, 15, 11, 3, 3, 4, 7, 15, 15, 6, 3, 3, 4, 11, 15, 11, 3, 3, 3, 6,
    15, 15, 7, 3, 3, 4, 10, 15, 13, 4, 2, 3, 6, 13, 15, 9, 3, 3, 3, 8, 15, 15,
    5, 3, 3, 4, 10, 15, 12, 3, 3, 3, 6, 13, 15, 9, 3, 3, 4, 8, 15, 15, 6, 3,
    3, 4, 10, 15, 13, 4, 3, 3, 5, 12, 15, 10, 3, 3, 4, 6, 14, 15, 8, 3, 3, 4,
    8, 15, 15, 6, 2, 3, 4, 9, 15, 14, 4, 3, 3, 5, 10, 15, 13, 3, 3, 3, 5, 12,
    15, 11, 3, 3, 4, 6, 13, 15, 10, 3, 3, 4, 6, 14, 15, 9, 3, 3, 4, 7, 14, 15,
    8, 3, 3, 4, 7, 14, 15, 8, 2, 3, 4, 7, 15, 15, 8, 3, 3, 4, 7, 14, 15, 7, 3,
    3, 4, 7, 14, 15, 8, 3, 3, 4, 7, 14, 15, 8, 3, 3, 4, 7, 13, 15, 10, 3, 3,
    4, 6, 12, 15, 11, 3, 3, 4, 6, 11, 15, 12, 4, 2, 3, 5, 9, 15, 13, 4, 2, 3,
    5, 9, 15, 15, 5, 3, 3, 5, 8, 15, 15, 7, 3, 3, 4, 7, 13, 15, 10, 3, 3, 4,
    6, 11, 15, 13, 4, 3, 3, 5, 9, 15, 15, 6, 3, 3, 5, 7, 13, 15, 9, 3, 3, 4,
    6, 10, 15, 13, 4, 3, 4, 5, 9, 15, 15, 7, 3, 3, 4, 7, 12, 15, 11, 3, 3, 3,
    6, 9, 15, 15, 6, 3, 3, 5, 7, 12, 15, 11, 3, 3, 4, 6, 9, 15, 15, 6, 3, 3,
    5, 7, 12, 15, 12, 4, 3, 3, 5, 8, 15, 15, 7, 3, 3, 4, 7, 10, 15, 13, 4, 3,
    3, 5, 7, 13, 15, 10, 3, 3, 4, 6, 9, 15, 15, 7, 3, 3, 4, 6, 10, 15, 14, 4,
    3, 3, 5, 7, 11, 15, 12, 4, 3, 3, 6, 8, 13, 15, 10, 3, 3, 4, 6, 8, 14, 15,
    8, 3, 3, 4, 6, 9, 15, 15, 6, 3, 3, 5, 6, 9, 15, 15, 5, 3, 3, 5, 6, 10, 15,
    14, 5, 3, 3, 5, 7, 10, 15, 14, 5, 3, 3, 5, 7, 10, 15, 14, 5, 3, 3, 5, 7,
    10, 15, 14, 6, 3, 3, 5, 7, 9, 15, 15, 7, 3, 3, 5, 6, 9, 14, 15, 8, 3, 3,
    4, 6, 8, 13, 15, 9, 3, 3, 4, 6, 8, 12, 15, 11, 4, 3, 4, 5, 7, 10, 15, 13,
    4, 3, 3, 5, 7, 9, 15, 15, 7, 3, 3, 4, 7, 8, 13, 15, 10, 4, 3, 4, 6, 7, 11,
    15, 13, 5, 3, 3, 5, 7, 9, 14, 15, 8, 3, 3, 4, 6, 8, 11, 15, 12, 4, 3, 4,
    6, 7, 9, 15, 15, 8, 4, 3, 4, 6, 7, 11, 15, 12, 5, 3, 4, 5, 7, 9, 14, 15,
    9, 3, 3, 4, 6, 7, 10, 15, 14, 6, 3, 4, 5, 6, 8, 11, 15, 12, 4, 3, 4, 5, 7,
    9, 13, 15, 10, 4, 3, 4, 6, 7, 9, 14, 15, 9, 4, 3, 4, 6, 7, 10, 15, 15, 7,
    3, 4, 4, 6, 7, 10, 15, 14, 6, 3, 3, 4, 6, 7, 10, 15, 14, 6, 3, 3, 4, 7, 8,
    10, 15, 14, 6, 3, 3, 4, 7, 8, 10, 15, 14, 7, 3, 3, 4, 6, 8, 10, 14, 15, 8,
    3, 3, 4, 6, 7, 9, 13, 15, 10, 4, 3, 4, 6, 7, 9, 12, 15, 11, 4, 3, 4, 5, 7,
    8, 11, 15, 14, 6, 4, 4, 4, 7, 8, 10, 14, 15, 9, 4, 3, 4, 6, 7, 9, 12, 15,
    12, 5, 3, 4, 5, 7, 8, 10, 14, 15, 8, 4, 4, 4, 6, 7, 8, 11, 15, 12, 5, 3,
    4, 5, 7, 8, 9, 13, 15, 10, 4, 3, 4, 6, 7, 8, 10, 15, 14, 7, 4, 3, 4, 6, 8,
    9, 11, 15, 13, 5, 3, 3, 4, 6, 8, 9, 12, 15, 11, 4, 3, 4, 5, 7, 8, 9, 12,
    15, 11, 4, 3, 4, 5, 7, 8, 9, 13, 15, 11, 4, 3, 4, 5, 7, 8, 9, 12, 15, 11,
    4, 3, 4, 5, 7, 8, 9, 12, 15, 12, 5, 3, 4, 5, 7, 8, 9, 11, 15, 13, 6, 4, 4,
    5, 6, 7, 8, 10, 14, 15, 8, 4, 3, 4, 6, 7, 8, 9, 12, 15, 11, 4, 3, 4, 5, 7,
    8, 9, 10, 15, 14, 6, 4, 3, 4, 6, 7, 8, 9, 12, 15, 11, 4, 3, 4, 5, 7, 8, 8,
    10, 14, 14, 8, 4, 3, 4, 6, 7, 8, 9, 11, 15, 13, 6, 4, 3, 5, 6, 7, 8, 9,
    12, 15, 12, 5, 3, 4, 5, 7, 7, 8, 9, 13, 15, 11, 4, 3, 4, 5, 7, 8, 9, 9,
    12, 15, 11, 4, 3, 4, 5, 7, 7, 9, 9, 12, 15, 12, 5, 3, 4, 5, 6, 7, 8, 9,
    11, 15, 13, 6, 3, 3, 5, 6, 7, 8, 9, 10, 14, 15, 8, 4, 3, 4, 6, 7, 8, 9,
    10, 12, 15, 11, 5, 3, 3, 5, 7, 7, 8, 9, 11, 14, 14, 8, 4, 3, 4, 6, 7, 8,
    9, 9, 12, 15, 13, 6, 4, 4, 4, 6, 7, 8, 9, 9, 12, 15, 11, 5, 3, 4, 4, 6, 7,
    8, 9, 9, 12, 15, 10, 4, 3, 3, 5, 6, 7, 8, 9, 9, 12, 15, 11, 4, 4, 4, 5, 6,
    7, 8, 9, 9, 12, 15, 12, 5, 3, 4, 5, 6, 7, 8, 9, 9, 11, 14, 13, 8, 4, 3, 4,
    6, 7, 8, 9, 9, 10, 12, 15, 11, 5, 3, 4, 5, 7, 8, 8, 9, 9, 11, 14, 14, 8,
    4, 3, 4, 6, 7, 8, 8, 9, 9, 11, 15, 13, 7, 3, 3, 4, 6, 7, 8, 9, 9, 9, 11,
    15, 12, 6, 4, 3, 4, 6, 7, 8, 9, 9, 9, 11, 14, 13, 7, 4, 3, 4, 6, 7, 8, 8,
    9, 9, 10, 13, 14, 9, 4, 3, 4, 5, 7, 8, 8, 9, 9, 9, 12, 14, 12, 6, 3, 3, 5,
    6, 7, 8, 9, 9, 9, 10, 12, 14, 10, 4, 3, 3, 5, 7, 7, 8, 9, 9, 9, 10, 13,
    14, 9, 4, 3, 4, 5, 7, 8, 8, 9, 9, 9, 10, 13, 14, 10, 4, 3, 4, 5, 6, 8, 8,
    9, 9, 9, 10, 12, 14, 11, 6, 3, 3, 4, 6, 7, 8, 9, 9, 9, 9, 10, 13, 14, 9,
    4, 3, 4, 5, 6, 7, 8, 9, 9, 9, 9, 11, 13, 12, 8, 4, 3, 4, 6, 7, 7, 8, 9, 9,
    9, 9, 11, 13, 13, 8, 4, 3, 4, 5, 7, 8, 8, 9, 9, 9, 9, 10, 12, 13, 10, 4,
    3, 4, 5, 6, 7, 8, 9, 9, 9, 9, 9, 11, 13, 12, 7, 4, 3, 4, 6, 7, 8, 8, 9, 9,
    9, 9, 9, 11, 13, 12, 7, 4, 3, 4, 6, 7, 8, 9, 9, 9, 9, 9, 9, 11, 13, 12, 8,
    4, 3, 4, 5, 7, 8, 8, 9, 9, 9, 9, 9, 10, 12, 13, 10, 6, 3, 3, 5, 6, 7, 8,
    8, 9, 9, 9, 9, 9, 10, 12, 13, 10, 5, 4, 3, 5, 6, 7, 8, 9, 9, 9, 9, 9, 9,
    9, 11, 13, 11, 7, 4, 3, 4, 6, 7, 8, 8, 9, 9, 9, 9, 9, 9, 10, 11, 13, 10,
    5, 3, 3, 4, 6, 7, 8, 8, 9, 9, 9, 9, 9, 8, 9, 11, 13, 10, 6, 3, 3, 5, 6, 7,
    8, 8, 9, 9, 9, 9, 9, 9, 8, 10, 12, 12, 9, 5, 3, 3, 5, 6, 7, 8, 9, 9, 9, 9,
    9, 9, 9, 9, 10, 12, 12, 10, 5, 4, 3, 5, 6, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 10, 12, 12, 9, 5, 3, 4, 5, 6, 7, 8, 9, 9, 9, 9, 9, 9, 9, 8, 9, 9, 11,
    12, 10, 6, 4, 3, 5, 6, 7, 8, 8, 9, 9, 9, 9, 9, 8, 9, 8, 8, 9, 11, 12, 10,
    6, 4, 3, 5, 6, 7, 8, 8, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 10, 11, 12, 9, 5, 4,
    3, 5, 6, 7, 8, 8, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 9, 10, 11, 11, 8, 5, 3, 4,
    5, 6, 7, 8, 9, 9, 9, 9, 9, 8, 9, 9, 8, 8, 8, 8, 9, 10, 11, 10, 7, 4, 3, 4,
    5, 7, 7, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 9, 11, 11, 10, 7, 4, 4,
    4, 6, 7, 8, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 9, 10, 11, 10, 7,
    4, 3, 4, 5, 7, 7, 8, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 10,
    10, 11, 9, 6, 4, 4, 5, 6, 7, 8, 8, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 9, 10, 11, 10, 7, 5, 4, 4, 5, 6, 8, 8, 8, 9, 9, 9, 9, 9, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 10, 10, 11, 9, 6, 5, 4, 5, 6, 7, 8, 8,
    9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 10,
    10, 10, 8, 6, 4, 4, 5, 6, 7, 8, 8, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 10, 10, 10, 8, 6, 5, 4, 4, 6, 7, 8,
    8, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 9, 10, 10, 10, 9, 8, 6, 5, 4, 4, 6, 7, 8, 8, 9, 9, 9, 9,
    9, 9, 9, 8, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 8, 7, 6, 5, 4, 5, 6, 7, 8, 8, 9,
    9, 9, 9, 9, 9, 9, 8, 10, 11, 7, 6, 7, 7, 7, 8, 10, 8, 6, 8, 7, 8, 10, 7,
    6, 8, 7, 9, 10, 7, 7, 8, 7, 8, 10, 8, 6, 8, 7, 8, 10, 8, 6, 8, 7, 8, 10,
    7, 7, 8, 7, 8, 10, 7, 6, 8, 7, 8, 10, 7, 7, 8, 7, 8, 10, 7, 7, 8, 7, 8,
    10, 8, 7, 8, 7, 8, 9, 8, 8, 8, 7, 8, 9, 9, 8, 7, 7, 7, 8, 10, 8, 7, 8, 7,
    8, 10, 8, 6, 8, 7, 8, 10, 7, 7, 8, 7, 8, 10, 8, 7, 8, 7, 8, 9, 9, 8, 7, 8,
    7, 8, 10, 7, 6, 8, 7, 8, 10, 7, 7, 8, 7, 8, 9, 8, 8, 7, 7, 8, 8, 10, 8, 7,
    8, 7, 8, 10, 7, 7, 8, 7, 8, 9, 8, 8, 7, 7, 7, 8, 10, 8, 7, 8, 7, 8, 10, 8,
    7, 8, 7, 8, 9, 9, 8, 7, 8, 7, 8, 10, 7, 7, 8, 7, 8, 9, 9, 8, 7, 7, 7, 8,
    10, 8, 7, 8, 7, 8, 9, 9, 8, 7, 8, 7, 8, 10, 7, 7, 8, 7, 8, 9, 9, 8, 7, 7,
    7, 8, 10, 7, 7, 8, 7, 8, 8, 10, 8, 7, 8, 7, 8, 10, 8, 8, 8, 7, 8, 8, 10,
    8, 7, 8, 7, 8, 9, 9, 8, 7, 7, 7, 8, 10, 8, 7, 8, 7, 8, 8, 10, 7, 7, 8, 7,
    8, 9, 10, 8, 7, 8, 7, 8, 9, 8, 8, 7, 7, 7, 8, 10, 7, 7, 8, 7, 8, 8, 10, 8,
    7, 8, 7, 8, 9, 10, 8, 7, 8, 7, 8, 9, 9, 8, 7, 7, 7, 8, 9, 8, 8, 7, 7, 8,
    8, 10, 8, 8, 8, 7, 7, 8, 10, 8, 8, 8, 7, 8, 8, 10, 8, 7, 8, 7, 8, 8, 10,
    7, 7, 8, 7, 8, 8, 10, 7, 7, 8, 7, 8, 8, 10, 7, 7, 8, 7, 8, 8, 10, 7, 7, 8,
    8, 8, 8, 10, 8, 8, 8, 7, 8, 8, 10, 8, 8, 8, 7, 8, 8, 9, 8, 8, 8, 7, 8, 8,
    9, 9, 8, 7, 7, 8, 8, 8, 9, 8, 7, 7, 8, 8, 8, 10, 8, 7, 8, 7, 7, 8, 10, 7,
    7, 8, 7, 8, 8, 9, 8, 8, 8, 7, 8, 8, 9, 9, 8, 7, 7, 8, 8, 8, 10, 8, 7, 8,
    8, 8, 8, 10, 8, 7, 8, 7, 8, 8, 9, 9, 8, 7, 7, 8, 7, 8, 10, 7, 7, 8, 7, 8,
    8, 9, 8, 8, 8, 7, 8, 8, 8, 10, 8, 7, 8, 7, 8, 8, 9, 8, 8, 8, 7, 8, 8, 8,
    10, 7, 7, 8, 7, 8, 8, 9, 8, 8, 8, 7, 8, 8, 8, 10, 7, 7, 8, 7, 8, 8, 9, 9,
    8, 8, 7, 8, 8, 8, 9, 8, 8, 8, 7, 8, 8, 8, 10, 8, 7, 8, 7, 8, 8, 9, 9, 8,
    8, 7, 8, 8, 8, 9, 8, 8, 8, 7, 8, 7, 8, 9, 7, 8, 8, 7, 8, 8, 8, 10, 8, 8,
    8, 7, 8, 8, 8, 9, 8, 8, 8, 8, 8, 8, 8, 9, 8, 8, 7, 8, 8, 8, 9, 9, 8, 8, 8,
    8, 8, 8, 9, 9, 8, 8, 8, 8, 8, 8, 8, 9, 8, 8, 8, 8, 8, 8, 9, 9, 8, 8, 8, 8,
    8, 8, 9, 9, 8, 8, 8, 8, 8, 8, 8, 9, 8, 7, 7, 7, 8, 8, 8, 9, 7, 7, 8, 7, 8,
    8, 8, 9, 7, 8, 8, 7, 8, 8, 8, 9, 8, 8, 8, 7, 8, 8, 8, 9, 8, 8, 8, 8, 8, 8,
    8, 8, 9, 8, 8, 8, 8, 8, 8, 8, 9, 8, 8, 8, 8, 8, 8, 8, 8, 9, 8, 8, 8, 8, 8,
    8, 8, 9, 7, 8, 8, 8, 8, 8, 8, 8, 9, 8, 8, 8, 8, 8, 8, 8, 9, 7, 8, 8, 8, 8,
    8, 8, 8, 9, 8, 8, 8, 8, 8, 8, 8, 9, 8, 8, 8, 8, 8, 8, 8, 8, 9, 7, 8, 8, 8,
    8, 8, 8, 8, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 8, 8, 8,
    8, 8, 8, 8, 8, 9, 8, 8, 8, 8, 8, 8, 8, 8, 9, 8, 8, 8, 8, 8, 8, 8, 8, 9, 8,
    8, 8, 7, 8, 8, 8, 8, 9, 8, 8, 8, 8, 8, 8, 8, 8, 9, 8, 8, 8, 7, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 8, 8, 8, 8, 8, 8, 8, 8, 9, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8
};

// explosion.wav converted to array
const unsigned char explosion[EXPLOSIONSIZE] = {
    120, 119, 119, 119, 120, 120, 129, 130, 133, 129, 125, 119, 119, 119, 125,
    128, 135, 137, 133, 123,   109, 99, 91, 92, 101, 116, 135, 140, 143, 130,
    123, 105, 96, 89, 92, 105, 115, 116, 120, 119,   130, 133, 139, 149, 163,
    171, 174, 173, 161, 143, 133, 115, 99, 79, 72, 75, 79, 82, 87, 103,   125,
    143, 139, 137, 137, 149, 163, 173, 168, 153, 133, 111, 105, 106, 109, 119,
    137, 149, 140, 133, 133, 143, 154, 168, 183, 187, 188, 184, 173, 163, 143,
    113, 75, 39, 5, 0, 0, 3, 9, 19,   46, 82, 105, 120, 135, 139, 144, 173,
    195, 208, 211, 202, 191, 181, 181, 202, 236, 255, 255, 255,   255, 255,
    240, 212, 192, 171, 130, 85, 47, 36, 41, 37, 33, 43, 57, 51, 33, 3, 0, 0,
    0, 0, 5, 9, 24, 67, 120, 157, 177, 201, 222, 239, 250, 246, 236, 216, 192,
    159, 101, 41,   0, 0, 0, 0, 0, 0, 58, 103, 129, 161, 192, 218, 239, 242,
    221, 184, 163, 157, 157, 159, 163, 161, 129, 81, 37, 17, 7, 19, 41, 61,
    89, 139, 178, 195, 205, 202, 184, 161, 153, 157,   161, 181, 187, 177,
    164, 149, 161, 197, 246, 255, 255, 255, 255, 255, 252, 226, 173, 105, 39,
    0, 0, 0, 19, 71, 101, 133, 168, 183, 174, 163, 139, 113, 99, 77, 47, 31,
    36, 41, 39, 43,   77, 125, 154, 149, 128, 95, 65, 57, 79, 99, 130, 161,
    173, 192, 221, 246, 255, 235, 181, 115,   48, 0, 0, 0, 19, 58, 115, 171,
    216, 216, 177, 119, 67, 43, 39, 31, 24, 17, 12, 15,   27, 79, 149, 226,
    255, 255, 255, 255, 255, 255, 255, 240, 207, 157, 77, 3, 0, 0, 0, 0,   0,
    0, 41, 72, 79, 67, 67, 95, 115, 125, 128, 120, 125, 147, 188, 222, 255,
    255, 255, 255,   255, 255, 249, 255, 255, 255, 255, 255, 202, 140, 85, 29,
    0, 0, 0, 0, 0, 46, 113, 129, 113, 79, 41, 17, 27, 61, 79, 92, 103, 103,
    106, 115, 125, 154, 212, 255, 255, 255, 255, 255,   255, 222, 163, 115,
    85, 96, 128, 163, 192, 207, 195, 143, 72, 0, 0, 0, 0, 0, 0, 0,   0, 53,
    135, 201, 255, 255, 255, 255, 255, 222, 183, 144, 106, 63, 0, 0, 0, 0, 0,
    0,   0, 29, 133, 192, 212, 207, 216, 245, 255, 255, 255, 249, 211, 205,
    221, 250, 255, 255, 255, 255, 212, 140, 106, 105, 135, 167, 195, 218, 216,
    192, 164, 135, 115, 105, 96, 92, 95, 103, 109, 119,   115, 85, 47, 15, 15,
    47, 87, 115, 135, 149, 159, 188, 232, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 183, 106, 55, 17, 27, 58, 87, 129, 174, 218, 239, 215, 161, 95,
    31, 0, 0, 0,   2, 17, 39, 87, 129, 147, 157, 168, 183, 188, 168, 115, 65,
    31, 29, 33, 29, 36, 53, 61,   65, 70, 85, 92, 82, 82, 75, 58, 41, 48, 58,
    72, 103, 149, 192, 229, 239, 226, 201, 164,   144, 143, 147, 137, 119,
    103, 87, 85, 115, 161, 221, 255, 255, 246, 236, 218, 208, 183, 150, 128,
    111, 101, 92, 99, 116, 135, 144, 149, 157, 163, 164, 164, 167, 159, 154,
    154, 163, 173, 183, 187, 187, 191, 187, 177, 167, 161, 150, 137, 119, 106,
    101, 99, 99, 96, 103, 105, 99, 92, 79, 70,   70, 71, 75, 77, 77, 82, 101,
    123, 137, 144, 154, 163, 174, 177, 173, 173, 161, 153, 137, 111,   82, 53,
    29, 22, 29, 37, 58, 87, 106, 119, 133, 149, 163, 173, 174, 164, 147, 137,
    135, 133,   135, 139, 135, 120, 95, 72, 65, 58, 65, 75, 85, 99, 119, 130,
    140, 147, 143, 135, 137, 153,   168, 168, 171, 161, 139, 123, 106, 113,
    135, 171, 207, 235, 255, 255, 255, 255, 255, 221, 154, 77, 17, 0, 3, 46,
    79, 91, 103, 120, 128, 119, 113, 92, 70, 51, 31, 17, 7, 12, 27, 48,   81,
    130, 187, 212, 202, 171, 139, 113, 106, 116, 119, 129, 140, 140, 153, 171,
    191, 195, 173, 130,   92, 57, 23, 13, 22, 36, 58, 99, 143, 177, 183, 157,
    119, 85, 71, 77, 89, 91, 79, 71,   71, 79, 119, 171, 216, 255, 255, 249,
    236, 225, 211, 202, 191, 173, 143, 82, 19, 0, 0, 0,   0, 0, 0, 46, 72, 79,
    67, 70, 95, 113, 123, 123, 120, 123, 144, 178, 205, 240, 255, 255,   255,
    255, 246, 236, 246, 255, 255, 255, 252, 205, 150, 101, 43, 0, 0, 0, 0, 0,
    48, 109, 123, 105, 71, 36, 15, 24, 58, 77, 95, 103, 101, 106, 113, 128,
    154, 212, 255, 255, 255, 255,   255, 255, 222, 163, 115, 85, 96, 128, 163,
    192, 207, 195, 143, 72, 0, 0, 0, 0, 0, 0,   0, 0, 53, 135, 201, 255, 255,
    255, 255, 255, 222, 183, 144, 106, 63, 0, 0, 0, 0, 0, 0, 0, 29, 133, 192,
    212, 207, 216, 245, 255, 255, 255, 249, 211, 205, 221, 250, 255, 255, 255,
    255, 212, 140, 106, 105, 135, 167, 195, 218, 216, 192, 164, 135, 115, 105,
    96, 92, 95, 103, 109, 119, 115, 85, 43, 13, 12, 46, 85, 115, 133, 149,
    161, 188, 236, 255, 255, 255, 255, 255, 255, 255, 255, 255, 191, 106, 51,
    13, 22, 51, 82, 125, 177, 226, 250, 225, 164, 96, 22, 0, 0,   0, 0, 0, 24,
    77, 125, 144, 157, 167, 183, 192, 168, 113, 53, 19, 17, 24, 19, 24, 47,
    57, 57, 57, 72, 81, 72, 70, 58, 33, 12, 19, 37, 57, 99, 159, 216, 255,
    255, 249, 216, 171, 149, 147, 147, 133, 103, 77, 55, 53, 92, 157, 240,
    255, 255, 255, 255, 255, 255, 250, 208,   173, 149, 123, 101, 101, 115,
    135, 147, 150, 153, 149, 147, 144, 149, 140, 143, 143, 144, 140, 140,
    144, 140, 143, 143, 143, 143, 139, 140, 140, 140, 140, 137, 135, 137, 137,
    137, 133, 130, 129, 130,   129, 129, 128, 128, 125, 125, 125, 128, 128,
    128, 120, 120, 119, 123, 119, 116, 120, 116, 119, 119,   119, 115, 119,
    116, 113, 115, 115, 115, 115, 113, 109, 106, 109, 113, 109, 109, 109, 109,
    109, 109,   109, 109, 109, 109, 113, 113, 111, 115, 116, 116, 115, 115,
    113, 96, 77, 75, 75, 67, 71, 105,   153, 183, 181, 154, 120, 87, 61, 48,
    46, 48, 63, 87, 143, 212, 255, 255, 255, 255, 255, 235,   143, 77, 58, 67,
    92, 92, 75, 57, 37, 24, 17, 15, 9, 0, 0, 0, 0, 0, 0, 3,   71, 159, 250,
    255, 255, 255, 255, 240, 232, 229, 211, 171, 128, 95, 70, 55, 46, 43, 33,
    3,   0, 33, 81, 113, 111, 96, 77, 61, 53, 53, 57, 75, 96, 120, 149, 177,
    212, 255, 255, 255,   255, 255, 255, 255, 255, 183, 106, 43, 0, 0, 0, 0,
    0, 0, 5, 67, 99, 105, 103, 96,   89, 82, 77, 79, 77, 79, 82, 89, 92, 99,
    103, 109, 111, 115, 115, 116, 101, 55, 24, 7,   7, 24, 48, 75, 113, 147,
    171, 202, 218, 236, 242, 255, 255, 255, 255, 255, 255, 255, 255, 250,
    109, 9, 0, 0, 0, 0, 0, 23, 96, 130, 120, 89, 53, 19, 3, 0, 0, 0, 0, 3,
    15, 24, 24, 0, 0, 9, 61, 109, 125, 120, 105, 101, 130, 178, 226, 245, 229,
    198, 164, 139, 116, 103, 99, 92, 95, 99, 96, 89, 61, 36, 22, 31, 87, 159,
    207, 215, 202, 174, 168, 177,   171, 154, 133, 129, 150, 154, 154, 157,
    183, 218, 229, 225, 221, 225, 215, 178, 133, 89, 57, 29,   15, 9, 12, 17,
    24, 31, 41, 43, 29, 37, 51, 63, 92, 133, 154, 149, 147, 135, 125, 123,
    115, 113, 111, 109, 105, 106, 105, 89, 87, 115, 137, 149, 149, 144, 143,
    137, 133, 129, 128, 125,   125, 123, 128, 125, 128, 128, 128, 128, 130,
    128, 128, 125, 125, 129, 129, 130, 133, 129, 128, 128, 125, 125, 113, 113,
    109, 115, 133, 143, 149, 144, 137, 135, 129, 120, 123, 113, 106, 113, 119,
    119,   123, 120, 120, 119, 115, 119, 116, 113, 103, 75, 58, 72, 113, 149,
    164, 183, 188, 181, 163, 143,   128, 116, 111, 103, 103, 103, 99, 103,
    105, 105, 106, 106, 109, 109, 113, 111, 115, 116, 116, 116,   119, 116,
    120, 119, 119, 119, 119, 119, 119, 113, 85, 55, 29, 33, 70, 103, 125, 135,
    140, 137, 135, 135, 140, 171, 208, 236, 255, 255, 255, 255, 242, 202, 171,
    129, 87, 71, 67, 55, 41, 48,   77, 113, 120, 125, 139, 144, 135, 103, 71,
    43, 24, 15, 5, 0, 0, 0, 0, 19, 37, 67,   113, 174, 226, 245, 229, 211,
    177, 149, 129, 111, 106, 95, 96, 99, 103, 109, 115, 119, 120, 99,   71,
    77, 89, 95, 101, 105, 137, 187, 240, 255, 245, 211, 184, 178, 174, 163,
    153, 163, 197, 218, 216, 216, 225, 225, 202, 159, 120, 95, 63, 48, 43, 39,
    43, 48, 53, 61, 67, 71, 79, 85,   89, 91, 92, 87, 61, 36, 19, 12, 19, 33,
    71, 129, 168, 192, 198, 205, 232, 255, 255, 255,   255, 255, 255, 222,
    192, 171, 140, 92, 47, 17, 0, 0, 0, 0, 0, 0, 23, 63, 99, 111,   109, 92,
    75, 75, 103, 154, 192, 202, 188, 178, 171, 154, 163, 178, 198, 211, 184,
    139, 81, 27,   15, 12, 19, 53, 96, 143, 159, 154, 133, 115, 92, 67, 51,
    46, 33, 23, 12, 13, 23, 39,   91, 163, 226, 255, 255, 255, 255, 255, 255,
    242, 205, 154, 125, 103, 95, 96, 123, 150, 161, 147, 125, 109, 91, 85, 79,
    79, 79, 85, 85, 91, 96, 101, 105, 109, 113, 115, 123, 120, 123, 128,
    130, 119, 96, 58, 36, 19, 23, 39, 63, 89, 119, 150, 174, 198, 222, 255,
    255, 255, 255, 255,   255, 255, 249, 168, 128, 111, 95, 101, 123, 150,
    168, 154, 128, 95, 48, 2, 0, 0, 0, 0, 0, 13, 57, 92, 130, 150, 149, 137,
    130, 135, 120, 92, 72, 53, 41, 33, 36, 33, 22, 17,   48, 91, 129, 144,
    144, 149, 147, 147, 143, 140, 140, 139, 140, 143, 149, 149, 150, 153, 154,
    157,   157, 159, 161, 161, 161, 161, 161, 161, 157, 161, 157, 153, 153,
    150, 149, 147, 144, 147, 140, 135, 115, 79, 53, 31, 27, 37, 55, 77, 105,
    133, 177, 232, 255, 255, 255, 255, 255, 255, 255, 212,   154, 101, 65, 57,
    81, 128, 174, 215, 235, 231, 197, 129, 58, 13, 0, 0, 0, 0, 0, 0,   0, 0,
    51, 135, 198, 249, 252, 229, 205, 188, 163, 128, 96, 70, 53, 46, 43, 46,
    53, 61,   57, 51, 57, 53, 51, 53, 57, 79, 125, 181, 221, 229, 225, 211,
    211, 226, 255, 255, 255, 255,   246, 208, 164, 130, 116, 125, 133, 133,
    137, 150, 168, 168, 153, 135, 115, 105, 92, 87, 89, 89,   95, 101, 103,
    109, 113, 116, 115, 116, 125, 133, 133, 128, 115, 103, 111, 128, 139, 149,
    150, 150,   144, 144, 139, 143, 153, 163, 174, 184, 201, 202, 195, 178,
    163, 150, 139, 120, 116, 113, 109, 101, 103, 113, 129, 133, 133, 137, 139,
    130, 119, 106, 92, 82, 65, 41, 39, 43, 57, 70, 65, 65,   82, 111, 140,
    168, 173, 163, 161, 159, 181, 188, 188, 191, 192, 187, 164, 137, 106, 91,
    87, 87,   81, 82, 103, 111, 101, 96, 95, 103, 123, 139, 140, 130, 115,
    101, 106, 116, 128, 154, 195, 240, 255, 255, 249, 242, 235, 211, 164, 119,
    92, 65, 43, 17, 9, 5, 9, 9, 22, 41, 70, 96,   116, 115, 105, 95, 81, 71,
    71, 65, 63, 72, 85, 105, 144, 164, 187, 198, 208, 231, 252, 252
};

// invaderkilled.wav converted to array
const unsigned char invaderkilled[INVADERKILLEDSIZE] = {
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 144, 164, 145, 111, 95, 91, 100, 106, 126,
    134, 108, 109, 123, 160, 158, 118, 101, 144, 189, 110, 79, 154, 202, 117,
    16, 96, 208, 187, 65, 100, 192, 175, 93, 0, 106, 253, 137, 17, 140, 242,
    103, 1, 134, 255, 134, 4, 110, 230, 118, 1, 149, 255, 89, 6, 160, 255,
    110, 0, 60, 177, 255, 81, 27, 207, 170, 43, 61, 200, 179, 23, 104, 245,
    112, 11, 102, 210, 217, 39, 73, 237, 114, 29, 57, 173, 255, 91, 0, 145,
    255, 138, 10, 62, 171, 252, 84, 0, 172, 244, 46, 47, 207, 190, 74, 0, 141,
    255, 147, 16, 65, 191, 215, 30, 84, 224, 163, 78, 0, 128, 255, 124, 0,
    149, 255, 102, 0, 138, 249, 169, 63, 0, 166, 255, 62, 24, 195, 229, 33,
    78, 224, 163, 70, 0, 145, 255, 100, 0, 161, 255, 92, 0, 163, 255, 95, 0,
    134, 246, 191, 77, 0, 125, 255, 130, 0, 88, 198, 226, 95, 0, 122, 255,
    158, 43, 53, 213, 178, 21, 99, 214, 200, 49, 39, 198, 214, 75, 0, 131,
    255, 134, 6, 104, 219, 179, 18, 105, 251, 104, 4, 106, 228, 204, 45, 51,
    185, 247, 76, 0, 178, 244, 39, 52, 199, 220, 85, 0, 105, 255, 182, 35, 99,
    254, 96, 0, 118, 207, 243, 84, 0, 137, 255, 124, 0, 140, 253, 121, 43, 19,
    162, 255, 147, 15, 60, 180, 255, 62, 26, 196, 222, 91, 0, 135, 255, 96, 0,
    178, 255, 76, 6, 179, 255, 80, 0, 166, 255, 108, 0, 110, 255, 92, 0, 122,
    228, 215, 57, 24, 181, 252, 75, 0, 118, 255, 134, 1, 133, 214, 188, 65, 0,
    163, 255, 95, 0, 143, 255, 126, 34, 48, 193, 255, 65, 22, 208, 201, 50,
    31, 209, 199, 42, 70, 190, 251, 57, 11, 190, 221, 87, 0, 140, 255, 129,
    27, 88, 209, 202, 54, 28, 186, 251, 94, 0, 144, 255, 82, 4, 190, 255, 60,
    19, 202, 220, 42, 55, 212, 186, 35, 78, 221, 169, 27, 95, 213, 189, 75, 0,
    146, 255, 113, 0, 169, 255, 83, 0, 118, 241, 164, 25, 107, 202, 212, 79,
    0, 133, 255, 153, 42, 62, 216, 164, 7, 148, 229, 154, 54, 0, 185, 255, 65,
    9, 197, 232, 54, 34, 189, 244, 80, 0, 113, 238, 210, 40, 90, 214, 159, 51,
    2, 197, 218, 59, 31, 192, 255, 70, 8, 168, 255, 122, 0, 117, 235, 92, 7,
    130, 234, 188, 16, 124, 229, 121, 46, 15, 178, 255, 104, 0, 142, 255, 87,
    0, 156, 254, 131, 25, 100, 212, 183, 64, 6, 164, 255, 107, 8, 97, 179,
    255, 99, 0, 121, 229, 155, 44, 87, 214, 181, 60, 35, 175, 255, 119, 15,
    50, 167, 255, 98, 0, 171, 241, 113, 14, 97, 238, 127, 19, 159, 252, 91, 0,
    162, 251, 126, 21, 102, 212, 172, 62, 15, 174, 255, 90, 0, 163, 229, 169,
    49, 14, 189, 231, 78, 0, 147, 255, 127, 31, 120, 221, 148, 36, 86, 227,
    127, 20, 131, 215, 195, 38, 70, 205, 178, 66, 0, 167, 255, 103, 5, 139,
    215, 175, 73, 0, 176, 255, 122, 15, 104, 213, 164, 68, 0, 179, 255, 73,
    22, 197, 245, 65, 0, 175, 255, 88, 0, 167, 242, 116, 39, 41, 198, 242, 67,
    12, 171, 255, 105, 0, 149, 224, 142, 29, 88, 195, 198, 63, 0, 192, 241,
    66, 10, 180, 255, 90, 0, 177, 250, 63, 24, 191, 236, 85, 0, 135, 247, 98,
    29, 134, 222, 197, 50, 52, 200, 209, 58, 19, 196, 230, 59, 20, 175, 255,
    103, 0, 158, 239, 80, 0, 148, 209, 206, 71, 0, 192, 234, 56, 28, 189, 255,
    85, 0, 149, 237, 135, 51, 38, 174, 255, 92, 0, 145, 211, 150, 63, 7, 189,
    255, 61, 17, 184, 255, 119, 21, 52, 182, 240, 63, 0, 190, 245, 86, 4, 126,
    229, 169, 62, 55, 195, 246, 55, 13, 192, 243, 65, 0, 181, 251, 118, 42,
    38, 187, 255, 68, 0, 186, 255, 131, 45, 29, 182, 255, 83, 0, 148, 211,
    187, 81, 0, 181, 255, 84, 9, 158, 240, 91, 11, 181, 249, 99, 19, 117, 229,
    107, 33, 121, 215, 206, 38, 87, 213, 153, 47, 47, 211, 177, 32, 119, 225,
    128, 24, 145, 236, 91, 31, 121, 208, 215, 61, 0, 181, 255, 85, 2, 165,
    228, 99, 28, 92, 213, 194, 39, 108, 211, 164, 66, 0, 189, 255, 109, 42,
    53, 202, 227, 62, 20, 179, 255, 99, 20, 97, 192, 219, 59, 1, 190, 255, 84,
    23, 83, 186, 255, 62, 0, 191, 236, 66, 0, 193, 242, 59, 28, 208, 212, 56,
    30, 181, 255, 65, 8, 198, 221, 46, 31, 204, 203, 42, 63, 213, 176, 53, 49,
    194, 251, 60, 6, 167, 246, 92, 19, 133, 199, 211, 60, 0, 170, 252, 126,
    32, 104, 209, 149, 41, 81, 204, 192, 42, 74, 218, 159, 49, 73, 193, 250,
    78, 0, 170, 235, 67, 15, 177, 252, 87, 31, 126, 195, 243, 68, 0, 180, 230,
    64, 8, 158, 242, 130, 40, 109, 191, 223, 64, 0, 170, 228, 151, 47, 38,
    200, 213, 63, 0, 152, 243, 167, 39, 124, 222, 105, 54, 43, 190, 255, 57,
    14, 175, 235, 142, 28, 91, 194, 171, 46, 23, 201, 240, 69, 7, 143, 239,
    145, 34, 157, 238, 79, 41, 86, 190, 255, 59, 0, 191, 234, 112, 40, 43,
    197, 248, 57, 3, 194, 255, 70, 17, 191, 232, 83, 13, 107, 209, 190, 54,
    41, 209, 217, 52, 25, 205, 239, 54, 20, 192, 251, 113, 29, 43, 190, 253,
    52, 0, 145, 235, 165, 34, 133, 224, 116, 33, 94, 212, 165, 33, 99, 230,
    109, 23, 182, 233, 110, 32, 106, 218, 148, 30, 128, 232, 86, 15, 191, 240,
    96, 42, 73, 201, 252, 45, 6, 208, 238, 53, 0, 157, 247, 130, 41, 104, 190,
    243, 42, 0, 176, 222, 140, 44, 6, 201, 255, 57, 0, 169, 216, 175, 49, 16,
    217, 203, 32, 72, 213, 185, 45, 51, 226, 176, 36, 89, 201, 250, 69, 0,
    177, 227, 53, 21, 152, 245, 149, 39, 94, 200, 250, 59, 0, 134, 216, 146,
    27, 144, 224, 121, 45, 46, 214, 240, 31, 64, 225, 157, 40, 91, 205, 206,
    43, 16, 212, 254, 75, 0, 160, 236, 78, 37, 118, 215, 215, 35, 68, 209,
    196, 46, 2, 209, 241, 60, 1, 174, 249, 80, 38, 139, 213, 221, 43, 0, 182,
    242, 134, 20, 100, 205, 161, 49, 5, 209, 255, 44, 34, 223, 219, 44, 21,
    187, 255, 64, 25, 136, 225, 168, 15, 134, 204, 139, 34, 36, 210, 219, 50,
    6, 216, 237, 34, 58, 209, 222, 53, 0, 188, 230, 140, 36, 65, 227, 142, 41,
    86, 218, 211, 29, 82, 218, 165, 37, 51, 206, 239, 34, 3, 220, 214, 41, 33,
    203, 255, 54, 4, 172, 232, 98, 25, 145, 212, 137, 28, 93, 209, 173, 42,
    23, 224, 207, 27, 94, 219, 179, 50, 6, 198, 255, 97, 26, 149, 222, 92, 34,
    103, 212, 212, 39, 27, 211, 252, 69, 0, 160, 225, 89, 30, 132, 219, 163,
    37, 75, 218, 195, 39, 36, 228, 196, 32, 84, 226, 152, 25, 130, 209, 151,
    39, 48, 228, 167, 40, 69, 209, 251, 38, 22, 214, 224, 35, 2, 170, 241,
    104, 26, 161, 204, 178, 41, 0, 207, 250, 90, 23, 118, 224, 112, 33, 144,
    222, 137, 51, 53, 206, 254, 55, 4, 183, 214, 132, 46, 5, 213, 255, 42, 30,
    172, 231, 167, 32, 45, 213, 202, 17, 86, 227, 113, 49, 85, 213, 252, 29,
    32, 229, 189, 40, 32, 191, 254, 83, 13, 165, 220, 73, 35, 108, 222, 208,
    34, 63, 219, 213, 35, 14, 195, 235, 137, 43, 0, 201, 255, 45, 34, 159,
    229, 161, 30, 83, 220, 162, 41, 54, 205, 248, 38, 19, 177, 224, 170, 31,
    25, 226, 198, 31, 71, 215, 236, 38, 0, 206, 237, 52, 31, 216, 217, 34, 22,
    218, 249, 74, 16, 156, 222, 62, 28, 216, 241, 68, 17, 142, 220, 89, 19,
    191, 227, 81, 42, 84, 207, 255, 35, 0, 180, 207, 157, 33, 51, 223, 180,
    38, 42, 226, 230, 23, 63, 222, 188, 40, 9, 205, 255, 66, 45, 107, 209,
    252, 26, 0, 213, 227, 84, 18, 140, 213, 132, 51, 24, 208, 255, 65, 39,
    213, 222, 40, 26, 115, 215, 242, 27, 21, 224, 225, 48, 11, 155, 229, 123,
    47, 119, 220, 168, 23, 121, 212, 129, 46, 25, 204, 255, 77, 29, 170, 206,
    124, 46, 24, 202, 255, 63, 37, 208, 219, 46, 17, 166, 223, 91, 35, 179,
    228, 70, 41, 135, 215, 214, 22, 20, 230, 192, 28, 83, 214, 191, 30, 32,
    227, 207, 30, 71, 229, 169, 40, 61, 199, 248, 70, 19, 153, 205, 123, 42,
    78, 221, 193, 22, 104, 209, 169, 42, 6, 215, 246, 58, 41, 203, 218, 46,
    17, 192, 221, 73, 41, 135, 227, 154, 45, 75, 202, 242, 59, 12, 173, 201,
    45, 44, 149, 232, 171, 40, 72, 208, 230, 27, 10, 215, 203, 38, 45, 217,
    226, 30, 31, 217, 210, 36, 26, 202, 223, 134, 45, 34, 227, 213, 32, 65,
    221, 194, 36, 47, 198, 231, 115, 24, 93, 197, 170, 32, 54, 228, 179, 44,
    56, 198, 238, 128, 44, 39, 213, 227, 23, 44, 218, 212, 46, 20, 163, 220,
    104, 61, 101, 212, 245, 43, 26, 106, 201, 236, 30, 15, 213, 218, 55, 46,
    122, 214, 203, 24, 73, 215, 163, 37, 66, 224, 174, 42, 69, 198, 235, 92,
    42, 84, 200, 226, 27, 23, 212, 209, 65, 38, 151, 217, 98, 45, 188, 210,
    94, 61, 70, 210, 242, 65, 47, 73, 203, 247, 27, 38, 145, 206, 219, 30, 16,
    155, 224, 152, 44, 116, 203, 177, 37, 28, 198, 227, 82, 47, 153, 199, 123,
    44, 103, 219, 130, 42, 169, 197, 120, 52, 41, 188, 239, 80, 49, 181, 206,
    68, 45, 163, 196, 166, 35, 37, 227, 180, 41, 92, 221, 170, 41, 101, 211,
    172, 46, 40, 199, 223, 53, 60, 138, 218, 182, 27, 106, 201, 130, 49, 49,
    188, 234, 115, 46, 137, 203, 88, 49, 174, 196, 119, 53, 65, 210, 210, 31,
    32, 194, 214, 72, 51, 198, 199, 50, 43, 167, 208, 79, 50, 188, 205, 85,
    49, 136, 193, 160, 43, 33, 217, 220, 79, 55, 103, 206, 199, 36, 49, 219,
    189, 41, 76, 213, 198, 36, 38, 183, 216, 99, 62, 89, 202, 234, 47, 40,
    167, 198, 94, 45, 182, 194, 90, 60, 69, 214, 218, 44, 77, 210, 188, 33,
    45, 139, 213, 205, 36, 50, 217, 191, 42, 43, 185, 215, 90, 69, 100, 204,
    220, 34, 61, 208, 186, 41, 37, 168, 206, 128, 57, 113, 205, 172, 41, 68,
    220, 163, 50, 83, 206, 215, 48, 41, 162, 194, 124, 62, 70, 190, 224, 65,
    59, 205, 184, 41, 52, 208, 199, 61, 49, 145, 202, 112, 61, 147, 202, 142,
    47, 105, 204, 147, 45, 100, 207, 156, 47, 89, 206, 176, 33, 106, 205, 116,
    64, 85, 197, 218, 62, 59, 124, 200, 179, 33, 92, 207, 137, 49, 110, 194,
    170, 40, 59, 219, 168, 47, 93, 206, 186, 39, 52, 149, 213, 184, 37, 66,
    209, 191, 45, 42, 202, 184, 50, 73, 133, 224, 186, 35, 112, 191, 150, 45,
    42, 201, 206, 70, 62, 160, 194, 118, 60, 105, 207, 172, 46, 67, 205, 195,
    44, 72, 206, 181, 44, 49, 181, 200, 107, 66, 116, 198, 174, 43, 51, 164,
    216, 121, 51, 175, 179, 89, 61, 95, 210, 158, 53, 100, 205, 186, 39, 51,
    169, 206, 119, 65, 88, 183, 211, 59, 60, 200, 176, 59, 61, 116, 203, 190,
    41, 75, 212, 177, 46, 59, 197, 196, 65, 68, 164, 195, 105, 57, 168, 181,
    87, 66, 109, 201, 191, 40, 51, 192, 194, 120, 64, 80, 205, 203, 50, 54,
    195, 182, 79, 73, 99, 210, 190, 50, 83, 203, 192, 45, 56, 174, 188, 86,
    65, 196, 176, 46, 79, 208, 169, 49, 68, 193, 198, 100, 70, 84, 202, 199,
    44, 65, 125, 207, 181, 51, 81, 200, 190, 47, 60, 172, 184, 84, 67, 188,
    185, 84, 65, 144, 195, 107, 73, 111, 194, 206, 60, 61, 149, 184, 111, 60,
    167, 177, 104, 69, 80, 206, 192, 58, 79, 199, 173, 55, 83, 140, 205, 175,
    29, 47, 181, 184, 78, 83, 102, 195, 204, 54, 73, 107, 198, 187, 47, 78,
    144, 205, 130, 60, 94, 189, 193, 66, 65, 114, 196, 152, 52, 135, 182, 137,
    58, 68, 207, 196, 78, 69, 154, 182, 93, 73, 157, 187, 104, 77, 103, 182,
    207, 69, 72, 192, 170, 64, 63, 166, 177, 90, 85, 105, 188, 204, 67, 75,
    198, 171, 64, 76, 104, 198, 203, 65, 73, 121, 190, 177, 43, 72, 157, 197,
    167, 50, 65, 202, 164, 66, 88, 145, 210, 138, 63, 95, 184, 190, 74, 68,
    111, 191, 184, 42, 71, 201, 172, 57, 82, 149, 198, 174, 47, 64, 187, 180,
    71, 87, 193, 159, 56, 82, 195, 173, 62, 82, 184, 179, 75, 75, 156, 184,
    104, 69, 148, 181, 105, 74, 116, 192, 178, 50, 72, 168, 183, 97, 76, 139,
    178, 150, 51, 92, 196, 153, 55, 80, 195, 183, 65, 87, 195, 147, 66, 89,
    167, 191, 104, 76, 108, 191, 162, 53, 82, 189, 178, 67, 79, 117, 194, 189,
    48, 70, 150, 185, 116, 69, 161, 166, 107, 78, 89, 196, 185, 57, 86, 192,
    164, 62, 82, 169, 182, 96, 76, 157, 170, 121, 65, 114, 189, 117, 78, 108,
    171, 197, 116, 60, 115, 180, 125, 71, 97, 189, 181, 60, 89, 195, 162, 63,
    76, 149, 184, 120, 70, 162, 168, 80, 84, 155, 184, 105, 80, 110, 175, 184,
    68, 83, 150, 177, 152, 49, 71, 187, 175, 96, 79, 97, 184, 181, 71, 84,
    170, 171, 86, 84, 131, 192, 167, 52, 77, 167, 178, 111, 75, 91, 179, 185,
    87, 81, 141, 179, 114, 83, 109, 173, 188, 85, 82, 112, 186, 170, 55, 91,
    192, 163, 60, 78, 157, 181, 109, 84, 138, 185, 149, 61, 83, 171, 182, 117,
    74, 88, 193, 174, 67, 86, 120, 191, 180, 52, 85, 168, 174, 90, 82, 180,
    156, 85, 85, 111, 193, 164, 65, 99, 173, 176, 107, 71, 96, 187, 162, 65,
    98, 184, 163, 72, 90, 185, 165, 72, 83, 156, 175, 123, 73, 116, 189, 133,
    80, 115, 188, 159, 59, 86, 133, 197, 157, 63, 109, 182, 157, 58, 82, 157,
    178, 121, 75, 92, 149, 194, 131, 68, 87, 159, 182, 106, 77, 121, 179, 135,
    74, 107, 180, 160, 65, 91, 169, 169, 104, 78, 99, 179, 173, 73, 95, 185,
    160, 74, 89, 128, 182, 163, 57, 93, 190, 159, 70, 86, 175, 159, 82, 98,
    146, 186, 153, 63, 83, 180, 166, 86, 88, 144, 171, 121, 82, 106, 184, 164,
    74, 93, 157, 171, 104, 84, 129, 181, 148, 64, 92, 138, 192, 166, 55, 87,
    184, 152, 70, 93, 159, 176, 105, 88, 155, 160, 114, 80, 124, 181, 122, 82,
    127, 179, 150, 66, 88, 173, 171, 87, 94, 151, 171, 133, 69, 106, 185, 131,
    77, 103, 141, 197, 137, 73, 127, 167, 132, 70, 86, 163, 177, 105, 89, 134,
    171, 133, 74, 106, 186, 143, 77, 105, 172, 166, 79, 88, 142, 170, 122, 80,
    105, 146, 190, 135, 71, 95, 174, 156, 73, 98, 126, 186, 159, 65, 90, 141,
    178, 139, 75, 101, 173, 156, 74, 98, 156, 168, 123, 75, 115, 176, 143, 69,
    101, 185, 145, 75, 106, 183, 149, 75, 97, 160, 164, 96, 96, 167, 154, 101,
    82, 140, 166, 100, 100, 119, 159, 179, 92, 94, 130, 176, 155, 63, 86, 157,
    164, 104, 92, 133, 175, 143, 72, 102, 170, 150, 85, 99, 163, 165, 100, 91,
    112, 149, 185, 117, 80, 129, 162, 111, 87, 140, 164, 111, 92, 142, 163,
    128, 78, 113, 176, 141, 76, 98, 173, 162, 106, 91, 114, 179, 148, 74, 105,
    163, 163, 100, 89, 145, 153, 99, 100, 136, 177, 127, 86, 114, 138, 184,
    137, 69, 94, 163, 160, 93, 99, 122, 177, 156, 72, 94, 150, 164, 109, 96,
    136, 171, 131, 82, 105, 147, 175, 105, 91, 151, 150, 104, 96, 107, 146,
    184, 118, 88, 144, 152, 108, 95, 119, 177, 149, 72, 102, 124, 176, 165,
    84, 96, 136, 165, 130, 80, 108, 171, 151, 82, 104, 141, 170, 133, 83, 103,
    150, 172, 130, 81, 100, 169, 157, 98, 99, 113, 169, 159, 85, 107, 150,
    162, 120, 87, 112, 171, 151, 77, 103, 169, 144, 93, 102, 139, 178, 124,
    94, 115, 133, 181, 134, 77, 102, 162, 153, 93, 95, 114, 166, 150, 80, 105,
    145, 163, 114, 90, 146, 147, 100, 101, 131, 171, 138, 79, 107, 128, 178,
    152, 78, 95, 135, 163, 130, 86, 115, 167, 143, 88, 108, 154, 158, 117, 89,
    108, 170, 153, 89, 102, 152, 148, 112, 99, 113, 173, 146, 90, 109, 143,
    170, 121, 89, 108, 143, 171, 130, 82, 108, 170, 139, 80, 107, 130, 173,
    158, 85, 106, 127, 169, 153, 80, 101, 148, 154, 109, 100, 136, 160, 121,
    94, 117, 163, 147, 93, 105, 145, 160, 110, 100, 119, 160, 157, 96, 103,
    117, 168, 147, 81, 105, 139, 165, 136, 86, 103, 158, 154, 101, 105, 147,
    156, 115, 98, 116, 156, 153, 91, 107, 161, 145, 93, 109, 116, 147, 174,
    106, 106, 118, 138, 168, 107, 95, 137, 149, 116, 96, 114, 163, 148, 93,
    107, 133, 163, 139, 83, 105, 160, 147, 96, 110, 153, 146, 105, 105, 117,
    141, 173, 133, 84, 113, 163, 132, 86, 109, 126, 165, 149, 97, 108, 127,
    166, 146, 81, 108, 146, 138, 103, 107, 153, 144, 104, 109, 132, 164, 130,
    97, 116, 152, 149, 102, 106, 129, 164, 137, 83, 105, 141, 160, 125, 96,
    110, 140, 167, 121, 101, 116, 155, 145, 94, 108, 135, 159, 132, 88, 108,
    138, 165, 130, 94, 118, 160, 137, 91, 108, 138, 156, 130, 97, 114, 160,
    143, 91, 112, 150, 141, 102, 109, 150, 145, 104, 108, 150, 142, 109, 108,
    127, 163, 136, 91, 110, 134, 161, 132, 96, 112, 148, 149, 111, 101, 130,
    153, 125, 99, 113, 137, 168, 136, 90, 108, 143, 152, 115, 106, 125, 153,
    138, 93, 122, 154, 127, 99, 125, 158, 119, 103, 116, 138, 167, 122, 97,
    115, 149, 145, 105, 108, 136, 146, 113, 109, 118, 133, 172, 133, 93, 109,
    139, 150, 113, 108, 134, 147, 128, 97, 112, 151, 147, 105, 115, 126, 142,
    153, 107, 107, 122, 148, 147, 101, 108, 130, 153, 127, 101, 120, 148, 139,
    106, 113, 127, 160, 139, 97, 109, 136, 152, 123, 105, 126, 154, 138, 94,
    111, 139, 149, 123, 105, 119, 152, 143, 106, 110, 135, 146, 122, 105, 118,
    153, 143, 108, 113, 116, 145, 145, 105, 111, 124, 153, 135, 93, 114, 150,
    134, 102, 117, 124, 148, 150, 109, 112, 123, 151, 138, 96, 112, 124, 152,
    142, 105, 112, 125, 154, 133, 102, 116, 126, 154, 145, 108, 111, 115, 141,
    150, 110, 116, 122, 133, 158, 115, 111, 128
};


// fastinvader1.wav converted to array
const unsigned char fastinvader1[FASTINVADER1SIZE] = {
    122, 105, 88, 60, 43, 20, 15, 9, 20, 31, 48, 65, 94, 105, 128, 144, 167,
    184, 195, 218, 224, 235, 240, 246, 252, 255, 252, 252, 252, 246, 246, 240,
    235, 224, 218, 207, 201, 195, 184, 178, 167, 161, 144, 139, 133, 122, 116,
    105, 99, 88, 82, 71, 65, 54, 60, 65, 65, 77, 82, 94, 94, 88, 94, 82, 71,
    60, 48, 37, 26, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 3, 15, 26, 31, 48, 60, 71, 77, 94, 111, 122, 128, 139, 150, 167,
    178, 190, 201, 207, 218, 224, 235, 240, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 246,
    235, 235, 229, 224, 212, 212, 201, 195, 195, 184, 178, 167, 161, 156, 150,
    150, 139, 133, 128, 122, 116, 111, 105, 99, 94, 94, 82, 82, 77, 77, 65,
    65, 60, 43, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 26, 43, 60, 77,
    82, 99, 105, 116, 116, 128, 128, 128, 128, 128, 128, 122, 116, 111, 105,
    99, 105, 94, 88, 82, 77, 65, 60, 48, 43, 37, 31, 26, 20, 15, 9, 3, 3, 0,
    0, 0, 3, 9, 26, 37, 48, 48, 48, 48, 43, 37, 26, 15, 9, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 15, 26, 37, 48, 60, 71, 88, 105,
    116, 128, 139, 150, 167, 178, 195, 207, 218, 235, 246, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 252, 240, 240, 235, 224, 212, 207, 195, 195, 184, 173, 167, 161,
    156, 150, 139, 133, 133, 128, 128, 116, 111, 105, 105, 94, 88, 71, 43, 15,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 26, 37, 54, 71, 82, 94, 105, 111, 116,
    116, 122, 122, 122, 128, 122, 122, 116, 116, 111, 111, 99, 88, 82, 77, 71,
    65, 54, 43, 43, 31, 20, 15, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 9, 15, 20,
    15, 20, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 3, 15, 26, 43, 54, 71, 88, 99, 111, 122, 133, 150, 161,
    173, 190, 201, 212, 224, 235, 246, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 246, 240, 235, 224, 218, 212, 207, 201,
    190, 184, 178, 173, 167, 156, 156, 150, 139, 128, 128, 128, 122, 116, 111,
    105, 99, 94, 94, 88, 65, 43, 15, 0, 0, 0, 0, 0, 0, 0, 0, 3, 15, 31, 48,
    65, 82, 94, 105, 116, 128, 133, 139, 144, 150, 150, 144, 150, 144, 139,
    139, 133, 128, 116, 111, 99, 94, 82, 82, 77, 60, 54, 48, 43, 37, 26, 15,
    15, 9, 3, 0, 0, 0, 0, 0, 3, 15, 26, 31, 43, 43, 37, 37, 31, 20, 15, 3, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 15, 31, 43,
    48, 65, 77, 94, 105, 122, 128, 144, 156, 167, 184, 195, 207, 218, 229,
    240, 252, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 252, 246, 235, 229, 224, 218, 212, 207, 201, 195, 184, 178, 178, 173,
    156, 150, 150, 139, 128, 128, 128, 122, 116, 111, 99, 94, 88, 88, 82, 77,
    71, 71, 65, 60, 54, 48, 43, 48, 43, 37, 31, 26, 31, 26, 26, 26, 26, 20,
    20, 15, 15, 9, 15, 9, 15, 9, 15, 9, 15, 15, 15, 9, 15, 15, 15, 20, 26, 20,
    26, 20, 26, 31, 26, 31, 31, 31, 31, 37, 37, 43, 43, 43, 48, 54, 48, 54,
    60, 54, 60, 60, 65, 71, 65, 71, 77, 71, 77, 82, 82, 88, 94, 88, 94, 99,
    99, 105, 99, 105, 105, 111, 111, 116, 116, 122, 128, 128, 128, 128, 128,
    128, 128, 133, 128, 133, 139, 139, 133, 139, 139, 144, 150, 144, 150, 156,
    150, 156, 150, 156, 161, 156, 161, 156, 161, 161, 161, 161, 167, 161, 167,
    173, 167, 173, 173, 173, 167, 173, 173, 178, 173, 178, 173, 178, 173, 173,
    178, 173, 173, 178, 173, 173, 178, 173, 178, 173, 173, 178, 173, 178, 173,
    167, 167, 173, 167, 173, 167, 161, 161, 167, 161, 167, 161, 161, 161, 167,
    161, 156, 161, 161, 161, 156, 150, 156, 156, 156, 156, 150, 156, 156, 156,
    150, 144, 144, 150, 144, 150, 144, 150, 144, 139, 144, 139, 144, 144, 139,
    144, 139, 133, 139, 139, 139, 133, 139, 133, 133, 133, 139, 133, 133, 128,
    133, 128, 128, 128, 128, 128, 128, 128, 128, 128, 116, 122, 116, 122, 116,
    111, 116, 116, 111, 111, 116, 111, 116, 111, 116, 111, 111, 116, 111, 116,
    111, 111, 116, 111, 116, 111, 111, 111
};

// // fastinvader2.wav converted to array
// const unsigned char fastinvader2[FASTINVADER2SIZE] = {
//     128, 128, 116, 94, 71, 54, 31, 20, 9, 20, 31, 48, 65, 88, 105, 128, 139,
//     161, 178, 190, 207, 218, 229, 240, 252, 252, 252, 255, 255, 252, 252, 252,
//     240, 240, 229, 224, 212, 207, 201, 184, 184, 173, 161, 150, 144, 128, 128,
//     122, 111, 99, 94, 82, 77, 65, 60, 54, 54, 71, 71, 82, 88, 94, 94, 94, 82,
//     77, 65, 60, 37, 31, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//     0, 0, 0, 3, 9, 20, 26, 43, 54, 65, 71, 88, 99, 116, 122, 133, 144, 156,
//     167, 178, 184, 195, 207, 218, 229, 235, 246, 252, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 252, 246,
//     240, 235, 224, 218, 218, 207, 201, 195, 190, 184, 178, 173, 167, 161, 156,
//     144, 139, 144, 133, 128, 128, 122, 116, 116, 105, 105, 94, 94, 88, 82, 77,
//     77, 65, 65, 60, 60, 54, 54, 48, 43, 43, 37, 37, 31, 31, 26, 26, 15, 3, 0,
//     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 37, 54, 71, 82, 94, 105, 111, 122,
//     128, 133, 133, 139, 133, 139, 139, 139, 133, 139, 128, 128, 128, 116, 116,
//     111, 111, 99, 88, 94, 82, 77, 71, 65, 60, 60, 48, 43, 37, 31, 37, 43, 54,
//     71, 77, 88, 94, 94, 88, 88, 77, 71, 60, 54, 43, 31, 20, 15, 3, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 3, 3, 15, 20, 31, 43, 48, 60, 71, 82, 99, 111, 122, 128,
//     139, 150, 167, 178, 190, 201, 212, 224, 235, 246, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 252, 240,
//     235, 224, 218, 218, 207, 201, 195, 190, 178, 178, 167, 156, 150, 144, 139,
//     133, 128, 122, 116, 116, 105, 99, 94, 94, 82, 71, 77, 71, 60, 54, 54, 48,
//     43, 37, 31, 26, 26, 26, 20, 15, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//     0, 15, 31, 48, 60, 77, 88, 94, 99, 105, 116, 116, 122, 122, 128, 122, 122,
//     116, 116, 111, 105, 99, 94, 88, 82, 77, 65, 60, 54, 48, 48, 37, 31, 26,
//     20, 15, 9, 3, 0, 3, 0, 9, 26, 31, 43, 48, 54, 48, 48, 43, 31, 26, 15, 3,
//     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 20, 31,
//     43, 54, 65, 82, 94, 105, 122, 128, 144, 156, 167, 184, 190, 207, 218, 229,
//     240, 252, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 252, 240, 235, 229, 224, 218, 207, 201, 195, 190, 184, 178, 178,
//     167, 161, 156, 144, 139, 133, 128, 133, 128, 116, 111, 111, 105, 94, 88,
//     77, 71, 65, 60, 60, 54, 54, 48, 48, 43, 43, 37, 31, 26, 20, 3, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0, 15, 26, 48, 65, 82, 94, 111, 122, 128, 128, 133,
//     133, 139, 139, 144, 139, 144, 139, 139, 133, 128, 128, 116, 116, 111, 99,
//     94, 88, 82, 82, 71, 60, 54, 48, 43, 37, 31, 26, 20, 26, 20, 26, 43, 48,
//     60, 65, 65, 65, 71, 65, 54, 48, 43, 31, 20, 9, 3, 0, 0, 0, 0, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0, 9, 20, 26, 43, 48, 60, 77, 88, 105, 116, 128, 133,
//     144, 161, 173, 190, 201, 212, 218, 229, 240, 252, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 252, 246, 240, 235, 224, 218, 212,
//     201, 195, 184, 184, 178, 167, 161, 156, 150, 144, 139, 128, 128, 128, 116,
//     116, 111, 99, 99, 94, 88, 82, 82, 77, 77, 65, 60, 54, 54, 48, 43, 43, 37,
//     31, 31, 26, 20, 26, 20, 15, 15, 20, 15, 15, 15, 15, 9, 9, 9, 9, 15, 9, 9,
//     15, 9, 3, 9, 15, 15, 9, 15, 9, 15, 15, 20, 15, 20, 26, 26, 20, 31, 31, 31,
//     37, 31, 37, 37, 43, 43, 48, 54, 48, 54, 54, 60, 60, 65, 65, 71, 71, 77,
//     77, 82, 82, 88, 88, 94, 99, 94, 99, 105, 105, 111, 116, 111, 116, 116,
//     122, 122, 128, 128, 128, 133, 128, 133, 139, 133, 139, 144, 139, 144, 144,
//     150, 156, 156, 156, 150, 156, 161, 156, 161, 156, 161, 161, 167, 167, 173,
//     167, 167, 173, 167, 173, 173, 167, 167, 173, 173, 178, 173, 178, 173, 178,
//     178, 173, 178, 178, 173, 178, 173, 178, 178, 173, 173, 178, 173, 178, 184,
//     178, 184, 178, 173, 178, 178, 173, 178, 173, 178, 178, 173, 173, 178, 178,
//     173, 167, 173, 178, 173, 167, 167, 173, 167, 173, 167, 161, 167, 161, 161,
//     156, 150, 150, 156, 150, 144, 144, 150, 144, 144, 150, 144, 139, 139, 144,
//     139, 144, 139, 144, 139, 133, 133, 133, 139, 133, 139, 133, 128, 133, 133,
//     128, 128, 133, 128, 133, 128, 133, 128, 133, 128, 128, 128, 128, 128, 128,
//     128, 128, 128, 128, 128, 128, 128, 122, 128, 122, 128, 122, 122, 122, 116,
//     122, 116, 116, 122, 122, 116, 122, 116, 111, 116, 116, 111, 111, 116, 111,
//     116, 111, 116, 111, 111, 111, 116, 111, 116, 111, 116, 111, 111, 116, 111,
//     111, 111, 111, 111, 116
// };

// // fastinvader3.wav converted to array
// const unsigned char fastinvader3[FASTINVADER3SIZE] = {
//     128, 128, 133, 133, 128, 133, 128, 116, 94, 71, 54, 31, 20, 15, 20, 31,
//     54, 71, 88, 111, 128, 150, 161, 184, 201, 218, 224, 240, 240, 252, 255,
//     255, 255, 255, 255, 255, 252, 246, 246, 235, 229, 218, 212, 201, 195, 184,
//     173, 161, 156, 144, 139, 128, 122, 111, 105, 94, 82, 77, 71, 65, 54, 60,
//     65, 77, 82, 94, 94, 94, 88, 88, 71, 60, 48, 37, 20, 9, 0, 0, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 20, 31, 43, 54, 60, 77,
//     94, 105, 116, 122, 133, 144, 156, 161, 178, 190, 195, 212, 218, 229, 240,
//     246, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 246, 240, 235, 235, 224, 212, 207, 201,
//     195, 184, 184, 173, 173, 161, 156, 150, 144, 133, 128, 128, 122, 122, 116,
//     105, 105, 99, 94, 88, 88, 77, 77, 65, 65, 60, 60, 48, 43, 31, 31, 26, 26,
//     20, 26, 20, 15, 20, 15, 15, 15, 9, 9, 15, 9, 9, 9, 9, 3, 3, 9, 9, 9, 3, 0,
//     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 37, 54, 77, 94, 111, 128, 133,
//     144, 156, 161, 173, 173, 184, 190, 190, 184, 190, 184, 184, 184, 173, 173,
//     167, 167, 156, 156, 144, 133, 128, 128, 122, 122, 111, 105, 94, 94, 88,
//     77, 71, 71, 77, 88, 99, 111, 122, 122, 128, 122, 116, 111, 105, 94, 82,
//     71, 60, 48, 37, 31, 31, 20, 15, 9, 9, 3, 3, 3, 9, 3, 15, 20, 20, 31, 37,
//     43, 54, 65, 77, 88, 99, 111, 122, 128, 144, 156, 161, 178, 190, 195, 212,
//     224, 229, 240, 252, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 252, 246, 235, 229, 218, 212, 207, 201, 190, 190, 178,
//     167, 161, 156, 144, 139, 128, 128, 122, 116, 111, 99, 94, 88, 82, 77, 71,
//     65, 60, 60, 54, 48, 43, 43, 31, 31, 26, 26, 20, 15, 9, 9, 3, 0, 3, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//     0, 0, 0, 20, 37, 60, 77, 94, 105, 116, 128, 128, 133, 139, 144, 150, 150,
//     156, 150, 150, 144, 144, 139, 133, 128, 128, 122, 116, 111, 105, 99, 94,
//     88, 82, 77, 71, 65, 60, 48, 48, 43, 43, 43, 54, 65, 77, 94, 94, 99, 99,
//     94, 88, 77, 65, 54, 43, 31, 26, 15, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//     3, 9, 20, 26, 37, 48, 60, 77, 82, 94, 111, 122, 128, 139, 150, 167, 178,
//     190, 201, 218, 229, 240, 246, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 252, 246, 240, 235, 229, 218, 212, 207, 201,
//     195, 184, 178, 173, 161, 156, 150, 144, 144, 133, 128, 128, 116, 111, 105,
//     105, 99, 88, 82, 82, 77, 71, 65, 60, 54, 54, 48, 43, 43, 37, 31, 31, 26,
//     26, 20, 20, 15, 20, 9, 9, 9, 9, 9, 3, 3, 3, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0,
//     3, 0, 3, 9, 3, 9, 15, 9, 15, 20, 15, 20, 20, 26, 31, 26, 31, 37, 43, 37,
//     43, 48, 54, 54, 48, 54, 60, 60, 65, 65, 71, 71, 77, 77, 82, 88, 94, 88,
//     88, 94, 99, 105, 105, 111, 111, 116, 122, 122, 116, 128, 128, 128, 128,
//     133, 128, 133, 139, 144, 144, 139, 144, 144, 150, 144, 150, 150, 156, 150,
//     156, 156, 161, 161, 167, 167, 167, 167, 173, 167, 173, 173, 178, 178, 178,
//     173, 178, 173, 178, 184, 178, 184, 178, 184, 184, 184, 190, 184, 184, 184,
//     184, 184, 190, 184, 190, 184, 190, 190, 184, 184, 190, 184, 190, 184, 178,
//     178, 184, 178, 184, 184, 184, 178, 178, 173, 178, 173, 173, 178, 173, 167,
//     167, 173, 167, 173, 173, 167, 173, 167, 161, 161, 167, 161, 167, 161, 156,
//     161, 156, 156, 156, 156, 150, 156, 150, 156, 150, 144, 144, 150, 144, 144,
//     139, 144, 139, 133, 133, 139, 133, 133, 139, 133, 133, 128, 133, 128, 128,
//     128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 122, 122, 128,
//     122, 128, 122, 128, 122, 116, 116, 122, 116, 122, 116, 111, 116, 116, 111,
//     111, 116, 111, 111, 116, 111, 105, 111, 111, 105, 111, 105, 111, 105, 105,
//     105, 105, 99, 105, 99, 105, 99, 105, 99, 105, 111, 105, 111, 111, 105,
//     105, 105, 99, 105, 105, 105, 99, 105, 105, 99, 105, 111, 105, 111, 105,
//     105, 111, 111, 105, 111, 105, 111, 111, 111, 116, 116, 111, 116, 111, 116,
//     116, 111, 116, 111, 111, 116, 111, 116, 116, 116, 116, 122, 116, 116, 122,
//     116, 122, 122, 116, 116, 122, 116, 122, 116, 111, 116, 111, 116, 116, 116,
//     122, 122, 116, 122, 116, 122, 116, 122, 128, 122, 128, 128, 128, 122, 128,
//     128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 133, 128, 133, 133,
//     128, 128, 133, 133, 128, 133, 139, 139, 133, 139, 133, 139, 144, 139, 133,
//     139, 144, 139, 133, 139, 139, 139, 144, 139, 139, 144, 144, 139, 144, 144,
//     139, 144, 144, 139, 139, 144, 139, 144, 144, 139, 139, 144, 139, 144, 139,
//     144, 139, 144, 139, 144, 144, 139, 144, 139, 139, 139, 139, 139, 144, 139,
//     144, 144, 139, 144, 144, 139, 139, 144, 139, 144, 144, 139, 144, 139, 139,
//     144, 144, 139, 144, 139, 144, 139, 139, 139
// };

// // fastinvader4.wav converted to array
// const unsigned char fastinvader4[FASTINVADER4SIZE] = {
//     133, 133, 128, 133, 128, 128, 133, 133, 139, 133, 128, 133, 133, 133, 133,
//     133, 128, 133, 133, 128, 133, 128, 133, 133, 133, 122, 99, 77, 54, 31, 20,
//     9, 15, 26, 43, 60, 88, 99, 128, 139, 161, 184, 201, 218, 229, 240, 246,
//     255, 255, 255, 255, 255, 255, 255, 255, 252, 252, 240, 235, 224, 218, 207,
//     201, 190, 184, 167, 156, 150, 133, 128, 122, 116, 105, 99, 82, 82, 71, 71,
//     60, 60, 60, 71, 82, 94, 88, 94, 99, 88, 82, 65, 54, 43, 31, 15, 3, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 15, 26, 37,
//     54, 60, 77, 82, 99, 111, 122, 128, 139, 150, 167, 173, 190, 201, 212, 218,
//     229, 235, 246, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 246, 235, 229, 224, 224,
//     212, 201, 195, 184, 161, 133, 111, 82, 60, 43, 37, 31, 37, 43, 54, 65, 82,
//     94, 105, 116, 122, 133, 139, 144, 150, 161, 161, 161, 167, 161, 156, 150,
//     150, 144, 139, 128, 128, 122, 116, 105, 99, 82, 77, 65, 54, 43, 37, 26,
//     15, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//     0, 15, 26, 43, 60, 77, 94, 111, 128, 139, 156, 173, 178, 195, 212, 224,
//     240, 252, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 252, 235, 207, 178, 150, 128, 111, 99, 99, 105, 111,
//     122, 128, 139, 150, 167, 178, 190, 201, 201, 212, 218, 224, 224, 229, 224,
//     224, 224, 212, 212, 207, 201, 190, 184, 173, 161, 150, 139, 128, 122, 105,
//     94, 88, 77, 65, 54, 43, 26, 26, 15, 0, 0, 0, 0, 0, 0, 0, 0, 3, 9, 9, 3, 3,
//     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0, 3, 15, 26, 43, 60, 71, 82, 99, 116, 128, 139, 150,
//     161, 178, 190, 201, 212, 218, 229, 246, 252, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     252, 246, 240, 235, 224, 218, 212, 195, 173, 139, 122, 99, 77, 71, 65, 65,
//     71, 82, 94, 105, 116, 128, 139, 150, 161, 173, 184, 190, 195, 195, 201,
//     195, 201, 195, 195, 190, 178, 173, 167, 161, 150, 139, 128, 128, 116, 105,
//     99, 82, 71, 60, 48, 37, 26, 20, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3,
//     3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0, 15, 31, 43, 60, 71, 94, 99, 116, 128, 139, 156,
//     173, 184, 195, 207, 224, 235, 246, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 252, 252, 240, 224, 207, 173, 144, 128, 105,
//     88, 82, 88, 82, 94, 111, 122, 128, 144, 156, 173, 178, 190, 207, 207, 212,
//     218, 218, 224, 224, 212, 207, 201, 190, 184, 178, 167, 156, 150, 139, 128,
//     128, 111, 99, 88, 77, 71, 54, 43, 37, 26, 15, 3, 0, 0, 0, 0, 0, 0, 0, 0,
//     0, 3, 9, 9, 15, 9, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 26, 43, 60, 71, 88, 99, 116,
//     128, 139, 156, 167, 178, 190, 207, 218, 229, 240, 252, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//     255, 255, 255, 255, 255, 255, 255, 252, 246, 240, 229, 224, 218, 212, 207,
//     195, 190, 184, 178, 173, 167, 156, 150, 144, 139, 133, 128, 128, 128, 122,
//     116, 111, 105, 99, 94, 88, 82, 77, 77, 77, 71, 65, 65, 60, 60, 54, 48, 43,
//     43, 37, 37, 43, 37, 31, 37, 31, 26, 31, 26, 31, 26, 26, 26, 26, 26, 31,
//     31, 31, 26, 31, 31, 37, 37, 31, 37, 37, 31, 37, 43, 37, 43, 43, 43, 48,
//     43, 48, 54, 54, 60, 54, 60, 60, 65, 71, 65, 71, 71, 77, 77, 82, 77, 82,
//     82, 88, 88, 94, 99, 105, 99, 105, 105, 105, 111, 111, 116, 116, 116, 122,
//     122, 116, 122, 128, 128, 128, 133, 133, 128, 133, 133, 139, 133, 139, 144,
//     144, 139, 144, 150, 150, 150, 156, 150, 156, 156, 156, 156, 161, 156, 161,
//     167, 167, 167, 161, 167, 173, 173, 167, 173, 167, 173, 167, 173, 167, 173,
//     173, 173, 173, 178, 173, 178, 173, 173, 178, 173, 173, 173, 167, 173, 173,
//     167, 173, 173, 173, 167, 173, 173, 173, 167, 167, 161, 167, 161, 167, 161,
//     167, 161, 167, 161, 167, 161, 156, 161, 156, 156, 156, 150, 150, 156, 150,
//     156, 150, 144, 144, 150, 144, 144, 144, 139, 144, 150, 150, 144, 144, 144,
//     139, 144, 139, 133, 139, 144, 139, 133, 139, 139, 139, 133, 128, 128, 133,
//     128, 133, 128, 133, 128, 128, 128, 128, 128, 128, 128, 128, 128, 122, 116,
//     116, 122, 116, 111, 111, 116, 111, 116, 111, 111, 116, 111, 111, 116, 111,
//     116, 111, 111, 116, 111, 105, 111, 116, 111, 111, 116, 111, 116, 111, 111,
//     116, 111, 116, 111, 105, 116
// };

// ufo_highpitch.wav converted to array
const unsigned char highpitch[HIGHPITCHSIZE] = {
    255, 162, 102, 101, 46, 7, 47, 59, 111, 150, 160, 176, 163, 226, 220, 199,
    157, 120, 74, 95, 31, 13, 47, 64, 116, 155, 162, 171, 181, 246, 207, 194,
    142, 102, 84, 70, 8, 31, 53, 92, 138, 156, 174, 162, 223, 226, 201, 167,
    124, 79, 95, 18, 18, 47, 71, 119, 154, 170, 159, 206, 239, 203, 183, 136,
    85, 101, 25, 9, 43, 62, 114, 155, 166, 164, 206, 239, 204, 183, 136, 87,
    97, 24, 10, 44, 71, 114, 153, 166, 163, 222, 233, 203, 172, 125, 89, 78,
    9, 23, 48, 91, 124, 163, 164, 183, 249, 212, 198, 147, 93, 96, 36, 6, 42,
    64, 110, 152, 166, 168, 227, 228, 203, 161, 113, 97, 58, 0, 37, 52, 104,
    141, 167, 162, 221, 236, 204, 171, 116, 99, 57, 0, 35, 53, 104, 139, 167,
    162, 221, 236, 204, 171, 113, 101, 54, 0, 37, 54, 106, 149, 157, 176, 238,
    225, 202, 155, 106, 98, 22, 8, 42, 76, 117, 160, 152, 209, 248, 209, 185,
    129, 107, 59, 0, 31, 51, 104, 142, 156, 180, 244, 222, 201, 152, 109, 86,
    10, 13, 45, 92, 123, 160, 159, 234, 233, 204, 162, 119, 92, 19, 8, 43, 81,
    125, 162, 155, 232, 236, 206, 166, 115, 92, 19, 8, 43, 88, 127, 156, 170,
    242, 227, 204, 149, 118, 71, 2, 19, 47, 102, 143, 148, 201, 252, 213, 195,
    128, 116, 38, 0, 36, 60, 107, 148, 149, 232, 245, 209, 153, 122, 66, 4,
    22, 47, 93, 139, 145, 216, 250, 212, 175, 123, 92, 16, 8, 43, 90, 131,
    143, 203, 253, 215, 188, 130, 102, 21, 5, 40, 86, 129, 144, 206, 253, 215,
    183, 135, 85, 19, 7, 42, 97, 139, 145, 219, 248, 210, 163, 143, 60, 2, 19,
    54, 106, 140, 168, 243, 233, 206, 144, 126, 32, 0, 39, 77, 126, 141, 210,
    252, 213, 174, 143, 59, 2, 19, 59, 109, 134, 183, 250, 227, 196, 143, 99,
    16, 6, 44, 99, 135, 163, 236, 238, 203, 150, 116, 19, 3, 40, 91, 127, 161,
    234, 241, 202, 153, 110, 21, 3, 40, 96, 122, 172, 237, 238, 194, 150, 92,
    9, 8, 50, 104, 126, 193, 255, 222, 175, 154, 53, 0, 31, 64, 116, 140, 216,
    252, 206, 164, 124, 24, 1, 47, 92, 112, 184, 252, 230, 182, 151, 48, 0,
    40, 64, 116, 155, 228, 247, 192, 163, 89, 9, 13, 52, 109, 132, 215, 253,
    202, 168, 107, 16, 5, 50, 105, 128, 211, 254, 199, 171, 113, 17, 4, 54,
    108, 125, 216, 253, 197, 171, 94, 13, 18, 55, 109, 142, 227, 249, 184,
    169, 62, 0, 47, 70, 107, 182, 247, 224, 185, 137, 28, 0, 49, 100, 125,
    220, 252, 190, 172, 72, 0, 46, 68, 104, 189, 252, 213, 182, 117, 21, 6,
    64, 99, 157, 237, 239, 188, 140, 36, 0, 57, 98, 126, 233, 248, 185, 161,
    38, 0, 56, 90, 130, 229, 249, 189, 154, 33, 0, 60, 93, 139, 231, 246, 181,
    148, 35, 0, 67, 90, 159, 240, 223, 195, 114, 24, 11, 71, 97, 192, 255,
    195, 190, 68, 0, 57, 72, 126, 221, 252, 189, 138, 42, 0, 73, 87, 188, 255,
    195, 191, 60, 0, 69, 69, 143, 235, 226, 199, 107, 21, 30, 66, 112, 215,
    255, 187, 135, 32, 1, 75, 99, 205, 255, 184, 159, 39, 0, 74, 89, 204, 255,
    189, 160, 38, 0, 83, 93, 206, 255, 188, 146, 36, 9, 72, 102, 217, 255,
    195, 113, 18, 39, 66, 134, 231, 227, 201, 66, 0, 72, 69, 181, 255, 194,
    172, 44, 0, 61, 103, 212, 240, 193, 87, 7, 58, 60, 176, 247, 193, 162, 31,
    13, 69, 127, 224, 227, 188, 55, 0, 72, 95, 209, 247, 197, 78, 4, 65, 71,
    202, 253, 198, 99, 12, 61, 65, 193, 249, 199, 105, 19, 60, 67, 195, 247,
    200, 97, 14, 64, 77, 202, 252, 187, 80, 7, 63, 108, 206, 252, 176, 60, 3,
    68, 144, 219, 233, 143, 43, 30, 66, 187, 244, 195, 87, 10, 65, 109, 207,
    246, 152, 58, 16, 68, 180, 243, 199, 84, 12, 65, 122, 214, 240, 130, 43,
    44, 76, 195, 246, 167, 63, 13, 66, 178, 243, 189, 76, 12, 64, 164, 230,
    209, 82, 18, 64, 147, 224, 217, 88, 17, 65, 143, 222, 211, 86, 23, 64,
    151, 231, 204, 79, 21, 68, 169, 236, 177, 69, 24, 74, 192, 246, 146, 55,
    37, 93, 206, 231, 103, 33, 59, 144, 228, 191, 74, 25, 83, 184, 251, 116,
    38, 61, 133, 221, 185, 79, 26, 93, 193, 238, 101, 33, 70, 155, 244, 134,
    60, 45, 125, 222, 178, 84, 23, 105, 192, 225, 93, 23, 96, 174, 249, 94,
    28, 92, 164, 249, 95, 38, 81, 155, 250, 103, 40, 88, 157, 244, 95, 35, 95,
    162, 243, 89, 25, 114, 176, 219, 86, 19, 135, 207, 162, 87, 38, 148, 236,
    107, 59, 86, 160, 233, 87, 22, 136, 201, 157, 86, 50, 159, 233, 91, 30,
    127, 198, 159, 81, 55, 165, 230, 86, 23, 145, 206, 127, 63, 101, 176, 183,
    80, 51, 169, 220, 81, 31, 158, 216, 100, 38, 143, 199, 120, 54, 123, 197,
    138, 61, 112, 185, 147, 64, 102, 190, 147, 68, 106, 180, 145, 65, 113,
    194, 130, 54, 132, 200, 105, 47, 158, 201, 91, 44, 181, 197, 75, 66, 189,
    165, 58, 121, 191, 103, 50, 171, 198, 75, 68, 194, 152, 53, 151, 188, 85,
    53, 192, 163, 52, 150, 183, 85, 59, 201, 141, 46, 176, 174, 68, 102, 198,
    98, 50, 205, 146, 45, 188, 162, 59, 141, 181, 79, 90, 199, 98, 59, 213,
    116, 51, 210, 126, 46, 206, 138, 46, 187, 160, 56, 150, 178, 78, 91, 198,
    105, 50, 199, 140, 46, 153, 178, 68, 77, 198, 123, 37, 184, 176, 62, 93,
    190, 119, 46, 175, 189, 66, 75, 194, 147, 53, 135, 193, 98, 46, 171, 200,
    76, 51, 184, 189, 70, 79, 186, 165, 61, 102, 193, 142, 65, 115, 190, 140,
    60, 109, 187, 149, 67, 99, 189, 163, 72, 77, 181, 191, 78, 44, 177, 221,
    78, 31, 157, 216, 106, 53, 124, 186, 167, 79, 52, 173, 227, 73, 30, 150,
    209, 135, 72, 71, 170, 231, 73, 29, 138, 200, 171, 77, 43, 161, 233, 102,
    63, 82, 163, 246, 75, 32, 116, 178, 223, 72, 21, 131, 197, 197, 82, 18,
    139, 206, 184, 78, 23, 134, 208, 188, 80, 21, 127, 201, 203, 77, 21, 109,
    194, 236, 77, 31, 91, 177, 253, 98, 46, 60, 150, 240, 147, 66, 37, 112,
    212, 217, 80, 25, 78, 181, 244, 138, 51, 42, 113, 209, 223, 82, 27, 70,
    169, 247, 166, 56, 23, 83, 209, 246, 125, 46, 46, 102, 213, 233, 93, 33,
    66, 123, 220, 215, 81, 26, 70, 140, 225, 210, 81, 23, 70, 138, 226, 220,
    89, 32, 65, 119, 219, 232, 104, 38, 44, 98, 216, 248, 134, 50, 25, 77,
    200, 246, 175, 56, 8, 73, 161, 226, 216, 97, 31, 59, 88, 215, 244, 159,
    53, 6, 74, 169, 229, 214, 109, 33, 45, 80, 208, 248, 179, 60, 12, 72, 110,
    226, 240, 160, 42, 7, 75, 143, 225, 229, 151, 33, 17, 68, 160, 232, 219,
    146, 32, 19, 75, 153, 234, 217, 159, 28, 10, 76, 141, 229, 227, 171, 43,
    3, 78, 104, 230, 245, 183, 68, 9, 67, 74, 205, 242, 194, 138, 19, 27, 71,
    142, 235, 228, 182, 46, 7, 76, 77, 216, 247, 189, 148, 21, 12, 79, 120,
    233, 247, 186, 80, 15, 52, 69, 161, 234, 222, 188, 46, 12, 73, 69, 180,
    244, 201, 184, 38, 0, 78, 72, 192, 243, 206, 188, 40, 5, 72, 73, 171, 236,
    223, 185, 59, 9, 59, 76, 147, 241, 239, 179, 101, 18, 22, 79, 109, 231,
    252, 179, 164, 15, 0, 85, 86, 189, 242, 209, 183, 76, 8, 45, 80, 118, 235,
    249, 174, 153, 14, 2, 67, 83, 156, 240, 235, 173, 121, 14, 5, 77, 100,
    186, 241, 215, 176, 93, 9, 18, 74, 112, 195, 246, 208, 179, 83, 11, 24,
    72, 112, 200, 246, 212, 174, 89, 12, 12, 75, 115, 181, 244, 228, 173, 122,
    9, 5, 69, 107, 148, 250, 238, 176, 156, 24, 0, 71, 80, 128, 219, 251, 200,
    174, 87, 3, 15, 73, 117, 158, 250, 233, 175, 153, 28, 0, 63, 79, 128, 199,
    250, 215, 176, 127, 11, 4, 65, 95, 128, 223, 251, 197, 169, 110, 6, 7, 70,
    103, 133, 229, 249, 193, 167, 107, 4, 8, 67, 102, 131, 222, 251, 203, 170,
    117, 3, 6, 68, 94, 130, 198, 249, 221, 168, 138, 19, 1, 55, 75, 133, 156,
    249, 233, 178, 152, 81, 0, 18, 69, 112, 137, 214, 252, 205, 169, 135, 14,
    2, 46, 79, 129, 149, 249, 239, 184, 158, 104, 0, 10, 59, 97, 138, 174,
    253, 227, 179, 146, 89, 0, 15, 64, 105, 133, 183, 250, 227, 178, 140, 86,
    0, 18, 64, 102, 138, 178, 252, 227, 183, 146, 100, 0, 13, 60, 98, 138,
    155, 250, 233, 187, 157, 116, 11, 5, 51, 73, 135, 140, 212, 251, 213, 174,
    125, 70, 0, 23, 62, 111, 141, 165, 253, 228, 189, 150, 114, 15, 5, 43, 76,
    124, 147, 193, 255, 219, 182, 130, 105, 0, 13, 52, 90, 140, 145, 212, 250,
    211, 177, 123, 100, 0, 19, 53, 92, 141, 151, 215, 249, 210, 177, 120, 103,
    0, 14, 56, 84, 140, 150, 188, 255, 215, 182, 139, 108, 10, 6, 43, 71, 136,
    151, 162, 255, 221, 195, 154, 111, 67, 0, 28, 62, 110, 142, 154, 213, 248,
    210, 173, 128, 104, 11, 8, 42, 70, 134, 160, 152, 253, 227, 204, 164, 107,
    99, 0, 17, 51, 82, 141, 158, 164, 255, 219, 196, 150, 107, 90, 0, 24, 59,
    89, 139, 159, 164, 255, 219, 202, 149, 111, 91, 0, 22, 51, 83, 143, 160,
    157, 244, 228, 204, 169, 112, 101, 23, 6, 40, 67, 127, 154, 162, 195, 250,
    210, 189, 132, 99, 77, 0, 30, 60, 96, 148, 161, 164, 241, 225, 199, 159,
    108, 88, 33, 6, 43, 60, 114, 150, 162, 169, 255, 215, 193, 149, 106, 90,
    11, 13, 45, 68, 125, 152, 166, 174, 254, 212, 191, 147, 103, 91, 10, 13,
    45, 68, 127, 158, 163, 174, 254, 212, 200, 154, 101, 90, 42, 5, 42, 67,
    119, 148, 166, 164, 238, 223, 202, 174, 112, 96, 78, 0, 34, 54, 99, 143,
    160, 166, 183, 250, 207
};

// smallexplosion.wav converted to array
const unsigned char smallexplosion[SMALLEXPLOSIONSIZE] = {
    8, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7, 8, 8, 8, 9, 8, 8, 7, 7, 7, 8, 8,
    8, 8, 8, 8, 8, 7, 7, 7, 8, 8, 8, 9, 8, 8, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 7,
    7, 7, 8, 8, 8, 9, 8, 8, 7, 6, 7, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7, 8, 8, 8, 9,
    8, 8, 7, 6, 6, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7, 8, 8, 8, 9, 8, 8, 7, 6, 6, 6,
    8, 8, 8, 8, 8, 8, 7, 7, 7, 8, 8, 8, 9, 8, 8, 7, 6, 6, 6, 6, 8, 8, 8, 8, 8,
    7, 7, 7, 8, 8, 8, 9, 8, 8, 7, 6, 6, 6, 6, 7, 8, 8, 8, 8, 7, 7, 7, 8, 8, 8,
    9, 8, 8, 7, 6, 6, 6, 6, 7, 8, 8, 8, 8, 7, 7, 7, 8, 8, 8, 9, 8, 8, 7, 6, 6,
    6, 6, 7, 8, 9, 8, 8, 7, 7, 7, 8, 8, 8, 9, 8, 8, 7, 6, 6, 6, 6, 7, 8, 9, 9,
    8, 7, 7, 7, 8, 8, 8, 9, 8, 8, 7, 6, 6, 6, 6, 7, 8, 9, 9, 8, 7, 7, 7, 8, 8,
    8, 9, 8, 8, 7, 6, 6, 6, 6, 7, 8, 9, 9, 8, 8, 7, 7, 8, 8, 8, 9, 8, 8, 7, 6,
    6, 6, 6, 7, 8, 9, 9, 8, 8, 7, 7, 8, 8, 8, 9, 8, 8, 7, 6, 6, 6, 6, 7, 8, 9,
    9, 8, 8, 7, 6, 2, 5, 9, 14, 16, 16, 16, 16, 16, 16, 16, 15, 13, 10, 5, 0,
    0, 0, 0, 0, 0, 0, 3, 5, 5, 4, 4, 6, 7, 8, 8, 8, 8, 9, 12, 14, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 13, 9, 5, 2, 0, 0, 0, 0, 0, 3, 7, 8,
    7, 5, 3, 1, 2, 4, 5, 6, 6, 6, 7, 7, 8, 10, 13, 16, 16, 16, 16, 16, 16, 14,
    10, 7, 5, 6, 8, 10, 12, 13, 12, 9, 5, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 13,
    16, 16, 16, 16, 16, 14, 11, 9, 7, 4, 0, 0, 0, 0, 0, 0, 0, 2, 8, 12, 13,
    13, 14, 15, 16, 16, 16, 16, 13, 13, 14, 16, 16, 16, 16, 16, 13, 9, 7, 7,
    8, 10, 12, 14, 14, 12, 10, 8, 7, 7, 6, 6, 6, 6, 7, 7, 7, 5, 3, 1, 1, 3, 5,
    7, 8, 9, 10, 12, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 11, 7, 3, 1, 2,
    4, 5, 8, 11, 14, 15, 13, 10, 6, 2, 0, 0, 0, 0, 1, 2, 5, 8, 9, 10, 11, 11,
    12, 11, 7, 4, 2, 2, 2, 2, 2, 3, 4, 4, 4, 5, 6, 5, 5, 5, 4, 3, 3, 4, 5, 6,
    9, 12, 14, 15, 14, 13, 10, 9, 9, 9, 9, 7, 6, 5, 5, 7, 10, 14, 16, 16, 15,
    15, 14, 13, 11, 9, 8, 7, 6, 6, 6, 7, 8, 9, 9, 10, 10, 10, 10, 10, 10, 10,
    10, 10, 11, 11, 12, 12, 12, 12, 11, 10, 10, 9, 9, 7, 7, 6, 6, 6, 6, 6, 7,
    6, 6, 5, 4, 4, 4, 5, 5, 5, 5, 6, 8, 9, 9, 10, 10, 11, 11, 11, 11, 10, 10,
    9, 7, 5, 3, 2, 1, 2, 2, 4, 5, 7, 7, 8, 9, 10, 11, 11, 10, 9, 9, 8, 8, 8,
    9, 8, 8, 6, 5, 4, 4, 4, 5, 5, 6, 7, 8, 9, 9, 9, 8, 9, 10, 11, 11, 11, 10,
    9, 8, 7, 7, 8, 11, 13, 15, 16, 16, 16, 16, 16, 14, 10, 5, 1, 0, 0, 3, 5,
    6, 6, 8, 8, 7, 7, 6, 4, 3, 2, 1, 0, 1, 2, 3, 5, 8, 12, 13, 13, 11, 9, 7,
    7, 7, 7, 8, 9, 9, 10, 11, 12, 12, 11, 8, 6, 4, 1, 1, 1, 2, 4, 6, 9, 11,
    11, 10, 7, 5, 4, 5, 6, 6, 5, 4, 4, 5, 7, 11, 14, 16, 16, 16, 15, 14, 13,
    13, 12, 11, 9, 5, 1, 0, 0, 0, 0, 0, 0, 3, 5, 5, 4, 4, 6, 7, 8, 8, 8, 8, 9,
    11, 13, 15, 16, 16, 16, 16, 15, 15, 15, 16, 16, 16, 16, 13, 9, 6, 3, 0, 0,
    0, 0, 0, 3, 7, 8, 7, 4, 2, 1, 2, 4, 5, 6, 6, 6, 7, 7, 8, 10, 13, 16, 16,
    16, 16, 16, 16, 14, 10, 7, 5, 6, 8, 10, 12, 13, 12, 9, 5, 0, 0, 0, 0, 0,
    0, 0, 0, 3, 8, 13, 16, 16, 16, 16, 16, 14, 11, 9, 7, 4, 0, 0, 0, 0, 0, 0,
    0, 2, 8, 12, 13, 13, 14, 15, 16, 16, 16, 16, 13, 13, 14, 16, 16, 16, 16,
    16, 13, 9, 7, 7, 8, 10, 12, 14, 14, 12, 10, 8, 7, 7, 6, 6, 6, 6, 7, 7, 7,
    5, 3, 1, 1, 3, 5, 7, 8, 9, 10, 12, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    12, 7, 3, 1, 1, 3, 5, 8, 11, 14, 16, 14, 10, 6, 1, 0, 0, 0, 0, 0, 2, 5, 8,
    9, 10, 10, 11, 12, 11, 7, 3, 1, 1, 2, 1, 2, 3, 4, 4, 4, 5, 5, 5, 4, 4, 2,
    1, 1, 2, 4, 6, 10, 14, 16, 16, 16, 14, 11, 9, 9, 9, 8, 6, 5, 3, 3, 6, 10,
    15, 16, 16, 16, 16, 16, 16, 16, 13, 11, 9, 8, 6, 6, 7, 8, 9, 9, 10, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 9, 9, 9, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 8, 7, 7, 8, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 6, 5, 5, 5, 4, 4, 7, 10, 11, 11, 10, 8, 5, 4, 3, 3, 3,
    4, 5, 9, 13, 16, 16, 16, 16, 16, 15, 9, 5, 4, 4, 6, 6, 5, 4, 2, 2, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 4, 10, 16, 16, 16, 16, 16, 15, 15, 14, 13, 11, 8,
    6, 4, 3, 3, 3, 2, 0, 0, 2, 5, 7, 7, 6, 5, 4, 3, 3, 4, 5, 6, 8, 9, 11, 13,
    16, 16, 16, 16, 16, 16, 16, 16, 11, 7, 3, 0, 0, 0, 0, 0, 0, 0, 4, 6, 7, 6,
    6, 6, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 7, 6, 3, 2, 0, 0, 2, 3, 5,
    7, 9, 11, 13, 14, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 7, 1, 0, 0,
    0, 0, 0, 1, 6, 8, 8, 6, 3, 1, 0, 0, 0, 0, 0, 0, 1, 2, 2, 0, 0, 1, 4, 7, 8,
    8, 7, 6, 8, 11, 14, 15, 14, 12, 10, 9, 7, 6, 6, 6, 6, 6, 6, 6, 4, 2, 1, 2,
    5, 10, 13, 13, 13, 11, 11, 11, 11, 10, 8, 8, 9, 10, 10, 10, 11, 14, 14,
    14, 14, 14, 13, 11, 8, 6, 4, 2, 1, 1, 1, 1, 2, 2, 3, 3, 2, 2, 3, 4, 6, 8,
    10, 9, 9, 8, 8, 8, 7, 7, 7, 7, 7, 7, 7, 6, 5, 7, 9, 9, 9, 9, 9, 9, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7,
    7, 7, 7, 8, 9, 9, 9, 9, 8, 8, 8, 8, 7, 7, 7, 7, 7, 8, 8, 8, 7, 7, 7, 7, 7,
    6, 5, 4, 5, 7, 9, 10, 11, 12, 11, 10, 9, 8, 7, 7, 6, 6, 6, 6, 6, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 7, 7, 7, 7, 7, 7, 7, 5, 3, 2, 2, 4, 6,
    8, 8, 9, 9, 8, 8, 9, 11, 13, 15, 16, 16, 16, 16, 15, 13, 11, 8, 5, 4, 4,
    3, 3, 3, 5, 7, 8, 8, 9, 9, 8, 6, 4, 3, 2, 1, 0, 0, 0, 0, 0, 1, 2, 4, 7,
    11, 14, 15, 14, 13, 11, 9, 8, 7, 7, 6, 6, 6, 6, 7, 7, 7, 8, 6
};

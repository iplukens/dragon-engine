iplukens, rjsmieja
Ian Lukens, Robert Smieja
Project 3, The Misadventures of Michigan Frank - imgd3000

We are using the official Dragonfly 2.5 engine

The platforms used for development were Mac OS X 10.6.8 and Windows 7 64-bit with Cygwin 64-bit.

Instructions for compiling:

1) Run 'make' in the directory where the source code is located
2) Run './game' after to launch the game. Controls are described in the title screen.

A more detailed description of the game is located in game.txt

All output display displays in the dragonfly.log file.

Source code is structured as follows:

Bullet.cpp/.h is a representation of the actual bullet fired by the player
EventHeroMove.cpp/.h is an event that is sent when the player or 'Hero' moves.
GameStart.cpp/.h handles the splash screen and main initialization of the game.
HealthPickup.cpp/.h is a representation of a pickup that restores the player's health.
Hero.cpp/.h is a representation of the player or 'Hero'
MaxHealthPickup.cpp/.h is a representation of a powerup that increases the player's max health.
MazePiece.cpp/.h is a representation of the walls in the play area
Monster.cpp/.h is the enemy that attempts path finding to the player
Pickup.h is a parent class that all other pickups inherit from
Points.cpp/.h is a ViewObject that represents the player's current score.
RapidFire.cpp/.h is a power up that increases the player's allowed firing rate

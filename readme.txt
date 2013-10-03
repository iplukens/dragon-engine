iplukens
Ian Lukens
Project 2c resubmission of 2b - imgd3000

The platform I used was Mac OS X 10.6.8, building in eclipse although building from terminal also works.  Just 'make' and run './game'.

All output display displays in the dragonfly.log file.

Most files should be working correctly for project 2b.  The manager correctly handles and sends events.  The gameManager loop works and sends step events.  The InputManager detects keyboard clicks.  The World Manager handles velocity, collisions and out of bounds.  Objects register everything appropriately.  However, display is currently not working although sprites load correctly.  

The game loop runs until the 'x' button is pressed, at which point it stops.  The display attempts to draw but nothing happens.

Basically, a bunch of IGetDeleted objects get created and start moving in the -1 x direction.  These objects are spectral and go forever until receiving an out event upon which they reset position. Upon receiving enough step events, these objects delete themselves.

The EndOfWorlds object takes in a velocity and tries to move in that direction.  I have it set up that there are two, so they collide and do not end up moving.  It also has a keyboard event response, and pressing x ends the game.
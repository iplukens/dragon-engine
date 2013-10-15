#
# Makefile for development of game using Dragonfly
#
# 'make' to build executable
# 'make depend' to generate new dependency list
# 'make clean' to remove all constructed files
#
# Variables of interest:
#   GAMESRC is the source code files for the game being developed
#   GAME is the game main() source
#   DEBUG can be set to -DDEBUG to enable various debug flags
#

CC= g++ 
#PLATFORM= -DCYGWIN		# uncomment for cygwin
PLATFORM= -DMACOS  		# uncomment for macos
#LDFLAGS= -lncurses -lrt	# uncomment linux/cygwin
LDFLAGS= -lncurses 		# uncomment for macos
INCPATH= include		# path to engine includes
ENG= lib/libdragonfly-macos64.a		# dragonfly engine for mac os x
#ENG= lib/libdragonfly-cygwin64.a # dragonfly engine for cygwin
GAMESRC = Bullet.cpp \
	Explosion.cpp \
	HealthPickup.cpp \
	Hero.cpp \
	MaxHealthPickup.cpp \
	MazePiece.cpp \
	RapidFire.cpp \
	EventHeroMove.cpp \
	Monster.cpp \
	Points.cpp \
	GameStart.cpp \
	LevelManager.cpp \
	PointsPickup.cpp \
	Ghost.cpp \
	Monster2.cpp
# ENGINESRC= Event.cpp \
	# LogManager.cpp \
	# Clock.cpp \
	# GameManager.cpp \
	# Object.cpp \
	# ObjectList.cpp \
	# ObjectListIterator.cpp \
	# Position.cpp \
	# WorldManager.cpp \
	# EventStep.cpp \
	# Manager.cpp \
	# GraphicsManager.cpp \
	# InputManager.cpp \
	# EventKeyboard.cpp \
	# EventMouse.cpp \
	# EventCollision.cpp \
	# Sprite.cpp \
	# Frame.cpp \
	# ResourceManager.cpp \
	# EventOut.cpp \
	# Box.cpp \
	# ViewObject.cpp \
	# EventView.cpp \
	# utility.cpp

GAME= game.cpp
EXECUTABLE= game		
OBJECTS= $(GAMESRC:.cpp=.o) $(ENGINESRC:.cpp=.o)

all: $(EXECUTABLE) Makefile

$(EXECUTABLE): $(ENG) $(OBJECTS) $(GAME) $(ENGINESRC) $(GAMESRC)
	$(CC) $(GAME) $(OBJECTS) $(ENG) -o $@ -I$(INCPATH) $(LDFLAGS) $(PLATFORM)

.cpp.o: 
	$(CC) -c $(DEBUG) $(PLATFORM) -I$(INCPATH) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) core dragonfly.log Makefile.bak *~

depend: 
	makedepend *.cpp 2> /dev/null

# DO NOT DELETE

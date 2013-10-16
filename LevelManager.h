///
/// The level manager
///

#ifndef __LEVEL_MANAGER_H__
#define __LEVEL_MANAGER_H__

#include <string>
#include <map>
#include <list>

#include "Position.h"
#include "Manager.h"

//Offset to account for viewObjects
#define VIEW_OBJECT_OFFSET 3

// Delimiters used to parse Level files -
// the LevelManager "knows" file format.
#define FRAMES_TOKEN "frames"
#define HEIGHT_TOKEN "height"
#define WIDTH_TOKEN "width"
#define COLOR_TOKEN "color"
#define END_FRAME_TOKEN "end"
#define END_SPRITE_TOKEN "eof"

using std::string;
using std::map;
using std::list;

class LevelManager : public Manager {

 private:
  LevelManager (LevelManager const&); ///< Don't allow copy.
  void operator=(LevelManager const&); ///< Don't allow assignment.
  LevelManager();                      ///< Private since a singleton.
  map<string, string> level_files;      ///< Array of filenames and levels
  map<string, int> levels;				///< Array of filenames and level
  int level_count;                       ///< Count of number of loaded levels.
  ObjectList current_level_obj; 		///< Current objects in the level
  list<string> level_order; 			///< Order to use when calling nextLevel

 public:
  /// Get the one and only instance of the ResourceManager.
  static LevelManager &getInstance();

  /// Get manager ready for resources.
  int startUp();

  /// Shut down manager, freeing up any allocated Levels.
  void shutDown();

  /// Load Level from file.
  /// Assign indicated label to sprite.
  /// Return 0 if ok, else -1.
  int prepareLevel(string filename, string label);

  /// Unload Level with indicated label.
  /// Return 0 if ok, else -1.
  int removePreparedLevel(string label);

  /// Find Level with indicated label.
  /// Returns true if loading succeeded, false if it failed
  bool loadLevel(string label);

  /// Loads the next level in the list
  /// Returns true if loading succeeded, false if it failed
  bool nextLevel();

  void objectDelete(Object* p_obj); //Notify the level manager when an object was deleted in the level
};

#endif //__LEVEL_MANAGER_H__

# Basic Game Engine: Wolf-3d
Inspired by Wolfenstein 3D, which has been recognized as the first true “First Person Shooter” in the history of video games, the goal of this project is to build a basic game engine using ray casting technique.
<img src="https://github.com/pootitan/Wolf-3d/blob/master/img/wolf-intro.png" height="50%" width="50%"><br>

## Objectives
The fun part of this project is the bonuses. But before we can start hunting Nazis, we need to completely match the following requirments. <br>
- Create a 3D graphically “realistic” representation that we could have from inside a maze in a subjective view.
- Be able to choose the size and the shape of mazes, it has to be a file outside of the source code.
- The management of the window must remain smooth: passing over of another window, minimization, etc.
- Pressing ESC and click the red cross on the window must close the window and quit the program cleanly.
- The arrows on the keyboard must allow you to move in real time in the maze, like in the original game.
- Display different wall textures that vary depending on which compass point the wall is facing.
<br>
Beside the mandatory part, I also made full scene textures, sprites(a two-dimensional bitmap that is integrated into game scene to represent objects), custom map etc.

## How to start
First build the project with makefile
```
make
```
After "wolf3d" created, execute it with a map. Some maps can be found under maps/ folder, and of course anyone is welcome to create their own map ;)
```
// For instance, run teature room
./wolf3d maps/teasure_room.txt
```
W & S to move forward and backward, A & D to rotate.<br>
<img src="https://github.com/pootitan/Wolf-3d/blob/master/img/teasures.gif"><br>
Looks like you found Nazi's teasures!<br>

## Map generate guide
To create a map, some rules and formats need to be follow.
1. Defined map on first line, map body need to follow the size.
2. Need to allocate at least one player, showing as -1 in map.
3. 0 as floor, 1 or above as wall, can't have 0 on the wall
4. Textures all start from 1
<br>
Right under the map body, starting the sprite section
1. First line in sprite section defined the sprite numbers
2. Sprite has been defined by three number: x, y, texture numbers

```
20 18										// Map width and height
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1		// Map body
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 -1 0 0 0 0 0 0 0 0 0 0 1 
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

5 			// Sprite numbers, set to 0 if no sprite
4 4 6 		// Sprite body
4 8 6 	
4 12 6 	
4 16 6
12 12 4
```

## Textures
Textures resources can be found under resources/xpm, file type as xpm. After adding new resources, update the source path to load_texture.c. There's some textures ready to load.
```
1: defualt wall
2: floor
3: ceiling

3~4: other wall texture
5~8: Hitler wall texture
9~12: Nazi wall texture
13~16: another wall texture
17~18: sky-like wall texture

19~29: object texture
30~33: teature object texture
34~36: boss texture
```

## ray-casting
Raycasting is a rendering technique to create a 3D perspective in a 2D map. Back when computers were slower it wasn't possible to run real 3D engines in realtime, and raycasting was the first solution. The basic idea of raycasting is, if the window size is 200 * 100(width * height), there's 200 vertical stripes of the screen, each with 1 pixel width. We shoot a ray from player's location to each stripes, if it hit a wall, calculate the distance of this hit point to the player, and use this distance to calculate how high this wall has to be drawn on the screen.<br>
<img src="https://github.com/pootitan/Wolf-3d/blob/master/img/ray.png"><br>

The image of ray casting without any texture looks like:<br>
<img src="https://github.com/pootitan/Wolf-3d/blob/master/img/simple_scene.png"><br>

## Mazes
To illustrate this simple, yet powerful, ray casting game engine, I made a stage of maze with some surprise hidden in it.<br>
<br>
When you first land on maze...<br>
<img src="https://github.com/pootitan/Wolf-3d/blob/master/img/landing.png"><br>
Pick up some weapon to protect yourself<br>
<img src="https://github.com/pootitan/Wolf-3d/blob/master/img/weapon.png"><br>
Some food can make you feel better...<br>
<img src="https://github.com/pootitan/Wolf-3d/blob/master/img/meal.png"><br>
This place is creepy...better find a way out fast...<br>
<img src="https://github.com/pootitan/Wolf-3d/blob/master/img/cage.png"><br>
Danger ahead...<br>
<img src="https://github.com/pootitan/Wolf-3d/blob/master/img/Achtung.png"><br>
Boss fight!!!<br>
<img src="https://github.com/pootitan/Wolf-3d/blob/master/img/fuhrers.png">

## Thanks!
<img src="https://github.com/pootitan/Wolf-3d/blob/master/img/thanks.png" height="50%" width="50%">
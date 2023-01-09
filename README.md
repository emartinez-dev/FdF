# FdF

## Project description

The representation in 3D of a landscape is a critical aspect of modern mapping.
For example, in these times of spatial exploration, to have a 3D representation of Mars is a prerequisite condition to its conquest.
As another example, comparing various 3D representations of an area of high tectonic activity will allow you to better understand these phenomena and their evolution,
and as a result, be better prepared. It’s your turn today to modelize some 3D magnificent landscapes, imaginary or not.

This project is about creating a simple wireframe model representation of a 3D landscape by linking various points (x, y, z) thanks to line segments (edges).

## Map characteristics

The coordinates of the landscape are stored in a .fdf file passed as a parameter to the program. You can find a bunch of .fdf maps at the `test_maps` folder.

Here is an example:

```
$>cat 42.fdf

0 0 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0 0 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0 0 10 10 0  0  10 10 0  0  0  10 10 10 10 10 0  0  0
0 0 10 10 0  0  10 10 0  0  0  0  0  0  0  10 10 0  0
0 0 10 10 0  0  10 10 0  0  0  0  0  0  0  10 10 0  0
0 0 10 10 10 10 10 10 0  0  0  0  10 10 10 10 0  0  0
0 0 0  10 10 10 10 10 0  0  0  10 10 0  0  0  0  0  0
0 0 0  0  0  0  10 10 0  0  0  10 10 0  0  0  0  0  0
0 0 0  0  0  0  10 10 0  0  0  10 10 10 10 10 10 0  0
0 0 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0 0 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0

```
## Output examples

![42 map file](https://i.imgur.com/ROFoDmD.png "42 map")
![Terrain with water and land](https://i.imgur.com/N7a6ri2.png "Terrain with water and land")

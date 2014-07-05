The Game of Life is a cellular automaton devised by the British Mathematician John Horton Conway in 1970. It proceeds from generation to generation on a grid of "cells" that are born, live, and die according to a small set of rules.

Learning Goals:
Learn how the event loop that underlies all GUI programs works.
Write a simple GUI toolkit to better understand how Java Swing, .Net, and related toolkits work.

Enhancements:
file-selection: user can select any *.txt file in the patterns folder. If it select other type of file, the program will exit. The CurrentModelFile label will display the file name. click the “next file” button to change a file, and click the “SET” button to choose that file with the starting configuration for the animation. User can change file anytime.

editor: allows users to specify the initial generation using the mouse anytime. If user click the life graphics while animation is running, animation will stop, and user can directly create their special generation. It can also work at the very beginning. Click “save” button to save the result in “savefile.txt” in patterns folder. 
However, there is a bug with the editor. The first row of the generation must contain a alive cell. If there isn’t, the output file will be wrong. 

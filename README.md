multimovieplayer
================

plays multi movs in sync over UDP: practice for openfameworks and C++ (formerly java program used on exhibition around 2004)
Using quicktime player in openframeworks ofvideoplayer

This program need ofxNetwork and rewrote ofxBezierWarp

control movie remotely with companion program or keyboard

with ofxBezierWarp the movie files can be warped.

this program composite 9 movies(or jpegs or supported files of quicktime)

each movie can use different OF_BLENDMODE over movie below


bin/
program multimovieplayer.exe
presets files for bezierwarp
presets.bin, presets1.bin ~ presets9.bin

bin/data
movies and multimovie.txt which defines up to 9 movies composition and mesh grid

example multimovieplayer.txt

" grid moviename OF_BLENDMODE
"	OF_BLENDMODE_DISABLED = 0,
"	OF_BLENDMODE_ALPHA 	  = 1,
"	OF_BLENDMODE_ADD 	  = 2,
"	OF_BLENDMODE_SUBTRACT = 3,
"	OF_BLENDMODE_MULTIPLY = 4,
"	OF_BLENDMODE_SCREEN   = 5

20,m1.mov,1,mov controllable
20,u.jpg,2
10,d.jpg,1
10,l.jpg,4
10,r.jpg,4

program reads csv file and ignore 2 or less field line.
so you can use as comment as above

grid,moviename(or jpeg), OF_BLENDMODE
grid is number of mesh for bezierwarp
1~29
only 1st line movie can controllable by keyboard or playctl program

in this example other 4 movies are mask jpg (up, down, left, right)


:multimovieplayer interaction

bezierwarp command
'1'~'9' select current movie and you can edit warp with anchors
'0' show presentation (no anchors)
'm' show status
'M' hide status
BS' show/hide current movie
'a' edit anchor only or normal mode(now not so much needed)
'b' background black (default)
'B' background white
'd' read default mesh
'p' last saved anchor position (affect only current selected movie)
's' save position of the anchors
'S' save all anchors of all movies(1~9)
'r' reload from presetfile(affect only current selected movie) 


movie control command
'f' fullscreen
'F' window mode
'g' pause
'G' unpause
if multiple program is running on 1 machine or more machines
pause stops same frame position of movie
some movie cannot stop at frame but motion jpeg is ok.
"cusor key down" go to start position ( again all programs connected)
"cusor key up" go to end position ( again all programs connected)


 

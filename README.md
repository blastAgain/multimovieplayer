multimovieplayer
================

plays multi movs in sync over UDP: practice for openfameworks and C++ (formerly java program used on exhibition around 2004)<br>
Using quicktime player in openframeworks ofvideoplayer<br>
<br>
This program need ofxNetwork and rewrote ofxBezierWarp<br>
<br>
control movie remotely with companion program or keyboard<br>
<br>
with ofxBezierWarp the movie files can be warped.<br>
<br>
this program composite 9 movies(or jpegs or supported files of quicktime)<br>
<br>
each movie can use different OF_BLENDMODE over movie below<br>
<br>
bin/<br>
program multimovieplayer.exe<br>
presets files for bezierwarp<br>
presets.bin, presets1.bin ~ presets9.bin<br>
<br>
bin/data<br>
movies and multimovie.txt which defines up to 9 movies composition and mesh grid<br>
<br>
example multimovieplayer.txt<br>
<br>
" grid moviename OF_BLENDMODE<br><br>
"	OF_BLENDMODE_DISABLED = 0,<br>
"	OF_BLENDMODE_ALPHA 	  = 1,<br>
"	OF_BLENDMODE_ADD 	  = 2,<br>
"	OF_BLENDMODE_SUBTRACT = 3,<br>
"	OF_BLENDMODE_MULTIPLY = 4,<br>
"	OF_BLENDMODE_SCREEN   = 5<br>
<br>
20,m1.mov,1,mov controllable<br>
20,u.jpg,2<br>
10,d.jpg,1<br>
10,l.jpg,4<br>
10,r.jpg,4<br>
<br>
program reads csv file and ignore 2 or less field line.<br>
so you can use as comment as above<br>
<br>
grid,moviename(or jpeg), OF_BLENDMODE<br>
grid is number of mesh for bezierwarp<br>
1~29<br>
only 1st line movie can controllable by keyboard or playctl program<br>
<br>
in this example other 4 movies are mask jpg (up, down, left, right)<br>
<br>
<br>
:multimovieplayer interaction<br>
<br>
bezierwarp command<br>
'1'~'9' select current movie and you can edit warp with anchors<br>
'0' show presentation (no anchors)<br>
'm' show status<br>
'M' hide status<br>
BS' show/hide current movie<br>
'a' edit anchor only or normal mode(now not so much needed)<br>
'b' background black (default)<br>
'B' background white<br>
'd' read default mesh<br>
'p' last saved anchor position (affect only current selected movie)<br>
's' save position of the anchors<br>
'S' save all anchors of all movies(1~9)<br>
'r' reload from presetfile(affect only current selected movie) <br>
<br>
<br>
movie control command<br>
'f' fullscreen<br>
'F' window mode<br>
'g' pause<br>
'G' unpause<br>
if multiple program is running on 1 machine or more machines<br>
pause stops same frame position of movie<br>
some movie cannot stop at frame but motion jpeg is ok.<br>
"cusor key down" go to start position ( again all programs connected)<br>
"cusor key up" go to end position ( again all programs connected)<br>


 

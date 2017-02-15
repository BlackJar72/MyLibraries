# Some classes good for games and game engines

This mostly contains vector (as in the math kind you would use in physics 
or engineering) and matrix classes, especially those used in 3D rendering. 

It also contains some random number generators, including a basic xorshift 
(for its speed), an enhanced 64 bit xorshift, and my own "spatial random" 
class that allows random numbers for a location and a pseudo-iteration 
(the fourth dimension, time).  The latter was created for use in procedural 
content generation so that the results for neigboring areas can be aquired 
easily without generating them, etc.; I suspect it might also have other 
uses, such as tiling texture variants in a way that avoids obvious patterns.
The SpacialRandom algorith has been tested statistically and does decently 
while running about as fast as a linear congruential generator or slightly 
faster, but it is by no means supposed to create really "good" output (i.e., 
it would NOT be appropriate for research or security purposes).

I have considered including other things, but: Fast square root (as was used 
in quake) is obsolete and modern hardware can produce better results faster. 
A fast trig library would consist mostly of large look-up tables and would 
thus be its own library rather than clutter this with huge amount of data 
(this is done in the Java world at least, getting results about 5 to 10 times 
faster than calculating appropriations with java.math).

# This is still incomplete / WIP

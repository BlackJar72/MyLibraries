These is a simple string tokenizing system I developed for reading config files 
in order improve on some short comings of Java's string tokenizer class (especially, 
its inability to account for quotations).  More to the point, it was part of 
Doomlike Dungeons, but I'm not porting it to C++, with some minor improvements, 
for more general use in other projects.

# This may or may not be complete

I might added a more advance StringLexer, capable of reading into a tree structure 
and using context sensitive tokenization.  Or I might make that its own library. 
Or I might not, if other things seem more interesting and or useful at the time. 
For reading basic config files this (which is what this was designed for) it 
can actually go a long way.  However, the current version seem to work fine.

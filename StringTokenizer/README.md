This is a simple string tokenizing system I developed for reading config files 
in order improve on some short comings of Java's string tokenizer class (especially, 
its inability to account for quotations).  More to the point, it was part of 
Doomlike Dungeons, but I'm porting it to C++, with some minor improvements, 
for more general use in other projects.

This is probably not the best way to do this, actually I'm convinced not that its 
just plain bad -- this is not how to do this in C++. It would make far more since 
to strip the class down to a small struct with just core data (i.e., the tokens 
and next counter) or even a instance of std::vector. Instead of all these class 
variables (mostly) kept "private" there should just be some functions, hidden 
in the implementation file -- or even re-write this as a C library.



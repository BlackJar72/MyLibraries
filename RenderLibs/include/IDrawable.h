#ifndef IDRAWABLE_H
#define IDRAWABLE_H

/*
// A pure virtual interface for things that can be drawn;
// at this point I am not sure if this the best way or if
// I should have this -- does this belong here or should
// it be left in Java.
//
// This may not stick around or be used.  I'm also not sure
// if it should take a paramers (e.g., location), etc., or
// what functions it should be used for.
*/
class IDrawable
{
    public:
        virtual void draw() const = 0;
        virtual ~IDrawable();
    protected:
        IDrawable();
};

#endif // IDRAWABLE_H

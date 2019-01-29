#ifndef SIZE_H
#define SIZE_H

struct Size
{
	Size(unsigned width, unsigned height): Width(width), Height(height) {};
	unsigned Width;
	unsigned Height;
};

#endif

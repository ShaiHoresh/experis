#ifndef __UNCOPYABLE__
#define __UNCOPYABLE__

class uncopyable
{
protected:
	uncopyable() {}
	~uncopyable() {}
private:
	uncopyable(const uncopyable&);
	const uncopyable& operator=(const uncopyable&);
};

#endif // !__UNCOPYABLE__
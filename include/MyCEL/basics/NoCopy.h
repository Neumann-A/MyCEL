#pragma once

#ifndef _NOCOPY_H_
#define _NOCOPY_H_
// from http://jrdodds.blogs.com/blog/2004/04/disallowing_cop.html

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;   \
  void operator=(const TypeName&) = delete;

class NoCopy
{
public:
protected:
	NoCopy() {};
	virtual ~NoCopy() {};
private:
	DISALLOW_COPY_AND_ASSIGN(NoCopy)
};

#endif //_NOCOPY_H_
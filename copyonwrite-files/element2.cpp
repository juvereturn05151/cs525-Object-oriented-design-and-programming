#include "element2.h"
using namespace DigiPen;

int Element2::aliveAmount = 0;
int Element2::totalAmount = 0;

Element2::Element2(int _val) : p_val(new int(_val)) 
{
	IncrementElement();	
}

Element2::Element2(const Element2& rhs) 
	: AbstractElement(), p_val(new int(*rhs.p_val)) 
{ }

Element2& DigiPen::Element2::operator=(const Element2& rhs) 
{
  if (this!=&rhs) 
  {
	delete p_val;
	p_val = new int(*rhs.p_val);
  } 

  return *this;
}

int Element2::Get() const
{
	return *p_val;
}

void Element2::Print() const
{ 
  std::cout << "(" << *p_val << ") "; 
}

void Element2::Set(int new_val) 
{ 
	*p_val = new_val; 
}

AbstractElement* Element2::Clone(int val) const
{ 
  return new Element2(val); 
}

void Element2::IncrementElement()
{ 
  aliveAmount++; 
  totalAmount++;
}

void Element2::DecrementElement()
{ 
  aliveAmount--;
}

Element2::~Element2() 
{
	DecrementElement();
	delete p_val;
}

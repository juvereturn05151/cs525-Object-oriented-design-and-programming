#include "element1.h"
using namespace DigiPen;

Element1::Element1(int _val) : val(_val) { }

int Element1::Get() const { return val; }

void Element1::Set(int new_val) { val=new_val; }

void Element1::Print() const
{ 
  std::cout << "[" << Get() << "] "; 
}

AbstractElement* Element1::Clone(int val) const
{ 
  return new Element1(val); 
}
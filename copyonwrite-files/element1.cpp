#include "element1.h"
using namespace DigiPen;

int Element1::aliveAmount = 0;
int Element1::totalAmount = 0;

Element1::Element1(int _val) : val(_val) 
{
  IncrementElement();	
}

int Element1::GetId() const
{
  return 1;
}

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

void Element1::IncrementElement()
{ 
  aliveAmount++; 
  totalAmount++;
}

void Element1::DecrementElement()
{ 
  aliveAmount--;
}

Element1::~Element1()
{
	DecrementElement();
}
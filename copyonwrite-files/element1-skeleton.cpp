#include "element1.h"

DigiPen::Element1::Element1(int _val) : val(_val) { }

int DigiPen::Element1::Get() const { return val; }

void DigiPen::Element1::Set(int new_val) { val=new_val; }

void DigiPen::Element1::Print() const { 
  std::cout << "[" << Get() << "] "; 
}


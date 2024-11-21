#include "element2.h"

DigiPen::Element2::Element2(int _val) : p_val(new int(_val)) { }

DigiPen::Element2::Element2(const Element2& rhs) 
	: AbstractElement(), p_val(new int(*rhs.p_val)) 
{ }

DigiPen::Element2& DigiPen::Element2::operator=(const Element2& rhs) {
  if (this!=&rhs) {
		delete p_val;
		p_val = new int(*rhs.p_val);
	} 
  return *this;
}

int DigiPen::Element2::Get() const {
	return *p_val;
}

void DigiPen::Element2::Print() const { 
  std::cout << "(" << *p_val << ") "; 
}

void DigiPen::Element2::Set(int new_val) { 
	*p_val = new_val; 
}

DigiPen::Element2::~Element2() {
	delete p_val;
}

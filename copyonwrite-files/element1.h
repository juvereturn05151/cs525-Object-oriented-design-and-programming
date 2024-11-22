#ifndef ELEMENT1_H
#define ELEMENT1_H
#include <iostream>
#include "abstract-element.h"

namespace DigiPen 
{
  class Element1 : public AbstractElement
  {
    public:
      Element1(int _val);
      int Get() const;
      void Set(int new_val); 
      void Print() const;
      AbstractElement* Clone(int val) const;
    private:
      int val;
  };
}
#endif

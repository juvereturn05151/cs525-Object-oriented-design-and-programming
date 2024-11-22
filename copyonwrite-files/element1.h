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
      int Get() const override;
      void Set(int new_val) override; 
      void Print() const override;
      AbstractElement* Clone(int val) const override;
    private:
      int val;
  };
}
#endif

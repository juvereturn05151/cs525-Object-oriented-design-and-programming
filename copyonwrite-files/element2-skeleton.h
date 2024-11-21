#ifndef ELEMENT2_H
#define ELEMENT2_H
#include <iostream>
#include "abstract-element.h"

namespace DigiPen {
  class Element2 {
    public:
      Element2(int _val);
      Element2(const Element2& rhs);
      Element2& operator=(const Element2& rhs);
      int Get() const;
      void Set(int new_val);
      void Print() const;
      ~Element2();
    private:
      int * p_val;
  };
}
#endif

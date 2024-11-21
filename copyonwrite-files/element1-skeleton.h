#ifndef ELEMENT1_H
#define ELEMENT1_H
#include <iostream>

namespace DigiPen {
  class Element1 {
    public:
      Element1(int _val);
      int Get() const;
      void Set(int new_val);
      void Print() const;
    private:
      int val;
  };
}
#endif

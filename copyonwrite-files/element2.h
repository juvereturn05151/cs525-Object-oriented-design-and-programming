#ifndef ELEMENT2_H
#define ELEMENT2_H
#include <iostream>
#include "abstract-element.h"

namespace DigiPen 
{
  class Element2 : public AbstractElement
  {
    public:
      // static functions
      static int GetAlive() {return aliveAmount;}
      static int GetTotal() {return totalAmount;}

      Element2(int _val);
      Element2(const Element2& rhs);
      Element2& operator=(const Element2& rhs);
      int GetId() const;
      int Get() const;
      void Set(int new_val);
      void Print() const;
      AbstractElement* Clone(int val) const;
      ~Element2();
    protected:
      void IncrementElement();
      void DecrementElement();
    
    private:
      // static variables
      static int aliveAmount;
      static int totalAmount;

      int * p_val;
  };
}
#endif

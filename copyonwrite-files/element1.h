#ifndef ELEMENT1_H
#define ELEMENT1_H
#include <iostream>
#include "abstract-element.h"

namespace DigiPen 
{
  class Element1 : public AbstractElement
  {
    public:
      // static functions
      static int GetAlive() {return aliveAmount;}
      static int GetTotal() {return totalAmount;}
      Element1(int _val);
      int GetId() const;
      int Get() const;
      void Set(int new_val); 
      void Print() const;
      AbstractElement* Clone(int val) const;
      ~Element1();
    protected:
      void IncrementElement();
      void DecrementElement();
    
    private:
      int val;
      // static variables
      static int aliveAmount;
      static int totalAmount;
  };
}
#endif

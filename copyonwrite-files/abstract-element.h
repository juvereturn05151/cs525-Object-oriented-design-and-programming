/*
Author: Ju-ve Chankasemporn
E-mail: juvereturn@gmail.com
Brief:
An abstract used for deriving Element1 and Element2
*/
#ifndef AbstractElement_H
#define AbstractElement_H
namespace DigiPen 
{
    class AbstractElement 
    {
    public:
        // virtual destructor to ensure proper cleanup of derived classes
        virtual ~AbstractElement() {}

        // pure virtual methods to be implemented by derived classes
        virtual int Get() const = 0;
        virtual void Set(int new_val) = 0;
        virtual void Print() const = 0;
        
        // clone function for deep copy (Prototype pattern)
        virtual AbstractElement* Clone(int val) const = 0;
    protected:
        // reference counting helper methods
        virtual void IncrementElement() = 0;
        virtual void DecrementElement() = 0;
    };
}
#endif
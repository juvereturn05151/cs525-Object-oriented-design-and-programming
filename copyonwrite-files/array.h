/*
Author: Ju-ve Chankasemporn
E-mail: juvereturn@gmail.com
Brief:
Class Array implements a simple array-like data structure.
Objects inside the Array have to be derived from AbstractElement.
*/

#ifndef ARRAY_H
#define ARRAY_H
#include "abstract-element.h"
#include "element-factory.h"
#include <iostream>

namespace DigiPen 
{
	class Array 
    {
		public:
			Array(int * array, unsigned int _size, const ElementFactory* _pElementFactory);
			Array(const Array& rhs);
			Array& operator=(const Array& other);
			~Array();
			
			int Get(unsigned int pos) const;
			void Set(int id, int pos, int value);
			void Print() const;
		private:
			AbstractElement** data;
			unsigned int size;
			ElementFactory const* pElementFactory;

			//Using a pointer for reference counting ensures multiple objects can share and modify the same reference count.
			int* refCount; 

			void DeepCopy(); 
			void DeleteData();
	};
}
#endif
#include "array.h"
using namespace DigiPen;
// if Factory is used cirrectly, there will be no more includes

Array::Array(int * array, unsigned int _size, const ElementFactory* _pElementFactory) 
: data(new AbstractElement*[_size]), size(_size), pElementFactory(_pElementFactory) , refCount(new int(1))
{
	for ( unsigned int i=0; i<size; ++i ) 
	{
		//create Element with id = 1 (that is Element1 )
		data[i] = pElementFactory->MakeElement( 1, array[i] );
	}
}

// Copy constructor 
Array::Array(const Array& other)
 : data(other.data), size(other.size), pElementFactory(other.pElementFactory), refCount(other.refCount) 
{ 
	++(*refCount); 
}

// Assignment operator 
Array& Array::operator=(const Array& other) 
{ 
	//if the array share the same address, we ignore this
	//if not, we have to delete the data(which will decrement 1 ref count)
	if (this != &other) 
	{
		DeleteData(); 
		data = other.data; 
		size = other.size; 
		pElementFactory = other.pElementFactory; 
		refCount = other.refCount; 
		++(*refCount); 
	} 
	
	return *this; 
} 
	
Array::~Array() 
{ 
	DeleteData(); 
}

int Array::Get(unsigned int pos) const
{
	return data[pos]->Get();			
}

void Array::Set( int id, int pos, int value ) 
{ 
	DeepCopy(); // modifying the data - need our own copy
	delete data[pos]; 
	data[pos] = pElementFactory->MakeElement(id,value); // make sure is used 
}

void Array::DeepCopy()
{ 
	// the data is shared, thus if we modify data, than more then
    // 1 object will see the change - something we want to avoid, so we need to
    // "fork" - we need both objects to have their own version of data.
	if (*refCount > 1) 
	{ 
		// decrement here because there will be 1 less shared data
		--(*refCount); 

		// create a new array to hold the copied elements 
		AbstractElement** newData = new AbstractElement*[size];
		for (unsigned int i = 0; i < size; ++i) 
		{ 
			// ensure a deep copy of each element 
			newData[i] = pElementFactory->MakeElement(data[i]->GetId(), data[i]->Get()); 
		} 

		// no need to delete elements here since they are still shared with other instances 
		// update the data pointer and reference count 
		data = newData; 
		// initialize a new reference count for the new data 
		refCount = new int(1); 
	 }
}

void Array::Print() const 
{
	for (unsigned int i=0;i<size;++i) data[i]->Print(); 
	std::cout << std::endl;
}

void Array::DeleteData() 
{ 
	if (--(*refCount) == 0) 
	{ 
		for (unsigned int i = 0; i < size; ++i) 
		{ 
			delete data[i]; 
		} 

		delete[] data; 
		delete refCount; 
	}
}
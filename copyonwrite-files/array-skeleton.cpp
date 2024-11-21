#include "array.h"
// if Factory is used cirrectly, there will be no more includes

DigiPen::Array::Array(int * array, 
		unsigned int _size, 
		const DigiPen::ElementFactory* _pElementFactory
		) 
: data(new AbstractElement*[_size]),
  size(_size),
	pElementFactory(_pElementFactory)
{
	for ( unsigned int i=0; i<size; ++i ) {
		//create Element with id = 1 (that is Element1 )
		data[i] = pElementFactory->MakeElement( 1, array[i] );
	}
}

void DigiPen::Array::Set( int id, int pos, int value ) { 
	DeepCopy(); // modifying the data - need our own copy
	delete data[pos]; 
	data[pos] = pElementFactory->MakeElement(id,value); // make sure is used 
}

void DigiPen::Array::Print() const {
	for (unsigned int i=0;i<size;++i) data[i]->Print(); 
	std::cout << std::endl;
}


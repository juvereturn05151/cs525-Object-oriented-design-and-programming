#include"vector.h";

namespace CS225
{

SparseVector::SparseVector()
{

}

SparseVector::SparseVector( SparseVector const& rhs )
{

}

SparseVector& SparseVector::operator=(SparseVector rhs)
{
  return *this;
}

SparseVector::~SparseVector()
{
  
}

int SparseVector::Get(long pos) const
{
  return 0;
}

void SparseVector::Insert(int val, long pos) 
{
  if (val==0 ) { Delete(pos); return; } //you may change this line
  if (pos>=dimension) 
  {
    dimension=pos+1; // automatically set dimension (it effects   operator<< only)
  }
  // .....................................
 }

void SparseVector::Delete(long pos)
{

}

int& SparseVector::operator[](unsigned int pos)
{
  return pHead->data;
}

int SparseVector::operator[](unsigned int pos) const
{
  return 0;
}

SparseVector SparseVector::operator+(const SparseVector& rhs) const
{

}

SparseVector SparseVector::operator*(const SparseVector& rhs) const
{

}

int SparseVector::operator*(const int rhs) const
{
  return 0;
}

std::ostream& operator<<(std::ostream &out, const SparseVector &v)
{ 
  int i,last_pos= 1; 
  ElementNode* p_e = v.pHead; 
  while (p_e) { 
  for (i=last_pos+1;i<p_e->pos;++i) out << " " << "0"; 
  out << " " << p_e->data; 
  last_pos=p_e->pos; 
  p_e = p_e->next; 
  } 
  for (i=last_pos+1;i<v.dimension;++i) {
  out << " " << "0"; 
  }
 return out; 
}

}
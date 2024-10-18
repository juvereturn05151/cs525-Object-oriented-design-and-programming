#include"vector.h";

namespace CS225
{

SparseVector::SparseVector() : pHead(nullptr), dimension(0)
{

}

SparseVector::SparseVector( SparseVector const& rhs ) : pHead(nullptr), dimension(rhs.dimension) 
{
    ElementNode* current = rhs.pHead;
    while (current) 
    {
        Insert(current->data, current->pos);
        current = current->next;
    }
}

SparseVector& SparseVector::operator=(SparseVector rhs)
{
  return *this;
}

SparseVector::~SparseVector()
{
  ElementNode* current = pHead;
  while (current) 
  {
    ElementNode* toDelete = current;
    current = current->next;
    delete toDelete;
  }
}

int SparseVector::Get(long pos) const
{
  return 0;
}

void SparseVector::Insert(int val, long pos) 
{
    ElementNode* newNode = new ElementNode;
    newNode->data = val;
    newNode->pos = pos;
    newNode->next = nullptr;

    if (!pHead || pos < pHead->pos) 
    {
        newNode->next = pHead;
        pHead = newNode;
    } 
    else 
    {
        ElementNode* current = pHead;
        while (current->next && current->next->pos < pos) 
        {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }
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
  SparseVector sp;
  sp.dimension = rhs.dimension;
  return  sp;
}

SparseVector SparseVector::operator*(const SparseVector& rhs) const
{
  SparseVector sp;
  sp.dimension = rhs.dimension;
  return  sp;
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
#include"vector.h"

namespace CS225
{

SparseVector::SparseVector() : pHead(NULL), dimension(0)
{

}

SparseVector::SparseVector( SparseVector const& rhs ) : pHead(NULL), dimension(rhs.dimension) 
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
  this->dimension = rhs.dimension;
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
  ElementNode* curr = pHead; 

  while (curr != NULL) 
  {
    if (curr->pos == pos)
    {
        return curr->data;  
    }
    curr = curr->next;  
  }

  return 0;
}

void SparseVector::Insert(int val, long pos) 
{
    if (pos >= dimension) 
    {
      dimension = pos + 1;
    }    

    ElementNode* newNode = new ElementNode;
    newNode->data = val;
    newNode->pos = pos;
    newNode->next = NULL;

    if (pHead == NULL || pos < pHead->pos) 
    {
        pHead = newNode;
    } 
    else 
    {
        ElementNode *temp = pHead;
        ElementNode *prev = NULL;

        /*Traverse the list to find the correct position*/
        while (temp && (temp->pos < newNode->pos))
        {
            prev = temp;
            temp = temp->next;
        }


        if (temp && temp->pos == pos)
        {
            temp->data = val;
            delete(newNode);
            return;
        }
        
        /*Insert at the head of the list if needed*/
        if (prev == NULL)
        {
            newNode->next = pHead;
            pHead = newNode;
        }
        else
        {
            prev->next = newNode;
            newNode->next = temp;
        }
    }
 }

void SparseVector::Delete(long pos)
{
  if (pHead && pHead->pos == pos) {
        ElementNode* temp = pHead;
        pHead = pHead->next;
        delete temp;
        return;
    }

    ElementNode* curr = pHead;
    while (curr && curr->next) {
        if (curr->next->pos == pos) {
            ElementNode* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
            return;
        }
        curr = curr->next;
    }
}

ElementProxy SparseVector::operator[](long pos)
{
  return ElementProxy(*this, pos);
}

int SparseVector::operator[](unsigned int pos) const
{
    return Get(pos); 
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
  SparseVector sp;
  sp.dimension = rhs;
  return 0;
}

std::ostream& operator<<(std::ostream &out, const SparseVector &v)
{ 
  int i,last_pos = -1; 
  ElementNode* p_e = v.pHead; 
  // Loop through the linked list and print each element
    while (p_e) {
        // Print zeros for positions not covered by the linked list
        for (i = last_pos + 1; i < p_e->pos; ++i)
        {
            out << " 0";
        }

        // Print the data for the current position
        out << " " << p_e->data;
        
        // Update last_pos to the current position
        last_pos = p_e->pos;

        // Move to the next element in the list
        p_e = p_e->next;
    }

    // Print remaining zeros after the last element in the linked list
    for (i = last_pos + 1; i < v.dimension; ++i) 
    {
        out << " 0";
    }

  return out; 
}

//Element Proxy

ElementProxy::ElementProxy(SparseVector& v, long pos) : v(v), pos(pos) {}

ElementProxy::operator int() const 
{
    return v.Get(pos);
}

ElementProxy& ElementProxy::operator=(int value) 
{
  v.Insert(value, pos);
  return *this; 
}

}
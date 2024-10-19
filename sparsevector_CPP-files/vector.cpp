#include"vector.h"

namespace CS225
{

SparseVector::SparseVector() : pHead(NULL), dimension(0)
{

}

SparseVector::SparseVector( SparseVector const& rhs ) : pHead(NULL), dimension(rhs.dimension) 
{
    if (rhs.pHead != NULL) 
    {
        pHead = new ElementNode();
        pHead->data = rhs.pHead->data;
        pHead->pos = rhs.pHead->pos;
        pHead->next = NULL;
        ElementNode* currentNew = pHead;
        ElementNode* currentOld = rhs.pHead->next;

        while (currentOld != NULL) 
        {
            Insert(currentOld->data, currentOld->pos);
            currentNew = currentNew->next;
            currentOld = currentOld->next;
        }
    }
}

SparseVector& SparseVector::operator=(SparseVector rhs)
{
  if (this != &rhs) 
  {
    // Clear old stuff
    ElementNode* current = this->pHead;
    while (current) 
    {
      ElementNode* toDelete = current;
      current = current->next;
      delete toDelete;
    }
    this->pHead = NULL;

    // Copy from the right hand side
    ElementNode* currentRhs = rhs.pHead;
    while (currentRhs) 
    {
      this->Insert(currentRhs->data, currentRhs->pos);
      currentRhs = currentRhs->next;
    }
        
    this->dimension = rhs.dimension;
  }

  return *this;
}

//Free all modes
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

//ElementProxy will call this on operator int()
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
    if(val == 0)
    {
      Delete(pos);
      return;
    }

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
        newNode->next = pHead;
        pHead = newNode;
    } 
    else 
    {
        ElementNode *temp = pHead;
        ElementNode *prev = NULL;

        //Traverse the list to find the correct position
        while (temp && (temp->pos < newNode->pos))
        {
            prev = temp;
            temp = temp->next;
        }

        //If the position is already existed, just replace the position
        if (temp && temp->pos == pos)
        {
            temp->data = val;
            delete(newNode);
            return;
        }
        
        //Insert at the head of the list if needed
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
  if (pHead && pHead->pos == pos) 
  {
    ElementNode* temp = pHead;
    pHead = pHead->next;
    delete temp;
    return;
  }

  ElementNode* curr = pHead;
  while (curr && curr->next)
  {
    if (curr->next->pos == pos) 
    {
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
  SparseVector result;
  ElementNode* current = this->pHead;
  ElementNode* currentRhs = rhs.pHead;

  while (current) 
  {
    result.Insert(current->data, current->pos);
    current = current->next;
  }

  while (currentRhs) 
  {
    int currentValue = result.Get(currentRhs->pos);
    result.Insert(currentValue + currentRhs->data, currentRhs->pos);
    currentRhs = currentRhs->next;
  }

  if(this->dimension >= rhs.dimension)
  {
    result.dimension = this->dimension;
  }
  else
  {
    result.dimension = rhs.dimension;
  }

  return  result;
}

int SparseVector::operator*(const SparseVector& rhs) const
{
  int sum = 0;
  ElementNode* current = this->pHead;

  while (current) {
    int rhsValue = rhs.Get(current->pos);
    sum += current->data * rhsValue;
    current = current->next;
  }

  return sum;
}

SparseVector SparseVector::operator*(int rhs) const
{
  SparseVector result;
  ElementNode* current = this->pHead;

  while (current)
  {
    result.Insert(current->data * rhs, current->pos);
    current = current->next;
  }

  result.dimension = this->dimension;
  return result;
}

//Friend Functions

std::ostream& operator<<(std::ostream &out, const SparseVector &v)
{ 
  int i,last_pos = -1; 
  ElementNode* p_e = v.pHead; 
  // Loop through the linked list and print each element
  while (p_e)
  {
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

SparseVector operator*(int value, const SparseVector& rhs)
{
  return rhs * value;
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

ElementProxy& ElementProxy::operator=(ElementProxy proxy) 
{
  v.Insert(proxy.v.Get(proxy.pos), pos);
  return *this; 
}

ElementProxy& ElementProxy::operator+=(int value)
{
  v.Insert(v.Get(pos) + value, pos);
  return *this; 
}

ElementProxy& ElementProxy::operator-=(int value)
{
  v.Insert(v.Get(pos) - value, pos);
  return *this; 
}

}
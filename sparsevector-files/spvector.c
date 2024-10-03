#include <stdlib.h>
#include <stdio.h>
#include "spvector.h" 
/* definition of Node is hidden from the client (driver) so that client CANNOT
 * use INTERNALS of the Node.  this is poor-man encapsulations - hiding
 * implementation details.  The main reason for encapsulations -- if I ever
 * decide to change Node struct no client code will break. Example: I decide to
 * change "left" to "Left", all I do is change map.h and map.c, no client code
 * is effected, since clients were FORCED to use getleft(...) function, rather
 * than field name "left".  Also see typedef in map.h
 */
struct ElementNode {
  int    data;
  int    pos;
  struct ElementNode* next;
};

typedef struct ElementNode ElementNode;
typedef struct RowNode RowNode;

/*print functions*/
void printf_elements(ConstElementNode_handle p_e, char const *fmt, int dim) 
{
	int i,last_pos=-1;
	while (p_e) 
    {
		for (i=last_pos+1;i<p_e->pos;++i) 
    { 
      printf(fmt,0); 
    }
		printf(fmt,p_e->data);
		last_pos=p_e->pos;
		p_e = p_e->next;
	}
	for (i=last_pos+1;i<dim;++i) 
    {
         printf(fmt,0); 
    }
}

void print_elements(ConstElementNode_handle p_e)
 {
	while (p_e) 
    {
		printf("%i at pos %i, ",p_e->data,p_e->pos);
		p_e = p_e->next;
	}
}

int insert_element(ElementNode_handle *p_e, int pos, int value)
{
    if(pos < 0)
    {
      perror("invalid position");
      return -1;
    }

    if (value == 0)
    {
        delete_element(p_e, pos);
        return 1;
    }
    
    ElementNode *element_node = (struct ElementNode *) malloc(sizeof(struct ElementNode));
    if (element_node == NULL)
    {
        perror("invalid allocation");
        return -1;
    }

    element_node->data = value;
    element_node->pos = pos;
    element_node->next = NULL;

    if ((*p_e) == NULL)
    {
        /*If list is empty, insert the first node*/
        (*p_e) = element_node;
    }
    else
    {
        ElementNode *temp = (*p_e);
        ElementNode *prev = NULL;

        /*Traverse the list to find the correct position*/
        while (temp && (temp->pos < element_node->pos)) 
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp && temp->pos == pos)
        {
            temp->data = value;
            free(element_node);
            return 0;
        }

        /*Insert at the head of the list if needed*/
        if (prev == NULL)
        {
            element_node->next = (*p_e);
            (*p_e) = element_node;
        }
        else
        {
            prev->next = element_node;
            element_node->next = temp;
        }
    }

    return 0;
}

void delete_element( ElementNode_handle *p_e, int pos)
{
  if(pos < 0)
  {
    perror("invalid position");
    return;
  }

  struct ElementNode *curr = (*p_e);
  struct ElementNode *prev = NULL;
   
  while (curr && curr->pos != pos)
  {
    prev = curr;
    curr = curr->next;
  }
 
  if (curr == NULL)
  {
    return;
  }
    
  if (prev == NULL)
  {
    (*p_e) = (*p_e)->next;
  }
  else
  {
    prev->next = curr->next;
  }

  free(curr);
}

/*
 * get the value at the given position,
 * p_e is the head pointer 
 */
int get( ConstElementNode_handle p_e, int i )
{
  while (p_e && p_e->pos <= i) 
  {
    if(p_e->pos == i)
    {
      return p_e->data;
    }
    p_e = p_e->next;
	}
  return 0;
}

/* 
 * scalar product of 2 lists.
 * */
int scalar_product(ConstElementNode_handle p_e, ConstElementNode_handle p_j)
{
    int value;
    value = 0;
    if(p_e == NULL || p_j == NULL)
    {
        return 0;
    }
    else
    {
      while(p_e && p_j)
      {
        if(p_e->pos < p_j->pos)
        {
          p_e = p_e->next;
        }
        else if(p_e->pos > p_j->pos)
        {
          p_j = p_j->next;
        }
        else if(p_e->pos == p_j->pos)
        {
          value += p_e->data * p_j->data;
          p_e = p_e->next;
          p_j = p_j->next;
        }
      }

      return value;
    }
}

/* 
 * adds 2 lists as vectors, returns a new list */
ElementNode_handle add( ConstElementNode_handle p_e,ConstElementNode_handle p_j)
{
  ElementNode_handle result_node = NULL;

    while(p_e && p_j)
      {
        if(p_e->pos < p_j->pos)
        {
          insert_element(&result_node, p_e->pos, p_e->data);
          p_e = p_e->next;
        }
        else if(p_e->pos > p_j->pos)
        {
          insert_element(&result_node, p_j->pos, p_j->data);
          p_j = p_j->next;
        }
        else if(p_e->pos == p_j->pos)
        {
          insert_element(&result_node, p_e->pos, p_e->data + p_j->data);
          p_e = p_e->next;
          p_j = p_j->next;
        }
      }

    /*Add remaining elements from p_e*/
    while (p_e) 
    {
        insert_element(&result_node, p_e->pos, p_e->data);
        p_e = p_e->next;
    }

    /*Add remaining elements from p_j*/
    while (p_j) 
    {
        insert_element(&result_node, p_j->pos, p_j->data);
        p_j = p_j->next;
    }

  return result_node;
}

void free_elements(ElementNode_handle p_e)
{
    ElementNode *temp;
    while (p_e)
    {
        temp = p_e;
        p_e = p_e->next;
        free(temp);
        temp = NULL;
    }
}
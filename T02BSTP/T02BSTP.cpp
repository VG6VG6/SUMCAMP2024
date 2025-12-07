/* FILE NAME: t02bstp.cpp
 * PROGRAMMER: VG6
 * LAST UPDATE: 19.07.2024
 * PURPOSE: Binary trees.
 */
#include <iostream>
#include <string>


/* Debug memory allocation support */
#ifdef _DEBUG
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h>
#  define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
static struct __Dummy
{
  /* Structure constructor */
  __Dummy( void )
  {
    SetDbgMemHooks();
  } /* End of '__Dummy' constructor */
} __oops;
#endif /* _DEBUG */

#ifdef _DEBUG
#  ifdef _CRTDBG_MAP_ALLOC
#    define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#  endif /* _CRTDBG_MAP_ALLOC */
#endif /* _DEBUG */

 /* Binary tree struct */
struct tree
{ 
  struct node
  {
    double Data; // Nodes data
    node *L;    // Poiner to left node 
    node *R;    // Poiner to right node 

    /* node construtor */
    node( const node &N )
    {
      Data = N.Data;
      L = nullptr;
      R = nullptr;
      if (N.L != nullptr)
        L = new node(*N.L);
      if (N.R != nullptr)
        R = new node(*N.R);
    }
    node( double Num ) : Data(Num)
    {
      R = nullptr;
      L = nullptr;
    }
    /* Node destructor */
    ~node( void )
    {
      if (this->L != nullptr)
        delete this->L;
      if (this->R != nullptr)
        delete this->R;
    }

    /* Search node function.
     * ARGUMENTS:
     *   - node data:
     *       float Data;
     * RETURNS: 
     *   (node *) pointer to node or prev node if NULL.
     */
    node * search( double Data )
    {
      node *tmp = this;
      
      if (tmp->R != nullptr && Data > tmp->Data)
        tmp = tmp->R->search(Data);
      if (tmp->L != nullptr)
        tmp = tmp->L->search(Data);
      

      return tmp;
    } /* End of 'search' function */

    /* Add new node function.
     * ARGUMENTS:
     *   - node data:
     *       float Data;
     * RETURNS: 
     *   (node *) pointer to node or prev node if NULL.
     */
    node * access( float Data )
    {
      node *tmp = this;
      
      
      if (tmp->L != nullptr && tmp->Data > Data)
        tmp = tmp->L->access(Data);
      if (tmp->R != nullptr )
        tmp = tmp->R->access(Data);
      
        return tmp;
    } /* End of 'access' function */

    /* Display node function
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    void display( void )
    {
      static int Level;

      Level++;
      if (this != nullptr)
      {
        if (this->R != nullptr)
          this->R->display();
        for (int i = 1; i < Level; i++)
          std::cout << "   ";
        std::cout << " " << this->Data << std::endl;
        if (this->L != nullptr)
          this->L->display();
      }
      //if (this->L == nullptr && this->R == nullptr)
      Level--;
    } /* End of 'display' function */
  };
  node *Root; /* Pointer to trees root node */

  /* Tree constructors */
  tree ( const tree &T )
  {
    Root = new node(*T.Root);
  }
  tree( float Num )
  {
    Root = new node(Num);
    std::cout << "New tree created" << std::endl;
  }
  tree( void )
  {
    Root = nullptr;
    std::cout << "New tree created" << std::endl;
  }
  /* Tree destructor */
  ~tree( void )
  {
    if (Root != nullptr)
      delete Root;
    Root = nullptr;
  }

  /* Add new element to tree funtion
   * ARGUMENTS: 
   *   - New data:
   *       float Data;
   * RETURNS: None.
   */
  void access( double Data )
  {
    if (Root == nullptr)
    {
      Root = new node(Data);
      return;
    }

    node *newNode = Root->search(Data);

    if (newNode->Data == Data)
      return;
    else
      if (Data > newNode->Data)
        newNode->R = new node(Data);
      else
        newNode->L = new node(Data);
  } /* End of 'access' function */

  /* Dispay tree function 
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  void display( void )
  {
    this->Root->display();
    std::cout << std::endl;
  } /* End of 'display' functoin */
};

/* Main programm function
 * ARGUMENTS: None.
 * RETURNS:
 *   (INT) Finish program code.
 */
int main( void )
{
  tree a;
  a.access(30);
  a.access(47);
  a.display();
  tree b(a);
  b.access(8);
  b.access(35);
  b.display();
} /* End of 'main' function */

/* End of 't02bstp' file */

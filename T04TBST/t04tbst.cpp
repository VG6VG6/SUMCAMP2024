/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : t04tbst.cpp
 * PURPOSE     : Raytracing project.
 *               Main startup module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov.
 * LAST UPDATE : 21.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <iostream>
#include <commondf.h>

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

/* Binary tree class */
template<typename TypeKey, typename TypeData>
  class tree
  {
    private:
      class node
      {
        private:
        TypeKey Key;       // Node key
        TypeData Data;     // Node data
        node *Less, *More; // Pointeers to next nodes.
      public:
          /* Node constructor */
          node( const TypeKey &NewKey, const TypeData &NewData,
                node *L = nullptr, node *M = nullptr ) :
            Key(NewKey), Data(NewData), Less(L), More(M)
          {
          }
          node ( const TypeKey &NewKey ) : Key(NewKey)
          {
            Less = nullptr, More = nullptr;
          }
          /* Node destructor */
          ~node( void )
          {
            if (Less != nullptr)
              delete Less;
            if (More != nullptr)
              delete More;
          }
          TypeData * Get( const TypeKey &NewKey )
          {
            if (Key == NewKey)
              return &Data;
            if (NewKey < Key)
            {
              if (Less == nullptr)
                return nullptr;
              return Less->Get(NewKey);
            }
            if (More == nullptr)
                return nullptr;
            return More->Get(NewKey);
          }
          TypeData * Set( const TypeKey &NewKey, const TypeData &NewData )
          {
            if (Key == NewKey)
            {
              Data = NewData;
              return &Data;
            }

            if (NewKey < Key)
            {
              if (Less == nullptr)
                Less = new node(NewKey, NewData);
              return Less->Set(NewKey, NewData);
            }
            if (More == nullptr)
                More = new node(NewKey, NewData);
            return More->Set(NewKey, NewData);
          }          

          VOID Display( VOID )
          {
            static int Level;

            Level++;
            if (this->More != nullptr)
              this->More->Display();
            std::cout.width(Level * 3);
            std::cout << " ";
            if (this->Data == TypeData{})
              std::cout << " " << "Empty" << std::endl;
            else
              std::cout << " " << this->Data << std::endl;
            if (this->Less != nullptr)
              this->Less->Display();

            Level--;
          }
      } *Root;
  public:
      tree( void ) : Root(nullptr)
      {
      }
      ~tree( void )
      {
        if (Root != nullptr)
          delete Root;
      }
      TypeData * Get( const TypeKey &Key )
      {
        if (Root != nullptr)
          return Root->Get(Key);
        return nullptr;
      }
      TypeData * Set( const TypeKey &Key, const TypeData &NewData )
      {
        if (Root == nullptr)
          Root = new node(Key, NewData);
        return Root->Set(Key, NewData);
      }
      VOID Display( VOID )
      {
        if (Root == nullptr)
          std::cout << "Tree is empty." << std::endl;
        Root->Display();
      }
      
      TypeData & operator[]( const TypeKey &Key )
      {
        
        TypeData *tmp = Root->Get(Key);
        if (tmp == nullptr)
          Root->Set(Key, TypeData{});
        return *Root->Get(Key);
      }
      
      TypeData operator[]( const TypeKey &Key ) const
      {
        if (Root == nullptr)
          return nullptr;
        return Root->Get(Key);
      }
  };

/* Main programm function
 * ARGUMENTS: None.
 * RETURNS:
 *   (INT) Finish program code.
 */
INT main( VOID )
{
  tree<int, int> a;
  a.Set(0, 30);
  a.Set(-1, 30);
  a.Set(-2, 47);
  a.Set(-5, 80);
  a.Set(-6, 80);
  a.Set(-4, 80);
  a.Set(1, 30);
  a.Set(2, 31);
  a.Set(2, 80);
  a.Display();
  tree<int, std::string> b;
  b.Set(0, "hi");
  b.Set(1, "I am 1");
  b.Set(4, "i am 4");
  b.Set(3, "i am 3");
  b.Set(2, "i am 2");
  b.Set(5, "i am 5");
  b.Display();
  tree<std::string, std::string> c;
  c.Set("Vlad", "Vlad");
  c["DK6"];
  c["A"];
  c["B"];
  c["C"];
  c["D"];
  c["DM"];
  c.Set("Anton", "Anton");
  c.Set("VG6", "VG6");
  c.Set("IR6", "IR6");
  c["Vlad"] = c["IR6"];
  c["MM6"] = "123";
  
  std::string abc = c["Vlad"];
  c.Display();
} /* End of 'main' function */

/* End of 't04tbst.cpp' file */
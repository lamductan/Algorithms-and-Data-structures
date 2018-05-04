//A simple example of hashtable
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#define SIZE_KEY       16
#define SIZE_VALUE1    64
#define SIZE_VALUE2    16
#define DEFAULT_TABLESIZE    101
using namespace std;

struct Node
{
   Node(const char* Key1 = "\0", const char* fName = "\0",
         const char *tele ="\0", const double sal = 0.0 )
   {
      strcpy(Key, Key1);
      strcpy(FullName, fName);
      strcpy(Tele_No, tele);
      Salary = sal;
      Tax = 0.005 * Salary;
      next = NULL;
   }
   char Key[SIZE_KEY];
   char FullName[SIZE_VALUE1];
   char Tele_No[SIZE_VALUE2];
   double Salary;
   double Tax;
   Node *next;
};

class Hashtable
{
   private:
      int table_size;
      Node** table;
      int size;
      long hashString(char* Key);
      Node* find(char* Key);
      Node* current_entry;
      int current_index;
   public:
      Hashtable(int T = DEFAULT_TABLESIZE);//constructor
      virtual ~Hashtable();//destructor
      bool put(Node *);
      bool get(Node *);
      bool contains(char* Key);
      bool remove(char* Key);
      void removeAll();
      int getSize();
      void initIterator();
      bool hasNext();
      void getNextKey(char* Key);
      friend void disp(Node *);
};

Hashtable::Hashtable(int T)
{
   size = 0;
   table_size = T;
   table = new Node*[table_size];
   for(int i=0; i<table_size; i++)
   {
      table[i] = NULL;
   }
}

Hashtable::~Hashtable()
{
   removeAll();
   delete[] table;
}

void disp(Node *N1)
{
 cout << "\nKey:      " << N1->Key << "\nFullName: "
      << N1->FullName <<"\nTele.:    " << N1->Tele_No << "\nSalary:   "
      << setprecision(12) << N1->Salary<< "\nTax:      " << N1->Tax << endl;
}

bool Hashtable::put(Node *N)
{//start put
   if(find(N->Key) != NULL)
   {
      return false;
   }
   Node* entry = new Node(N->Key, N->FullName,N->Tele_No, N->Salary);
   int bucket = hashString(N->Key);
   entry->next = table[bucket];
   table[bucket] = entry;
   size++;
   return true;
}//end put


bool Hashtable::get(Node* N)
{//start get
   Node* temp = find(N->Key);
   if(temp == NULL)
   {
      N->FullName[0] = '\0';
      return false;
   }
   else
   {
      strcpy(N->FullName, temp->FullName);
      strcpy(N->Tele_No, temp->Tele_No);
      N->Salary = temp->Salary;
      N->Tax = temp->Tax;
      return true;
   }
}//end get

bool Hashtable::contains(char* Key)
{//start contains
   if(find(Key) == NULL)
   {
      return false;
   }
   else
   {
      return true;
   }
}//end contains


bool Hashtable::remove(char* Key)
{//start remove
   int bucket = hashString(Key);
   Node* temp = table[bucket];
   if(temp == NULL)
   {
      return false;
   }
   else if(strcmp(Key, temp->Key) == 0)
   {
      table[bucket] = temp->next;
      delete temp;
      size--;
      return true;
   }
   else
   {
      Node* temp_next = temp->next;
      while(temp_next != NULL)
      {
         if(strcmp(Key, temp_next->Key) == 0)
         {
            temp->next = temp_next->next;
            delete temp_next;
            size--;
            return true;
         }
         temp = temp->next;
         temp_next = temp_next->next;
      }
   }
   return false;
}//end remove


void Hashtable::removeAll()
{//start removeAll
   for(int i=0; i<table_size; i++)
   {
      Node* temp = table[i];
      while(temp != NULL)
      {
         Node* next = temp->next;
         disp(temp);
         delete temp;
         temp = next;
      }
   }
   size = 0;
}//end removeAll

int Hashtable::getSize()
{
   return size;
}

Node* Hashtable::find(char* Key)
{ //start find
   int bucket = hashString(Key);
   Node* temp = table[bucket];
   while(temp != NULL)
   {
      if(strcmp(Key, temp->Key) == 0)
      {
         return temp;
      }
      temp = temp->next;
   }
   return NULL;
}//end find

long Hashtable::hashString(char* Key)
{//start hashString
   int n = strlen(Key);
   long h = 0;
   for(int i=0; i<n; i++)
   {
      //To get almost fair distributions of Nodes over the array
      h = (h << 3) ^ Key[i];
   }
    return abs(h % table_size );
}//end hashString

void Hashtable::initIterator()
{//start initIterator
   current_entry = NULL;
   current_index = table_size;
   for(int i=0; i<table_size; i++)
   {
      if(table[i] == NULL)
      {
          continue;
      }
      else
      {
         current_entry = table[i];
         current_index = i;
         break;
      }
   }
}//end initIterator

bool Hashtable::hasNext()
{
   if(current_entry == NULL)
   {
      return false;
   }
   else
   {
      return true;
   }
}
void Hashtable::getNextKey(char* Key)
{
   if(current_entry == NULL)
   {
      Key[0] = '\0';
      return;
   }
   strcpy(Key, current_entry->Key);
   if(current_entry->next != NULL)
   {
      current_entry = current_entry->next;
   }
   else
   {
     for(int i=current_index+1; i<table_size; i++)
     {
        if(table[i] == NULL)
        {
           continue;
        }
        current_entry = table[i];
        current_index = i;
        return;
     }
     current_entry = NULL;
     current_index = table_size;
   }
}

void dispAll(Hashtable* hashtable);

int main()
{
   char temp1[SIZE_KEY];
   Hashtable* hashtable = new Hashtable();

   Node N1("389","Mariam","8216734",22123.267);

   if(!hashtable->contains(N1.Key))
   {
      cout << "\nAdding Node:  ";
      disp(&N1);
      hashtable->put(&N1);
   }

   strcpy(N1.Key, "314");
   strcpy(N1.FullName, "Zeki");
   strcpy(N1.Tele_No, "8765623");
   N1.Salary = 98124.567;
   if(!hashtable->contains(N1.Key))
   {
      cout << "\nAdding Node:  ";
      disp(&N1);
      hashtable->put(&N1);
   }

   strcpy(N1.Key, "320");
   strcpy(N1.FullName, "Murad");
   strcpy(N1.Tele_No, "7231144");
   N1.Salary = 19834.575;
   if(!hashtable->contains(N1.Key))
   {
      cout << "\nAdding Node:  ";
      disp(&N1);
      hashtable->put(&N1);
   }

   strcpy(N1.Key, "768");
   strcpy(N1.FullName, "Hassan");
   strcpy(N1.Tele_No, "7689876");
   N1.Salary = 45124.755;
   if(!hashtable->contains(N1.Key))
   {
      cout << "\nAdding Node:  ";
      disp(&N1);
      hashtable->put(&N1);
   }

   strcpy(N1.Key, "756");
   strcpy(N1.FullName, "Ali");
   strcpy(N1.Tele_No, "9874545");
   N1.Salary = 43554.125;
   if(!hashtable->contains(N1.Key))
   {
      cout << "\nAdding Node:  ";
      disp(&N1);
      hashtable->put(&N1);
   }

   dispAll(hashtable);

    strcpy(temp1,"314");
   hashtable->remove(temp1);
   cout << "\n\nAfter removing 314:" << endl;
   dispAll(hashtable);
   cout << "\n\nDestroying hashtable:" << endl;
   delete hashtable;
   return 0;
}

void dispAll(Hashtable *hashtable)
{
        Node N1;
   cout << "\n\nCurrent Nodes in hashtable:" << endl;
   hashtable->initIterator();
   while(hashtable->hasNext())
   {
      hashtable->getNextKey(N1.Key);
      hashtable->get(&N1);
      disp(&N1);
   }
}

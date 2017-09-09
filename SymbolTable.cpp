// SymbolTable.cpp
#include "SymbolTable.h"
#include <string>
//#include <list>
//#include <iostream>
#include <stack>
#include <forward_list>
#include <functional>

using namespace std;


const int bucketSize=19997;
/*
 struct aBucket
 {
 string myID;
 int level;
 int myLineNumber;
 };
 class LinkList
 {
 public:
 
 void addFront(aBucket n);
 void deleteValue(aBucket n);
 bool searchValue(aBucket n);
 LinkList();
 ~LinkList();
 private:
 
 struct Node
 {
 Node * next;
 
 aBucket mybucket;
 };
 
 };
 LinkList::LinkList()
 {
 
 }
 LinkList::~LinkList()
 {
 
 }
 void LinkList::addFront(aBucket n)
 {
 
 }
 void LinkList::deleteValue(aBucket n)
 {
 
 }
 bool LinkList::searchValue(aBucket n)
 {
 return true;
 }
 
 
 */

class HashTableSymbol
{
public:
    //it must be able to "add" when enter scope is called, so define what it means to "push_back" in a hash
    HashTableSymbol();
    ~HashTableSymbol();
    bool addValue(int Line, string ID);
    void deleteValue(string id);
    int searchValue(string id)const; //i guess it searches something based on ID not really by line number, but i mean line number does help with indexing theoretically.
    
    bool isEmpty()const;
    int size()const;
    int hash(string id)const; //hash that shit into a nice int.
    int getLevel(string id,bool &found)const;
    
    //int mids=0;
    //vector<string> mids; //each id index is corresponding to the line number.
    //start popping from new closed paren to most recent closed paren, then from that one's corresponding open paren and up to the newest open paren.
    
    //int maxDiff;
    //snt prevMostRecentLine;
    
    int levelCount;
    //we dont actually keep track of the string id though or need that string ID in there. so when deleting adding searching can actually just remove the concept of the ID. but then again, about collisions, how do i keep track? will there be some different string that maps into the same string? i dont think so, but its not impossible, though its not likely. so maybe i can go along with assumptions.
private:
    struct aBucket
    {
        string myID;
        int level;
        int myLineNumber;
    };
    // vector<list<aBucket>> buckets; //i guess buckets will hold string id which correspond to line numbers?
    //in each bucket, actually, an id will correspond to the "hashing" and repeats of same string id must follow same hashing ok. so i should probably do this as an open and yea bucket for now should be list but later on change to BST if i have time and figure out how to balance it.
    //2. the index of the vector corresponds to their line num it needs to hold a line num too...
    //3. i should figure out a consistent map to the bucket rn. what should the map be?
    
    forward_list<aBucket> buckets[bucketSize]; //or does he want an array of list abuckets
    
    
    
    //at some pt when optimizing, might have a bucket of binary search trees.
    
    int sizeCount;
    
    
    //write own linkedlist struct?
    
    
    //  stack<int> lineOfScope; //each time i push i care of its line number, and pop top. this might eliminate i mean im technically already doing this so i dont need to worry about this condition unless the buckets start becoming an issue.
    
};

///each entry has a unique line number, but not guaranteed unique msg...
//if i hash by line number, how do i check if there are collision and that im handling case of strings well/right

//actually you search by the string id. im assuming there are 20,000 at most unique strings in a sense then.


//when deleting though, i delete by value instead of by key. so im essentailly deleting the value not the key.
HashTableSymbol::HashTableSymbol()
{
    sizeCount=0;
    
    
    
    //mids.push_back("{");
    //mids++; //mids is size 1.
    
    //if buckets were an array, i would just insert all values to 0 default, or -1 or something and henever im inserting into the buckets then stuff happens. oh jk i can just initialize it to a bucket full of unknowns but turn into false, in here. (shit thats already O(n) i think b/c setting step. does that make it worse? or just default them to false in the struct and change it if necessary.
}
HashTableSymbol::~HashTableSymbol()
{
    
}
int HashTableSymbol::getLevel(string id, bool &found)const
{
    
    int index=hash(id);
    found=false;
    for(forward_list<aBucket>::const_iterator q=buckets[index].begin();q!=buckets[index].end();q++)
    {
        if(q->myID==id)
        {
            found=true;
            return q->level; //b.c push front so return first.
        }
    }
    return -1;
    
}
int HashTableSymbol::searchValue(string id) const//gimme the id, and hash it, and pass into this function.
{
    //search must return the "latest" version of it and must contains it too .
    
    //how about it returns a value (line number if found, if not found, it returns -1?
    
    int index=hash(id);
    // int answer=-1;
    for(forward_list<aBucket>::const_iterator q=buckets[index].begin();q!=buckets[index].end();q++)
    {
        if(q->myID==id)
        {
            return  q->myLineNumber; //b.c push front so return first.
        }
    }
    return -1;
}


bool HashTableSymbol::addValue(int Line, string ID) //should make this a bool.
//if you can find the value and before making a new { as a separator, then dont add and return false.
{
    
    //several conditions for inserting. there are going to be times when i can't insert and therefore, can't declare
    //1. in the case of pushing values, when doing the declare, pay close attention to that and make sure the vec is pushing always when addvalue OR search value is called. however, that owuld mean a much bigger vector (technically just need to add value in a search b/c i conduct a search here anyways. sometimes evn two. so its pushing back a whole bunch of duplicates, but its main goal is to also make sure that the line numbers are matching up accordingly.
    /* if(mids==Line)
     {
     mids++;
     }
     
     else
     {
     while(mids!=Line)
     {
     mids++;
     }
     if(mids==Line)
     {
     mids++;
     }
     }
     */
    bool isFound=true;
    //if(searchValue(ID)!=-1)//found duplicates.
    //{
    //check the level before insertion.
    //if that level is less than equal to, GET OUT.
    if(getLevel(ID,isFound)>=levelCount) //getlevel is 1
    {
        if(isFound)
        {
            return false;
        }
    }
    // }
    
    int index=hash(ID);
    aBucket thisBucket;
    thisBucket.myID=ID;
    thisBucket.myLineNumber=Line;
    thisBucket.level=levelCount;
    buckets[index].push_front(thisBucket);
    sizeCount++;
    
    
    return true;
    
    
    //but before declaring or returning true or false here, i must check to see if i reach a { in term of line number.
    
    
}
int HashTableSymbol::size()const
{
    return sizeCount;
}
bool HashTableSymbol::isEmpty()const
{
    return size()==0;
}
int HashTableSymbol::hash(string id) const
{
    //might need to make a special case about whenever my char processor PICKS UP a scope b/c id want all the scope related stuff to hash the same way, evn if there is a ya know, void f() for example before scope.
    //also how does it take line numbers? the right way? does it just ignore them?
    //  if(id=="{")//either empty or { regardless just return 0, were not hashing empty strings.
    //  {
    //      return 0;
    //  }
    
    unsigned long index=0;
    //formula could be size * ascii value of char index its not that hard to write a for loop is it
    std::hash<string> str_hash;
    
    index= str_hash(id);
    
    /*
     for(int c=0;c<id.size();c++)
     {
     index+=id[c];
     index*=16777619;
     }
     */
    
    index=index%bucketSize; //guarantees a map for same value and always stuck inside bucketSize.
    
    
    /*unsigned int h=2166136261U;
     for(int c=0;c<tohash.size();c++)
     {
     h+=tohash[c];
     h*=16777619; //kinda did this tbh first attempt.
     }
     */
    
    
    
    // i mean i can also multiply each value in here by some base value to spread them out even more?
    //if(index<0)
    //  index=index*-1; //ensure a positive index inside bucketSize
    
    //have to reserve bucket spot that corresponds to the { and }
    
    //if(index==0)
    //{
    //don't want to be inserting at index of 0.
    //  index++; //i guess we insert at index =1.
    //}
    return index;
    //so basially, break the string into chars, then after its broken to chars, get its ascii value, and summatoin all that into the value that needs to be hashed. omg genius that makes sense.
}
void HashTableSymbol::deleteValue(string id)
{
    //check what the id i passed in is. if it matches one of the stuff in the vector, then i can check if it falls in range of lineNumber. if that also passes, then delete the value.
    int hashed=hash(id);
    
  
    forward_list<aBucket>::const_iterator q=buckets[hashed].before_begin();
    buckets[hashed].erase_after(q);

  /*  for(forward_list<aBucket>::iterator p = buckets[hashed].begin();p!=buckets[hashed].end();p++)
    {
        
        //check the linked list
        if(p->myID==id)  //ill worry about the level on the interface lvl .
        {
            //delete it.
            //   p--;
            buckets[hashed].erase_after(q);
            sizeCount--;
            return; //don't waste more time after erasing. since u cant have multiple duplicates in same scope.
        }
        q++;
        
    }
   */
}


class SymbolTableImpl
{
public:
    void enterScope();
    bool exitScope();
    bool declare(string id, int lineNum); // declare that
    int find(string id) const;
private:
    
    struct cont
    {
        string id;
        int level;
    };
    stack <cont> myIds;    //litearlly keep track of all the IDS of interest.
    HashTableSymbol myHashTable;
};
void SymbolTableImpl::enterScope()  // have to push kinda like a place holder.
{
    myHashTable.levelCount++;
}

bool SymbolTableImpl::exitScope()  //  pop until you hit that place holder or basically, delete a whole bunch.
{
    int c=myHashTable.levelCount; //nah c will be equal to the level.
    //int count=myIds.size()-1;   //myIds is technically a stack..
    
    if(c==0)
    {
        return false;
    }
    
    while(!myHashTable.isEmpty()&&myIds.top().level==c) //you have to pop all the values whose line numbers are above and not equal to the bracket. so myhashtable line # for the { is some value.
    {
        myHashTable.deleteValue(myIds.top().id);
        myIds.pop();
    }
    //    levelCount--;
    myHashTable.levelCount--;
    // myHashTable.deleteValue("0"); //which should correspond to the { line number.
    if(myHashTable.isEmpty())
    {
        return false;
    }
    return true;
}

bool SymbolTableImpl::declare(string id, int lineNum) //declare must do a search and then try to insert a value.
{
    if(myHashTable.addValue(lineNum,id))
    {
        //set the thing into ids vector
        cont val;
        val.id=id;
        val.level=myHashTable.levelCount; //so starts of at level 0.
        myIds.push(val);
        return true;
    }//inserts id into bucket at lineNum
    return false;
}

int SymbolTableImpl::find(string id) const  //find must just do a search.
{
    return(myHashTable.searchValue(id)); //also, 2 searches? really
}

//*********** SymbolTable functions **************

// For the most part, these functions simply delegate to SymbolTableImpl's
// functions.

SymbolTable::SymbolTable()
{
    m_impl = new SymbolTableImpl;
}

SymbolTable::~SymbolTable()
{
    delete m_impl;
}

void SymbolTable::enterScope()
{
    m_impl->enterScope();
}

bool SymbolTable::exitScope()
{
    return m_impl->exitScope();
}

bool SymbolTable::declare(string id, int lineNum)
{
    return m_impl->declare(id, lineNum);
}

int SymbolTable::find(string id) const
{
    return m_impl->find(id);
}

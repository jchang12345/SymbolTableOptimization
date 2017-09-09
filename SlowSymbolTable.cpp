//SLOW VERSION OF SYMBOL BASICALLY UNMODIFIED. TURN THIS GUY ON WHEN TESTING ONE VS THE OTHER...
/*

#include "SymbolTable.h"
#include <string>
#include <vector>
using namespace std;

// This class does the real work of the implementation.

class SymbolTableImpl
{
public:
    void enterScope();
    bool exitScope();
    bool declare(string id, int lineNum);
    int find(string id) const;
private:
    vector<string> m_ids;
    vector<int> m_lines;
};

void SymbolTableImpl::enterScope()
{
    // Extend the id vector with an empty string that
    // serves as a scope entry marker.
    
    m_ids.push_back("");
    m_lines.push_back(0);
}

bool SymbolTableImpl::exitScope()               //tbh idk match their impl
{
    // Remove ids back to the last scope entry.
    
    while (!m_ids.empty() &&  m_ids.back() != "")
    {
        m_ids.pop_back();
        m_lines.pop_back();
    }
    if (m_ids.empty())
        return false;
    
    // Remove the scope entry marker itself.
    
    m_ids.pop_back();
    m_lines.pop_back();
    return true;
}

bool SymbolTableImpl::declare(string id, int lineNum) //this can be optimized.
{
    if (id.empty())
        return false;
    
    // Check for another declaration in the same scope.
    // Return if found, break out if encounter the scope
    // entry marker.
    
    size_t k = m_ids.size();
    while (k > 0)
    {
        k--;
        if (m_ids[k].empty())
            break;
        if (m_ids[k] == id)
            return false;
    }
    
    // Save the declaration
    
    m_ids.push_back(id);
    m_lines.push_back(lineNum);
    return true;
}

int SymbolTableImpl::find(string id) const    //this can be optimized.
{
    if (id.empty())
        return -1;
    
    // Search back for the most recent declaration still
    // available.
    
    size_t k = m_ids.size();
    while (k > 0)
    {
        k--;
        if (m_ids[k] == id)
            return m_lines[k];
    }
    return -1;
}

//  c*********** SymbolTable functions **************

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
*/

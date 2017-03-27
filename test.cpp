/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/04/2016 12:31:12 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "MemoryPool.h"
#include <vector>

int main()
{
    vector<int*> v;
    MemPool<int> mp;
    int i;
    int* tmp;
    for( i = 0; i < 100; i++)
    {
        tmp = mp.New();
        cout << "creat : " << tmp << endl;
        v.push_back(tmp);
    }
    cout << "===============================================" << endl;
    for(i = 0; i < 50; i++)
    {
        tmp = v.back();
        cout << "destroy : " << tmp << endl;
        mp.Delete(tmp);
        v.pop_back();
    }
    cout << "===============================================" << endl;
    for(i = 0; i < 300; i++)
    {
        cout << "CREAT SUCCESSFUL" << endl;
        tmp = mp.New();
        cout << "creat : " << tmp << endl;
        v.push_back(tmp);
    }
    cout << "===============================================" << endl;
    cout << v.size() << endl;
    return 0;
}


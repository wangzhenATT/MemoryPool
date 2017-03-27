/*
 * =====================================================================================
 *
 *       Filename:  MemoryPool.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/03/2016 09:36:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (wangzhen), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
using namespace std;

const size_t MAXNUM = 10000;

template<class T>
class MemPool
{
	struct MemNode
	{
		void* _memPoint;
		MemNode* _next;
		size_t _itemNum;

		MemNode(size_t itemNum): _itemNum(itemNum), _next(NULL)
		{
			_memPoint = malloc(_itemSize * _itemNum);
		}
		~MemNode()
		{		
	        free(_memPoint);
			_next = NULL;
			_memPoint = NULL;
		}
	};
protected:
	size_t _countIn;
	MemNode* _first;
	MemNode* _last;
	size_t _maxNum;			//the max size for one block
    static size_t _itemSize;
	T* _lastDelete;
protected:
	static size_t _GetItemSize()
	{
		return sizeof(T) > sizeof(void*) ? sizeof(T) : sizeof(void*);
	}
    size_t _GetMemSize()
    {
        if(_last->_itemNum * 2 > _maxNum)
            return _maxNum;
        else
            return _last->_itemNum * 2;
    }
public:
	MemPool(size_t initNum = 32, size_t maxNum = MAXNUM): _maxNum(maxNum), _countIn(0), _lastDelete(NULL)
	{
		//_itemSize = _GetItemSize();
		_first = _last = new MemNode(initNum);
	}
	~MemPool()
	{
		MemNode* cur = _first;
		while(cur)
		{
			MemNode* del = cur;
			cur = cur->_next;
			delete del;
		}
		_first = _last = NULL;
		if(_lastDelete)
			cout << "has ever destroy memory and not used" << endl;
		_lastDelete = NULL;
	}
	T* New()
	{
		T* obj = NULL;
		if(_lastDelete)
		{
			obj = _lastDelete;
			_lastDelete = *(T**)(_lastDelete);
			return new(obj)T;
		}
		else
		{
			if(_countIn >= _last->_itemNum)
            {
                MemNode* tmp = new MemNode(_GetMemSize());
                _last->_next = tmp;
                _last = tmp;
                _countIn = 0;
            }
            obj = (T*)((char*)_last->_memPoint + _itemSize*_countIn);
            _countIn++;
            return new(obj)T;
		}
	}
    void Delete(T* del)
    {
       //assert(del);
        if(del == NULL)
            return ;

        *(T**)del = _lastDelete;
        _lastDelete = del;
    }
};
template<class T>
size_t MemPool<T>::_itemSize = MemPool<T>::_GetItemSize();


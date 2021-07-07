#include<iostream>
#include<unordered_map>
#include<list>

using namespace std;

class Node
{
	public :

	string key;
	int value;

	Node(string key,int value)
	{
		this->key = key;
		this->value = value;
	}

};


class LRUCache
{
	public:

	int maxSize;
	list<Node> l;
	unordered_map<string,list<Node>::iterator > m;

	LRUCache(int maxSize)
	{
		this->maxSize = maxSize > 1 ? maxSize : 1;
	}

	void insertKeyValue(string key,int value)
	{
		//  2 cases

		// 1 if key-value is present inside the cache

		if(m.count(key) != 0)
		{
			// replace the old value with new value

			auto it = m[key];
			it->value = value;
		}
		else // if not present inside the cache
		{
			// check if cache is full or not

			// if list size is full remove LRU(least recently used from cache)

			if(l.size() == maxSize)
			{
				Node last = l.back();
				m.erase(last.key);
				l.pop_back();
			}

			Node n(key,value);

			l.push_front(n);

			m[key] = l.begin();
		}
	}

	int* getValue(string key)
	{
		// -------

		if(m.count(key) != 0)
		{
			auto it = m[key];

			int value = it->value;

			l.push_front(*it);
			l.erase(it);
			m[key] = l.begin();

			return &l.begin()->value;
		}

		return NULL;
	}

	string mostRecentKey()
	{
		// ------------

		return l.front().key;
	}

};


int main()
{

	int size;

	cout<<"Enter LRU Size :-";
	cin>>size;

	LRUCache lru(size);

	lru.insertKeyValue("Mango",10);
	lru.insertKeyValue("Banana",20);
	lru.insertKeyValue("Guva",30);

	cout<<"Most Recently Used :-"<<lru.mostRecentKey()<<"\n";

	lru.insertKeyValue("Mango",40);

	cout<<"Most Recently Used :-"<<lru.mostRecentKey()<<"\n";


	lru.insertKeyValue("Apple",40);

	cout<<"Most Recently Used :-"<<lru.mostRecentKey()<<"\n";

	if(lru.getValue("Mango") == NULL)
	{
		cout<<"Mango Not exists\n";
	}

	return 0;
}




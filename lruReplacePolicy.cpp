#include <list>
using namespace std;

class LRU
{

	private:
		int size;
		vector<list<int>> accessList;
		int lastEntry;

	public:
		int hit;
		int miss;


	LRU()
	{}

	LRU(int size, int sets)
	{
		this->size =  size;                
        this->lastEntry =  -1;             
		this->hit =  0;                  
		this->miss =  0;                   
		for(int i = 0; i < sets; i++)
		{
			list<int> temp_l;
			accessList.push_back(temp_l);
		}
	}

	//for FULLY ASSOCIATIVE CACHE.
	int getIndex(int tag, vector<int> &tags, vector<bool> &valid)
	{
		int i;
		
		for(i = 0; i < tags.capacity(); i++)
		{
			if(valid[i] && tags[i] == tag)
			{
				hit++;
				accessList[0].remove(i);
				accessList[0].push_back(i);
				return i;
			}
		}

		miss++;
		if(lastEntry == tags.capacity())
		{
			i = accessList[0].front();
			accessList[0].pop_front();
			accessList[0].push_back(i);
			valid[i] = 1;
			tags[i] = tag;
		}
		else
		{
			lastEntry++;
			i = lastEntry;
			accessList[0].push_back(i);
			valid[i] = 1;
			tags[i] = tag;
		}

		return i;
	}

	//for SET ASSOCIATIVE CACHE.
	int getIndex(int tag, vector<int> &tags, vector<bool> &valid, int set, int ways)
	{
		int i, base;	

		base = set*ways;

		for(i = 0; i < ways; i++)
		{
			if(!valid[i+base])
			{
				break;
			}
			if(valid[i+base] && tags[i+base] == tag)
			{
				hit++;
				accessList[set].remove(i+base);
				accessList[set].push_back(i+base);
				return i;
			}
		}

		i += base;
		miss++;
		
		if(accessList[set].size() == ways)
		{
			i = accessList[set].front();
			accessList[set].pop_front();
			accessList[set].push_back(i);
			valid[i] = 1;
			tags[i] = tag;
		}
		else
		{
			accessList[set].push_back(i);
			valid[i] = 1;
			tags[i] = tag;
		}

		return i;
	}
};

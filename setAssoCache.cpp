#include <fstream>
#include <bits/stdc++.h>
using namespace std;


class SetAssoCache {
public:

	/*
	* @param
	* cacheSize = size of cache(int word units)
	* blockSize = size of cache block (in word units)
	* numOfBlock = number of blocks in cache
	* numOfSets = number of sets for cache
	* offSetBits = number of offset bits in address
	* setBits = number of set bits in address
	* tagBits = number of tag bits in address
	* replacementPolicy = represents replacement policy for cache (1 = FIFO, 2 = LRU)
	* tags = data structure to store tag bits
	* valid = data structure to store valid bits
	* data = data structure to store data
	* fifo = instance of FIFO replacement policy
	* lru = instance of LRU replacement policy
	*/
	int cacheSize;
	int blockSize;
	int ways;
	int numOfBlock;
	int numOfSets;
	int offsetBits;
	int setBits;
	int tagBits;
	int replacementPolicy;
	vector<int> tags;
	vector<bool> valid;
	vector<int> data;

	int hit;
	int miss;

	FIFO fifo;
	PLRU plru;
	RANDOM random;
	LRU lru;
	

	/*
	* @constructor
	* 
	* @param
	* blockSize = represents block size for cache (in word units)
	* cacheSize = represents cache size for cache (in word units)
	* ways = represents number of ways
	* replacement = represnt replacement policy for cache (1 = RANDOM, 2 = FIFO, 3 = LRU and 4 = PLRU)
	*/
	SetAssoCache(int blockSize, int cacheSize, int ways, int replacement) {
		this->cacheSize = cacheSize;					//WRITE YOUR CODE HERE
		this->blockSize = blockSize;					//WRITE YOUR CODE HERE
		this->ways =  ways;								//WRITE YOUR CODE HERE
		this->numOfBlock = cacheSize / blockSize;		//WRITE YOUR CODE HERE
		this->offsetBits = (int)log2(blockSize) + 2;	//WRITE YOUR CODE HERE
		this->numOfSets = numOfBlock / ways;			//WRITE YOUR CODE HERE
		this->setBits = (int)log2(numOfSets);			//WRITE YOUR CODE HERE
		this->tagBits = 16 - setBits - offsetBits;		//WRITE YOUR CODE HERE
		this->tags.reserve(numOfBlock);
		this->valid.reserve(numOfBlock);
		this->data.reserve(numOfBlock);
		this->replacementPolicy = replacement;
		for(int i = 0; i < numOfBlock; i++)
		{
			valid[i] = false;							//WRITE YOUR CODE HERE
		}

		this -> hit = 0;
		this -> miss = 0;


		
		//cout<<offsetBits;

		switch (replacementPolicy)
		{

					case RANDOM_POLICY:

						//WRITE YOUR CODE HERE;
						
						random = RANDOM(ways, numOfSets);

					    break;

					case FIFO_POLICY:

						//WRITE YOUR CODE HERE;

						fifo = FIFO(ways, numOfSets);

					    break;

					case LRU_POLICY:

						//WRITE YOUR CODE HERE;

						lru = LRU(ways, numOfSets);

					    break;

					case PLRU_POLICY:

						//WRITE YOUR CODE HERE; 

						plru = PLRU(ways, numOfSets);

					    break;
				}
	}

	/*
	* @method
	* method to get data from cache given mem address
	* 
	* @param
	* addr = represnets memory address to access data
	*/

	int get(int addr)
	{
		int index, offset, tag, set;		
        //WRITE YOUR CODE HERE

		offset = addr & ((1 << offsetBits) - 1);
		tag = addr >> (setBits + offsetBits);
		set = (addr & (((1 << (setBits + offsetBits)) - 1))) >> offsetBits;

		switch (replacementPolicy)
		{

			case RANDOM_POLICY:

				index = random.getIndex(tag, tags, valid, set, ways);
				this -> hit = random.hit;
				this -> miss = random.miss;

				break;

			case FIFO_POLICY:

				index = fifo.getIndex(tag, tags, valid, set, ways);
				this -> hit = fifo.hit;
				this -> miss = fifo.miss;

				break;
			
			case LRU_POLICY:

				index = lru.getIndex(tag, tags, valid, set, ways);
				this -> hit = lru.hit;
				this -> miss = lru.miss;

				break;

			case PLRU_POLICY:

				index = plru.getIndex(tag, tags, valid, set, ways);
				this -> hit = plru.hit;
				this -> miss = plru.miss;

				break;
		}

		return data[index];
	}

	/*
	* @method
	* method to print valid, tag and data tables
	*/

	void display()
	{
		cout << "VALID tabel" << endl;

		for(int i = 0; i < numOfBlock; i++)
		{
			cout << i << " : " << (valid[i] ? "1" : "0") << endl;
		}
		
		cout << "TAG tabel" << endl;

		stringstream ss;
		for(int i = 0; i < numOfBlock; i++)
		{
			ss.str("");
			ss << hex << tags[i];
			string temp = ss.str();
			cout << i << " : " <<  temp << endl;
		}

		cout << "DATA tabel" << endl;

		for(int i = 0; i < numOfBlock; i++)
		{
			ss.str("");
			ss << hex << data[i];
			string temp = ss.str();
			cout << i << " : " <<  temp << endl;
		}
	}
};
#include <bits/stdc++.h>
using namespace std;

class FullyAssoCache
{
	public:

	/*
	* @param
	* cacheSize = size of cache(int word units)
	* blockSize = size of cache block (in word units)
	* numOfBlock = number of blocks in cache
	* offSetBits = number of offset bits in address
	* tagBits = number of tag bits in address
	* replacementPolicy = represents replacement policy for cache (1 = FIFO, 2 = LRU)
	* tags = data structure to store tag bits
	* data = data structure to store data
	* fifo = instance of FIFO replacement policy
	* lru = instance of LRU replacement policy
	*/
	int cacheSize;
	int blockSize;
	int numOfBlock;
	int offsetBits;
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
	* @param
	* blockSize = represents block size for cache (in word units)
	* cacheSize = represents cache size for cache (in word units)
	* replacement = represnt replacement policy for cache (1 = RANDOM, 2 = FIFO, 3 = LRU and 4 = PLRU)
	*/

	FullyAssoCache(int blockSize, int cacheSize, int replacement) {
		this->cacheSize = cacheSize;					//WRITE YOUR CODE HERE
		this->blockSize = blockSize;					//WRITE YOUR CODE HERE
		this->numOfBlock =  cacheSize / blockSize;		//WRITE YOUR CODE HERE
		this->offsetBits =  (int)log2(blockSize) + 2;	//WRITE YOUR CODE HERE
		this->tagBits =  16 - offsetBits;				//WRITE YOUR CODE HERE
		this->tags.reserve(numOfBlock);
		this->valid.reserve(numOfBlock);
		this->data.reserve(numOfBlock);
		this->replacementPolicy = replacement;
		this -> hit = 0;
		this -> miss = 0;

		for(int i = 0; i < numOfBlock; i++)
		{
			valid[i] =  false;                 //WRITE YOUR CODE HERE	
		}
	
		switch (replacementPolicy){

					case RANDOM_POLICY:

						//WRITE YOUR CODE HERE;

						random = RANDOM(numOfBlock, 1);

					    break;
						  
					case FIFO_POLICY:

						//WRITE YOUR CODE HERE;

						fifo = FIFO(numOfBlock, 1);

						break;
						
					case LRU_POLICY:

						//WRITE YOUR CODE HERE; 

						lru = LRU(numOfBlock, 1);

					    break;

					case PLRU_POLICY:

						//WRITE YOUR CODE HERE; 

						plru = PLRU(numOfBlock, 1);

						break;
				}

	}


	/*
	* @method
	* method to get data from cache given address
	*
	* @param
	* addr = represent memory address
	*/

	int get(int addr) {
		int index, offset, tag;		
        //WRITE YOUR CODE HERE

		offset = addr & ((1 << offsetBits) - 1);
		tag = addr >> offsetBits;

		switch (replacementPolicy)
		{

			case RANDOM_POLICY:

				index = random.getIndex(tag, tags, valid);
				this -> hit = random.hit;
				this -> miss = random.miss;

				break;

			case FIFO_POLICY:

				index = fifo.getIndex(tag, tags, valid);
				this -> hit = fifo.hit;
				this -> miss = fifo.miss;

				break;
			
			case LRU_POLICY:

				index = lru.getIndex(tag, tags, valid);
				this -> hit = lru.hit;
				this -> miss = lru.miss;

				break;

			case PLRU_POLICY:

				index = plru.getIndex(tag, tags, valid);
				this -> hit = plru.hit;
				this -> miss = plru.miss;

				break;
		}

		return data[index];
	}

	/*
	* @method
	* method to display tag, valid and data tables
	*/

	void display()
	{
		
		cout << "TAG table" << endl;

		stringstream ss;
		for(int i = 0; i < numOfBlock; i++)
		{
			ss.str("");
			ss << hex << tags[i];
			string temp = ss.str();
			cout << i << " : " <<  temp << endl;
		}

		cout << "DATA table" << endl;

		for(int i = 0; i < numOfBlock; i++)
		{
			ss.str("");
			ss << hex << data[i];
			string temp = ss.str();
			cout << i << " : " <<  temp << endl;
		}
	}
};
#include <bits/stdc++.h>

using namespace std;

class DirCache {
public:

	/*
	* @param
	* cacheSize = size of cache(int word units)
	* blockSize = size of cache block (in word units)
	* numOfBlock = number of blocks in cache
	* offSetBits = number of offset bits in address
	* indexBits = number of index bits in address
	* tagBits = number of tag bits in address
	* tags = data structure to store tag bits
	* valid = data structure to store valid bits
	* data = data structure to store data
	* hit = represents number of hits
	* miss = represents number of miss
	*/
	int cacheSize;
	int blockSize;
	int numOfBlock;
	int offsetBits;
	int indexBits;
	int tagBits;
	vector<unsigned int> tags;
	vector<bool> valid;
	vector<int> data; 

	int hit;
	int miss;

	/*
	* @construnctor
	* @param
	* blockSize = represents number of blocksize for cache (in word units)
	* cacheSize = represnts number of cache size for cache (in word units)
	*/
	DirCache(int blockSize, int cacheSize) {
		this->cacheSize =  cacheSize;								//WRITE YOUR CODE HERE
		this->blockSize =  blockSize;								//WRITE YOUR CODE HERE
		this->numOfBlock = cacheSize / blockSize; 					//WRITE YOUR CODE HERE
		this->offsetBits = (int)log2(blockSize) + 2; 				//WRITE YOUR CODE HERE
		this->indexBits =  (int)log2(numOfBlock); 					//WRITE YOUR CODE HERE
		this->tagBits =  16 - offsetBits - indexBits;				//WRITE YOUR CODE HERE
		this->tags.reserve(numOfBlock);
		this->valid.reserve(numOfBlock);
		this->data.reserve(numOfBlock);
		for(int i = 0; i < numOfBlock; i++)
		{
			valid[i] = false;										//WRITE YOUR CODE HERE
		}
		//cout<<"index bits = "<<indexBits<<"\n";
		this->hit = 0;												//WRITE YOUR CODE HERE
		this->miss = 0;												//WRITE YOUR CODE HERE
	}


	/*
	* @method
	* method to get data from cache
	*
	* @param
	* addr = represents memory address
	*/
	int get(int addr) {
		
		int index, offset, tag;		
        //WRITE YOUR CODE HERE
		
		offset = addr & ((1 << offsetBits) - 1);
		tag = addr >> (indexBits + offsetBits);
		index = addr & (((1 << (indexBits + offsetBits)) - 1) - ((1 << offsetBits) - 1));

		if(valid[index] && tags[index] == tag)
		{
			hit++;
		}

		else
		{
			miss++;
			valid[index] = 1;
			tags[index] = tag;
		}

		return data[index];
		
	}

	/*
	* @method
	* method to display valid, tag and data table
	*/
	void display() {
		cout << "VALID table" << endl;

		for(int i = 0; i < numOfBlock; i++) {
			cout << i << " : " << (valid[i] ? "1" : "0") << endl;
		}
		
		cout << "TAG table" << endl;

		stringstream ss;
		for(int i = 0; i < numOfBlock; i++) {
			ss.str("");
			ss << hex << tags[i];
			string temp = ss.str();
			cout << i << " : " <<  temp << endl;
		}

		cout << "DATA table" << endl;

		for(int i = 0; i < numOfBlock; i++) {
			ss.str("");
			ss << hex << data[i];
			string temp = ss.str();
			cout << i << " : " <<  temp << endl;
		}
	}
};
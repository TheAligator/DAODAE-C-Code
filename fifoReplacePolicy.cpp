using namespace std;

class FIFO
{

    private:
        int size;
        vector<queue <int>> q;
        int qSize;
        int count;
        int popCount;

    public:
        int hit;
        int miss;

    FIFO()
    {}

    FIFO(int size, int sets)
    {
        this -> size = size;
        this -> hit = 0;
        this -> miss = 0;
        this -> qSize = 0;
        this -> count = -1;
        this -> popCount = -1;
        for(int i = 0; i < sets; i++)
        {
            queue<int> tempQ;
            q.push_back(tempQ);
        }

    }

    //for Fully Associative Cache.
    int getIndex(int tag, vector<int> &tags, vector<bool> &valid)
    {
        int i = 0;
        //cout<<tags.capacity()<<endl;
        for(i = 0; i < tags.capacity(); i++)
        {
            if(valid[i] && tags[i] == tag)
            {
                hit++;
                return i;
            }
        }

        miss++;
        
        if(count == tags.capacity())
        {
            
            popCount++;
            popCount = popCount % (tags.capacity());
            i = popCount;
            q[0].pop();
            q[0].push(i);
            valid[i] = 1;
            tags[i] = tag;
        
        }

        else
        {

            count++;
            i = count;
            q[0].push(i);
            valid[i] = 1;
            tags[i] = tag;
                
        }

        return i;
    }

    //for SET ASSOCIATIVE CACHE.
    int getIndex(int tag, vector<int> &tags, vector<bool> &valid, int set, int ways)
    {
        int i = 0;
        int nLines = ways * set;

        for(i = 0; i < ways; i++)
        {

            if(valid[nLines + i] && tags[nLines + i] == tag)
            {
                hit++;
                return (nLines + i);
            }
        }

        miss++;

        if(q[set].size() == ways)
        {
            i = q[set].front();
            q[set].pop();
            q[set].push(i);
            valid[i] = 1;
            tags[i] = tag;
        }

        else
        {   
            i = nLines + q[set].size();
            q[set].push(i);
            valid[i] = 1;
            tags[i] = tag;
        }

        return i;
    }
};
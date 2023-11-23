using namespace std;

class RANDOM
{
    private:
        int count;


    public:
        int hit;
        int miss;

    RANDOM()
    {}

    RANDOM(int size, int sets)
    {
        this -> hit = 0;
        this -> miss = 0;
        this -> count = -1;
    }

    //for Fully Associative Cache.
    int getIndex(int tag, vector<int> &tags, vector<bool> &valid)
    {
        int i = 0;

        for(i = 0; i < tags.capacity(); i++)
        {
            if(valid[i] && tags[i] == tag)
            {
                hit++;
                return i;
            }
        }

        miss++;
        //cout<<tags.size() << " " << tags.capacity()<<endl;
        if(count < tags.capacity())
        {
            count++;
            i = count;
            valid[i] = 1;
            //cout<<i<<endl;
            tags[i] = tag;
        }
            
        else
        {   
            i = rand() % tags.capacity();
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

        for(int j = nLines; j < (nLines + ways); j++)
        {
            if(!valid[j])
            {
                valid[j] = 1;
                tags[j] = tag;
                return j;
            }
        }

        i = rand() % ways;
        valid[nLines + i] = 1;
        tags[nLines + i] = tag;
        
        return i;

    }


};
using namespace std;

class PLRU
{
    private:
        int size;
        vector<vector<int>> v;
        vector<int> nBits;
        vector<vector<int>> setBits;

    public:
        int hit;
        int miss;

    PLRU()
    {}

    PLRU(int size, int sets)
    {
        this -> size = size;
        this -> hit = 0;
        this -> miss = 0;

        for(int i = 0; i < sets; i++)
        {
            vector<int> tempV;
            v.push_back(tempV);
            setBits.push_back(tempV);

        }

        this -> nBits.reserve(size - 1);
        for(int k = 0; k < sets; k++)
        {
            setBits[k].reserve(size - 1);
        }
    }

    //for Fully Associative Cache.
    int getIndex(int tag, vector<int> &tags, vector<bool> &valid)
    {
        int i = 0;
        int p = 0;
        int q = tags.capacity();
        int mid = 0;
        int count = 0;
        int lValue = (int)log2(q);
        int node = 0;

        for(i = 0; i < tags.capacity(); i++)
        {
            if(valid[i] && tags[i] == tag)
            {
                hit++;

                //change the bits.
                mid = (p + q) / 2;

                while(count < lValue)
                {
                    if(i < mid)
                    {
                        nBits[node] = 0;
                        q = mid;
                        node = 2 * count + 1;
                    }

                    else
                    {
                        nBits[node] = 1;
                        p = mid;
                        node = 2 * count + 2;
                    }

                    mid = (p + q) / 2;
                    count++;
                }


                return i;
            }
        }

        miss++;
        
        if(v[0].size() == tags.capacity())
        {
            //perform PLRU.
            i = 0;
            count = 0;
            node = 0;

            while(count < lValue)
            {
                if(nBits[node] == 0)
                {
                    nBits[node] = 1;
                    node = 2 * count + 2;
                    i = i | (1 << (lValue - count - 1));

                }

                else
                {
                    nBits[node] = 0;
                    node = 2 * count + 1;
                }

                count++;
            }

            valid[i] = 1;
            tags[i] = tag;            

        }

        else
        {
            
            i = v[0].size();
            v[0].push_back(i);
            valid[i] = 1;
            tags[i] = tag;
            p = 0;
            q = tags.capacity();
            node = 0;
            mid = (p + q) / 2;
            count = 0;

            //change bits.
            while(count < lValue)
                {
                    if(i < mid)
                    {
                        nBits[node] = 0;
                        q = mid;
                        node = 2 * count + 1;
                    }

                    else
                    {
                        nBits[node] = 1;
                        p = mid;
                        node = 2 * count + 2;
                    }

                    mid = (p + q) / 2;
                    count++;
                }
        }

        //cout<<miss<<"\n";

        return i;
    }


    //for SET ASSOCIATIVE CACHE.
    int getIndex(int tag, vector<int> &tags, vector<bool> &valid, int set, int ways)
    {
        int i = 0;
        int nLines = ways * set;
        int p = 0;
        int q = ways;
        int mid = (p + q) / 2;
        int count = 0;
        int lValue = (int)log2(ways);
        int node = 0;
        //cout<<"v[set] = "<< v[set].size()<<"\n";
        //cout<<set<<endl;

        for(i = 0; i < ways; i++)
        {

            if(valid[nLines + i] && tags[nLines + i] == tag)
            {
                hit++;
                //cout<<" "<<set <<"  hit\n";

                while(count < lValue)
                {
                    if(i < mid)
                    {
                        setBits[set][node] = 0;
                        q = mid;
                        node = 2 * count + 1;
                    }

                    else
                    {
                        setBits[set][node] = 1;
                        p = mid;
                        node = 2 * count + 2;
                    }

                    mid = (p + q) / 2;
                    count++;
                }

                return (nLines + i);
            }

        }

        miss++;
        //cout<<nLines + i <<" "<< tags[nLines + i]<<" "<<tag <<"\n";
        if(v[set].size() == ways)
        {
            //perform PLRU.
            i = 0;
            count = 0;
            node = 0;

            while(count < lValue)
            {
                if(setBits[set][node] == 0)
                {
                    setBits[set][node] = 1;
                    node = 2 * count + 2;
                    i = i | (1 << (lValue - count - 1));
                }

                else
                {
                    setBits[set][node] = 0;
                    node = 2 * count + 1;
                }

                count++;
                //cout<<count<<"\n";
            }

            valid[nLines + i] = 1;
            tags[nLines + i] = tag;            

        }

        else
        {
            i = v[set].size();
            v[set].push_back(nLines + i);
            valid[nLines + i] = 1;
            tags[nLines + i] = tag;
            p = 0;
            q = ways;
            node = 0;
            mid = (p + q) / 2;
            count = 0;

            //change bits.
            while(count < lValue)
            {
                if(i < mid)
                {
                    setBits[set][node] = 0;
                    q = mid;
                    node = 2 * count + 1;
                }

                else
                {
                    setBits[set][node] = 1;
                    p = mid;
                    node = 2 * count + 2;
                }

                mid = (p + q) / 2;
                count++;
            }
        }

        return (nLines + i);  
    }

};
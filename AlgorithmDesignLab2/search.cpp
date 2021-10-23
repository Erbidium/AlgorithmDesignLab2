#include "search.h"
#include <vector>
#include <cmath>

int search::sharrMethod(const std::vector<std::pair<int, std::string>>& fields, int key, int& comparisonsNumber)
{
	comparisonsNumber++;
	if(fields.empty())
    {
        return -1;
    }
	int N = fields.size();
	int k=log2(N);
	int pos=pow(2, k);
	int Ki = fields[pos].first;
	int K = key;
	if(K==Ki)
	{
		return pos;
	}
	if(K>Ki)
	{
		int l = floor(log2(N-pow(2, k)+1));
		pos=N+1-pow(2, l);
		return homogeneousBinarySearch(key, fields, pos, l, comparisonsNumber);
	}
	if(K<Ki)
	{
		return homogeneousBinarySearch(key, fields, pos, k, comparisonsNumber);
	}
	 
}

int search::homogeneousBinarySearch(int key, const std::vector<std::pair<int, std::string>>& fields, int pos, int k, int& comparisonsNumber)
{
	comparisonsNumber++;
	if((pos<0)||(pos>fields.size()))
	{
		return -1;
	}
	if(((fields[pos].first<key)&&(pos+1<=fields.size())&&(fields[pos+1].first>key))||((fields[pos].first>key)&&(pos-1>=0)&&(fields[pos-1].first<key)))
	{
		return -1;
	}
	int Ki = 0;
	if(pos==fields.size())
	{
		Ki=INT_MAX;
	}
	else
	{
		Ki = fields[pos].first;
	}
	
	if(key==Ki)
	{
		return pos;
	}
	if(key<Ki)
	{
		k--;
		pos -= static_cast<int>(pow(2, k))/2 + 1;
		return homogeneousBinarySearch(key, fields,pos, k, comparisonsNumber);
	}
	k--;
	pos += static_cast<int>(pow(2, k))/2 + 1;
	return homogeneousBinarySearch(key, fields,pos, k, comparisonsNumber);	
}

bool search::elementWithKeyExists(const std::vector<std::pair<int, std::string>>& fields, int key, int& comparisonsNumber)
{
	const int indexOfElementWithKey = sharrMethod(fields, key, comparisonsNumber);
	if(indexOfElementWithKey>=0)
	{
		return true;
	}
	return false;
}

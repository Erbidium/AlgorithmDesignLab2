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
	int i=pow(2, k);
	int Ki = fields[i].first;
	int K = key;
	if(K==Ki)
	{
		return i;
	}
	if(K<Ki)
	{
		int delta = pow(2, k-1);
		i=i-(delta/2+1);
		return homogeneousBinarySearch(i, delta, fields,key, comparisonsNumber);
	}
	int l = log2(N-pow(2, k)+1);
	i=N+1-pow(2, l);
	int delta = pow(2, l-1);
	return homogeneousBinarySearch(i, delta, fields,key, comparisonsNumber); 
}

int search::homogeneousBinarySearch(int i, int delta, const std::vector<std::pair<int, std::string>>& fields, int key, int& comparisonsNumber)
{
	comparisonsNumber++;
	int Ki = 0;
	if(i>fields.size())
	{
		Ki=INT_MAX;
	}
	else
	{
		Ki = fields[i].first;
	}
	if(key==Ki)
	{
		return i;
	}
	if(delta == 0)
	{
		return -1;
	}
	if(key<Ki)
	{
		i=i-(delta/2+1);
		delta=delta/2;
		return homogeneousBinarySearch(i, delta, fields,key, comparisonsNumber);
	}
	i=i+(delta/2+1);
	delta=delta/2;
	return homogeneousBinarySearch(i, delta, fields,key, comparisonsNumber);
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

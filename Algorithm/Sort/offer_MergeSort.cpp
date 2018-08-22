/*************************************************************************
    > File Name: a.cpp
    > Author: zhengli
    > Mail: zldata@aliyun.com 
    > Created Time: 二  7/ 3 08:13:59 2018
    > Brief: 
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

void printVector(vector<int> &data)
{
	int size = data.size();
	for (int i = 0; i < size; ++i) {
		cout << data[i] << " ";
	}
	cout << endl;
}


class Solution {
    long long InversePairsCore(vector<int> &data, vector<int> &copy, int start, int end)
    {
		cout << "---- " << start << " " << end << " ----\n";
		cout << "data: ";
		printVector(data);
		cout << "copy: ";
		printVector(copy);

        if (start == end) {
            copy[start] = data[start];
            return 0;
        }

        int length = (end - start) / 2;
        long long left = InversePairsCore(copy, data, start, start + length);
		cout << " left = " << left << endl;
        long long rigth = InversePairsCore(copy, data, start + length + 1, end);
		cout << " rigth = " << rigth << endl;

        int i = start + length;
        int j = end;
        int indexcopy = end;
        long long count = 0;
        while (i >= start && j >= start + length + 1)
        {
            if (data[i] > data[j]) {
                copy[indexcopy--] = data[i--];
                count += j - start - length;		// 记录逆序对个数
            }
            else {
                copy[indexcopy--] = data[j--];
            }
        }

        for (; i >= start; --i) {
            copy[indexcopy--] = data[i];
        }
        for (; j >= start + length + 1; --j) {
            copy[indexcopy--] = data[j];
        }

        return left + rigth + count;
    }
public:
    long long InversePairs(vector<int> data) {
        if (data.empty())    return -1;
        int size = data.size();
        vector<int> copy;
		for (int i = 0; i < size; ++i) {
			copy.push_back(data[i]);
		}

        long long count = InversePairsCore(data, copy, 0, size - 1);

        return count;
    }
};

int main()
{
	Solution sol;
	vector<int> data;
	data.push_back(7);
	data.push_back(5);
	data.push_back(6);
	data.push_back(4);

	cout << sol.InversePairs(data) << endl;

	return 0;
}

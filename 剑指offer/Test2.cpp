#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
using namespace std;

bool Find(int* arr, size_t rows, size_t cols, int value)
{
	assert(arr);
	int x = 0;
	int y = cols - 1;
	// x�����Ͻǵ�ֵ��Ϊ��㿪ʼ�Ƚ�
	while (x<rows && y>=0)
	{
		if (arr[x*cols + y] < value) //��ǰλ��С��value���ų���һ��
		{
			++x;
		}
		else if (arr[x*cols + y] > value) //��ǰλ�ô���value���ų���һ��
		{
			--y;
		}
		else
		{
			return true;
		}
	}
	return false;
}
void Test()
{
	int arr1[4][4] = 
	{ { 1, 2, 8, 9 }
	, { 2, 4, 9, 12 }
	, { 4, 7, 10, 13 }
	, { 6, 8, 11, 15 } 
	};
	/*cout << Find((int*)arr1, 4, 4, 1) <<endl;
	cout << Find((int*)arr1, 4, 4, 15) << endl;
	cout << Find((int*)arr1, 4, 4, 3) << endl;*/
	int arr2[4][3] =
	{ { 1,2,4 }
	, { 3,5,7 }
	, { 9,11,13 }
	, {10,15,16 }
	};
	cout << Find((int*)arr2, 4, 4, 11) << endl;
}
int main()
{
	Test();
	system("pause");
	return 0; 
}
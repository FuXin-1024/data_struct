#include<iostream>
#include<map>
#include<set>
#include<string>

using namespace std;

//template <class K,class V>
//struct pair
//{
//	K first;
//	V second;
//	pair(const K& key, const V& value)
//		:first(key)
//		, second(value)
//	{}
//};

//template<class K,class V>
//pair<K, V> make_pair(const K& k, const V& v)
//{
//	return pair<K, V>(k, v);
//}

void PrintMap(const map<string, string>& dict)
{
	map<string, string>::const_iterator dictIt = dict.begin();
	while (dictIt != dict.end())
	{
		cout << (*dictIt).first << ":" << dictIt->second << endl;
		++dictIt;
	}
	cout << endl;
}

void TestMap()
{
	pair < map<string, string>::iterator, bool> ret_ptr;
	map<string, string> dict;
	dict["sort"] = "排序";
	dict["insert"] = "插入";

	dict.insert(pair<string, string>("sort", "排序"));
	dict.insert(pair<string, string>("one", "一"));
	ret_ptr = dict.insert(pair<string, string>("left", "左边"));
	ret_ptr = dict.insert(pair<string, string>("left", "剩余"));
	ret_ptr.first->second = "剩余";
	PrintMap(dict);

	map<string, string>::iterator ret = dict.find("one");
	if (ret != dict.end()) //如果没有找到返回end
	{
		cout << "找到" << endl;
		dict.erase(ret);
	}
	else
	{
		cout << "没有找到" << endl;
	}
	PrintMap(dict);

	string fruits[] = {"苹果","葡萄","苹果","葡萄","香蕉", "西瓜","西瓜","西瓜","西瓜","西瓜","西瓜","西瓜","西瓜","苹果", "苹果", "苹果","苹果"};

	map<string, int> countMap;
	for (size_t i = 0; i < sizeof(fruits) / sizeof(fruits[0]); ++i)
	{
		/*map<string, int>::iterator ret = countMap.find(fruits[i]);
		if (ret != countMap.end())
		{
			ret->second++;
		}
		else
		{
			countMap.insert(make_pair(fruits[i], 1));
		}
*/
		/*pair<map<string, int>::iterator, bool> pr = countMap.insert(make_pair(fruits[i], 1));
		if (pr.second == false)
			pr.first->second++;*/

		countMap[fruits[i]]++;
	}
}

int main()
{
	TestMap();
	system("pause");
	return 0;
}
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
	dict["sort"] = "����";
	dict["insert"] = "����";

	dict.insert(pair<string, string>("sort", "����"));
	dict.insert(pair<string, string>("one", "һ"));
	ret_ptr = dict.insert(pair<string, string>("left", "���"));
	ret_ptr = dict.insert(pair<string, string>("left", "ʣ��"));
	ret_ptr.first->second = "ʣ��";
	PrintMap(dict);

	map<string, string>::iterator ret = dict.find("one");
	if (ret != dict.end()) //���û���ҵ�����end
	{
		cout << "�ҵ�" << endl;
		dict.erase(ret);
	}
	else
	{
		cout << "û���ҵ�" << endl;
	}
	PrintMap(dict);

	string fruits[] = {"ƻ��","����","ƻ��","����","�㽶", "����","����","����","����","����","����","����","����","ƻ��", "ƻ��", "ƻ��","ƻ��"};

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
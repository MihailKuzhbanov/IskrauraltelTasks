#pragma once
#include <string>
#include <vector>
#include <fstream>

using namespace std;
//составитель имен
string FileNameBuilder(string dir, string pre, string post, int number)
{
	return string(dir + pre + to_string(number) + post);
}

//считывание файла
vector<string> GetDataFromFile(string fileName)
{
	vector<string> result;
	ifstream file;
	string temp("");
	file.open(fileName);
	while (getline(file, temp))
	{
		if (temp != "") result.push_back(temp);
	}
	return result;
}

//запись файла
void SaveDataToFile(vector<string> data, string fileName)
{
	ofstream out(fileName);
	for (auto current : data)
	{
		string input = current;
		out << input;
	}
	out.close();
}

//слияние векторов из листа
//шаблон позволит использовать функцию для любых данных, организованных list<vector<T>>
template<typename T>
vector<T> MergeVectors(list<vector<T>> vectorsList, int overallObjects)
{
	vector<T> result;
	result.reserve(overallObjects);
	for (auto& currentProduct : vectorsList)
	{
		result.insert(result.end(), currentProduct.begin(), currentProduct.end());
	}
	return result;
}


#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "Product.hpp"
#include "FileHandler.hpp"

//возможен вариант определения данных переменных через #define, но Cpp-Style через константы
//правильнее было бы перенести в аргументы функции main(int argc, char* argv)
const std::string productSourceDir("./product_data_files/");
const std::string productSourcePrefix("prod_data_");
const std::string fileFormat(".txt");

//возможен подсчет количества файлов в указанной папке:
//с использованием boost - зависит от версии компилятора 
//с использованием count_if - зависит от целевой платформы
//поэтому в соответствии с заданием указано число
const int fileAmount(5);

//ключевые слова в соответствии с заданием
const string keywords[3] = { "FredInc", "AfroFruit", "Apple" };

//содержит все продукты, предлагаемые во входных данных. Реализация через std::list позволяет существенно сократить временные затраты при большом количестве входных файлов
std::list<std::vector<Product>> ProductFromAllFiles;

//список всех продуктов
std::vector<Product> productCache;

//получение объектов через парсинг файла
//шаблон сделает данную функцию небезопасной (безопасной можно сделать через constrexpr, но только начиная с С++17)
//но позволит использовать со структурами, отличными от Product, достаточно лишь иметь Constructor(string arg) для данного класса
std::vector<Product> ParseRawData(std::vector<std::string> input)
{
	std::vector<Product> result;
	result.reserve(input.size());
	for (auto &el : input)
	{
		result.push_back(Product(el));
	}
	return result;
}

//получение всех объектов из всех файлов
//использование шаблона имеет последствия, аналогичные с ParseRawData
std::vector<Product> GetProductFromFiles(std::string dir, std::string pre, std::string post, int _fileAmount)
{
	std::string fileName;
	std::list<std::vector<Product>> allProductsList;
	int productCounter(0);
	for (int i = 0; i < _fileAmount; i++)
	{
		fileName = FileNameBuilder(dir, pre, post, i);
		std::vector<Product> products = ParseRawData(GetDataFromFile(fileName));
		allProductsList.push_back(products);
		productCounter += products.size();
	}
	return MergeVectors(allProductsList, productCounter);
}

//отбор по производителю
std::vector<Product> SelectByManufacturer(std::vector<Product> input, std::string condition)
{
	vector<Product> result;
	for (auto current : input)
	{
		if (current.GetManufacturer() == condition) result.push_back(current);
	}
	return result;
}

//отбор по товару
std::vector<Product> SelectByName(std::vector<Product> input, std::string condition)
{
	vector<Product> result;
	for (auto current : input)
	{
		if (current.GetName() == condition) result.push_back(current);
	}
	return result;
}

//получение данных в требуемом виде (как было во входных файлах)
std::vector<std::string> RequeredFormatOutput(std::vector<Product> input)
{
	std::vector<string> result;
	result.reserve(input.size());
	for (auto current : input)
	{
		result.push_back(current.GetName() + ',' + std::to_string(current.GetPrice()) + ',' + current.GetManufacturer() + ',' + std::to_string(current.GetPrice()) + '\n');
	}
	return result;
}

int main()
{
	std::vector<string> answer;
	productCache = GetProductFromFiles(productSourceDir, productSourcePrefix, fileFormat, fileAmount);
	
	std::vector<Product> listOne = SelectByManufacturer(productCache, keywords[0]);
	std::vector<Product> listTwo = SelectByManufacturer(productCache, keywords[1]);
	std::vector<Product> listThree = SelectByName(productCache, keywords[2]);
	
	answer = RequeredFormatOutput(listOne);
	SaveDataToFile(answer, productSourceDir + keywords[0] + fileFormat);
	answer = RequeredFormatOutput(listTwo);
	SaveDataToFile(answer, productSourceDir + keywords[1] + fileFormat);
	answer = RequeredFormatOutput(listThree);
	SaveDataToFile(answer, productSourceDir + keywords[2] + fileFormat);

	system("pause");
}

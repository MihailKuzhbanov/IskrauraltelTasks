#pragma once
#include <string>

using namespace std;
//структура продукта
struct Product
{
private:
	string name, manufacturer;
	int price, count;

public:
	//конструкторы
	//
	//конструктор по умолчанию, для создания пустых позиций, при необходимости использовать с поврежденными/неполными данными
	Product() : name(""), manufacturer(""), price(0), count(0) {};

	//конструктор для ручного добавления продукта в список (безопасный)
	Product(string _name, string _manufacturer, int _price, int _count) : name(_name), manufacturer(_manufacturer), price(_price), count(_count) {};

	//конструктор с парсером строки (не безопасный)
	Product(string inputData)
	{
		string strTemp("");
		//присваивание полей для возможности отследить битые данные
		name = "n/a";
		manufacturer = "n/a";
		price = -1;
		count = -1;

		for (char c : inputData)
		{
			if (c != ',') strTemp += c;
			else
			{
				if (name == "n/a") name = strTemp;
				else if (price == -1) price = stoi(strTemp);
				else if (manufacturer == "n/a") manufacturer = strTemp;
				strTemp = "";
			}
			
		}
		count = stoi(strTemp);
	}

	//геттеры, сеттеры
	//
	string GetName()
	{
		return name;
	}

	string GetManufacturer()
	{
		return manufacturer;
	}

	int GetPrice()
	{
		return price;
	}

	int GetCount()
	{
		return count;
	}

	void SetName(string _name)
	{
		name = _name;
	}

	void SetManufacturer(string _manufacturer)
	{
		manufacturer = _manufacturer;
	}

	void SetPrice(int _price)
	{
		price = _price;
	}

	void SetCount(int _count)
	{
		count = _count;
	}

};
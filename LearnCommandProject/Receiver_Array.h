#pragma once
#include<vector>
#include<optional>
#include<iostream>
template <class T>
class Receiver_Array
{
private:
	std::vector<T>* myArry;
public:
	~Receiver_Array()
	{
	}
	Receiver_Array() 
	{
		myArry = new std::vector<T>();
	}
	Receiver_Array(std::vector<T>* _myArry)
	{
		if (_myArry)
		{
			myArry = new std::vector<T>(*_myArry);
		}
		else
		{
			myArry = new std::vector<T>();
		}
	}
	bool add(const int pos, const T& val)
	{
		if (errorCheck(pos))
		{
			return false;
		}
		myArry->insert(pos + myArry->begin(), val);
		return true;
	}
	bool del(const int pos)
	{
		if (errorCheck(pos))
		{
			return false;
		}
		myArry->erase(pos + myArry->begin());
		return true;
	}
	bool modify(const int pos, const T& val)
	{
		if (errorCheck(pos))
		{
			return false;
		}
		myArry->erase(pos + myArry->begin());
		return true;
	}
	std::optional<T> seek(const int pos)
	{
		if (errorCheck(pos))
		{
			return std::nullopt;
		}
		return (*myArry)[pos];
	}
	bool errorCheck(const int pos)
	{
		if (pos >= myArry->size())
		{
			printf("  Operation Failed.Array Bounds Errors.  ");
			return true;
		}
		return false;
	}
	void display()
	{
		for (int i = 0; i < myArry->size(); ++i)
		{
			std::cout << (*myArry)[i] << "  ";
		}
		std::cout << std::endl;
	}
};


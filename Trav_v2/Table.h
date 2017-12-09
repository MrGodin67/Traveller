#pragma once

#include <vector>

template<typename T>
class Table
{
public:
	std::vector<T> container;
	std::size_t columns;
	Table() = default;
	Table(std::size_t& row, std::size_t col)
	{
		container.resize(size);
		columns = col;
	}
	T& operator()(const std::size_t& r, const std::size_t& c)
	{
		return container[r * columns + c];
	}
	T& operator()(const std::size_t& r, const std::size_t& c)const
	{
		return container[r * columns + c];
	}
	T& operator()(const std::size_t& index)const
	{ 
		return container[index]; 
	}
	T& operator()(const std::size_t& index) 
	{ 
		return container[index]; 
	}
	std::size_t size()const { return container.size(); }
	std::size_t size() { return container.size(); }
	std::size_t Resize(const std::size_t& r, const std::size_t& c)
	{
		 columns = c;
		 container.resize(r * c);
		 return container.size();
	}
	void Flush()
	{
		container.clear();
	}
};
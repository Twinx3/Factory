#include <iostream>
#include <string>
#include <memory>
using namespace std;

//В функцию передается имя класса и параметры, возвращается созданный обект.

class Gadget
{
public:
	virtual int GetPrice() = 0;
};


class MobilePhone : public Gadget
{
private:
	string model;
	int year;
public:
	MobilePhone(const std::string& model, int year)
	{
		this->model = model;
		this->year = year;
	}
	int GetPrice()
	{
		int cost = model.length() + year;
		return cost;
	}
};


class Laptop : public Gadget
{
private:
	string model;
	int ram_size;
	int cpu_level;
public:
	Laptop(const std::string& model, int ram_size, int cpu_level)
	{
		this->cpu_level = cpu_level;
		this->model = model;
		this->ram_size = ram_size;
	}
	int GetPrice()
	{
		int cost = model.length() + ram_size + cpu_level;
		return cost;
	}
};

template<typename T, typename... ARGS>
unique_ptr<T> Const(ARGS... args)
{
	if constexpr (is_constructible_v<T, ARGS...>)
	{
		unique_ptr<T> gadget(new T(args...));
		return gadget;
	}
	else
		return nullptr;
}

template<typename... ARGS>
unique_ptr<Gadget> Factory(const string& name, ARGS&&... params)
{
	unique_ptr<Gadget> gadget;
	if  (name == "Mobile phone")
	{
		gadget = Const<MobilePhone>(forward<ARGS>(params)...);
		return gadget;
	}
	else if  (name == "Laptop")
	{
		gadget = Const<Laptop>(forward<ARGS>(params)...);
		return gadget;
	}
	else
		return nullptr;
}

int main()
{
	auto gadget1 = Factory("Mobile phone", "Samsung", 2020);
	std::cout << gadget1->GetPrice() << endl;

	auto gadget2 = Factory("Mobile phone", "IPhone", 2021);
	std::cout << gadget2->GetPrice() << endl;



	auto gadget3 = Factory("Laptop", "Asus", 16000, 2400);
	std::cout << gadget3->GetPrice() << endl;
}
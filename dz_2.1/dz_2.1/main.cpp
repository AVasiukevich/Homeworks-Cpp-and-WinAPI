#include<iostream>

template<class T>
class UniquePtr
{
private:
	T* ptr = nullptr;

public:
	template<class T>
	friend std::ostream& operator<<(std::ostream& os, const UniquePtr<T>& obj);

	UniquePtr() = default;

	explicit UniquePtr(T* obj)
		:ptr{ obj }
	{}

	UniquePtr(const UniquePtr& obj) = delete;

	UniquePtr& operator=(const UniquePtr& obj) = delete;

	~UniquePtr()
	{
		delete ptr;
	}
};

template<class T>
std::ostream& operator<<(std::ostream& os, const UniquePtr<T>& obj)
{
	os << *obj.ptr;
	return os;
}

template<class T>
class AssignPtr
{
private:
	T* ptr = nullptr;

public:
	template<class T>
	friend std::ostream& operator<<(std::ostream& os, const AssignPtr<T>& obj);

	AssignPtr() = default;

	explicit AssignPtr(T* obj)
		:ptr{ obj }
	{}

	AssignPtr(AssignPtr& obj)
		:ptr{ obj.ptr }
	{
		obj.ptr = nullptr;
	}

	AssignPtr& operator=(AssignPtr& obj)
	{
		if (&obj != this)
		{
			ptr = obj.ptr;
			obj.ptr = nullptr;
		}
		return *this;
	}

	~AssignPtr()
	{
		delete ptr;
	}
};

template<class T>
std::ostream& operator<<(std::ostream& os, const AssignPtr<T>& obj)
{
	if (!obj.ptr)
		os << "Nullptr!";
	else
		os << *obj.ptr;
	return os;
}

template<class T>
class CoopPtr
{
private:
	T* ptr = nullptr;
	int* count = nullptr;

public:
	template<class T>
	friend std::ostream& operator<<(std::ostream& os, const CoopPtr<T>& obj);

	CoopPtr() = default;

	explicit CoopPtr(T* obj)
		:ptr{ obj }, count{ new int(1) }
	{}
	CoopPtr(const CoopPtr& obj)
		:ptr{ obj.ptr }, count{ obj.count }
	{
		++(*count);
	}

	CoopPtr& operator=(const CoopPtr& obj)
	{
		if (&obj != this)
		{
			ptr = obj.ptr;
			count = obj.count;
			++(*count);
		}
		return *this;
	}
	~CoopPtr()
	{
		if (*count == 1) {
			delete ptr;
			delete count;
		}
		else
			--(*count);
	}
};

template<class T>
std::ostream& operator<<(std::ostream& os, const CoopPtr<T>& obj)
{
	os << " Value: " << *obj.ptr << " Count: " << *obj.count;

	return os;
}

class Res_1
{
private:
	UniquePtr<int> ptr;
public:
	friend std::ostream& operator<<(std::ostream& os, const Res_1& obj);
	Res_1()
		: ptr(nullptr)
	{}
	Res_1(int num)
		: ptr(new int(num))
	{}
};

std::ostream& operator<<(std::ostream& os, const Res_1& obj)
{
	os << obj.ptr;

	return os;
}

class Res_2
{
private:
	AssignPtr<int> ptr;
public:
	friend std::ostream& operator<<(std::ostream& os, const Res_2& obj);
	Res_2()
		: ptr(nullptr)
	{}
	Res_2(int num)
		: ptr(new int(num))
	{}
};

std::ostream& operator<<(std::ostream& os, const Res_2& obj)
{
	os << obj.ptr;

	return os;
}

class Res_3
{
private:
	CoopPtr<int> ptr;
public:
	friend std::ostream& operator<<(std::ostream& os, const Res_3& obj);
	Res_3()
		: ptr(nullptr)
	{}
	Res_3(int num)
		: ptr(new int(num))
	{}
};

std::ostream& operator<<(std::ostream& os, const Res_3& obj)
{
	os << obj.ptr;

	return os;
}

void menu()
{
	bool par = true;
	while (par)
	{
		int num;
		std::cout << "1. Wrapper assignment." << std::endl;
		std::cout << "2. Wrapper unique resource." << std::endl;
		std::cout << "3. Wrapper co-ownership." << std::endl;
		std::cin >> num;
		system("cls");

		switch (num)
		{
		case 1:
		{
			std::cout << "Create a resource with value (int) 10." << std::endl;
			Res_2 obj(10);
			int pos;
			std::cout << "1. Copy." << std::endl;
			std::cout << "2. Assignment." << std::endl;
			std::cout << "3. Exit." << std::endl;
			std::cin >> pos;
			if (pos == 1)
			{
				Res_2 obj_2 = obj;
				std::cout << "Resource obj_2 = obj;" << std::endl;
				std::cout << "obj_2 = " << obj_2 << std::endl;
				std::cout << "obj = " << obj << std::endl;
			}
			else if (pos == 2)
			{
				Res_2 obj_2;
				obj_2 = obj;
				std::cout << "Resource obj_2;" << std::endl;
				std::cout << "obj_2 = obj;" << std::endl;
				std::cout << "obj_2 = " << obj_2 << std::endl;
				std::cout << "obj = " << obj << std::endl;
			}
			else
				par = false;
			break;
		}
		case 2:
		{
			std::cout << "Create a resource with value (int) 10." << std::endl;
			/*Res_1 obj(10);
			Res_1 obj_2 = obj;
			Res_1 obj_3;
			obj_3 = obj;*/
			int pos;
			std::cout << "1. Copy." << std::endl;
			std::cout << "2. Assignment." << std::endl;
			std::cout << "3. Exit." << std::endl;
			std::cin >> pos;
			if (pos == 1 || pos == 2)
				std::cout << "Error C2280: attempting to reference a deleted function" << std::endl;
			else
				par = false;

			break;
		}
		case 3:
		{
			std::cout << "Create a resource with value (int) 10." << std::endl;
			Res_3 obj(10);
			int pos;
			std::cout << "1. Copy." << std::endl;
			std::cout << "2. Assignment." << std::endl;
			std::cout << "3. Exit." << std::endl;
			std::cin >> pos;
			if (pos == 1)
			{
				Res_3 obj_2 = obj;
				std::cout << "Resource obj_2 = obj;" << std::endl;
				std::cout << "obj_2 = " << obj_2 << std::endl;
				std::cout << "obj = " << obj << std::endl;
			}
			else if (pos == 2)
			{
				Res_3 obj_2;
				obj_2 = obj;
				std::cout << "Resource obj_2;" << std::endl;
				std::cout << "obj_3 = obj;" << std::endl;
				std::cout << "obj_2 = " << obj_2 << std::endl;
				std::cout << "obj = " << obj << std::endl;
			}
			else
				par = false;
			break;
		}
		default:
		{
			par = false;
			break;
		}
		}
		std::cout << std::endl;
	}
}

int main()
{
	menu();
	return 0;
}
#include <iostream>
using namespace std;

#define DIFF_REGISTER 32

class String
{
private:
	int size;
	char* str;

public:
	String(const char*);
	char* getString() const;
	int length() const;
	char* changeString(const char*);
	char* unionString(const char*);
	char* addSymbol(char, int);
	void showASCII() const;
	char* upString();
	char* downString();
	~String();
};

String::String(const char* st)
	: size{ (int)strlen(st) }, str{ new char[size + 1] }
{
	strcpy_s(str, size + 1, st);
}

inline char* String::getString() const
{
	return str;
}

inline int String::length() const
{
	return size;
}

char* String::changeString(const char* st)
{
	delete[] str;
	size = strlen(st);
	str = new char[size + 1];
	strcpy_s(str, size + 1, st);
	return str;
}

char* String::unionString(const char* st)
{
	size += strlen(st);
	char* tmp_str = new char[size + 1];
	strcpy_s(tmp_str, size + 1, str);
	strcat_s(tmp_str, size + 1, st);
	delete[] str;
	str = tmp_str;
	return str;
}

char* String::addSymbol(char sym, int index)
{
	if (index < 0 || index > size)
	{
		cout << "Invalid index." << endl;
		return str;
	}
	char* tmp_str = new char[++size + 1];
	strncpy_s(tmp_str, size + 1, str, index); //Copying text to the element
	strcat_s(tmp_str, size + 1, &str[index - 1]); //Copy the text after the element + 1
	tmp_str[index] = sym; // Copy element
	delete[] str;
	str = tmp_str;
	return str;
}

void String::showASCII() const
{
	for (int i = 0; i < size; ++i)
		cout << (int)str[i] << " ";
	cout << endl;
}

char* String::upString()
{
	for (int i = 0; i < size; ++i)
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= DIFF_REGISTER;

	return str;
}

char* String::downString()
{
	for (int i = 0; i < size; ++i)
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += DIFF_REGISTER;

	return str;
}

String::~String()
{
	delete[] str;
}

int main()
{
	String str_("Hello World!");
	cout << "Output string: " << str_.getString() << endl;
	cout << "Length string: " << str_.length() << endl;
	cout << "Change string: " << str_.changeString("GoodBye World") << endl;
	cout << "Add string: " << str_.unionString(" GoodBye") << endl;
	cout << "Insert symbol: " << str_.addSymbol('?', 21) << endl;
	str_.showASCII();
	cout << "Upper registers: " << str_.upString() << endl;
	cout << "Lower registers: " << str_.downString() << endl;

	return 0;
}

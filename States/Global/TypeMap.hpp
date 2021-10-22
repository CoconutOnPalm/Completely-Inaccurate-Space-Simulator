#pragma once

#include <iostream>
#include <map>

class TypeTranslator
{
public:

	TypeTranslator();
	~TypeTranslator();

	TypeTranslator(const TypeTranslator& left) = delete;
	void operator= (const TypeTranslator& left) = delete;

	static TypeTranslator& Get();

	static std::string getClassName(int object_class);
	static std::string getSubtypeName(int object_subtype);

private:

	void loadClassMap();
	void loadSubtypeMap();

	std::map<int, std::string> m_classes;
	std::map<int, std::string> m_subtypes;
};


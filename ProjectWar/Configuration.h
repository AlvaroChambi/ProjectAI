#pragma once
#include <unordered_map>
#include <iostream>
#include <string>

/*
 *	Class that contains a map with key-value structure. This map has all the configuration
 *	for the execution of the game in this format.
 */
class Configuration {
public:
	Configuration();
	~Configuration();

	bool load(const char* filename);

	template <typename T>
	T get(const char * key, T defaultValue);
	
private:
	std::unordered_map<std::string, std::string> configuration;
};
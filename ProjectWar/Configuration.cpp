#include "Configuration.h"
#include <fstream>
#include <regex>

Configuration::Configuration() {
	configuration.reserve(10);
}

Configuration::~Configuration() {}

bool Configuration::load(const char* filename) {
	std::ifstream configurationFile;
	configurationFile.open(filename, std::ifstream::in);
	
	if ( configurationFile.is_open() ) {
		std::string line;
		while (std::getline(configurationFile, line))
		{
			std::regex expression("^([^:]+):([^:]+)$");
			std::regex_iterator<std::string::iterator> match(line.begin(), line.end(), expression);
			std::string key = (*match)[1];
			std::string value = (*match)[2];
			configuration[key] = value;
		}
	} else {
		return false;
	}

	configurationFile.close();
	return true;
}

template <>
int Configuration::get<int>(const char * key, int default) {
	std::unordered_map<std::string, std::string>::iterator iterator = configuration.find(key);
	if (iterator == configuration.end()) {
		return default;
	}
	else {
		return atoi(iterator->second.c_str());
	}
}

template<>
std::string Configuration::get<std::string>(const char * key, std::string default) {
	std::unordered_map<std::string, std::string>::iterator iterator = configuration.find(key);
	if (iterator == configuration.end()) {
		return default;
	}
	else {
		return iterator->second;
	}
}

// more specialized types for get will go here
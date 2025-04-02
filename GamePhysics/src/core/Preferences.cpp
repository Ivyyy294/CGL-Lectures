#include "Preferences.h"

#include <fstream>
#include <map>

std::map<std::string, std::string> preferences{};
const char* FILE_NAME = "preferences.txt";

void Preferences::Load() {
    std::ifstream file(FILE_NAME);
    std::string key;
    std::string value;
    while (file >> key >> value) {
        preferences[key] = value;
    }
}

void Preferences::SetBool(const std::string& key, bool value) {
    preferences[key] = value ? "1" : "0";
}

bool Preferences::GetBool(const std::string& key, bool defaultValue) {
    if (preferences.count(key) > 0) {
        return preferences[key] == "1";
    }
    return defaultValue;
}

void Preferences::SetInt(const std::string& key, int value) {
    preferences[key] = std::to_string(value);
}

int Preferences::GetInt(const std::string& key, int defaultValue) {
    if (preferences.count(key) > 0) {
        return std::stoi(preferences[key]);
    }
    return defaultValue;
}

void Preferences::SetFloat(const std::string& key, float value) {
    preferences[key] = std::to_string(value);
}

float Preferences::GetFloat(const std::string& key, float defaultValue) {
    if (preferences.count(key) > 0) {
        return std::stof(preferences[key]);
    }
    return defaultValue;
}

void Preferences::SetString(const std::string& key, const std::string& value) {
    preferences[key] = value;
}

const std::string& Preferences::GetString(const std::string& key,
                                          const std::string& defaultValue) {
    if (preferences.count(key) > 0) {
        return preferences[key];
    }
    return defaultValue;
}

void Preferences::Save() {
    std::ofstream file(FILE_NAME);
    for (const auto& entry : preferences) {
        file << entry.first << std::endl;
        file << entry.second << std::endl;
    }
}

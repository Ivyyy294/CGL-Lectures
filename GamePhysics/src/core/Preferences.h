#pragma once

#include <string>

// Simple storing of preferences in a file.
namespace Preferences {

// Loads the preferences from the file.
void Load();
void SetBool(const std::string& key, bool value);
bool GetBool(const std::string& key, bool defaultValue=false);
void SetInt(const std::string& key, int value);
int GetInt(const std::string& key, int defaultValue=0);
void SetFloat(const std::string& key, float value);
float GetFloat(const std::string& key, float defaultValue = 0.0f);
void SetString(const std::string& key, const std::string& value);
const std::string& GetString(const std::string& key,
                             const std::string& defaultValue = "");
// Store the preferences to the file.
void Save();

}
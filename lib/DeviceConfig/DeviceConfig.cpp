/**
 * Device config
 */

#include <DeviceConfig.h>

#include <Arduino.h>
#include <ArduinoJson.h>

#include <Debug.h>
#include <DeviceConfigShared.h>
#include <FileSystem.h>

// allocate memory for variables

bool DeviceConfig::configFileExists = false;

DynamicJsonDocument *DeviceConfig::_config = new DynamicJsonDocument(1024); // This is the config file size

// Private methods

void DeviceConfig::loadConfigFile()
{
    Debug::l(F("I(\"DeviceConfig.loadConfigFile: called\")"));

    String *filePath = new String(FPSTR(DEVICE_CONFIG_DIR));
    filePath->concat("/");
    filePath->concat(FPSTR(DEVICE_CONFIG_FILE));

    Debug::w(F("I(\"DeviceConfig.loadConfigFile: Path: "));
    Debug::w(filePath->c_str());
    Debug::l(F("\")"));

    DeviceConfig::configFileExists = FileSystem::fileExists(filePath->c_str());

    Debug::w(F("I(\"DeviceConfig.loadConfigFile: Exists: "));
    Debug::w(DeviceConfig::configFileExists ? F("True") : F("False"));
    Debug::l(F("\")"));

    if (DeviceConfig::configFileExists)
    {
        Debug::l(F("I(\"DeviceConfig.loadConfigFile: Loading JSON file...\")"));

        FileSystemReadJsonFileErrors err = FileSystem::readJsonFile(filePath->c_str(), 1024, DeviceConfig::_config);

        switch (err)
        {
        case FileSystemReadJsonFileErrors::OK:
        {
            Debug::l(F("I(\"DeviceConfig.loadConfigFile: Config file OK\")"));
            break;
        }
        case FileSystemReadJsonFileErrors::FILE_NOT_FOUND:
        {
            Debug::l(F("I(\"DeviceConfig.loadConfigFile: File not found\")"));
            break;
        }
        case FileSystemReadJsonFileErrors::READ_FAILED:
        {
            Debug::l(F("I(\"DeviceConfig.loadConfigFile: Read failed\")"));
            break;
        }
        case FileSystemReadJsonFileErrors::LARGE_FILE:
        {
            Debug::l(F("I(\"DeviceConfig.loadConfigFile: Large file\")"));
            break;
        }
        case FileSystemReadJsonFileErrors::INVALID_JSON:
        {
            Debug::l(F("I(\"DeviceConfig.loadConfigFile: Invalid JSON file\")"));
            break;
        }
        }
    }

    Debug::l(F("I(\"DeviceConfig.loadConfigFile: Done\")"));
}

// Public methods

void DeviceConfig::setup()
{
    Debug::l(F("I(\"DeviceConfig.setup: called\")"));

    DeviceConfig::loadConfigFile();

    Debug::l(F("I(\"DeviceConfig.setup: Done\")"));
}

JsonObject DeviceConfig::get(const char *moduleName)
{
    Debug::w(F("I(\"DeviceConfig.get: moduleName: "));
    Debug::w(moduleName);
    Debug::l(F("\")"));

    if (!DeviceConfig::configFileExists)
    {
        Debug::l(F("I(\"DeviceConfig.get: Not exists\")"));
        return JsonObject();
    }

    if (!DeviceConfig::_config->containsKey(moduleName))
    {
        Debug::l(F("I(\"DeviceConfig.get: No config\")"));
        return JsonObject();
    }

    return DeviceConfig::_config->getMember(moduleName).as<JsonObject>();
}
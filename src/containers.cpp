#include "containers.h"

const std::string settingsFilePath = "settings.ini";
CDataFile settingsFileData(settingsFilePath);

std::string currentFilePath;
CDataFile currentFileData;

std::string tsRulesPath;
std::string fsRulesPath;

std::string lastUsedPath = ".";

std::map <std::string, Trigger*> triggers;
std::map <std::string, Tag*> tags;
std::map <std::string, Team*> teams;
std::map <std::string, Script*> scripts;
std::map <std::string, Taskforce*> taskforces;
std::map <std::string, std::string > aitriggers;

std::map <uint16_t, unitContainer> buildings;
std::map <std::string, unitContainer> vehicles;
std::map <std::string, unitContainer> infantry;
std::map <std::string, unitContainer> aircraft;

std::map <uint16_t, std::string > houses;

std::map <uint16_t, variableContainer> localvariables;
std::map <uint16_t, variableContainer> globalvariables;

std::vector <int32_t> waypoints;

bool cloneOfNaming, ascNumNaming, alphabetNaming;

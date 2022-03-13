#include "cLoader.h"
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>

#include <rapidjson/filereadstream.h>
#include <rapidjson/document.h>

static const std::string levelListFileName = "assets/LevelList.json";

void cLoader::LoadTextureNames(cBasicTextureManager* manager)
{
    std::vector<std::string> listOfTextures;
    std::ifstream file("textures.txt");


    if (!file)
    {
        std::cout << "File not found" << std::endl;
        return;
    }
    
    int length;
    file >> length;

    std::string line;
    for (int i = 0; i < length; i++)
    {
        file >> line;
        listOfTextures.push_back(line);
    }

    manager->SetBasePath("assets/textures");
    for (int i = 0; i < length; i++)
    {
        if (!manager->HasTexture(listOfTextures[i]))
        {
            bool thing = manager->Create2DTextureFromBMPFile(listOfTextures[i], true);
        }
    }


}

void cLoader::SaveTextureNames(std::vector<std::string> texNames, cBasicTextureManager* manager)
{
    std::ofstream file("textures.txt");

    file << texNames.size() << std::endl;

    for (int i = 0; i < texNames.size(); i++)
    {
        file << texNames[i] << std::endl;
    }

    file.close();
}

void cLoader::LoadAllLevels(std::vector<cLevel*>& levels)
{
    using namespace rapidjson;

    FILE* fp = 0;
    fopen_s(&fp, levelListFileName.c_str(), "rb"); // non-Windows use "r"

    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    Document d;
    d.ParseStream(is);

    std::vector<std::string> levelFileNames;

    const Value& levelNames = d["LevelList"];
    for (int i = 0; i < levelNames.Size(); i++)
    {
        //languages.insert(languages.end(), languageOptions[i].GetString());
        levelFileNames.push_back(levelNames[i].GetString());
    }

    fclose(fp);

    for (int i = 0; i < levelFileNames.size(); i++)
    {
        std::string fileName = "assets/levels/" + levelFileNames[i];
        cLevel* newLevel = new cLevel();

        LoadSpecificLevel(fileName, newLevel);
        levels.push_back(newLevel);
    }
}

void cLoader::LoadSpecificLevel(std::string levelFileName, cLevel* level)
{
    using namespace rapidjson;

    FILE* fp = 0;
    fopen_s(&fp, levelFileName.c_str(), "rb"); // non-Windows use "r"

    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    Document d;
    d.ParseStream(is);

    glm::vec3 spawnPosition;
    spawnPosition.x = d["spawnPosition"]["x"].GetFloat();
    spawnPosition.y = d["spawnPosition"]["y"].GetFloat();
    spawnPosition.z = d["spawnPosition"]["z"].GetFloat();
    level->spawnPosition = spawnPosition;

    glm::vec3 goalPosition;
    goalPosition.x = d["goalPosition"]["x"].GetFloat();
    goalPosition.y = d["goalPosition"]["y"].GetFloat();
    goalPosition.z = d["goalPosition"]["z"].GetFloat();
    level->goalPosition = goalPosition;

    const Value& plataforms = d["plataforms"];
    for (int i = 0; i < plataforms.Size(); i++)
    {
        sPlataform newPlataform;
        newPlataform.id = plataforms[i]["id"].GetInt();
        newPlataform.position.x = plataforms[i]["position"]["x"].GetFloat();
        newPlataform.position.y = plataforms[i]["position"]["y"].GetFloat();
        newPlataform.position.z = plataforms[i]["position"]["z"].GetFloat();
        newPlataform.length = plataforms[i]["length"].GetFloat();
        newPlataform.width = plataforms[i]["width"].GetFloat();

        level->plataforms.push_back(newPlataform);
    }

    const Value& buttons = d["buttons"];
    for (int i = 0; i < buttons.Size(); i++)
    {
        cButton newButton;

        int platId = buttons[i]["plataformId"].GetInt();
        newButton.connectedPlataform = &(level->plataforms[platId]);

        newButton.position.x = buttons[i]["position"]["x"].GetFloat();
        newButton.position.y = buttons[i]["position"]["y"].GetFloat();
        newButton.position.z = buttons[i]["position"]["z"].GetFloat();
        newButton.plataformAlternatePosition.x = buttons[i]["alternatePosition"]["x"].GetFloat();
        newButton.plataformAlternatePosition.y = buttons[i]["alternatePosition"]["y"].GetFloat();
        newButton.plataformAlternatePosition.z = buttons[i]["alternatePosition"]["z"].GetFloat();
        newButton.plataformOgPosition = level->plataforms[platId].position;
        
        level->buttons.push_back(newButton);
    }

    fclose(fp);
}

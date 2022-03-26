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

void cLoader::LoadAllLevels()
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

    /*glm::vec3 goalPosition;
    goalPosition.x = d["goalPosition"]["x"].GetFloat();
    goalPosition.y = d["goalPosition"]["y"].GetFloat();
    goalPosition.z = d["goalPosition"]["z"].GetFloat();
    level->goalPosition = goalPosition;*/

    const Value& treasures = d["treasures"];
    for (int i = 0; i < treasures.Size(); i++) {
        
        cMesh* treasure = new cMesh();
        treasure->meshName = "SpriteHolder.ply";
        treasure->scale = glm::vec3(0.5f);
        treasure->orientationXYZ.y = -1.57f;
        treasure->orientationXYZ.x = -1.57f;
        treasure->bDontLight = true;
        int end = treasures[i]["end"].GetInt();
        treasure->positionXYZ.x = treasures[i]["position"]["x"].GetFloat();
        treasure->positionXYZ.y = treasures[i]["position"]["y"].GetFloat();
        treasure->positionXYZ.z = treasures[i]["position"]["z"].GetFloat();
        if (end == 1) {
            treasure->textureNames[0] = "Crown.bmp";
            treasure->textureRatios[0] = 1.0f;
        }
        else {
            treasure->textureNames[0] = "Coins.bmp";
            treasure->textureRatios[0] = 1.0f;
        }

        TreasureEntity* treasureEntity = new TreasureEntity(treasure);
        if (end == 1) {
            treasureEntity->isMainTreasure = true;
        }
        level->treasures.push_back(treasureEntity);
    }

    const Value& plataforms = d["plataforms"];
    for (int i = 0; i < plataforms.Size(); i++)
    {
        //sPlataform newPlataform;
        //newPlataform.id = plataforms[i]["id"].GetInt();
        //newPlataform.position.x = plataforms[i]["position"]["x"].GetFloat();
        //newPlataform.position.y = plataforms[i]["position"]["y"].GetFloat();
        //newPlataform.position.z = plataforms[i]["position"]["z"].GetFloat();
        //newPlataform.length = plataforms[i]["length"].GetFloat();
        //newPlataform.width = plataforms[i]["width"].GetFloat();

        //level->plataforms.push_back(newPlataform);

        cMesh* platformMesh = new cMesh();
        platformMesh->meshName = "Invader_Single_Cube.ply";
        platformMesh->orientationXYZ.x = 3.14f;
        platformMesh->positionXYZ.x = plataforms[i]["position"]["x"].GetFloat();
        platformMesh->positionXYZ.y = plataforms[i]["position"]["y"].GetFloat();
        platformMesh->positionXYZ.z = plataforms[i]["position"]["z"].GetFloat();
        int type = plataforms[i]["type"].GetInt();
        platformMesh->textureNames[0] = "futurebrick.bmp";
        platformMesh->textureRatios[0] = 1.0f;
        // change whatever you need for the mesh here

        float platformWidth = plataforms[i]["width"].GetFloat();
        float platformLength = plataforms[i]["length"].GetFloat();

        PlatformEntity* newPlatform = new PlatformEntity(platformMesh, platformWidth, platformLength);
        if (type == 1) {
            newPlatform->behaviour = PLATFORM_MOVING;
            float xPos = plataforms[i]["offset"]["x"].GetFloat();
            float yPos = plataforms[i]["offset"]["y"].GetFloat();
            float zPos = plataforms[i]["offset"]["z"].GetFloat();

            newPlatform->target = glm::vec3(xPos, yPos, zPos);

            newPlatform->resetTime = plataforms[i]["reset"].GetFloat();
            newPlatform->moveTime = plataforms[i]["move"].GetFloat();

            newPlatform->isMoving = true;
        }
        level->plataforms.push_back(newPlatform);
    }

    const Value& buttons = d["buttons"];
    for (int i = 0; i < buttons.Size(); i++)
    {
        //cButton newButton;

        //int platId = buttons[i]["plataformId"].GetInt();
        //newButton.connectedPlataform = &(level->plataforms[platId]);

        //newButton.position.x = buttons[i]["position"]["x"].GetFloat();
        //newButton.position.y = buttons[i]["position"]["y"].GetFloat();
        //newButton.position.z = buttons[i]["position"]["z"].GetFloat();
        //newButton.plataformAlternatePosition.x = buttons[i]["alternatePosition"]["x"].GetFloat();
        //newButton.plataformAlternatePosition.y = buttons[i]["alternatePosition"]["y"].GetFloat();
        //newButton.plataformAlternatePosition.z = buttons[i]["alternatePosition"]["z"].GetFloat();
        //newButton.plataformOgPosition = level->plataforms[platId].position;
        //
        //level->buttons.push_back(newButton);

        cMesh* buttonMesh = new cMesh();
        buttonMesh->meshName = "SpriteHolder.ply";
        buttonMesh->orientationXYZ.y = -1.57f;
        buttonMesh->orientationXYZ.x = -1.57f;
        buttonMesh->positionXYZ.x = buttons[i]["position"]["x"].GetFloat();
        buttonMesh->positionXYZ.y = buttons[i]["position"]["y"].GetFloat();
        buttonMesh->positionXYZ.z = buttons[i]["position"]["z"].GetFloat();
        buttonMesh->bDontLight = true;
        buttonMesh->textureNames[0] = "ButtonUp.bmp";
        buttonMesh->textureRatios[0] = 1.0f;
        // change whatever you need for the mesh here

        glm::vec3 platformAlternatePosition;
        platformAlternatePosition.x = buttons[i]["alternatePosition"]["x"].GetFloat();
        platformAlternatePosition.y = buttons[i]["alternatePosition"]["y"].GetFloat();
        platformAlternatePosition.z = buttons[i]["alternatePosition"]["z"].GetFloat();

        int type = buttons[i]["type"].GetInt();
        int platformId = buttons[i]["plataformId"].GetInt();

        ButtonEntity* newButton = new ButtonEntity(buttonMesh, 0.5f, platformAlternatePosition, platformId);
        if (type == 1) {
            newButton->behaviour = BUTTON_PAUSE;
        }
        level->buttons.push_back(newButton);
    }

    fclose(fp);
}

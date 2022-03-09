#include "cLoader.h"
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>



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

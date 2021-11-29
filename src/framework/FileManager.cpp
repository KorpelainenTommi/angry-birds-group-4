#include <framework/FileManager.hpp>
#include <sstream>
#include <iostream>
#include <filesystem>

bool FileManager::LoadTexture(sf::Texture& texture, const std::string& path) const {
    std::cout << "  Loading texture: " << path << std::endl;
    return texture.loadFromFile(path);
}

bool FileManager::LoadAudio(sf::SoundBuffer& soundBuffer, const std::string& path) const {
    std::cout << "  Loading audio: " << path << std::endl;
    return soundBuffer.loadFromFile(path);
}

bool FileManager::LoadFont(sf::Font& font, const std::string& path) const {
    std::cout << "  Loading font: " << path << std::endl;    
    return font.loadFromFile(path);
}

std::vector<std::string> FileManager::ListLevelPaths(std::string folder) const {
    std::vector<std::string> paths;
    for(const auto& entry : std::filesystem::directory_iterator(folder)) {
        if(entry.is_regular_file() && entry.path().extension() == "lvl") paths.push_back(entry.path().string());
    }
    return paths;
}

std::vector<Level> FileManager::LoadLevels(std::string path) const {
    std::vector<std::string> paths = ListLevelPaths(path);
    std::vector<Level> levels; Level l;
    for(const auto& p : paths)
        if(LoadLevel(l, p)) levels.push_back(l);

    return levels;
}

std::vector<Level> FileManager::ListLevels() const {
    return LoadLevels(levelPath);
}

std::vector<Level> FileManager::ListEndless() const {
    return LoadLevels(endlessPath);
}


void FileManager::PrintGameObjectData(std::ofstream& file, const gm::GameObjectData& data) const {
    file << "DATA " << data.x << " " << data.y << " " << data.rot << " " << data.type << "\n";
}

void FileManager::PrintHighScores(std::ofstream& file, const std::pair<std::string, int>& score) const {
    file << "HIGH " << score.first << " " << score.second << "\n";
}

bool FileManager::SaveLevel(const Level& level, const std::string& path) const{
    std::ofstream file;
    file.open(path, std::ios::out);
    if (!file.is_open()){
        return false;
    }

    file << "NAME " << level.levelName << "\n";
    file << "MODE " << level.levelMode << "\n";
    
    for(const auto& i : level.objectData){
        PrintGameObjectData(file, i);
    }

    for(const auto& i : level.highscores){
        PrintHighScores(file, i);
    }

    file << "BACKGROUND " << level.backgroundImage << "\n";
    file << "END\n";

    file.close();
    return true;
}

bool FileManager::LoadLevel(Level& level, const std::string& path) const {
    std::ifstream file;
    file.open(path, std::ios::in);
    if (!file.is_open()){
        return false;
    }
    std::string line;
    while(std::getline(file, line)){
        std::istringstream ss(line);
        std::vector<std::string> lineData;
        std::string temp;

        while (std::getline(ss, temp, ' ')){
            lineData.push_back(temp);
        }

        if (lineData[0] == "NAME"){
            level.levelName = lineData[1];
        }   else if (lineData[0] == "MODE"){
            int num = std::stoi(lineData[1]);
            LevelMode mode = static_cast<LevelMode>(num);
            level.levelMode = mode;

        }   else if (lineData[0] == "DATA"){
            gm::GameObjectData object;
            object.x = std::stof(lineData[1]);
            object.y = std::stof(lineData[2]);
            object.rot = std::stof(lineData[3]);
            object.type = static_cast<gm::GameObjectType>(std::stoi(lineData[4]));
            level.objectData.push_back(object);

        }   else if (lineData[0] == "HIGH"){
            std::pair<std::string, int> pair;
            pair.first = lineData[1];
            pair.second = std::stoi(lineData[2]);
            level.highscores.push_back(pair);

        }   else if (lineData[0] == "BACKGROUND"){
            level.backgroundImage = static_cast<SpriteID>(stoi(lineData[1]));
            
        }   else if (lineData[0] == "END"){
            file.close();
            return true;
        }
    }
    file.close();
    return false; //Didn't end in END line, so propably some problems in file
}
#ifndef GAME_BLOCK_HPP
#define GAME_BLOCK_HPP

#include <gameplay/PhysObject.hpp>
#include <gameplay/GameObjectTypes.hpp>

//Basic blocks are 

class Block : public PhysObject {
public:

    Block(Game& game, gm::GameObjectID objectID, float x, float y, float rot) : 
    PhysObject(game, objectID, x, y, rot) {
        blockData_ = gm::blockTypes.at(objectID);
        shapeData_ = gm::shapeProperties.at(blockData_.shape);
        materialData_ = gm::materialProperties.at(blockData_.material);

        

    }

    virtual void Render() {

    }

private:
    gm::BlockData blockData_;
    gm::BlockShapeData shapeData_;
    gm::BlockMaterialData materialData_;

};



#endif
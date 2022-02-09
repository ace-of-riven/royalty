#pragma once

#include "eng_texture.h"
#include "eng_gameobject.h"
#include "eng_mesh.h"

#include <string>

void ClearAllAssets ( ) ;

Texture *ImportTexture ( const std::string& name ) ;
GameObject *ImportGameObject ( const glm::mat4 &transform , const std::string& name , bool fix = false ) ;

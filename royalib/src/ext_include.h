#pragma once

#include <windows.h>

#include "../ext/glew/include/gl/glew.h"

#include "../ext/glm/glm/glm.hpp"
#include "../ext/glm/glm/matrix.hpp"
#include "../ext/glm/glm/gtc/matrix_transform.hpp"
#include "../ext/glm/glm/gtx/transform.hpp"
#include "../ext/glm/glm/gtc/type_ptr.hpp"
#include "../ext/glm/glm/gtx/euler_angles.hpp"
#include "../ext/glm/glm/gtx/matrix_decompose.hpp"
#include "../ext/glm/glm/gtx/quaternion.hpp"
#include "../ext/glm/glm/gtx/rotate_vector.hpp"

#include "../ext/json/include/rapidjson/document.h"
#include "../ext/json/include/rapidjson/writer.h"
#include "../ext/json/include/rapidjson/stringbuffer.h"
#include "../ext/json/include/rapidjson/error/error.h"
#include "../ext/json/include/rapidjson/error/en.h"

#define _CRT_SECURE_NO_WARNINGS
#include <reactphysics3d/reactphysics3d.h>

namespace json = rapidjson;

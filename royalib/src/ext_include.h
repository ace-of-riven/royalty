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

#include "../ext/json/include/rapidjson/document.h"
#include "../ext/json/include/rapidjson/writer.h"
#include "../ext/json/include/rapidjson/stringbuffer.h"
#include "../ext/json/include/rapidjson/error/error.h"
#include "../ext/json/include/rapidjson/error/en.h"

#define _CRT_SECURE_NO_WARNINGS
#include <reactphysics3d/reactphysics3d.h>

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../ext/zlib/zlib.h"

namespace json = rapidjson;

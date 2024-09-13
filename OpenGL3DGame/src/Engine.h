#pragma once

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "RenderEngine/Window.h"
#include "RenderEngine/Loader.h"
#include "RenderEngine/Renderer.h"

#include "Model/Primitive.h"
#include "Model/Model.h"

#include "Entities/Material.h"
#include "Shaders/Shader.h"

#include "Entities/TerrainEntity.h"
#include "Entities/Entity.h"
#include "Entities/Time.h"
#include "Entities/Light.h"

#include "Terrain/Terrain.h"
#include "Terrain/FaultFormationTerrain.h"
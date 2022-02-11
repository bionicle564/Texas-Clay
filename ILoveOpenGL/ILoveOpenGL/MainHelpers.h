#pragma once

#include "GLCommon.h"

//#include "linmath.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> 
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>       // "smart array"
#include <fstream>      // C++ file I-O library (look like any other stream)

#include "VAOManager.h"
#include "Entity.h"
#include "ShaderManager.h"
#include "cBasicTextureManager.h"



void SetUpTextures(cMesh* pCurrentMesh, GLuint shaderProgram, 
    cBasicTextureManager* gTextureManager, float skyboxOffset);

void DrawObject(cMesh* curMesh, glm::mat4 matModel,
    GLint matModel_Location,
    GLint matModelInverseTranspose_Location,
    GLuint program,
    cVAOManager* gVAOManager,
    cBasicTextureManager* gTextureManager,
    float gradualIncrease);
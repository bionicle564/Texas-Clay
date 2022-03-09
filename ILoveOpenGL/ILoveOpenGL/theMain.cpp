#include "GLCommon.h"

//TheMain.cpp
//gian tullo, 0886424
//121221
//does the majority of the open gl stuff

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
#include "Player.h"
#include "TreasureEntity.h"
#include "ShaderManager.h"

#include "LightManager.h"
#include "LightHelper.h"

#include "cFlyCamera.h"
#include "DebugMarker.h"
#include "JsonIOHandler.h"
#include "cBasicTextureManager.h"
#include "MainHelpers.h"
#include "cLoader.h"

// 2 stages: Load file into the RAM, then copy RAM into GPU format
bool LoadPlyFile(std::string fileName);
void CopyStupidPlyFormatToOpenGLNiceFormat(void);

//glm::vec3 cameraEye = glm::vec3(0.0, 0.0, -4.0f);

cFlyCamera flyCamera;
DebugMarker debugMarker;

cVAOManager*     gVAOManager;
cShaderManager  gShaderManager;
cLightManager   gTheLights;
cLightHelper    gTheLightHelper;
cBasicTextureManager* gTextureManager;

JsonIOHandler jsonIO;

Player* player;

//std::vector<cMesh> g_vecMeshes;
std::vector<Entity*> world;
std::vector<Entity*> sprites;
std::vector<Entity*> templates;
std::vector<Entity*> particles;
std::vector<Command> anims;

int currentAnimFrame = 0;
float gradualIncrease = 0.0f;
float cameraAngle = 0.0f;

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


//void AttemptToGoToNextFrame() {
//    //check to see if stuff is still executing
//    bool stillExecuting = false;
//    for (int i = 0; i < entities.size(); i++) { stillExecuting |= entities[i]->executing; }
//    if (!stillExecuting) {//the last frame is done, so we can get to business
//
//        currentAnimFrame++;
//        for (int i = 0; i < anims.size(); i++) {
//            //load the the models with the animations for this frame
//            if (anims[i].batch == currentAnimFrame) {
//                for (int j = 0; j < entities.size(); j++) {
//
//                    //find the right models for the animation
//                    if (entities[j]->mesh->nameID == anims[i].owner) {
//                        if (anims[i].dispatch == "parallel") { entities[j]->RegisterParallel(anims[i]); }
//                        if (anims[i].dispatch == "serial") { entities[j]->RegisterSerial(anims[i]); }
//                    }
//                }
//            }
//        }
//
//        //have each model start executing it's commands
//        //!For each batch, the model can only have set of paralells or a set of serials, NOT both
//        for (int i = 0; i < entities.size(); i++) {
//            entities[i]->ExecNextParallel();
//            entities[i]->ExecSerial();
//        }
//
//    }
//
//}

bool up = false;
bool down = false;
bool left = false;
bool right = false;
bool space = false;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    //float cameraSpeed = 0.1f;

    // Basic camera controls
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        //cameraEye.x -= cameraSpeed;     // Go left
        //flyCamera.MoveLeftRight_X(-flyCamera.movementSpeed);
        //player->MoveLeft();
        left = true;
    }
    else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
    {
        left = false;
    }


    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        //cameraEye.x += cameraSpeed;     // Go right
        //flyCamera.MoveLeftRight_X(flyCamera.movementSpeed);
        //player->MoveRight();
        right = true;
    }
    else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
    {
        right = false;
    }


    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        //cameraEye.z += cameraSpeed;     // Go forward
        //flyCamera.MoveForward_Z(flyCamera.movementSpeed);
        //player->MoveFoward();
        up = true;
    }
    else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
    {
        up = false;
    }


    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        //cameraEye.z -= cameraSpeed;     // Go backwards
        //flyCamera.MoveForward_Z(-flyCamera.movementSpeed);
        //player->MoveBackward();
        down = true;
    }
    else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
    {
        down = false;
    }


    if (key == GLFW_KEY_Q)
    {
        //cameraEye.y -= cameraSpeed;     // Go "Down"
        //flyCamera.MoveUpDown_Y(-flyCamera.movementSpeed);
        cameraAngle += 0.03f;
        if (cameraAngle > 3.14f) { cameraAngle -= 6.28;  }
        
    }
    if (key == GLFW_KEY_E)
    {
        //cameraEye.y += cameraSpeed;     // Go "Up"
        //flyCamera.MoveUpDown_Y(flyCamera.movementSpeed);
        cameraAngle -= 0.03f;
        if (cameraAngle < -3.14f) { cameraAngle += 6.28f; }
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        
        space = true;
    }
    else if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
    {
        space = false;
    }

    /*if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        AttemptToGoToNextFrame();
    }*/

    
    if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
        gTheLights.SaveLightInformationToFile("testLights.txt");
    }

    if (key == GLFW_KEY_9 && action == GLFW_PRESS)
    {
        gTheLights.LoadLightInformationFromFile("testLights.txt");
        gTheLights.CopyLightInfoToShader();
    }


    

    /*std::cout << "Camera: "
        << flyCamera.getAtInWorldSpace().x << ", "
        << flyCamera.getAtInWorldSpace().y << ", "
        << flyCamera.getAtInWorldSpace().z << std::endl;*/
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        std::cout << "\tglick." << std::endl;
    }
}





//-------------------
//
// THE MAIN
// 
int main(void)
{
    GLFWwindow* window;
    GLuint program = 0;     // 0 means "no shader program"
    GLint mvp_location = -1;

    gTextureManager = new cBasicTextureManager();
    gVAOManager = new cVAOManager();

    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(1280, 640, "GAME DEMO", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwMakeContextCurrent(window);
    // Tiny change from the original documentation code
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    //    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    // NOTE: OpenGL error checks have been omitted for brevity

    cShaderManager::cShader vertShader;
    vertShader.fileName = "assets/shaders/vertShader_01.glsl";

    cShaderManager::cShader fragShader;
    fragShader.fileName = "assets/shaders/fragShader_01.glsl";

    if (gShaderManager.createProgramFromFile("Shader#1", vertShader, fragShader))
    {
        std::cout << "Shader compiled OK" << std::endl;
        // 
        // Set the "program" variable to the one the Shader Manager used...
        program = gShaderManager.getIDFromFriendlyName("Shader#1");
    }
    else
    {
        std::cout << "Error making shader program: " << std::endl;
        std::cout << gShaderManager.getLastError() << std::endl;
    }

    //test this
    glUseProgram(program);

    mvp_location = glGetUniformLocation(program, "MVP");
    // Get "uniform locations" (aka the registers these are in)
    GLint matModel_Location = glGetUniformLocation(program, "matModel");
    GLint matView_Location = glGetUniformLocation(program, "matView");
    GLint matProjection_Location = glGetUniformLocation(program, "matProjection");
    GLint matModelInverseTranspose_Location = glGetUniformLocation(program, "matModelInverseTranspose");

    flyCamera.setEye(glm::vec3(0.0f, 3.5f, -12.5f));



    //loads from external .txt file now
    gTheLights.SetUpUniformLocations(program);
    gTheLights.LoadLightInformationFromFile("testLights.txt");
    gTheLights.CopyLightInfoToShader();

    //easier to read and load models, just add to this vector
    std::vector<std::string> modelNames;
    modelNames.push_back("bun_zipper_res4_xyz_n_rgb.ply");
    modelNames.push_back("debug_triangle.ply");
    modelNames.push_back("Ground.ply");
    modelNames.push_back("SpriteHolder.ply");
    modelNames.push_back("Isosphere_Smooth_Inverted_Normals_for_SkyBox.ply");

    for (int i = 0; i < modelNames.size(); i++)
    {
        sModelDrawInfo tempInfo;
        //    if (gVAOManager.LoadModelIntoVAO("bun_zipper_res2 (justXYZ).ply", modelBunny, program))
        if (gVAOManager->LoadModelIntoVAO(modelNames[i], tempInfo, program))
        {
            std::cout << "Loaded the model: " << tempInfo.meshName << std::endl;
            std::cout << tempInfo.numberOfVertices << " vertices loaded" << std::endl;
            std::cout << tempInfo.numberOfTriangles << " triangles loaded" << std::endl;
        }
        else
        {
            std::cout << "Error: Didn't load the model OK" << std::endl;
        }
    }
    


    cMesh* debug = new cMesh();
    debug->meshName = "debug_triangle.ply";
    debug->bDontLight = true;
    debug->bIsWireframe = true;

    debugMarker.debugMesh = debug;

    //for this scene we will need
    //1x room
    cMesh* room = new cMesh();
    room->meshName = "Ground.ply";
    //room->orientationXYZ.x = -1.57f;
    //room->orientationXYZ.y = 1.57f;

    cMesh* dude = new cMesh();
    dude->meshName = "SpriteHolder.ply";
    dude->positionXYZ.y = 10.f;
    dude->orientationXYZ.y = -1.57f;
    dude->orientationXYZ.x = -1.57;
    dude->bDontLight = true;

    cMesh* goal1 = new cMesh();
    goal1->meshName = "SpriteHolder.ply";
    goal1->scale = 0.5f;
    goal1->positionXYZ = glm::vec3(10.0f, 0.0f, 10.5f);
    goal1->orientationXYZ.y = -1.57f;
    goal1->orientationXYZ.x = -1.57f;
    goal1->bDontLight = true;

    cMesh* goal2 = new cMesh();
    goal2->meshName = "SpriteHolder.ply";
    goal2->scale = 0.5f;
    goal2->positionXYZ = glm::vec3(-8.0f, 0.0f, 10.5f);
    goal2->orientationXYZ.y = -1.57f;
    goal2->orientationXYZ.x = -1.57f;
    goal2->bDontLight = true;


    // Create a skybox object (a sphere with inverted normals that moves with the camera eye)
    cMesh* pSkyBox = new cMesh();
    pSkyBox->meshName = "Isosphere_Smooth_Inverted_Normals_for_SkyBox.ply";
    pSkyBox->scale = flyCamera.nearPlane * 1000.0f;
    pSkyBox->positionXYZ = flyCamera.getEye();

    Entity* skyBoxEntity = new Entity(pSkyBox);
    world.push_back(skyBoxEntity);

    Entity* groundEntity = new Entity(room);
    world.push_back(groundEntity);

    player = new Player(dude);
    sprites.push_back(player);

    Entity* goal1Entity = new TreasureEntity(goal1, 0.5f, player);
    sprites.push_back(goal1Entity);

    Entity* goal2Entity = new TreasureEntity(goal2, 0.5f, player);
    sprites.push_back(goal2Entity);


    //jsonIO.ReadManyModels("SceneModels.json", entities);

    //flyCamera.setEye(dudeEntity->mesh->positionXYZ);

    GLint glMaxCombinedTextureImageUnits = 0;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &glMaxCombinedTextureImageUnits);
    std::cout << "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS = " << glMaxCombinedTextureImageUnits << std::endl;

    GLint glMaxVertexTextureImageUnits = 0;
    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &glMaxVertexTextureImageUnits);
    std::cout << "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS = " << glMaxVertexTextureImageUnits << std::endl;

    GLint glMaxTextureSize = 0;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &glMaxTextureSize);
    std::cout << "GL_MAX_TEXTURE_SIZE = " << glMaxTextureSize << std::endl;

    //texture loading
    gTextureManager->SetBasePath("assets/textures");

    cLoader texLoader;
    texLoader.LoadTextureNames(gTextureManager);
    

    //texture assignment

    //floor
    world[1]->mesh->textureNames[0] = "futurebrick.bmp";
    world[1]->mesh->textureRatios[0] = 1.0f;
    sprites[0]->mesh->textureNames[0] = "TexasClayFront1.bmp";
    sprites[0]->mesh->textureRatios[0] = 1.0f;
    sprites[1]->mesh->textureNames[0] = "Coins.bmp";
    sprites[1]->mesh->textureRatios[0] = 1.0f;
    sprites[2]->mesh->textureNames[0] = "Crown.bmp";
    sprites[2]->mesh->textureRatios[0] = 1.0f;


    // Add a skybox texture
    std::string errorTextString;
    if (!gTextureManager->CreateCubeTextureFromBMPFiles("Skybox",
        "stoneBoxSide.bmp",    /* posX_fileName */
        "stoneBoxSide.bmp",     /*negX_fileName */
        "stoneBoxBot.bmp",     /*posY_fileName*/
        "stoneBoxTop.bmp",       /*negY_fileName*/
        "stoneBoxSide.bmp",     /*posZ_fileName*/
        "stoneBoxSide.bmp",    /*negZ_fileName*/
        true, errorTextString))
    {
        std::cout << "Didn't load because: " << errorTextString << std::endl;
    }
    else
    {
        std::cout << "Loaded the skybox cube texture OK" << std::endl;
    }

    if (!gTextureManager->CreateCubeTextureFromBMPFiles("Daybox",
        "side1_2.bmp",    /* posX_fileName */
        "side2_2.bmp",     /*negX_fileName */
        "ground_2.bmp",     /*posY_fileName*/
        "sky_2.bmp",       /*negY_fileName*/
        "side3_2.bmp",     /*posZ_fileName*/
        "side4_2.bmp",    /*negZ_fileName*/
        true, errorTextString))
    {
        std::cout << "Didn't load because: " << errorTextString << std::endl;
    }
    else
    {
        std::cout << "Loaded the skybox cube texture OK" << std::endl;
    }

    std::cout << "I've loaded these textures:" << std::endl;
    std::vector<std::string> vecTexturesLoaded;
    gTextureManager->GetLoadedTextureList(vecTexturesLoaded);

    for (std::vector<std::string>::iterator itTexName = vecTexturesLoaded.begin();
        itTexName != vecTexturesLoaded.end(); itTexName++)
    {
        std::cout << "\t" << *itTexName << std::endl;
    }


    //texture end
    

    //time to set up camera stuff
    glm::vec3 cameraPos(0.0f);
    cameraPos.x = player->mesh->positionXYZ.x;
    cameraPos.y = player->mesh->positionXYZ.y + 2.5f;
    cameraPos.z = player->mesh->positionXYZ.z - 10.0f;
    flyCamera.setEye(cameraPos);

    float distance = glm::distance(player->mesh->positionXYZ, flyCamera.eye);
    
    float lastCameraAngle = cameraAngle;

    const double MAX_DELTA_TIME = 0.1;  // 100 ms
    double previousTime = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glm::mat4 matModel;    // used to be "m"; Sometimes it's called "world"
        glm::mat4 p;
        glm::mat4 v;
        glm::mat4 mvp;
        //        mat4x4 m, p, mvp;

        double currentTime = glfwGetTime();
        double deltaTime = currentTime - previousTime;
        deltaTime = (deltaTime > MAX_DELTA_TIME ? MAX_DELTA_TIME : deltaTime);
        previousTime = currentTime;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;

        // Turn on the depth buffer
        glEnable(GL_DEPTH);         // Turns on the depth buffer
        glEnable(GL_DEPTH_TEST);    // Check if the pixel is already closer

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //======================
        //    async controls
        //======================

        if (up)
        {
            player->MoveFoward();
        }

        if (down)
        {
            player->MoveBackward();
        }

        if (left)
        {
            player->MoveLeft();
        }

        if (right)
        {
            player->MoveRight();
        }

        if (space)
        {
            player->Jump();
            space = false;
        }



        // *******************************************************
        // Screen is cleared and we are ready to draw the scene...
        // *******************************************************

        //Calcs for arcball camera and Movement
        player->Update(deltaTime); 
        glm::vec3 direction = flyCamera.eye - player->mesh->positionXYZ;
        glm::vec3 newCameraPos(0.0f);
        //position = (Rotate(some other angle, (0, 1, 0)) * (position - target)) + target;
        newCameraPos = (glm::angleAxis(lastCameraAngle - cameraAngle, glm::vec3(0, 1, 0)) * direction) + player->mesh->positionXYZ;      
  
        float curDistance = glm::distance(player->mesh->positionXYZ, flyCamera.eye);

        if (curDistance != distance) {
            // Calculate the normal.
            glm::vec3 normal = player->mesh->positionXYZ - flyCamera.eye;
            normal = glm::normalize(normal);
            // The contact normal depends on whether we’re extending
            // or compressing.
            float penetration = 0.0f;
            if (curDistance > distance) {
                penetration = curDistance - distance;
            }
            else {
                normal *= -1.0f;
                penetration = distance - curDistance;
            }

            glm::vec3 resolveMove = normal * penetration;
            newCameraPos += resolveMove;

            newCameraPos.y = player->mesh->positionXYZ.y + 2.5f;
        }


        flyCamera.setEye(newCameraPos);
        flyCamera.setAt(player->mesh->positionXYZ);
        //move the skybox
        world[0]->mesh->positionXYZ = flyCamera.getEye();
        //cameraAngle = 0.0f;

        //Arcball end

        //make anything in the sprites list always face the camera
        for (int i = 0; i < sprites.size(); i++) {
            glm::vec2 spritePos(sprites[i]->mesh->positionXYZ.x, sprites[i]->mesh->positionXYZ.z);
            glm::vec2 camPos(newCameraPos.x, newCameraPos.z);

            glm::vec2 direction2D = spritePos - camPos;
            direction2D = glm::normalize(direction2D);

            //angle = cosInv(a dot b/a.lenght * b.length)
            float dotProduct = direction2D.x * 0.0f + direction2D.y * 1.0f;
            float angle = acosf(dotProduct);

            if (direction2D.x < 0.0f) {
                angle *= -1.0f;
            }
            
            sprites[i]->mesh->orientationXYZ.y = angle - 1.57f;
        }
        lastCameraAngle = cameraAngle;
        //sprite facing end

        gTheLights.CopyLightInfoToShader();

        p = glm::perspective(
            flyCamera.FOV,
            ratio,
            flyCamera.nearPlane,      // Near plane (as large as possible)
            flyCamera.farPlane);      // Far plane (as small as possible)

        flyCamera.Update(deltaTime);

        glm::vec3 cameraEye = flyCamera.getEye();
        glm::vec3 cameraAt = player->mesh->positionXYZ;
        glm::vec3 cameraUp = flyCamera.getUpVector();


        v = glm::mat4(1.0f);
        v = glm::lookAt(cameraEye,   // "eye"
            cameraAt,    // "at"
            cameraUp);

        glUniformMatrix4fv(matView_Location, 1, GL_FALSE, glm::value_ptr(v));
        glUniformMatrix4fv(matProjection_Location, 1, GL_FALSE, glm::value_ptr(p));

       

        

        // Ordering the objects by transparency
        // 1. Make two arrays or vectors
        // 2. Clear them
        // 3. Go through all your "things to draw", separating transparent from non-transparent
        //    (if the alpha < 1.0f, then it's "transparent" )
        // 3a. glDisable(GL_BLEND);
        // 4. Draw all the NON transparent things (in any order you want)
        // 5. Sort ONLY the transparent object from "far" to "close" for THIS frame
        //     glm::distance() to compare 
        //     Can be ONE PASS of the bubble sort
        // 5a. glEnable(GL_BLEND);
        // 6. Draw transparent objects from FAR to CLOSE


        // Set up the discard texture, etc.
        
        //for world objects
        for (unsigned int index = 0; index != world.size(); index++)
        {
            //world[index]->Process();

            // So the code is a little easier...
            cMesh* curMesh = world[index]->mesh;

            GLint bIsSkyBox_LocID;
            if (index == 0) { //skybox
                 // *********************************************************************
        //    ____  _            ____             
        //   / ___|| | ___   _  | __ )  _____  __ 
        //   \___ \| |/ / | | | |  _ \ / _ \ \/ / 
        //    ___) |   <| |_| | | |_) | (_) >  <  
        //   |____/|_|\_\\__, | |____/ \___/_/\_\ 
        //               |___/                    
        //
        // Since this is a space game (most of the screen is filled with "sky"), 
        //  I'll draw the skybox first
        // 
        // This is updated to the "proper" way to do a skybox. 
        // Here's how:
        // 1. Turn off the depth function AND depth test
        // 2. Draw the skybox - it doesn't matter how big it is, since it's the 1st thing being drawn.
        //    Since I'm NOT writing to the depth buffer, it's written to the colour buffer 
        //    (i.e. we can see it), but anything drawn later doesn't "know" that's happened, 
        //    so all the other objects draw "on top" of it (on the colour buffer)
        // 
                bIsSkyBox_LocID = glGetUniformLocation(program, "bIsSkyBox");
                glUniform1f(bIsSkyBox_LocID, (GLfloat)GL_TRUE);

                glDisable(GL_DEPTH_TEST);
                // Move the "skybox object" with the camera
                


            }

            {
                GLint bDiscardTransparencyWindowsOn_LodID = glGetUniformLocation(program, "bDiscardTransparencyWindowsOn");
                // Turn discard transparency off
                glUniform1f(bDiscardTransparencyWindowsOn_LodID, (GLfloat)GL_FALSE);

                if (curMesh->meshName == "SpriteHolder.ply")
                {
                    //                GLuint discardTextureNumber = ::g_pTextureManager->getTextureIDFromName("Lisse_mobile_shipyard-mal1.bmp");
                    GLuint discardTextureNumber = gTextureManager->getTextureIDFromName(curMesh->textureNames[0]);
                    // I'm picking texture unit 30 since it's not in use.
                    GLuint discardTextureUnit = 30;			// Texture unit go from 0 to 79
                    glActiveTexture(discardTextureUnit + GL_TEXTURE0);	// GL_TEXTURE0 = 33984
                    glBindTexture(GL_TEXTURE_2D, discardTextureNumber);
                    GLint discardTexture_LocID = glGetUniformLocation(program, "discardTexture");
                    glUniform1i(discardTexture_LocID, discardTextureUnit);

                    // Turn discard function on
                    glUniform1f(bDiscardTransparencyWindowsOn_LodID, (GLfloat)GL_TRUE);
                }
            }

            matModel = glm::mat4(1.0f);  // "Identity" ("do nothing", like x1)
            //mat4x4_identity(m);

            // Alpha transparency
            glEnable(GL_BLEND);
            // Basic "alpha transparency"
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            if (index < 19) { glDisable(GL_BLEND); } //if we're not at the transparent stuff, don't actully blend

            DrawObject(curMesh, matModel, matModel_Location, matModelInverseTranspose_Location, program,
                gVAOManager, gTextureManager, gradualIncrease);

            if (index == 0) { //skybox
                glUniform1f(bIsSkyBox_LocID, (GLfloat)GL_FALSE);
                //
                glEnable(GL_DEPTH_TEST);
                // *********************************************************************
            }
        }

        //for sprites
        for (unsigned int index = 0; index != sprites.size(); index++)
        {
            sprites[index]->Process();

            // So the code is a little easier...
            cMesh* curMesh = sprites[index]->mesh;

            {
                GLint bDiscardTransparencyWindowsOn_LodID = glGetUniformLocation(program, "bDiscardTransparencyWindowsOn");
                // Turn discard transparency off
                glUniform1f(bDiscardTransparencyWindowsOn_LodID, (GLfloat)GL_FALSE);

                if (curMesh->meshName == "SpriteHolder.ply")
                {
                    //                GLuint discardTextureNumber = ::g_pTextureManager->getTextureIDFromName("Lisse_mobile_shipyard-mal1.bmp");
                    GLuint discardTextureNumber = gTextureManager->getTextureIDFromName(curMesh->textureNames[0]);
                    // I'm picking texture unit 30 since it's not in use.
                    GLuint discardTextureUnit = 30;			// Texture unit go from 0 to 79
                    glActiveTexture(discardTextureUnit + GL_TEXTURE0);	// GL_TEXTURE0 = 33984
                    glBindTexture(GL_TEXTURE_2D, discardTextureNumber);
                    GLint discardTexture_LocID = glGetUniformLocation(program, "discardTexture");
                    glUniform1i(discardTexture_LocID, discardTextureUnit);

                    // Turn discard function on
                    glUniform1f(bDiscardTransparencyWindowsOn_LodID, (GLfloat)GL_TRUE);
                }
            }

            matModel = glm::mat4(1.0f);  // "Identity" ("do nothing", like x1)
            //mat4x4_identity(m);

            // Alpha transparency
            glEnable(GL_BLEND);
            // Basic "alpha transparency"
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            if (index < 19) { glDisable(GL_BLEND); } //if we're not at the transparent stuff, don't actully blend

            DrawObject(curMesh, matModel, matModel_Location, matModelInverseTranspose_Location, program,
                gVAOManager, gTextureManager, gradualIncrease);

        }



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    for (int i = world.size() - 1; i >= 0; i--) {
        delete world[i];
    }
    for (int i = sprites.size() - 1; i >= 0; i--) {
        delete sprites[i];
    }
    for (int i = templates.size() - 1; i >= 0; i--) {
        delete templates[i];
    }
    for (int i = particles.size() - 1; i >= 0; i--) {
        delete particles[i];
    }
    
    delete gTextureManager;
    delete gVAOManager;

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

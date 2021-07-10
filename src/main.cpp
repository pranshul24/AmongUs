#include "main.h"
#include "timer.h"
#include "player.h"
#include "coin.h" //coin
#include "buttonThings.h"
#include "buttonVapour.h"
#include "imposter.h"
#include "bomb.h"
#include "dynamite.h"
#include "hudBox.h"
#include "heart.h"
#include "grid.h"
#include "gridBox.h"
#include <time.h>
#include "cell.h"
#include <ft2build.h>
#include FT_FREETYPE_H

using namespace std;

GLMatrices Matrices;
int ambientStrengthID;
GLuint programID;
GLuint programID2;
GLFWwindow *window;
int viewPosID;
// PentagonalCupola fig3;
Player player;
Imposter imposter;
GridBox gridBox;
Grid grid;
HudBox hud;
ButtonThings button1;
ButtonVapour buttonV;
int fragPosId, PlayerPosID, specularStrengthID;
int selectedFig = 0;
int timeup = 0;
int ButtonVapourCellNum;
int ButtonThingsCellNum;
vector<int> thingsCellNumArr;
int imposterNextIdx = -1;
int spinAboutAxis = 0;
int noAffectOnInput = 0;
int UpdPos = 0;
float rotateRadius = 0.0;
char lastKey = 'P';
char toBeNextKey = 'P';
int buttonTRem = 0;
int buttonVRem = 0;
int imposterMet = 0;
int gateOpen = 0;
vector<Bomb> bombArr;
vector<Coin> coinArr;
vector<Heart> heartArr;
vector<Dynamite> dynamiteArr;
unsigned int VAOint, VBOint;
int won = 0;
int health = 0;
int completedTask = 0;
int lightSituation = 1; //1 implies on
int countdown = 40;
int canExit = 0;
int avoidLeft = 0;
int avoidRight = 0;
int avoidUp = 0;
int avoidDown = 0;
float ImoveX = 0;
float ImoveY = 0;
float ImoveZ = 0;
vector<int> cellIdxArr;
int showAll = 1;
Timer t60(1.0 / 60);
glm::vec3 CameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 CameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::mat4 projection;
void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);

struct Character
{
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2 Size;        // Size of glyph
    glm::ivec2 Bearing;     // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};
std::map<GLchar, Character> Characters;

void draw()
{
    // clear the color and depth in the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram(programID);

    //create view matrix
    Matrices.view = glm::lookAt(CameraPos, CameraTarget, up);

    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP; // MVP = Projection * View * Model
    // glm::vec3 fragPos = glm::vec3(0.7f, 0.7f, 0.7f);
    glUniform3f(viewPosID, player.position[0], player.position[1] + 2.0f, player.position[2] - 9.0f);
    glUniform3f(PlayerPosID, player.position[0], player.position[1], 1.0);

    // Scene render
    // if (selectedFig == 1)
    // {
    // fig1.draw(VP, spinAboutAxis);
    if (lightSituation == 1)
    {
        glUniform1f(ambientStrengthID, 1.0f);
        glUniform1f(specularStrengthID, 0.0);
    }
    else
    {
        glUniform1f(ambientStrengthID, 0.1f);
        glUniform1f(specularStrengthID, 0.7);
    }
    if (won == 1 || imposterMet == 1 || timeup == 1)
    {
        glUniform1f(ambientStrengthID, 1.0f);
        glUniform1f(specularStrengthID, 0.0);
    }
    if (won == 0 && imposterMet == 0 && timeup == 0)
    {
        gridBox.draw(VP);
    }
    // glUniform1f(specularStrengthID, 0.0);

    grid.draw(VP);
    player.draw(VP, spinAboutAxis);
    if (buttonVRem == 0)
        imposter.draw(VP, spinAboutAxis);
    if (buttonTRem == 0)
        button1.draw(VP, spinAboutAxis);
    if (buttonVRem == 0)
        buttonV.draw(VP, spinAboutAxis);
    if (buttonTRem == 1)
    {
        for (int tem = 0; tem < bombArr.size(); tem++)
        {
            bombArr[tem].draw(VP, spinAboutAxis);
        }
        for (int tem = 0; tem < heartArr.size(); tem++)
        {
            heartArr[tem].draw(VP, spinAboutAxis);
        }
        for (int tem = 0; tem < dynamiteArr.size(); tem++)
        {
            dynamiteArr[tem].draw(VP, spinAboutAxis);
        }
        for (int tem = 0; tem < coinArr.size(); tem++)
        {
            coinArr[tem].draw(VP, spinAboutAxis);
        }
    }
    glUniform1f(ambientStrengthID, 1.0f);
    glUniform1f(specularStrengthID, 0.0);
    hud.draw(VP, spinAboutAxis);
    string healthStr = "Health/Score : " + to_string(health);
    string lightStr = "Light Status : ";
    string countdownStr = "Time Remaining : " + to_string(countdown);
    string completedTaskStr = "Task Completed : " + to_string(completedTask);
    if (lightSituation == 0)
    {
        lightStr += "Off";
    }
    else
    {
        lightStr += "On";
    }
    RenderText(healthStr, 21.0f, 650.0f, 0.40f, glm::vec3(0.9, 0.9f, 0.75f));
    RenderText(lightStr, 21.0f, 620.0f, 0.40f, glm::vec3(0.9, 0.9f, 0.75f));
    RenderText(countdownStr, 21.0f, 590.0f, 0.40f, glm::vec3(0.9, 0.9f, 0.75f));
    RenderText(completedTaskStr, 21.0f, 560.0f, 0.40f, glm::vec3(0.9, 0.9f, 0.75f));
    if (timeup == 1)
    {
        RenderText("Time Up !", 575.0f, 390.0f, 0.8f, glm::vec3(0.9, 0.9f, 0.75f));
        RenderText("You Lost !", 565.0f, 350.0f, 0.9f, glm::vec3(0.3, 0.1f, 0.0f));
        RenderText("Press 'Q' to exit ...", 520.0f, 310.0f, 0.6f, glm::vec3(0.8, 0.9f, 0.3f));
    }
    if (gateOpen == 1)
    {
        RenderText("Exit gate open !", 21.0f, 530.0f, 0.40f, glm::vec3(0.9, 0.5f, 0.75f));
    }
    if (imposterMet == 1)
    {
        RenderText("You Lost !", 565.0f, 350.0f, 1.0f, glm::vec3(0.3, 0.1f, 0.0f));
        RenderText("Press 'Q' to exit ...", 520.0f, 310.0f, 0.6f, glm::vec3(0.8, 0.9f, 0.3f));
    }
    if (won == 1)
    {
        RenderText("You Won !", 565.0f, 350.0f, 1.0f, glm::vec3(0.3, 0.1f, 0.0f));
        RenderText("Press 'Q' to exit ...", 520.0f, 310.0f, 0.6f, glm::vec3(0.8, 0.9f, 0.3f));
    }
}

void openGate()
{
    grid.cells[grid.width - 1].walls[0] = 0;
}

void OnButtonVCollision()
{
    completedTask += 1;
    buttonVRem = 1;
}

void OnButtonTCollision()
{
    buttonTRem = 1;
    completedTask += 1;
    int IcellNum = grid.imposterPosCell(imposter.position[0], imposter.position[1]);
    int PcellNum = grid.playerPosCell(player.position[0], player.position[1]);

    for (int i = 0; i < 1 + rand() % 4; i++)
    {
        int cellNum = rand() % grid.cells.size();
        for (int v = 0; v < 20; v++)
        {
            int tem = rand() % grid.cells.size();
            if ((tem / 17 == 0 && tem % 17 == 16) || tem / 17 == 11)
                continue;
            int toEx = 0;
            for (int var = 0; var < thingsCellNumArr.size(); var++)
            {
                if (tem == thingsCellNumArr[var])
                {
                    toEx = 1;
                    break;
                }
            }
            if (toEx == 1)
                continue;

            if ((tem != IcellNum || tem != IcellNum + grid.width || tem != IcellNum + 1) and (tem != PcellNum || tem != PcellNum + grid.width || tem != PcellNum + 1) and tem != ButtonThingsCellNum and tem != ButtonVapourCellNum)
            {
                cellNum = tem;
                break;
            }
        }
        float Tx = grid.cells[cellNum].posX + 0.35;
        float Ty = grid.cells[cellNum].posY - 0.35;
        bombArr.push_back(Bomb(Tx, Ty, -11));
        thingsCellNumArr.push_back(cellNum);
    }
    for (int i = 0; i < 3 + rand() % 6; i++)
    {
        int cellNum = rand() % grid.cells.size();
        for (int v = 0; v < 20; v++)
        {
            int tem = rand() % grid.cells.size();
            if ((tem / 17 == 0 && tem % 17 == 16) || tem / 17 == 11)
                continue;
            int toEx = 0;
            for (int var = 0; var < thingsCellNumArr.size(); var++)
            {
                if (tem == thingsCellNumArr[var])
                {
                    toEx = 1;
                    break;
                }
            }
            if (toEx == 1)
                continue;

            if ((tem != IcellNum || tem != IcellNum + grid.width || tem != IcellNum + 1) and (tem != PcellNum || tem != PcellNum + grid.width || tem != PcellNum + 1) and tem != ButtonThingsCellNum and tem != ButtonVapourCellNum)
            {
                cellNum = tem;
                break;
            }
        }
        float Tx = grid.cells[cellNum].posX + 0.35;
        float Ty = grid.cells[cellNum].posY - 0.35;
        heartArr.push_back(Heart(Tx, Ty, -11));
        thingsCellNumArr.push_back(cellNum);
    }
    for (int i = 0; i < 1 + rand() % 4; i++)
    {
        int cellNum = rand() % grid.cells.size();
        for (int v = 0; v < 20; v++)
        {
            int tem = rand() % grid.cells.size();
            if ((tem / 17 == 0 && tem % 17 == 16) || tem / 17 == 11)
                continue;
            int toEx = 0;
            for (int var = 0; var < thingsCellNumArr.size(); var++)
            {
                if (tem == thingsCellNumArr[var])
                {
                    toEx = 1;
                    break;
                }
            }
            if (toEx == 1)
                continue;

            if ((tem != IcellNum || tem != IcellNum + grid.width || tem != IcellNum + 1) and (tem != PcellNum || tem != PcellNum + grid.width || tem != PcellNum + 1) and tem != ButtonThingsCellNum and tem != ButtonVapourCellNum)
            {
                cellNum = tem;
                break;
            }
        }
        float Tx = grid.cells[cellNum].posX + 0.35;
        float Ty = grid.cells[cellNum].posY - 0.35;
        dynamiteArr.push_back(Dynamite(Tx, Ty, -11));
        thingsCellNumArr.push_back(cellNum);
    }
    for (int i = 0; i < 3 + rand() % 8; i++)
    {
        int cellNum = rand() % grid.cells.size();
        for (int v = 0; v < 20; v++)
        {
            int tem = rand() % grid.cells.size();
            if ((tem / 17 == 0 && tem % 17 == 16) || tem / 17 == 11)
                continue;
            int toEx = 0;
            for (int var = 0; var < thingsCellNumArr.size(); var++)
            {
                if (tem == thingsCellNumArr[var])
                {
                    toEx = 1;
                    break;
                }
            }
            if (toEx == 1)
                continue;

            if ((tem != IcellNum || tem != IcellNum + grid.width || tem != IcellNum + 1) and (tem != PcellNum || tem != PcellNum + grid.width || tem != PcellNum + 1) and tem != ButtonThingsCellNum and tem != ButtonVapourCellNum)
            {
                cellNum = tem;
                break;
            }
        }
        float Tx = grid.cells[cellNum].posX + 0.35;
        float Ty = grid.cells[cellNum].posY - 0.35;
        coinArr.push_back(Coin(Tx, Ty, -11));
        thingsCellNumArr.push_back(cellNum);
    }
}

void checkCollision()
{
    float Px = player.position[0];
    float Py = player.position[1];
    float cellLen = 0.7f;
    // cout << Px << " " << Py << "\n";
    int cellNum = grid.playerPosCell(Px, Py);
    if (imposterMet == 0 && buttonVRem == 0)
    {
        float Ix = imposter.position[0];
        float Iy = imposter.position[1];
        if (Ix + cellLen > Px + 0.2f and Ix < Px + cellLen - 0.2f and Iy + cellLen > Py + 0.2f and Py + cellLen - 0.2f > Iy)
        {
            imposterMet = 1;
            ImoveX = 0;
            ImoveY = 0;
            if (lightSituation == 0)
                health -= (200 - 4 * (40 - countdown)) / 2;
            else
            {
                health -= 200 - 4 * (40 - countdown);
            }
            return;
        }
    }
    if (buttonTRem == 0)
    {
        if (cellNum == grid.playerPosCell(button1.position[0], button1.position[1]))
        {
            OnButtonTCollision();
            if (lightSituation == 1)
                health += 250 - 3 * (40 - countdown);
            else
            {
                health += 2 * (250 - 3 * (40 - countdown));
            }
            return;
        }
    }
    if (buttonVRem == 0)
    {
        if (cellNum == grid.playerPosCell(buttonV.position[0], buttonV.position[1]))
        {
            OnButtonVCollision();
            if (lightSituation == 1)
                health += 300 - 5 * (40 - countdown);
            else
            {
                health += 2 * (300 - 5 * (40 - countdown));
            }
            return;
        }
    }
    if (buttonTRem == 1)
    {
        for (int tem = 0; tem < bombArr.size(); tem++)
        {
            // cout << cellNum << " " << grid.playerPosCell(bombArr[tem].position[0], bombArr[tem].position[1]) << "\n";
            //playerposcell is generic just name as player pos cell
            if (cellNum == grid.playerPosCell(bombArr[tem].position[0], bombArr[tem].position[1]))
            {
                bombArr.erase(bombArr.begin() + tem);
                if (lightSituation == 1)
                    health -= 100;
                else
                {
                    health -= 100 / 2;
                }
                return;
            }
        }
        for (int tem = 0; tem < coinArr.size(); tem++)
        {
            //playerposcell is generic just name as player pos cell
            if (cellNum == grid.playerPosCell(coinArr[tem].position[0], coinArr[tem].position[1]))
            {
                coinArr.erase(coinArr.begin() + tem);
                if (lightSituation == 1)
                    health += 30 + countdown;
                else
                {
                    health += 2 * (30 + countdown);
                }
                return;
            }
        }
        for (int tem = 0; tem < dynamiteArr.size(); tem++)
        {
            //playerposcell is generic just name as player pos cell
            if (cellNum == grid.playerPosCell(dynamiteArr[tem].position[0], dynamiteArr[tem].position[1]))
            {
                dynamiteArr.erase(dynamiteArr.begin() + tem);
                if (lightSituation == 1)
                    health -= 50;
                else
                {
                    health -= 50 / 2;
                }
                return;
            }
        }
        for (int tem = 0; tem < heartArr.size(); tem++)
        {
            //playerposcell is generic just name as player pos cell
            if (cellNum == grid.playerPosCell(heartArr[tem].position[0], heartArr[tem].position[1]))
            {
                heartArr.erase(heartArr.begin() + tem);
                if (lightSituation == 1)
                    health += 60 + countdown;
                else
                {
                    health += (60 + countdown) * 2;
                }
                return;
            }
        }
    }
}

void followPlayer()
{
    float Px = player.position[0];
    float Py = player.position[1];
    float Ix = imposter.position[0];
    float Iy = imposter.position[1];
    float moveX = 0;
    float moveY = 0;
    float moveZ = 0;
    int fl = grid.checkInBox(Ix, Iy);
    // cout << fl << "\n";
    // cout << Px << " " << Py << "\n";
    if (fl >= 0 and cellIdxArr.size() == 0)
    {
        // cout << "ghum\n";
        vector<int> temArr = grid.followDirection(Ix, Iy, Px, Py);
        // cout << "yo " << cellIdx << "\n";
        int toLen = temArr.size();
        for (int tem = 0; tem < toLen - 1; tem++)
        {
            // cout << temArr[tem] << " ";
            cellIdxArr.push_back(temArr[tem]);
        }
        imposterNextIdx = cellIdxArr.back();
        cellIdxArr.pop_back();
    }
    if (fl >= 0)
    {
        int cellIdx = imposterNextIdx;

        if (fl == imposterNextIdx or imposterNextIdx == -1)
        {
            cellIdx = cellIdxArr.back();
            // cout << fl << " " << cellIdx << "\n";
            imposterNextIdx = cellIdxArr.back();
            cellIdxArr.pop_back();
        }
        int curRow = fl / grid.width;
        int curCol = fl % grid.width;
        int Row = cellIdx / grid.width;
        int Col = cellIdx % grid.width;
        moveX = 0;
        moveY = 0;
        if (Row == curRow && Col > curCol)
        {
            moveX = 0.06;
            ImoveX = moveX;
            ImoveY = 0;
        }
        else if (Row == curRow && Col < curCol)
        {
            moveX = -0.06;
            ImoveX = moveX;
            ImoveY = 0;
        }
        else if (Row > curRow && Col == curCol)
        {
            moveY = -0.06;
            ImoveY = moveY;
            ImoveX = 0;
        }
        else if (Row < curRow && Col == curCol)
        {
            moveY = 0.06;
            ImoveY = moveY;
            ImoveX = 0;
        }
    }
    else
    {
        // cout << ImoveX << " " << ImoveY << "\n";
        moveX = ImoveX;
        moveY = ImoveY;
    }
    imposter.set_position(moveX, moveY, moveZ);
}

void tick_input(GLFWwindow *window)
{
    if (imposterMet == 1 or timeup == 1 or won == 1)
    {
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            canExit = 1;
        }
    }
    else
    {
        float movex = 0, movey = 0, movez = 0;
        float cam_movex = 0, cam_movey = 0, cam_movez = 0;

        int changePos = 0;

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) //left
        {
            float mm = grid.checkLeftPossible(player.position[0], player.position[1]);
            if (mm < -0.01f)
            {
                lastKey = 'A';
                // toBeNextKey = 'P';
            }
            else
            {
                toBeNextKey = 'A';
            }
        }
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) //right
        {
            float mm = grid.checkRightPossible(player.position[0], player.position[1]);
            if (mm > 0.01f)
            {
                lastKey = 'D';
                // toBeNextKey = 'P';
            }
            else
            {
                toBeNextKey = 'D';
            }
        }
        else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) //up
        {
            float mm = grid.checkUpPossible(player.position[0], player.position[1], gateOpen);
            if (mm > 0.01f)
            {
                lastKey = 'W';
                // toBeNextKey = 'P';
            }
            else
            {
                toBeNextKey = 'W';
            }
        }
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) //down
        {
            float mm = grid.checkDownPossible(player.position[0], player.position[1]);
            if (mm < -0.01f)
            {
                lastKey = 'S';
                // toBeNextKey = 'P';
            }
            else
            {
                toBeNextKey = 'S';
            }
        }
        if (lastKey == 'A')
        {
            movex = grid.checkLeftPossible(player.position[0], player.position[1]);
            movey = 0;
            movez = 0;
            changePos = 1;
        }
        else if (lastKey == 'D')
        {
            movex = grid.checkRightPossible(player.position[0], player.position[1]);
            movey = 0;
            movez = 0;
            changePos = 1;
        }
        else if (lastKey == 'S')
        {
            movex = 0;
            movey = grid.checkDownPossible(player.position[0], player.position[1]);
            movez = 0;
            changePos = 1;
        }
        else if (lastKey == 'W')
        {
            movex = 0;
            movey = grid.checkUpPossible(player.position[0], player.position[1], gateOpen);
            movez = 0;
            changePos = 1;
        }
        if (changePos == 1)
        {
            player.set_position(movex, movey, movez);
        }
        if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) //down
        {
            if (lightSituation == 1)
            {
                lightSituation = 0;
            }
        }
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) //down
        {
            if (lightSituation == 0)
            {
                lightSituation = 1;
            }
        }
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height)
{
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, "../assets/RobotoMono-VariableFont_wght.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }
    else
    {
        FT_Set_Pixel_Sizes(face, 0, 48);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 0; c < 128; c++)
        {
            // Load character glyph
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer);
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)};
            Characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    // destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    //------------------------------
    hud = HudBox(-6.2, 2.7, -11);
    grid = Grid(0, 0, -11);
    gridBox = GridBox(0, 0, -11);
    int PcellNum = rand() % grid.cells.size();
    float Px = grid.cells[PcellNum].posX + 0.35;
    float Py = grid.cells[PcellNum].posY - 0.25;
    player = Player(Px, Py, -11);
    int IcellNum = rand() % grid.cells.size();
    for (int v = 0; v < 30; v++)
    {
        int tem = rand() % grid.cells.size();
        if (tem / 17 == 0 && tem % 17 == 16)
            continue;
        if (abs(tem / 17 - PcellNum / 17) + abs(tem % 17 - PcellNum % 17) > abs(IcellNum / 17 - PcellNum / 17) + abs(IcellNum % 17 - PcellNum % 17))
        {
            IcellNum = tem;
        }
    }

    float Ix = grid.cells[IcellNum].posX + 0.35;
    float Iy = grid.cells[IcellNum].posY - 0.25;

    imposter = Imposter(Ix, Iy, -11);

    ButtonVapourCellNum = rand() % grid.cells.size();
    for (int v = 0; v < 30; v++)
    {
        int tem = rand() % grid.cells.size();
        if ((tem / 17 == 0 || tem % 17 == 16) || tem / 17 == 11)
            continue;
        if (tem != IcellNum and tem != PcellNum)
        {
            if (pow(abs(tem / 17 - PcellNum / 17), 2) + pow(abs(tem % 17 - PcellNum % 17), 2) + pow(abs(tem / 17 - IcellNum / 17), 2) + pow(abs(tem % 17 - IcellNum % 17), 2) < pow(abs(ButtonVapourCellNum / 17 - PcellNum / 17), 2) + pow(abs(ButtonVapourCellNum % 17 - PcellNum % 17), 2) + pow(abs(ButtonVapourCellNum / 17 - IcellNum / 17), 2) + pow(abs(ButtonVapourCellNum % 17 - IcellNum % 17), 2))
            {
                ButtonVapourCellNum = tem;
            }
        }
    }
    float Vx = grid.cells[ButtonVapourCellNum].posX + 0.35;
    float Vy = grid.cells[ButtonVapourCellNum].posY - 0.35;
    buttonV = ButtonVapour(Vx, Vy, -11);

    ButtonThingsCellNum = rand() % grid.cells.size();
    for (int v = 0; v < 30; v++)
    {
        int tem = rand() % grid.cells.size();
        if ((tem / 17 == 0 || tem % 17 == 16) || tem / 17 == 11)
            continue;
        if (tem != IcellNum and tem != PcellNum and tem != ButtonVapourCellNum)
        {
            if (pow(abs(tem / 17 - PcellNum / 17), 2) + pow(abs(tem % 17 - PcellNum % 17), 2) + pow(abs(tem / 17 - ButtonVapourCellNum / 17), 2) + pow(abs(tem % 17 - ButtonVapourCellNum % 17), 2) > pow(abs(ButtonThingsCellNum / 17 - PcellNum / 17), 2) + pow(abs(ButtonThingsCellNum % 17 - PcellNum % 17), 2) + pow(abs(ButtonVapourCellNum / 17 - ButtonThingsCellNum / 17), 2) + pow(abs(ButtonVapourCellNum % 17 - ButtonThingsCellNum % 17), 2))
            {
                ButtonThingsCellNum = tem;
            }
        }
    }
    float Tx = grid.cells[ButtonThingsCellNum].posX + 0.35;
    float Ty = grid.cells[ButtonThingsCellNum].posY - 0.35;
    button1 = ButtonThings(Tx, Ty, -11);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../src/shaders/shader.vert", "../src/shaders/shader.frag");
    programID2 = LoadShaders("../src/shaders/shaderT.vert", "../src/shaders/shaderT.frag");

    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    ambientStrengthID = glGetUniformLocation(programID, "ambientStrength");
    viewPosID = glGetUniformLocation(programID, "viewPos");
    PlayerPosID = glGetUniformLocation(programID, "PlayerPosition");
    specularStrengthID = glGetUniformLocation(programID, "specularStrength");
    Matrices.modelID = glGetUniformLocation(programID, "Model");

    reshapeWindow(window, width, height);

    // Background color of the scene
    glClearColor(0.6f, 0.6f, 0.5f, 0.0f); // R, G, B, A
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

void gameLost()
{
    glClearColor(0.6f, 0.4f, 0.5f, 0.0f); // R, G, B, A
    glClearDepth(1.0f);
}

void gameWon()
{
    glClearColor(0.7f, 0.2f, 0.3f, 0.0f); // R, G, B, A
    glClearDepth(1.0f);
    if (won == 0)
    {
        health += (200 - (40 - countdown) * 3);
        player.position[1] += 0.10f;
    }
    won = 1;
}

void timeUp()
{
    glClearColor(0.4f, 0.6f, 0.5f, 0.0f); // R, G, B, A
    glClearDepth(1.0f);
    timeup = 1;
}

int main(int argc, char **argv)
{
    srand(time(0));
    int width = 1280;
    int height = 720;
    int k;

    selectedFig = 1;
    window = initGLFW(width, height);

    initGL(window, width, height);
    glGenVertexArrays(1, &VAOint);
    glGenBuffers(1, &VBOint);
    glBindVertexArray(VAOint);
    glBindBuffer(GL_ARRAY_BUFFER, VBOint);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    int ticks = 0;
    /* Draw in loop */
    while (!glfwWindowShouldClose(window))
    {
        // Process timers

        if (t60.processTick())
        {
            ticks++;
            if (ticks >= 60 && imposterMet == 0 && timeup == 0 && won == 0)
            {
                ticks = 0;
                countdown -= 1;
                health += 5;
                if (lightSituation == 0)
                    health += 3;
            }
            checkCollision();
            if (imposterMet == 1)
            {
                gameLost();
            }
            if (completedTask == 2 && gateOpen == 0)
            {
                openGate();
                gateOpen = 1;
            }
            if (countdown == 0)
            {
                timeUp();
            }
            // 60 fps
            if (buttonVRem == 0 and imposterMet == 0)
                followPlayer();
            if (player.position[1] + 0.13 - 0.015 > 4.2)
            {
                gameWon();
            }
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            // tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }
    quit(window);
}

void reset_screen(int width, int height)
{
    Matrices.projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    // projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);
    // projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

    glUniformMatrix4fv(glGetUniformLocation(programID2, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    // compile and setup the shader
    // ----------------------------

    // create perspective projection matrix
}

void RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // activate corresponding render state
    glUseProgram(programID2);
    glUniform3f(glGetUniformLocation(programID2, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAOint);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos, ypos, 0.0f, 1.0f},
            {xpos + w, ypos, 1.0f, 1.0f},

            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos + w, ypos, 1.0f, 1.0f},
            {xpos + w, ypos + h, 1.0f, 0.0f}};
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBOint);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

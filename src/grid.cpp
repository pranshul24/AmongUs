#include "grid.h"
#include <stdlib.h>
#include <iostream>
#include "cell.h"

Grid::Grid(float x, float y, float z)
{
    this->position = glm::vec3(0, 0, -11);
    this->rotation = glm::radians(24.0f);
    this->elapsedTime = 0;
    this->rotationAlongX = 0.0;
    this->width = 17;
    this->height = 12;
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            this->cells.push_back(Cell(row, column));
        }
    }
    float topY = 4.9f, topX = -4.0f;
    for (int i = 0; i < cells.size(); i++)
    {
        if (i % this->width == 0)
        {
            topY -= 0.7f;
            topX = -4.0f;
        }
        cells[i].posX = topX;
        cells[i].posY = topY;
        topX += 0.7f;
    }

    current = &this->cells[0];
    generateMaze();
    cells[width - 1].walls[0] = 0;
    float colorRed[] = {0.772f, 0.066f, 0.066f};

    float colorDarkRed[] = {0.478f, 0.031f, 0.219f};

    float colorBlue[] = {0.588f, 0.792f, 0.866f};

    float colorYellow[] = {0.960f, 0.960f, 0.341f};

    float colorBrown[] = {0.760f, 0.529f, 0.133f};

    float colorGrey[] = {0.286f, 0.388f, 0.427f};
    float colorGold[] = {0.866f, 0.698f, 0.192f};
    float colorHeart[] = {0.890f, 0.105f, 0.137f};
    float colorBlack[] = {0.0f, 0.0f, 0.0f};

    int totlength = 0;

    GLfloat grid1[2500];
    int var = 0, cnt = 0;
    topY = 4.9f;
    topX = -4.0f;
    for (int i = 0; i < cells.size(); i++)
    {
        if (i % this->width == 0)
        {
            topY -= 0.7f;
            topX = -4.0f;
        }
        int topT = 0, leftT = 0;
        if (cells[i].walls[0] == 1 && i / width == 0) //top
        {
            grid1[var++] = topX;
            grid1[var++] = topY;
            grid1[var++] = 0;
            grid1[var++] = topX + 0.7f;
            grid1[var++] = topY;
            grid1[var++] = 0;
            cnt += 6;
        }
        if (cells[i].walls[1] == 1) //right
        {
            grid1[var++] = topX + 0.7f;
            grid1[var++] = topY;
            grid1[var++] = 0;
            grid1[var++] = topX + 0.7f;
            grid1[var++] = topY - 0.7f;
            grid1[var++] = 0;
            cnt += 6;
        }
        if (cells[i].walls[2] == 1) //bottom
        {
            grid1[var++] = topX;
            grid1[var++] = topY - 0.7f;
            grid1[var++] = 0;
            grid1[var++] = topX + 0.7f;
            grid1[var++] = topY - 0.7f;
            grid1[var++] = 0;
            cnt += 6;
        }
        if (cells[i].walls[3] == 1 && i % width == 0) //left
        {
            grid1[var++] = topX;
            grid1[var++] = topY;
            grid1[var++] = 0;
            grid1[var++] = topX;
            grid1[var++] = topY - 0.7f;
            grid1[var++] = 0;
            cnt += 6;
        }
        topX += 0.7f;
    }
    GLfloat vertex_buffer_data[cnt]; //5 rectangles
    for (int i = 0; i < cnt; i++)
    {
        vertex_buffer_data[i] = grid1[i];
    }
    totlength += cnt;
    int totlengthTillBlack = totlength;
    GLfloat color[totlength];
    for (int i = 0; i < totlength / 3; i++)
    {
        if (i < totlengthTillBlack / 3)
        {
            int k = 3 * i;
            color[k] = colorBlack[0];
            color[k + 1] = colorBlack[1];
            color[k + 2] = colorBlack[2];
        }
    }

    this->object = create3DObject(GL_LINES, totlength / 3, vertex_buffer_data, color, GL_LINE);
}

void Grid::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef

    Matrices.model *= (translate);
    // Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

int Grid::checkInBox(float Ix, float Iy)
{
    float cellLen = 0.7f;
    float objYLen = 0.128 * 4.7;
    float objXLen = 0.145 * 3.85;
    float posY = Iy + 0.25 - 0.015;
    float posX = Ix - 0.35 + 0.015;
    for (int i = 0; i < cells.size(); i++)
    {
        if (cells[i].posX < posX && cells[i].posX + cellLen > posX + objXLen)
        {
            if (cells[i].posY > posY && cells[i].posY - cellLen < posY - objYLen)
            {
                return i;
            }
        }
    }
    // std::cout << "ho";
    return -1;
}

int Grid::imposterPosCell(float Ix, float Iy)
{
    float cellLen = 0.7f;
    float objYLen = 0.128 * 4.7;
    float objXLen = 0.145 * 3.85;
    float posY = Iy + 0.25 - 0.015;
    float posX = Ix - 0.35 + 0.015;
    int toIdx = -1;
    for (int i = 0; i < cells.size(); i++)
    {
        if (cells[i].posX < posX && cells[i].posX + cellLen > posX + objXLen)
        {
            if (cells[i].posY > posY && cells[i].posY - cellLen < posY - objYLen)
            {
                toIdx = i;
                break;
            }
            else if (cells[i].posY > posY && cells[i].row < height - 1 && cells[i].posY - cellLen < posY && cells[i].posY - 2 * cellLen < posY - objYLen)
            {
                toIdx = i;
                break;
            }
        }
        else if (cells[i].posX < posX && cells[i].column < width - 1 && cells[i].posX + cellLen > posX && cells[i].posX + 2 * cellLen > posX + objXLen)
        {
            if (cells[i].posY > posY && cells[i].posY - cellLen < posY - objYLen)
            {
                toIdx = i;
                break;
            }
        }
    }
    return toIdx;
}

int Grid::playerPosCell(float Px, float Py)
{
    float cellLen = 0.7f;
    float objYLen = 0.128 * 4.7;
    float objXLen = 0.145 * 3.85;
    float posY = Py + 0.25 - 0.015;
    float posX = Px - 0.35 + 0.015;
    int toIdx = -1;
    for (int i = 0; i < cells.size(); i++)
    {
        if (cells[i].posX < posX && cells[i].posX + cellLen > posX + objXLen)
        {
            if (cells[i].posY > posY && cells[i].posY - cellLen < posY - objYLen)
            {
                toIdx = i;
                break;
            }
            else if (cells[i].posY > posY && cells[i].row < height - 1 && cells[i].posY - cellLen < posY && cells[i].posY - 2 * cellLen < posY - objYLen)
            {
                toIdx = i;
                break;
            }
        }
        else if (cells[i].posX < posX && cells[i].column < width - 1 && cells[i].posX + cellLen > posX && cells[i].posX + 2 * cellLen > posX + objXLen)
        {
            if (cells[i].posY > posY && cells[i].posY - cellLen < posY - objYLen)
            {
                toIdx = i;
                break;
            }
        }
    }
    return toIdx;
}

std::vector<int> Grid::followDirection(float posX_temp, float posY_temp, float player_posX_temp, float player_posY_temp)
{

    for (int i = 0; i < cells.size(); i++)
    {
        cells[i].visited = false;
    }
    int s = backtrace.size();
    for (int i = 0; i < s; i++)
    {
        backtrace.pop();
    }
    float cellLen = 0.7f;
    float objYLen = 0.128 * 4.7;
    float objXLen = 0.145 * 3.85;
    float posY = posY_temp + 0.25 - 0.015;
    float player_posY = player_posY_temp + 0.25 - 0.015;

    float posX = posX_temp - 0.35 + 0.015;
    float player_posX = player_posX_temp - 0.35 + 0.015;
    int n = cells.size(); // number of nodes

    std::vector<std::vector<int>> adj(n); // adjacency list representation

    std::queue<int> queue;
    std::vector<bool> used(n);
    std::vector<int> d(n), p(n);
    for (int i = 0; i < cells.size(); i++)
    {
        if (cells[i].row > 0 && cells[i].walls[0] == 0)
        {
            adj[i].push_back(i - width);
        }
        if (cells[i].row < height - 1 && cells[i].walls[2] == 0)
        {
            adj[i].push_back(i + width);
        }
        if (cells[i].column > 0 && cells[i].walls[3] == 0)
        {
            adj[i].push_back(i - 1);
        }
        if (cells[i].column < width - 1 && cells[i].walls[1] == 0)
        {
            adj[i].push_back(i + 1);
        }
    }

    int startIdx = -1, toIdx = -1;
    for (int i = 0; i < cells.size(); i++)
    {
        if (cells[i].posX < posX && cells[i].posX + cellLen > posX + objXLen)
        {
            if (cells[i].posY > posY && cells[i].posY - cellLen < posY - objYLen)
            {
                startIdx = i;
                break;
            }
        }
    }
    for (int i = 0; i < cells.size(); i++)
    {
        if (cells[i].posX < player_posX && cells[i].posX + cellLen > player_posX + objXLen)
        {
            if (cells[i].posY > player_posY && cells[i].posY - cellLen < player_posY - objYLen)
            {
                toIdx = i;
                break;
            }
            else if (cells[i].posY > player_posY && cells[i].row < height - 1 && cells[i].posY - cellLen < player_posY && cells[i].posY - 2 * cellLen < player_posY - objYLen)
            {
                toIdx = i;
                break;
            }
        }
        else if (cells[i].posX < player_posX && cells[i].column < width - 1 && cells[i].posX + cellLen > player_posX && cells[i].posX + 2 * cellLen > player_posX + objXLen)
        {
            if (cells[i].posY > player_posY && cells[i].posY - cellLen < player_posY - objYLen)
            {
                toIdx = i;
                break;
            }
        }
    }

    queue.push(startIdx);
    used[startIdx] = true;
    p[startIdx] = -1;
    while (!queue.empty())
    {
        int v = queue.front();
        queue.pop();
        for (int u : adj[v])
        {
            if (!used[u])
            {
                used[u] = true;
                queue.push(u);
                d[u] = d[v] + 1;
                p[u] = v;
            }
        }
    }

    std::vector<int> path;
    for (int v = toIdx; v != -1; v = p[v])
        path.push_back(v);

    if (path.size() > 0)
        path.pop_back();
    int val = 20, totInc = 0;
    std::vector<int> followArr, sendFollowArr;
    followArr.push_back(20);
    while (path.size() > 0 and totInc < val)
    {
        followArr.push_back(path.back());
        path.pop_back();
        totInc++;
    }
    for (int tem = 0; tem < followArr.size(); tem++)
    {
        sendFollowArr.push_back(followArr[followArr.size() - 1 - tem]);
    }
    return sendFollowArr;
}

void Grid::generateMaze()
{
    int goOn = 1;
    while (goOn == 1)
    {
        current->setVisited(true);
        Cell *next = findNextCell();

        if (next != NULL)
        {
            next->setVisited(true);
            backtrace.push(current);
            current->removeWalls(*next);
            current = next;
        }
        else if (backtrace.size() > 0)
        {
            current = backtrace.top();
            backtrace.pop();
        }
        else if (backtrace.size() == 0)
        {
            break;
        }
    }
    int maxRem = cells.size() - 1, cnt;
    for (int i = 0; i < cells.size() * 2 / 3 - 1; i++)
    {
        int cellNum = rand() % cells.size();
        if (cells[cellNum].walls[0] + cells[cellNum].walls[1] + cells[cellNum].walls[2] + cells[cellNum].walls[3] <= 1)
            continue;
        if (cells[cellNum].row != 0 && cells[cellNum].column != 0 && cells[cellNum].column != width - 1 && cells[cellNum].row != height - 1)
        {
            int c = 10;
            while (c--)
            {
                int ind = rand() % 4;
                if (cells[cellNum].walls[ind] == 1)
                {
                    if (cells[cellNum].row > 0)
                    {
                        if (cells[cellNum - width].walls[0] + cells[cellNum - width].walls[1] + cells[cellNum - width].walls[2] + cells[cellNum - width].walls[3] <= 1)
                        {
                            break;
                        }
                    }
                    if (cells[cellNum].column > 0)
                    {
                        if (cells[cellNum - 1].walls[0] + cells[cellNum - 1].walls[1] + cells[cellNum - 1].walls[2] + cells[cellNum - 1].walls[3] <= 1)
                        {
                            break;
                        }
                    }
                    if (cells[cellNum].column < height - 1)
                    {
                        if (cells[cellNum + 1].walls[0] + cells[cellNum + 1].walls[1] + cells[cellNum + 1].walls[2] + cells[cellNum + 1].walls[3] <= 1)
                        {
                            break;
                        }
                    }
                    if (cells[cellNum].row < width - 1)
                    {
                        if (cells[cellNum + width].walls[0] + cells[cellNum + width].walls[1] + cells[cellNum + width].walls[2] + cells[cellNum + width].walls[3] <= 1)
                        {
                            break;
                        }
                    }
                    if (ind == 0) //top
                    {
                        if (cells[cellNum].row > 0 && cells[cellNum].column > 0) //top left
                        {
                            if (cells[cellNum].walls[3] + cells[cellNum].walls[0] + cells[cellNum - width - 1].walls[1] + cells[cellNum - width - 1].walls[2] <= 1)
                                break;
                        }
                        if (cells[cellNum].row > 0 && cells[cellNum].column < width - 1) //top right
                        {
                            if (cells[cellNum].walls[1] + cells[cellNum].walls[0] + cells[cellNum - width + 1].walls[3] + cells[cellNum - width + 1].walls[2] <= 1)
                                break;
                        }
                    }
                    if (ind == 1) //right
                    {
                        if (cells[cellNum].row < (height - 1) && cells[cellNum].column < width - 1) //bottom right
                        {
                            if (cells[cellNum].walls[1] + cells[cellNum].walls[2] + cells[cellNum + width + 1].walls[0] + cells[cellNum + width + 1].walls[3] <= 1)
                                break;
                        }
                        if (cells[cellNum].row > 0 && cells[cellNum].column < width - 1) //top right
                        {
                            if (cells[cellNum].walls[1] + cells[cellNum].walls[0] + cells[cellNum - width + 1].walls[3] + cells[cellNum - width + 1].walls[2] <= 1)
                                break;
                        }
                    }
                    if (ind == 2) //bottom
                    {
                        if (cells[cellNum].row < (height - 1) && cells[cellNum].column < width - 1) //bottom right
                        {
                            if (cells[cellNum].walls[1] + cells[cellNum].walls[2] + cells[cellNum + width + 1].walls[0] + cells[cellNum + width + 1].walls[3] <= 1)
                                break;
                        }
                        if (cells[cellNum].row < width - 1 && cells[cellNum].column > 0) //bottom left
                        {
                            if (cells[cellNum].walls[3] + cells[cellNum].walls[2] + cells[cellNum + width - 1].walls[1] + cells[cellNum + width - 1].walls[0] <= 1)
                                break;
                        }
                    }
                    if (ind == 3)
                    {
                        if (cells[cellNum].row > 0 && cells[cellNum].column > 0) //top left
                        {
                            if (cells[cellNum].walls[3] + cells[cellNum].walls[0] + cells[cellNum - width - 1].walls[1] + cells[cellNum - width - 1].walls[2] <= 1)
                                break;
                        }
                        if (cells[cellNum].row < width - 1 && cells[cellNum].column > 0) //bottom left
                        {
                            if (cells[cellNum].walls[3] + cells[cellNum].walls[2] + cells[cellNum + width - 1].walls[1] + cells[cellNum + width - 1].walls[0] <= 1)
                                break;
                        }
                    }

                    cells[cellNum].walls[ind] = 0;
                    if (ind == 0)
                    {
                        // if (cellNum / width > 0)
                        // {
                        cells[cellNum - width].walls[2] = 0;
                        // }
                    }
                    else if (ind == 1)
                    {
                        // if (cellNum % width < width - 1)
                        // {
                        cells[cellNum + 1].walls[3] = 0;
                        // }
                    }
                    else if (ind == 2)
                    {
                        // if (cellNum / width < height - 1)
                        // {
                        cells[cellNum + width].walls[0] = 0;
                        // }
                    }
                    else if (ind == 3)
                    {
                        // if (cellNum % width > 0)
                        // {
                        cells[cellNum - 1].walls[1] = 0;
                        // }
                    }
                    cnt++;
                    break;
                }
            }
            if (cnt == maxRem)
            {
                break;
            }
        }
    }
    for (int i = 0; i < cells.size(); i++)
    {
        cells[i].visited = false;
    }
}

Cell *Grid::findNextCell()
{
    std::vector<Cell *> availableNeighbors = getAvailableNeighbors();
    if (availableNeighbors.size() > 0)
    {
        return availableNeighbors.at(rand() % availableNeighbors.size());
    }

    return NULL;
}

Cell *Grid::findNextCellForPath(float Ix, float Iy, float Px, float Py)
{
    std::vector<Cell *> availableNeighbors = getAvailableNeighborsForPath(Ix, Iy, Px, Py);
    if (availableNeighbors.size() > 0)
    {
        return availableNeighbors.at(rand() % availableNeighbors.size());
    }

    return NULL;
}

std::vector<Cell *> Grid::getAvailableNeighborsForPath(float Ix, float Iy, float Px, float Py)
{
    std::vector<Cell *> neighbors;

    int currentRow = current->getRow();
    int currentColumn = current->getColumn();

    int neighborIndexes[4] = {
        calculateIndex(currentRow - 1, currentColumn),
        calculateIndex(currentRow, currentColumn + 1),
        calculateIndex(currentRow + 1, currentColumn),
        calculateIndex(currentRow, currentColumn - 1),
    };

    for (int i : neighborIndexes)
    {
        if (i != -1 && !cells[i].isVisited())
        {
            int up = 0, down = 0, left = 0, right = 0;
            if (i == calculateIndex(currentRow - 1, currentColumn) and current->walls[0] == 1)
            {
                continue;
            }
            if (i == calculateIndex(currentRow, currentColumn + 1) and current->walls[1] == 1)
            {
                continue;
            }
            if (i == calculateIndex(currentRow + 1, currentColumn) and current->walls[2] == 1)
            {
                continue;
            }
            if (i == calculateIndex(currentRow, currentColumn - 1) and current->walls[3] == 1)
            {
                continue;
            }
            if (i == calculateIndex(currentRow - 1, currentColumn))
                up = 1;
            else if (i == calculateIndex(currentRow, currentColumn + 1))
                right = 1;
            else if (i == calculateIndex(currentRow + 1, currentColumn))
                down = 1;
            else if (i == calculateIndex(currentRow, currentColumn - 1))
                left = 1;

            int iterNum = 4;
            if (Ix > Px and Iy > Py)
            {
                if (left == 1 or down == 1)
                {
                    for (int temn = 0; temn < iterNum; temn++)
                        neighbors.push_back(&cells[i]);
                }
            }
            else if (Ix > Px and Iy < Py)
            {
                if (left == 1 or up == 1)
                {
                    for (int temn = 0; temn < iterNum; temn++)
                        neighbors.push_back(&cells[i]);
                }
            }
            else if (Ix < Px and Iy > Py)
            {
                if (right == 1 or down == 1)
                {
                    for (int temn = 0; temn < iterNum; temn++)
                        neighbors.push_back(&cells[i]);
                }
            }
            else if (Ix < Px and Iy < Py)
            {
                if (right == 1 or up == 1)
                {
                    for (int temn = 0; temn < iterNum; temn++)
                        neighbors.push_back(&cells[i]);
                }
            }
            else if (Ix == Px and Iy > Py)
            {
                if (down == 1)
                {
                    for (int temn = 0; temn < iterNum; temn++)
                        neighbors.push_back(&cells[i]);
                }
            }
            else if (Ix == Px and Iy < Py)
            {
                if (up == 1)
                {
                    for (int temn = 0; temn < iterNum; temn++)
                        neighbors.push_back(&cells[i]);
                }
            }
            else if (Ix < Px and Iy == Py)
            {
                if (right == 1)
                {
                    for (int temn = 0; temn < iterNum; temn++)
                        neighbors.push_back(&cells[i]);
                }
            }
            else if (Ix > Px and Iy == Py)
            {
                if (left == 1)
                {
                    for (int temn = 0; temn < iterNum; temn++)
                        neighbors.push_back(&cells[i]);
                }
            }
            neighbors.push_back(&cells[i]);
        }
    }
    return neighbors;
}

std::vector<Cell *> Grid::getAvailableNeighbors()
{
    std::vector<Cell *> neighbors;

    int currentRow = current->getRow();
    int currentColumn = current->getColumn();

    int neighborIndexes[4] = {
        calculateIndex(currentRow - 1, currentColumn),
        calculateIndex(currentRow, currentColumn + 1),
        calculateIndex(currentRow + 1, currentColumn),
        calculateIndex(currentRow, currentColumn - 1),
    };

    for (int i : neighborIndexes)
    {
        if (i != -1 && !cells[i].isVisited())
        {
            neighbors.push_back(&cells[i]);
        }
    }

    return neighbors;
}

int Grid::calculateIndex(int row, int column)
{
    if (row < 0 || column < 0 || column > width - 1 || row > height - 1)
        return -1;
    else
        return column + row * width;
}

void Grid::set_position(float x, float y, float z)
{
    this->position = this->position + glm::vec3(x, y, z);
}

float Grid::checkLeftPossible(float posX_temp, float posY_temp)
{
    float cellLen = 0.7f;
    float objYLen = 0.128 * 4.7;
    float objXLen = 0.145 * 3.85;
    float posY = posY_temp + 0.25 - 0.015;

    float posX = posX_temp - 0.35 + 0.015;
    int mink = -1;
    for (int i = 0; i < cells.size(); i++)
    {

        if (cells[i].posY > posY && cells[i].posY - cellLen < posY - objYLen)
        {
            if (cells[i].posX - posX < 0)
            {
                if (cells[i].posX + cellLen > posX + objXLen)
                {

                    if (posX - 0.06f > cells[i].posX)
                    {

                        return -0.06f;
                    }
                    else
                    {
                        if (cells[i].walls[3] == 1)
                            return (0.0f);
                        else
                        {
                            return (-0.06f);
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < cells.size(); i++)
    {

        if (cells[i].posY > posY && i / width < height - 1 && cells[i].posY - cellLen < posY && cells[i + width].posY - cellLen < posY - objYLen)
        {
            if (cells[i].posX - posX < 0)
            {
                if (cells[i].posX + cellLen > posX + objXLen)
                {

                    if (posX - 0.06f > cells[i].posX)
                    {
                        return -0.06f;
                    }
                    else
                    {
                        if (cells[i].walls[3] == 1 or cells[i + width].walls[3] == 1 or (i % width > 0 and cells[i + width - 1].walls[0] == 1))
                            return (0.0f);
                        else
                        {
                            return (-0.06f);
                        }
                    }
                }
            }
        }
    }
    return -0.06;
}

float Grid::checkRightPossible(float posX_temp, float posY_temp)
{
    float cellLen = 0.7f;
    float objYLen = 0.128 * 4.7;
    float objXLen = 0.145 * 3.85;
    float posY = posY_temp + 0.25 - 0.015;

    float posX = posX_temp - 0.35 + 0.015;
    for (int i = 0; i < cells.size(); i++)
    {

        if (cells[i].posY > posY && cells[i].posY - cellLen < posY - objYLen)
        {
            if (cells[i].posX - posX < 0)
            {
                if (cells[i].posX + cellLen > posX + objXLen)
                {

                    if (posX + objXLen + 0.06f + 0.08f < cells[i].posX + cellLen)
                    {
                        return 0.06f;
                    }
                    else
                    {
                        if (cells[i].walls[1] == 1)
                            return (0.0f);
                        else
                        {
                            return (0.06f);
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < cells.size(); i++)
    {

        if (cells[i].posY > posY && i / width < height - 1 && cells[i].posY - cellLen < posY && cells[i + width].posY - cellLen < posY - objYLen)
        {
            if (cells[i].posX - posX < 0)
            {
                if (cells[i].posX + cellLen > posX + objXLen)
                {

                    if (posX + objXLen + 0.06f + 0.08f < cells[i].posX + cellLen)
                    {

                        return 0.06f;
                    }
                    else
                    {
                        if (cells[i].walls[1] == 1 or cells[i + width].walls[1] == 1 or (i % width < width - 1 and cells[i + width + 1].walls[0] == 1))
                            return (0.0f);
                        else
                        {
                            return (0.06f);
                        }
                    }
                }
            }
        }
    }
    return 0.06;
}

float Grid::checkUpPossible(float posX_temp, float posY_temp, int gateOpen)
{
    float cellLen = 0.7f;
    float objYLen = 0.128 * 4.7;
    float objXLen = 0.145 * 3.85;
    float posY = posY_temp + 0.25 - 0.015;

    float posX = posX_temp - 0.35 + 0.015;

    for (int i = 0; i < cells.size(); i++)
    {
        if (cells[i].posX < posX && cells[i].posX + cellLen > posX + objXLen)
        {
            if (cells[i].posY > posY)
            {

                if (cells[i].posY - cellLen < posY - objYLen)
                {
                    if (posY + 0.06f < cells[i].posY)
                    {
                        return (0.06f);
                    }
                    else
                    {
                        if (cells[i].walls[0] == 1 or (i == width - 1 and gateOpen == 0))
                            return 0.0f;
                        else
                        {
                            return (0.06f);
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < cells.size(); i++)
    {
        if (cells[i].posX < posX && i % width < width - 1 && cells[i].posX + cellLen > posX && cells[i + 1].posX + cellLen > posX + objXLen)
        {
            if (cells[i].posY > posY)
            {
                if (cells[i].posY - cellLen < posY - objYLen)
                {
                    if (posY + 0.06f < cells[i].posY)
                    {
                        return (0.06f);
                    }
                    else
                    {
                        if (cells[i].walls[0] == 1 or cells[i + 1].walls[0] == 1 or (i / width > 0 and cells[i - width].walls[1] == 1))
                            return 0.0f;
                        else
                        {
                            return (0.06f);
                        }
                    }
                }
            }
        }
    }
    return 0.06;
}

float Grid::checkDownPossible(float posX_temp, float posY_temp)
{
    float cellLen = 0.7f;
    float objYLen = 0.128 * 4.7;
    float objXLen = 0.145 * 3.85;
    float posY = posY_temp + 0.25 - 0.015;

    float posX = posX_temp - 0.35 + 0.015;
    for (int i = 0; i < cells.size(); i++)
    {
        if (cells[i].posX < posX && cells[i].posX + cellLen > posX + objXLen)
        {
            if (cells[i].posY > posY)
            {
                if (cells[i].posY - cellLen < posY - objYLen)
                {
                    if (posY - objYLen - 0.06f - 0.035f > cells[i].posY - cellLen)
                    {
                        return (-0.06f);
                    }
                    else
                    {
                        if (cells[i].walls[2] == 1)
                            return 0.0f;
                        else
                        {
                            return (-0.06f);
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < cells.size(); i++)
    {
        if (cells[i].posX < posX && i % width < width - 1 && cells[i].posX + cellLen > posX && cells[i + 1].posX + cellLen > posX + objXLen)
        {
            if (cells[i].posY > posY)
            {
                if (cells[i].posY - cellLen < posY - objYLen)
                {
                    if (posY - objYLen - 0.06f - 0.035f > cells[i].posY - cellLen)
                    {
                        return (-0.06f);
                    }
                    else
                    {
                        if (cells[i].walls[2] == 1 or cells[i + 1].walls[2] == 1 or (i / width < height - 1 and cells[i + width].walls[1] == 1))
                            return 0.0f;
                        else
                        {
                            return (-0.06f);
                        }
                    }
                }
            }
        }
    }
    return -0.06;
}
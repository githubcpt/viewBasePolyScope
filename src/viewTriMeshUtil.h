#pragma once
#include <igl/readOBJ.h>
#include <igl/readOFF.h>
#include <polyscope/curve_network.h>
#include <polyscope/point_cloud.h>
#include <polyscope/polyscope.h>
#include <polyscope/surface_mesh.h>

class viewTriMeshUtil
{
public:
    void render();

    void loadVertexData();

    void loadEdgeData();

    void loadFaceData();

    void renderVertex();

    void renderEdge();

    void renderFace();

private:
    // Face info
    Eigen::MatrixXd meshV;
    Eigen::MatrixXi meshF;

    // Edge info
    std::vector<glm::vec3> pointsOfEdge;
    std::vector<std::array<int, 2>> indicesOfEdge;

    // Vertex info
    std::vector<glm::vec3> points;
};
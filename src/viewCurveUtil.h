#pragma once
#include "polyscope/polyscope.h"

#include <igl/PI.h>
#include <igl/avg_edge_length.h>
#include <igl/barycenter.h>
#include <igl/boundary_loop.h>
#include <igl/exact_geodesic.h>
#include <igl/gaussian_curvature.h>
#include <igl/invert_diag.h>
#include <igl/lscm.h>
#include <igl/massmatrix.h>
#include <igl/per_vertex_normals.h>
#include <igl/readOBJ.h>

#include "polyscope/messages.h"
#include "polyscope/point_cloud.h"
#include "polyscope/surface_mesh.h"
#include "polyscope/volume_mesh.h"

#include <igl/readMESH.h>
#include <polyscope/curve_network.h>
#include <iostream>
#include <unordered_set>
#include <utility>

class viewCurveUtil
{
public:
    void readMyPointsAndEdges(std::string filename,
                              std::vector<glm::vec3>& nodes);

    void readMyPoints(std::string filename, std::vector<glm::vec3>& nodes);

    void readMyPointsAndColors(std::string filename, std::vector<glm::vec3>& nodes, std::vector<glm::vec3>& colors);

    void readMyPointsAndColorsAndVectors(std::string filename,
                                         std::vector<glm::vec3>& nodes,
                                         std::vector<glm::vec3>& colors,
                                         std::vector<glm::vec3>& vectors);

    void viewMyCurveByEdges();

    void viewMyCurveByPoints();

    void viewMyCurveByPointsWithColor();

private:
};
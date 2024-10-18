#include "viewTriMeshUtil.h"

std::string vertexFileName = "E:/PoissonOffsetResearch/RenderData/v.txt";
std::string edgeFileName = "E:/PoissonOffsetResearch/RenderData/e.txt";
std::string faceFileName = "E:/PoissonOffsetResearch/RenderData/f.off";

void viewTriMeshUtil::render()
{
    loadFaceData();

    loadEdgeData();

    loadVertexData();

    // Initialize Polyscope
    polyscope::init();
    polyscope::options::groundPlaneMode = polyscope::GroundPlaneMode::None;
    polyscope::options::ssaaFactor = 4;

    renderFace();

    renderEdge();

    renderVertex();

    // Show the GUI
    polyscope::show();
}

void viewTriMeshUtil::loadVertexData()
{
    // Read points info
    std::ifstream file(vertexFileName);
    if (!file.is_open())
    {
        std::cerr << "Failed to open point cloud file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        double x, y, z;
        std::istringstream iss(line);
        if (!(iss >> x >> y >> z))
        {
            std::cerr << "Error parsing point coordinates." << std::endl;
            continue;
        }

        points.push_back(glm::vec3{x, y, z});
    }

    file.close();
}

void viewTriMeshUtil::loadEdgeData()
{
    // Read points info
    std::ifstream file(edgeFileName);
    if (!file.is_open())
    {
        std::cerr << "Failed to open point cloud file." << std::endl;
        return;
    }

    std::vector<int> indices;

    std::string line;
    while (std::getline(file, line))
    {
        if (line == "#####")
        {
            indices.push_back(pointsOfEdge.size());
        }
        else
        {
            double x, y, z;
            std::istringstream iss(line);
            if (!(iss >> x >> y >> z))
            {
                std::cerr << "Error parsing point coordinates." << std::endl;
                continue;
            }

            pointsOfEdge.push_back(glm::vec3{x, y, z});
        }
    }

    file.close();

    // Construct edge info
    int start = 0;
    for (int i = 0; i < indices.size(); i++)
    {
        for (int j = start + 1; j < indices[i]; ++j)
        {
            indicesOfEdge.push_back({j - 1, j});
        }

        start = indices[i];
    }
}

void viewTriMeshUtil::loadFaceData()
{
    // Read the mesh
    igl::readOFF(faceFileName, meshV, meshF);
}

void viewTriMeshUtil::renderVertex()
{
    // Add the point cloud
    polyscope::registerPointCloud("Vertex", points);
}

void viewTriMeshUtil::renderEdge()
{
    // Add the curve network
    polyscope::registerCurveNetwork("Edge", pointsOfEdge, indicesOfEdge);
}

void viewTriMeshUtil::renderFace()
{
    // Register the mesh with Polyscope
    polyscope::registerSurfaceMesh("Face", meshV, meshF);
}

// void exportCurveBspline(std::string filename, PSGMCurveBSplineBasisSPtr curve, int numPoints = 1000)
//{
//    numPoints = std::max<int>(100, numPoints);
//    std::ofstream output_file(filename, std::ios::out);
//    auto poles = curve->getControlPoints();
//    output_file << "POLES " << poles.size() << "\n";
//    for (auto& p : poles)
//    {
//        output_file << p.x() << " " << p.y() << " " << p.z() << "\n";
//    }
//    output_file << "POINTS " << numPoints << "\n";
//    for (int i = 0; i < numPoints; ++i)
//    {
//        double t = 1.0 * i / (numPoints - 1);
//        auto p = curve->getPoint(t);
//        output_file << p.x() << " " << p.y() << " " << p.z() << "\n";
//    }
//    output_file.close();
//}
//
// void exportSurfaceBspline(std::string filename, PSGMSurfBSplineBaseSPtr surface, int numU = 25, int numV = 25)
//{
//    std::cout << "export surface begin...\n";
//    std::cout << "numU = " << numU << ", numV = " << numV << "\n";
//    psgmstd::vector<PSGMPoint> vertices(numU * numV);
//    for (int i = 0; i < numU; ++i)
//    {
//        double u = 1.0 * i / (numU - 1);
//        for (int j = 0; j < numV; ++j)
//        {
//            double v = 1.0 * j / (numV - 1);
//            vertices[i * numV + j] = surface->getPoint(PSGMUVParam(u, v));
//        }
//    }
//
//    psgmstd::vector<psgmstd::vector<int>> faces;
//    for (int i = 1; i < numU; ++i)
//    {
//        for (int j = 1; j < numV; ++j)
//        {
//            int v1 = (i - 1) * numV + j - 1;
//            int v2 = i * numV + j - 1;
//            int v3 = i * numV + j;
//            int v4 = (i - 1) * numV + j;
//            faces.push_back({v1, v2, v3, v4});
//        }
//    }
//
//    std::ofstream output_file(filename, std::ios::out);
//    output_file << "OFF\n";
//    output_file << vertices.size() << " " << faces.size() << " 0\n";
//    for (auto& v : vertices)
//    {
//        output_file << v.x() << " " << v.y() << " " << v.z() << "\n";
//    }
//    for (auto& f : faces)
//    {
//        output_file << f.size();
//        for (auto& vid : f)
//        {
//            output_file << " " << vid;
//        }
//        output_file << "\n";
//    }
//    output_file.close();
//    std::cout << "export surface success...\n";
//}

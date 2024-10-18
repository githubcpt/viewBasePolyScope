#include "viewCurveUtil.h"

void viewCurveUtil::readMyPointsAndEdges(std::string filename, std::vector<glm::vec3>& nodes)
{
    std::ifstream file(filename);
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

        nodes.push_back(glm::vec3{x, y, z});
    }

    file.close();
}

void viewCurveUtil::readMyPoints(std::string filename, std::vector<glm::vec3>& nodes)
{
    std::ifstream file(filename);
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

        nodes.push_back(glm::vec3{x, y, z});
    }

    file.close();
}

void viewCurveUtil::readMyPointsAndColorsAndVectors(std::string filename,
                                               std::vector<glm::vec3>& nodes,
                                               std::vector<glm::vec3>& colors,
                                               std::vector<glm::vec3>& vectors)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open point cloud file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        double x, y, z, a, b, c, p, q, r;
        std::istringstream iss(line);
        if (!(iss >> x >> y >> z >> a >> b >> c >> p >> q >> r))
        {
            std::cerr << "Error parsing point coordinates." << std::endl;
            continue;
        }

        nodes.push_back(glm::vec3{x, y, z});
        colors.push_back(glm::vec3{a, b, c});
        vectors.push_back(glm::vec3{p, q, r});
    }

    file.close();
}

void viewCurveUtil::readMyPointsAndColors(std::string filename,
                                     std::vector<glm::vec3>& nodes,
                                     std::vector<glm::vec3>& colors)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open point cloud file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        double x, y, z, a, b, c;
        std::istringstream iss(line);
        if (!(iss >> x >> y >> z >> a >> b >> c))
        {
            std::cerr << "Error parsing point coordinates." << std::endl;
            continue;
        }

        nodes.push_back(glm::vec3{x, y, z});
        colors.push_back(glm::vec3{a, b, c});
    }

    file.close();
}

void viewCurveUtil::viewMyCurveByEdges()
{
    polyscope::init();
    polyscope::options::groundPlaneMode = polyscope::GroundPlaneMode::None;
    polyscope::options::ssaaFactor = 4;

    std::vector<glm::vec3> nodes;
    auto name = "E:/PoissonOffsetResearch/test.pts";
    readMyPoints(name, nodes);

    std::vector<std::array<int, 2>> edges;
    for (int i = 1; i < nodes.size(); i++)
    {
        edges.push_back({i - 1, i});
    }
    // Add the curve network
    auto curve = polyscope::registerCurveNetwork("my network", nodes, edges);
    curve->setColor({0, 0, 0});

    polyscope::show();
}

void viewCurveUtil::viewMyCurveByPoints()
{
    polyscope::init();
    polyscope::options::groundPlaneMode = polyscope::GroundPlaneMode::None;
    polyscope::options::ssaaFactor = 4;
    std::vector<glm::vec3> nodes;

    for (int i = 0; i < 10; i++)
    {
        auto name = "line" + std::to_string(i) + ".pts";
        readMyPoints("E:/PoissonOffsetResearch/" + name, nodes);
    }

    auto point = polyscope::registerPointCloud("my network", nodes);
    point->setPointColor({0, 0, 0});

    polyscope::show();
}

void viewCurveUtil::viewMyCurveByPointsWithColor()
{
    polyscope::view::windowWidth = 200;
    polyscope::view::windowHeight = 200;
    polyscope::init();
    polyscope::options::groundPlaneMode = polyscope::GroundPlaneMode::None;
    polyscope::options::ssaaFactor = 4;

    auto name = "E:/PoissonOffsetResearch/test.pts";
    int viewMode = 0;
    if (viewMode == 0) // only points
    {
        std::vector<glm::vec3> points;
        readMyPoints(name, points);
        auto VP = polyscope::registerPointCloud("Points", points);
        VP->setPointRadius(0.001);
    }
    else if (viewMode == 1) // points and colors
    {
        std::vector<glm::vec3> points;
        std::vector<glm::vec3> colors;
        readMyPointsAndColors(name, points, colors);
        auto VP = polyscope::registerPointCloud("Points", points);
        VP->setPointRadius(0.001);
        auto c = polyscope::getPointCloud(VP->name)->addColorQuantity("Colors", colors);
        c->setEnabled(true);

        //auto name1 = "E:/PoissonOffsetResearch/test1.pts";
        //std::vector<glm::vec3> colors1;
        //std::vector<glm::vec3> points1;
        //readMyPointsAndColors(name1, points1, colors1);
        //auto VP1 = polyscope::registerPointCloud("Points1", points1);
        //VP1->setPointRadius(0.001);
        //auto c1 = polyscope::getPointCloud(VP1->name)->addColorQuantity("Colors1", colors1);
        //c1->setEnabled(true);
    }
    else if (viewMode == 2) // points and vectors
    {
        std::vector<glm::vec3> points;
        std::vector<glm::vec3> vectors;
        readMyPointsAndColors(name, points, vectors);
        auto VP = polyscope::registerPointCloud("Points", points);
        VP->setPointRadius(0.001);
        auto v = polyscope::getPointCloud(VP->name)->addVectorQuantity("Vectors", vectors);
        v->setEnabled(true);
    }
    else // points and colors and vectors
    {
        std::vector<glm::vec3> points;
        std::vector<glm::vec3> colors;
        std::vector<glm::vec3> vectors;
        readMyPointsAndColorsAndVectors(name, points, colors, vectors);
        auto VP = polyscope::registerPointCloud("Points", points);
        VP->setPointRadius(0.001);
        auto v = polyscope::getPointCloud(VP->name)->addVectorQuantity("Vectors", vectors);
        v->setEnabled(true);
        auto c = polyscope::getPointCloud(VP->name)->addColorQuantity("Colors", colors);
        c->setEnabled(true);
    }

    polyscope::show();
}

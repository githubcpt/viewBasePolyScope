#include <exception>
#include "polyscope/polyscope.h"
#include "viewCurveUtil.h"
#include "viewTriMeshUtil.h"

void callback()
{
    if (ImGui::Button("Exit"))
    {
        std::abort();
    }
}

int main(int argc, char** argv)
{
    polyscope::state::userCallback = callback;

#define VIEWTRIMESH 1
#if VIEWTRIMESH

    viewTriMeshUtil render;
    render.render();


#else

    viewCurveUtil vu;
    int viewType = 1;
    switch (viewType)
    {
    case 0:
    {
        vu.viewMyCurveByPoints();
        break;
    }
    case 1:
    {
        vu.viewMyCurveByPointsWithColor();
        break;
    }
    case 2:
    {
        vu.viewMyCurveByEdges();
        break;
    }
    case 3:
    {
        /*vu.viewMyCurveByEdgesWithColor()*/;
        break;
    }
    default:
        break;
    }

#endif

    return 0;
}

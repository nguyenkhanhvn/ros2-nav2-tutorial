#include "tutorial.h"
#include <fields2cover.h>

// Headland generator
int tutorial3() {
    f2c::Random rand(42);
    F2CField field = rand.generateRandField(1e4, 4);
    F2CCells cells = field.getField();
    F2CRobot robot (2.0, 26.0);

    // Constant width headland
    f2c::hg::ConstHL const_hl;
    F2CCells no_hl = const_hl.generateHeadlands(cells, 3.0 * robot.getWidth());
    std::cout << "The complete area is " << cells.area() <<
        ", and the area without headlands is " << no_hl.area() << std::endl;

    // Visualizing Fields2Cover data
    f2c::Visualizer::figure();
    f2c::Visualizer::plot(field);
    // f2c::Visualizer::plot(no_hl);
    f2c::Visualizer::show();
    return 0;
}
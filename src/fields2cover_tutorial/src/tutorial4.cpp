#include "tutorial.h"
#include <fields2cover.h>

// Swath generator
int tutorial4() {
    f2c::Random rand(42);
    F2CRobot robot (2.0, 6.0);
    f2c::hg::ConstHL const_hl;
    F2CCells cells = rand.generateRandField(1e4, 20).getField();
    F2CCells no_hl = const_hl.generateHeadlands(cells, 3.0 * robot.getWidth());

    // Brute force
    f2c::obj::NSwath n_swath_obj;
    f2c::sg::BruteForce bf_sw_gen_nswath;
    F2CSwaths swaths_bf_nswath = bf_sw_gen_nswath.generateBestSwaths(n_swath_obj, robot.getCovWidth(), no_hl.getGeometry(0));

    f2c::obj::SwathLength swath_length;
    F2CSwaths swaths_bf_swathlength = bf_sw_gen_nswath.generateBestSwaths(swath_length, robot.getCovWidth(), no_hl.getGeometry(0));

    F2CSwaths swaths_bf_angle = bf_sw_gen_nswath.generateSwaths(M_PI / 2, robot.getCovWidth(), no_hl.getGeometry(0));

    // Visualizing Fields2Cover data
    f2c::Visualizer::figure();
    f2c::Visualizer::plot(cells);
    f2c::Visualizer::plot(no_hl);
    // f2c::Visualizer::plot(swaths_bf_nswath);
    // f2c::Visualizer::plot(swaths_bf_swathlength);
    f2c::Visualizer::plot(swaths_bf_angle);
    f2c::Visualizer::show();
    return 0;
}
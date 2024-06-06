#include "tutorial.h"
#include <fields2cover.h>

F2CCells createCells(int code);

// Cell Decomposition
int tutorial7() {
    F2CRobot robot (10.0);
    F2CCells cells = createCells(2);
    f2c::hg::ConstHL const_hl;
    F2CCells mid_hl = const_hl.generateHeadlands(cells, 1.0 * robot.getWidth());
    F2CCells no_hl = const_hl.generateHeadlands(cells, 2.0 * robot.getWidth());

    robot.setMinTurningRadius(2);  // m
    robot.setMaxDiffCurv(0.1);  // 1/m^2

    double r_w = robot.getCovWidth();
    f2c::sg::BruteForce bf;
    f2c::obj::NSwathModified obj;

    F2CSwathsByCells swaths_wo_decomp = bf.generateBestSwaths(obj, r_w, no_hl);

    // Decomposition
    f2c::decomp::TrapezoidalDecomp decomp;
    decomp.setSplitAngle(0.5*M_PI);
    F2CCells decomp_cell = decomp.decompose(cells);

    F2CCells no_hl_decomp = const_hl.generateHeadlands(decomp_cell, 2.0 * r_w);
    F2CSwathsByCells swaths_decomp = bf.generateBestSwaths(obj, r_w, no_hl_decomp);

    // Visualizing Fields2Cover data
    f2c::Visualizer::figure();
    f2c::Visualizer::plot(cells);
    f2c::Visualizer::plot(no_hl_decomp);
    // f2c::Visualizer::plot(swaths_decomp);
    f2c::Visualizer::show();

    return 0;
}
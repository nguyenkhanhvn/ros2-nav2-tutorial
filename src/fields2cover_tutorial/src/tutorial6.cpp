#include "tutorial.h"
#include <fields2cover.h>

F2CCells createCells(int code);

// Path planning
int tutorial6() {
    F2CRobot robot (10);
    F2CCells cells = createCells(3);
    f2c::hg::ConstHL const_hl;
    F2CCells mid_hl = const_hl.generateHeadlands(cells, 1.0 * robot.getWidth());
    F2CCells no_hl = const_hl.generateHeadlands(cells, 2.0 * robot.getWidth());

    robot.setMinTurningRadius(2);  // m
    robot.setMaxDiffCurv(0.1);  // 1/m^2
    f2c::pp::PathPlanning path_planner;
    f2c::sg::BruteForce bf;
    F2CSwaths brute_force_swaths = bf.generateSwaths(M_PI, robot.getCovWidth(), no_hl.getGeometry(0));

    // Boustrophedon order
    f2c::rp::BoustrophedonOrder boustrophedon_sorter;
    F2CSwaths boustrophedon_swaths = boustrophedon_sorter.genSortedSwaths(brute_force_swaths);

    // Snake order
    f2c::rp::SnakeOrder snake_sorter;
    F2CSwaths snake_swaths = snake_sorter.genSortedSwaths(brute_force_swaths);


    // Dubins curves
    F2CSwaths swaths = snake_swaths;
    f2c::pp::DubinsCurves dubins;
    F2CPath path_dubins = path_planner.planPath(robot, swaths, dubins);

    // Dubins curves with Continuous curvature
    f2c::pp::DubinsCurvesCC dubins_cc;
    F2CPath path_dubins_cc = path_planner.planPath(robot, swaths, dubins_cc);

    // Reeds-Shepp curves
    f2c::pp::ReedsSheppCurves reeds_shepp;
    F2CPath path_reeds_shepp = path_planner.planPath(robot, swaths, reeds_shepp);

    // Reeds-Shepp curves with Continuous curvature
    f2c::pp::ReedsSheppCurvesHC reeds_shepp_hc;
    F2CPath path_reeds_shepp_hc = path_planner.planPath(robot, swaths, reeds_shepp_hc);

    // Visualizing Fields2Cover data
    f2c::Visualizer::figure();
    f2c::Visualizer::plot(cells);
    f2c::Visualizer::plot(no_hl);
    f2c::Visualizer::plot(swaths);
    f2c::Visualizer::plot(path_dubins);
    f2c::Visualizer::show();
    return 0;
}

F2CCells createCells(int code) {
    f2c::Random rand(42);

    switch (code)
    {
    case 1:
        return rand.generateRandField(1e5, 5).getField();
        
    case 2:
    {    
        // Note: First ring is outter, the others are inner, all inner is not intersect with each others
        F2CLinearRing outter_ring{
            F2CPoint(0, 0), F2CPoint(650, 0), F2CPoint(450, 250), F2CPoint(650, 650), F2CPoint(450, 450), F2CPoint(0, 650), F2CPoint(0, 0)};
        F2CLinearRing inner_ring1{
            F2CPoint(50, 50), F2CPoint(150, 50), F2CPoint(150, 150),
            F2CPoint(50, 150), F2CPoint(50, 50)};
        F2CLinearRing inner_ring2{
            F2CPoint(250, 250), F2CPoint(350, 250), F2CPoint(350, 350),
            F2CPoint(250, 350), F2CPoint(250, 250)};
        F2CCell cell;
        cell.addRing(outter_ring);
        cell.addRing(inner_ring1);
        cell.addRing(inner_ring2);
        return F2CCells(cell);
    }

    case 3:
        return F2CCells(F2CCell(F2CLinearRing({
            F2CPoint(   0,   0),
            F2CPoint( 900,   0),
            F2CPoint( 900, 200),
            F2CPoint( 200, 200),
            F2CPoint( 200, 900),
            F2CPoint(   0, 900),
            F2CPoint(   0,   0)})));
    
    default:
        return F2CCells();
    }
}

#include "tutorial.h"
#include <fields2cover.h>

// Metaheuristics for route planning
void tutorial_5_1();

// Known patterns
void tutorial_5_2();

// Route planning
int tutorial5() {
    // tutorial_5_1();
    tutorial_5_2();
    return 0;
}

void tutorial_5_1() {
    F2CRobot robot (10, 30);
    
    // Note: First ring is outter, the others are inner, all inner is not intersect with each others
    F2CLinearRing outter_ring{
        F2CPoint(0, 0), F2CPoint(650, 0), F2CPoint(450, 250) , F2CPoint(650, 450), F2CPoint(0, 650), F2CPoint(0, 0)};
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
    F2CCells cells(cell);
    f2c::hg::ConstHL const_hl;
    F2CCells mid_hl = const_hl.generateHeadlands(cells, 1.5 * robot.getWidth());
    F2CCells no_hl = const_hl.generateHeadlands(cells, 3.0 * robot.getWidth());

    f2c::sg::BruteForce bf;
    F2CSwathsByCells swaths = bf.generateSwaths(M_PI/2.0, robot.getCovWidth(), no_hl);

    f2c::rp::RoutePlannerBase route_planner;
    F2CRoute route = route_planner.genRoute(no_hl, swaths);

    // Visualizing Fields2Cover data
    f2c::Visualizer::figure();
    f2c::Visualizer::plot(cells);
    // f2c::Visualizer::plot(mid_hl);
    // f2c::Visualizer::plot(no_hl);
    f2c::Visualizer::plot(route);
    f2c::Visualizer::show();
}

void tutorial_5_2() {
    f2c::Random rand(42);
    F2CRobot robot (10, 30);
    f2c::hg::ConstHL const_hl;

        // Note: First ring is outter, the others are inner, all inner is not intersect with each others
    F2CLinearRing outter_ring{
        F2CPoint(0, 0), F2CPoint(650, 0), F2CPoint(450, 250) , F2CPoint(650, 450), F2CPoint(0, 650), F2CPoint(0, 0)};
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
    F2CCells cells(cell);
    // F2CCells cells = rand.generateRandField(1e4, 5).getField();
    F2CCells no_hl = const_hl.generateHeadlands(cells, 3.0 * robot.getWidth());
    f2c::sg::BruteForce bf;
    F2CSwaths swaths = bf.generateSwaths(M_PI, robot.getCovWidth(), no_hl.getGeometry(0));

    // Boustrophedon order
    f2c::rp::BoustrophedonOrder boustrophedon_sorter;
    F2CSwaths boustrophedon_swaths = boustrophedon_sorter.genSortedSwaths(swaths);

    // Snake order
    f2c::rp::SnakeOrder snake_sorter;
    F2CSwaths snake_swaths = snake_sorter.genSortedSwaths(swaths);

    // Spiral order
    f2c::rp::SpiralOrder spiral_sorter(6);
    F2CSwaths spiral_swaths = spiral_sorter.genSortedSwaths(swaths);

    // Custom order
    // f2c::rp::CustomOrder custom_order({0, 1, 2, 3, 4});
    // F2CSwaths custom_swaths = custom_order.genSortedSwaths(swaths);

    // Visualizing Fields2Cover data
    f2c::Visualizer::figure();
    f2c::Visualizer::plot(cells);
    // f2c::Visualizer::plot(mid_hl);
    // f2c::Visualizer::plot(no_hl);
    f2c::Visualizer::plot(boustrophedon_swaths);
    f2c::Visualizer::show();
}

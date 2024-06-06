#include "tutorial.h"
#include <fields2cover.h>

int tutorial2() {
    // HG objective functions
    //  Remaining area
    F2CCells total_field(F2CCell(F2CLinearRing(
        {F2CPoint(-2,-2), F2CPoint(6,-2), F2CPoint(6,6), F2CPoint(-2,6), F2CPoint(-2,-2)})));
    F2CCells field(F2CCell(F2CLinearRing(
        {F2CPoint(0,0), F2CPoint(4,0), F2CPoint(4,4), F2CPoint(0,4), F2CPoint(0,0)})));

    f2c::obj::RemArea rem_area;
    std::cout << "The remaining area is "
        << rem_area.computeCost(total_field, field) << std::endl;
    std::cout << "The remaining area with sign is "
        << rem_area.computeCostWithMinimizingSign(total_field, field) <<std::endl;

    // SG objective functions
    //  Field coverage
    double width {2.0};
    F2CSwath swath1(F2CLineString({F2CPoint(0.0, 1.0), F2CPoint(4.0, 1.0)}), width);
    F2CSwath swath2(F2CLineString({F2CPoint(0.0, 3.0), F2CPoint(4.0, 3.0)}), width);
    F2CSwath swath3(F2CLineString({F2CPoint(0.0, 2.0), F2CPoint(4.0, 2.0)}), width);

    f2c::obj::FieldCoverage field_cov;

    std::cout << "The field coverage with swath1 is "
        << field_cov.computeCost(field, F2CSwaths({swath1})) << " and with all of the swaths "
        << field_cov.computeCost(field, F2CSwaths({swath1, swath2, swath3})) <<std::endl;

    std::cout << "The field coverage with sign for all of the swaths is "
        << field_cov.computeCostWithMinimizingSign(field, F2CSwaths({swath1, swath2, swath3})) <<std::endl;

    //  Number of swaths
    f2c::obj::NSwath n_swaths;

    std::cout << "The number of swaths with swath1 is "
        << n_swaths.computeCost(F2CSwaths({swath1})) << " and with all of the swaths "
        << n_swaths.computeCost(field, F2CSwaths({swath1, swath2, swath3})) <<std::endl;

    f2c::obj::NSwathModified n_swaths_mod;

    std::cout << "The number of swaths with swath1 is "
        << n_swaths_mod.computeCost(F2CSwaths({swath1})) << " and with all of the swaths "
        << n_swaths_mod.computeCost(field, F2CSwaths({swath1, swath2, swath3})) <<std::endl;

    //  Overlap
    f2c::obj::Overlaps overlaps;

    std::cout << "The field overlapping with swath1 is "
        << overlaps.computeCost(field, F2CSwaths({swath1})) << " and with all of the swaths "
        << overlaps.computeCost(field, F2CSwaths({swath1, swath3})) <<std::endl;

    //  Swath Length
    f2c::obj::SwathLength swath_length;

    std::cout << "The swath length with swath1 is "
        << swath_length.computeCost(F2CSwaths({swath1})) << " and with all of the swaths "
        << swath_length.computeCost(field, F2CSwaths({swath1, swath2, swath3})) <<std::endl;

    // RP objective functions
    //  Distance with turns
    F2CSwaths swaths_path({
        F2CSwath(F2CLineString({F2CPoint(0.0, 0.0), F2CPoint(0.0, 1.0)})),
        F2CSwath(F2CLineString({F2CPoint(1.0, 1.0), F2CPoint(1.0, 0.0)}))});
    F2CRobot robot(3.0, 39.0);
    robot.setMinTurningRadius(0.5);

    f2c::obj::CompleteTurnPathObj<f2c::pp::DubinsCurves> complete_length(robot);

    std::cout << "The complete length is: " << complete_length.computeCost(swaths_path) <<
        " =~= " << 1 + 1 + M_PI/2.0 << std::endl;

    //  Direct distance without turns
    f2c::obj::DirectDistPathObj direct_dist;

    std::cout << "The aproximated length is: " <<
        direct_dist.computeCost(swaths_path) << std::endl;

    // PP objective functions
    //  Path length
    F2CPath path;
    path.appendSwath(swaths_path.at(0), 1);
    path.appendSwath(swaths_path.at(1), 1);

    f2c::obj::PathLength path_length;
    std::cout << "The path length is: " <<
        path_length.computeCost(path) << std::endl;


    // Visualizing Fields2Cover data
    // f2c::Visualizer::figure();
    // f2c::Visualizer::plot(field);
    // f2c::Visualizer::show();
    return 0;
}
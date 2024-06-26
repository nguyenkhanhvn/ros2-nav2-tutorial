#include "tutorial.h"
#include <fields2cover.h>

int tutorial1() {
    // Initialize a F2CPoint
    F2CPoint p1 (1.2, 3.4);
    std::cout << "Point 1: " << p1 << std::endl;
    
    F2CPoint p2 (9.8, 7.6, 5.4);
    std::cout << "Point 2: " << p2 << std::endl;

    F2CPoint p3 (OGRPoint(11, 22));
    std::cout << "Point 3: " << p3 << std::endl;

    F2CPoint p4;
    p4.setX(3.0);
    p4.setZ(-1.0);
    std::cout << "Point 4: " << p4;
    std::cout << ". Its components are: {x: " << p4.getX();
    std::cout << ", y: " << p4.getY();
    std::cout << ", z: " << p4.getZ() << "}\n";

    F2CPoint p5;
    p5.importFromWkt("POINT (0 4 4)");
    std::cout << "Point 5: " << p5 << std::endl;

    // Basic types are shared pointers
    std::cout << "Access to OGRPoints: " << p4->Distance(p5.get()) << std::endl;
    std::cout << "Without accessing: " << p4.distance(p5) << std::endl;

    // Initialize a F2CLineString
    F2CLineString line1;
    line1.addPoint(3, 0);
    line1.addPoint(p5);  // Point(0, 4)
    std::cout << "Length of line 1: " << line1.length() << std::endl;

    F2CLineString line2({F2CPoint(1, 0), F2CPoint(1, 1), F2CPoint(0, 1)});
    std::cout << "Length of line 2: " << line2.length() << std::endl;

    // Initialize a F2CLinearRing
    F2CLinearRing ring{F2CPoint(1,1), F2CPoint(1,2), F2CPoint(2,2), F2CPoint(1,1)};
    std::cout << "Area of the ring: " << ring.area() << std::endl;

    // Initializing other collections
    F2CMultiLineString lines;
    lines.addGeometry(line1);
    lines.addGeometry(line2);
    std::cout << "Lines have length: ";
    for (auto line : lines) {
        std::cout << line.length() << ", ";
    }
    std::cout << std::endl;

    // Note: First ring is outter, the others are inner, all inner is not intersect with each others
    F2CLinearRing outter_ring{
        F2CPoint(0, 0), F2CPoint(4.5, 0),F2CPoint(4.5, 4.5), F2CPoint(0, 4.5), F2CPoint(0, 0)};
    std::cout << "Area of the outter ring: " << outter_ring.area() << std::endl;
    F2CLinearRing inner_ring1{
        F2CPoint(0.5, 0.5), F2CPoint(1.5, 0.5), F2CPoint(1.5, 1.5),
        F2CPoint(0.5, 1.5), F2CPoint(0.5, 0.5)};
    std::cout << "Area of the inner ring1: " << inner_ring1.area() << std::endl;
    F2CLinearRing inner_ring2{
        F2CPoint(2.5, 2.5), F2CPoint(3.5, 2.5), F2CPoint(3.5, 3.5),
        F2CPoint(2.5, 3.5), F2CPoint(2.5, 2.5)};
    std::cout << "Area of the inner ring2: " << inner_ring2.area() << std::endl;
    F2CLinearRing inner_ring3{
        F2CPoint(20.5, 20.5), F2CPoint(22.5, 20.5), F2CPoint(22.5, 22.5),
        F2CPoint(20.5, 22.5), F2CPoint(20.5, 20.5)};
    std::cout << "Area of the inner ring3: " << inner_ring3.area() << std::endl;
    F2CCell cell;
    cell.addRing(outter_ring);
    cell.addRing(inner_ring1);
    cell.addRing(inner_ring2);
    cell.addRing(inner_ring3);
    std::cout << "The area of the cell is: " << cell.area() << std::endl;

    F2CCells cells;
    cells.addGeometry(cell);
    std::cout << "The area of the cells is: " << cells.area() << std::endl;
    
    F2CMultiPoint points {F2CPoint(1, 2), F2CPoint(3, 4)};
    std::cout << "Points contains " << points.size() << " points." << std::endl;
    points.addPoint(5, 6);
    std::cout << "Points contains " << points.size() << " points." << std::endl;
    points.addPoint(p5);
    std::cout << "Points contains " << points.size() << " points." << std::endl;

    // Accessing elements in collections
    F2CPoint p_0 = points.getGeometry(0);
    std::cout << "First point in points: " << p_0 << std::endl;

    p_0 *= 1e5;
    std::cout << "Modified p_0: " << p_0 << std::endl;
    std::cout << "First point in points without modification: " << points.getGeometry(0) << std::endl;
    points.setGeometry(0, p_0);
    std::cout << "Modified first point in points: " << points.getGeometry(0) << std::endl;

    // F2CRobot
    F2CRobot robot (3.0, 39.0);

    // Visualizing Fields2Cover data
    f2c::Visualizer::figure();
    f2c::Visualizer::plot(cells);
    f2c::Visualizer::show();
    // f2c::Visualizer::save("Tutorial_image.png");

    return 0;
}
#include <cmath>
#include "simple_class/map_elements.h"

void road::calcu_leng() {
    const double degToRad = M_PI / 180.0;
    const double earthRadius = 6378137.0;

    double dLat = (end.second - start.second) * degToRad;
    double dLon = (end.first - start.first) * degToRad;

    double meanLat = (end.second + start.second) / 2.0 * degToRad;
    double dx = dLon * earthRadius * cos(meanLat);
    double dy = dLat * earthRadius;

    length = sqrt(dx * dx + dy * dy);
}

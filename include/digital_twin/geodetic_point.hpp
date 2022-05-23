#ifndef GEODETIC_POINT_HPP
#define GEODETIC_POINT_HPP

#include <digital_twin/timestamp.hpp>

namespace digital_twin {

  struct GeodeticPoint {
    Timestamp time;
    
    double latitude;
    double longitude;
    double altitude;
  };

} // namespace digital_twin

#endif // GEODETIC_POINT_HPP

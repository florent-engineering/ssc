#include "TrackGenerator.hpp"
#include "LatitudeLongitudeGenerators.hpp"
#include <algorithm> // std::min, std::max

template <> Track get_min_bound() {return Track({LatitudeLongitude(0,0),LatitudeLongitude(90,90)});}
template <> Track get_max_bound() {return Track({LatitudeLongitude(0,0),LatitudeLongitude(90,90)});}

template <> Track TypedScalarDataGenerator<Track>::get() const
{
    const size_t n = random<size_t>().between(2,20);
    return Track(random_vector_of<LatitudeLongitude>().of_size(n));
}


template <> Angle TypedScalarDataGenerator<Angle>::get() const
{
    return Angle::degree(random<double>().between(0,360));
}


#include "Interval.hpp"

Interval::Interval() : min(+RT_INFINITY), max(-RT_INFINITY) {}
Interval::Interval(const double min, const double max) : min(min), max(max) {}

const Interval Interval::empty = Interval(+RT_INFINITY, -RT_INFINITY);
const Interval Interval::universe = Interval(-RT_INFINITY, +RT_INFINITY);

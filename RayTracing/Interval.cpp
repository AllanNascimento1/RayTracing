#include "Interval.hpp"

Interval::Interval() : min(+RT_INFINITY), max(-RT_INFINITY) {}
Interval::Interval(double min, double max) : min(min), max(max) {}
Interval::Interval(const Interval inter1, const Interval inter2) {
	min = (inter1.min < inter2.min) ? inter1.min : inter2.min;
	max = (inter1.max > inter2.max) ? inter1.max : inter2.max;
}

const Interval Interval::empty = Interval(+RT_INFINITY, -RT_INFINITY);
const Interval Interval::universe = Interval(-RT_INFINITY, +RT_INFINITY);

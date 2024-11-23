#ifndef INTERVAL_H
#define INTERVAL_H

#include <limits>

const double RT_INFINITY = std::numeric_limits<double>::infinity();

class Interval {
	public:
		double max, min;

        Interval();
        Interval(const double min, const double max);

        double size() const {
            return max - min;
        }

        bool contains(double x) const {
            return min <= x && x <= max;
        }

        bool surrounds(double x) const {
            return min < x && x < max;
        }

        double floor(double x) const {
            if (x <min || x>max) {
                return x < min ? min : max;
            }
            return x;
        }

		static const Interval empty, universe;
};

#endif
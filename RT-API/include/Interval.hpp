#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include "SussyUtility.hpp"

class interval {
    public:
    double min, max;

    interval() : min(+sussy::infinity), max(-sussy::infinity) {} // Default interval is empty

    interval(double min, double max) : min(min), max(max) {}

    double size() const {
        return max - min;
    }

    bool contains(double x) const {
        return min <= x && x <= max;
    }

    bool surrounds(double x) const {
        return min < x && x < max;
    }

    static const interval empty, universe;
};

const interval interval::empty    = interval(+sussy::infinity, -sussy::infinity);
const interval interval::universe = interval(-sussy::infinity, +sussy::infinity);

#endif //INTERvAL_HPP
// SPDX-License-Identifier: GPL-3.0-or-later
/*
 * This file is part of Inovesa (github.com/Inovesa/Inovesa).
 * It's copyrighted by the contributors recorded
 * in the version control history of the file.
 */

#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

#include "defines.hpp"

namespace vfps
{

// foreward declaration
template <typename ruler_t> class Ruler;

typedef std::shared_ptr<Ruler<meshaxis_t>> meshRuler_ptr;

template <typename ruler_t>
class Ruler
{
public:
    Ruler() = delete;

    Ruler(meshindex_t steps, ruler_t min, ruler_t max
          , const std::map<std::string,double>& scale)
      : _steps(steps)
      , _max(max)
      , _min(min)
      , _delta((max-min)/static_cast<ruler_t>(steps-1))
      , _scale(scale)
      , _zerobin(((min+max)/(min-max)+1)*(steps-1)/2)
    {
        if (min >= max) {
            throw std::invalid_argument("Tried to set up Ruler with min >= max.");
        }
        ruler_t* meshaxis_tmp = new ruler_t[_steps];

        for (meshindex_t i=0; i<_steps; i++){
            meshaxis_tmp[i] = _min+(ruler_t(i)*_delta);
        }

        _data = meshaxis_tmp;
    }

    Ruler(const Ruler& other) :
        _steps(other._steps),
        _max(other._max),
        _min(other._min),
        _delta(other._delta),
        _scale(other._scale),
        _zerobin(other._zerobin)
    {
        ruler_t* meshaxis_tmp = new ruler_t[_steps];
        std::copy_n(other._data,_steps,meshaxis_tmp);
        _data = meshaxis_tmp;
    }

    ~Ruler() noexcept
    {
        delete [] _data;
    }

    inline const ruler_t& at(meshindex_t d) const
        { return _data[d]; }

    inline const ruler_t* data() const
        { return _data; }

    inline const ruler_t max() const
        {return _max;}

    inline const ruler_t min() const
        { return _min; }

    std::map<std::string,double> scale() const
        { return _scale; }

    inline double scale(std::string unit) const
        { return _scale.at(unit); }

    inline meshindex_t steps() const
        { return _steps; }

    inline const ruler_t delta() const
        { return _delta; }

    inline const ruler_t length() const
        { return _max - _min; }

    inline const ruler_t zerobin() const
        { return _zerobin; }

    inline const ruler_t& operator[](meshindex_t d) const
        { return at(d); }

    /**
     * @brief operator == compares grids
     * @param other grid to compare
     * @return true (same dimensions) or false (different dimensions)
     */
    bool operator==(const Ruler& other) const
    {
        if (_min == other._min && _max == other._max && _steps == other._steps){
            return true;
        } else {
            return false;
        }
    }

protected:
    const ruler_t* _data;

    const meshindex_t _steps;

    const ruler_t _max;

    const ruler_t _min;

    /**
     * @brief _delta step size
     */
    const ruler_t _delta;

    const std::map<std::string,double> _scale;

    const ruler_t _zerobin;
};

}

#pragma once

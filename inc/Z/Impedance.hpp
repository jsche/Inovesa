/******************************************************************************
 * Inovesa - Inovesa Numerical Optimized Vlasov-Equation Solver Application   *
 * Copyright (c) 2014-2016: Patrik Schönfeldt                                 *
 *                                                                            *
 * This file is part of Inovesa.                                              *
 * Inovesa is free software: you can redistribute it and/or modify            *
 * it under the terms of the GNU General Public License as published by       *
 * the Free Software Foundation, either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * Inovesa is distributed in the hope that it will be useful,                 *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with Inovesa.  If not, see <http://www.gnu.org/licenses/>.           *
 ******************************************************************************/

#ifndef IMPEDANCE_HPP
#define IMPEDANCE_HPP

#include <fstream>
#include <string>
#include <vector>

#include "CL/OpenCLHandler.hpp"
#include "defines.hpp"
#include "PS/Ruler.hpp"

namespace vfps
{

class Impedance
{
public:
    /**
     * @brief Impedance basic constructor that initializes everything
     * @param z
     * @param f_max
     */
    Impedance(const std::vector<impedance_t>& z, const frequency_t f_max);

    /**
     * @brief Impedance
     * @param name of datafile in the format "n Re(Z) Im(Z)",
     *        where n=f/f_rev is the revolution harmonic
     */
    Impedance(std::string datafile, double f_max);

    inline const impedance_t* data() const
        { return _data.data(); }

    inline const std::vector<impedance_t>& impedance() const
        { return _data; }

    inline const impedance_t operator[](size_t n) const
        { return _data[n]; }

    inline size_t nFreqs() const
        { return _nfreqs; }

    inline size_t size() const
        { return _data.size(); }

    inline const Ruler<frequency_t>* getRuler() const
        { return &_axis; }

    cl::Buffer data_buf;

    static constexpr double factor4Ohms = 1;

private:
    size_t _nfreqs;

    const Ruler<frequency_t> _axis;

protected:
    std::vector<impedance_t> _data;

    void syncCLMem();

private:
    static std::vector<impedance_t> readData(std::string fname);

    /**
     * @brief upper_power_of_two
     * @param v
     * @return
     *
     * see http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
     */
    uint64_t upper_power_of_two(uint64_t v);
};

} // namespace vfps

#endif // IMPEDANCE_HPP

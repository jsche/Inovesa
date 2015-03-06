/******************************************************************************/
/* Inovesa - Inovesa Numerical Optimized Vlesov-Equation Solver Application   */
/* Copyright (c) 2014-2015: Patrik Schönfeldt                                 */
/*                                                                            */
/* This file is part of Inovesa.                                              */
/* Inovesa is free software: you can redistribute it and/or modify            */
/* it under the terms of the GNU General Public License as published by       */
/* the Free Software Foundation, either version 3 of the License, or          */
/* (at your option) any later version.                                        */
/*                                                                            */
/* Inovesa is distributed in the hope that it will be useful,                 */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of             */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              */
/* GNU General Public License for more details.                               */
/*                                                                            */
/* You should have received a copy of the GNU General Public License          */
/* along with Inovesa.  If not, see <http://www.gnu.org/licenses/>.           */
/******************************************************************************/

#include "HM/WakeKickMap.hpp"

vfps::WakeKickMap::WakeKickMap(vfps::PhaseSpace* in, vfps::PhaseSpace* out,
					const size_t xsize, const size_t ysize,
					const std::array<vfps::integral_t,2*ps_xsize> wake) :
	HeritageMap(in,out,xsize,ysize),
	_wake(wake)
{
}

void vfps::WakeKickMap::apply()
{
	integral_t* density = _in->projectionToX();
	for (unsigned int i=0;i<_xsize;i++) {
		_wakeforce[i] = 0;
		for (unsigned int j=0;j<_xsize;j++) {
			_wakeforce[i] += meshaxis_t(density[j]*_wake[_xsize+i-j]);
		}
	}
	// translate force into HM

	// call original apply method
	HeritageMap::apply();
}

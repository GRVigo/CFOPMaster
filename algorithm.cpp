/*  This file is part of "GR Cube"

	Copyright (C) 2020 German Ramos Rodriguez

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	German Ramos Rodriguez
	Vigo, Spain
	grvigo@hotmail.com
*/

#include <iostream>
#include <random>
#include <vector>

#include "algorithm.h"

using namespace std;

namespace grcube3
{
	const Steps Algorithm::m_inverted[] = // Array to get the inverted movements
	{
		Steps::NONE,
	
		// Single layer
		Steps::Up, Steps::U, Steps::U2,
		Steps::Dp, Steps::D, Steps::D2,
		Steps::Fp, Steps::F, Steps::F2,
		Steps::Bp, Steps::B, Steps::B2,
		Steps::Rp, Steps::R, Steps::R2,
		Steps::Lp, Steps::L, Steps::L2,
	
		// Double layer
		Steps::up, Steps::u, Steps::u2,
		Steps::dp, Steps::d, Steps::d2,
		Steps::fp, Steps::f, Steps::f2,
		Steps::bp, Steps::b, Steps::b2,
		Steps::rp, Steps::r, Steps::r2,
		Steps::lp, Steps::l, Steps::l2,
	
		// Middle layers
		Steps::Ep, Steps::E, Steps::E2,
		Steps::Sp, Steps::S, Steps::S2,
		Steps::Mp, Steps::M, Steps::M2,
	
		// Full cube
		Steps::xp, Steps::x, Steps::x2,
		Steps::yp, Steps::y, Steps::y2,
		Steps::zp, Steps::z, Steps::z2,
	
		// Parentheses --limited to a maximum 9 repetitions--
		Steps::PARENTHESIS_OPEN, 		// "("
		Steps::PARENTHESIS_CLOSE_1_REP, // ")"
		Steps::PARENTHESIS_CLOSE_2_REP,	// ")2"
		Steps::PARENTHESIS_CLOSE_3_REP,	// ")3"
		Steps::PARENTHESIS_CLOSE_4_REP,	// ")4"
		Steps::PARENTHESIS_CLOSE_5_REP,	// ")5"
		Steps::PARENTHESIS_CLOSE_6_REP,	// ")6"
		Steps::PARENTHESIS_CLOSE_7_REP,	// ")7"
		Steps::PARENTHESIS_CLOSE_8_REP,	// ")8"
		Steps::PARENTHESIS_CLOSE_9_REP	// ")9"
	};
	
	const Steps Algorithm::m_symmetrical[] = // Array to get the symmetrical movements
	{
		Steps::NONE,
	
		// Single layer
		Steps::D, Steps::Dp, Steps::D2,
		Steps::U, Steps::Up, Steps::U2,
		Steps::B, Steps::Bp, Steps::B2,
		Steps::F, Steps::Fp, Steps::F2,
		Steps::L, Steps::Lp, Steps::L2,
		Steps::R, Steps::Rp, Steps::R2,
	
		// Double layer
		Steps::d, Steps::dp, Steps::d2,
		Steps::u, Steps::up, Steps::u2,
		Steps::b, Steps::bp, Steps::b2,
		Steps::f, Steps::fp, Steps::f2,
		Steps::l, Steps::lp, Steps::l2,
		Steps::r, Steps::rp, Steps::r2,
	
		// Middle layers
		Steps::E, Steps::Ep, Steps::E2,
		Steps::S, Steps::Sp, Steps::S2,
		Steps::M, Steps::Mp, Steps::M2,
	
		// Full cube
		Steps::x, Steps::xp, Steps::x2,
		Steps::y, Steps::yp, Steps::y2,
		Steps::z, Steps::zp, Steps::z2,
	
		// Parentheses --limited to a maximum 9 repetitions--
		Steps::PARENTHESIS_OPEN, 		// "("
		Steps::PARENTHESIS_CLOSE_1_REP, // ")"
		Steps::PARENTHESIS_CLOSE_2_REP,	// ")2"
		Steps::PARENTHESIS_CLOSE_3_REP,	// ")3"
		Steps::PARENTHESIS_CLOSE_4_REP,	// ")4"
		Steps::PARENTHESIS_CLOSE_5_REP,	// ")5"
		Steps::PARENTHESIS_CLOSE_6_REP,	// ")6"
		Steps::PARENTHESIS_CLOSE_7_REP,	// ")7"
		Steps::PARENTHESIS_CLOSE_8_REP,	// ")8"
		Steps::PARENTHESIS_CLOSE_9_REP	// ")9"
	};
	
	const Steps Algorithm::m_x[] = // Array for x turn
	{
		Steps::NONE,
	
		// Single layer movements
		Steps::B, Steps::Bp, Steps::B2,
		Steps::F, Steps::Fp, Steps::F2,
		Steps::U, Steps::Up, Steps::U2,
		Steps::D, Steps::Dp, Steps::D2,
		Steps::R, Steps::Rp, Steps::R2,
		Steps::L, Steps::Lp, Steps::L2,
	
		// Double layer movements
		Steps::b, Steps::bp, Steps::b2,
		Steps::f, Steps::fp, Steps::f2,
		Steps::u, Steps::up, Steps::u2,
		Steps::d, Steps::dp, Steps::d2,
		Steps::r, Steps::rp, Steps::r2,
		Steps::l, Steps::lp, Steps::l2,
	
		// Middle layer movements
		Steps::Sp, Steps::S, Steps::S2,
		Steps::E, Steps::Ep, Steps::E2,
		Steps::M, Steps::Mp, Steps::M2,
	
		// Full cube turns
		Steps::x, Steps::xp, Steps::x2,
		Steps::zp, Steps::z, Steps::z2,
		Steps::y, Steps::yp, Steps::y2,
	
		// Parentheses --limited to a maximum 9 repetitions--
		Steps::PARENTHESIS_OPEN, 		// "("
		Steps::PARENTHESIS_CLOSE_1_REP, // ")"
		Steps::PARENTHESIS_CLOSE_2_REP,	// ")2"
		Steps::PARENTHESIS_CLOSE_3_REP,	// ")3"
		Steps::PARENTHESIS_CLOSE_4_REP,	// ")4"
		Steps::PARENTHESIS_CLOSE_5_REP,	// ")5"
		Steps::PARENTHESIS_CLOSE_6_REP,	// ")6"
		Steps::PARENTHESIS_CLOSE_7_REP,	// ")7"
		Steps::PARENTHESIS_CLOSE_8_REP,	// ")8"
		Steps::PARENTHESIS_CLOSE_9_REP	// ")9"
	};
	
	const Steps Algorithm::m_xp[] = // Array for x' turn
	{
		Steps::NONE,
		
		// Single layer movements
		Steps::F, Steps::Fp, Steps::F2,
		Steps::B, Steps::Bp, Steps::B2,
		Steps::D, Steps::Dp, Steps::D2,
		Steps::U, Steps::Up, Steps::U2,
		Steps::R, Steps::Rp, Steps::R2,
		Steps::L, Steps::Lp, Steps::L2,
		
		// Double layer movements
		Steps::f, Steps::fp, Steps::f2,
		Steps::b, Steps::bp, Steps::b2,
		Steps::d, Steps::dp, Steps::d2,
		Steps::u, Steps::up, Steps::u2,
		Steps::r, Steps::rp, Steps::r2,
		Steps::l, Steps::lp, Steps::l2,
		
		// Middle layer movements
		Steps::S, Steps::Sp, Steps::S2,
		Steps::Ep, Steps::E, Steps::E2,
		Steps::M, Steps::Mp, Steps::M2,
		
		// Full cube turns
		Steps::x, Steps::xp, Steps::x2,
		Steps::z, Steps::zp, Steps::z2,
		Steps::yp, Steps::y, Steps::y2,
		
		// Parentheses --limited to a maximum 9 repetitions--
		Steps::PARENTHESIS_OPEN, 		// "("
		Steps::PARENTHESIS_CLOSE_1_REP, // ")"
		Steps::PARENTHESIS_CLOSE_2_REP,	// ")2"
		Steps::PARENTHESIS_CLOSE_3_REP,	// ")3"
		Steps::PARENTHESIS_CLOSE_4_REP,	// ")4"
		Steps::PARENTHESIS_CLOSE_5_REP,	// ")5"
		Steps::PARENTHESIS_CLOSE_6_REP,	// ")6"
		Steps::PARENTHESIS_CLOSE_7_REP,	// ")7"
		Steps::PARENTHESIS_CLOSE_8_REP,	// ")8"
		Steps::PARENTHESIS_CLOSE_9_REP	// ")9"
	};
	
	const Steps Algorithm::m_x2[] = // Array for x2 turn
	{
	 	Steps::NONE,
		 
		// Single layer movements
		Steps::D, Steps::Dp, Steps::D2,
		Steps::U, Steps::Up, Steps::U2,
		Steps::B, Steps::Bp, Steps::B2,
		Steps::F, Steps::Fp, Steps::F2,
		Steps::R, Steps::Rp, Steps::R2,
		Steps::L, Steps::Lp, Steps::L2,
		 
		// Double layer movements
		Steps::d, Steps::dp, Steps::d2,
		Steps::u, Steps::up, Steps::u2,
		Steps::b, Steps::bp, Steps::b2,
		Steps::f, Steps::fp, Steps::f2,
		Steps::r, Steps::rp, Steps::r2,
		Steps::l, Steps::lp, Steps::l2,
		
		// Middle layer movements
		Steps::Ep, Steps::E, Steps::E2,
		Steps::Sp, Steps::S, Steps::S2,
		Steps::M, Steps::Mp, Steps::M2,
		
		// Full cube turns
		Steps::x, Steps::xp, Steps::x2,
		Steps::yp, Steps::y, Steps::y2,
		Steps::zp, Steps::z, Steps::z2,
	
		// Parentheses --limited to a maximum 9 repetitions--
		Steps::PARENTHESIS_OPEN, 		// "("
		Steps::PARENTHESIS_CLOSE_1_REP, // ")"
		Steps::PARENTHESIS_CLOSE_2_REP,	// ")2"
		Steps::PARENTHESIS_CLOSE_3_REP,	// ")3"
		Steps::PARENTHESIS_CLOSE_4_REP,	// ")4"
		Steps::PARENTHESIS_CLOSE_5_REP,	// ")5"
		Steps::PARENTHESIS_CLOSE_6_REP,	// ")6"
		Steps::PARENTHESIS_CLOSE_7_REP,	// ")7"
		Steps::PARENTHESIS_CLOSE_8_REP,	// ")8"
		Steps::PARENTHESIS_CLOSE_9_REP	// ")9"
	};
	
	const Steps Algorithm::m_y[] = // Array for y turn
	{
		Steps::NONE,
	
		// Single layer movements
	    Steps::U, Steps::Up, Steps::U2,
	    Steps::D, Steps::Dp, Steps::D2,
	    Steps::L, Steps::Lp, Steps::L2,
	    Steps::R, Steps::Rp, Steps::R2,
	    Steps::F, Steps::Fp, Steps::F2,
	    Steps::B, Steps::Bp, Steps::B2,
	
	    // Double layer movements
	    Steps::u, Steps::up, Steps::u2,
	    Steps::d, Steps::dp, Steps::d2,
	    Steps::l, Steps::lp, Steps::l2,
	    Steps::r, Steps::rp, Steps::r2,
	    Steps::f, Steps::fp, Steps::f2,
	    Steps::b, Steps::bp, Steps::b2,
	
	    // Middle layers movememts
	    Steps::E, Steps::Ep, Steps::E2,
	    Steps::Mp, Steps::M, Steps::M2,
	    Steps::S, Steps::Sp, Steps::S2,
	
	    // Full cube turns
	    Steps::z, Steps::zp, Steps::z2,
	    Steps::y, Steps::yp, Steps::y2,
	    Steps::xp, Steps::x, Steps::x2,
	
		// Parentheses --limited to a maximum 9 repetitions--
		Steps::PARENTHESIS_OPEN, 		// "("
		Steps::PARENTHESIS_CLOSE_1_REP, // ")"
		Steps::PARENTHESIS_CLOSE_2_REP,	// ")2"
		Steps::PARENTHESIS_CLOSE_3_REP,	// ")3"
		Steps::PARENTHESIS_CLOSE_4_REP,	// ")4"
		Steps::PARENTHESIS_CLOSE_5_REP,	// ")5"
		Steps::PARENTHESIS_CLOSE_6_REP,	// ")6"
		Steps::PARENTHESIS_CLOSE_7_REP,	// ")7"
		Steps::PARENTHESIS_CLOSE_8_REP,	// ")8"
		Steps::PARENTHESIS_CLOSE_9_REP	// ")9"
	};
	
	const Steps Algorithm::m_yp[] = // Array for y' turn
	{
		Steps::NONE,
		
		// Single layer movements
		Steps::U, Steps::Up, Steps::U2,
		Steps::D, Steps::Dp, Steps::D2,
		Steps::R, Steps::Rp, Steps::R2,
		Steps::L, Steps::Lp, Steps::L2,
		Steps::B, Steps::Bp, Steps::B2,
		Steps::F, Steps::Fp, Steps::F2,
		
		// Double layer movements
		Steps::u, Steps::up, Steps::u2,
		Steps::d, Steps::dp, Steps::d2,
		Steps::r, Steps::rp, Steps::r2,
		Steps::l, Steps::lp, Steps::l2,
		Steps::b, Steps::bp, Steps::b2,
		Steps::f, Steps::fp, Steps::f2,
		
		// Middle layers movememts
		Steps::E, Steps::Ep, Steps::E2,
		Steps::M, Steps::Mp, Steps::M2,
		Steps::Sp, Steps::S, Steps::S2,
		
		// Full cube turns
		Steps::zp, Steps::z, Steps::z2,
		Steps::y, Steps::yp, Steps::y2,
		Steps::x, Steps::xp, Steps::x2,
		
		// Parentheses --limited to a maximum 9 repetitions--
		Steps::PARENTHESIS_OPEN, 		// "("
		Steps::PARENTHESIS_CLOSE_1_REP, // ")"
		Steps::PARENTHESIS_CLOSE_2_REP,	// ")2"
		Steps::PARENTHESIS_CLOSE_3_REP,	// ")3"
		Steps::PARENTHESIS_CLOSE_4_REP,	// ")4"
		Steps::PARENTHESIS_CLOSE_5_REP,	// ")5"
		Steps::PARENTHESIS_CLOSE_6_REP,	// ")6"
		Steps::PARENTHESIS_CLOSE_7_REP,	// ")7"
		Steps::PARENTHESIS_CLOSE_8_REP,	// ")8"
		Steps::PARENTHESIS_CLOSE_9_REP	// ")9"
	};
	
	const Steps Algorithm::m_y2[] = // Array for y2 turn
	{
		Steps::NONE,
		
		// Single layer movements
		Steps::U, Steps::Up, Steps::U2,
		Steps::D, Steps::Dp, Steps::D2,
		Steps::B, Steps::Bp, Steps::B2,
		Steps::F, Steps::Fp, Steps::F2,
		Steps::L, Steps::Lp, Steps::L2,
		Steps::R, Steps::Rp, Steps::R2,
		
		// Double layer movements
		Steps::u, Steps::up, Steps::u2,
		Steps::d, Steps::dp, Steps::d2,
		Steps::b, Steps::bp, Steps::b2,
		Steps::f, Steps::fp, Steps::f2,
		Steps::l, Steps::lp, Steps::l2,
		Steps::r, Steps::rp, Steps::r2,
		
		// Middle layers movememts
		Steps::E, Steps::Ep, Steps::E2,
		Steps::Sp, Steps::S, Steps::S2,
		Steps::Mp, Steps::M, Steps::M2,
		
		// Full cube turns
		Steps::xp, Steps::x, Steps::x2,
		Steps::y, Steps::yp, Steps::y2,
		Steps::zp, Steps::z, Steps::z2,
		
		// Parentheses --limited to a maximum 9 repetitions--
		Steps::PARENTHESIS_OPEN, 		// "("
		Steps::PARENTHESIS_CLOSE_1_REP, // ")"
		Steps::PARENTHESIS_CLOSE_2_REP,	// ")2"
		Steps::PARENTHESIS_CLOSE_3_REP,	// ")3"
		Steps::PARENTHESIS_CLOSE_4_REP,	// ")4"
		Steps::PARENTHESIS_CLOSE_5_REP,	// ")5"
		Steps::PARENTHESIS_CLOSE_6_REP,	// ")6"
		Steps::PARENTHESIS_CLOSE_7_REP,	// ")7"
		Steps::PARENTHESIS_CLOSE_8_REP,	// ")8"
		Steps::PARENTHESIS_CLOSE_9_REP	// ")9"
	};
	
	const Steps Algorithm::m_z[] = // Array for z turn
	{
		Steps::NONE,
	
	    // Single layer movements
		Steps::R, Steps::Rp, Steps::R2,
	    Steps::L, Steps::Lp, Steps::L2,
	    Steps::F, Steps::Fp, Steps::F2,
	    Steps::B, Steps::Bp, Steps::B2,
	    Steps::D, Steps::Dp, Steps::D2,
	    Steps::U, Steps::Up, Steps::U2,
	
	    // Double layer movements
	    Steps::r, Steps::rp, Steps::r2,
	    Steps::l, Steps::lp, Steps::l2,
	    Steps::f, Steps::fp, Steps::f2,
	    Steps::b, Steps::bp, Steps::b2,
	    Steps::d, Steps::dp, Steps::d2,
	    Steps::u, Steps::up, Steps::u2,
	
	    // Middle layers movememts
	    Steps::M, Steps::Mp, Steps::M2,
	    Steps::S, Steps::Sp, Steps::S2,
	    Steps::Ep, Steps::E, Steps::E2,
	
	    // Full cube turns
	    Steps::yp, Steps::y, Steps::y2,
	    Steps::x, Steps::xp, Steps::x2,
	    Steps::z, Steps::zp, Steps::z2,
	
		// Parentheses --limited to a maximum 9 repetitions--
		Steps::PARENTHESIS_OPEN, 		// "("
		Steps::PARENTHESIS_CLOSE_1_REP, // ")"
		Steps::PARENTHESIS_CLOSE_2_REP,	// ")2"
		Steps::PARENTHESIS_CLOSE_3_REP,	// ")3"
		Steps::PARENTHESIS_CLOSE_4_REP,	// ")4"
		Steps::PARENTHESIS_CLOSE_5_REP,	// ")5"
		Steps::PARENTHESIS_CLOSE_6_REP,	// ")6"
		Steps::PARENTHESIS_CLOSE_7_REP,	// ")7"
		Steps::PARENTHESIS_CLOSE_8_REP,	// ")8"
		Steps::PARENTHESIS_CLOSE_9_REP	// ")9"
	};
	
	const Steps Algorithm::m_zp[] = // Array for z' turn
	{
		Steps::NONE,
	
	    // Single layer movements
		Steps::L, Steps::Lp, Steps::L2,
	    Steps::R, Steps::Rp, Steps::R2,
	    Steps::F, Steps::Fp, Steps::F2,
	    Steps::B, Steps::Bp, Steps::B2,
	    Steps::U, Steps::Up, Steps::U2,
	    Steps::D, Steps::Dp, Steps::D2,
	
	    // Double layer movements 
	    Steps::l, Steps::lp, Steps::l2,
	    Steps::r, Steps::rp, Steps::r2,
	    Steps::f, Steps::fp, Steps::f2,
	    Steps::b, Steps::bp, Steps::b2,
	    Steps::u, Steps::up, Steps::u2,
	    Steps::d, Steps::dp, Steps::d2,
	
	    // Middle layers movememts
	    Steps::Mp, Steps::M, Steps::M2,
	    Steps::S, Steps::Sp, Steps::S2,
	    Steps::E, Steps::Ep, Steps::E2,
	
	    // Full cube turns
	    Steps::y, Steps::yp, Steps::y2,
	    Steps::xp, Steps::x, Steps::x2,
	    Steps::z, Steps::zp, Steps::z2,
	
		// Parentheses --limited to a maximum 9 repetitions--
		Steps::PARENTHESIS_OPEN, 		// "("
		Steps::PARENTHESIS_CLOSE_1_REP, // ")"
		Steps::PARENTHESIS_CLOSE_2_REP,	// ")2"
		Steps::PARENTHESIS_CLOSE_3_REP,	// ")3"
		Steps::PARENTHESIS_CLOSE_4_REP,	// ")4"
		Steps::PARENTHESIS_CLOSE_5_REP,	// ")5"
		Steps::PARENTHESIS_CLOSE_6_REP,	// ")6"
		Steps::PARENTHESIS_CLOSE_7_REP,	// ")7"
		Steps::PARENTHESIS_CLOSE_8_REP,	// ")8"
		Steps::PARENTHESIS_CLOSE_9_REP	// ")9"
	};
	
	const Steps Algorithm::m_z2[] = // Array for z2 turn
	{
		Steps::NONE,
	
	    // Single layer movements
		Steps::D, Steps::Dp, Steps::D2,
	    Steps::U, Steps::Up, Steps::U2,
	    Steps::F, Steps::Fp, Steps::F2,
	    Steps::B, Steps::Bp, Steps::B2,
	    Steps::L, Steps::Lp, Steps::L2,
	    Steps::R, Steps::Rp, Steps::R2,
	
	    // Double layer movements
	    Steps::d, Steps::dp, Steps::d2,
	    Steps::u, Steps::up, Steps::u2,
	    Steps::f, Steps::fp, Steps::f2,
	    Steps::b, Steps::bp, Steps::b2,
	    Steps::l, Steps::lp, Steps::l2,
	    Steps::r, Steps::rp, Steps::r2,
	
	    // Middle layers movememts
	    Steps::Ep, Steps::E, Steps::E2,
	    Steps::S, Steps::Sp, Steps::S2,
	    Steps::Mp, Steps::M, Steps::M2,
	
	    // Full cube turns
	    Steps::xp, Steps::x, Steps::x2,
	    Steps::yp, Steps::y, Steps::y2,
	    Steps::z, Steps::zp, Steps::z2,
	
		// Parentheses --limited to a maximum 9 repetitions--
		Steps::PARENTHESIS_OPEN, 		// "("
		Steps::PARENTHESIS_CLOSE_1_REP, // ")"
		Steps::PARENTHESIS_CLOSE_2_REP,	// ")2"
		Steps::PARENTHESIS_CLOSE_3_REP,	// ")3"
		Steps::PARENTHESIS_CLOSE_4_REP,	// ")4"
		Steps::PARENTHESIS_CLOSE_5_REP,	// ")5"
		Steps::PARENTHESIS_CLOSE_6_REP,	// ")6"
		Steps::PARENTHESIS_CLOSE_7_REP,	// ")7"
		Steps::PARENTHESIS_CLOSE_8_REP,	// ")8"
		Steps::PARENTHESIS_CLOSE_9_REP	// ")9"
	};
	
	const Steps Algorithm::m_sequence[][3] = // Array of equivalent three movements sequence
	{
		{ Steps::NONE, Steps::NONE, Steps::NONE }, // NONE
	
		// Single layer
		{ Steps::U, Steps::NONE, Steps::NONE },    // U
		{ Steps::Up, Steps::NONE, Steps::NONE },   // U'
		{ Steps::U2, Steps::NONE, Steps::NONE },   // U2
		{ Steps::D, Steps::NONE, Steps::NONE },    // D
		{ Steps::Dp, Steps::NONE, Steps::NONE },   // D'
		{ Steps::D2, Steps::NONE, Steps::NONE },   // D2
		{ Steps::F, Steps::NONE, Steps::NONE },    // F
		{ Steps::Fp, Steps::NONE, Steps::NONE },   // F'
		{ Steps::F2, Steps::NONE, Steps::NONE },   // F2
		{ Steps::B, Steps::NONE, Steps::NONE },    // B
		{ Steps::Bp, Steps::NONE, Steps::NONE },   // B'
		{ Steps::B2, Steps::NONE, Steps::NONE },   // B2
		{ Steps::R, Steps::NONE, Steps::NONE },    // R
		{ Steps::Rp, Steps::NONE, Steps::NONE },   // R'
		{ Steps::R2, Steps::NONE, Steps::NONE },   // R2
		{ Steps::L, Steps::NONE, Steps::NONE },    // L
		{ Steps::Lp, Steps::NONE, Steps::NONE },   // L'
		{ Steps::L2, Steps::NONE, Steps::NONE },   // L2
	
		// Double layer, adjacent layers, same direction
		{ Steps::D, Steps::y, Steps::NONE },       // u
		{ Steps::Dp, Steps::yp, Steps::NONE },     // u'
		{ Steps::D2, Steps::y2, Steps::NONE },     // u2
		{ Steps::U, Steps::yp, Steps::NONE },      // d
		{ Steps::Up, Steps::y, Steps::NONE },      // d'
		{ Steps::U2, Steps::y2, Steps::NONE },     // d2
		{ Steps::B, Steps::z, Steps::NONE },       // f
		{ Steps::Bp, Steps::zp, Steps::NONE },     // f'
		{ Steps::B2, Steps::z2, Steps::NONE },     // f2
		{ Steps::F, Steps::zp, Steps::NONE },      // b
		{ Steps::Fp, Steps::z, Steps::NONE },      // b'
		{ Steps::F2, Steps::z2, Steps::NONE },     // b2
		{ Steps::L, Steps::x, Steps::NONE },       // r
		{ Steps::Lp, Steps::xp, Steps::NONE },     // r'
		{ Steps::L2, Steps::x2, Steps::NONE },     // r2
		{ Steps::R, Steps::xp, Steps::NONE },      // l
		{ Steps::Rp, Steps::x, Steps::NONE },      // l'
		{ Steps::R2, Steps::x2, Steps::NONE },     // l2
	
		// Middle layers
		{ Steps::U, Steps::Dp, Steps::yp },        // E -> As layer D
		{ Steps::Up, Steps::D, Steps::y },         // E'
		{ Steps::U2, Steps::D2, Steps::y2 },       // E2
		{ Steps::Fp, Steps::B, Steps::z },         // S -> As layer F
		{ Steps::F, Steps::Bp, Steps::zp },        // S'
		{ Steps::F2, Steps::B2, Steps::z2 },       // S2
		{ Steps::R, Steps::Lp, Steps::xp },        // M -> As layer L
		{ Steps::Rp, Steps::L, Steps::x },         // M'
		{ Steps::R2, Steps::L2, Steps::x2 },       // M2
	
		// Full cube
		{ Steps::x, Steps::NONE, Steps::NONE },    // x
		{ Steps::xp, Steps::NONE, Steps::NONE },   // x'
		{ Steps::x2, Steps::NONE, Steps::NONE },   // x2
		{ Steps::y, Steps::NONE, Steps::NONE },    // y
		{ Steps::yp, Steps::NONE, Steps::NONE },   // y'
		{ Steps::y2, Steps::NONE, Steps::NONE },   // y2
		{ Steps::z, Steps::NONE, Steps::NONE },    // z
		{ Steps::zp, Steps::NONE, Steps::NONE },   // z'
		{ Steps::z2, Steps::NONE, Steps::NONE },   // z2
	
		// Parentheses
		{ Steps::PARENTHESIS_OPEN, Steps::NONE, Steps::NONE },
		{ Steps::PARENTHESIS_CLOSE_1_REP, Steps::NONE, Steps::NONE },
		{ Steps::PARENTHESIS_CLOSE_2_REP, Steps::NONE, Steps::NONE },
		{ Steps::PARENTHESIS_CLOSE_3_REP, Steps::NONE, Steps::NONE },
		{ Steps::PARENTHESIS_CLOSE_4_REP, Steps::NONE, Steps::NONE },
		{ Steps::PARENTHESIS_CLOSE_5_REP, Steps::NONE, Steps::NONE },
		{ Steps::PARENTHESIS_CLOSE_6_REP, Steps::NONE, Steps::NONE },
		{ Steps::PARENTHESIS_CLOSE_7_REP, Steps::NONE, Steps::NONE },
		{ Steps::PARENTHESIS_CLOSE_8_REP, Steps::NONE, Steps::NONE },
		{ Steps::PARENTHESIS_CLOSE_9_REP, Steps::NONE, Steps::NONE }
	};
	
	const Layers Algorithm::m_layer[] = // Array for get movements layer
	{
		Layers::NONE,
	
		// Single layer
		Layers::U, Layers::U, Layers::U,
		Layers::D, Layers::D, Layers::D,
		Layers::F, Layers::F, Layers::F,
		Layers::B, Layers::B, Layers::B,
		Layers::R, Layers::R, Layers::R,
		Layers::L, Layers::L, Layers::L,
	
		// Double layer
		Layers::U, Layers::U, Layers::U,
		Layers::D, Layers::D, Layers::D,
		Layers::F, Layers::F, Layers::F,
		Layers::B, Layers::B, Layers::B,
		Layers::R, Layers::R, Layers::R,
		Layers::L, Layers::L, Layers::L,
	
		// Middle layers
		Layers::E, Layers::E, Layers::E,
		Layers::S, Layers::S, Layers::S,
		Layers::M, Layers::M, Layers::M,
	
		// Full cube
		Layers::R, Layers::R, Layers::R,
		Layers::U, Layers::U, Layers::U,
		Layers::F, Layers::F, Layers::F,
	
		// Parentheses
		Layers::NONE,
		Layers::NONE,
		Layers::NONE,
		Layers::NONE,
		Layers::NONE,
		Layers::NONE,
		Layers::NONE,
		Layers::NONE,
		Layers::NONE,
		Layers::NONE
	};
	
	const Layers Algorithm::m_layer_opposite[] = // Array for get movements opposite layer
	{
		Layers::NONE,
	
		// Single layer
		Layers::D, Layers::D, Layers::D,
		Layers::U, Layers::U, Layers::U,
		Layers::B, Layers::B, Layers::B,
		Layers::F, Layers::F, Layers::F,
		Layers::L, Layers::L, Layers::L,
		Layers::R, Layers::R, Layers::R,
	
		// Double layer
		Layers::D, Layers::D, Layers::D,
		Layers::U, Layers::U, Layers::U,
		Layers::B, Layers::B, Layers::B,
		Layers::F, Layers::F, Layers::F,
		Layers::L, Layers::L, Layers::L,
		Layers::R, Layers::R, Layers::R,
	
		// Middle layers
		Layers::E, Layers::E, Layers::E,
		Layers::S, Layers::S, Layers::S,
		Layers::M, Layers::M, Layers::M,
	
		// Full cube
		Layers::R, Layers::R, Layers::R,
		Layers::U, Layers::U, Layers::U,
		Layers::F, Layers::F, Layers::F,
	
		// Parentheses
		Layers::NONE,
		Layers::NONE,
		Layers::NONE,
		Layers::NONE,
		Layers::NONE,
		Layers::NONE,
		Layers::NONE,
		Layers::NONE,
		Layers::NONE,
		Layers::NONE
	};
	
	const Ranges Algorithm::m_range[] = // Array for get movements range
	{
		Ranges::NONE,
	
		// Single layer
		Ranges::SINGLE, Ranges::SINGLE, Ranges::SINGLE,
		Ranges::SINGLE, Ranges::SINGLE, Ranges::SINGLE,
		Ranges::SINGLE, Ranges::SINGLE, Ranges::SINGLE,
		Ranges::SINGLE, Ranges::SINGLE, Ranges::SINGLE,
		Ranges::SINGLE, Ranges::SINGLE, Ranges::SINGLE,
		Ranges::SINGLE, Ranges::SINGLE, Ranges::SINGLE,
	
		// Double layer
		Ranges::DOUBLE, Ranges::DOUBLE, Ranges::DOUBLE,
		Ranges::DOUBLE, Ranges::DOUBLE, Ranges::DOUBLE,
		Ranges::DOUBLE, Ranges::DOUBLE, Ranges::DOUBLE,
		Ranges::DOUBLE, Ranges::DOUBLE, Ranges::DOUBLE,
		Ranges::DOUBLE, Ranges::DOUBLE, Ranges::DOUBLE,
		Ranges::DOUBLE, Ranges::DOUBLE, Ranges::DOUBLE,
	
		// Middle layers
		Ranges::INTERNAL, Ranges::INTERNAL, Ranges::INTERNAL,
		Ranges::INTERNAL, Ranges::INTERNAL, Ranges::INTERNAL,
		Ranges::INTERNAL, Ranges::INTERNAL, Ranges::INTERNAL,
	
		// Full cube
		Ranges::TURN, Ranges::TURN, Ranges::TURN,
		Ranges::TURN, Ranges::TURN, Ranges::TURN,
		Ranges::TURN, Ranges::TURN, Ranges::TURN,
	
		// Parentheses
		Ranges::PARENTHESES,
		Ranges::PARENTHESES,
		Ranges::PARENTHESES,
		Ranges::PARENTHESES,
		Ranges::PARENTHESES,
		Ranges::PARENTHESES,
		Ranges::PARENTHESES,
		Ranges::PARENTHESES,
		Ranges::PARENTHESES,
		Ranges::PARENTHESES
	};
	
	// Array with allowed chars in an algorithm
	constexpr auto m_chars_SIZE = 33;
	const char Algorithm::m_chars[m_chars_SIZE] = 
	{ 
		'U', 'D', 'F', 'B', 'R', 'L',
		'u', 'd', 'f', 'b', 'r', 'l', 'w',
		'E', 'S', 'M',
		'x', 'y', 'z', 'X', 'Y', 'Z',
		'\'', 
		'(', ')',
		'2', '3', '4', '5', '6', '7', '8', '9'
	};
	
	 // Array with steps string representation
	const string Algorithm::m_strings[]
	{
		"", // No movement
	
		// Single layer
		"U", "U'", "U2",
		"D", "D'", "D2",
		"F", "F'", "F2",
		"B", "B'", "B2",
		"R", "R'", "R2",
		"L", "L'", "L2",
	
		// Double layer
		"u", "u'", "u2",
		"d", "d'", "d2",
		"f", "f'", "f2",
		"b", "b'", "b2",
		"r", "r'", "r2",
		"l", "l'", "l2",
	
		// Middle layers
		"E", "E'", "E2",
		"S", "S'", "S2",
		"M", "M'", "M2",
	
		// Full cube
		"x", "x'", "x2",
		"y", "y'", "y2",
		"z", "z'", "z2",
	
		// Parentheses --limited to a maximum of 9 repetitions--
		"(",
		")",
		")2",
		")3",
		")4",
		")5",
		")6",
		")7",
		")8",
		")9"
	};
	
	// Equal operator
	bool Algorithm::operator==(Algorithm& rhalg) const
	{
		uint size = GetSize();
		if (size != rhalg.GetSize()) return false;
		for (uint i = 0u; i < size; i++) if (Movs[i] != rhalg[i]) return false;
		return true;
	}

	// Not equal operator
	bool Algorithm::operator!=(Algorithm& rhalg) const
	{
		uint size = GetSize();
		if (size != rhalg.GetSize()) return true;
		for (uint i = 0u; i < size; i++) if (Movs[i] != rhalg[i]) return true;
		return false;
	}

	// Addition operator
	Algorithm Algorithm::operator+(Algorithm& rhalg)
	{
		Algorithm Aux = *this;
		uint size = rhalg.GetSize();
		for (uint i = 0u; i < size; i++) Aux.Append(rhalg[i]);
		return Aux;
	}

	 // Step addition operator
	Algorithm Algorithm::operator+(Steps rhalg)
	{
		Algorithm Aux = *this;
		Aux.Append(rhalg);
		return Aux;
	}
	
	// Erase single movement (step) in given position
	bool Algorithm::Erase(const uint pos) 
	{
        if (pos < GetSize())
        {
            Movs.erase(Movs.begin() + pos);
			return true;
        }
		return false;
    }

	// Erase movements (steps) in given range
	bool Algorithm::Erase(const uint pos, const uint len)
	{
		if (pos < GetSize() && pos + len <= GetSize())
		{
			Movs.erase(Movs.begin() + pos, Movs.begin() + pos + len);
			return true;
		}
		return false;
	}
    
	// Get the number of efective steps in the algorithm (parentheses are developed in the count)
	uint Algorithm::GetNumSteps() const
	{
		uint count = 0u, size = GetSize();
		int iStep;

		for (uint i = 0; i < size; i++)
		{
			iStep = static_cast<int>(Movs[i]);
			if (m_range[iStep] != Ranges::NONE && m_range[iStep] != Ranges::PARENTHESES) count++;
			else if (Movs[i] == Steps::PARENTHESIS_OPEN)
			{
				int nesting = 1;
				Algorithm AlgPar; // Subalgorithm between parentheses
				while (nesting > 0)
				{
					if (++i == size) return 0u; // No count as parentheses are not ok
					iStep = static_cast<int>(Movs[i]);

					if (Movs[i] == Steps::PARENTHESIS_OPEN) nesting++;
					else if (m_range[iStep] == Ranges::PARENTHESES) nesting--;

					if (nesting == 0)
						count += GetCloseParenthesisRepetitions(Movs[i]) * AlgPar.GetNumSteps(); // Recursive				
					else AlgPar.Append(Movs[i]);
				}
			}
		}

		return count;
	}

	// Check if algorithm parentheses are OK (final nesting == 0 and nesting always >= 0)
	bool Algorithm::CheckParentheses() const
	{
		int nesting = 0;

		for (auto S : Movs)
		{
			if (S == Steps::PARENTHESIS_OPEN) nesting++;
			else if (S > Steps::PARENTHESIS_OPEN) nesting--; // Close parenthesis

			if (nesting < 0) return false; // Nesting must be always greater or equal than zero
		}

		return nesting == 0;
	}
	
	// Check if algorithm parentheses are OK (final nesting == 0 and nesting always >= 0) and returns by reference if there are parentheses
	bool Algorithm::CheckParentheses(bool& HasParentheses) const
	{ 
		int nesting = 0;
		HasParentheses = false;
		
		for (auto S : Movs)
		{
			if (S == Steps::PARENTHESIS_OPEN) { HasParentheses = true; nesting++; }
			else if (S > Steps::PARENTHESIS_OPEN) { HasParentheses = true; nesting--; }
			
			if (nesting < 0) return false; // Nesting must be always greater or equal than zero
		}
		
		return nesting == 0;
	}
	
	// Check the parentheses in a string (final nesting == 0 and nesting always >= 0)
	bool Algorithm::CheckParentheses(const string& s)
	{
		int nesting = 0;
		
		for (auto c : s)
		{
			if (c == '(') nesting++;
			else if (c == ')') nesting--;

			if (nesting < 0) return false;
		}
		
		return nesting == 0;
	}
	
	// Gets parentheses nesting (0 -> parentheses OK, >0 -> more open than close, <0 -> more close than open)
	int Algorithm::GetParenthesesNesting() const
	{ 
		int nesting = 0;
		
		for (auto S : Movs)
		{
			if (S == Steps::PARENTHESIS_OPEN) nesting++;
			else if (S > Steps::PARENTHESIS_OPEN) nesting--;
		}
		
		return nesting;
	}
	
	// Join two steps, return true if the join has been done
	bool Algorithm::JoinSteps(const Steps S1, const Steps S2, Steps& SJ)
	{ 
		int iS1 = static_cast<int>(S1), iS2 = static_cast<int>(S2);

		if (S1 < Steps::PARENTHESIS_OPEN && S2 < Steps::PARENTHESIS_OPEN && // Steps are not parentheses
			m_layer[iS1] == m_layer[iS2] && // Steps are in the same layer
			m_range[iS1] == m_range[iS2]) // Steps are in the same range
		{
			int S1_n = (iS1 - 1) % 3; // Examples -> U: S1_n = 0 / U': S1_n = 1 / U2: S1_n = 2
			int S2_n = (iS2 - 1) % 3;
	
			if      ((S1_n == 1 && S2_n == 2) || (S1_n == 2 && S2_n == 1)) SJ = static_cast<Steps>(iS1 - S1_n);
			else if ((S1_n == 0 && S2_n == 2) || (S1_n == 2 && S2_n == 0)) SJ = static_cast<Steps>(iS1 - S1_n + 1);
			else if ((S1_n == 0 && S2_n == 0) || (S1_n == 1 && S2_n == 1)) SJ = static_cast<Steps>(iS1 - S1_n + 2);
			else SJ = Steps::NONE; // ((S1_n == 0 && S2_n == 1) || (S1_n == 1 && S2_n == 0) || (S1_n == 2 && S2_n == 2))
			return true;
		}
		return false;
	}
	
	// Join two steps with a middle step, return true if the join has been done
	bool Algorithm::JoinSteps(const Steps S1, const Steps SM, const Steps S2, Steps& SJ)
	{ 
		int iS1 = static_cast<int>(S1), iSM = static_cast<int>(SM), iS2 = static_cast<int>(S2);

		if (S1 < Steps::PARENTHESIS_OPEN && SM < Steps::PARENTHESIS_OPEN && S2 < Steps::PARENTHESIS_OPEN && // Steps are not parentheses
			m_range[iS1] == Ranges::SINGLE &&  m_range[iS2] == Ranges::SINGLE && // Steps are in the single external layer range
			(m_range[iSM] == Ranges::SINGLE || m_range[iSM] == Ranges::DOUBLE) && // Middle step is in the single or double external layer range
			m_layer[iS1] == m_layer_opposite[iSM] && // Middle step has the opposite layer
			m_layer[iS1] == m_layer[iS2]) // Steps are in the same layer
		{
			int S1_n = (iS1 - 1) % 3; // Examples -> U: S1_n = 0 / F': S1_n = 1 / R2: S1_n = 2
			int S2_n = (iS2 - 1) % 3;
	
			if      ((S1_n == 1 && S2_n == 2) || (S1_n == 2 && S2_n == 1)) SJ = static_cast<Steps>(iS1 - S1_n);
			else if ((S1_n == 0 && S2_n == 2) || (S1_n == 2 && S2_n == 0)) SJ = static_cast<Steps>(iS1 - S1_n + 1);
			else if ((S1_n == 0 && S2_n == 0) || (S1_n == 1 && S2_n == 1)) SJ = static_cast<Steps>(iS1 - S1_n + 2);
			else SJ = Steps::NONE; // ((S1_n == 0 && S2_n == 1) || (S1_n == 1 && S2_n == 0) || (S1_n == 2 && S2_n == 2))
			return true;
		}
		return false;
	}
	
	// Returns false if the algorithm is shrinked - if returns true apply shrink again
	bool Algorithm::Shrink()
	{ 
		bool changes = false;

		for (uint i = 0u; i < GetSize(); i++) if (Movs[i] == Steps::NONE) Erase(i--); // Remove empty steps

		if (GetSize() <= 1u) return false; // No more shrink needed

		Steps JoinedStep;
		uint index = 1u, index_prev = 0u, index_med;

		do // Shrink adjacent steps
		{
			if (JoinSteps(Movs[index_prev], Movs[index], JoinedStep))
			{ // Steps have been joined
				if (JoinedStep != Steps::NONE) Insert(index + 1u, JoinedStep); // Add joined step
	
				// Delete steps that have been joined
				Erase(index);
				Erase(index_prev);
				changes = true;
			}
			else
			{ // Steps have not been joined, try the next pair
				index++;
				index_prev++;
			}
		}
		while (index < GetSize());
	
		if (GetSize() <= 2u) return changes;
	
		index = 2u, index_prev = 0u, index_med = 1u;
	
		do // Shrink alternate steps
		{
			if (JoinSteps(Movs[index_prev], Movs[index_med], Movs[index], JoinedStep))
			{   // Steps have been joined
				if (JoinedStep != Steps::NONE) Insert(index + 1u, JoinedStep); // Add joined step
	
				// Delete steps that have been joined
				Erase(index);
				Erase(index_prev);
				changes = true;
			}
			else
			{ // Steps have not been joined, try the next trio
				index++;
				index_med++;
				index_prev++;
			}
		}
		while (index < GetSize());
	
		return changes;
	}

	// Shrink last step only - returns true if shrink has been done
	bool Algorithm::ShrinkLast()
	{
		if (GetSize() > 1u)
		{
			Steps JoinedStep;
			uint index, index_prev, index_med;

			index = GetSize() - 1u;
			index_prev = index - 1u;

			if (JoinSteps(Movs[index_prev], Movs[index], JoinedStep)) // Adjacent steps
			{ // Steps have been joined
				if (JoinedStep != Steps::NONE) Insert(index + 1u, JoinedStep); // Add joined step

				// Delete steps that have been joined
				Erase(index);
				Erase(index_prev);
				return true;
			}
			else if (GetSize() > 2u) // Non adjacent steps
			{
				index_med = index_prev--;

				if (JoinSteps(Movs[index_prev], Movs[index_med], Movs[index], JoinedStep))
				{ // Steps have been joined
					if (JoinedStep != Steps::NONE) Insert(index + 1u, JoinedStep); // Add joined step

					// Delete steps that have been joined
					Erase(index);
					Erase(index_prev);
					return true;
				}
			}
		}
		return false;
	}
	
	// Returns a clean algorithm string (removes not allowed chars, changes "2'" and "'2" for "2", 'Uw' notation to 'u' notation )
	string Algorithm::CleanString(const string& s)
	{ 
		string clean_s;
		for (uint i = 0; i < s.length(); i++)
		{
			for (uint j = 0u; j < m_chars_SIZE; j++)
			{
				if (s[i] == m_chars[j])
				{ // Allowed char detected
					if (s[i] == 'X') clean_s.push_back('x'); // Turns in lower case
					else if (s[i] == 'Y') clean_s.push_back('y');
					else if (s[i] == 'Z') clean_s.push_back('z');
					else clean_s.push_back(m_chars[j]);
					break;
				}
			}
		}
		
		// "2'" & "'2" is the same than "2"
		size_t c_pos;
		while ((c_pos = clean_s.find("2'")) != string::npos)
			clean_s.erase(c_pos + 1, 1); // Erase '\'' char
		while ((c_pos = clean_s.find("'2")) != string::npos)
			clean_s.erase(c_pos, 1); // Erase '\'' char
			
		// Replace 'Uw' notation to 'u' notation for double layer movements
		while ((c_pos = clean_s.find("w")) != string::npos)
		{
			if (c_pos == 0) clean_s.erase(c_pos, 1); // First char is 'w', erase
			else
			{
				switch (clean_s[c_pos - 1])
				{
					case 'U': clean_s[c_pos - 1] = 'u'; clean_s.erase(c_pos, 1); break;
					case 'D': clean_s[c_pos - 1] = 'd'; clean_s.erase(c_pos, 1); break;
					case 'F': clean_s[c_pos - 1] = 'f'; clean_s.erase(c_pos, 1); break;
					case 'B': clean_s[c_pos - 1] = 'b'; clean_s.erase(c_pos, 1); break;
					case 'R': clean_s[c_pos - 1] = 'r'; clean_s.erase(c_pos, 1); break;
					case 'L': clean_s[c_pos - 1] = 'l'; clean_s.erase(c_pos, 1); break;
					default: clean_s.erase(c_pos, 1); break;
				}
			}
		}
		
		return clean_s;
	}
	
	// Append given algorithm at the end of the algorithm (no shrinking)
	void Algorithm::Append(Algorithm& A) { uint size = A.GetSize(); for (uint n = 0u; n < size; n++) Append(A[n]); }
	
	 // Reads steps from plain text and append them to the algorithm
	bool Algorithm::Append(string& ss)
	{
		string s = CleanString(ss);
		if (s.length() == 0 || !CheckParentheses(s)) return false;
	
		Steps stp;
		uint pos = 0u, next_pos;
		while ((stp = GetStepFromString(s, pos, next_pos)) != Steps::NONE)
		{
			Append(stp);
			pos = next_pos;
		}
	
		return true;
	}
	
	// Append random movements (between initial step and end step) until get the given size (with shrink)
    void Algorithm::Append(const uint size, const Steps iStep, const Steps eStep)
	{
        if (iStep > eStep) return; // Not valid range of steps

        static std::random_device random_hardware; // Random numbers from hardware
        static std::mt19937 eng(random_hardware()); // Seed the random generator
		uniform_int_distribution<> distr(static_cast<int>(iStep), static_cast<int>(eStep)); // Define the range for allowed movements
	
		while (GetSize() < size) AppendShrink(static_cast<Steps>(distr(eng)));
	}
	
	// Insert given step in given position
	bool Algorithm::Insert(const uint pos, const Steps s)
	{
		uint size = GetSize();
		if (pos < size) Movs.insert(Movs.begin() + pos, s);
		else if (pos == size) Append(s);
		else return false;

		return true;
	}

	// Surround the given range in parentheses with the given repetitions
	bool Algorithm::InsertParentheses(const uint pos, const uint len, const uint rep)
	{
		Algorithm Aux = GetSubAlgorithm(pos, len);
		Steps s_Aux = GetCloseParenthesis(rep);

		if (Aux.GetSize() > 0u && Aux.CheckParentheses() && s_Aux != Steps::NONE)
		{
			Insert(pos + len, s_Aux);
			Insert(pos, Steps::PARENTHESIS_OPEN);
			return true;
		}

		return false;
	}

	// Get the step in the 'pos' positions inside the string 's'
	// 'next_pos' is the index of the following char after the current step
	// String should be a previous cleaned string and with parentheses checked
	Steps Algorithm::GetStepFromString(const string& s, uint pos, uint& next_pos)
	{
		uint s_size = static_cast<uint>(s.length());

		if (s_size == 0u) { next_pos = 0u; return Steps::NONE; }
	
		uint pos_1, pos_2;
		
		while(pos < s_size)
		{
			pos_1 = pos + 1u; // Position increased in 1
			pos_2 = pos + 2u; // Position increased in 2
			
			switch (s[pos])
			{
				case 'U':
					if (pos_1 < s_size)
					{
						if (s[pos_1] == '\'') { next_pos = pos_2; return Steps::Up; }
						if (s[pos_1] == '2')  { next_pos = pos_2; return Steps::U2; }
					}
					next_pos = pos_1; return Steps::U;
				case 'D':
					if (pos_1 < s_size)
					{
						if (s[pos_1] == '\'') { next_pos = pos_2; return Steps::Dp; }
						if (s[pos_1] == '2')  { next_pos = pos_2; return Steps::D2; }
					}
					next_pos = pos_1; return Steps::D;
				case 'F':
					if (pos_1 < s_size)
					{
						if (s[pos_1] == '\'') { next_pos = pos_2; return Steps::Fp; }
						if (s[pos_1] == '2')  { next_pos = pos_2; return Steps::F2; }
					}
					next_pos = pos_1; return Steps::F;
				case 'B':
					if (pos_1 < s_size)
					{
						if (s[pos_1] == '\'') { next_pos = pos_2; return Steps::Bp; }
						if (s[pos_1] == '2')  { next_pos = pos_2; return Steps::B2; }
					}
					next_pos = pos_1; return Steps::B;
				case 'R':
				if (pos_1 < s_size)
					{
						if (s[pos_1] == '\'') { next_pos = pos_2; return Steps::Rp; }
						if (s[pos_1] == '2')  { next_pos = pos_2; return Steps::R2; }
					}
					next_pos = pos_1; return Steps::R;
				case 'L':
					if (pos_1 < s_size)
					{
						if (s[pos_1] == '\'') { next_pos = pos_2; return Steps::Lp; }
						if (s[pos_1] == '2')  { next_pos = pos_2; return Steps::L2; }
					}
					next_pos = pos_1; return Steps::L;
				case 'u':
					if (pos_1 < s_size)
					{
						if (s[pos_1] == '\'') { next_pos = pos_2; return Steps::up; }
						if (s[pos_1] == '2')  { next_pos = pos_2; return Steps::u2; }
					}
					next_pos = pos_1; return Steps::u;
				case 'd':
					if (pos_1 < s_size)
					{
						if (s[pos_1] == '\'') { next_pos = pos_2; return Steps::dp; }
						if (s[pos_1] == '2')  { next_pos = pos_2; return Steps::d2; }
					}
					next_pos = pos_1; return Steps::d;
				case 'f':
					if (pos_1 < s_size)
					{
						if (s[pos_1] == '\'') { next_pos = pos_2; return Steps::fp; }
						if (s[pos_1] == '2')  { next_pos = pos_2; return Steps::f2; }
					}
					next_pos = pos_1; return Steps::f;
				case 'b':
					if (pos_1 < s_size)
					{
						if (s[pos_1] == '\'') { next_pos = pos_2; return Steps::bp; }
						if (s[pos_1] == '2')  { next_pos = pos_2; return Steps::b2; }
					}
					next_pos = pos_1; return Steps::b;
				case 'r':
					if (pos_1 < s_size)
					{
						if (s[pos_1] == '\'') { next_pos = pos_2; return Steps::rp; }
						if (s[pos_1] == '2')  { next_pos = pos_2; return Steps::r2; }
					}
					next_pos = pos_1; return Steps::r;
				case 'l':
					if (pos_1 < s_size)
					{
						if (s[pos_1] == '\'') { next_pos = pos_2; return Steps::lp; }
						if (s[pos_1] == '2')  { next_pos = pos_2; return Steps::l2; }
					}
					next_pos = pos_1; return Steps::l;
				case 'E':
					if (pos_1 < s_size)
					{
						if (s[pos_1] == '\'') { next_pos = pos_2; return Steps::Ep; }
						if (s[pos_1] == '2')  { next_pos = pos_2; return Steps::E2; }
					}
					next_pos = pos_1; return Steps::E;
				case 'S':
					if (pos_1 < s_size)
					{
						if (s[pos_1] == '\'') { next_pos = pos_2; return Steps::Sp; }
						if (s[pos_1] == '2')  { next_pos = pos_2; return Steps::S2; }
					}
					next_pos = pos_1; return Steps::S;
				case 'M':
					if (pos_1 < s_size)
					{
						if (s[pos_1] == '\'') { next_pos = pos_2; return Steps::Mp; }
						if (s[pos_1] == '2')  { next_pos = pos_2; return Steps::M2; }
					}
					next_pos = pos_1; return Steps::M;
				case 'x':
					if (pos_1 < s_size)
					{
						if (s[pos_1] == '\'') { next_pos = pos_2; return Steps::xp; }
						if (s[pos_1] == '2')  { next_pos = pos_2; return Steps::x2; }
					}
					next_pos = pos_1; return Steps::x;
				case 'y':
					if (pos_1 < s_size)
					{
						if (s[pos_1] == '\'') { next_pos = pos_2; return Steps::yp; }
						if (s[pos_1] == '2')  { next_pos = pos_2; return Steps::y2; }
					}
					next_pos = pos_1; return Steps::y;
				case 'z':
					if (pos_1 < s_size)
					{
						if (s[pos_1] == '\'') { next_pos = pos_2; return Steps::zp; }
						if (s[pos_1] == '2')  { next_pos = pos_2; return Steps::z2; }
					}
					next_pos = pos_1; return Steps::z;
				case '(': next_pos = pos_1; return Steps::PARENTHESIS_OPEN;
				case ')':
					if (pos_1 < s_size)
					{
						if (s[pos_1] == '2') { next_pos = pos_2; return Steps::PARENTHESIS_CLOSE_2_REP; }
						if (s[pos_1] == '3') { next_pos = pos_2; return Steps::PARENTHESIS_CLOSE_3_REP; }
						if (s[pos_1] == '4') { next_pos = pos_2; return Steps::PARENTHESIS_CLOSE_4_REP; }
						if (s[pos_1] == '5') { next_pos = pos_2; return Steps::PARENTHESIS_CLOSE_5_REP; }
						if (s[pos_1] == '6') { next_pos = pos_2; return Steps::PARENTHESIS_CLOSE_6_REP; }
						if (s[pos_1] == '7') { next_pos = pos_2; return Steps::PARENTHESIS_CLOSE_7_REP; }
						if (s[pos_1] == '8') { next_pos = pos_2; return Steps::PARENTHESIS_CLOSE_8_REP; }
						if (s[pos_1] == '9') { next_pos = pos_2; return Steps::PARENTHESIS_CLOSE_9_REP; }
					}
					next_pos = pos_1; return Steps::PARENTHESIS_CLOSE_1_REP;
				default: pos++; break;
			}
		}
		next_pos = pos;
		return Steps::NONE;
	}
	
	// Return current algorithm as plain text string
	string Algorithm::ToString(const char sep) const
	{
		string s;

		for (auto step : Movs)
		{
			if (!s.empty() && s.back() == sep && m_range[static_cast<int>(step)] == Ranges::PARENTHESES && step != Steps::PARENTHESIS_OPEN) s.pop_back();
			s += m_strings[static_cast<int>(step)];
			if (step != Steps::PARENTHESIS_OPEN) s.push_back(sep);
		}

		if (!s.empty() && s.back() == sep) s.pop_back();
		
		return s;
	}
	
	// Get the same algorithm with single (default) or without parentheses (steps inside parentheses developed)
	Algorithm Algorithm::GetDeveloped(const bool KeepSingleParentheses) const
	{
		Algorithm DA; // Developed algorithm
		
		if (!CheckParentheses()) return DA; // Return empty algorithm
	
		uint size = GetSize();
		for (uint i = 0u; i < size; i++)
		{
			int iStep = static_cast<int>(Movs[i]);
			if (m_range[iStep] != Ranges::NONE && m_range[iStep] != Ranges::PARENTHESES) DA.Append(Movs[i]);
			else if (Movs[i] == Steps::PARENTHESIS_OPEN)
			{
				int nesting = 1;
				Algorithm aux;
				while (nesting > 0 && i < size)
				{
					if (++i < size)
					{
						if (Movs[i] == Steps::PARENTHESIS_OPEN) nesting++;
						else if (m_range[static_cast<int>(Movs[i])] == Ranges::PARENTHESES) nesting--;

						if (nesting == 0)
						{
							uint rep = GetCloseParenthesisRepetitions(Movs[i]);
							for (uint n = 0u; n < rep; n++)
							{
								if (KeepSingleParentheses) DA.Append(Steps::PARENTHESIS_OPEN);
								Algorithm AuxA = aux.GetDeveloped(KeepSingleParentheses);
								DA.Append(AuxA);
								if (KeepSingleParentheses) DA.Append(Steps::PARENTHESIS_CLOSE_1_REP);
							}
						}
						else aux.Append(Movs[i]);
					}
				}
			}
		}

		return DA;
	}
	 
	// Gets a sub-algorithm from an algorithm position with given length
	Algorithm Algorithm::GetSubAlgorithm(const uint pos, const uint len) const
	{
	 	Algorithm SA; // Sub-algorithm

	 	if ((pos + len) <= GetSize()) for (uint n = pos; n < pos + len; n++) SA.Append(Movs[n]);
		
		return SA;
	}
	
	 // Gets the same algorithm with single layer movements and turns and no parentheses
	 // Should be used before applying the algorithm to a cube (simplify doesn't shrinks!)
	Algorithm Algorithm::GetSimplified() const
	{
		Algorithm SA; // Simplified algorithm
		int iStep;
		
		if (!CheckParentheses()) return SA; // Return empty algorithm

		uint size = GetSize();

		for (uint i = 0u; i < size; i++)
		{
			iStep = static_cast<int>(Movs[i]);

			if (m_range[iStep] != Ranges::PARENTHESES)
			{
				if (m_sequence[iStep][0] != Steps::NONE) SA.Append(m_sequence[iStep][0]);
				if (m_sequence[iStep][1] != Steps::NONE) SA.Append(m_sequence[iStep][1]);
				if (m_sequence[iStep][2] != Steps::NONE) SA.Append(m_sequence[iStep][2]);
			}

			if (Movs[i] == Steps::PARENTHESIS_OPEN)
			{
				int nesting = 1;
				Algorithm aux;
				while (nesting > 0 && ++i < size)
				{
					iStep = static_cast<int>(Movs[i]);

					if (Movs[i] == Steps::PARENTHESIS_OPEN) nesting++;
					else if (m_range[iStep] == Ranges::PARENTHESES) nesting--;

					if (nesting == 0)
						for (int n = 0; n < iStep - static_cast<int>(Steps::PARENTHESIS_OPEN); n++)
						{
							Algorithm aux_s = aux.GetSimplified();
							SA.Append(aux_s);
						}
					else aux.Append(Movs[i]);
				}
			}
		}
	
		return SA;
	}

	// Transform the algorithm applying the given turn
	void Algorithm::TransformTurn(const Steps T)
	{
		switch (T)
		{
		case Steps::x: Transform_x(); break;
		case Steps::xp: Transform_xp(); break;
		case Steps::x2: Transform_x2(); break;
		case Steps::y: Transform_y(); break;
		case Steps::yp: Transform_yp(); break;
		case Steps::y2: Transform_y2(); break;
		case Steps::z: Transform_z(); break;
		case Steps::zp: Transform_zp(); break;
		case Steps::z2: Transform_z2(); break;
		default: break;
		}
	}

	// Transform the algorithm applying an x turn to the specified range of steps
	bool Algorithm::Transform_x(const uint pos, const uint len)
	{
		Algorithm Aux = GetSubAlgorithm(pos, len);

		if (Aux.GetSize() > 0u && Aux.CheckParentheses())
		{
			for (uint n = pos; n < pos + len; n++) Movs[n] = m_x[static_cast<int>(Movs[n])];
			Insert(pos + len, Steps::xp);
			Insert(pos, Steps::x);

			return true;
		}

		return false;
	}

	// Transform the algorithm applying an x' turn to the specified range of steps
	bool Algorithm::Transform_xp(const uint pos, const uint len)
	{
		Algorithm Aux = GetSubAlgorithm(pos, len);

		if (Aux.GetSize() > 0u && Aux.CheckParentheses())
		{
			for (uint n = pos; n < pos + len; n++) Movs[n] = m_xp[static_cast<int>(Movs[n])];
			Insert(pos + len, Steps::x);
			Insert(pos, Steps::xp);

			return true;
		}

		return false;
	}

	// Transform the algorithm applying an x2 turn to the specified range of steps
	bool Algorithm::Transform_x2(const uint pos, const uint len)
	{
		Algorithm Aux = GetSubAlgorithm(pos, len);

		if (Aux.GetSize() > 0u && Aux.CheckParentheses())
		{
			for (uint n = pos; n < pos + len; n++) Movs[n] = m_x2[static_cast<int>(Movs[n])];
			Insert(pos + len, Steps::x2);
			Insert(pos, Steps::x2);

			return true;
		}

		return false;
	}

	// Transform the algorithm applying an y turn to the specified range of steps
	bool Algorithm::Transform_y(const uint pos, const uint len)
	{
		Algorithm Aux = GetSubAlgorithm(pos, len);

		if (Aux.GetSize() > 0u && Aux.CheckParentheses())
		{
			for (uint n = pos; n < pos + len; n++) Movs[n] = m_y[static_cast<int>(Movs[n])];
			Insert(pos + len, Steps::yp);
			Insert(pos, Steps::y);

			return true;
		}

		return false;
	}

	// Transform the algorithm applying an y' turn to the specified range of steps
	bool Algorithm::Transform_yp(const uint pos, const uint len)
	{
		Algorithm Aux = GetSubAlgorithm(pos, len);

		if (Aux.GetSize() > 0u && Aux.CheckParentheses())
		{
			for (uint n = pos; n < pos + len; n++) Movs[n] = m_yp[static_cast<int>(Movs[n])];
			Insert(pos + len, Steps::y);
			Insert(pos, Steps::yp);

			return true;
		}

		return false;
	}

	// Transform the algorithm applying an y2 turn to the specified range of steps
	bool Algorithm::Transform_y2(const uint pos, const uint len)
	{
		Algorithm Aux = GetSubAlgorithm(pos, len);

		if (Aux.GetSize() > 0u && Aux.CheckParentheses())
		{
			for (uint n = pos; n < pos + len; n++) Movs[n] = m_y2[static_cast<int>(Movs[n])];
			Insert(pos + len, Steps::y2);
			Insert(pos, Steps::y2);

			return true;
		}

		return false;
	}

	// Transform the algorithm applying a z turn to the specified range of steps
	bool Algorithm::Transform_z(const uint pos, const uint len)
	{
		Algorithm Aux = GetSubAlgorithm(pos, len);

		if (Aux.GetSize() > 0u && Aux.CheckParentheses())
		{
			for (uint n = pos; n < pos + len; n++) Movs[n] = m_z[static_cast<int>(Movs[n])];
			Insert(pos + len, Steps::zp);
			Insert(pos, Steps::z);

			return true;
		}

		return false;
	}

	// Transform the algorithm applying a z' turn to the specified range of steps
	bool Algorithm::Transform_zp(const uint pos, const uint len)
	{
		Algorithm Aux = GetSubAlgorithm(pos, len);

		if (Aux.GetSize() > 0u && Aux.CheckParentheses())
		{
			for (uint n = pos; n < pos + len; n++) Movs[n] = m_zp[static_cast<int>(Movs[n])];
			Insert(pos + len, Steps::z);
			Insert(pos, Steps::zp);

			return true;
		}

		return false;
	}

	// Transform the algorithm applying a z2 turn to the specified range of steps
	bool Algorithm::Transform_z2(const uint pos, const uint len)
	{
		Algorithm Aux = GetSubAlgorithm(pos, len);

		if (Aux.GetSize() > 0u && Aux.CheckParentheses())
		{
			for (uint n = pos; n < pos + len; n++) Movs[n] = m_z2[static_cast<int>(Movs[n])];
			Insert(pos + len, Steps::z2);
			Insert(pos, Steps::z2);

			return true;
		}

		return false;
	}

	// Transform the algorithm applying the given turn to the specified range of steps
	bool Algorithm::TransformTurn(const Steps T, const uint pos, const uint len)
	{
		switch (T)
		{
		case Steps::x: return Transform_x(pos, len);
		case Steps::xp: return Transform_xp(pos, len);
		case Steps::x2: return Transform_x2(pos, len);
		case Steps::y: return Transform_y(pos, len);
		case Steps::yp: return Transform_yp(pos, len);
		case Steps::y2: return Transform_y2(pos, len);
		case Steps::z: return Transform_z(pos, len);
		case Steps::zp: return Transform_zp(pos, len);
		case Steps::z2: return Transform_z2(pos, len);
		default: return false;
		}
	}
	
	// Changes the steps order
	bool Algorithm::TransformReverse()
	{
		if (!CheckParentheses()) return false;
		
		const uint size = GetSize();
		
		if (size <= 1u) return true;
		
		Steps AuxStep;

        for (uint n = 0u; n < size / 2u; n++)
        {
            AuxStep = Movs[n];
			Movs[n] = Movs[size - 1u - n];
			Movs[size - 1u - n] = AuxStep;
    	}
    	
		// Check if there are parentheses and move them to the right position in the algorithm
		int nest;
		uint j;

		std::vector<bool> ParenthesesControl;

		for (uint i = 0u; i < size; i++) ParenthesesControl.push_back(false); // all false by default

		for (uint i = 0u; i < size - 1u; i++)
		{
			if (m_range[static_cast<int>(Movs[i])] == Ranges::PARENTHESES && Movs[i] != Steps::PARENTHESIS_OPEN && !ParenthesesControl[i])
			{
				nest = 1;
				for (j = i + 1u; j < size; j++)
				{
					if (m_range[static_cast<int>(Movs[j])] == Ranges::PARENTHESES && Movs[j] != Steps::PARENTHESIS_OPEN) nest++;
					else if (Movs[j] == Steps::PARENTHESIS_OPEN) if (--nest == 0) break;
				}
				AuxStep = Movs[i];
				Movs[i] = Movs[j];
				Movs[j] = AuxStep;
				ParenthesesControl[i] = true;
				ParenthesesControl[j] = true;
			}
		}

		return true;
	}

	// Changes every movement for the invert one
	void Algorithm::TransformInvert()
	{
		for (auto &S : Movs) S = m_inverted[static_cast<int>(S)];
	}

	// Changes the steps order and every movement for the invert one
	bool Algorithm::TransformReverseInvert()
	{
		TransformInvert();
		return TransformReverse();
	}
	
	// Changes every movement for the symmetrical one
	void Algorithm::TransformSymmetrical()
	{
		for (auto& S : Movs) S = m_symmetrical[static_cast<int>(S)];
	}

	// Change M to M' and M' to M
	void Algorithm::TransformInvertMSteps()
	{
		for (auto& S : Movs) if (S == Steps::M || S == Steps::Mp) S = m_inverted[static_cast<int>(S)];
	}

	// Change E to E' and E' to E
	void Algorithm::TransformInvertESteps()
	{
		for (auto& S : Movs) if (S == Steps::E || S == Steps::Ep) S = m_inverted[static_cast<int>(S)];
	}

	// Change S to S' and S' to S
	void Algorithm::TransformInvertSSteps()
	{
		for (auto& S : Movs) if (S == Steps::S || S == Steps::Sp) S = m_inverted[static_cast<int>(S)];
	}

    // Remove x, y and z turns from the algorithm (maintaining the functionality)
    // Algorithm must be simplified.
    Algorithm Algorithm::GetWithoutTurns() const
    {
		Algorithm Aux = GetDeveloped(false);
        uint size = Aux.GetSize();
		
        for (int n = size - 1; n >= 0; n--)
        {
            if (m_range[static_cast<int>(Aux[n])] == Ranges::TURN)
            {
                switch (Aux[n])
                {
                    case Steps::x:
                        for (uint i = n + 1; i < size; i++) Aux[i] = m_xp[static_cast<int>(Aux[i])];
                        break;
                    case Steps::xp:
                        for (uint i = n + 1; i < size; i++) Aux[i] = m_x[static_cast<int>(Aux[i])];
                        break;
                    case Steps::x2:
                        for (uint i = n + 1; i < size; i++) Aux[i] = m_x2[static_cast<int>(Aux[i])];
                        break;

                    case Steps::y:
                        for (uint i = n + 1; i < size; i++) Aux[i] = m_yp[static_cast<int>(Aux[i])];
                        break;
                    case Steps::yp:
                        for (uint i = n + 1; i < size; i++) Aux[i] = m_y[static_cast<int>(Aux[i])];
                        break;
                    case Steps::y2:
                        for (uint i = n + 1; i < size; i++) Aux[i] = m_y2[static_cast<int>(Aux[i])];
                        break;

                    case Steps::z:
                        for (uint i = n + 1; i < size; i++) Aux[i] = m_zp[static_cast<int>(Aux[i])];
                        break;
                    case Steps::zp:
                        for (uint i = n + 1; i < size; i++) Aux[i] = m_z[static_cast<int>(Aux[i])];
                        break;
                    case Steps::z2:
                        for (uint i = n + 1; i < size; i++) Aux[i] = m_z2[static_cast<int>(Aux[i])];
                        break;
						
                    default: break;
                }
                Aux.Erase(n); // Clear turn movement
				size--;
            }
        }
        return Aux;
    }

	// Add given search steps group to a steps list
	bool Algorithm::AddToStepsList(const SearchSteps SS, std::vector<Steps>& SL)
	{
		switch (SS)
		{
		case SearchSteps::SINGLE_ALL:
			SL.push_back(Steps::U); SL.push_back(Steps::Up); SL.push_back(Steps::U2);
			SL.push_back(Steps::D); SL.push_back(Steps::Dp); SL.push_back(Steps::D2);
			SL.push_back(Steps::F); SL.push_back(Steps::Fp); SL.push_back(Steps::F2);
			SL.push_back(Steps::B); SL.push_back(Steps::Bp); SL.push_back(Steps::B2);
			SL.push_back(Steps::R); SL.push_back(Steps::Rp); SL.push_back(Steps::R2);
			SL.push_back(Steps::L); SL.push_back(Steps::Lp); SL.push_back(Steps::L2); return true;

		case SearchSteps::SINGLE_U: SL.push_back(Steps::U); SL.push_back(Steps::Up); SL.push_back(Steps::U2); return true;
		case SearchSteps::SINGLE_D: SL.push_back(Steps::D); SL.push_back(Steps::Dp); SL.push_back(Steps::D2); return true;
		case SearchSteps::SINGLE_F: SL.push_back(Steps::F); SL.push_back(Steps::Fp); SL.push_back(Steps::F2); return true;
		case SearchSteps::SINGLE_B: SL.push_back(Steps::B); SL.push_back(Steps::Bp); SL.push_back(Steps::B2); return true;
		case SearchSteps::SINGLE_R: SL.push_back(Steps::R); SL.push_back(Steps::Rp); SL.push_back(Steps::R2); return true;
		case SearchSteps::SINGLE_L: SL.push_back(Steps::L); SL.push_back(Steps::Lp); SL.push_back(Steps::L2); return true;

		case SearchSteps::SINGLE_U_NONE: SL.push_back(Steps::U); SL.push_back(Steps::Up); SL.push_back(Steps::U2);
			SL.push_back(Steps::NONE); return true;
		case SearchSteps::SINGLE_D_NONE: SL.push_back(Steps::D); SL.push_back(Steps::Dp); SL.push_back(Steps::D2);
			SL.push_back(Steps::NONE); return true;
		case SearchSteps::SINGLE_F_NONE: SL.push_back(Steps::F); SL.push_back(Steps::Fp); SL.push_back(Steps::F2);
			SL.push_back(Steps::NONE); return true;
		case SearchSteps::SINGLE_B_NONE: SL.push_back(Steps::B); SL.push_back(Steps::Bp); SL.push_back(Steps::B2);
			SL.push_back(Steps::NONE); return true;
		case SearchSteps::SINGLE_R_NONE: SL.push_back(Steps::R); SL.push_back(Steps::Rp); SL.push_back(Steps::R2);
			SL.push_back(Steps::NONE); return true;
		case SearchSteps::SINGLE_L_NONE: SL.push_back(Steps::L); SL.push_back(Steps::Lp); SL.push_back(Steps::L2);
			SL.push_back(Steps::NONE); return true;

		case SearchSteps::LATERAL_UD: SL.push_back(Steps::F); SL.push_back(Steps::Fp);
			SL.push_back(Steps::B); SL.push_back(Steps::Bp);
			SL.push_back(Steps::R); SL.push_back(Steps::Rp);
			SL.push_back(Steps::L); SL.push_back(Steps::Lp); return true;
		case SearchSteps::LATERAL_FB: SL.push_back(Steps::U); SL.push_back(Steps::Up);
			SL.push_back(Steps::D); SL.push_back(Steps::Dp);
			SL.push_back(Steps::R); SL.push_back(Steps::Rp);
			SL.push_back(Steps::L); SL.push_back(Steps::Lp); return true;
		case SearchSteps::LATERAL_RL: SL.push_back(Steps::U); SL.push_back(Steps::Up);
			SL.push_back(Steps::D); SL.push_back(Steps::Dp);
			SL.push_back(Steps::F); SL.push_back(Steps::Fp);
			SL.push_back(Steps::B); SL.push_back(Steps::Bp); return true;

			/* TODO: Complete */

		default: return false;
		}
	}
}

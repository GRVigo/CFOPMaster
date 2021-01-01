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

#include "cube.h"

namespace grcube3
{
	const Spins Cube::s_Spins[24][9] = // Array to follow spins when a cube has a turn (24x9 elements array)
	{ //      x          xp         x2         y          yp         y2         z          zp         z2
		{ Spins::FD, Spins::BU, Spins::DB, Spins::UR, Spins::UL, Spins::UB, Spins::LF, Spins::RF, Spins::DF }, // UF
		{ Spins::RD, Spins::LU, Spins::DL, Spins::UB, Spins::UF, Spins::UL, Spins::FR, Spins::BR, Spins::DR }, // UR
		{ Spins::BD, Spins::FU, Spins::DF, Spins::UL, Spins::UR, Spins::UF, Spins::RB, Spins::LB, Spins::DB }, // UB
		{ Spins::LD, Spins::RU, Spins::DR, Spins::UF, Spins::UB, Spins::UR, Spins::BL, Spins::FL, Spins::DL }, // UL
		{ Spins::FU, Spins::BD, Spins::UB, Spins::DL, Spins::DR, Spins::DB, Spins::RF, Spins::LF, Spins::UF }, // DF
		{ Spins::RU, Spins::LD, Spins::UL, Spins::DF, Spins::DB, Spins::DL, Spins::BR, Spins::FR, Spins::UR }, // DR
		{ Spins::BU, Spins::FD, Spins::UF, Spins::DR, Spins::DL, Spins::DF, Spins::LB, Spins::RB, Spins::UB }, // DB
		{ Spins::LU, Spins::RD, Spins::UR, Spins::DB, Spins::DF, Spins::DR, Spins::FL, Spins::BL, Spins::UL }, // DL
		{ Spins::UB, Spins::DF, Spins::BD, Spins::FL, Spins::FR, Spins::FD, Spins::RU, Spins::LU, Spins::BU }, // FU
		{ Spins::RB, Spins::LF, Spins::BL, Spins::FU, Spins::FD, Spins::FL, Spins::DR, Spins::UR, Spins::BR }, // FR
		{ Spins::DB, Spins::UF, Spins::BU, Spins::FR, Spins::FL, Spins::FU, Spins::LD, Spins::RD, Spins::BD }, // FD
		{ Spins::LB, Spins::RF, Spins::BR, Spins::FD, Spins::FU, Spins::FR, Spins::UL, Spins::DL, Spins::BL }, // FL
		{ Spins::UF, Spins::DB, Spins::FD, Spins::BR, Spins::BL, Spins::BD, Spins::LU, Spins::RU, Spins::FU }, // BU
		{ Spins::RF, Spins::LB, Spins::FL, Spins::BD, Spins::BU, Spins::BL, Spins::UR, Spins::DR, Spins::FR }, // BR
		{ Spins::DF, Spins::UB, Spins::FU, Spins::BL, Spins::BR, Spins::BU, Spins::RD, Spins::LD, Spins::FD }, // BD
		{ Spins::LF, Spins::RB, Spins::FR, Spins::BU, Spins::BD, Spins::BR, Spins::DL, Spins::UL, Spins::FL }, // BL
		{ Spins::UL, Spins::DR, Spins::LD, Spins::RF, Spins::RB, Spins::RD, Spins::BU, Spins::FU, Spins::LU }, // RU
		{ Spins::FL, Spins::BR, Spins::LB, Spins::RD, Spins::RU, Spins::RB, Spins::UF, Spins::DF, Spins::LF }, // RF
		{ Spins::DL, Spins::UR, Spins::LU, Spins::RB, Spins::RF, Spins::RU, Spins::FD, Spins::BD, Spins::LD }, // RD
		{ Spins::BL, Spins::FR, Spins::LF, Spins::RU, Spins::RD, Spins::RF, Spins::DB, Spins::UB, Spins::LB }, // RB
		{ Spins::UR, Spins::DL, Spins::RD, Spins::LB, Spins::LF, Spins::LD, Spins::FU, Spins::BU, Spins::RU }, // LU
		{ Spins::FR, Spins::BL, Spins::RB, Spins::LU, Spins::LD, Spins::LB, Spins::DF, Spins::UF, Spins::RF }, // LF
		{ Spins::DR, Spins::UL, Spins::RU, Spins::LF, Spins::LB, Spins::LU, Spins::BD, Spins::FD, Spins::RD }, // LD
		{ Spins::BR, Spins::FL, Spins::RF, Spins::LD, Spins::LU, Spins::LF, Spins::UB, Spins::DB, Spins::RB }  // LB
	};

	// Two turns array for get a final spin from an inital spin [Start spin][Final spin][Turns to pass from start to final spin]
	const Steps Cube::s_Turns[24][24][2] =
	{ //			UF							UR								UB							UL								DF							DR								DB							DL								FU							FR								FD							FL								BU							BR								BD							BL								RU							RF								RD							RB								LU							LF								LD							LB
	{ { Steps::NONE, Steps::NONE }, { Steps::y,    Steps::NONE }, { Steps::y2,   Steps::NONE }, { Steps::yp,   Steps::NONE }, { Steps::z2,   Steps::NONE }, { Steps::y,    Steps::z2 },   { Steps::x2,   Steps::NONE }, { Steps::y,    Steps::x2 },   { Steps::y2,   Steps::xp },   { Steps::y,    Steps::z },    { Steps::x,    Steps::NONE }, { Steps::yp,   Steps::z },    { Steps::xp,   Steps::NONE }, { Steps::y,    Steps::z },    { Steps::y2,   Steps::x },    { Steps::yp,   Steps::z },    { Steps::yp,   Steps::xp },   { Steps::zp,   Steps::NONE }, { Steps::y,    Steps::x },    { Steps::y2,   Steps::z },    { Steps::y,    Steps::xp },   { Steps::z,    Steps::NONE }, { Steps::yp,   Steps::x },    { Steps::y2,   Steps::zp },  }, 	// UF
	{ { Steps::yp,   Steps::NONE }, { Steps::NONE, Steps::NONE }, { Steps::y,    Steps::NONE }, { Steps::y2,   Steps::NONE }, { Steps::yp,   Steps::z2 },   { Steps::z2,   Steps::NONE }, { Steps::yp,   Steps::x2 },   { Steps::x2,   Steps::NONE }, { Steps::y,    Steps::xp },   { Steps::z,    Steps::NONE }, { Steps::yp,   Steps::x },    { Steps::y2,   Steps::z },    { Steps::yp,   Steps::xp },   { Steps::zp,   Steps::NONE }, { Steps::y,    Steps::x },    { Steps::y2,   Steps::z },    { Steps::y2,   Steps::xp },   { Steps::yp,   Steps::z },    { Steps::x,    Steps::NONE }, { Steps::y,    Steps::z },    { Steps::xp,   Steps::NONE }, { Steps::yp,   Steps::z },    { Steps::y2,   Steps::x },    { Steps::y,    Steps::zp },  }, 	// UR
	{ { Steps::y2,   Steps::NONE }, { Steps::yp,   Steps::NONE }, { Steps::NONE, Steps::NONE }, { Steps::y,    Steps::NONE }, { Steps::x2,   Steps::NONE }, { Steps::yp,   Steps::z2 },   { Steps::z2,   Steps::NONE }, { Steps::yp,   Steps::x2 },   { Steps::xp,   Steps::NONE }, { Steps::yp,   Steps::z },    { Steps::y2,   Steps::x },    { Steps::y,    Steps::z },    { Steps::y2,   Steps::xp },   { Steps::yp,   Steps::z },    { Steps::x,    Steps::NONE }, { Steps::y,    Steps::z },    { Steps::y,    Steps::xp },   { Steps::y2,   Steps::z },    { Steps::yp,   Steps::x },    { Steps::z,    Steps::NONE }, { Steps::yp,   Steps::xp },   { Steps::y2,   Steps::z },    { Steps::y,    Steps::x },    { Steps::zp,   Steps::NONE },  }, 	// UB
	{ { Steps::y,    Steps::NONE }, { Steps::y2,   Steps::NONE }, { Steps::yp,   Steps::NONE }, { Steps::NONE, Steps::NONE }, { Steps::y,    Steps::z2 },   { Steps::x2,   Steps::NONE }, { Steps::y,    Steps::x2 },   { Steps::z2,   Steps::NONE }, { Steps::yp,   Steps::xp },   { Steps::y2,   Steps::z },    { Steps::y,    Steps::x },    { Steps::zp,   Steps::NONE }, { Steps::y,    Steps::xp },   { Steps::y2,   Steps::z },    { Steps::yp,   Steps::x },    { Steps::z,    Steps::NONE }, { Steps::xp,   Steps::NONE }, { Steps::y,    Steps::z },    { Steps::y2,   Steps::x },    { Steps::yp,   Steps::z },    { Steps::y2,   Steps::xp },   { Steps::y,    Steps::z },    { Steps::x,    Steps::NONE }, { Steps::yp,   Steps::zp },  }, 	// UL
	{ { Steps::z2,   Steps::NONE }, { Steps::z2,   Steps::y },    { Steps::x2,   Steps::NONE }, { Steps::z2,   Steps::yp },   { Steps::NONE, Steps::NONE }, { Steps::yp,   Steps::NONE }, { Steps::y2,   Steps::NONE }, { Steps::y,    Steps::NONE }, { Steps::x,    Steps::NONE }, { Steps::yp,   Steps::z },    { Steps::z2,   Steps::x },    { Steps::y,    Steps::z },    { Steps::z2,   Steps::xp },   { Steps::yp,   Steps::z },    { Steps::xp,   Steps::NONE }, { Steps::y,    Steps::z },    { Steps::yp,   Steps::x },    { Steps::z,    Steps::NONE }, { Steps::y,    Steps::xp },   { Steps::x2,   Steps::z },    { Steps::y,    Steps::x },    { Steps::zp,   Steps::NONE }, { Steps::yp,   Steps::xp },   { Steps::x2,   Steps::zp },  }, 	// DF
	{ { Steps::z2,   Steps::yp },   { Steps::z2,   Steps::NONE }, { Steps::z2,   Steps::y },    { Steps::x2,   Steps::NONE }, { Steps::y,    Steps::NONE }, { Steps::NONE, Steps::NONE }, { Steps::yp,   Steps::NONE }, { Steps::y2,   Steps::NONE }, { Steps::y,    Steps::x },    { Steps::zp,   Steps::NONE }, { Steps::yp,   Steps::xp },   { Steps::x2,   Steps::z },    { Steps::yp,   Steps::x },    { Steps::z,    Steps::NONE }, { Steps::y,    Steps::xp },   { Steps::x2,   Steps::z },    { Steps::x,    Steps::NONE }, { Steps::y,    Steps::z },    { Steps::z2,   Steps::x },    { Steps::yp,   Steps::z },    { Steps::z2,   Steps::xp },   { Steps::y,    Steps::z },    { Steps::xp,   Steps::NONE }, { Steps::yp,   Steps::z },  }, 		// DR
	{ { Steps::x2,   Steps::NONE }, { Steps::x2,   Steps::y },    { Steps::z2,   Steps::NONE }, { Steps::x2,   Steps::yp },   { Steps::y2,   Steps::NONE }, { Steps::y,    Steps::NONE }, { Steps::NONE, Steps::NONE }, { Steps::yp,   Steps::NONE }, { Steps::z2,   Steps::xp },   { Steps::y,    Steps::z },    { Steps::xp,   Steps::NONE }, { Steps::yp,   Steps::z },    { Steps::x,    Steps::NONE }, { Steps::y,    Steps::z },    { Steps::z2,   Steps::x },    { Steps::yp,   Steps::z },    { Steps::y,    Steps::x },    { Steps::x2,   Steps::z },    { Steps::yp,   Steps::xp },   { Steps::zp,   Steps::NONE }, { Steps::yp,   Steps::x },    { Steps::x2,   Steps::z },    { Steps::y,    Steps::xp },   { Steps::z,    Steps::NONE },  }, 	// DB
	{ { Steps::x2,   Steps::yp },   { Steps::x2,   Steps::NONE }, { Steps::x2,   Steps::y },    { Steps::z2,   Steps::NONE }, { Steps::yp,   Steps::NONE }, { Steps::y2,   Steps::NONE }, { Steps::y,    Steps::NONE }, { Steps::NONE, Steps::NONE }, { Steps::yp,   Steps::x },    { Steps::x2,   Steps::z },    { Steps::y,    Steps::xp },   { Steps::z,    Steps::NONE }, { Steps::y,    Steps::x },    { Steps::x2,   Steps::z },    { Steps::yp,   Steps::xp },   { Steps::zp,   Steps::NONE }, { Steps::z2,   Steps::xp },   { Steps::yp,   Steps::z },    { Steps::xp,   Steps::NONE }, { Steps::y,    Steps::z },    { Steps::x,    Steps::NONE }, { Steps::yp,   Steps::z },    { Steps::z2,   Steps::x },    { Steps::y,    Steps::z },  }, 		// DL
	{ { Steps::x,    Steps::y2 },   { Steps::x,    Steps::yp },   { Steps::x,    Steps::NONE }, { Steps::x,    Steps::y },    { Steps::xp,   Steps::NONE }, { Steps::xp,   Steps::yp },   { Steps::x,    Steps::z2 },   { Steps::xp,   Steps::y },    { Steps::NONE, Steps::NONE }, { Steps::yp,   Steps::NONE }, { Steps::y2,   Steps::NONE }, { Steps::y,    Steps::NONE }, { Steps::z2,   Steps::NONE }, { Steps::yp,   Steps::z2 },   { Steps::x2,   Steps::NONE }, { Steps::yp,   Steps::x2 },   { Steps::z,    Steps::NONE }, { Steps::xp,   Steps::z },    { Steps::y2,   Steps::z },    { Steps::x,    Steps::z },    { Steps::zp,   Steps::NONE }, { Steps::xp,   Steps::z },    { Steps::y2,   Steps::z },    { Steps::x,    Steps::zp },  }, 	// FU
	{ { Steps::zp,   Steps::yp },   { Steps::zp,   Steps::NONE }, { Steps::zp,   Steps::y },    { Steps::zp,   Steps::y2 },   { Steps::z,    Steps::y },    { Steps::z,    Steps::NONE }, { Steps::z,    Steps::yp },   { Steps::zp,   Steps::x2 },   { Steps::y,    Steps::NONE }, { Steps::NONE, Steps::NONE }, { Steps::yp,   Steps::NONE }, { Steps::y2,   Steps::NONE }, { Steps::y,    Steps::z2 },   { Steps::z2,   Steps::NONE }, { Steps::y,    Steps::x2 },   { Steps::x2,   Steps::NONE }, { Steps::z,    Steps::x },    { Steps::y2,   Steps::xp },   { Steps::zp,   Steps::x },    { Steps::x,    Steps::NONE }, { Steps::zp,   Steps::xp },   { Steps::xp,   Steps::NONE }, { Steps::z,    Steps::xp },   { Steps::y2,   Steps::x },  }, 		// FR
	{ { Steps::xp,   Steps::NONE }, { Steps::xp,   Steps::y },    { Steps::xp,   Steps::y2 },   { Steps::xp,   Steps::yp },   { Steps::xp,   Steps::z2 },   { Steps::x,    Steps::y },    { Steps::x,    Steps::NONE }, { Steps::x,    Steps::yp },   { Steps::y2,   Steps::NONE }, { Steps::y,    Steps::NONE }, { Steps::NONE, Steps::NONE }, { Steps::yp,   Steps::NONE }, { Steps::x2,   Steps::NONE }, { Steps::y,    Steps::z2 },   { Steps::z2,   Steps::NONE }, { Steps::y,    Steps::x2 },   { Steps::y2,   Steps::z },    { Steps::xp,   Steps::z },    { Steps::zp,   Steps::NONE }, { Steps::x,    Steps::z },    { Steps::y2,   Steps::z },    { Steps::xp,   Steps::z },    { Steps::z,    Steps::NONE }, { Steps::x,    Steps::z },  }, 		// FD
	{ { Steps::z,    Steps::y },    { Steps::z,    Steps::y2 },   { Steps::z,    Steps::yp },   { Steps::z,    Steps::NONE }, { Steps::zp,   Steps::yp },   { Steps::z,    Steps::x2 },   { Steps::zp,   Steps::y },    { Steps::zp,   Steps::NONE }, { Steps::yp,   Steps::NONE }, { Steps::y2,   Steps::NONE }, { Steps::y,    Steps::NONE }, { Steps::NONE, Steps::NONE }, { Steps::yp,   Steps::z2 },   { Steps::x2,   Steps::NONE }, { Steps::yp,   Steps::x2 },   { Steps::z2,   Steps::NONE }, { Steps::z,    Steps::xp },   { Steps::xp,   Steps::NONE }, { Steps::zp,   Steps::xp },   { Steps::y2,   Steps::x },    { Steps::zp,   Steps::x },    { Steps::y2,   Steps::xp },   { Steps::z,    Steps::x },    { Steps::x,    Steps::NONE },  }, 	// FL
	{ { Steps::x,    Steps::NONE }, { Steps::x,    Steps::y },    { Steps::x,    Steps::y2 },   { Steps::x,    Steps::yp },   { Steps::x,    Steps::z2 },   { Steps::xp,   Steps::y },    { Steps::xp,   Steps::NONE }, { Steps::xp,   Steps::yp },   { Steps::z2,   Steps::NONE }, { Steps::z2,   Steps::yp },   { Steps::x2,   Steps::NONE }, { Steps::z2,   Steps::y },    { Steps::NONE, Steps::NONE }, { Steps::y,    Steps::NONE }, { Steps::y2,   Steps::NONE }, { Steps::yp,   Steps::NONE }, { Steps::zp,   Steps::NONE }, { Steps::x,    Steps::z },    { Steps::x2,   Steps::z },    { Steps::xp,   Steps::z },    { Steps::z,    Steps::NONE }, { Steps::x,    Steps::z },    { Steps::x2,   Steps::z },    { Steps::xp,   Steps::z },  }, 		// BU
	{ { Steps::z,    Steps::yp },   { Steps::z,    Steps::NONE }, { Steps::z,    Steps::y },    { Steps::z,    Steps::y2 },   { Steps::zp,   Steps::y },    { Steps::zp,   Steps::NONE }, { Steps::zp,   Steps::yp },   { Steps::z,    Steps::x2 },   { Steps::z2,   Steps::y },    { Steps::z2,   Steps::NONE }, { Steps::z2,   Steps::yp },   { Steps::x2,   Steps::NONE }, { Steps::yp,   Steps::NONE }, { Steps::NONE, Steps::NONE }, { Steps::y,    Steps::NONE }, { Steps::y2,   Steps::NONE }, { Steps::zp,   Steps::x },    { Steps::x,    Steps::NONE }, { Steps::z,    Steps::x },    { Steps::z2,   Steps::x },    { Steps::z,    Steps::xp },   { Steps::z2,   Steps::xp },   { Steps::zp,   Steps::xp },   { Steps::xp,   Steps::NONE },  }, 	// BR
	{ { Steps::xp,   Steps::y2 },   { Steps::xp,   Steps::yp },   { Steps::xp,   Steps::NONE }, { Steps::xp,   Steps::y },    { Steps::x,    Steps::NONE }, { Steps::x,    Steps::yp },   { Steps::xp,   Steps::z2 },   { Steps::x,    Steps::y },    { Steps::x2,   Steps::NONE }, { Steps::x2,   Steps::yp },   { Steps::z2,   Steps::NONE }, { Steps::x2,   Steps::y },    { Steps::y2,   Steps::NONE }, { Steps::yp,   Steps::NONE }, { Steps::NONE, Steps::NONE }, { Steps::y,    Steps::NONE }, { Steps::x2,   Steps::z },    { Steps::x,    Steps::z },    { Steps::z,    Steps::NONE }, { Steps::xp,   Steps::z },    { Steps::x2,   Steps::z },    { Steps::x,    Steps::z },    { Steps::zp,   Steps::NONE }, { Steps::xp,   Steps::zp },  }, 	// BD
	{ { Steps::zp,   Steps::y },    { Steps::zp,   Steps::y2 },   { Steps::zp,   Steps::yp },   { Steps::zp,   Steps::NONE }, { Steps::z,    Steps::yp },   { Steps::zp,   Steps::x2 },   { Steps::z,    Steps::y },    { Steps::z,    Steps::NONE }, { Steps::x2,   Steps::y },    { Steps::x2,   Steps::NONE }, { Steps::x2,   Steps::yp },   { Steps::z2,   Steps::NONE }, { Steps::y,    Steps::NONE }, { Steps::y2,   Steps::NONE }, { Steps::yp,   Steps::NONE }, { Steps::NONE, Steps::NONE }, { Steps::zp,   Steps::xp },   { Steps::z2,   Steps::xp },   { Steps::z,    Steps::xp },   { Steps::xp,   Steps::NONE }, { Steps::z,    Steps::x },    { Steps::x,    Steps::NONE }, { Steps::zp,   Steps::x },    { Steps::z2,   Steps::x },  }, 		// BL
	{ { Steps::x,    Steps::y },    { Steps::x,    Steps::y2 },   { Steps::x,    Steps::yp },   { Steps::x,    Steps::NONE }, { Steps::xp,   Steps::y },    { Steps::xp,   Steps::NONE }, { Steps::xp,   Steps::yp },   { Steps::x,    Steps::z2 },   { Steps::zp,   Steps::NONE }, { Steps::xp,   Steps::z },    { Steps::zp,   Steps::y2 },   { Steps::x,    Steps::z },    { Steps::z,    Steps::NONE }, { Steps::xp,   Steps::z },    { Steps::zp,   Steps::x2 },   { Steps::x,    Steps::z },    { Steps::NONE, Steps::NONE }, { Steps::y,    Steps::NONE }, { Steps::y2,   Steps::NONE }, { Steps::yp,   Steps::NONE }, { Steps::z2,   Steps::NONE }, { Steps::y,    Steps::z2 },   { Steps::x2,   Steps::NONE }, { Steps::y,    Steps::x2 },  }, 	// RU
	{ { Steps::z,    Steps::NONE }, { Steps::z,    Steps::y },    { Steps::z,    Steps::y2 },   { Steps::z,    Steps::yp },   { Steps::zp,   Steps::NONE }, { Steps::zp,   Steps::yp },   { Steps::z,    Steps::x2 },   { Steps::zp,   Steps::y },    { Steps::zp,   Steps::x },    { Steps::x,    Steps::y2 },   { Steps::z,    Steps::x },    { Steps::x,    Steps::NONE }, { Steps::z,    Steps::xp },   { Steps::xp,   Steps::NONE }, { Steps::zp,   Steps::xp },   { Steps::x,    Steps::z2 },   { Steps::yp,   Steps::NONE }, { Steps::NONE, Steps::NONE }, { Steps::y,    Steps::NONE }, { Steps::y2,   Steps::NONE }, { Steps::yp,   Steps::z2 },   { Steps::z2,   Steps::NONE }, { Steps::yp,   Steps::x2 },   { Steps::x2,   Steps::NONE },  }, 	// RF
	{ { Steps::xp,   Steps::yp },   { Steps::xp,   Steps::NONE }, { Steps::xp,   Steps::y },    { Steps::xp,   Steps::y2 },   { Steps::x,    Steps::yp },   { Steps::xp,   Steps::z2 },   { Steps::x,    Steps::y },    { Steps::x,    Steps::NONE }, { Steps::z,    Steps::y2 },   { Steps::xp,   Steps::z },    { Steps::z,    Steps::NONE }, { Steps::x,    Steps::z },    { Steps::z,    Steps::x2 },   { Steps::xp,   Steps::z },    { Steps::zp,   Steps::NONE }, { Steps::x,    Steps::z },    { Steps::y2,   Steps::NONE }, { Steps::yp,   Steps::NONE }, { Steps::NONE, Steps::NONE }, { Steps::y,    Steps::NONE }, { Steps::x2,   Steps::NONE }, { Steps::yp,   Steps::z2 },   { Steps::z2,   Steps::NONE }, { Steps::yp,   Steps::x2 },  }, 	// RD
	{ { Steps::zp,   Steps::y2 },   { Steps::zp,   Steps::yp },   { Steps::zp,   Steps::NONE }, { Steps::zp,   Steps::y },    { Steps::zp,   Steps::x2 },   { Steps::z,    Steps::y },    { Steps::z,    Steps::NONE }, { Steps::z,    Steps::yp },   { Steps::zp,   Steps::xp },   { Steps::xp,   Steps::NONE }, { Steps::z,    Steps::xp },   { Steps::xp,   Steps::y2 },   { Steps::z,    Steps::x },    { Steps::xp,   Steps::z2 },   { Steps::zp,   Steps::x },    { Steps::x,    Steps::NONE }, { Steps::y,    Steps::NONE }, { Steps::y2,   Steps::NONE }, { Steps::yp,   Steps::NONE }, { Steps::NONE, Steps::NONE }, { Steps::y,    Steps::z2 },   { Steps::x2,   Steps::NONE }, { Steps::y,    Steps::x2 },   { Steps::z2,   Steps::NONE },  }, 	// RB
	{ { Steps::x,    Steps::yp },   { Steps::x,    Steps::NONE }, { Steps::x,    Steps::y },    { Steps::x,    Steps::y2 },   { Steps::xp,   Steps::yp },   { Steps::x,    Steps::z2 },   { Steps::xp,   Steps::y },    { Steps::xp,   Steps::NONE }, { Steps::z,    Steps::NONE }, { Steps::x,    Steps::z },    { Steps::z,    Steps::y2 },   { Steps::xp,   Steps::z },    { Steps::zp,   Steps::NONE }, { Steps::x,    Steps::z },    { Steps::z,    Steps::x2 },   { Steps::xp,   Steps::z },    { Steps::z2,   Steps::NONE }, { Steps::z2,   Steps::y },    { Steps::x2,   Steps::NONE }, { Steps::z2,   Steps::yp },   { Steps::NONE, Steps::NONE }, { Steps::yp,   Steps::NONE }, { Steps::y2,   Steps::NONE }, { Steps::y,    Steps::NONE },  }, 	// LU
	{ { Steps::zp,   Steps::NONE }, { Steps::zp,   Steps::y },    { Steps::zp,   Steps::y2 },   { Steps::zp,   Steps::yp },   { Steps::z,    Steps::NONE }, { Steps::z,    Steps::yp },   { Steps::zp,   Steps::x2 },   { Steps::z,    Steps::y },    { Steps::z,    Steps::x },    { Steps::x,    Steps::NONE }, { Steps::zp,   Steps::x },    { Steps::x,    Steps::y2 },   { Steps::zp,   Steps::xp },   { Steps::x,    Steps::z2 },   { Steps::z,    Steps::xp },   { Steps::xp,   Steps::NONE }, { Steps::z2,   Steps::yp },   { Steps::z2,   Steps::NONE }, { Steps::z2,   Steps::y },    { Steps::x2,   Steps::NONE }, { Steps::y,    Steps::NONE }, { Steps::NONE, Steps::NONE }, { Steps::yp,   Steps::NONE }, { Steps::y2,   Steps::NONE },  }, 	// LF
	{ { Steps::xp,   Steps::y },    { Steps::xp,   Steps::y2 },   { Steps::xp,   Steps::yp },   { Steps::xp,   Steps::NONE }, { Steps::x,    Steps::y },    { Steps::x,    Steps::NONE }, { Steps::x,    Steps::yp },   { Steps::xp,   Steps::z2 },   { Steps::zp,   Steps::y2 },   { Steps::x,    Steps::z },    { Steps::zp,   Steps::NONE }, { Steps::xp,   Steps::z },    { Steps::zp,   Steps::x2 },   { Steps::x,    Steps::z },    { Steps::z,    Steps::NONE }, { Steps::xp,   Steps::z },    { Steps::x2,   Steps::NONE }, { Steps::x2,   Steps::y },    { Steps::z2,   Steps::NONE }, { Steps::x2,   Steps::yp },   { Steps::y2,   Steps::NONE }, { Steps::y,    Steps::NONE }, { Steps::NONE, Steps::NONE }, { Steps::yp,   Steps::NONE },  }, 	// LD
	{ { Steps::z,    Steps::y2 },   { Steps::z,    Steps::yp },   { Steps::z,    Steps::NONE }, { Steps::z,    Steps::y },    { Steps::z,    Steps::x2 },   { Steps::zp,   Steps::y },    { Steps::zp,   Steps::NONE }, { Steps::zp,   Steps::yp },   { Steps::z,    Steps::xp },   { Steps::xp,   Steps::y2 },   { Steps::zp,   Steps::xp },   { Steps::xp,   Steps::NONE }, { Steps::zp,   Steps::x },    { Steps::x,    Steps::NONE }, { Steps::z,    Steps::x },    { Steps::xp,   Steps::z2 },   { Steps::x2,   Steps::yp },   { Steps::x2,   Steps::NONE }, { Steps::x2,   Steps::y },    { Steps::z2,   Steps::NONE }, { Steps::yp,   Steps::NONE }, { Steps::y2,   Steps::NONE }, { Steps::y,    Steps::NONE }, { Steps::NONE, Steps::NONE },  }, 	// LB
	};
	
	const Faces Cube::f_Stickers[54] = // Array to know the solved face of the stickers
	{
		// Centers from 0 to 5
	    Faces::U, Faces::D, Faces::F, Faces::B, Faces::R, Faces::L,  // Centers
	    // Edges from 6 to 29
		Faces::F, Faces::R, Faces::F, Faces::L, Faces::B, Faces::L, Faces::B, Faces::R, // Middle layer
	    Faces::U, Faces::F, Faces::U, Faces::L, Faces::U, Faces::B, Faces::U, Faces::R, // Upper layer
	    Faces::D, Faces::F, Faces::D, Faces::L, Faces::D, Faces::B, Faces::D, Faces::R, // Lower layer
	    // Corners from 30 to 53
	    Faces::U, Faces::F, Faces::R, Faces::U, Faces::F, Faces::L, // Upper layer
		Faces::U, Faces::B, Faces::L, Faces::U, Faces::B, Faces::R, // Upper layer
	    Faces::D, Faces::F, Faces::R, Faces::D, Faces::F, Faces::L, // Lower layer
		Faces::D, Faces::B, Faces::L, Faces::D, Faces::B, Faces::R  // Lower layer
	};

	const PiecesTypes Cube::t_Pieces[26] = // Array to know the pieces type
	{
		PiecesTypes::CENTER, PiecesTypes::CENTER, PiecesTypes::CENTER, PiecesTypes::CENTER, PiecesTypes::CENTER, PiecesTypes::CENTER, 
		PiecesTypes::EDGE, PiecesTypes::EDGE, PiecesTypes::EDGE, PiecesTypes::EDGE, PiecesTypes::EDGE, PiecesTypes::EDGE, 
		PiecesTypes::EDGE, PiecesTypes::EDGE, PiecesTypes::EDGE, PiecesTypes::EDGE, PiecesTypes::EDGE, PiecesTypes::EDGE, 
		PiecesTypes::CORNER, PiecesTypes::CORNER, PiecesTypes::CORNER, PiecesTypes::CORNER,
		PiecesTypes::CORNER, PiecesTypes::CORNER, PiecesTypes::CORNER, PiecesTypes::CORNER
	};

	const Layers Cube::l_OppositeLayers[10] = // Array to know the opposite layer
	{
		Layers::NONE, Layers::D, Layers::U, Layers::B, Layers::F, Layers::L, Layers::R, Layers::E, Layers::S, Layers::M
	};

	const Faces Cube::f_OppositeFaces[6] = // Array to know the opposite face
	{
		Faces::D, Faces::U, Faces::B, Faces::F, Faces::L, Faces::R
	};

	const char Cube::c_Layers[10] = // Array to know the layer char
	{
		'-', 'U', 'D', 'F', 'B', 'R', 'L', 'E', 'S', 'M'
	};

	// Array with spins string representation
	const std::string Cube::sp_strings[] =
	{
		"UF", "UR", "UB", "UL",
		"DF", "DR", "DB", "DL",
		"FU", "FR", "FD", "FL",
		"BU", "BR", "BD", "BL",
		"RU", "RF", "RD", "RB",
		"LU", "LF", "LD", "LB"
	};

	void Cube::U() // Movement U
	{
		switch (spin)
	    {
	        case Spins::UF:
	        case Spins::UR:
	        case Spins::UB:
			case Spins::UL: e_U(); c_U(); break;
	        case Spins::DF:
	        case Spins::DR:
	        case Spins::DB:
	        case Spins::DL: e_D(); c_D(); break;
	        case Spins::FU:
	        case Spins::FR:
	        case Spins::FD:
			case Spins::FL: e_F(); c_F(); break;
	        case Spins::BU:
	        case Spins::BR:
	        case Spins::BD:
			case Spins::BL: e_B(); c_B(); break;
	        case Spins::RU:
	        case Spins::RF:
	        case Spins::RD:
			case Spins::RB: e_R(); c_R(); break;
	        // case Spins::LU:
	        // case Spins::LF:
	        // case Spins::LD:
	        // case Spins::LB:
			default: e_L(); c_L(); break;
	    }
	}
	
	void Cube::U2()  // Movement U2
	{
		switch (spin)
	    {
	        case Spins::UF:
	        case Spins::UR:
	        case Spins::UB:
	        case Spins::UL: e_U2(); c_U2(); break;
	        case Spins::DF:
	        case Spins::DR:
	        case Spins::DB:
	        case Spins::DL: e_D2(); c_D2(); break;
	        case Spins::FU:
	        case Spins::FR:
	        case Spins::FD:
	        case Spins::FL: e_F2(); c_F2(); break;
	        case Spins::BU:
	        case Spins::BR:
	        case Spins::BD:
	        case Spins::BL: e_B2(); c_B2(); break;
	        case Spins::RU:
	        case Spins::RF:
	        case Spins::RD:
	        case Spins::RB: e_R2(); c_R2(); break;
	        // case Spins::LU:
	        // case Spins::LF:
	        // case Spins::LD:
	        // case Spins::LB:
			default: e_L2(); c_L2(); break;                 
	    }
	}
	
	void Cube::Up()  // Movement U'
	{
		switch (spin)
	    {
	        case Spins::UF:
	        case Spins::UR:
	        case Spins::UB:
	        case Spins::UL: e_Up(); c_Up(); break;
	        case Spins::DF:
	        case Spins::DR:
	        case Spins::DB:
	        case Spins::DL: e_Dp(); c_Dp(); break;
	        case Spins::FU:
	        case Spins::FR:
	        case Spins::FD:
	        case Spins::FL: e_Fp(); c_Fp(); break;
	        case Spins::BU:
	        case Spins::BR:
	        case Spins::BD:
	        case Spins::BL: e_Bp(); c_Bp(); break;
	        case Spins::RU:
	        case Spins::RF:
	        case Spins::RD:
	        case Spins::RB: e_Rp(); c_Rp(); break;
	        // case Spins::LU:
	        // case Spins::LF:
	        // case Spins::LD:
	        // case Spins::LB:
			default: e_Lp(); c_Lp(); break;                 
	    }
	}
	
	void Cube::D()  // Movement D
	{
	    switch (spin)
	    {
	    	case Spins::UF:
	    	case Spins::UR:
	    	case Spins::UB:
	    	case Spins::UL: e_D(); c_D(); break;
	    	case Spins::DF:
	    	case Spins::DR:
	    	case Spins::DB:
	    	case Spins::DL: e_U(); c_U(); break;
	    	case Spins::FU:
	    	case Spins::FR:
	    	case Spins::FD:
	    	case Spins::FL: e_B(); c_B(); break;
	    	case Spins::BU:
	    	case Spins::BR:
	    	case Spins::BD:
	    	case Spins::BL: e_F(); c_F(); break;
	    	case Spins::RU:
	    	case Spins::RF:
	    	case Spins::RD:
	    	case Spins::RB: e_L(); c_L(); break;
	    	// case Spins::LU:
	    	// case Spins::LF:
	    	// case Spins::LD:
	    	// case Spins::LB:
	    	default: e_R(); c_R(); break;
	    }
	}
	
	void Cube::D2()  // Movement D2
	{
	    switch (spin)
	    {
	    	case Spins::UF:
	    	case Spins::UR:
	    	case Spins::UB:
	    	case Spins::UL: e_D2(); c_D2(); break;
	    	case Spins::DF:
	    	case Spins::DR:
	    	case Spins::DB:
	    	case Spins::DL: e_U2(); c_U2(); break;
	    	case Spins::FU:
	    	case Spins::FR:
	    	case Spins::FD:
	    	case Spins::FL: e_B2(); c_B2(); break;
	    	case Spins::BU:
	    	case Spins::BR:
	    	case Spins::BD:
	    	case Spins::BL: e_F2(); c_F2(); break;
	    	case Spins::RU:
	    	case Spins::RF:
	    	case Spins::RD:
	    	case Spins::RB: e_L2(); c_L2(); break;
	    	// case Spins::LU:
	    	// case Spins::LF:
	    	// case Spins::LD:
	    	// case Spins::LB:
	    	default: e_R2(); c_R2(); break;
	    }
	}
	
	void Cube::Dp()  // Movement D'
	{
	    switch (spin)
	    {
	    	case Spins::UF:
	    	case Spins::UR:
	    	case Spins::UB:
	    	case Spins::UL: e_Dp(); c_Dp(); break;
	    	case Spins::DF:
	    	case Spins::DR:
	    	case Spins::DB:
	    	case Spins::DL: e_Up(); c_Up(); break;
	    	case Spins::FU:
	    	case Spins::FR:
	    	case Spins::FD:
	    	case Spins::FL: e_Bp(); c_Bp(); break;
	    	case Spins::BU:
	    	case Spins::BR:
	    	case Spins::BD:
	    	case Spins::BL: e_Fp(); c_Fp(); break;
	    	case Spins::RU:
	    	case Spins::RF:
	    	case Spins::RD:
	    	case Spins::RB: e_Lp(); c_Lp(); break;
	    	// case Spins::LU:
	    	// case Spins::LF:
	    	// case Spins::LD:
	    	// case Spins::LB:
	    	default: e_Rp(); c_Rp(); break;
	    }
	}
	
	void Cube::F()  // Movement F
	{
	    switch (spin)
	    {
	        case Spins::FU:
	        case Spins::BU:
	        case Spins::RU:
	        case Spins::LU: e_U(); c_U(); break;
	        case Spins::FD:
	        case Spins::BD:
	        case Spins::RD:
	        case Spins::LD: e_D(); c_D(); break;
	        case Spins::UF:
	        case Spins::DF:
	        case Spins::RF:
	        case Spins::LF: e_F(); c_F(); break;
	        case Spins::UB:
	        case Spins::DB:
	        case Spins::RB:
	        case Spins::LB: e_B(); c_B(); break;
	        case Spins::UR:
	        case Spins::DR:
	        case Spins::FR:
	        case Spins::BR: e_R(); c_R(); break;
	        // case Spins::UL:
	        // case Spins::DL:
	        // case Spins::FL:
	        // case Spins::BL:
	        default: e_L(); c_L(); break;
		}
	}
	
	void Cube::F2()  // Movement F2
	{
	    switch (spin)
	    {
	        case Spins::FU:
	        case Spins::BU:
	        case Spins::RU:
	        case Spins::LU: e_U2(); c_U2(); break;
	        case Spins::FD:
	        case Spins::BD:
	        case Spins::RD:
	        case Spins::LD: e_D2(); c_D2(); break;
	        case Spins::UF:
	        case Spins::DF:
	        case Spins::RF:
	        case Spins::LF: e_F2(); c_F2(); break;
	        case Spins::UB:
	        case Spins::DB:
	        case Spins::RB:
	        case Spins::LB: e_B2(); c_B2(); break;
	        case Spins::UR:
	        case Spins::DR:
	        case Spins::FR:
	        case Spins::BR: e_R2(); c_R2(); break;
	        // case Spins::UL:
	        // case Spins::DL:
	        // case Spins::FL:
	        // case Spins::BL:
	        default: e_L2(); c_L2(); break;
		}
	}
	
	void Cube::Fp()  // Movement F'
	{
	    switch (spin)
	    {
	        case Spins::FU:
	        case Spins::BU:
	        case Spins::RU:
	        case Spins::LU: e_Up(); c_Up(); break;
	        case Spins::FD:
	        case Spins::BD:
	        case Spins::RD:
	        case Spins::LD: e_Dp(); c_Dp(); break;
	        case Spins::UF:
	        case Spins::DF:
	        case Spins::RF:
	        case Spins::LF: e_Fp(); c_Fp(); break;
	        case Spins::UB:
	        case Spins::DB:
	        case Spins::RB:
	        case Spins::LB: e_Bp(); c_Bp(); break;
	        case Spins::UR:
	        case Spins::DR:
	        case Spins::FR:
	        case Spins::BR: e_Rp(); c_Rp(); break;
	        // case Spins::UL:
	        // case Spins::DL:
	        // case Spins::FL:
	        // case Spins::BL:
	        default: e_Lp(); c_Lp(); break;
		}
	}
	
	void Cube::B()  // Movement B
	{
		switch (spin)
	    {
	        case Spins::FU:
	        case Spins::BU:
	        case Spins::RU:
	        case Spins::LU: e_D(); c_D(); break;
	        case Spins::FD:
	        case Spins::BD:
	        case Spins::RD:
	        case Spins::LD: e_U(); c_U(); break;
	        case Spins::UF:
	        case Spins::DF:
	        case Spins::RF:
	        case Spins::LF: e_B(); c_B(); break;
	        case Spins::UB:
	        case Spins::DB:
	        case Spins::RB:
	        case Spins::LB: e_F(); c_F(); break;
	        case Spins::UR:
	        case Spins::DR:
	        case Spins::FR:
	        case Spins::BR: e_L(); c_L(); break;
	        // case Spins::UL:
	        // case Spins::DL:
	        // case Spins::FL:
	        // case Spins::BL:
			default: e_R(); c_R(); break;
		}
	}
	
	void Cube::B2()  // Movement B2
	{
		switch (spin)
	    {
	        case Spins::FU:
	        case Spins::BU:
	        case Spins::RU:
	        case Spins::LU: e_D2(); c_D2(); break;
	        case Spins::FD:
	        case Spins::BD:
	        case Spins::RD:
	        case Spins::LD: e_U2(); c_U2(); break;
	        case Spins::UF:
	        case Spins::DF:
	        case Spins::RF:
	        case Spins::LF: e_B2(); c_B2(); break;
	        case Spins::UB:
	        case Spins::DB:
	        case Spins::RB:
	        case Spins::LB: e_F2(); c_F2(); break;
	        case Spins::UR:
	        case Spins::DR:
	        case Spins::FR:
	        case Spins::BR: e_L2(); c_L2(); break;
	        // case Spins::UL:
	        // case Spins::DL:
	        // case Spins::FL:
	        // case Spins::BL:
			default: e_R2(); c_R2(); break;
		}
	}
	
	void Cube::Bp()  // Movement B'
	{
		switch (spin)
	    {
	        case Spins::FU:
	        case Spins::BU:
	        case Spins::RU:
	        case Spins::LU: e_Dp(); c_Dp(); break;
	        case Spins::FD:
	        case Spins::BD:
	        case Spins::RD:
	        case Spins::LD: e_Up(); c_Up(); break;
	        case Spins::UF:
	        case Spins::DF:
	        case Spins::RF:
	        case Spins::LF: e_Bp(); c_Bp(); break;
	        case Spins::UB:
	        case Spins::DB:
	        case Spins::RB:
	        case Spins::LB: e_Fp(); c_Fp(); break;
	        case Spins::UR:
	        case Spins::DR:
	        case Spins::FR:
	        case Spins::BR: e_Lp(); c_Lp(); break;
	        // case Spins::UL:
	        // case Spins::DL:
	        // case Spins::FL:
	        // case Spins::BL:
			default: e_Rp(); c_Rp(); break;
		}
	}
	
	void Cube::R()  // Movement R
	{
	    switch (spin)
	    {
	        case Spins::FR:
	        case Spins::BL:
	        case Spins::RB:
	        case Spins::LF: e_U(); c_U(); break;
	        case Spins::FL:
	        case Spins::BR:
	        case Spins::RF:
	        case Spins::LB: e_D(); c_D(); break;
	        case Spins::UL:
	        case Spins::DR:
	        case Spins::RU:
	        case Spins::LD: e_F(); c_F(); break;
	        case Spins::UR:
	        case Spins::DL:
	        case Spins::RD:
	        case Spins::LU: e_B(); c_B(); break;
	        case Spins::UF:
	        case Spins::DB:
	        case Spins::FD:
	        case Spins::BU: e_R(); c_R(); break;
	        // case Spins::UB:
	        // case Spins::DF:
	        // case Spins::FU:
	        // case Spins::BD:
	        default: e_L(); c_L(); break;
	    }
	}
	
	void Cube::R2()  // Movement R2
	{
	    switch (spin)
	    {
	        case Spins::FR:
	        case Spins::BL:
	        case Spins::RB:
	        case Spins::LF: e_U2(); c_U2(); break;
	        case Spins::FL:
	        case Spins::BR:
	        case Spins::RF:
	        case Spins::LB: e_D2(); c_D2(); break;
	        case Spins::UL:
	        case Spins::DR:
	        case Spins::RU:
	        case Spins::LD: e_F2(); c_F2(); break;
	        case Spins::UR:
	        case Spins::DL:
	        case Spins::RD:
	        case Spins::LU: e_B2(); c_B2(); break;
	        case Spins::UF:
	        case Spins::DB:
	        case Spins::FD:
	        case Spins::BU: e_R2(); c_R2(); break;
	        // case Spins::UB:
	        // case Spins::DF:
	        // case Spins::FU:
	        // case Spins::BD:
	        default: e_L2(); c_L2(); break;
	    }
	}
	
	void Cube::Rp()  // Movement R'
	{
	    switch (spin)
	    {
	        case Spins::FR:
	        case Spins::BL:
	        case Spins::RB:
	        case Spins::LF: e_Up(); c_Up(); break;
	        case Spins::FL:
	        case Spins::BR:
	        case Spins::RF:
	        case Spins::LB: e_Dp(); c_Dp(); break;
	        case Spins::UL:
	        case Spins::DR:
	        case Spins::RU:
	        case Spins::LD: e_Fp(); c_Fp(); break;
	        case Spins::UR:
	        case Spins::DL:
	        case Spins::RD:
	        case Spins::LU: e_Bp(); c_Bp(); break;
	        case Spins::UF:
	        case Spins::DB:
	        case Spins::FD:
	        case Spins::BU: e_Rp(); c_Rp(); break;
	        // case Spins::UB:
	        // case Spins::DF:
	        // case Spins::FU:
	        // case Spins::BD:
	        default: e_Lp(); c_Lp(); break;
	    }
	}
	
	void Cube::L()  // Movement L
	{
	    switch (spin)
	    {
	        case Spins::FR:
	        case Spins::BL:
	        case Spins::RB:
	        case Spins::LF: e_D(); c_D(); break;
	        case Spins::FL:
	        case Spins::BR:
	        case Spins::RF:
	        case Spins::LB: e_U(); c_U(); break;
	        case Spins::UL:
	        case Spins::DR:
	        case Spins::RU:
	    	case Spins::LD: e_B(); c_B(); break;
	        case Spins::UR:
	        case Spins::DL:
	        case Spins::RD:
	        case Spins::LU: e_F(); c_F(); break;
	        case Spins::UF:
	        case Spins::DB:
	        case Spins::FD:
	        case Spins::BU: e_L(); c_L(); break;
	        // case Spins::UB:
	        // case Spins::DF:
	        // case Spins::FU:
	        // case Spins::BD:
	        default: e_R(); c_R(); break;
	    }
	}
	
	void Cube::L2()  // Movement L2
	{
	    switch (spin)
	    {
	        case Spins::FR:
	        case Spins::BL:
	        case Spins::RB:
	        case Spins::LF: e_D2(); c_D2(); break;
	        case Spins::FL:
	        case Spins::BR:
	        case Spins::RF:
	        case Spins::LB: e_U2(); c_U2(); break;
	        case Spins::UL:
	        case Spins::DR:
	        case Spins::RU:
	    	case Spins::LD: e_B2(); c_B2(); break;
	        case Spins::UR:
	        case Spins::DL:
	        case Spins::RD:
	        case Spins::LU: e_F2(); c_F2(); break;
	        case Spins::UF:
	        case Spins::DB:
	        case Spins::FD:
	        case Spins::BU: e_L2(); c_L2(); break;
	        // case Spins::UB:
	        // case Spins::DF:
	        // case Spins::FU:
	        // case Spins::BD:
	        default: e_R2(); c_R2(); break;
	    }
	}
	
	void Cube::Lp()  // Movement L'
	{
	    switch (spin)
	    {
	        case Spins::FR:
	        case Spins::BL:
	        case Spins::RB:
	        case Spins::LF: e_Dp(); c_Dp(); break;
	        case Spins::FL:
	        case Spins::BR:
	        case Spins::RF:
	        case Spins::LB: e_Up(); c_Up(); break;
	        case Spins::UL:
	        case Spins::DR:
	        case Spins::RU:
	    	case Spins::LD: e_Bp(); c_Bp(); break;
	        case Spins::UR:
	        case Spins::DL:
	        case Spins::RD:
	        case Spins::LU: e_Fp(); c_Fp(); break;
	        case Spins::UF:
	        case Spins::DB:
	        case Spins::FD:
	        case Spins::BU: e_Lp(); c_Lp(); break;
	        // case Spins::UB:
	        // case Spins::DF:
	        // case Spins::FU:
	        // case Spins::BD:
	        default: e_Rp(); c_Rp(); break;
	    }
	}
	
	// Apply algorithm to cube (algorithm should have developed parentheses)
	// If there are parentheses with more than one repetitions returns false and cube status remains unchanged
	bool Cube::ApplyAlgorithm(Algorithm& A)
	{
	    // Save current cube status
		S64 edges_backup = edges, corners_backup = corners;
		Spins spin_backup = spin;
	
	    // Apply movements (steps)
		for (uint n = 0; n < A.GetSize(); n++)
		{
			if(!ApplyStep(A[n]))
			{
				edges = edges_backup;
				corners = corners_backup;
				spin = spin_backup;
				return false;
			}
		}
	    return true;
	}

	// Apply movement (step) to the cube
	// Returns false if the step is a close parentheses with more than one repetition
	bool Cube::ApplyStep(const Steps s)
	{
		switch (s)
		{
			case Steps::U: 	U(); 	return true;
			case Steps::Up: Up();	return true;
			case Steps::U2: U2(); 	return true;
			case Steps::D: 	D(); 	return true;
			case Steps::Dp: Dp(); 	return true;
			case Steps::D2: D2(); 	return true;
			case Steps::F: 	F(); 	return true;
			case Steps::Fp: Fp();	return true;
			case Steps::F2: F2(); 	return true;
			case Steps::B: 	B(); 	return true;
			case Steps::Bp: Bp(); 	return true;
			case Steps::B2: B2(); 	return true;
			case Steps::R: 	R(); 	return true;
			case Steps::Rp: Rp(); 	return true;
			case Steps::R2: R2(); 	return true;
			case Steps::L: 	L(); 	return true;
			case Steps::Lp: Lp(); 	return true;
			case Steps::L2: L2(); 	return true;
			
			case Steps::x: 	x(); 	return true;
			case Steps::xp: xp(); 	return true;
			case Steps::x2: x2(); 	return true;
			case Steps::y: 	y(); 	return true;
			case Steps::yp: yp(); 	return true;
			case Steps::y2: y2(); 	return true;
			case Steps::z: 	z(); 	return true;
			case Steps::zp: zp(); 	return true;
			case Steps::z2: z2(); 	return true;

			case Steps::u: 	D(); 	y(); 	return true;
			case Steps::up: Dp();	yp(); 	return true;
			case Steps::u2: D2(); 	y2();	return true;
			case Steps::d: 	U();	yp();	return true;
			case Steps::dp: Up(); 	y();	return true;
			case Steps::d2: U2();	y2();	return true;
			case Steps::f: 	B();	z();	return true;
			case Steps::fp: Bp();	zp();	return true;
			case Steps::f2: B2();	z2();	return true;
			case Steps::b: 	F();	zp();	return true;
			case Steps::bp: Fp();	z();	return true;
			case Steps::b2: F2();	z2();	return true;
			case Steps::r: 	L();	x();	return true;
			case Steps::rp: Lp();	xp();	return true;
			case Steps::r2: L2();	x2();	return true;
			case Steps::l: 	R();	xp();	return true;
			case Steps::lp: Rp();	x();	return true;
			case Steps::l2: R2();	x2();	return true;

			case Steps::E:	U();	Dp();	yp();	return true; // E -> As layer D
			case Steps::Ep:	Up();	D();	y();	return true; // E'
			case Steps::E2:	U2();	D2();	y2();	return true; // E2
			case Steps::S:	Fp();	B();	z();	return true; // S -> As layer F
			case Steps::Sp:	F();	Bp();	zp();	return true; // S'
			case Steps::S2:	F2();	B2();	z2();	return true; // S2
			case Steps::M:	R();	Lp();	xp();	return true; // M -> As layer L
			case Steps::Mp:	Rp();	L();	x();	return true; // M'
			case Steps::M2:	R2();	L2();	x2();	return true; // M2

			case Steps::NONE:
			case Steps::PARENTHESIS_OPEN:
			case Steps::PARENTHESIS_CLOSE_1_REP: return true;

			default: return false; // Close parentheses step with more than one repetition
		}
	}
	
	// Get the sticker in the given sticker position
    Stickers Cube::GetSticker(const StickerPositions SP) const
	{
        switch (SP)
		{
			case StickerPositions::FR_F: return s_FR_F[GetStatusPos_FR()][GetStatusDir_FR()];
			case StickerPositions::FR_R: return s_FR_R[GetStatusPos_FR()][GetStatusDir_FR()];
			case StickerPositions::FL_F: return s_FL_F[GetStatusPos_FL()][GetStatusDir_FL()];
			case StickerPositions::FL_L: return s_FL_L[GetStatusPos_FL()][GetStatusDir_FL()];
			case StickerPositions::BL_B: return s_BL_B[GetStatusPos_BL()][GetStatusDir_BL()];
			case StickerPositions::BL_L: return s_BL_L[GetStatusPos_BL()][GetStatusDir_BL()];
			case StickerPositions::BR_B: return s_BR_B[GetStatusPos_BR()][GetStatusDir_BR()];
			case StickerPositions::BR_R: return s_BR_R[GetStatusPos_BR()][GetStatusDir_BR()];
				
			case StickerPositions::UF_U: return s_UF_U[GetStatusPos_UF()][GetStatusDir_UF()];
			case StickerPositions::UF_F: return s_UF_F[GetStatusPos_UF()][GetStatusDir_UF()];
			case StickerPositions::UL_U: return s_UL_U[GetStatusPos_UL()][GetStatusDir_UL()];
			case StickerPositions::UL_L: return s_UL_L[GetStatusPos_UL()][GetStatusDir_UL()];
			case StickerPositions::UB_U: return s_UB_U[GetStatusPos_UB()][GetStatusDir_UB()];
			case StickerPositions::UB_B: return s_UB_B[GetStatusPos_UB()][GetStatusDir_UB()];
			case StickerPositions::UR_U: return s_UR_U[GetStatusPos_UR()][GetStatusDir_UR()];
			case StickerPositions::UR_R: return s_UR_R[GetStatusPos_UR()][GetStatusDir_UR()];
				
			case StickerPositions::DF_D: return s_DF_D[GetStatusPos_DF()][GetStatusDir_DF()];
			case StickerPositions::DF_F: return s_DF_F[GetStatusPos_DF()][GetStatusDir_DF()];
			case StickerPositions::DL_D: return s_DL_D[GetStatusPos_DL()][GetStatusDir_DL()];
			case StickerPositions::DL_L: return s_DL_L[GetStatusPos_DL()][GetStatusDir_DL()];
			case StickerPositions::DB_D: return s_DB_D[GetStatusPos_DB()][GetStatusDir_DB()];
			case StickerPositions::DB_B: return s_DB_B[GetStatusPos_DB()][GetStatusDir_DB()];
			case StickerPositions::DR_D: return s_DR_D[GetStatusPos_DR()][GetStatusDir_DR()];
			case StickerPositions::DR_R: return s_DR_R[GetStatusPos_DR()][GetStatusDir_DR()];
		
			case StickerPositions::UFR_U: return s_UFR_U[GetStatusPos_UFR()][GetStatusDir_UFR()];
			case StickerPositions::UFR_F: return s_UFR_F[GetStatusPos_UFR()][GetStatusDir_UFR()];
			case StickerPositions::UFR_R: return s_UFR_R[GetStatusPos_UFR()][GetStatusDir_UFR()];
			case StickerPositions::UFL_U: return s_UFL_U[GetStatusPos_UFL()][GetStatusDir_UFL()];
			case StickerPositions::UFL_F: return s_UFL_F[GetStatusPos_UFL()][GetStatusDir_UFL()];
			case StickerPositions::UFL_L: return s_UFL_L[GetStatusPos_UFL()][GetStatusDir_UFL()];
				
			case StickerPositions::UBL_U: return s_UBL_U[GetStatusPos_UBL()][GetStatusDir_UBL()];
			case StickerPositions::UBL_B: return s_UBL_B[GetStatusPos_UBL()][GetStatusDir_UBL()];
			case StickerPositions::UBL_L: return s_UBL_L[GetStatusPos_UBL()][GetStatusDir_UBL()];
			case StickerPositions::UBR_U: return s_UBR_U[GetStatusPos_UBR()][GetStatusDir_UBR()];
			case StickerPositions::UBR_B: return s_UBR_B[GetStatusPos_UBR()][GetStatusDir_UBR()];
			case StickerPositions::UBR_R: return s_UBR_R[GetStatusPos_UBR()][GetStatusDir_UBR()];
			
			case StickerPositions::DFR_D: return s_DFR_D[GetStatusPos_DFR()][GetStatusDir_DFR()];
			case StickerPositions::DFR_F: return s_DFR_F[GetStatusPos_DFR()][GetStatusDir_DFR()];
			case StickerPositions::DFR_R: return s_DFR_R[GetStatusPos_DFR()][GetStatusDir_DFR()];
			case StickerPositions::DFL_D: return s_DFL_D[GetStatusPos_DFL()][GetStatusDir_DFL()];
			case StickerPositions::DFL_F: return s_DFL_F[GetStatusPos_DFL()][GetStatusDir_DFL()];
			case StickerPositions::DFL_L: return s_DFL_L[GetStatusPos_DFL()][GetStatusDir_DFL()];
				
			case StickerPositions::DBL_D: return s_DBL_D[GetStatusPos_DBL()][GetStatusDir_DBL()];
			case StickerPositions::DBL_B: return s_DBL_B[GetStatusPos_DBL()][GetStatusDir_DBL()];
			case StickerPositions::DBL_L: return s_DBL_L[GetStatusPos_DBL()][GetStatusDir_DBL()];
			case StickerPositions::DBR_D: return s_DBR_D[GetStatusPos_DBR()][GetStatusDir_DBR()];
			case StickerPositions::DBR_B: return s_DBR_B[GetStatusPos_DBR()][GetStatusDir_DBR()];
			case StickerPositions::DBR_R: return s_DBR_R[GetStatusPos_DBR()][GetStatusDir_DBR()];
	
	        case StickerPositions::U: return Stickers::U;
			case StickerPositions::D: return Stickers::D;
			case StickerPositions::F: return Stickers::F;
			case StickerPositions::B: return Stickers::B;
			case StickerPositions::R: return Stickers::R;
			// case StickerPositions::L: return Stickers::L;
			default: return Stickers::L;
		}
	}

    // Get the current position for the given sticker
	StickerPositions Cube::GetStickerPosition(const Stickers S) const
    {
        // Edges
        if (GetSticker_UF_U() == S) return StickerPositions::UF_U;
        if (GetSticker_UF_F() == S) return StickerPositions::UF_F;
        if (GetSticker_UB_U() == S) return StickerPositions::UB_U;
        if (GetSticker_UB_B() == S) return StickerPositions::UB_B;
        if (GetSticker_UR_U() == S) return StickerPositions::UR_U;
        if (GetSticker_UR_R() == S) return StickerPositions::UR_R;
        if (GetSticker_UL_U() == S) return StickerPositions::UL_U;
        if (GetSticker_UL_L() == S) return StickerPositions::UL_L;

        if (GetSticker_DF_D() == S) return StickerPositions::DF_D;
        if (GetSticker_DF_F() == S) return StickerPositions::DF_F;
        if (GetSticker_DB_D() == S) return StickerPositions::DB_D;
        if (GetSticker_DB_B() == S) return StickerPositions::DB_B;
        if (GetSticker_DR_D() == S) return StickerPositions::DR_D;
        if (GetSticker_DR_R() == S) return StickerPositions::DR_R;
        if (GetSticker_DL_D() == S) return StickerPositions::DL_D;
        if (GetSticker_DL_L() == S) return StickerPositions::DL_L;

        if (GetSticker_FR_F() == S) return StickerPositions::FR_F;
        if (GetSticker_FR_R() == S) return StickerPositions::FR_R;
        if (GetSticker_FL_F() == S) return StickerPositions::FL_F;
        if (GetSticker_FL_L() == S) return StickerPositions::FL_L;
        if (GetSticker_BR_B() == S) return StickerPositions::BR_B;
        if (GetSticker_BR_R() == S) return StickerPositions::BR_R;
        if (GetSticker_BL_B() == S) return StickerPositions::BL_B;
        if (GetSticker_BL_L() == S) return StickerPositions::BL_L;

        // Corners
        if (GetSticker_UFR_U() == S) return StickerPositions::UFR_U;
        if (GetSticker_UFR_F() == S) return StickerPositions::UFR_F;
        if (GetSticker_UFR_R() == S) return StickerPositions::UFR_R;
        if (GetSticker_UFL_U() == S) return StickerPositions::UFL_U;
        if (GetSticker_UFL_F() == S) return StickerPositions::UFL_F;
        if (GetSticker_UFL_L() == S) return StickerPositions::UFL_L;
        if (GetSticker_UBR_U() == S) return StickerPositions::UBR_U;
        if (GetSticker_UBR_B() == S) return StickerPositions::UBR_B;
        if (GetSticker_UBR_R() == S) return StickerPositions::UBR_R;
        if (GetSticker_UBL_U() == S) return StickerPositions::UBL_U;
        if (GetSticker_UBL_B() == S) return StickerPositions::UBL_B;
        if (GetSticker_UBL_L() == S) return StickerPositions::UBL_L;

        if (GetSticker_DFR_D() == S) return StickerPositions::DFR_D;
        if (GetSticker_DFR_F() == S) return StickerPositions::DFR_F;
        if (GetSticker_DFR_R() == S) return StickerPositions::DFR_R;
        if (GetSticker_DFL_D() == S) return StickerPositions::DFL_D;
        if (GetSticker_DFL_F() == S) return StickerPositions::DFL_F;
        if (GetSticker_DFL_L() == S) return StickerPositions::DFL_L;
        if (GetSticker_DBR_D() == S) return StickerPositions::DBR_D;
        if (GetSticker_DBR_B() == S) return StickerPositions::DBR_B;
        if (GetSticker_DBR_R() == S) return StickerPositions::DBR_R;
        if (GetSticker_DBL_D() == S) return StickerPositions::DBL_D;
        if (GetSticker_DBL_B() == S) return StickerPositions::DBL_B;
        if (GetSticker_DBL_L() == S) return StickerPositions::DBL_L;

        return static_cast<StickerPositions>(S); // Centers
    }
	
    // Get the current piece in the given piece position
    Pieces Cube::GetPiece(const PiecePositions P) const
    {
        switch (P)
        {
        // Edges
		case PiecePositions::UF: return static_cast<Pieces>(static_cast<int>(GetEdgePiece_UF()) + static_cast<int>(Pieces::First_Edge));
        case PiecePositions::UB: return static_cast<Pieces>(static_cast<int>(GetEdgePiece_UB()) + static_cast<int>(Pieces::First_Edge));
        case PiecePositions::UR: return static_cast<Pieces>(static_cast<int>(GetEdgePiece_UR()) + static_cast<int>(Pieces::First_Edge));
        case PiecePositions::UL: return static_cast<Pieces>(static_cast<int>(GetEdgePiece_UL()) + static_cast<int>(Pieces::First_Edge));

        case PiecePositions::DF: return static_cast<Pieces>(static_cast<int>(GetEdgePiece_DF()) + static_cast<int>(Pieces::First_Edge));
        case PiecePositions::DB: return static_cast<Pieces>(static_cast<int>(GetEdgePiece_DB()) + static_cast<int>(Pieces::First_Edge));
        case PiecePositions::DR: return static_cast<Pieces>(static_cast<int>(GetEdgePiece_DR()) + static_cast<int>(Pieces::First_Edge));
        case PiecePositions::DL: return static_cast<Pieces>(static_cast<int>(GetEdgePiece_DL()) + static_cast<int>(Pieces::First_Edge));

        case PiecePositions::FR: return static_cast<Pieces>(static_cast<int>(GetEdgePiece_FR()) + static_cast<int>(Pieces::First_Edge));
        case PiecePositions::FL: return static_cast<Pieces>(static_cast<int>(GetEdgePiece_FL()) + static_cast<int>(Pieces::First_Edge));
        case PiecePositions::BR: return static_cast<Pieces>(static_cast<int>(GetEdgePiece_BR()) + static_cast<int>(Pieces::First_Edge));
        case PiecePositions::BL: return static_cast<Pieces>(static_cast<int>(GetEdgePiece_BL()) + static_cast<int>(Pieces::First_Edge));

        // Corners
        case PiecePositions::UFR: return static_cast<Pieces>(static_cast<int>(GetCornerPiece_UFR()) + static_cast<int>(Pieces::First_Corner));
        case PiecePositions::UFL: return static_cast<Pieces>(static_cast<int>(GetCornerPiece_UFL()) + static_cast<int>(Pieces::First_Corner));
        case PiecePositions::UBR: return static_cast<Pieces>(static_cast<int>(GetCornerPiece_UBR()) + static_cast<int>(Pieces::First_Corner));
        case PiecePositions::UBL: return static_cast<Pieces>(static_cast<int>(GetCornerPiece_UBL()) + static_cast<int>(Pieces::First_Corner));

        case PiecePositions::DFR: return static_cast<Pieces>(static_cast<int>(GetCornerPiece_DFR()) + static_cast<int>(Pieces::First_Corner));
        case PiecePositions::DFL: return static_cast<Pieces>(static_cast<int>(GetCornerPiece_DFL()) + static_cast<int>(Pieces::First_Corner));
        case PiecePositions::DBR: return static_cast<Pieces>(static_cast<int>(GetCornerPiece_DBR()) + static_cast<int>(Pieces::First_Corner));
        case PiecePositions::DBL: return static_cast<Pieces>(static_cast<int>(GetCornerPiece_DBL()) + static_cast<int>(Pieces::First_Corner));

        default: return static_cast<Pieces>(P); // Centers
        }
    }

    // Get the current position for the given piece
	PiecePositions Cube::GetPiecePosition(const Pieces P) const
    {
        // Edges
        if (t_Pieces[static_cast<uint>(P)] == PiecesTypes::EDGE)
        {
            if (GetPiece(PiecePositions::UF) == P) return PiecePositions::UF;
            if (GetPiece(PiecePositions::UB) == P) return PiecePositions::UB;
            if (GetPiece(PiecePositions::UR) == P) return PiecePositions::UR;
            if (GetPiece(PiecePositions::UL) == P) return PiecePositions::UL;

            if (GetPiece(PiecePositions::DF) == P) return PiecePositions::DF;
            if (GetPiece(PiecePositions::DB) == P) return PiecePositions::DB;
            if (GetPiece(PiecePositions::DR) == P) return PiecePositions::DR;
            if (GetPiece(PiecePositions::DL) == P) return PiecePositions::DL;

            if (GetPiece(PiecePositions::FR) == P) return PiecePositions::FR;
            if (GetPiece(PiecePositions::FL) == P) return PiecePositions::FL;
            if (GetPiece(PiecePositions::BR) == P) return PiecePositions::BR;
            if (GetPiece(PiecePositions::BL) == P) return PiecePositions::BL;
        }

        // Corners
        if (t_Pieces[static_cast<uint>(P)] == PiecesTypes::CORNER)
        {
            if (GetPiece(PiecePositions::UFR) == P) return PiecePositions::UFR;
            if (GetPiece(PiecePositions::UFL) == P) return PiecePositions::UFL;
            if (GetPiece(PiecePositions::UBR) == P) return PiecePositions::UBR;
            if (GetPiece(PiecePositions::UBL) == P) return PiecePositions::UBL;

            if (GetPiece(PiecePositions::DFR) == P) return PiecePositions::DFR;
            if (GetPiece(PiecePositions::DFL) == P) return PiecePositions::DFL;
            if (GetPiece(PiecePositions::DBR) == P) return PiecePositions::DBR;
            if (GetPiece(PiecePositions::DBL) == P) return PiecePositions::DBL;
        }

        return static_cast<PiecePositions>(P); // Center)
    }

	// Get the sticker face in the given sticker position
	Faces Cube::GetFace(const StickerPositions P) const
	{
		switch (P)
		{
			case StickerPositions::FR_F: return f_FR_F[GetStatusPos_FR()][GetStatusDir_FR()];
			case StickerPositions::FR_R: return f_FR_R[GetStatusPos_FR()][GetStatusDir_FR()];
			case StickerPositions::FL_F: return f_FL_F[GetStatusPos_FL()][GetStatusDir_FL()];
			case StickerPositions::FL_L: return f_FL_L[GetStatusPos_FL()][GetStatusDir_FL()];
			case StickerPositions::BL_B: return f_BL_B[GetStatusPos_BL()][GetStatusDir_BL()];
			case StickerPositions::BL_L: return f_BL_L[GetStatusPos_BL()][GetStatusDir_BL()];
			case StickerPositions::BR_B: return f_BR_B[GetStatusPos_BR()][GetStatusDir_BR()];
			case StickerPositions::BR_R: return f_BR_R[GetStatusPos_BR()][GetStatusDir_BR()];
				
			case StickerPositions::UF_U: return f_UF_U[GetStatusPos_UF()][GetStatusDir_UF()];
			case StickerPositions::UF_F: return f_UF_F[GetStatusPos_UF()][GetStatusDir_UF()];
			case StickerPositions::UL_U: return f_UL_U[GetStatusPos_UL()][GetStatusDir_UL()];
			case StickerPositions::UL_L: return f_UL_L[GetStatusPos_UL()][GetStatusDir_UL()];
			case StickerPositions::UB_U: return f_UB_U[GetStatusPos_UB()][GetStatusDir_UB()];
			case StickerPositions::UB_B: return f_UB_B[GetStatusPos_UB()][GetStatusDir_UB()];
			case StickerPositions::UR_U: return f_UR_U[GetStatusPos_UR()][GetStatusDir_UR()];
			case StickerPositions::UR_R: return f_UR_R[GetStatusPos_UR()][GetStatusDir_UR()];
				
			case StickerPositions::DF_D: return f_DF_D[GetStatusPos_DF()][GetStatusDir_DF()];
			case StickerPositions::DF_F: return f_DF_F[GetStatusPos_DF()][GetStatusDir_DF()];
			case StickerPositions::DL_D: return f_DL_D[GetStatusPos_DL()][GetStatusDir_DL()];
			case StickerPositions::DL_L: return f_DL_L[GetStatusPos_DL()][GetStatusDir_DL()];
			case StickerPositions::DB_D: return f_DB_D[GetStatusPos_DB()][GetStatusDir_DB()];
			case StickerPositions::DB_B: return f_DB_B[GetStatusPos_DB()][GetStatusDir_DB()];
			case StickerPositions::DR_D: return f_DR_D[GetStatusPos_DR()][GetStatusDir_DR()];
			case StickerPositions::DR_R: return f_DR_R[GetStatusPos_DR()][GetStatusDir_DR()];
		
			case StickerPositions::UFR_U: return f_UFR_U[GetStatusPos_UFR()][GetStatusDir_UFR()];
			case StickerPositions::UFR_F: return f_UFR_F[GetStatusPos_UFR()][GetStatusDir_UFR()];
			case StickerPositions::UFR_R: return f_UFR_R[GetStatusPos_UFR()][GetStatusDir_UFR()];
			case StickerPositions::UFL_U: return f_UFL_U[GetStatusPos_UFL()][GetStatusDir_UFL()];
			case StickerPositions::UFL_F: return f_UFL_F[GetStatusPos_UFL()][GetStatusDir_UFL()];
			case StickerPositions::UFL_L: return f_UFL_L[GetStatusPos_UFL()][GetStatusDir_UFL()];
				
			case StickerPositions::UBL_U: return f_UBL_U[GetStatusPos_UBL()][GetStatusDir_UBL()];
			case StickerPositions::UBL_B: return f_UBL_B[GetStatusPos_UBL()][GetStatusDir_UBL()];
			case StickerPositions::UBL_L: return f_UBL_L[GetStatusPos_UBL()][GetStatusDir_UBL()];
			case StickerPositions::UBR_U: return f_UBR_U[GetStatusPos_UBR()][GetStatusDir_UBR()];
			case StickerPositions::UBR_B: return f_UBR_B[GetStatusPos_UBR()][GetStatusDir_UBR()];
			case StickerPositions::UBR_R: return f_UBR_R[GetStatusPos_UBR()][GetStatusDir_UBR()];
			
			case StickerPositions::DFR_D: return f_DFR_D[GetStatusPos_DFR()][GetStatusDir_DFR()];
			case StickerPositions::DFR_F: return f_DFR_F[GetStatusPos_DFR()][GetStatusDir_DFR()];
			case StickerPositions::DFR_R: return f_DFR_R[GetStatusPos_DFR()][GetStatusDir_DFR()];
			case StickerPositions::DFL_D: return f_DFL_D[GetStatusPos_DFL()][GetStatusDir_DFL()];
			case StickerPositions::DFL_F: return f_DFL_F[GetStatusPos_DFL()][GetStatusDir_DFL()];
			case StickerPositions::DFL_L: return f_DFL_L[GetStatusPos_DFL()][GetStatusDir_DFL()];
				
			case StickerPositions::DBL_D: return f_DBL_D[GetStatusPos_DBL()][GetStatusDir_DBL()];
			case StickerPositions::DBL_B: return f_DBL_B[GetStatusPos_DBL()][GetStatusDir_DBL()];
			case StickerPositions::DBL_L: return f_DBL_L[GetStatusPos_DBL()][GetStatusDir_DBL()];
			case StickerPositions::DBR_D: return f_DBR_D[GetStatusPos_DBR()][GetStatusDir_DBR()];
			case StickerPositions::DBR_B: return f_DBR_B[GetStatusPos_DBR()][GetStatusDir_DBR()];
			case StickerPositions::DBR_R: return f_DBR_R[GetStatusPos_DBR()][GetStatusDir_DBR()];
	
	        case StickerPositions::U: return Faces::U;
			case StickerPositions::D: return Faces::D;
			case StickerPositions::F: return Faces::F;
			case StickerPositions::B: return Faces::B;
			case StickerPositions::R: return Faces::R;
			// case StickerPositions::L: return Faces::L;
			default: return Faces::L;
		}
	}

	// Check if given piece is in given layer
	bool Cube::IsPieceInLayer(const Pieces P, const Layers L) const
	{
		if (t_Pieces[static_cast<uint>(P)] == PiecesTypes::CORNER) return IsCornerInLayer(static_cast<Corners>(static_cast<int>(P) - static_cast<int>(Pieces::First_Corner)), L);
		if (t_Pieces[static_cast<uint>(P)] == PiecesTypes::EDGE) return IsEdgeInLayer(static_cast<Edges>(static_cast<int>(P) - static_cast<int>(Pieces::First_Edge)), L);
		return ((P == Pieces::U && L == Layers::U) ||
				(P == Pieces::D && L == Layers::D) ||
				(P == Pieces::F && L == Layers::F) ||
				(P == Pieces::B && L == Layers::B) ||
				(P == Pieces::R && L == Layers::R) ||
				(P == Pieces::L && L == Layers::L));
	}

	// Check if given pieces are in given layer
	bool Cube::ArePiecesInLayer(const std::vector<Pieces> Ps, const Layers L) const
	{
		for (auto P : Ps) if (!IsPieceInLayer(P, L)) return false;
		return true;
	}

	// Check if given pieces are in given layer
	bool Cube::ArePiecesInLayer(const PiecesGroups SP, const Layers L) const
	{
		std::vector<Pieces> PList;
		if (!AddToPiecesList(SP, PList)) return false;
		return ArePiecesInLayer(PList, L);
	}

	// Add groups of pieces to a pieces list
	bool Cube::AddToPiecesList(const std::vector<PiecesGroups>& SPV, std::vector<Pieces>& PList)
	{
		for (auto SP : SPV) { if (!AddToPiecesList(SP, PList)) return false; }
		return true;
	}

	// Add a group of pieces to a pieces list
	bool Cube::AddToPiecesList(const PiecesGroups SP, std::vector<Pieces>& PList)
	{
		switch (SP)
		{
			// Four Edges
		case PiecesGroups::C_U:
			PList.push_back(Pieces::UF); PList.push_back(Pieces::UB);
			PList.push_back(Pieces::UR); PList.push_back(Pieces::UL); return true;
		case PiecesGroups::C_D:
			PList.push_back(Pieces::DF); PList.push_back(Pieces::DB);
			PList.push_back(Pieces::DR); PList.push_back(Pieces::DL); return true;
		case PiecesGroups::C_F:
			PList.push_back(Pieces::UF); PList.push_back(Pieces::DF);
			PList.push_back(Pieces::FR); PList.push_back(Pieces::FL); return true;
		case PiecesGroups::C_B:
			PList.push_back(Pieces::UB); PList.push_back(Pieces::DB);
			PList.push_back(Pieces::BR); PList.push_back(Pieces::BL); return true;
		case PiecesGroups::C_R:
			PList.push_back(Pieces::UR); PList.push_back(Pieces::DR);
			PList.push_back(Pieces::FR); PList.push_back(Pieces::BR); return true;
		case PiecesGroups::C_L:
			PList.push_back(Pieces::UL); PList.push_back(Pieces::DL);
			PList.push_back(Pieces::FL); PList.push_back(Pieces::BL); return true;

            // Corner + Edge: First element must be a corner, second an edge
		case PiecesGroups::F2L_U_UFR: PList.push_back(Pieces::UFR); PList.push_back(Pieces::FR); return true;
		case PiecesGroups::F2L_U_UFL: PList.push_back(Pieces::UFL); PList.push_back(Pieces::FL); return true;
		case PiecesGroups::F2L_U_UBR: PList.push_back(Pieces::UBR); PList.push_back(Pieces::BR); return true;
		case PiecesGroups::F2L_U_UBL: PList.push_back(Pieces::UBL); PList.push_back(Pieces::BL); return true;

		case PiecesGroups::F2L_D_DFR: PList.push_back(Pieces::DFR); PList.push_back(Pieces::FR); return true;
		case PiecesGroups::F2L_D_DFL: PList.push_back(Pieces::DFL); PList.push_back(Pieces::FL); return true;
		case PiecesGroups::F2L_D_DBR: PList.push_back(Pieces::DBR); PList.push_back(Pieces::BR); return true;
		case PiecesGroups::F2L_D_DBL: PList.push_back(Pieces::DBL); PList.push_back(Pieces::BL); return true;

		case PiecesGroups::F2L_F_UFR: PList.push_back(Pieces::UFR); PList.push_back(Pieces::UR); return true;
		case PiecesGroups::F2L_F_UFL: PList.push_back(Pieces::UFL); PList.push_back(Pieces::UL); return true;
		case PiecesGroups::F2L_F_DFR: PList.push_back(Pieces::DFR); PList.push_back(Pieces::DR); return true;
		case PiecesGroups::F2L_F_DFL: PList.push_back(Pieces::DFL); PList.push_back(Pieces::DL); return true;

		case PiecesGroups::F2L_B_UBR: PList.push_back(Pieces::UBR); PList.push_back(Pieces::UR); return true;
		case PiecesGroups::F2L_B_UBL: PList.push_back(Pieces::UBL); PList.push_back(Pieces::UL); return true;
		case PiecesGroups::F2L_B_DBR: PList.push_back(Pieces::DBR); PList.push_back(Pieces::DR); return true;
		case PiecesGroups::F2L_B_DBL: PList.push_back(Pieces::DBL); PList.push_back(Pieces::DL); return true;

		case PiecesGroups::F2L_R_UFR: PList.push_back(Pieces::UFR); PList.push_back(Pieces::UF); return true;
		case PiecesGroups::F2L_R_UBR: PList.push_back(Pieces::UBR); PList.push_back(Pieces::UB); return true;
		case PiecesGroups::F2L_R_DFR: PList.push_back(Pieces::DFR); PList.push_back(Pieces::DF); return true;
		case PiecesGroups::F2L_R_DBR: PList.push_back(Pieces::DBR); PList.push_back(Pieces::DB); return true;

		case PiecesGroups::F2L_L_UFL: PList.push_back(Pieces::UFL); PList.push_back(Pieces::UF); return true;
		case PiecesGroups::F2L_L_UBL: PList.push_back(Pieces::UBL); PList.push_back(Pieces::UB); return true;
		case PiecesGroups::F2L_L_DFL: PList.push_back(Pieces::DFL); PList.push_back(Pieces::DF); return true;
		case PiecesGroups::F2L_L_DBL: PList.push_back(Pieces::DBL); PList.push_back(Pieces::DB); return true;

			/* TODO: Complete */

		default: return false;
		}
	}

	// Check if the given piece cube is solved
	bool Cube::IsSolved(const Pieces P) const
	{
		switch (P)
		{
		case Pieces::FR: return IsSolved_FR();
		case Pieces::FL: return IsSolved_FL();
		case Pieces::BL: return IsSolved_BL();
		case Pieces::BR: return IsSolved_BR();
		case Pieces::UF: return IsSolved_UF();
		case Pieces::UL: return IsSolved_UL();
		case Pieces::UB: return IsSolved_UB();
		case Pieces::UR: return IsSolved_UR();
		case Pieces::DF: return IsSolved_DF();
		case Pieces::DL: return IsSolved_DL();
		case Pieces::DB: return IsSolved_DB();
		case Pieces::DR: return IsSolved_DR();

		case Pieces::UFR: return IsSolved_UFR();
		case Pieces::UFL: return IsSolved_UFL();
		case Pieces::UBL: return IsSolved_UBL();
		case Pieces::UBR: return IsSolved_UBR();
		case Pieces::DFR: return IsSolved_DFR();
		case Pieces::DFL: return IsSolved_DFL();
		case Pieces::DBL: return IsSolved_DBL();
		case Pieces::DBR: return IsSolved_DBR();

		case Pieces::U:
		case Pieces::D:
		case Pieces::F:
		case Pieces::B:
		case Pieces::R:
		case Pieces::L: return true;

		default: return false;
		}
	}

	// Check if the cube is solved for the given group of pieces
	bool Cube::IsSolved(const PiecesGroups SP) const
	{
		std::vector<Pieces> PList;
		std::vector<Edges> EList;
		std::vector<Corners> CList;

		AddToPiecesList(SP, PList);
		for (auto P : PList)
		{
			if (IsEdge(P)) EList.push_back(static_cast<Edges>(static_cast<int>(P) - static_cast<int>(Pieces::First_Edge)));
			else if (IsCorner(P)) CList.push_back(static_cast<Corners>(static_cast<int>(P) - static_cast<int>(Pieces::First_Corner)));
		}

		return IsSolved(GetMasksSolvedEdges(EList), GetMasksSolvedCorners(CList));
	}

	// Check if the cube is solved for the given groups of pieces
	bool Cube::IsSolved(const std::vector<PiecesGroups>& SPV) const
	{
		for (auto SP : SPV) { if (!IsSolved(SP)) return false; }
		return true;
	}

	// Check if the cube is solved for the given layer
	bool Cube::IsSolved(const Layers Ly) const
	{
		switch (Ly)
		{
		case Layers::U: return IsSolved(EMASK_U, CMASK_U);
		case Layers::D: return IsSolved(EMASK_D, CMASK_D);
		case Layers::F: return IsSolved(EMASK_F, CMASK_F);
		case Layers::B: return IsSolved(EMASK_B, CMASK_B);
		case Layers::R: return IsSolved(EMASK_R, CMASK_R);
		case Layers::L: return IsSolved(EMASK_L, CMASK_L);

		case Layers::E: return IsSolved(EMASK_E, CMASK_E);
		case Layers::M: return IsSolved(EMASK_M, CMASK_M);
		case Layers::S: return IsSolved(EMASK_S, CMASK_S);
		
		default: return false;
		}
	}

	// Checks is the main face of given layer has the correct orientation
	bool Cube::IsLayerOriented(const Layers Ly) const
	{
		switch (Ly)
		{
		case Layers::U: 
			return (GetFace_UF_U() == Faces::U) &&
			 	   (GetFace_UB_U() == Faces::U) &&
				   (GetFace_UL_U() == Faces::U) &&
				   (GetFace_UR_U() == Faces::U) &&
				   (GetFace_UFL_U() == Faces::U) &&
				   (GetFace_UFR_U() == Faces::U) &&
				   (GetFace_UBL_U() == Faces::U) &&
				   (GetFace_UBR_U() == Faces::U);
		case Layers::D: 
			return (GetFace_DF_D() == Faces::D) &&
			 	   (GetFace_DB_D() == Faces::D) &&
				   (GetFace_DL_D() == Faces::D) &&
				   (GetFace_DR_D() == Faces::D) &&
				   (GetFace_DFL_D() == Faces::D) &&
				   (GetFace_DFR_D() == Faces::D) &&
				   (GetFace_DBL_D() == Faces::D) &&
				   (GetFace_DBR_D() == Faces::D);
		case Layers::F: 
			return (GetFace_UF_F() == Faces::F) &&
			 	   (GetFace_DF_F() == Faces::F) &&
				   (GetFace_FR_F() == Faces::F) &&
				   (GetFace_FL_F() == Faces::F) &&
				   (GetFace_UFR_F() == Faces::F) &&
				   (GetFace_UFL_F() == Faces::F) &&
				   (GetFace_DFR_F() == Faces::F) &&
				   (GetFace_DFL_F() == Faces::F);
		case Layers::B: 
			return (GetFace_UB_B() == Faces::B) &&
			 	   (GetFace_DB_B() == Faces::B) &&
				   (GetFace_BR_B() == Faces::B) &&
				   (GetFace_BL_B() == Faces::B) &&
				   (GetFace_UBR_B() == Faces::B) &&
				   (GetFace_UBL_B() == Faces::B) &&
				   (GetFace_DBR_B() == Faces::B) &&
				   (GetFace_DBL_B() == Faces::B);
		case Layers::R: 
			return (GetFace_UR_R() == Faces::R) &&
			 	   (GetFace_DR_R() == Faces::R) &&
				   (GetFace_FR_R() == Faces::R) &&
				   (GetFace_BR_R() == Faces::R) &&
				   (GetFace_UFR_R() == Faces::R) &&
				   (GetFace_UBR_R() == Faces::R) &&
				   (GetFace_DFR_R() == Faces::R) &&
				   (GetFace_DBR_R() == Faces::R);
		case Layers::L: 
			return (GetFace_UL_L() == Faces::L) &&
			 	   (GetFace_DL_L() == Faces::L) &&
				   (GetFace_FL_L() == Faces::L) &&
				   (GetFace_BL_L() == Faces::L) &&
				   (GetFace_UFL_L() == Faces::L) &&
				   (GetFace_UBL_L() == Faces::L) &&
				   (GetFace_DFL_L() == Faces::L) &&
				   (GetFace_DBL_L() == Faces::L);
		default: return false;
		}
	}

    // Get the number of F2L solved for given cross layer
    uint Cube::GetF2LSolved(Layers CrossLayer) const
    {
        uint F2L_Counter = 0u;

        switch (CrossLayer)
        {
        case Layers::U:
            if (!IsSolved(PiecesGroups::C_U)) break;
            if (IsSolved(PiecesGroups::F2L_U_UFR)) F2L_Counter++;
            if (IsSolved(PiecesGroups::F2L_U_UFL)) F2L_Counter++;
            if (IsSolved(PiecesGroups::F2L_U_UBR)) F2L_Counter++;
            if (IsSolved(PiecesGroups::F2L_U_UBL)) F2L_Counter++;
            break;

        case Layers::D:
            if (!IsSolved(PiecesGroups::C_D)) break;
            if (IsSolved(PiecesGroups::F2L_D_DFR)) F2L_Counter++;
            if (IsSolved(PiecesGroups::F2L_D_DFL)) F2L_Counter++;
            if (IsSolved(PiecesGroups::F2L_D_DBR)) F2L_Counter++;
            if (IsSolved(PiecesGroups::F2L_D_DBL)) F2L_Counter++;
            break;

        case Layers::F:
            if (!IsSolved(PiecesGroups::C_F)) break;
            if (IsSolved(PiecesGroups::F2L_F_UFR)) F2L_Counter++;
            if (IsSolved(PiecesGroups::F2L_F_UFL)) F2L_Counter++;
            if (IsSolved(PiecesGroups::F2L_F_DFR)) F2L_Counter++;
            if (IsSolved(PiecesGroups::F2L_F_DFL)) F2L_Counter++;
            break;

        case Layers::B:
            if (!IsSolved(PiecesGroups::C_B)) break;
            if (IsSolved(PiecesGroups::F2L_B_UBR)) F2L_Counter++;
            if (IsSolved(PiecesGroups::F2L_B_UBL)) F2L_Counter++;
            if (IsSolved(PiecesGroups::F2L_B_DBR)) F2L_Counter++;
            if (IsSolved(PiecesGroups::F2L_B_DBL)) F2L_Counter++;
            break;

        case Layers::R:
            if (!IsSolved(PiecesGroups::C_R)) break;
            if (IsSolved(PiecesGroups::F2L_R_UFR)) F2L_Counter++;
            if (IsSolved(PiecesGroups::F2L_R_UBR)) F2L_Counter++;
            if (IsSolved(PiecesGroups::F2L_R_DFR)) F2L_Counter++;
            if (IsSolved(PiecesGroups::F2L_R_DBR)) F2L_Counter++;
            break;

        case Layers::L:
            if (!IsSolved(PiecesGroups::C_L)) break;
            if (IsSolved(PiecesGroups::F2L_L_UFL)) F2L_Counter++;
            if (IsSolved(PiecesGroups::F2L_L_UBL)) F2L_Counter++;
            if (IsSolved(PiecesGroups::F2L_L_DFL)) F2L_Counter++;
            if (IsSolved(PiecesGroups::F2L_L_DBL)) F2L_Counter++;
            break;

        default: break;
        }
        return F2L_Counter;
    }

    // Get if the given F2L pair is adjacent (the corner next to the edge), orientation is not checked
    bool Cube::IsF2LAdjacent(PiecesGroups F2L) const
    {
        std::vector<Pieces> F2L_List;
        AddToPiecesList(F2L, F2L_List);
        if (F2L_List.size() != 2) return false;

        PiecePositions F2L_Corner = GetPiecePosition(F2L_List[0]), F2L_Edge = GetPiecePosition(F2L_List[1]);

        switch (F2L_Corner)
        {
        case PiecePositions::UFR: return F2L_Edge == PiecePositions::UF || F2L_Edge == PiecePositions::UR || F2L_Edge == PiecePositions::FR;
        case PiecePositions::UFL: return F2L_Edge == PiecePositions::UF || F2L_Edge == PiecePositions::UL || F2L_Edge == PiecePositions::FL;
        case PiecePositions::UBR: return F2L_Edge == PiecePositions::UB || F2L_Edge == PiecePositions::UR || F2L_Edge == PiecePositions::BR;
        case PiecePositions::UBL: return F2L_Edge == PiecePositions::UB || F2L_Edge == PiecePositions::UL || F2L_Edge == PiecePositions::BL;

        case PiecePositions::DFR: return F2L_Edge == PiecePositions::DF || F2L_Edge == PiecePositions::DR || F2L_Edge == PiecePositions::FR;
        case PiecePositions::DFL: return F2L_Edge == PiecePositions::DF || F2L_Edge == PiecePositions::DL || F2L_Edge == PiecePositions::FL;
        case PiecePositions::DBR: return F2L_Edge == PiecePositions::DB || F2L_Edge == PiecePositions::DR || F2L_Edge == PiecePositions::BR;
        case PiecePositions::DBL: return F2L_Edge == PiecePositions::DB || F2L_Edge == PiecePositions::DL || F2L_Edge == PiecePositions::BL;

        default: return false;
        }
    }

    // Check if the common colors for F2L pair are in the same face
    bool Cube::IsF2LOriented(PiecesGroups F2L) const
    {
        std::vector<Pieces> F2L_List;
        AddToPiecesList(F2L, F2L_List);
        if (F2L_List.size() != 2) return false;

		PiecePositions F2L_Corner = GetPiecePosition(F2L_List[0]), F2L_Edge = GetPiecePosition(F2L_List[1]);

        StickerPositions Edge_Sticker_1, Edge_Sticker_2, Corner_Sticker_1, Corner_Sticker_2, Corner_Sticker_3;
        switch (F2L_Edge)
        {
        case PiecePositions::UF: Edge_Sticker_1 = StickerPositions::UF_U; Edge_Sticker_2 = StickerPositions::UF_F; break;
        case PiecePositions::UB: Edge_Sticker_1 = StickerPositions::UB_U; Edge_Sticker_2 = StickerPositions::UB_B; break;
        case PiecePositions::UR: Edge_Sticker_1 = StickerPositions::UR_U; Edge_Sticker_2 = StickerPositions::UR_R; break;
        case PiecePositions::UL: Edge_Sticker_1 = StickerPositions::UL_U; Edge_Sticker_2 = StickerPositions::UL_L; break;
        case PiecePositions::DF: Edge_Sticker_1 = StickerPositions::DF_D; Edge_Sticker_2 = StickerPositions::DF_F; break;
        case PiecePositions::DB: Edge_Sticker_1 = StickerPositions::DB_D; Edge_Sticker_2 = StickerPositions::DB_B; break;
        case PiecePositions::DR: Edge_Sticker_1 = StickerPositions::DR_D; Edge_Sticker_2 = StickerPositions::DR_R; break;
        case PiecePositions::DL: Edge_Sticker_1 = StickerPositions::DL_D; Edge_Sticker_2 = StickerPositions::DL_L; break;
        case PiecePositions::FR: Edge_Sticker_1 = StickerPositions::FR_F; Edge_Sticker_2 = StickerPositions::FR_R; break;
        case PiecePositions::FL: Edge_Sticker_1 = StickerPositions::FL_F; Edge_Sticker_2 = StickerPositions::FL_L; break;
        case PiecePositions::BR: Edge_Sticker_1 = StickerPositions::BR_B; Edge_Sticker_2 = StickerPositions::BR_R; break;
        case PiecePositions::BL: Edge_Sticker_1 = StickerPositions::BL_B; Edge_Sticker_2 = StickerPositions::BL_L; break;
        default: return false;
        }

        switch (F2L_Corner)
        {
        case PiecePositions::UFR: Corner_Sticker_1 = StickerPositions::UFR_U; Corner_Sticker_2 = StickerPositions::UFR_F; Corner_Sticker_3 = StickerPositions::UFR_R; break;
        case PiecePositions::UFL: Corner_Sticker_1 = StickerPositions::UFL_U; Corner_Sticker_2 = StickerPositions::UFL_F; Corner_Sticker_3 = StickerPositions::UFL_L; break;
        case PiecePositions::UBR: Corner_Sticker_1 = StickerPositions::UBR_U; Corner_Sticker_2 = StickerPositions::UBR_B; Corner_Sticker_3 = StickerPositions::UBR_R; break;
        case PiecePositions::UBL: Corner_Sticker_1 = StickerPositions::UBL_U; Corner_Sticker_2 = StickerPositions::UBL_B; Corner_Sticker_3 = StickerPositions::UBL_L; break;
        case PiecePositions::DFR: Corner_Sticker_1 = StickerPositions::DFR_D; Corner_Sticker_2 = StickerPositions::DFR_F; Corner_Sticker_3 = StickerPositions::DFR_R; break;
        case PiecePositions::DFL: Corner_Sticker_1 = StickerPositions::DFL_D; Corner_Sticker_2 = StickerPositions::DFL_F; Corner_Sticker_3 = StickerPositions::DFL_L; break;
        case PiecePositions::DBR: Corner_Sticker_1 = StickerPositions::DBR_D; Corner_Sticker_2 = StickerPositions::DBR_B; Corner_Sticker_3 = StickerPositions::DBR_R; break;
        case PiecePositions::DBL: Corner_Sticker_1 = StickerPositions::DBL_D; Corner_Sticker_2 = StickerPositions::DBL_B; Corner_Sticker_3 = StickerPositions::DBL_L; break;
        default: return false;
        }

        Faces ES1 = GetFace(Edge_Sticker_1), ES2 = GetFace(Edge_Sticker_2),
              CS1 = GetFace(Corner_Sticker_1), CS2 = GetFace(Corner_Sticker_2), CS3 = GetFace(Corner_Sticker_3);

        return ((ES1 == CS1) && (ES2 == CS2)) ||
               ((ES1 == CS1) && (ES2 == CS1)) ||
               ((ES1 == CS1) && (ES2 == CS3)) ||
               ((ES1 == CS3) && (ES2 == CS1)) ||
               ((ES1 == CS2) && (ES2 == CS3)) ||
               ((ES1 == CS3) && (ES2 == CS2));
    }
}

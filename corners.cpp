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

#include "corners.h"

namespace grcube3
{	
	// Array to get the face (color) in the UFR_U sticker position
	const Faces c_Corners::f_UFR_U[8][3] =
	{ //      UD        FB        RL
	    {Faces::U, Faces::R, Faces::F}, // UFR
	    {Faces::U, Faces::F, Faces::L}, // UFL
	    {Faces::U, Faces::L, Faces::B}, // UBL
	    {Faces::U, Faces::B, Faces::R}, // UBR
	    {Faces::D, Faces::F, Faces::R}, // DFR
	    {Faces::D, Faces::L, Faces::F}, // DFL
	    {Faces::D, Faces::B, Faces::L}, // DBL
	    {Faces::D, Faces::R, Faces::B}  // DBR
	};
	
	// Array to get the face (color) in the UFR_F sticker position
	const Faces c_Corners::f_UFR_F[8][3] =
	{ //      UD        FB        RL
		{Faces::F, Faces::U, Faces::R}, // UFR
		{Faces::L, Faces::U, Faces::F}, // UFL
		{Faces::B, Faces::U, Faces::L}, // UBL
		{Faces::R, Faces::U, Faces::B}, // UBR
		{Faces::R, Faces::D, Faces::F}, // DFR
		{Faces::F, Faces::D, Faces::L}, // DFL
		{Faces::L, Faces::D, Faces::B}, // DBL
		{Faces::B, Faces::D, Faces::R}  // DBR
	};
	
	// Array to get the face (color) in the UFR_R sticker position
	const Faces c_Corners::f_UFR_R[8][3] =
	{ //      UD        FB        RL
		{Faces::R, Faces::F, Faces::U}, // UFR
		{Faces::F, Faces::L, Faces::U}, // UFL
		{Faces::L, Faces::B, Faces::U}, // UBL
		{Faces::B, Faces::R, Faces::U}, // UBR
		{Faces::F, Faces::R, Faces::D}, // DFR
		{Faces::L, Faces::F, Faces::D}, // DFL
		{Faces::B, Faces::L, Faces::D}, // DBL
		{Faces::R, Faces::B, Faces::D}  // DBR
	};
	
	// Array to get the face (color) in the UFL_U sticker position
	const Faces c_Corners::f_UFL_U[8][3] =
	{ //      UD        FB        RL
		{Faces::U, Faces::F, Faces::R}, // UFR
		{Faces::U, Faces::L, Faces::F}, // UFL
		{Faces::U, Faces::B, Faces::L}, // UBL
		{Faces::U, Faces::R, Faces::B}, // UBR
		{Faces::D, Faces::R, Faces::F}, // DFR
		{Faces::D, Faces::F, Faces::L}, // DFL
		{Faces::D, Faces::L, Faces::B}, // DBL
		{Faces::D, Faces::B, Faces::R}  // DBR
	};
	
	// Array to get the face (color) in the UFL_F sticker position
	const Faces c_Corners::f_UFL_F[8][3] =
	{ //      UD        FB        RL
		{Faces::R, Faces::U, Faces::F}, // UFR
		{Faces::F, Faces::U, Faces::L}, // UFL
		{Faces::L, Faces::U, Faces::B}, // UBL
		{Faces::B, Faces::U, Faces::R}, // UBR
		{Faces::F, Faces::D, Faces::R}, // DFR
		{Faces::L, Faces::D, Faces::F}, // DFL
		{Faces::B, Faces::D, Faces::L}, // DBL
		{Faces::R, Faces::D, Faces::B}  // DBR
	};
	
	// Array to get the face (color) in the UFL_L sticker position
	const Faces c_Corners::f_UFL_L[8][3] =
	{ //      UD        FB        RL
		{Faces::F, Faces::R, Faces::U}, // UFR
		{Faces::L, Faces::F, Faces::U}, // UFL
		{Faces::B, Faces::L, Faces::U}, // UBL
		{Faces::R, Faces::B, Faces::U}, // UBR
		{Faces::R, Faces::F, Faces::D}, // DFR
		{Faces::F, Faces::L, Faces::D}, // DFL
		{Faces::L, Faces::B, Faces::D}, // DBL
		{Faces::B, Faces::R, Faces::D}  // DBR
	};
	
	// Array to get the sticker in the UFR_U sticker position
	const Stickers c_Corners::s_UFR_U[8][3] =
	{ //      UD               FB               RL
	    {Stickers::UFR_U, Stickers::UFR_R, Stickers::UFR_F}, // UFR
	    {Stickers::UFL_U, Stickers::UFL_F, Stickers::UFL_L}, // UFL
	    {Stickers::UBL_U, Stickers::UBL_L, Stickers::UBL_B}, // UBL
	    {Stickers::UBR_U, Stickers::UBR_B, Stickers::UBR_R}, // UBR
	    {Stickers::DFR_D, Stickers::DFR_F, Stickers::DFR_R}, // DFR
	    {Stickers::DFL_D, Stickers::DFL_L, Stickers::DFL_F}, // DFL
	    {Stickers::DBL_D, Stickers::DBL_B, Stickers::DBL_L}, // DBL
	    {Stickers::DBR_D, Stickers::DBR_R, Stickers::DBR_B}  // DBR
	};
	
	// Array to get the sticker in the UFR_F sticker position
	const Stickers c_Corners::s_UFR_F[8][3] =
	{ //      UD               FB               RL
		{Stickers::UFR_F, Stickers::UFR_U, Stickers::UFR_R}, // UFR
		{Stickers::UFL_L, Stickers::UFL_U, Stickers::UFL_F}, // UFL
		{Stickers::UBL_B, Stickers::UBL_U, Stickers::UBL_L}, // UBL
		{Stickers::UBR_R, Stickers::UBR_U, Stickers::UBR_B}, // UBR
		{Stickers::DFR_R, Stickers::DFR_D, Stickers::DFR_F}, // DFR
		{Stickers::DFL_F, Stickers::DFL_D, Stickers::DFL_L}, // DFL
		{Stickers::DBL_L, Stickers::DBL_D, Stickers::DBL_B}, // DBL
		{Stickers::DBR_B, Stickers::DBR_D, Stickers::DBR_R}  // DBR
	};
	
	// Array to get the sticker in the UFR_R sticker position
	const Stickers c_Corners::s_UFR_R[8][3] =
	{ //      UD               FB               RL
		{Stickers::UFR_R, Stickers::UFR_F, Stickers::UFR_U}, // UFR
		{Stickers::UFL_F, Stickers::UFL_L, Stickers::UFL_U}, // UFL
		{Stickers::UBL_L, Stickers::UBL_B, Stickers::UBL_U}, // UBL
		{Stickers::UBR_B, Stickers::UBR_R, Stickers::UBR_U}, // UBR
		{Stickers::DFR_F, Stickers::DFR_R, Stickers::DFR_D}, // DFR
		{Stickers::DFL_L, Stickers::DFL_F, Stickers::DFL_D}, // DFL
		{Stickers::DBL_B, Stickers::DBL_L, Stickers::DBL_D}, // DBL
		{Stickers::DBR_R, Stickers::DBR_B, Stickers::DBR_D}  // DBR
	};
	
	// Array to get the sticker in the UFL_U sticker position
	const Stickers c_Corners::s_UFL_U[8][3] =
	{ //      UD               FB               RL
		{Stickers::UFR_U, Stickers::UFR_F, Stickers::UFR_R}, // UFR
		{Stickers::UFL_U, Stickers::UFL_L, Stickers::UFL_F}, // UFL
		{Stickers::UBL_U, Stickers::UBL_B, Stickers::UBL_L}, // UBL
		{Stickers::UBR_U, Stickers::UBR_R, Stickers::UBR_B}, // UBR
		{Stickers::DFR_D, Stickers::DFR_R, Stickers::DFR_F}, // DFR
		{Stickers::DFL_D, Stickers::DFL_F, Stickers::DFL_L}, // DFL
		{Stickers::DBL_D, Stickers::DBL_L, Stickers::DBL_B}, // DBL
		{Stickers::DBR_D, Stickers::DBR_B, Stickers::DBR_R}  // DBR
	};
	
	// Array to get the sticker in the UFL_F sticker position
	const Stickers c_Corners::s_UFL_F[8][3] =
	{ //      UD               FB               RL
		{Stickers::UFR_R, Stickers::UFR_U, Stickers::UFR_F}, // UFR
		{Stickers::UFL_F, Stickers::UFL_U, Stickers::UFL_L}, // UFL
		{Stickers::UBL_L, Stickers::UBL_U, Stickers::UBL_B}, // UBL
		{Stickers::UBR_B, Stickers::UBR_U, Stickers::UBR_R}, // UBR
		{Stickers::DFR_F, Stickers::DFR_D, Stickers::DFR_R}, // DFR
		{Stickers::DFL_L, Stickers::DFL_D, Stickers::DFL_F}, // DFL
		{Stickers::DBL_B, Stickers::DBL_D, Stickers::DBL_L}, // DBL
		{Stickers::DBR_R, Stickers::DBR_D, Stickers::DBR_B}  // DBR
	};
	
	// Array to get the sticker in the UFL_L sticker position
	const Stickers c_Corners::s_UFL_L[8][3] =
	{ //      UD               FB               RL
		{Stickers::UFR_F, Stickers::UFR_R, Stickers::UFR_U}, // UFR
		{Stickers::UFL_L, Stickers::UFL_F, Stickers::UFL_U}, // UFL
		{Stickers::UBL_B, Stickers::UBL_L, Stickers::UBL_U}, // UBL
		{Stickers::UBR_R, Stickers::UBR_B, Stickers::UBR_U}, // UBR
		{Stickers::DFR_R, Stickers::DFR_F, Stickers::DFR_D}, // DFR
		{Stickers::DFL_F, Stickers::DFL_L, Stickers::DFL_D}, // DFL
		{Stickers::DBL_L, Stickers::DBL_B, Stickers::DBL_D}, // DBL
		{Stickers::DBR_B, Stickers::DBR_R, Stickers::DBR_D}  // DBR
	};

	void c_Corners::c_U() // U
	{
		S64 buffer = GetStatus_UFR();
		PutStatus_UFR(GetStatus_UBR());
		PutStatus_UBR(GetStatus_UBL());
		PutStatus_UBL(GetStatus_UFL());
		PutStatus_UFL(buffer);

		buffer = GetStatusDir_UFR();
		if (buffer == CORNER_DIR_FB) PutStatusDir_UFR(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_UFR(CORNER_DIR_FB);
		
		buffer = GetStatusDir_UFL();
		if (buffer == CORNER_DIR_FB) PutStatusDir_UFL(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_UFL(CORNER_DIR_FB);
	
		buffer = GetStatusDir_UBL();
		if (buffer == CORNER_DIR_FB) PutStatusDir_UBL(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_UBL(CORNER_DIR_FB);
		
		buffer = GetStatusDir_UBR();
		if (buffer == CORNER_DIR_FB) PutStatusDir_UBR(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_UBR(CORNER_DIR_FB);
	}
	
	void c_Corners::c_U2() // U2
	{
		S64 buffer = GetStatus_UFR();
		PutStatus_UFR(GetStatus_UBL());
		PutStatus_UBL(buffer);
	
		buffer = GetStatus_UFL();
		PutStatus_UFL(GetStatus_UBR());
		PutStatus_UBR(buffer);
	}
	
	void c_Corners::c_Up() // U'
	{
		S64 buffer = GetStatus_UFR();
		PutStatus_UFR(GetStatus_UFL());
		PutStatus_UFL(GetStatus_UBL());
		PutStatus_UBL(GetStatus_UBR());
		PutStatus_UBR(buffer);

		buffer = GetStatusDir_UFR();
		if (buffer == CORNER_DIR_FB) PutStatusDir_UFR(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_UFR(CORNER_DIR_FB);
		
		buffer = GetStatusDir_UFL();
		if (buffer == CORNER_DIR_FB) PutStatusDir_UFL(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_UFL(CORNER_DIR_FB);
	
		buffer = GetStatusDir_UBL();
		if (buffer == CORNER_DIR_FB) PutStatusDir_UBL(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_UBL(CORNER_DIR_FB);
		
		buffer = GetStatusDir_UBR();
		if (buffer == CORNER_DIR_FB) PutStatusDir_UBR(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_UBR(CORNER_DIR_FB);
	}
	
	void c_Corners::c_D() // D
	{
		S64 buffer = GetStatus_DFR();
		PutStatus_DFR(GetStatus_DFL());
		PutStatus_DFL(GetStatus_DBL());
		PutStatus_DBL(GetStatus_DBR());
		PutStatus_DBR(buffer);

		buffer = GetStatusDir_DFR();
		if (buffer == CORNER_DIR_FB) PutStatusDir_DFR(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_DFR(CORNER_DIR_FB);
		
		buffer = GetStatusDir_DFL();
		if (buffer == CORNER_DIR_FB) PutStatusDir_DFL(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_DFL(CORNER_DIR_FB);
	
		buffer = GetStatusDir_DBL();
		if (buffer == CORNER_DIR_FB) PutStatusDir_DBL(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_DBL(CORNER_DIR_FB);
		
		buffer = GetStatusDir_DBR();
		if (buffer == CORNER_DIR_FB) PutStatusDir_DBR(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_DBR(CORNER_DIR_FB);
	}
	
	void c_Corners::c_D2() // D2
	{
		S64 buffer = GetStatus_DFR();
		PutStatus_DFR(GetStatus_DBL());
		PutStatus_DBL(buffer);
	
		buffer = GetStatus_DFL();
		PutStatus_DFL(GetStatus_DBR());
		PutStatus_DBR(buffer);
	}
	
	void c_Corners::c_Dp() // D'
	{
		S64 buffer = GetStatus_DFR();
		PutStatus_DFR(GetStatus_DBR());
		PutStatus_DBR(GetStatus_DBL());
		PutStatus_DBL(GetStatus_DFL());
		PutStatus_DFL(buffer);

		buffer = GetStatusDir_DFR();
		if (buffer == CORNER_DIR_FB) PutStatusDir_DFR(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_DFR(CORNER_DIR_FB);
		
		buffer = GetStatusDir_DFL();
		if (buffer == CORNER_DIR_FB) PutStatusDir_DFL(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_DFL(CORNER_DIR_FB);
	
		buffer = GetStatusDir_DBL();
		if (buffer == CORNER_DIR_FB) PutStatusDir_DBL(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_DBL(CORNER_DIR_FB);
		
		buffer = GetStatusDir_DBR();
		if (buffer == CORNER_DIR_FB) PutStatusDir_DBR(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_DBR(CORNER_DIR_FB);
	}
	
	void c_Corners::c_F() // F
	{
		S64 buffer = GetStatus_UFR();
		PutStatus_UFR(GetStatus_UFL());
		PutStatus_UFL(GetStatus_DFL());
		PutStatus_DFL(GetStatus_DFR());
		PutStatus_DFR(buffer);
	
		buffer = GetStatusDir_UFR();
		if (buffer == CORNER_DIR_UD) PutStatusDir_UFR(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_UFR(CORNER_DIR_UD);
		
		buffer = GetStatusDir_UFL();
		if (buffer == CORNER_DIR_UD) PutStatusDir_UFL(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_UFL(CORNER_DIR_UD);
	
		buffer = GetStatusDir_DFL();
		if (buffer == CORNER_DIR_UD) PutStatusDir_DFL(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_DFL(CORNER_DIR_UD);
		
		buffer = GetStatusDir_DFR();
		if (buffer == CORNER_DIR_UD) PutStatusDir_DFR(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_DFR(CORNER_DIR_UD);	
	}
	
	void c_Corners::c_F2() // F2
	{
		S64 buffer = GetStatus_UFR();
		PutStatus_UFR(GetStatus_DFL());
		PutStatus_DFL(buffer);
	
		buffer = GetStatus_UFL();
		PutStatus_UFL(GetStatus_DFR());
		PutStatus_DFR(buffer);
	}
	
	void c_Corners::c_Fp() // F'
	{
		S64 buffer = GetStatus_UFR();
		PutStatus_UFR(GetStatus_DFR());
		PutStatus_DFR(GetStatus_DFL());
		PutStatus_DFL(GetStatus_UFL());
		PutStatus_UFL(buffer);
	
		buffer = GetStatusDir_UFR();
		if (buffer == CORNER_DIR_UD) PutStatusDir_UFR(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_UFR(CORNER_DIR_UD);
		
		buffer = GetStatusDir_UFL();
		if (buffer == CORNER_DIR_UD) PutStatusDir_UFL(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_UFL(CORNER_DIR_UD);
	
		buffer = GetStatusDir_DFL();
		if (buffer == CORNER_DIR_UD) PutStatusDir_DFL(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_DFL(CORNER_DIR_UD);
		
		buffer = GetStatusDir_DFR();
		if (buffer == CORNER_DIR_UD) PutStatusDir_DFR(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_DFR(CORNER_DIR_UD);
	}
	
	void c_Corners::c_B() // B
	{
		S64 buffer = GetStatus_UBR();
		PutStatus_UBR(GetStatus_DBR());
		PutStatus_DBR(GetStatus_DBL());
		PutStatus_DBL(GetStatus_UBL());
		PutStatus_UBL(buffer);
		
		buffer = GetStatusDir_UBR();
		if (buffer == CORNER_DIR_UD) PutStatusDir_UBR(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_UBR(CORNER_DIR_UD);
		
		buffer = GetStatusDir_UBL();
		if (buffer == CORNER_DIR_UD) PutStatusDir_UBL(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_UBL(CORNER_DIR_UD);
	
		buffer = GetStatusDir_DBL();
		if (buffer == CORNER_DIR_UD) PutStatusDir_DBL(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_DBL(CORNER_DIR_UD);
		
		buffer = GetStatusDir_DBR();
		if (buffer == CORNER_DIR_UD) PutStatusDir_DBR(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_DBR(CORNER_DIR_UD);
	}
	
	void c_Corners::c_B2() // B2
	{
		S64 buffer = GetStatus_UBL();
		PutStatus_UBL(GetStatus_DBR());
		PutStatus_DBR(buffer);
	
		buffer = GetStatus_UBR();
		PutStatus_UBR(GetStatus_DBL());
		PutStatus_DBL(buffer);
	}
	
	void c_Corners::c_Bp() // B'
	{
		S64 buffer = GetStatus_UBR();
		PutStatus_UBR(GetStatus_UBL());
		PutStatus_UBL(GetStatus_DBL());
		PutStatus_DBL(GetStatus_DBR());
		PutStatus_DBR(buffer);
	
		buffer = GetStatusDir_UBR();
		if (buffer == CORNER_DIR_UD) PutStatusDir_UBR(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_UBR(CORNER_DIR_UD);
		
		buffer = GetStatusDir_UBL();
		if (buffer == CORNER_DIR_UD) PutStatusDir_UBL(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_UBL(CORNER_DIR_UD);
	
		buffer = GetStatusDir_DBL();
		if (buffer == CORNER_DIR_UD) PutStatusDir_DBL(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_DBL(CORNER_DIR_UD);
		
		buffer = GetStatusDir_DBR();
		if (buffer == CORNER_DIR_UD) PutStatusDir_DBR(CORNER_DIR_RL);
		else if (buffer == CORNER_DIR_RL) PutStatusDir_DBR(CORNER_DIR_UD);
	}
	
	void c_Corners::c_R() // R
	{
		S64 buffer = GetStatus_UFR();
		PutStatus_UFR(GetStatus_DFR());
		PutStatus_DFR(GetStatus_DBR());
		PutStatus_DBR(GetStatus_UBR());
		PutStatus_UBR(buffer);
	
		buffer = GetStatusDir_UFR();
		if (buffer == CORNER_DIR_UD) PutStatusDir_UFR(CORNER_DIR_FB);
		else if (buffer == CORNER_DIR_FB) PutStatusDir_UFR(CORNER_DIR_UD);
		
		buffer = GetStatusDir_DFR();
		if (buffer == CORNER_DIR_UD) PutStatusDir_DFR(CORNER_DIR_FB);
		else if (buffer == CORNER_DIR_FB) PutStatusDir_DFR(CORNER_DIR_UD);
	
		buffer = GetStatusDir_DBR();
		if (buffer == CORNER_DIR_UD) PutStatusDir_DBR(CORNER_DIR_FB);
		else if (buffer == CORNER_DIR_FB) PutStatusDir_DBR(CORNER_DIR_UD);
		
		buffer = GetStatusDir_UBR();
		if (buffer == CORNER_DIR_UD) PutStatusDir_UBR(CORNER_DIR_FB);
		else if (buffer == CORNER_DIR_FB) PutStatusDir_UBR(CORNER_DIR_UD);
	}
	
	void c_Corners::c_R2() // R2
	{
		S64 buffer = GetStatus_UFR();
		PutStatus_UFR(GetStatus_DBR());
		PutStatus_DBR(buffer);
	
		buffer = GetStatus_UBR();
		PutStatus_UBR(GetStatus_DFR());
		PutStatus_DFR(buffer);
	}
	
	void c_Corners::c_Rp() // R'
	{
		S64 buffer = GetStatus_UFR();
		PutStatus_UFR(GetStatus_UBR());
		PutStatus_UBR(GetStatus_DBR());
		PutStatus_DBR(GetStatus_DFR());
		PutStatus_DFR(buffer);
	
		buffer = GetStatusDir_UFR();
		if (buffer == CORNER_DIR_UD) PutStatusDir_UFR(CORNER_DIR_FB);
		else if (buffer == CORNER_DIR_FB) PutStatusDir_UFR(CORNER_DIR_UD);
		
		buffer = GetStatusDir_DFR();
		if (buffer == CORNER_DIR_UD) PutStatusDir_DFR(CORNER_DIR_FB);
		else if (buffer == CORNER_DIR_FB) PutStatusDir_DFR(CORNER_DIR_UD);
	
		buffer = GetStatusDir_DBR();
		if (buffer == CORNER_DIR_UD) PutStatusDir_DBR(CORNER_DIR_FB);
		else if (buffer == CORNER_DIR_FB) PutStatusDir_DBR(CORNER_DIR_UD);
		
		buffer = GetStatusDir_UBR();
		if (buffer == CORNER_DIR_UD) PutStatusDir_UBR(CORNER_DIR_FB);
		else if (buffer == CORNER_DIR_FB) PutStatusDir_UBR(CORNER_DIR_UD);
	}
	
	void c_Corners::c_L() // L
	{
		S64 buffer = GetStatus_UFL();
		PutStatus_UFL(GetStatus_UBL());
		PutStatus_UBL(GetStatus_DBL());
		PutStatus_DBL(GetStatus_DFL());
		PutStatus_DFL(buffer);
	
		buffer = GetStatusDir_UFL();
		if (buffer == CORNER_DIR_UD) PutStatusDir_UFL(CORNER_DIR_FB);
		else if (buffer == CORNER_DIR_FB) PutStatusDir_UFL(CORNER_DIR_UD);
		
		buffer = GetStatusDir_UBL();
		if (buffer == CORNER_DIR_UD) PutStatusDir_UBL(CORNER_DIR_FB);
		else if (buffer == CORNER_DIR_FB) PutStatusDir_UBL(CORNER_DIR_UD);
	
		buffer = GetStatusDir_DBL();
		if (buffer == CORNER_DIR_UD) PutStatusDir_DBL(CORNER_DIR_FB);
		else if (buffer == CORNER_DIR_FB) PutStatusDir_DBL(CORNER_DIR_UD);
		
		buffer = GetStatusDir_DFL();
		if (buffer == CORNER_DIR_UD) PutStatusDir_DFL(CORNER_DIR_FB);
		else if (buffer == CORNER_DIR_FB) PutStatusDir_DFL(CORNER_DIR_UD);
	}
	
	void c_Corners::c_L2() // L2
	{
		S64 buffer = GetStatus_UFL();
		PutStatus_UFL(GetStatus_DBL());
		PutStatus_DBL(buffer);
	
		buffer = GetStatus_UBL();
		PutStatus_UBL(GetStatus_DFL());
		PutStatus_DFL(buffer);
	}
	
	void c_Corners::c_Lp() // L'
	{
		S64 buffer = GetStatus_UFL();
		PutStatus_UFL(GetStatus_DFL());
		PutStatus_DFL(GetStatus_DBL());
		PutStatus_DBL(GetStatus_UBL());
		PutStatus_UBL(buffer);
	
		buffer = GetStatusDir_UFL();
		if (buffer == CORNER_DIR_UD) PutStatusDir_UFL(CORNER_DIR_FB);
		else if (buffer == CORNER_DIR_FB) PutStatusDir_UFL(CORNER_DIR_UD);
		
		buffer = GetStatusDir_UBL();
		if (buffer == CORNER_DIR_UD) PutStatusDir_UBL(CORNER_DIR_FB);
		else if (buffer == CORNER_DIR_FB) PutStatusDir_UBL(CORNER_DIR_UD);
	
		buffer = GetStatusDir_DBL();
		if (buffer == CORNER_DIR_UD) PutStatusDir_DBL(CORNER_DIR_FB);
		else if (buffer == CORNER_DIR_FB) PutStatusDir_DBL(CORNER_DIR_UD);
		
		buffer = GetStatusDir_DFL();
		if (buffer == CORNER_DIR_UD) PutStatusDir_DFL(CORNER_DIR_FB);
		else if (buffer == CORNER_DIR_FB) PutStatusDir_DFL(CORNER_DIR_UD);
	}
	
    // Get mask for check if corners in given list of pieces are in solve conditions
	S64 c_Corners::GetMasksSolvedCorners(const std::vector<Corners>& p_list)
	{
		S64 c_mask = 0ull;
		
		for (auto P : p_list)
		{
			switch (P)
			{
				case Corners::UFR: c_mask |= CMASK_UFR; break;
				case Corners::UFL: c_mask |= CMASK_UFL; break;
				case Corners::UBL: c_mask |= CMASK_UBL; break;
				case Corners::UBR: c_mask |= CMASK_UBR; break;
				case Corners::DFR: c_mask |= CMASK_DFR; break;
				case Corners::DFL: c_mask |= CMASK_DFL; break;
				case Corners::DBL: c_mask |= CMASK_DBL; break;
				case Corners::DBR: c_mask |= CMASK_DBR; break;
				default: break;
			}
		}

		return c_mask;
	}
	
	// Check if the given corner is in the given layer
	bool c_Corners::IsCornerInLayer(const Corners P, const Layers L) const
	{
		switch (L)
		{
		case Layers::U: return IsCornerInLayerU(P);
		case Layers::D: return IsCornerInLayerD(P);
		case Layers::F: return IsCornerInLayerF(P);
		case Layers::B: return IsCornerInLayerB(P);
		case Layers::R: return IsCornerInLayerR(P);
		case Layers::L: return IsCornerInLayerL(P);
		default: return false;
		}
	}
}

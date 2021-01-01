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

#pragma once

#include <vector>

#include "cube_definitions.h"

namespace grcube3
{
	class c_Corners
	{
	public:
		c_Corners() { corners = CMASK_SOLVED; }
		~c_Corners() {}
	
		// Get corner piece in corner position
		Corners GetCornerPiece_UFR() const { return static_cast<Corners>(GetStatusPos_UFR()); }
		Corners GetCornerPiece_UFL() const { return static_cast<Corners>(GetStatusPos_UFL()); }
		Corners GetCornerPiece_UBL() const { return static_cast<Corners>(GetStatusPos_UBL()); }
		Corners GetCornerPiece_UBR() const { return static_cast<Corners>(GetStatusPos_UBR()); }
		Corners GetCornerPiece_DFR() const { return static_cast<Corners>(GetStatusPos_DFR()); }
		Corners GetCornerPiece_DFL() const { return static_cast<Corners>(GetStatusPos_DFL()); }
		Corners GetCornerPiece_DBL() const { return static_cast<Corners>(GetStatusPos_DBL()); }
		Corners GetCornerPiece_DBR() const { return static_cast<Corners>(GetStatusPos_DBR()); }
	
		// Get corner piece direction in corner position
		CornerDirections GetCornerDir_UFR() const { return static_cast<CornerDirections>(GetStatusDir_UFR()); }
		CornerDirections GetCornerDir_UFL() const { return static_cast<CornerDirections>(GetStatusDir_UFL()); }
		CornerDirections GetCornerDir_UBL() const { return static_cast<CornerDirections>(GetStatusDir_UBL()); }
		CornerDirections GetCornerDir_UBR() const { return static_cast<CornerDirections>(GetStatusDir_UBR()); }
		CornerDirections GetCornerDir_DFR() const { return static_cast<CornerDirections>(GetStatusDir_DFR()); }
		CornerDirections GetCornerDir_DFL() const { return static_cast<CornerDirections>(GetStatusDir_DFL()); }
		CornerDirections GetCornerDir_DBL() const { return static_cast<CornerDirections>(GetStatusDir_DBL()); }
		CornerDirections GetCornerDir_DBR() const { return static_cast<CornerDirections>(GetStatusDir_DBR()); }

		// Get current sticker for stickers positions
		Stickers GetSticker_UFR_U() const { return s_UFR_U[GetStatusPos_UFR()][GetStatusDir_UFR()]; }
		Stickers GetSticker_UFR_F() const { return s_UFR_F[GetStatusPos_UFR()][GetStatusDir_UFR()]; }
		Stickers GetSticker_UFR_R() const { return s_UFR_R[GetStatusPos_UFR()][GetStatusDir_UFR()]; }
		Stickers GetSticker_UFL_U() const { return s_UFL_U[GetStatusPos_UFL()][GetStatusDir_UFL()]; }
		Stickers GetSticker_UFL_F() const { return s_UFL_F[GetStatusPos_UFL()][GetStatusDir_UFL()]; }
		Stickers GetSticker_UFL_L() const { return s_UFL_L[GetStatusPos_UFL()][GetStatusDir_UFL()]; }
		Stickers GetSticker_UBL_U() const { return s_UBL_U[GetStatusPos_UBL()][GetStatusDir_UBL()]; }
		Stickers GetSticker_UBL_B() const { return s_UBL_B[GetStatusPos_UBL()][GetStatusDir_UBL()]; }
		Stickers GetSticker_UBL_L() const { return s_UBL_L[GetStatusPos_UBL()][GetStatusDir_UBL()]; }
		Stickers GetSticker_UBR_U() const { return s_UBR_U[GetStatusPos_UBR()][GetStatusDir_UBR()]; }
		Stickers GetSticker_UBR_B() const { return s_UBR_B[GetStatusPos_UBR()][GetStatusDir_UBR()]; }
		Stickers GetSticker_UBR_R() const { return s_UBR_R[GetStatusPos_UBR()][GetStatusDir_UBR()]; }
		
		Stickers GetSticker_DFR_D() const { return s_DFR_D[GetStatusPos_DFR()][GetStatusDir_DFR()]; }
		Stickers GetSticker_DFR_F() const { return s_DFR_F[GetStatusPos_DFR()][GetStatusDir_DFR()]; }
		Stickers GetSticker_DFR_R() const { return s_DFR_R[GetStatusPos_DFR()][GetStatusDir_DFR()]; }
		Stickers GetSticker_DFL_D() const { return s_DFL_D[GetStatusPos_DFL()][GetStatusDir_DFL()]; }
		Stickers GetSticker_DFL_F() const { return s_DFL_F[GetStatusPos_DFL()][GetStatusDir_DFL()]; }
		Stickers GetSticker_DFL_L() const { return s_DFL_L[GetStatusPos_DFL()][GetStatusDir_DFL()]; }
		Stickers GetSticker_DBL_D() const { return s_DBL_D[GetStatusPos_DBL()][GetStatusDir_DBL()]; }
		Stickers GetSticker_DBL_B() const { return s_DBL_B[GetStatusPos_DBL()][GetStatusDir_DBL()]; }
		Stickers GetSticker_DBL_L() const { return s_DBL_L[GetStatusPos_DBL()][GetStatusDir_DBL()]; }
		Stickers GetSticker_DBR_D() const { return s_DBR_D[GetStatusPos_DBR()][GetStatusDir_DBR()]; }
		Stickers GetSticker_DBR_B() const { return s_DBR_B[GetStatusPos_DBR()][GetStatusDir_DBR()]; }
		Stickers GetSticker_DBR_R() const { return s_DBR_R[GetStatusPos_DBR()][GetStatusDir_DBR()]; }
		
		// Get faces for stickers positions
		Faces GetFace_UFR_U() const { return f_UFR_U[GetStatusPos_UFR()][GetStatusDir_UFR()]; }
		Faces GetFace_UFR_F() const { return f_UFR_F[GetStatusPos_UFR()][GetStatusDir_UFR()]; }
		Faces GetFace_UFR_R() const { return f_UFR_R[GetStatusPos_UFR()][GetStatusDir_UFR()]; }
		Faces GetFace_UFL_U() const { return f_UFL_U[GetStatusPos_UFL()][GetStatusDir_UFL()]; }
		Faces GetFace_UFL_F() const { return f_UFL_F[GetStatusPos_UFL()][GetStatusDir_UFL()]; }
		Faces GetFace_UFL_L() const { return f_UFL_L[GetStatusPos_UFL()][GetStatusDir_UFL()]; }
		Faces GetFace_UBL_U() const { return f_UBL_U[GetStatusPos_UBL()][GetStatusDir_UBL()]; }
		Faces GetFace_UBL_B() const { return f_UBL_B[GetStatusPos_UBL()][GetStatusDir_UBL()]; }
		Faces GetFace_UBL_L() const { return f_UBL_L[GetStatusPos_UBL()][GetStatusDir_UBL()]; }
		Faces GetFace_UBR_U() const { return f_UBR_U[GetStatusPos_UBR()][GetStatusDir_UBR()]; }
		Faces GetFace_UBR_B() const { return f_UBR_B[GetStatusPos_UBR()][GetStatusDir_UBR()]; }
		Faces GetFace_UBR_R() const { return f_UBR_R[GetStatusPos_UBR()][GetStatusDir_UBR()]; }
		
		Faces GetFace_DFR_D() const { return f_DFR_D[GetStatusPos_DFR()][GetStatusDir_DFR()]; }
		Faces GetFace_DFR_F() const { return f_DFR_F[GetStatusPos_DFR()][GetStatusDir_DFR()]; }
		Faces GetFace_DFR_R() const { return f_DFR_R[GetStatusPos_DFR()][GetStatusDir_DFR()]; }
		Faces GetFace_DFL_D() const { return f_DFL_D[GetStatusPos_DFL()][GetStatusDir_DFL()]; }
		Faces GetFace_DFL_F() const { return f_DFL_F[GetStatusPos_DFL()][GetStatusDir_DFL()]; }
		Faces GetFace_DFL_L() const { return f_DFL_L[GetStatusPos_DFL()][GetStatusDir_DFL()]; }
		Faces GetFace_DBL_D() const { return f_DBL_D[GetStatusPos_DBL()][GetStatusDir_DBL()]; }
		Faces GetFace_DBL_B() const { return f_DBL_B[GetStatusPos_DBL()][GetStatusDir_DBL()]; }
		Faces GetFace_DBL_L() const { return f_DBL_L[GetStatusPos_DBL()][GetStatusDir_DBL()]; }
		Faces GetFace_DBR_D() const { return f_DBR_D[GetStatusPos_DBR()][GetStatusDir_DBR()]; }
		Faces GetFace_DBR_B() const { return f_DBR_B[GetStatusPos_DBR()][GetStatusDir_DBR()]; }
		Faces GetFace_DBR_R() const { return f_DBR_R[GetStatusPos_DBR()][GetStatusDir_DBR()]; }
		
        // Get mask for check if corners in given list of pieces are in solve conditions
		static S64 GetMasksSolvedCorners(const std::vector<Corners>&);
		
        // Check if corners coded in given mask are solved (default = all corners)
		bool IsSolvedCorners (const S64 CMask = CMASK_DATA) const { return (corners & CMask) == (CMASK_SOLVED & CMask); }

		// Check if a corner is solved
		bool IsSolved_UFR() const { return GetCornerPiece_UFR() == Corners::UFR && GetCornerDir_UFR() == CornerDirections::UD; }
		bool IsSolved_UFL() const { return GetCornerPiece_UFL() == Corners::UFL && GetCornerDir_UFL() == CornerDirections::UD; }
		bool IsSolved_UBL() const { return GetCornerPiece_UBL() == Corners::UBL && GetCornerDir_UBL() == CornerDirections::UD; }
		bool IsSolved_UBR() const { return GetCornerPiece_UBR() == Corners::UBR && GetCornerDir_UBR() == CornerDirections::UD; }
		bool IsSolved_DFR() const { return GetCornerPiece_DFR() == Corners::DFR && GetCornerDir_DFR() == CornerDirections::UD; }
		bool IsSolved_DFL() const { return GetCornerPiece_DFL() == Corners::DFL && GetCornerDir_DFL() == CornerDirections::UD; }
		bool IsSolved_DBL() const { return GetCornerPiece_DBL() == Corners::DBL && GetCornerDir_DBL() == CornerDirections::UD; }
		bool IsSolved_DBR() const { return GetCornerPiece_DBR() == Corners::DBR && GetCornerDir_DBR() == CornerDirections::UD; }
	
	protected:
		// General masks for corners
        static constexpr auto CMASK_DATA 	= 0x3737373737373737ULL;	// 0011_0111_0011_0111_0011_0111_0011_0111_0011_0111_0011_0111_0011_0111_0011_0111
		static constexpr auto CMASK_SOLVED  = 0x0706050403020100ULL;	// 0000_0111_0000_0110_0000_0101_0000_0100_0000_0011_0000_0010_0000_0001_0000_0000
		
		// Masks for corners position
		static constexpr auto CMASK_POS_UFR = 0x0000000000000007ULL;
		static constexpr auto CMASK_POS_UFL = 0x0000000000000700ULL;
		static constexpr auto CMASK_POS_UBL = 0x0000000000070000ULL;
		static constexpr auto CMASK_POS_UBR = 0x0000000007000000ULL;
		static constexpr auto CMASK_POS_DFR = 0x0000000700000000ULL;
		static constexpr auto CMASK_POS_DFL = 0x0000070000000000ULL;
		static constexpr auto CMASK_POS_DBL = 0x0007000000000000ULL;
		static constexpr auto CMASK_POS_DBR = 0x0700000000000000ULL;
		
		// Masks for corners direction
		static constexpr auto CMASK_DIR_UFR = 0x0000000000000030ULL;
		static constexpr auto CMASK_DIR_UFL = 0x0000000000003000ULL;
		static constexpr auto CMASK_DIR_UBL = 0x0000000000300000ULL;
		static constexpr auto CMASK_DIR_UBR = 0x0000000030000000ULL;
		static constexpr auto CMASK_DIR_DFR = 0x0000003000000000ULL;
		static constexpr auto CMASK_DIR_DFL = 0x0000300000000000ULL;
		static constexpr auto CMASK_DIR_DBL = 0x0030000000000000ULL;
		static constexpr auto CMASK_DIR_DBR = 0x3000000000000000ULL;
		
		// Masks for corners (position + direction)
		static constexpr auto CMASK_UFR = 0x0000000000000037ULL;
		static constexpr auto CMASK_UFL = 0x0000000000003700ULL;
		static constexpr auto CMASK_UBL = 0x0000000000370000ULL;
		static constexpr auto CMASK_UBR = 0x0000000037000000ULL;
		static constexpr auto CMASK_DFR = 0x0000003700000000ULL;
		static constexpr auto CMASK_DFL = 0x0000370000000000ULL;
		static constexpr auto CMASK_DBL = 0x0037000000000000ULL;
		static constexpr auto CMASK_DBR = 0x3700000000000000ULL;

		// Masks for layers (corners in layer)
		static constexpr auto CMASK_U = CMASK_UFR | CMASK_UFL | CMASK_UBL | CMASK_UBR;
		static constexpr auto CMASK_D = CMASK_DFR | CMASK_DFL | CMASK_DBL | CMASK_DBR;
		static constexpr auto CMASK_F = CMASK_UFR | CMASK_UFL | CMASK_DFR | CMASK_DFL;
		static constexpr auto CMASK_B = CMASK_UBL | CMASK_UBR | CMASK_DBL | CMASK_DBR;
		static constexpr auto CMASK_R = CMASK_UFR | CMASK_UBR | CMASK_DFR | CMASK_DBR;
		static constexpr auto CMASK_L = CMASK_UFL | CMASK_UBL | CMASK_DFL | CMASK_DBL;
		static constexpr auto CMASK_E = 0x0ULL;
		static constexpr auto CMASK_M = 0x0ULL;
		static constexpr auto CMASK_S = 0x0ULL;
		
		// Three possible directions for corners: UD, FB and RL
		static constexpr auto CORNER_DIR_UD = 0x0000000000000000ULL;
		static constexpr auto CORNER_DIR_FB = 0x0000000000000001ULL;
		static constexpr auto CORNER_DIR_RL = 0x0000000000000002ULL;
			
		S64 corners; // Corners status

		static const Faces f_UFR_U[8][3]; // Array to get the face (color) in the UFR_U sticker position
		static const Faces f_UFR_F[8][3]; // Array to get the face (color) in the UFR_F sticker position
		static const Faces f_UFR_R[8][3]; // Array to get the face (color) in the UFR_R sticker position
		static const Faces f_UFL_U[8][3]; // Array to get the face (color) in the UFL_U sticker position
		static const Faces f_UFL_F[8][3]; // Array to get the face (color) in the UFL_F sticker position
		static const Faces f_UFL_L[8][3]; // Array to get the face (color) in the UFL_L sticker position

		static constexpr auto f_UBR_U = f_UFL_U; // Array to get the face (color) in the UBR_U sticker position
		static constexpr auto f_UBR_B = f_UFL_F; // Array to get the face (color) in the UBR_B sticker position
		static constexpr auto f_UBR_R = f_UFL_L; // Array to get the face (color) in the UBR_R sticker position
		static constexpr auto f_UBL_U = f_UFR_U; // Array to get the face (color) in the UBL_U sticker position
		static constexpr auto f_UBL_B = f_UFR_F; // Array to get the face (color) in the UBL_B sticker position
		static constexpr auto f_UBL_L = f_UFR_R; // Array to get the face (color) in the UBL_L sticker position
		
		static constexpr auto f_DFR_D = f_UFL_U; // Array to get the face (color) in the DFR_D sticker position
		static constexpr auto f_DFR_F = f_UFL_F; // Array to get the face (color) in the DFR_F sticker position
		static constexpr auto f_DFR_R = f_UFL_L; // Array to get the face (color) in the DFR_R sticker position
		static constexpr auto f_DFL_D = f_UFR_U; // Array to get the face (color) in the DFL_D sticker position
		static constexpr auto f_DFL_F = f_UFR_F; // Array to get the face (color) in the DFL_F sticker position
		static constexpr auto f_DFL_L = f_UFR_R; // Array to get the face (color) in the DFL_L sticker position

		static constexpr auto f_DBR_D = f_UFR_U; // Array to get the face (color) in the DBR_D sticker position
		static constexpr auto f_DBR_B = f_UFR_F; // Array to get the face (color) in the DBR_B sticker position
		static constexpr auto f_DBR_R = f_UFR_R; // Array to get the face (color) in the DBR_R sticker position
		static constexpr auto f_DBL_D = f_UFL_U; // Array to get the face (color) in the DBL_D sticker position
		static constexpr auto f_DBL_B = f_UFL_F; // Array to get the face (color) in the DBL_B sticker position
		static constexpr auto f_DBL_L = f_UFL_L; // Array to get the face (color) in the DBL_L sticker position

		static const Stickers s_UFR_U[8][3]; // Array to get the sticker in the UFR_U sticker position
		static const Stickers s_UFR_F[8][3]; // Array to get the sticker in the UFR_F sticker position
		static const Stickers s_UFR_R[8][3]; // Array to get the sticker in the UFR_R sticker position
		static const Stickers s_UFL_U[8][3]; // Array to get the sticker in the UFL_U sticker position
		static const Stickers s_UFL_F[8][3]; // Array to get the sticker in the UFL_F sticker position
		static const Stickers s_UFL_L[8][3]; // Array to get the sticker in the UFL_L sticker position

		static constexpr auto s_UBR_U = s_UFL_U; // Array to get the sticker in the UBR_U sticker position
		static constexpr auto s_UBR_B = s_UFL_F; // Array to get the sticker in the UBR_B sticker position
		static constexpr auto s_UBR_R = s_UFL_L; // Array to get the sticker in the UBR_R sticker position
		static constexpr auto s_UBL_U = s_UFR_U; // Array to get the sticker in the UBL_U sticker position
		static constexpr auto s_UBL_B = s_UFR_F; // Array to get the sticker in the UBL_B sticker position
		static constexpr auto s_UBL_L = s_UFR_R; // Array to get the sticker in the UBL_L sticker position
		
		static constexpr auto s_DFR_D = s_UFL_U; // Array to get the sticker in the DFR_D sticker position
		static constexpr auto s_DFR_F = s_UFL_F; // Array to get the sticker in the DFR_F sticker position
		static constexpr auto s_DFR_R = s_UFL_L; // Array to get the sticker in the DFR_R sticker position
		static constexpr auto s_DFL_D = s_UFR_U; // Array to get the sticker in the DFL_D sticker position
		static constexpr auto s_DFL_F = s_UFR_F; // Array to get the sticker in the DFL_F sticker position
		static constexpr auto s_DFL_L = s_UFR_R; // Array to get the sticker in the DFL_L sticker position

		static constexpr auto s_DBR_D = s_UFR_U; // Array to get the sticker in the DBR_D sticker position
		static constexpr auto s_DBR_B = s_UFR_F; // Array to get the sticker in the DBR_B sticker position
		static constexpr auto s_DBR_R = s_UFR_R; // Array to get the sticker in the DBR_R sticker position
		static constexpr auto s_DBL_D = s_UFL_U; // Array to get the sticker in the DBL_D sticker position
		static constexpr auto s_DBL_B = s_UFL_F; // Array to get the sticker in the DBL_B sticker position
		static constexpr auto s_DBL_L = s_UFL_L; // Array to get the sticker in the DBL_L sticker position
		
		void c_Reset() { corners = CMASK_SOLVED; } // Reset corners status
	
		// Movements
		void c_U();		void c_U2();	void c_Up();
		void c_D();		void c_D2();	void c_Dp();
		void c_F();		void c_F2();	void c_Fp();
		void c_B();		void c_B2();	void c_Bp();
		void c_R();		void c_R2();	void c_Rp();
		void c_L();		void c_L2();	void c_Lp();
	
		// Get corners status bits (position + direction)
		S64 GetStatus_UFR() const { return (corners & CMASK_UFR); }
		S64 GetStatus_UFL() const { return (corners & CMASK_UFL) >> 8; }
		S64 GetStatus_UBL() const { return (corners & CMASK_UBL) >> 16; }
		S64 GetStatus_UBR() const { return (corners & CMASK_UBR) >> 24; }
		S64 GetStatus_DFR() const { return (corners & CMASK_DFR) >> 32; }
		S64 GetStatus_DFL() const { return (corners & CMASK_DFL) >> 40; }
		S64 GetStatus_DBL() const { return (corners & CMASK_DBL) >> 48; }
		S64 GetStatus_DBR() const { return (corners & CMASK_DBR) >> 56; }
	
		// Change corners status bits (position + direction)
		void PutStatus_UFR(const S64 S) { corners = (corners & ~CMASK_UFR) | S; }
		void PutStatus_UFL(const S64 S) { corners = (corners & ~CMASK_UFL) | (S << 8); }
		void PutStatus_UBL(const S64 S) { corners = (corners & ~CMASK_UBL) | (S << 16); }
		void PutStatus_UBR(const S64 S) { corners = (corners & ~CMASK_UBR) | (S << 24); }
		void PutStatus_DFR(const S64 S) { corners = (corners & ~CMASK_DFR) | (S << 32); }
		void PutStatus_DFL(const S64 S) { corners = (corners & ~CMASK_DFL) | (S << 40); }
		void PutStatus_DBL(const S64 S) { corners = (corners & ~CMASK_DBL) | (S << 48); }
		void PutStatus_DBR(const S64 S) { corners = (corners & ~CMASK_DBR) | (S << 56); }
	
		// Get corners status bits (position only)
		S64 GetStatusPos_UFR() const { return (corners & CMASK_POS_UFR); }
		S64 GetStatusPos_UFL() const { return (corners & CMASK_POS_UFL) >> 8; }
		S64 GetStatusPos_UBL() const { return (corners & CMASK_POS_UBL) >> 16; }
		S64 GetStatusPos_UBR() const { return (corners & CMASK_POS_UBR) >> 24; }
		S64 GetStatusPos_DFR() const { return (corners & CMASK_POS_DFR) >> 32; }
		S64 GetStatusPos_DFL() const { return (corners & CMASK_POS_DFL) >> 40; }
		S64 GetStatusPos_DBL() const { return (corners & CMASK_POS_DBL) >> 48; }
		S64 GetStatusPos_DBR() const { return (corners & CMASK_POS_DBR) >> 56; }
	
		// Get corners status bits (direction only)
		S64 GetStatusDir_UFR() const { return (corners & CMASK_DIR_UFR) >> 4; }
		S64 GetStatusDir_UFL() const { return (corners & CMASK_DIR_UFL) >> 12; }
		S64 GetStatusDir_UBL() const { return (corners & CMASK_DIR_UBL) >> 20; }
		S64 GetStatusDir_UBR() const { return (corners & CMASK_DIR_UBR) >> 28; }
		S64 GetStatusDir_DFR() const { return (corners & CMASK_DIR_DFR) >> 36; }
		S64 GetStatusDir_DFL() const { return (corners & CMASK_DIR_DFL) >> 44; }
		S64 GetStatusDir_DBL() const { return (corners & CMASK_DIR_DBL) >> 52; }
		S64 GetStatusDir_DBR() const { return (corners & CMASK_DIR_DBR) >> 60; }
	
		// Change corners status bits (direction only)
		void PutStatusDir_UFR(const S64 D) { corners = (corners & ~CMASK_DIR_UFR) | (D << 4); }
		void PutStatusDir_UFL(const S64 D) { corners = (corners & ~CMASK_DIR_UFL) | (D << 12); }
		void PutStatusDir_UBL(const S64 D) { corners = (corners & ~CMASK_DIR_UBL) | (D << 20); }
		void PutStatusDir_UBR(const S64 D) { corners = (corners & ~CMASK_DIR_UBR) | (D << 28); }
		void PutStatusDir_DFR(const S64 D) { corners = (corners & ~CMASK_DIR_DFR) | (D << 36); }
		void PutStatusDir_DFL(const S64 D) { corners = (corners & ~CMASK_DIR_DFL) | (D << 44); }
		void PutStatusDir_DBL(const S64 D) { corners = (corners & ~CMASK_DIR_DBL) | (D << 52); }
		void PutStatusDir_DBR(const S64 D) { corners = (corners & ~CMASK_DIR_DBR) | (D << 60); }

		// Check if the given corner is in the given layer
		bool IsCornerInLayerU(const Corners P) const { return (GetCornerPiece_UFR() == P || GetCornerPiece_UFL() == P || GetCornerPiece_UBR() == P || GetCornerPiece_UBL() == P); }
		bool IsCornerInLayerD(const Corners P) const { return (GetCornerPiece_DFR() == P || GetCornerPiece_DFL() == P || GetCornerPiece_DBR() == P || GetCornerPiece_DBL() == P); }
		bool IsCornerInLayerF(const Corners P) const { return (GetCornerPiece_UFR() == P || GetCornerPiece_UFL() == P || GetCornerPiece_DFR() == P || GetCornerPiece_DFL() == P); }
		bool IsCornerInLayerB(const Corners P) const { return (GetCornerPiece_UBR() == P || GetCornerPiece_UBL() == P || GetCornerPiece_DBR() == P || GetCornerPiece_DBL() == P); }
		bool IsCornerInLayerR(const Corners P) const { return (GetCornerPiece_UFR() == P || GetCornerPiece_UBR() == P || GetCornerPiece_DFR() == P || GetCornerPiece_DBR() == P); }
		bool IsCornerInLayerL(const Corners P) const { return (GetCornerPiece_UFL() == P || GetCornerPiece_UBL() == P || GetCornerPiece_DFL() == P || GetCornerPiece_DBL() == P); }
		bool IsCornerInLayer(const Corners, const Layers) const;
	};
}

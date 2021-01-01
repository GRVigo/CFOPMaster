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
	class c_Edges
	{
	public:
		c_Edges() { edges = EMASK_SOLVED; } // Constructor
		~c_Edges() {} // Destructor
	
		// Get piece in edge position
		Edges GetEdgePiece_FR() const { return static_cast<Edges>(GetStatusPos_FR()); }
		Edges GetEdgePiece_FL() const { return static_cast<Edges>(GetStatusPos_FL()); }
		Edges GetEdgePiece_BL() const { return static_cast<Edges>(GetStatusPos_BL()); }
		Edges GetEdgePiece_BR() const { return static_cast<Edges>(GetStatusPos_BR()); }
		Edges GetEdgePiece_UF() const { return static_cast<Edges>(GetStatusPos_UF()); }
		Edges GetEdgePiece_UL() const { return static_cast<Edges>(GetStatusPos_UL()); }
		Edges GetEdgePiece_UB() const { return static_cast<Edges>(GetStatusPos_UB()); }
		Edges GetEdgePiece_UR() const { return static_cast<Edges>(GetStatusPos_UR()); }
		Edges GetEdgePiece_DF() const { return static_cast<Edges>(GetStatusPos_DF()); }
		Edges GetEdgePiece_DL() const { return static_cast<Edges>(GetStatusPos_DL()); }
		Edges GetEdgePiece_DB() const { return static_cast<Edges>(GetStatusPos_DB()); }
		Edges GetEdgePiece_DR() const { return static_cast<Edges>(GetStatusPos_DR()); }
	
		// Get piece direction in edge position
		EdgeDirections GetEdgeDir_FR() const { return static_cast<EdgeDirections>(GetStatusDir_FR()); }
		EdgeDirections GetEdgeDir_FL() const { return static_cast<EdgeDirections>(GetStatusDir_FL()); }
		EdgeDirections GetEdgeDir_BL() const { return static_cast<EdgeDirections>(GetStatusDir_BL()); }
		EdgeDirections GetEdgeDir_BR() const { return static_cast<EdgeDirections>(GetStatusDir_BR()); }
		EdgeDirections GetEdgeDir_UF() const { return static_cast<EdgeDirections>(GetStatusDir_UF()); }
		EdgeDirections GetEdgeDir_UL() const { return static_cast<EdgeDirections>(GetStatusDir_UL()); }
		EdgeDirections GetEdgeDir_UB() const { return static_cast<EdgeDirections>(GetStatusDir_UB()); }
		EdgeDirections GetEdgeDir_UR() const { return static_cast<EdgeDirections>(GetStatusDir_UR()); }
		EdgeDirections GetEdgeDir_DF() const { return static_cast<EdgeDirections>(GetStatusDir_DF()); }
		EdgeDirections GetEdgeDir_DL() const { return static_cast<EdgeDirections>(GetStatusDir_DL()); }
		EdgeDirections GetEdgeDir_DB() const { return static_cast<EdgeDirections>(GetStatusDir_DB()); }
		EdgeDirections GetEdgeDir_DR() const { return static_cast<EdgeDirections>(GetStatusDir_DR()); }

		// Get current sticker for stickers positions
		Stickers GetSticker_FR_F() const { return s_FR_F[GetStatusPos_FR()][GetStatusDir_FR()]; }
		Stickers GetSticker_FR_R() const { return s_FR_R[GetStatusPos_FR()][GetStatusDir_FR()]; }
		Stickers GetSticker_FL_F() const { return s_FL_F[GetStatusPos_FL()][GetStatusDir_FL()]; }
		Stickers GetSticker_FL_L() const { return s_FL_L[GetStatusPos_FL()][GetStatusDir_FL()]; }
		Stickers GetSticker_BL_B() const { return s_BL_B[GetStatusPos_BL()][GetStatusDir_BL()]; }
		Stickers GetSticker_BL_L() const { return s_BL_L[GetStatusPos_BL()][GetStatusDir_BL()]; }
		Stickers GetSticker_BR_B() const { return s_BR_B[GetStatusPos_BR()][GetStatusDir_BR()]; }
		Stickers GetSticker_BR_R() const { return s_BR_R[GetStatusPos_BR()][GetStatusDir_BR()]; }
			
		Stickers GetSticker_UF_U() const { return s_UF_U[GetStatusPos_UF()][GetStatusDir_UF()]; }
		Stickers GetSticker_UF_F() const { return s_UF_F[GetStatusPos_UF()][GetStatusDir_UF()]; }
		Stickers GetSticker_UL_U() const { return s_UL_U[GetStatusPos_UL()][GetStatusDir_UL()]; }
		Stickers GetSticker_UL_L() const { return s_UL_L[GetStatusPos_UL()][GetStatusDir_UL()]; }
		Stickers GetSticker_UB_U() const { return s_UB_U[GetStatusPos_UB()][GetStatusDir_UB()]; }
		Stickers GetSticker_UB_B() const { return s_UB_B[GetStatusPos_UB()][GetStatusDir_UB()]; }
		Stickers GetSticker_UR_U() const { return s_UR_U[GetStatusPos_UR()][GetStatusDir_UR()]; }
		Stickers GetSticker_UR_R() const { return s_UR_R[GetStatusPos_UR()][GetStatusDir_UR()]; }
			
		Stickers GetSticker_DF_D() const { return s_DF_D[GetStatusPos_DF()][GetStatusDir_DF()]; }
		Stickers GetSticker_DF_F() const { return s_DF_F[GetStatusPos_DF()][GetStatusDir_DF()]; }
		Stickers GetSticker_DL_D() const { return s_DL_D[GetStatusPos_DL()][GetStatusDir_DL()]; }
		Stickers GetSticker_DL_L() const { return s_DL_L[GetStatusPos_DL()][GetStatusDir_DL()]; }
		Stickers GetSticker_DB_D() const { return s_DB_D[GetStatusPos_DB()][GetStatusDir_DB()]; }
		Stickers GetSticker_DB_B() const { return s_DB_B[GetStatusPos_DB()][GetStatusDir_DB()]; }
		Stickers GetSticker_DR_D() const { return s_DR_D[GetStatusPos_DR()][GetStatusDir_DR()]; }
		Stickers GetSticker_DR_R() const { return s_DR_R[GetStatusPos_DR()][GetStatusDir_DR()]; }
		
		// Get faces for stickers positions
		Faces GetFace_FR_F() const { return f_FR_F[GetStatusPos_FR()][GetStatusDir_FR()]; }
		Faces GetFace_FR_R() const { return f_FR_R[GetStatusPos_FR()][GetStatusDir_FR()]; }
		Faces GetFace_FL_F() const { return f_FL_F[GetStatusPos_FL()][GetStatusDir_FL()]; }
		Faces GetFace_FL_L() const { return f_FL_L[GetStatusPos_FL()][GetStatusDir_FL()]; }
		Faces GetFace_BL_B() const { return f_BL_B[GetStatusPos_BL()][GetStatusDir_BL()]; }
		Faces GetFace_BL_L() const { return f_BL_L[GetStatusPos_BL()][GetStatusDir_BL()]; }
		Faces GetFace_BR_B() const { return f_BR_B[GetStatusPos_BR()][GetStatusDir_BR()]; }
		Faces GetFace_BR_R() const { return f_BR_R[GetStatusPos_BR()][GetStatusDir_BR()]; }
			
		Faces GetFace_UF_U() const { return f_UF_U[GetStatusPos_UF()][GetStatusDir_UF()]; }
		Faces GetFace_UF_F() const { return f_UF_F[GetStatusPos_UF()][GetStatusDir_UF()]; }
		Faces GetFace_UL_U() const { return f_UL_U[GetStatusPos_UL()][GetStatusDir_UL()]; }
		Faces GetFace_UL_L() const { return f_UL_L[GetStatusPos_UL()][GetStatusDir_UL()]; }
		Faces GetFace_UB_U() const { return f_UB_U[GetStatusPos_UB()][GetStatusDir_UB()]; }
		Faces GetFace_UB_B() const { return f_UB_B[GetStatusPos_UB()][GetStatusDir_UB()]; }
		Faces GetFace_UR_U() const { return f_UR_U[GetStatusPos_UR()][GetStatusDir_UR()]; }
		Faces GetFace_UR_R() const { return f_UR_R[GetStatusPos_UR()][GetStatusDir_UR()]; }
			
		Faces GetFace_DF_D() const { return f_DF_D[GetStatusPos_DF()][GetStatusDir_DF()]; }
		Faces GetFace_DF_F() const { return f_DF_F[GetStatusPos_DF()][GetStatusDir_DF()]; }
		Faces GetFace_DL_D() const { return f_DL_D[GetStatusPos_DL()][GetStatusDir_DL()]; }
		Faces GetFace_DL_L() const { return f_DL_L[GetStatusPos_DL()][GetStatusDir_DL()]; }
		Faces GetFace_DB_D() const { return f_DB_D[GetStatusPos_DB()][GetStatusDir_DB()]; }
		Faces GetFace_DB_B() const { return f_DB_B[GetStatusPos_DB()][GetStatusDir_DB()]; }
		Faces GetFace_DR_D() const { return f_DR_D[GetStatusPos_DR()][GetStatusDir_DR()]; }
		Faces GetFace_DR_R() const { return f_DR_R[GetStatusPos_DR()][GetStatusDir_DR()]; }
		
        // Get mask for check if edges in given list of pieces are in solve conditions
        static S64 GetMasksSolvedEdges(const std::vector<Edges>&);
		
        // Check if edges coded in given mask are solved (default = all edges)
		bool IsSolvedEdges(const S64 EMask = EMASK_DATA) const { return (edges & EMask) == (EMASK_SOLVED & EMask); }

		// Check if an edge is solved
		bool IsSolved_FR() const { return GetEdgePiece_FR() == Edges::FR && GetEdgeDir_FR() == EdgeDirections::POS; }
		bool IsSolved_FL() const { return GetEdgePiece_FL() == Edges::FL && GetEdgeDir_FL() == EdgeDirections::POS; }
		bool IsSolved_BL() const { return GetEdgePiece_BL() == Edges::BL && GetEdgeDir_BL() == EdgeDirections::POS; }
		bool IsSolved_BR() const { return GetEdgePiece_BR() == Edges::BR && GetEdgeDir_BR() == EdgeDirections::POS; }
		bool IsSolved_UF() const { return GetEdgePiece_UF() == Edges::UF && GetEdgeDir_UF() == EdgeDirections::POS; }
		bool IsSolved_UL() const { return GetEdgePiece_UL() == Edges::UL && GetEdgeDir_UL() == EdgeDirections::POS; }
		bool IsSolved_UB() const { return GetEdgePiece_UB() == Edges::UB && GetEdgeDir_UB() == EdgeDirections::POS; }
		bool IsSolved_UR() const { return GetEdgePiece_UR() == Edges::UR && GetEdgeDir_UR() == EdgeDirections::POS; }
		bool IsSolved_DF() const { return GetEdgePiece_DF() == Edges::DF && GetEdgeDir_DF() == EdgeDirections::POS; }
		bool IsSolved_DL() const { return GetEdgePiece_DL() == Edges::DL && GetEdgeDir_DL() == EdgeDirections::POS; }
		bool IsSolved_DB() const { return GetEdgePiece_DB() == Edges::DB && GetEdgeDir_DB() == EdgeDirections::POS; }
		bool IsSolved_DR() const { return GetEdgePiece_DR() == Edges::DR && GetEdgeDir_DR() == EdgeDirections::POS; }

	protected:
		// General masks for edges
		static constexpr auto EMASK_DATA   = 0x0FFFFFFFFFFFFFFFULL;	// 0000_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111_1111
		static constexpr auto EMASK_SOLVED = 0x0000BA9876543210ULL;	// 0000_0000_0000_0000_1011_1010_1001_1000_0111_0110_0101_0100_0011_0010_0001_0000
		
		// Masks to get edges position
		static constexpr auto EMASK_POS_FR = 0x000000000000000FULL;
		static constexpr auto EMASK_POS_FL = 0x00000000000000F0ULL;
		static constexpr auto EMASK_POS_BL = 0x0000000000000F00ULL;
		static constexpr auto EMASK_POS_BR = 0x000000000000F000ULL;
		static constexpr auto EMASK_POS_UF = 0x00000000000F0000ULL;
		static constexpr auto EMASK_POS_UL = 0x0000000000F00000ULL;
		static constexpr auto EMASK_POS_UB = 0x000000000F000000ULL;
		static constexpr auto EMASK_POS_UR = 0x00000000F0000000ULL;
		static constexpr auto EMASK_POS_DF = 0x0000000F00000000ULL;
		static constexpr auto EMASK_POS_DL = 0x000000F000000000ULL;
		static constexpr auto EMASK_POS_DB = 0x00000F0000000000ULL;
		static constexpr auto EMASK_POS_DR = 0x0000F00000000000ULL;
		
		// Masks to get edges direction
		static constexpr auto EMASK_DIR_FR = 0x0001000000000000ULL;
		static constexpr auto EMASK_DIR_FL = 0x0002000000000000ULL;
		static constexpr auto EMASK_DIR_BL = 0x0004000000000000ULL;
		static constexpr auto EMASK_DIR_BR = 0x0008000000000000ULL;
		static constexpr auto EMASK_DIR_UF = 0x0010000000000000ULL;
		static constexpr auto EMASK_DIR_UL = 0x0020000000000000ULL;
		static constexpr auto EMASK_DIR_UB = 0x0040000000000000ULL;
		static constexpr auto EMASK_DIR_UR = 0x0080000000000000ULL;
		static constexpr auto EMASK_DIR_DF = 0x0100000000000000ULL;
		static constexpr auto EMASK_DIR_DL = 0x0200000000000000ULL;
		static constexpr auto EMASK_DIR_DB = 0x0400000000000000ULL;
		static constexpr auto EMASK_DIR_DR = 0x0800000000000000ULL;
		
		// Masks for edges (position + direction)
		static constexpr auto EMASK_FR = 0x000100000000000FULL;
		static constexpr auto EMASK_FL = 0x00020000000000F0ULL;
		static constexpr auto EMASK_BL = 0x0004000000000F00ULL;
		static constexpr auto EMASK_BR = 0x000800000000F000ULL;
		static constexpr auto EMASK_UF = 0x00100000000F0000ULL;
		static constexpr auto EMASK_UL = 0x0020000000F00000ULL;
		static constexpr auto EMASK_UB = 0x004000000F000000ULL;
		static constexpr auto EMASK_UR = 0x00800000F0000000ULL;
		static constexpr auto EMASK_DF = 0x0100000F00000000ULL;
		static constexpr auto EMASK_DL = 0x020000F000000000ULL;
		static constexpr auto EMASK_DB = 0x04000F0000000000ULL;
		static constexpr auto EMASK_DR = 0x0800F00000000000ULL;

		// Masks for layers (edges in layer)
		static constexpr auto EMASK_U = EMASK_UF | EMASK_UL | EMASK_UB | EMASK_UR;
		static constexpr auto EMASK_D = EMASK_DF | EMASK_DL | EMASK_DB | EMASK_DR;
		static constexpr auto EMASK_F = EMASK_FR | EMASK_FL | EMASK_UF | EMASK_DF;
		static constexpr auto EMASK_B = EMASK_BL | EMASK_BR | EMASK_UB | EMASK_DB;
		static constexpr auto EMASK_R = EMASK_FR | EMASK_BR | EMASK_UR | EMASK_DR;
		static constexpr auto EMASK_L = EMASK_FL | EMASK_BL | EMASK_UL | EMASK_DL;
		static constexpr auto EMASK_E = EMASK_FR | EMASK_FL | EMASK_BL | EMASK_BR;
		static constexpr auto EMASK_M = EMASK_UF | EMASK_DF | EMASK_DB | EMASK_UB;
		static constexpr auto EMASK_S = EMASK_UR | EMASK_DR | EMASK_DL | EMASK_UL;
		
		// Two possible directions for edges: positive and negative
		static constexpr auto EDGE_DIR_POS = 0x0000000000000000ULL;
		static constexpr auto EDGE_DIR_NEG = 0x0000000000000001ULL;

		S64 edges; // Edges status

		const static Faces f_FR_F[12][2]; // Array to get the face (color) in the FR_F sticker position
		const static Faces f_FR_R[12][2]; // Array to get the face (color) in the FR_R sticker position
				
		static constexpr auto f_FL_F = f_FR_F; // Array to get the face (color) in the FL_F sticker position
		static constexpr auto f_FL_L = f_FR_R; // Array to get the face (color) in the FL_L sticker position
		static constexpr auto f_BL_B = f_FR_F; // Array to get the face (color) in the BL_B sticker position
		static constexpr auto f_BL_L = f_FR_R; // Array to get the face (color) in the BL_L sticker position
		static constexpr auto f_BR_B = f_FR_F; // Array to get the face (color) in the BR_B sticker position
		static constexpr auto f_BR_R = f_FR_R; // Array to get the face (color) in the BR_R sticker position
		
		static constexpr auto f_UF_U = f_FR_F; // Array to get the face (color) in the UF_U sticker position
		static constexpr auto f_UF_F = f_FR_R; // Array to get the face (color) in the UF_F sticker position
		static constexpr auto f_UL_U = f_FR_F; // Array to get the face (color) in the UL_U sticker position
		static constexpr auto f_UL_L = f_FR_R; // Array to get the face (color) in the UL_L sticker position
		static constexpr auto f_UB_U = f_FR_F; // Array to get the face (color) in the UB_U sticker position
		static constexpr auto f_UB_B = f_FR_R; // Array to get the face (color) in the UB_B sticker position
		static constexpr auto f_UR_U = f_FR_F; // Array to get the face (color) in the UR_U sticker position
		static constexpr auto f_UR_R = f_FR_R; // Array to get the face (color) in the UR_R sticker position
		
		static constexpr auto f_DF_D = f_FR_F; // Array to get the face (color) in the DF_D sticker position
		static constexpr auto f_DF_F = f_FR_R; // Array to get the face (color) in the DF_F sticker position
		static constexpr auto f_DL_D = f_FR_F; // Array to get the face (color) in the DL_D sticker position
		static constexpr auto f_DL_L = f_FR_R; // Array to get the face (color) in the DL_L sticker position
		static constexpr auto f_DB_D = f_FR_F; // Array to get the face (color) in the DB_D sticker position
		static constexpr auto f_DB_B = f_FR_R; // Array to get the face (color) in the DB_B sticker position
		static constexpr auto f_DR_D = f_FR_F; // Array to get the face (color) in the DR_D sticker position
		static constexpr auto f_DR_R = f_FR_R; // Array to get the face (color) in the DR_R sticker position
		
		const static Stickers s_FR_F[12][2]; // Array to get the sticker in the FR_F sticker position
		const static Stickers s_FR_R[12][2]; // Array to get the sticker in the FR_R sticker position

		static constexpr auto s_FL_F = s_FR_F; // Array to get the sticker in the FL_F sticker position
		static constexpr auto s_FL_L = s_FR_R; // Array to get the sticker in the FL_L sticker position
		static constexpr auto s_BL_B = s_FR_F; // Array to get the sticker in the BL_B sticker position
		static constexpr auto s_BL_L = s_FR_R; // Array to get the sticker in the BL_L sticker position
		static constexpr auto s_BR_B = s_FR_F; // Array to get the sticker in the BR_B sticker position
		static constexpr auto s_BR_R = s_FR_R; // Array to get the sticker in the BR_R sticker position
		
		static constexpr auto s_UF_U = s_FR_F; // Array to get the sticker in the UF_U sticker position
		static constexpr auto s_UF_F = s_FR_R; // Array to get the sticker in the UF_F sticker position
		static constexpr auto s_UL_U = s_FR_F; // Array to get the sticker in the UL_U sticker position
		static constexpr auto s_UL_L = s_FR_R; // Array to get the sticker in the UL_L sticker position
		static constexpr auto s_UB_U = s_FR_F; // Array to get the sticker in the UB_U sticker position
		static constexpr auto s_UB_B = s_FR_R; // Array to get the sticker in the UB_B sticker position
		static constexpr auto s_UR_U = s_FR_F; // Array to get the sticker in the UR_U sticker position
		static constexpr auto s_UR_R = s_FR_R; // Array to get the sticker in the UR_R sticker position
		
		static constexpr auto s_DF_D = s_FR_F; // Array to get the sticker in the DF_D sticker position
		static constexpr auto s_DF_F = s_FR_R; // Array to get the sticker in the DF_F sticker position
		static constexpr auto s_DL_D = s_FR_F; // Array to get the sticker in the DL_D sticker position
		static constexpr auto s_DL_L = s_FR_R; // Array to get the sticker in the DL_L sticker position
		static constexpr auto s_DB_D = s_FR_F; // Array to get the sticker in the DB_D sticker position
		static constexpr auto s_DB_B = s_FR_R; // Array to get the sticker in the DB_B sticker position
		static constexpr auto s_DR_D = s_FR_F; // Array to get the sticker in the DR_D sticker position
		static constexpr auto s_DR_R = s_FR_R; // Array to get the sticker in the DR_R sticker position	
	
		void e_Reset() { edges = EMASK_SOLVED; } // Reset edges status
	
		// Movements
		void e_U();		void e_U2();	void e_Up();
		void e_D();		void e_D2();	void e_Dp();
		void e_F();		void e_F2();	void e_Fp();
		void e_B();		void e_B2();	void e_Bp();
		void e_R();		void e_R2();	void e_Rp();
		void e_L();		void e_L2();	void e_Lp();
	
		// Change edges status bits (position only)
		void PutStatusPos_FR(const S64 P) { edges = (edges & ~EMASK_POS_FR) | P; }
		void PutStatusPos_FL(const S64 P) { edges = (edges & ~EMASK_POS_FL) | (P << 4); }
		void PutStatusPos_BL(const S64 P) { edges = (edges & ~EMASK_POS_BL) | (P << 8); }
		void PutStatusPos_BR(const S64 P) { edges = (edges & ~EMASK_POS_BR) | (P << 12); }
		void PutStatusPos_UF(const S64 P) { edges = (edges & ~EMASK_POS_UF) | (P << 16); }
		void PutStatusPos_UL(const S64 P) { edges = (edges & ~EMASK_POS_UL) | (P << 20); }
		void PutStatusPos_UB(const S64 P) { edges = (edges & ~EMASK_POS_UB) | (P << 24); }
		void PutStatusPos_UR(const S64 P) { edges = (edges & ~EMASK_POS_UR) | (P << 28); }
		void PutStatusPos_DF(const S64 P) { edges = (edges & ~EMASK_POS_DF) | (P << 32); }
		void PutStatusPos_DL(const S64 P) { edges = (edges & ~EMASK_POS_DL) | (P << 36); }
		void PutStatusPos_DB(const S64 P) { edges = (edges & ~EMASK_POS_DB) | (P << 40); }
		void PutStatusPos_DR(const S64 P) { edges = (edges & ~EMASK_POS_DR) | (P << 44); }
	
		// Change edges status bits (direction only)
		void PutStatusDir_FR(const S64 D) { edges = (edges & ~EMASK_DIR_FR) | (D << 48); }
		void PutStatusDir_FL(const S64 D) { edges = (edges & ~EMASK_DIR_FL) | (D << 49); }
		void PutStatusDir_BL(const S64 D) { edges = (edges & ~EMASK_DIR_BL) | (D << 50); }
		void PutStatusDir_BR(const S64 D) { edges = (edges & ~EMASK_DIR_BR) | (D << 51); }
		void PutStatusDir_UF(const S64 D) { edges = (edges & ~EMASK_DIR_UF) | (D << 52); }
		void PutStatusDir_UL(const S64 D) { edges = (edges & ~EMASK_DIR_UL) | (D << 53); }
		void PutStatusDir_UB(const S64 D) { edges = (edges & ~EMASK_DIR_UB) | (D << 54); }
		void PutStatusDir_UR(const S64 D) { edges = (edges & ~EMASK_DIR_UR) | (D << 55); }
		void PutStatusDir_DF(const S64 D) { edges = (edges & ~EMASK_DIR_DF) | (D << 56); }
		void PutStatusDir_DL(const S64 D) { edges = (edges & ~EMASK_DIR_DL) | (D << 57); }
		void PutStatusDir_DB(const S64 D) { edges = (edges & ~EMASK_DIR_DB) | (D << 58); }
		void PutStatusDir_DR(const S64 D) { edges = (edges & ~EMASK_DIR_DR) | (D << 59); }
		
		// Get edges status bits (positions only)
		S64 GetStatusPos_FR() const { return (edges & EMASK_POS_FR); }
		S64 GetStatusPos_FL() const { return (edges & EMASK_POS_FL) >> 4; }
		S64 GetStatusPos_BL() const { return (edges & EMASK_POS_BL) >> 8; }
		S64 GetStatusPos_BR() const { return (edges & EMASK_POS_BR) >> 12; }
		S64 GetStatusPos_UF() const { return (edges & EMASK_POS_UF) >> 16; }
		S64 GetStatusPos_UL() const { return (edges & EMASK_POS_UL) >> 20; }
		S64 GetStatusPos_UB() const { return (edges & EMASK_POS_UB) >> 24; }
		S64 GetStatusPos_UR() const { return (edges & EMASK_POS_UR) >> 28; }
		S64 GetStatusPos_DF() const { return (edges & EMASK_POS_DF) >> 32; }
		S64 GetStatusPos_DL() const { return (edges & EMASK_POS_DL) >> 36; }
		S64 GetStatusPos_DB() const { return (edges & EMASK_POS_DB) >> 40; }
		S64 GetStatusPos_DR() const { return (edges & EMASK_POS_DR) >> 44; }
		
		// Get edges status bits (directions only)
		S64 GetStatusDir_FR() const { return (edges & EMASK_DIR_FR) >> 48; }
		S64 GetStatusDir_FL() const { return (edges & EMASK_DIR_FL) >> 49; }
		S64 GetStatusDir_BL() const { return (edges & EMASK_DIR_BL) >> 50; }
		S64 GetStatusDir_BR() const { return (edges & EMASK_DIR_BR) >> 51; }
		S64 GetStatusDir_UF() const { return (edges & EMASK_DIR_UF) >> 52; }
		S64 GetStatusDir_UL() const { return (edges & EMASK_DIR_UL) >> 53; }
		S64 GetStatusDir_UB() const { return (edges & EMASK_DIR_UB) >> 54; }
		S64 GetStatusDir_UR() const { return (edges & EMASK_DIR_UR) >> 55; }
		S64 GetStatusDir_DF() const { return (edges & EMASK_DIR_DF) >> 56; }
		S64 GetStatusDir_DL() const { return (edges & EMASK_DIR_DL) >> 57; }
		S64 GetStatusDir_DB() const { return (edges & EMASK_DIR_DB) >> 58; }
		S64 GetStatusDir_DR() const { return (edges & EMASK_DIR_DR) >> 59; }
	
		// Invert edges direction status bit
		void InvertStatusDir_FR() { edges = edges & EMASK_DIR_FR ? edges & ~EMASK_DIR_FR : edges | EMASK_DIR_FR; }
		void InvertStatusDir_FL() { edges = edges & EMASK_DIR_FL ? edges & ~EMASK_DIR_FL : edges | EMASK_DIR_FL; }
		void InvertStatusDir_BL() { edges = edges & EMASK_DIR_BL ? edges & ~EMASK_DIR_BL : edges | EMASK_DIR_BL; }
		void InvertStatusDir_BR() { edges = edges & EMASK_DIR_BR ? edges & ~EMASK_DIR_BR : edges | EMASK_DIR_BR; }
		void InvertStatusDir_UF() { edges = edges & EMASK_DIR_UF ? edges & ~EMASK_DIR_UF : edges | EMASK_DIR_UF; }
		void InvertStatusDir_UL() { edges = edges & EMASK_DIR_UL ? edges & ~EMASK_DIR_UL : edges | EMASK_DIR_UL; }
		void InvertStatusDir_UB() { edges = edges & EMASK_DIR_UB ? edges & ~EMASK_DIR_UB : edges | EMASK_DIR_UB; }
		void InvertStatusDir_UR() { edges = edges & EMASK_DIR_UR ? edges & ~EMASK_DIR_UR : edges | EMASK_DIR_UR; }
		void InvertStatusDir_DF() { edges = edges & EMASK_DIR_DF ? edges & ~EMASK_DIR_DF : edges | EMASK_DIR_DF; }
		void InvertStatusDir_DL() { edges = edges & EMASK_DIR_DL ? edges & ~EMASK_DIR_DL : edges | EMASK_DIR_DL; }
		void InvertStatusDir_DB() { edges = edges & EMASK_DIR_DB ? edges & ~EMASK_DIR_DB : edges | EMASK_DIR_DB; }
		void InvertStatusDir_DR() { edges = edges & EMASK_DIR_DR ? edges & ~EMASK_DIR_DR : edges | EMASK_DIR_DR; }

		// Check if the given edge is in the given layer
		bool IsEdgeInLayerU(const Edges P) const { return (GetEdgePiece_UF() == P || GetEdgePiece_UB() == P || GetEdgePiece_UR() == P || GetEdgePiece_UL() == P); }
		bool IsEdgeInLayerD(const Edges P) const { return (GetEdgePiece_DF() == P || GetEdgePiece_DB() == P || GetEdgePiece_DR() == P || GetEdgePiece_DL() == P); }
		bool IsEdgeInLayerF(const Edges P) const { return (GetEdgePiece_UF() == P || GetEdgePiece_DF() == P || GetEdgePiece_FR() == P || GetEdgePiece_FL() == P); }
		bool IsEdgeInLayerB(const Edges P) const { return (GetEdgePiece_UB() == P || GetEdgePiece_DB() == P || GetEdgePiece_BR() == P || GetEdgePiece_BL() == P); }
		bool IsEdgeInLayerR(const Edges P) const { return (GetEdgePiece_UR() == P || GetEdgePiece_DR() == P || GetEdgePiece_FR() == P || GetEdgePiece_BR() == P); }
		bool IsEdgeInLayerL(const Edges P) const { return (GetEdgePiece_UL() == P || GetEdgePiece_DL() == P || GetEdgePiece_FL() == P || GetEdgePiece_BL() == P); }
		bool IsEdgeInLayerE(const Edges P) const { return (GetEdgePiece_FR() == P || GetEdgePiece_FL() == P || GetEdgePiece_BR() == P || GetEdgePiece_BL() == P); }
		bool IsEdgeInLayerM(const Edges P) const { return (GetEdgePiece_UF() == P || GetEdgePiece_UB() == P || GetEdgePiece_DF() == P || GetEdgePiece_DB() == P); }
		bool IsEdgeInLayerS(const Edges P) const { return (GetEdgePiece_UR() == P || GetEdgePiece_UL() == P || GetEdgePiece_DR() == P || GetEdgePiece_DL() == P); }
		bool IsEdgeInLayer(const Edges, const Layers) const;
	};
}

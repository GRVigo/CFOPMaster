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

#include <cstdint>

namespace grcube3
{
	// Type definitions
	
	using S64 = std::uint64_t; // 64 bits status
	using M16 = std::uint16_t; // 16 bits masks
	using uint = unsigned int;
	
	// Enumerators
	
	enum class Spins // All cube possible spins as faces oriented to up and front
	{ 
		UF, UR, UB, UL,
		DF, DR, DB, DL,
		FU, FR, FD, FL,
		BU, BR, BD, BL,
		RU, RF, RD, RB,
		LU, LF, LD, LB,
		Default = UF
	};
	
	// Centers from 0 to 5
	// Edges from 6 to 17 [First_Edge + (4 bits)]: FR 0000 - FL 0001 - BL 0010 - BR 0011 - UF 0100 - UL 0101 - UB 0110 - UR 0111 - DF 1000 - DL 1001 - DB 1010 - DR 1011
	// Corners from 18 to 23 [First_Corner + (3 bits)]: UFR 000 - UFL 001 - UBL 010 - UBR 011 - DFR 100 - DFL 101 - DBL 110 - DBR 111
	enum class Pieces // Rubik's cube all pieces
	{ 
		U, D, F, B, R, L, 
		FR, FL, BL, BR, UF, UL, UB, UR, DF, DL, DB, DR,
		UFR, UFL, UBL, UBR, DFR, DFL, DBL, DBR,
		First = U, Last = DBR,
		First_Center = U, First_Edge = FR, First_Corner = UFR
	};

	enum class PiecePositions // Rubik's cube all piece positions
	{
		U, D, F, B, R, L,
		FR, FL, BL, BR, UF, UL, UB, UR, DF, DL, DB, DR,
		UFR, UFL, UBL, UBR, DFR, DFL, DBL, DBR,
		First = U, Last = DBR,
		First_Center = U, First_Edge = FR, First_Corner = UFR
	};

	// Directions for edges:
	// 'E' layer edge in layer 'E': -EDGE_POS- if F/B sticker is in FB direction / -EDGE_NEG- if F/B sticker is in RL direction
	// 'E' layer edge in layer 'U/D': -EDGE_POS- if F/B sticker is in UD direction / -EDGE_NEG- if F/B sticker is in FB/RL directions
	// 'U/D' layer edge in layer 'E': -EDGE_POS- if U/D sticker is in FB direction / -EDGE_NEG- if U/D sticker is in RL direction
	// 'U/D' layer edge in layer 'U/D': -EDGE_POS- if U/D sticker is in UD direction / -EDGE_NEG- if U/D sticker is in FB/RL directions
	// Directions for corners:
	// U/D sticker direction: UD -> CORNER_UD / FB -> CORNER_FB / RL -> CORNER_RL
	enum class PieceDirections // All possible directions for pieces
	{ 
		NONE, // Centers don't need direction
		POS, NEG, // Edges direction (positive / negative)
		UD, FB, RL, // Corners direction (UD, FB or RL direction for U/D sticker)
		First_Edge = POS, First_Corner = UD
	};

	enum class Centers // Rubik's cube center pieces
	{
		U, D, F, B, R, L
	};

	enum class CenterPositions // Rubik's cube center piece positions
	{
		U, D, F, B, R, L
	};

	enum class CenterDirections // Rubik's cube center piece directions
	{
		NONE // Centers don't need direction
	};

	enum class Edges // Rubik's cube edges pieces
	{
		FR, FL, BL, BR, UF, UL, UB, UR, DF, DL, DB, DR
	};

	enum class EdgePositions // Rubik's cube edge positions
	{
		FR, FL, BL, BR, UF, UL, UB, UR, DF, DL, DB, DR
	};

	// 'E' layer edge in layer 'E': -EDGE_POS- if F/B sticker is in FB direction / -EDGE_NEG- if F/B sticker is in RL direction
	// 'E' layer edge in layer 'U/D': -EDGE_POS- if F/B sticker is in UD direction / -EDGE_NEG- if F/B sticker is in FB/RL directions
	// 'U/D' layer edge in layer 'E': -EDGE_POS- if U/D sticker is in FB direction / -EDGE_NEG- if U/D sticker is in RL direction
	// 'U/D' layer edge in layer 'U/D': -EDGE_POS- if U/D sticker is in UD direction / -EDGE_NEG- if U/D sticker is in FB/RL directions
	enum class EdgeDirections // Rubik's cube edge piece directions
	{
		POS, NEG // Edges direction (positive / negative)
	};

	enum class Corners // Rubik's cube corner pieces
	{
		UFR, UFL, UBL, UBR, DFR, DFL, DBL, DBR
	};

	enum class CornerPositions // Rubik's cube corner positions
	{
		UFR, UFL, UBL, UBR, DFR, DFL, DBL, DBR
	};

	// U/D sticker direction: UD -> CORNER_UD / FB -> CORNER_FB / RL -> CORNER_RL
	enum class CornerDirections // Rubik's cube corner piece directions
	{
		UD, FB, RL // Corners direction (UD, FB or RL direction for U/D sticker)
	};

	enum class PiecesTypes { CENTER, EDGE, CORNER }; // Rubik's cube pieces types
	
	enum class Stickers // Rubik's cube all stickers
	{ 
		U, D, F, B, R, L,  // Centers
		// Edges
		FR_F, FR_R, FL_F, FL_L, BL_B, BL_L, BR_B, BR_R, // Middle layer
		UF_U, UF_F, UL_U, UL_L, UB_U, UB_B, UR_U, UR_R, // Upper layer
		DF_D, DF_F, DL_D, DL_L, DB_D, DB_B, DR_D, DR_R, // Lower layer
		// Corners
		UFR_U, UFR_F, UFR_R, UFL_U, UFL_F, UFL_L, // Upper layer
		UBL_U, UBL_B, UBL_L, UBR_U, UBR_B, UBR_R, // Upper layer
		DFR_D, DFR_F, DFR_R, DFL_D, DFL_F, DFL_L, // Lower layer
		DBL_D, DBL_B, DBL_L, DBR_D, DBR_B, DBR_R, // Lower layer
		First = U, Last = DBR_R,
		First_Center = U, First_Edge = FR_F, First_Corner = UFR_U
	};

	enum class StickerPositions // Rubik's cube all sticker positions
	{
		U, D, F, B, R, L,  // Centers
		// Edges
		FR_F, FR_R, FL_F, FL_L, BL_B, BL_L, BR_B, BR_R, // Middle layer
		UF_U, UF_F, UL_U, UL_L, UB_U, UB_B, UR_U, UR_R, // Upper layer
		DF_D, DF_F, DL_D, DL_L, DB_D, DB_B, DR_D, DR_R, // Lower layer
		// Corners
		UFR_U, UFR_F, UFR_R, UFL_U, UFL_F, UFL_L, // Upper layer
		UBL_U, UBL_B, UBL_L, UBR_U, UBR_B, UBR_R, // Upper layer
		DFR_D, DFR_F, DFR_R, DFL_D, DFL_F, DFL_L, // Lower layer
		DBL_D, DBL_B, DBL_L, DBR_D, DBR_B, DBR_R, // Lower layer
		First = U, Last = DBR_R,
		First_Center = U, First_Edge = FR_F, First_Corner = UFR_U
	};
	
	enum class Faces // Rubik's cube faces
	{ 
		U, D, F, B, R, L
	};
	
	enum class Layers // Rubik's cube layers
	{ 
		NONE, U, D, F, B, R, L, E, S, M
	};
	
	enum class Steps // All possible movements
	{ 
		NONE, // No movement
	
		// Single layer movements
		U, Up, U2,
		D, Dp, D2,
		F, Fp, F2,
		B, Bp, B2,
		R, Rp, R2,
		L, Lp, L2,
	
		// Double layer movements
		u, up, u2,
		d, dp, d2,
		f, fp, f2,
		b, bp, b2,
		r, rp, r2,
		l, lp, l2,
	
		// Middle layer movements
		E, Ep, E2,
		S, Sp, S2,
		M, Mp, M2,
	
		// Full cube turns
		x, xp, x2,
		y, yp, y2,
		z, zp, z2,
	
		// Parentheses
		PARENTHESIS_OPEN, 			// Open parenthesis
		PARENTHESIS_CLOSE_1_REP, 	// Close parenthesis
		PARENTHESIS_CLOSE_2_REP, 	// Close parenthesis with two repetitions
		PARENTHESIS_CLOSE_3_REP, 	// Close parenthesis with three repetitions
		PARENTHESIS_CLOSE_4_REP, 	// Close parenthesis with four repetitions
		PARENTHESIS_CLOSE_5_REP, 	// Close parenthesis with five repetitions
		PARENTHESIS_CLOSE_6_REP, 	// Close parenthesis with six repetitions
		PARENTHESIS_CLOSE_7_REP, 	// Close parenthesis with seven repetitions
		PARENTHESIS_CLOSE_8_REP, 	// Close parenthesis with eight repetitions
		PARENTHESIS_CLOSE_9_REP 	// Close parenthesis with nine repetitions
	};
	
	enum class Ranges // All possible ranges (types) for movements (steps)
	{ 
		NONE, 		// No movement
		SINGLE, 	// Single external layer (U, D, F, B, R, L)
		DOUBLE, 	// Double layer (u, d, f, b, r, l)
		INTERNAL, 	// Single internal layer (E, S, M)
		TURN, 		// Turn (x, y, z)
		PARENTHESES	// Parentheses
	};
	
	//  Groups of pieces for search
	enum class PiecesGroups 
	{
		// CFOP method
		C_U, C_D, C_F, C_B, C_R, C_L, // Crosses - four edges in the layer
		F2L_U_UFR, F2L_U_UFL, F2L_U_UBR, F2L_U_UBL, // First two layers pieces starting with U cross
		F2L_D_DFR, F2L_D_DFL, F2L_D_DBR, F2L_D_DBL, // First two layers pieces starting with D cross
		F2L_F_UFR, F2L_F_UFL, F2L_F_DFR, F2L_F_DFL, // First two layers pieces starting with F cross
		F2L_B_UBR, F2L_B_UBL, F2L_B_DBR, F2L_B_DBL, // First two layers pieces starting with B cross
		F2L_R_UFR, F2L_R_UBR, F2L_R_DFR, F2L_R_DBR, // First two layers pieces starting with R cross
		F2L_L_UFL, F2L_L_UBL, F2L_L_DFL, F2L_L_DBL, // First two layers pieces starting with L cross
		LL_U, LL_D, LL_F, LL_B, LL_R, LL_L, // Last layer (for OLL & PLL)
	};
	
	// Groups of steps for search
	enum class SearchSteps
	{
		NONE,
		SINGLE_ALL, // U, U', U2, ..., L', L2
		SINGLE_U, SINGLE_D, SINGLE_F, SINGLE_B, SINGLE_R, SINGLE_L, // Single movements in given layer 
		SINGLE_U_NONE, SINGLE_D_NONE, SINGLE_F_NONE, SINGLE_B_NONE, SINGLE_R_NONE, SINGLE_L_NONE, // Single movements in given layer + no movement
		LATERAL_UD, LATERAL_FB, LATERAL_RL // Lateral movements, only 90 degrees both directions
	};
	
	// Check or no check the solve in current level
	enum class SearchCheck { CHECK, NO_CHECK };

	// Search actions for each level
	enum class SearchActions
	{
		STEPS_LIST, // Apply Steps list in current level
		OPPOSITE_STEP_2_PREVIOUS // Opposite movement from two levels before
	};

	// Search evaluation policies
	enum class SearchPolicies
	{
		BEST_SOLVES, // Maximum amount of pieces solved
		SHORT // Minimum amount of steps
	};

	// OLL cases
	enum class OLL
	{
		SKIP, // OLL skip
		OCLL1, OCLL2, OCLL3, OCLL4, OCLL5, OCLL6, OCLL7, // All edges oriented correctly
		T1, T2, // T shapes
		S1, S2,	// Squares
		C1, C2, // C shapes
		W1, W2, // W shapes
		E1, E2, // Corners correct, edges flipped
		P1, P2, P3, P4, // P shapes
		I1, I2, I3, I4, // I shapes
		F1, F2, F3, F4, // Fish shapes
		K1, K2, K3, K4, // Knight move shapes
		A1, A2, A3, A4, // Awkward shapes
		L1, L2, L3, L4, L5, L6, // L shapes
		B1, B2, B3, B4, B5, B6, // Lightning bolts
        O1, O2, O3, O4, O5, O6, O7, O8 // No edges flipped correctly
	};
	
	// PLL cases
	enum class PLL
	{
		SKIP, // PLL skip
		Ua, Ub, Z, H, // Permutations of edges only
		Aa, Ab, E, // Permutations of corners only
		Ra, Rb, Ja, Jb, T, F, // Swap one set of adjacent corners
		V, Y, Na, Nb, // Swap one set of diagonal corners
		Ga, Gb, Gc, Gd // G permutations (double cycles)
	};
}

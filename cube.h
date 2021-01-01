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

#include "cube_definitions.h"
#include "edges.h"
#include "corners.h"
#include "algorithm.h"

namespace grcube3
{
	// 3x3x3 Rubik's cube class
	class Cube: public c_Edges, public c_Corners
	{
	public:
        // Default constructor
        Cube() { spin = Spins::Default; } // UF

        // Algorithm constructor (develop algorithm parentheses)
        Cube(Algorithm& A)
		{ 
			spin = Spins::Default;
            if (!ApplyAlgorithm(A))
            { // Algorithm have parentheses with more than one repetition, must be developed
                Algorithm Aux = A.GetDeveloped(false);
                ApplyAlgorithm(Aux);
            }
		}
		
        // Get corners status
        S64 GetCornersStatus() const { return corners; }

        // Get edges status
        S64 GetEdgesStatus() const { return edges; }

        // Get cube spin
        Spins GetSpin() const { return spin; }

        // Get cube spin as text
        std::string GetSpinText() const { return sp_strings[static_cast<int>(spin)]; }

        // Get a given cube spin as text
        static std::string GetSpinText(Spins s) { return sp_strings[static_cast<int>(s)]; }

        // Get steps to pass from a start spin to a final spin
        static void GetSpinsSteps(const Spins sS, const Spins sF, Steps &s1, Steps &s2) 
        { 
            s1 = s_Turns[static_cast<int>(sS)][static_cast<int>(sF)][0]; 
            s2 = s_Turns[static_cast<int>(sS)][static_cast<int>(sF)][1];
        }
		
        // Reset cube to default status (solved)
        void Reset() { e_Reset(); c_Reset(); spin = Spins::Default; }

		// Equal operator - corners & edges must match, spin is not important
		bool operator==(const Cube& rhcube) const { return edges == rhcube.GetEdgesStatus() && corners == rhcube.GetCornersStatus(); }

        // Not equal operator - corners & edges must not match, spin is not important
        bool operator!=(const Cube& rhcube) const { return edges != rhcube.GetEdgesStatus() || corners != rhcube.GetCornersStatus(); }
		
        // Check if cube is solved for given pieces masks
		bool IsSolved(const S64 EMask = EMASK_DATA, const S64 CMask = CMASK_DATA) const
		{
			return IsSolvedEdges(EMask) && IsSolvedCorners(CMask);
		}

        // Check if a single piece is in solve condition
		bool IsSolved(const Pieces) const;

        // Check if a group of pieces are in solve condition
		bool IsSolved(const PiecesGroups) const;

        // Check if some groups of pieces are in solve condition
		bool IsSolved(const std::vector<PiecesGroups>&) const;

        // Check if all pieces in the given layer are in solve condition
		bool IsSolved(const Layers) const;

		// Checks is the main face of given layer has the correct orientation
		bool IsLayerOriented(const Layers) const;
	
        // Get the current sticker in the given sticker position
        Stickers GetSticker(const StickerPositions) const;

        // Get the current position for the given sticker
        StickerPositions GetStickerPosition(const Stickers) const;

        // Get the current piece in the given piece position
        Pieces GetPiece(const PiecePositions) const;

        // Get the current position for the given piece
        PiecePositions GetPiecePosition(const Pieces) const;

		// Get the solved face of the sticker in the given sticker position
        Faces GetSolvedFace(const StickerPositions P) const { return f_Stickers[static_cast<int>(P)]; }

        // Get the current sticker face in the given sticker position
        Faces GetFace(const StickerPositions) const;

        // Get sticker for U center sticker position
        Stickers GetSticker_U() const { return Stickers::U; }

        // Get sticker for D center sticker position
		Stickers GetSticker_D() const { return Stickers::D; }

        // Get sticker for F center sticker position
		Stickers GetSticker_F() const { return Stickers::F; }

        // Get sticker for B center sticker position
		Stickers GetSticker_B() const { return Stickers::B; }

        // Get sticker for R center sticker position
		Stickers GetSticker_R() const { return Stickers::R; }

        // Get sticker for L center sticker position
		Stickers GetSticker_L() const { return Stickers::L; }
		
        // Get faces (color) for U center sticker position
        Faces GetFace_U() const { return Faces::U; }

        // Get faces (color) for D center sticker position
		Faces GetFace_D() const { return Faces::D; }

        // Get faces (color) for F center sticker position
		Faces GetFace_F() const { return Faces::F; }

        // Get faces (color) for B center sticker position
		Faces GetFace_B() const { return Faces::B; }

        // Get faces (color) for R center sticker position
		Faces GetFace_R() const { return Faces::R; }

        // Get faces (color) for L center sticker position
		Faces GetFace_L() const { return Faces::L; }	

        // Set cube spin
        void SetSpin(Spins s) { spin = s; }
	
        // Cube x turn
		void x()  { spin = s_Spins[static_cast<int>(spin)][0]; }

        // Cube x' turn
        void xp() { spin = s_Spins[static_cast<int>(spin)][1]; }

        // Cube x2 turn
		void x2() { spin = s_Spins[static_cast<int>(spin)][2]; }

        // Cube y turn
		void y()  { spin = s_Spins[static_cast<int>(spin)][3]; }

        // Cube y' turn
        void yp() { spin = s_Spins[static_cast<int>(spin)][4]; }

        // Cube y2 turn
		void y2() { spin = s_Spins[static_cast<int>(spin)][5]; }

        // Cube z turn
		void z()  { spin = s_Spins[static_cast<int>(spin)][6]; }

        // Cube z' turn
        void zp() { spin = s_Spins[static_cast<int>(spin)][7]; }

        // Cube z2 turn
		void z2() { spin = s_Spins[static_cast<int>(spin)][8]; }

        // Cube U movement
        void U();

        // Cube U2 movement
        void U2();

        // Cube U' movement
        void Up();

        // Cube D movement
        void D();

        // Cube D2 movement
        void D2();

        // Cube D' movement
        void Dp();

        // Cube F movement
        void F();

        // Cube F2 movement
        void F2();

        // Cube F' movement
        void Fp();

        // Cube B movement
        void B();

        // Cube B2 movement
        void B2();

        // Cube B' movement
        void Bp();

        // Cube R movement
        void R();

        // Cube R2 movement
        void R2();

        // Cube R' movement
        void Rp();

        // Cube L movement
        void L();

        // Cube L2 movement
        void L2();

        // Cube L' movement
        void Lp();
		
		// Apply algorithm to cube (algorithm should not have parentheses with more than one repetition)
        // If there are parentheses with more than one repetition returns false and cube status remains unchanged
		bool ApplyAlgorithm(Algorithm&);

		// Apply movement (step) to the cube
		// Returns false if the step is a close parentheses with more than one repetition
		bool ApplyStep(const Steps);

		// Check if given piece is in given layer
		bool IsPieceInLayer(const Pieces, const Layers) const;

		// Check if given pieces are in given layer
		bool ArePiecesInLayer(const std::vector<Pieces>, const Layers) const;

		// Check if given pieces are in given layer
		bool ArePiecesInLayer(const PiecesGroups, const Layers) const;

        // Get the number of F2L solved for given cross layer
        uint GetF2LSolved(Layers) const;

        // Check if the given F2L pair is adjacent (the corner next to the edge), orientation is not checked
        bool IsF2LAdjacent(PiecesGroups) const;

        // Check if the common colors for F2L pair are in the same face
        bool IsF2LOriented(PiecesGroups) const;

		// Return the opposite layer
		static Layers OppositeLayer(const Layers L) { return l_OppositeLayers[static_cast<uint>(L)]; }

		// Return the opposite face
		static Faces OppositeFace(const Faces F) { return f_OppositeFaces[static_cast<uint>(F)]; }

        // Add pieces from a group of pieces to a list
		static bool AddToPiecesList(const PiecesGroups, std::vector<Pieces>&);

        // Add pieces from groups of pieces to a list
		static bool AddToPiecesList(const std::vector<PiecesGroups>&, std::vector<Pieces>&);

        // Get the char for representing a layer
		static char GetLayerChar(const Layers Ly) { return c_Layers[static_cast<uint>(Ly)]; }

        // Check if a piece is a center
        static bool IsCenter(const Pieces P) { return t_Pieces[static_cast<uint>(P)] == PiecesTypes::CENTER; }

        // Check if a piece is an edge
        static bool IsEdge(const Pieces P) { return t_Pieces[static_cast<uint>(P)] == PiecesTypes::EDGE; }

        // Check if a piece is a corner
        static bool IsCorner(const Pieces P) { return t_Pieces[static_cast<uint>(P)] == PiecesTypes::CORNER; }
	
	private:
		// Cube spin (orientation)
		Spins spin;
			
		// Array to follow spins when a cube has a turn (24x9 elements array)
		const static Spins s_Spins[24][9]; 

        // Two turns array for get an spin from an inital spin
        const static Steps s_Turns[24][24][2];
		
		// Array to know the solved face of the stickers
		const static Faces f_Stickers[54];

		// Array to know the pieces type
		const static PiecesTypes t_Pieces[26];

		// Array to know the opposite layer
		const static Layers l_OppositeLayers[10];

		// Array to know the opposite face
		const static Faces f_OppositeFaces[6];

		// Array to know the layer char
		const static char c_Layers[10];

        // Array with spins string representation
        const static std::string sp_strings[];
	};
}

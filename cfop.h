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
#include "deep_search.h"

namespace grcube3
{
    // Class to search a solve for a Rubik's cube using CFOP method
	class CFOP
	{
	public:
		// Constructor with cube scramble
		CFOP(const Algorithm& Scr, int NumCores = 0) { Scramble = Scr; CubeBase = Cube(Scramble); Reset(); Cores = NumCores; }

		// Destructor
		~CFOP() {}

		// Reset the search results
		void Reset();

		// Search the best cross solve algorithm with the given search deep for the crosses pieces groups
		// Return false if no cross found
		bool SearchCross(const uint, const std::vector<PiecesGroups>&);

		// Search the best F2L 'Solves' algorithms for the 'Scramble'.
        bool SearchF2L()
        {
            auto time_F2L_start = std::chrono::system_clock::now();

            while(!SearchF2LStep()); // Repeat until returns true

            auto time_F2L_end = std::chrono::system_clock::now();
            std::chrono::duration<double> F2L_elapsed_seconds = time_F2L_end - time_F2L_start;
            F2LTime = F2L_elapsed_seconds.count();

            return IsF2LSolved();
        }

		// Orientation of last layer search
		bool SearchOLL();

		// Permutation of last layer search
		bool SearchPLL();

        // One-Look Last Layer search (1LLL)
        bool Search1LLL();

		// Check if the cross is solved
        bool IsCrossSolved() const
		{
			switch (CrossLayer)
			{
			case Layers::U: return CubeCross.IsSolved(PiecesGroups::C_U);
			case Layers::D: return CubeCross.IsSolved(PiecesGroups::C_D);
			case Layers::F: return CubeCross.IsSolved(PiecesGroups::C_F);
			case Layers::B: return CubeCross.IsSolved(PiecesGroups::C_B);
			case Layers::R: return CubeCross.IsSolved(PiecesGroups::C_R);
			case Layers::L: return CubeCross.IsSolved(PiecesGroups::C_L);
			default: return false;
			}
		}

		// Check if F2L is solved
        bool IsF2LSolved() const
		{
			switch (CrossLayer)
			{
			case Layers::U: return CubeF2L.IsSolved(Layers::U) && CubeF2L.IsSolved(Layers::E);
			case Layers::D: return CubeF2L.IsSolved(Layers::D) && CubeF2L.IsSolved(Layers::E);
			case Layers::F: return CubeF2L.IsSolved(Layers::F) && CubeF2L.IsSolved(Layers::S);
			case Layers::B: return CubeF2L.IsSolved(Layers::B) && CubeF2L.IsSolved(Layers::S);
			case Layers::R: return CubeF2L.IsSolved(Layers::R) && CubeF2L.IsSolved(Layers::M);
			case Layers::L: return CubeF2L.IsSolved(Layers::L) && CubeF2L.IsSolved(Layers::M);
			default: return false;
			}
		}

        // Get the number of F2L pairs solved with the cross
        uint GetCrossF2LSolved() const { return CubeCross.GetF2LSolved(CrossLayer); }

		// Check if the last layer is oriented (OLL search completed)
        bool IsLastLayerOriented() const { return CubeOLL.IsLayerOriented(Cube::OppositeLayer(CrossLayer)); }

		// Check if final cube is solved
        bool IsSolved() const { return CubeFinal.IsSolved(); }

		// Returns the current cross layer ('U', 'D', 'F', 'B', 'R' or 'L').
		Layers GetCrossLayer() const { return CrossLayer; }

		// Get the maximum cross deep used in the last search
		uint GetLastCrossDeep() const { return LastCrossDeep; }

		// Get current OLL case
		OLL GetOLLCase() const { return OLLCase; }

		// Get current PLL case
		PLL GetPLLCase() const { return PLLCase; }

		// Get search algorithms texts
        std::string GetTextScramble() const { return Scramble.ToString(); }
        std::string GetTextInspection() const { return Algorithm::GetTextStep(Turn_Inspection); }
        std::string GetTextCrossSolve() const { Algorithm Aux = Solve_Cross; Aux.TransformTurn(Turn_Inspection); return Aux.ToString(); }
        std::string GetTextF2LFirstSolve() const { Algorithm Aux = Solve_F2L_First; Aux.TransformTurn(Turn_Inspection); return Aux.ToString(); }
        std::string GetTextF2LSecondSolve() const { Algorithm Aux = Solve_F2L_Second; Aux.TransformTurn(Turn_Inspection); return Aux.ToString(); }
        std::string GetTextF2LThirdSolve() const { Algorithm Aux = Solve_F2L_Third; Aux.TransformTurn(Turn_Inspection); return Aux.ToString(); }
        std::string GetTextF2LFourthSolve() const { Algorithm Aux = Solve_F2L_Fourth; Aux.TransformTurn(Turn_Inspection); return Aux.ToString(); }
        std::string GetTextOLLTurn() const { return Algorithm::GetTextStep(Turn_OLL); }
        std::string GetTextOLLSolve() const { return Solve_OLL.ToString(); }
        std::string GetTextAUFSolve() const { return Algorithm::GetTextStep(Step_AUF); }
        std::string GetTextPLLTurn() const { return Algorithm::GetTextStep(Turn_PLL); }
        std::string GetTextPLLSolve() const { return Solve_PLL.ToString(); }
        std::string GetText1LLLTurn() const { return Algorithm::GetTextStep(Turn_1LLL); }
        std::string GetText1LLLSolve() const { return Solve_1LLL.ToString(); }

        // Get search algorithms lengths
        uint GetLengthScramble() const { return Scramble.GetNumSteps(); }
        uint GetLengthInspection() const { return Turn_Inspection == Steps::NONE ? 0u : 1u; }
        uint GetLengthCrossSolve() const { return Solve_Cross.GetNumSteps(); }
        uint GetLengthF2LFirstSolve() const { return Solve_F2L_First.GetNumSteps(); }
        uint GetLengthF2LSecondSolve() const { return Solve_F2L_Second.GetNumSteps(); }
        uint GetLengthF2LThirdSolve() const { return Solve_F2L_Third.GetNumSteps(); }
        uint GetLengthF2LFourthSolve() const { return Solve_F2L_Fourth.GetNumSteps(); }
        uint GetLengthOLLTurn() const { return Turn_OLL == Steps::NONE ? 0u : 1u; }
        uint GetLengthOLLSolve() const { return Solve_OLL.GetNumSteps(); }
        uint GetLengthAUFSolve() const { return Step_AUF == Steps::NONE ? 0u : 1u; }
        uint GetLengthPLLTurn() const { return Turn_PLL == Steps::NONE ? 0u : 1u; }
        uint GetLengthPLLSolve() const { return Solve_PLL.GetNumSteps(); }
        uint GetLength1LLLTurn() const { return Turn_1LLL == Steps::NONE ? 0u : 1u; }
        uint GetLength1LLLSolve() const { return Solve_1LLL.GetNumSteps(); }

        // Get the full solve lengh (total number of movements) - inspection is not included
        uint GetLengthSolve() const
        {
            return GetLengthCrossSolve() +
                   GetLengthF2L1Solve() + GetLengthF2L2Solve() + GetLengthF2L3Solve() + GetLengthF2L4Solve() +
                   GetLengthAUFSolve() +
                   (Case1LLL == 0u ? (GetLengthOLLTurn() + GetLengthOLLSolve() + GetLengthPLLTurn() + GetLengthPLLSolve()) :
                                     (GetLength1LLLTurn() + GetLength1LLLSolve()));
        }
		
		// Get text for current OLL case
        std::string GetTextOLLCase() const { return OLL_Strings[static_cast<uint>(OLLCase)]; }

		// Get text for given OLL case
        static std::string GetTextOLLCase(OLL OLL_Case) { return OLL_Strings[static_cast<uint>(OLL_Case)]; }

        // Get text for current 1LLL case
        std::string GetText1LLLCase() const { return std::to_string(Case1LLL); }

        // Get algorithm in text format for given OLL case
        static std::string GetTextOLLAlgorithm(OLL OLL_Case)
        {
            Algorithm A = OLL_Algorithms[static_cast<uint>(OLL_Case)][0];
            return A.ToString();
        }

		// Get text for current PLL case
        std::string GetTextPLLCase() const { return PLL_Strings[static_cast<uint>(PLLCase)]; }

		// Get text for given PLL case
        static std::string GetTextPLLCase(PLL PLL_Case) { return PLL_Strings[static_cast<uint>(PLL_Case)]; }

        // Get algorithm in text format for given PLL case
        static std::string GetTextPLLAlgorithm(PLL PLL_Case)
        {
            Algorithm A = PLL_Algorithms[static_cast<uint>(PLL_Case)][0];
            return A.ToString();
        }

        // Get the time elapsed searching cross
        double GetCrossTime() const { return CrossTime; }

        // Get the time elapsed searching F2L
        double GetF2LTime() const { return F2LTime; }

        // Get the time elapsed searching OLL
        double GetOLLTime() const { return OLLTime; }

        // Get the time elapsed searching PLL
        double GetPLLTime() const { return PLLTime; }

        // Get the time elapsed searching 1LLL
        double Get1LLLTime() const { return Time1LLL; }

        // Get the time for the full search
        double GetFullTime() const { return CrossTime + F2LTime + (Case1LLL == 0 ?  (OLLTime + PLLTime) : Time1LLL); }

        // Get a solve report
        std::string GetReport() const;

		// Get used cores in the solve
		int GetUsedCores() const { return Cores; }

	private:
		
		Algorithm Scramble, // Cube scramble
                  Solve_Cross, // Algorithm for the cross solve
				  Solve_F2L_First, // Algorithm to apply for solve the first F2L pair
				  Solve_F2L_Second, // Algorithm to apply for solve the second F2L pair
			      Solve_F2L_Third, // Algorithm to apply for solve the third F2L pair
			      Solve_F2L_Fourth, // Algorithm to apply for solve the fourth F2L pair
			      Solve_F2L_1, // Auxiliary algorithm for solve first F2L pair
				  Solve_F2L_2, // Auxiliary algorithm for solve second F2L pair
			      Solve_F2L_3, // Auxiliary algorithm for solve third F2L pair
			      Solve_F2L_4, // Auxiliary algorithm for solve fourth F2L pair
			      Solve_OLL, // Algorithm to apply for OLL solve
                  Solve_PLL, // Algorithm to apply for PLL solve
                  Solve_1LLL; // Algorithm to apply for 1LLL solve

		Steps Turn_Inspection, // Turn for inspection
			  Turn_PLL, // Turn for PLL
			  Step_AUF, // Step to apply for AUF
              Turn_OLL, // Turn for OLL
              Turn_1LLL; // Turn for 1LLL

		// Layer where the cross is found
		Layers CrossLayer;

		// Last used maximum cross deep
		uint LastCrossDeep;

		// OLL case 
		OLL OLLCase;

		// PLL case 
		PLL PLLCase;

        // One-Look Last Layer Case
        uint Case1LLL;

		// Cubes
        Cube CubeBase, CubeCross, CubeF2L, CubeOLL, CubeFinal, Cube1LLL; // No inspection turn

        // Times
        double CrossTime, F2LTime, OLLTime, PLLTime, Time1LLL;

		// Cores to use in the search: -1 = no multithreading, 0 = all avaliable cores, other = use this amount of cores
		int Cores;

        // Returns true if the search is complete. If returns false, call this function again.
        bool SearchF2LStep();

		// Static Array with all possible OLL masks (58 possibilities in 4 orientations).
		const static M16 OLL_Masks[4][58];

		// Static Array with all possible PLL masks (22 possibilities in 4 orientations).
		const static M16 PLL_Masks[4][22];

		// Static array with OLL solve algorithms (by case)
		const static std::vector<Algorithm> OLL_Algorithms[58];

		// Static array with PLL solve algorithms (by case)
		const static std::vector<Algorithm> PLL_Algorithms[22];

        // Static array with 1LLL solve algorithms
        static std::vector<Algorithm> Algorithms_1LLL;

		// Array with OLL cases string representation
		const static std::string OLL_Strings[58];

		// Array with PLL cases string representation
		const static std::string PLL_Strings[22];

		// Level configurations for cross and F2L searchs
		const static SearchLevel CrossLevelConf, F2L_LC,
								 F2L_U_L0, F2L_U_L1, F2L_U_L2, F2L_U_L3,
								 F2L_D_L0, F2L_D_L1, F2L_D_L2, F2L_D_L3,
								 F2L_F_L0, F2L_F_L1, F2L_F_L2, F2L_F_L3,
								 F2L_B_L0, F2L_B_L1, F2L_B_L2, F2L_B_L3,
								 F2L_R_L0, F2L_R_L1, F2L_R_L2, F2L_R_L3,
								 F2L_L_L0, F2L_L_L1, F2L_L_L2, F2L_L_L3;

		// Configurations for F2L search according to cross layer
		const static std::vector<SearchLevel> SearchConf_F2L_U, SearchConf_F2L_D, 
											  SearchConf_F2L_F, SearchConf_F2L_B,
											  SearchConf_F2L_R, SearchConf_F2L_L;

		// Get the layer with the best solve score
		static Layers GetBestScoreLayer(const uint, const uint, const uint, const uint, const uint, const uint);

		// Get auxiliary F2L solves
        uint GetLengthF2L1Solve() const { return Solve_F2L_1.GetNumSteps(); }
        uint GetLengthF2L2Solve() const { return Solve_F2L_2.GetNumSteps(); }
        uint GetLengthF2L3Solve() const { return Solve_F2L_3.GetNumSteps(); }
        uint GetLengthF2L4Solve() const { return Solve_F2L_4.GetNumSteps(); }
	};
}

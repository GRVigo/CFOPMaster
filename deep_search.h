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
#include <mutex>
#include <thread>

#include "cube_definitions.h"
#include "algorithm.h"
#include "cube.h"

namespace grcube3
{
    // Struct to store information about what to do in each search level
	struct SearchLevel
	{
        SearchActions SAction; // What search action has to be done at current level
        SearchSteps SSteps; // A list of steps (movements) allowed to be added for the next level (if needed)
        SearchCheck SCheck; // If it's necessary to check the given pieces are solved in this level
		
        // Constructor with default parameters
		SearchLevel(const SearchActions SA = SearchActions::STEPS_LIST,
				    const SearchSteps SS = SearchSteps::SINGLE_ALL, 
			        const SearchCheck SC = SearchCheck::CHECK) { SAction = SA; SSteps = SS; SCheck = SC; }
	};

    // Struct to store a pair of masks (edges and corners status masks)
	struct MasksPair
	{
        S64 MaskE, MaskC; // Masks for check the solve condition in edges and corners

        // Constructor with default parameters
		MasksPair(const S64 EMask = 0ull, const S64 CMask = 0ull) { MaskE = EMask; MaskC = CMask; }
	};

    // Class to do a search
	class DeepSearch
	{
	public:
		// Algorithms that solve the search
		std::vector<Algorithm> Solves; 
		
        // Algorithm search class constructor
        // Scramble to start the search
        // Goups of pieces to check (wich pieces have to be solved for finishing the search)
        // What kind of search has to be done in each search level
        // If OptimizeThreads is true (and exist the conditions to optimize threads), the first search level never will be checked
        // If multiple search is enabled, each pieces group will be checked separatelly. If disabled, all pieces groups are evaluated together
        DeepSearch(Algorithm&, std::vector<PiecesGroups>&, std::vector<SearchLevel>&, bool = false, bool = false);

		uint GetCores() const { return Cores; } // Get system cores
		uint GetCoresUsed() const { return UsedCores; } // Get system cores used in the last search
		uint GetBranches() const { return RootBranches; } // Get number of root branches in the search
		uint GetDeep() const { return MaxSearchDeep; } // Get the maximum deep in the search

        void Run(const int = 0); // Run the search; -1: use no threads, 0: use all threas avaliable, other: use specified number of threads

        // Returns best F2L solve from the Solves vector class member and his score for the given start layer
        // F2L pieces are used as evaluation condition
		uint EvaluateF2LResult(Algorithm&, Layers, SearchPolicies);

		// Get the real number of cores used (a search should be done )
		int GetRealCores (int RequestedCores) const { return RequestedCores < 0 ? -1 : RequestedCores <= Cores ? RequestedCores : Cores; }

		// Get the number of cores (threads) in the current system
		static uint GetSystemCores() { return std::thread::hardware_concurrency(); }

	private:
		std::vector<SearchActions> LevelsActions; // Search actions in each level
		std::vector<SearchCheck> LevelsCheck; // Search levels check list
		std::vector<std::vector<Steps>> LevelsSteps; // Steps to search for each level
        bool ExtendFirstLevel; // Use precalculated algorithms as first search level
        std::vector<Algorithm> FirstLevelAlgs; // Extended first level with two-steps algorithms for search

		uint MaxSearchDeep; // Maximum deep for the search (levels)
		int Cores; // Number of phisical cores in the machine
		uint UsedCores; // Number of cores to limit the threads
		uint RootBranches; // Number of search root branches to be distributed among cores

		Algorithm Scramble; // Cube scramble to start the search
		Cube CubeBase; // Cube with the scramble already applyed

		std::vector<MasksPair> SolveMasks; // Mask pairs for check solves

		std::mutex SearchMutex; // Mutex for multithreading
		
		void RunThread(const uint); // Divide search branches into threads

		void RunSearch(Algorithm&, uint, M16 = 1u); // Run a search branch

        // Returns the initial mask for control which group of pieces are solved - for multiple search
		M16 GetStartGroupMask() const
		{
			M16 GroupMask = 0u, iMask = 1u;
			for (uint i = 0u; i < SolveMasks.size(); i++) { GroupMask |= iMask; iMask <<= 1; }
			return GroupMask;
		}
	};
}


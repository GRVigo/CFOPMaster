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

#include <thread>
#include <mutex>

#include "deep_search.h"

namespace grcube3
{
    // Algorithm search class constructor
    // Scramble to start the search
    // Goups of pieces to check (wich pieces have to be solved for finishing the search)
    // What kind of search has to be done in each search level
    // If OptimizeThreads is true (and exist the conditions to optimize threads), the first search level never will be checked
    // If multiple search is enabled, each pieces group will be checked separatelly. If disabled, all pieces groups are evaluated together
    DeepSearch::DeepSearch(Algorithm& Scr, std::vector<PiecesGroups>& SP, std::vector<SearchLevel>& SL, bool OptimizeThreads, bool MultipleSearch)
	{	
		std::vector<Pieces> PiecesList; // Pieces list to solve
        std::vector<Edges> EdgesList; // Edges list to solve
        std::vector<Corners> CornersList; // Corners list to solve

		if (MultipleSearch) // Each piece group generates a solve mask pair (edges and corners)
		{
			for (auto s : SP)
			{
				PiecesList.clear();
				Cube::AddToPiecesList(s, PiecesList); // Each piece group
				EdgesList.clear();
				CornersList.clear();
				for (auto P : PiecesList) // Separate pieces in edges and corners
				{
					if (Cube::IsEdge(P))
						EdgesList.push_back(static_cast<Edges>(static_cast<int>(P) - static_cast<int>(Pieces::First_Edge)));
					else if (Cube::IsCorner(P))
						CornersList.push_back(static_cast<Corners>(static_cast<int>(P) - static_cast<int>(Pieces::First_Corner)));
				}
				MasksPair MP(Cube::GetMasksSolvedEdges(EdgesList), Cube::GetMasksSolvedCorners(CornersList));
				SolveMasks.push_back(MP);
			}
		}
        else // All pieces in a pair of masks (edges + corners)
		{
			for (auto s : SP) Cube::AddToPiecesList(s, PiecesList); // No multimple search, all pieces together
			
			for (auto P : PiecesList) // Separate pieces in edges and corners
			{
				if (Cube::IsEdge(P))
					EdgesList.push_back(static_cast<Edges>(static_cast<int>(P) - static_cast<int>(Pieces::First_Edge)));
				else if (Cube::IsCorner(P))
					CornersList.push_back(static_cast<Corners>(static_cast<int>(P) - static_cast<int>(Pieces::First_Corner)));
			}
			MasksPair MP(Cube::GetMasksSolvedEdges(EdgesList), Cube::GetMasksSolvedCorners(CornersList));
			SolveMasks.push_back(MP);
		}

        MaxSearchDeep = static_cast<uint>(SL.size()); // Maximum search deep is the number of levels in the search levels vector

        std::vector<std::vector<Steps>> AuxLevelSteps; // Double vector to store steps to be used in each level

        // Read what to do in each level
        for (uint level = 0; level < MaxSearchDeep; level++)
		{
			LevelsActions.push_back(SL[level].SAction);

			LevelsCheck.push_back(SL[level].SCheck);

			std::vector<Steps> Aux;
			AuxLevelSteps.push_back(Aux);
			
			if (SL[level].SAction == SearchActions::STEPS_LIST) Algorithm::AddToStepsList(SL[level].SSteps, AuxLevelSteps[level]);
			LevelsSteps.push_back(AuxLevelSteps[level]);
		}
		
        // Apply the scramble
		Scramble = Scr;
		CubeBase.ApplyAlgorithm(Scramble);
		
        Cores = GetSystemCores(); // For multithreading

        // Check if it is possible to optimize threads
        if (OptimizeThreads && MaxSearchDeep > 2u && Scramble.GetNumSteps() > 2u)
        {
            ExtendFirstLevel = true;
            for (uint n = 0; n < 2u; n++) if (LevelsActions[n] != SearchActions::STEPS_LIST) ExtendFirstLevel = false;
        }
        else ExtendFirstLevel = false;

        // To optimize I merge the two first tree search levels to get more and smaller branches that fit better into threads
        if (ExtendFirstLevel)
        {
            for (auto L0 : LevelsSteps[0])
                for (auto L1: LevelsSteps[1])
                {
                    Algorithm A;
                    A.Append(L0);
                    if (!A.AppendShrink(L1)) FirstLevelAlgs.push_back(A); // If the two steps can be joined, reject as first level algorithm
                }
        }
        else for (auto L0 : LevelsSteps[0]) // Thread optimization is not used
		{
			Algorithm A;
           	A.Append(L0);
			FirstLevelAlgs.push_back(A);
		}

        // The number of root branches are determined by the number of steps in the first level       
        RootBranches = static_cast<uint>(FirstLevelAlgs.size());

        if (RootBranches < 1u) RootBranches = 1u; // Should not happend

		UsedCores = 0; // Not used cored yet
	}
	
	// Run the search - -1: use no threads, 0: use all threads avaliable, other: use specified number of threads
	void DeepSearch::Run(const int UseThreads)
	{
		if (UseThreads >= 0) // Multithreading
		{
			UsedCores = (UseThreads == 0) || (UseThreads >= Cores) ? Cores : UseThreads;

			std::vector<std::thread> Pool; // Threads pool

			for (uint nc = 0; nc < UsedCores; nc++) Pool.push_back(std::thread(&DeepSearch::RunThread, this, nc)); // Add a thread per core
			for (auto& t : Pool) t.join(); // Wait for all threads
		}
        else // Without multithreading (for debugging, slower)
		{
			for (uint n = 0; n < RootBranches; n++)
			{
				if (ExtendFirstLevel) RunSearch(FirstLevelAlgs[n], 1u, GetStartGroupMask());
				else RunSearch(FirstLevelAlgs[n], 0u, GetStartGroupMask());
			}
			UsedCores = -1;
		}
	}
	
    // Run search a thread
	void DeepSearch::RunThread(const uint NCore)
	{	
		for (uint n = NCore; n < RootBranches; n += UsedCores)
		{
            if (ExtendFirstLevel) RunSearch(FirstLevelAlgs[n], 1u, GetStartGroupMask()); // Start search in deep 1 (as levels 0 and 1 are merged) -first level is not checked-
            else RunSearch(FirstLevelAlgs[n], 0u, GetStartGroupMask()); // Start search in deep level 0
		}
    }
    
	// Recursive search code
    void DeepSearch::RunSearch(Algorithm& Alg, uint Deep, M16 GroupMask)
	{
		if (Deep >= MaxSearchDeep || GroupMask == 0u) return;

        // Check if current algorithm solves the pieces
		if (LevelsCheck[Deep] == SearchCheck::CHECK)
		{
			Cube CubeTest = CubeBase;
			CubeTest.ApplyAlgorithm(Alg);

			M16 iMask = 1u;
			for (const auto& M : SolveMasks)
			{
				if (((GroupMask & iMask) > 0u) && CubeTest.IsSolved(M.MaskE, M.MaskC))
				{ // Solve algorithm found
					GroupMask &= ~iMask; // The search for this group is complete
					std::lock_guard<std::mutex> guard(SearchMutex);
					Solves.push_back(Alg); // Thread safe code
				}
				iMask <<= 1; // Next group
			}
		}

        if (++Deep == MaxSearchDeep) return; // It's no necessary to continue the search

        // Prepare the branches for the next level of the search
		Steps LastStep, AuxStep;
		switch (LevelsActions[Deep])
		{
        case SearchActions::STEPS_LIST: // Use a steps (movements) list to create new branches
			LastStep = Alg.Last();
			for (auto S : LevelsSteps[Deep])
			{
				// As in an algorithm "... U D ..." branch is the same than "... D U ..." branch, compute only one.
				if (Algorithm::OppositeSteps(LastStep, S) && LastStep > S) continue;
				
                // If NONE step are expressed specifically, go to the next level with the same algorithm
                if (S == Steps::NONE) RunSearch(Alg, Deep, GroupMask);
                else // Continue the search only on a longer algorithm (shorter or equal lenght means that will be calculated upper in the tree)
				{
					Algorithm Alg2 = Alg;
					if (!Alg2.AppendShrink(S)) RunSearch(Alg2, Deep, GroupMask); // Recursive
				}
			}
			break;

        case SearchActions::OPPOSITE_STEP_2_PREVIOUS: // Use a opposite step of two levels before to continue the branch
			LastStep = Alg.Last();
			AuxStep = Alg.PenultimateInverted();

			// As in an algorithm "... U D ..." branch is the same than "... D U ..." branch, compute only one.
			if (!(Algorithm::OppositeSteps(LastStep, AuxStep) && LastStep > AuxStep))
			{
				Algorithm Alg2 = Alg;
				// Go deeper only on a longer algorithm (shorter or equal lenght means that will be calculated upper in the tree)
				if (!Alg2.AppendShrink(AuxStep)) RunSearch(Alg2, Deep, GroupMask); // Recursive
			}
			break;

		default: break;
		}
    }

    // Returns best solve algorithm from the Solves vector class member and his score for the given start layer
    // F2L pieces are used as evaluation condition
	uint DeepSearch::EvaluateF2LResult(Algorithm& BestSolve, Layers StartLayer, SearchPolicies Policy) 
	{
		if (Solves.size() <= 0) return 0u; // No solves

		// Pieces to search
		PiecesGroups F2L_1, F2L_2, F2L_3, F2L_4, CrossPG;

        // Get the required cross and F2L pieces groups based on the start layer
		switch (StartLayer)
		{
		case Layers::U:
			CrossPG = PiecesGroups::C_U;
			F2L_1 = PiecesGroups::F2L_U_UFR;
			F2L_2 = PiecesGroups::F2L_U_UFL;
			F2L_3 = PiecesGroups::F2L_U_UBR;
			F2L_4 = PiecesGroups::F2L_U_UBL;
			break;
		case Layers::D:
			CrossPG = PiecesGroups::C_D;
			F2L_1 = PiecesGroups::F2L_D_DFR;
			F2L_2 = PiecesGroups::F2L_D_DFL;
			F2L_3 = PiecesGroups::F2L_D_DBR;
			F2L_4 = PiecesGroups::F2L_D_DBL;
			break;
		case Layers::F:
			CrossPG = PiecesGroups::C_F;
			F2L_1 = PiecesGroups::F2L_F_UFR;
			F2L_2 = PiecesGroups::F2L_F_UFL;
			F2L_3 = PiecesGroups::F2L_F_DFR;
			F2L_4 = PiecesGroups::F2L_F_DFL;
			break;
		case Layers::B:
			CrossPG = PiecesGroups::C_B;
			F2L_1 = PiecesGroups::F2L_B_UBR;
			F2L_2 = PiecesGroups::F2L_B_UBL;
			F2L_3 = PiecesGroups::F2L_B_DBR;
			F2L_4 = PiecesGroups::F2L_B_DBL;
			break;
		case Layers::R:
			CrossPG = PiecesGroups::C_R;
			F2L_1 = PiecesGroups::F2L_R_UFR;
			F2L_2 = PiecesGroups::F2L_R_UBR;
			F2L_3 = PiecesGroups::F2L_R_DFR;
			F2L_4 = PiecesGroups::F2L_R_DBR;
			break;
		case Layers::L:
			CrossPG = PiecesGroups::C_L;
			F2L_1 = PiecesGroups::F2L_L_UFL;
			F2L_2 = PiecesGroups::F2L_L_UBL;
			F2L_3 = PiecesGroups::F2L_L_DFL;
			F2L_4 = PiecesGroups::F2L_L_DBL;
			break;
		default: return 0u; // Invalid cross layer
		}

        // Based on the search policy, different conditions have different weights in the final score
        uint SolveSizeMagnitude, SolveF2LMagnitude, SolveOppositeLayerMagnitude, SolveOrientedMagnitude, SolveNotAdjacentMagnitude;
		switch (Policy)
		{
		case SearchPolicies::SHORT:
			SolveSizeMagnitude = 1000u;
			SolveF2LMagnitude = 100u;
			SolveOppositeLayerMagnitude = 10u;
            SolveOrientedMagnitude = 50u;
            SolveNotAdjacentMagnitude = 10u;
			break;
		case SearchPolicies::BEST_SOLVES:
		default: 
			SolveSizeMagnitude = 1u;
			SolveF2LMagnitude = 1000u;
			SolveOppositeLayerMagnitude = 10u;
            SolveOrientedMagnitude = 50u;
            SolveNotAdjacentMagnitude = 10u;
			break;
		}

		uint Score, MaxScore = 0u, MaxScoreIndex = 0u, Index = 0u;

        for (auto& s : Solves) // Check each solve to get the best one
		{
			Score = (s.GetSize() > 50u ? 0u : 50u - s.GetSize()) * SolveSizeMagnitude;
			Cube CheckCube = CubeBase;
			CheckCube.ApplyAlgorithm(s);

			if (!CheckCube.IsSolved(CrossPG)) {	Index++; continue; }

			// Check F2L solves
			if (CheckCube.IsSolved(F2L_1)) Score += SolveF2LMagnitude;
			if (CheckCube.IsSolved(F2L_2)) Score += SolveF2LMagnitude;
			if (CheckCube.IsSolved(F2L_3)) Score += SolveF2LMagnitude;
			if (CheckCube.IsSolved(F2L_4)) Score += SolveF2LMagnitude;

            // Check both F2L pieces conditionvin the opposite layer
			Layers EndLayer = Cube::OppositeLayer(StartLayer);
			
            if (CheckCube.IsF2LOriented(F2L_1)) Score += SolveOrientedMagnitude;
            else
            {
                if (CheckCube.ArePiecesInLayer(F2L_1, EndLayer))
                {
                    Score += SolveOppositeLayerMagnitude;
                    if (CheckCube.IsF2LAdjacent(F2L_1)) Score += SolveNotAdjacentMagnitude;
                }
            }

            if (CheckCube.IsF2LOriented(F2L_2)) Score += SolveOrientedMagnitude;
            else
            {
                if (CheckCube.ArePiecesInLayer(F2L_2, EndLayer))
                {
                    Score += SolveOppositeLayerMagnitude;
                    if (CheckCube.IsF2LAdjacent(F2L_2)) Score += SolveNotAdjacentMagnitude;
                }
            }

            if (CheckCube.IsF2LOriented(F2L_3)) Score += SolveOrientedMagnitude;
            else
            {
                if (CheckCube.ArePiecesInLayer(F2L_3, EndLayer))
                {
                    Score += SolveOppositeLayerMagnitude;
                    if (CheckCube.IsF2LAdjacent(F2L_3)) Score += SolveNotAdjacentMagnitude;
                }
            }

            if (CheckCube.IsF2LOriented(F2L_4)) Score += SolveOrientedMagnitude;
            else
            {
                if (CheckCube.ArePiecesInLayer(F2L_4, EndLayer))
                {
                    Score += SolveOppositeLayerMagnitude;
                    if (CheckCube.IsF2LAdjacent(F2L_4)) Score += SolveNotAdjacentMagnitude;
                }
            }

			if (Score > MaxScore)
			{
				MaxScore = Score;
				MaxScoreIndex = Index;
			}
			Index++;
		}

		BestSolve = Solves[MaxScoreIndex];

		return MaxScore;
	}
}

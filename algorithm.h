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

#include <string>
#include <vector>

#include "cube_definitions.h"

namespace grcube3
{
	class Algorithm
	{
	public:
		Algorithm() { }; // Empty algorithm constructor
		Algorithm(uint n) { Append(n); } // Random algorithm constructor
		Algorithm(const char* s) { std::string ss(s); Append(ss); } // Algorithm from chars array
		Algorithm(std::string& s) { Append(s); } // Algorithm from string constructor
		~Algorithm() { } // Destructor
		
		Steps& operator[](const uint pos) { return Movs[pos]; } // Return step at position
		bool operator==(Algorithm&) const; // Equal operator
		bool operator!=(Algorithm&) const; // Not equal operator
		Algorithm operator+(Algorithm&); // Algorithm addition operator
		Algorithm operator+(Steps); // Step addition operator
        Algorithm& operator+=(Algorithm& rhalg)	{ Append(rhalg); return *this; } // Add algorithm operator
        Algorithm& operator+=(Steps rhstp) { Append(rhstp); return *this; } // Add step operator
		
		void Clear() { Movs.clear(); } // Clear algorithm
		bool Erase(const uint); // Erase single movement (step) in given position
		bool Erase(const uint, const uint); // Erase movements (steps) in given range
		void EraseLast() { Movs.pop_back(); } // Erase last movememnt
		void EraseFirst() { Erase(0u); } // Erase first movement
	
		uint GetSize() const { return static_cast<uint>(Movs.size()); } // Get the algorithm length (number of steps in the list)
		uint GetNumSteps() const; // Get the number of steps in the algorithm (parentheses are developed in the count)

		Steps First() const { return Movs.front(); }  // Get the algorithm first step
		Steps Last() const { return Movs.back(); } // Get the algorithm last step
		Steps Penultimate() const { return GetSize() < 2u ? Steps::NONE : Movs[GetSize() - 2u]; } // Gets the penultimate step in the algorithm
		Steps PenultimateInverted() const { return GetSize() < 2u ? Steps::NONE : m_inverted[static_cast<int>(Movs[GetSize() - 2u])]; } // Gets the inverted penultimate step in the algorithm

		// Returns true if given step is in the opposite layer of the last algorithm step
		bool OppositeLayerLastStep(const Steps S) const { return m_layer[static_cast<int>(S)] == m_layer_opposite[static_cast<int>(Last())]; }
		
		bool CheckParentheses() const; // Check if algorithm parentheses are OK
		bool CheckParentheses(bool&) const; // Check if algorithm parentheses are OK and returns by reference if there are parentheses
	
		void Append(const Steps stp) { Movs.push_back(stp); } // Append given step at the end of the algorithm (no shrink)
		bool AppendShrink(const Steps stp) { Movs.push_back(stp);  return ShrinkLast(); } // Append given step at the end of the algorithm and shrink it
		void Append(Algorithm&); // Append given algorithm at the end of the algorithm (no shrink)
		bool Append(std::string&); // Append given text algorithm at the end of the algorithm (no shrink)
        void Append(const uint, const Steps = Steps::U, const Steps = Steps::L2); // Append random movements (by default U, D, F, B, R ,L) until get the given size (with shrink)

		bool Insert(const uint, const Steps); // Insert given step in given position
		bool InsertParentheses(const uint, const uint, const uint = 1u); // Surround the given range in parentheses with the given repetitions
		
		std::string ToString(const char = ' ') const; // Return current algorithm as plain text string
		
		Algorithm GetDeveloped(const bool = false) const; // Gets the same algorithm with single or without parentheses -default- (steps inside parentheses developed)
		Algorithm GetSimplified() const; // Gets the same algorithm with single layer movements and turns and no parentheses (should be used before applying the algorithm to a cube)
		Algorithm GetSubAlgorithm(const uint, const uint) const; // Gets a sub-algorithm from an algorithm position with given length
		Algorithm GetWithoutTurns() const; // Returns an algorithm removing x, y and z turns from the algorithm (maintaining the functionality)
		
		bool Shrink(); // Returns false if the algorithm is shrinked; if returns true apply shrink again
		bool ShrinkLast(); // Shrinks last step only

		void Transform_x() { for (auto& S : Movs) S = m_x[static_cast<int>(S)];	} // Transform the algorithm applying an x turn
		void Transform_xp() { for (auto& S : Movs) S = m_xp[static_cast<int>(S)]; } // Transform the algorithm applying an x' turn
		void Transform_x2() { for (auto& S : Movs) S = m_x2[static_cast<int>(S)]; } // Transform the algorithm applying an x2 turn
		void Transform_y() { for (auto& S : Movs) S = m_y[static_cast<int>(S)]; } // Transform the algorithm applying an y turn
		void Transform_yp() { for (auto& S : Movs) S = m_yp[static_cast<int>(S)]; } // Transform the algorithm applying an y' turn
		void Transform_y2() { for (auto& S : Movs) S = m_y2[static_cast<int>(S)]; } // Transform the algorithm applying an y2 turn
		void Transform_z() { for (auto& S : Movs) S = m_z[static_cast<int>(S)]; } // Transform the algorithm applying an z turn
		void Transform_zp() { for (auto& S : Movs) S = m_zp[static_cast<int>(S)]; } // Transform the algorithm applying an z' turn
		void Transform_z2() { for (auto& S : Movs) S = m_z2[static_cast<int>(S)]; } // Transform the algorithm applying an z2 turn

		void TransformTurn(const Steps); // Transform the algorithm applying the given turn

		bool Transform_x(const uint, const uint); // Transform the algorithm applying an x turn to the specified range of steps
		bool Transform_xp(const uint, const uint); // Transform the algorithm applying an x' turn to the specified range of steps
		bool Transform_x2(const uint, const uint); // Transform the algorithm applying an x2 turn to the specified range of steps
		bool Transform_y(const uint, const uint); // Transform the algorithm applying an y turn to the specified range of steps
		bool Transform_yp(const uint, const uint); // Transform the algorithm applying an y' turn to the specified range of steps
		bool Transform_y2(const uint, const uint); // Transform the algorithm applying an y2 turn to the specified range of steps
		bool Transform_z(const uint, const uint); // Transform the algorithm applying an z turn to the specified range of steps
		bool Transform_zp(const uint, const uint); // Transform the algorithm applying an z' turn to the specified range of steps
		bool Transform_z2(const uint, const uint); // Transform the algorithm applying an z2 turn to the specified range of steps

		// Transform the algorithm applying the given turn to the specified range of steps
		bool TransformTurn(const Steps, const uint, const uint);

		bool TransformReverse(); // Changes the steps order
		void TransformInvert(); // Changes every movement for the invert one
		bool TransformReverseInvert(); // Changes the steps order and every movement for the invert one
		void TransformSymmetrical(); // Changes every movement for the symmetrical one
		void TransformInvertMSteps(); // Change M to M' and M' to M
		void TransformInvertESteps(); // Change E to E' and E' to E
		void TransformInvertSSteps(); // Change S to S' and S' to S

		// Gets the close parenthesis step with given repetitions
		static Steps GetCloseParenthesis(const uint rep = 1u)
		{
			return (rep < 1u || rep > 9u) ?
				Steps::NONE : static_cast<Steps>(static_cast<uint>(Steps::PARENTHESIS_OPEN) + rep);
		}

		// Gets the repetitions of the given close parenthesis step
		static uint GetCloseParenthesisRepetitions(const Steps s)
		{
			return (s < Steps::PARENTHESIS_CLOSE_1_REP || s > Steps::PARENTHESIS_CLOSE_9_REP) ?
				0u : static_cast<uint>(s) - static_cast<uint>(Steps::PARENTHESIS_OPEN);
		}

		static bool CheckParentheses(const std::string&); // Check the parentheses in a string (final nesting == 0 and nesting always >= 0)
		static std::string CleanString(const std::string&); // Returns a clean algorithm string (removes not allowed chars)
		static bool AddToStepsList(const SearchSteps, std::vector<Steps>&); // Add given steps group to the steps list
		// Returns true if given steps are in opposite layers (and steps are single layer ones <- Commented for speed) 
		static bool OppositeSteps(const Steps S1, const Steps S2) {	return (m_layer[static_cast<int>(S1)] == m_layer_opposite[static_cast<int>(S2)]) /* &&
			                                                               (m_range[static_cast<int>(S1)] == Ranges::SINGLE)*/; }
		static std::string GetTextStep(const Steps s) { return m_strings[static_cast<uint>(s)]; }

	private:
		std::vector<Steps> Movs; // Algorithm movements (steps)
	
		const static Steps m_x[]; // Array for x turn
		const static Steps m_xp[]; // Array for x' turn
		const static Steps m_x2[]; // Array for x2 turn
		const static Steps m_y[]; // Array for y turn
		const static Steps m_yp[]; // Array for y' turn
		const static Steps m_y2[]; // Array for y2 turn
		const static Steps m_z[]; // Array for z turn
		const static Steps m_zp[]; // Array for z' turn
		const static Steps m_z2[]; // Array for z2 turn

		const static Steps m_inverted[]; // Array to get the inverted movements
		const static Steps m_symmetrical[]; // Array to get the symmetrical movements
	
		const static Steps m_sequence[][3]; // Array of equivalent three movements sequence
	
		const static Layers m_layer[]; // Array for get movements layer
		const static Layers m_layer_opposite[]; // Array for get movements opposite layer
		const static Ranges m_range[]; // Array for get movements range
	
		const static char m_chars[]; // Array with allowed chars in an algorithm
	
		const static std::string m_strings[]; // Array with steps string representation

		static Steps GetStepFromString(const std::string&, uint, uint&); // Get a step inside the string
		int GetParenthesesNesting() const; // Gets parentheses nesting
		static bool JoinSteps(const Steps, const Steps, Steps&); // Join two steps, return true if the join has been done
		static bool JoinSteps(const Steps, const Steps, const Steps, Steps&); // Join two steps with a middle step, return true if the join has been done
	};
}

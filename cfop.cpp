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

#include "cfop.h"

#include <chrono>

namespace grcube3
{
	// Static array with OLL solve algorithms (by case)
	const std::vector<Algorithm> CFOP::OLL_Algorithms[58] =
	{
		{ // Skip
			Algorithm()
		}, 
		{ // OCLL1
			Algorithm("(R U2 R') (U' R U R') (U' R U' R')"), 
			Algorithm("(R U R' U) (R U' R' U) (R U2' R')")  
		}, 
		{ // OCLL2
			Algorithm("R U2' R2' U' R2 U' R2' U2' R") 
		}, 
		{ // OCLL3
			Algorithm("R2 D (R' U2 R) D' (R' U2 R')"),
			Algorithm("R2' D' (R U2 R') D (R U2 R)")
		}, 
		{ // OCLL4
			Algorithm("(r U R' U') (r' F R F')"), 
			Algorithm("(R U R D) (R' U' R D') R2'")
		}, 
		{ // OCLL5
			Algorithm("F' (r U R' U') r' F R"), 
			Algorithm("x (R' U R) D' (R' U' R) D x'")
		}, 
		{ // OCLL6
			Algorithm("R U2 R' U' R U' R'"),
			Algorithm("R' U' R U' R' U2 R")
		}, 
		{ // OCLL7
			Algorithm("R U R' U R U2' R'"),
			Algorithm("R' U2' R U R' U R")
		},
		{ // T1
			Algorithm("(R U R' U') (R' F R F')") 
		}, 
		{ // T2
			Algorithm("F (R U R' U') F'")
		}, 
		{ // S1
			Algorithm("(r' U2' R U R' U r)")
		}, 
		{ // S2
			Algorithm("(r U2 R' U' R U' r')")
		}, 
		{ // C1
			Algorithm("(R U R2' U') (R' F R U) R U' F'")
		}, 
		{ // C2
			Algorithm("R' U' (R' F R F') U R") 
		}, 
		{ // W1
			Algorithm("(R' U' R U') (R' U R U) l U' R' U x"),
			Algorithm("(R U R' F') (R U R' U') (R' F R U') (R' F R F')")
		}, 
		{ // W2
			Algorithm("(R U R' U) (R U' R' U') (R' F R F')") 
		}, 
		{ // E1
			Algorithm("(r U R' U') M (U R U' R')") 
		}, 
		{ // E2
			Algorithm("(R U R' U') M' (U R U' r')") 
		}, 
		{ // P1
			Algorithm("(R' U' F) (U R U' R') F' R") 
		}, 
		{ // P2
			Algorithm("R U B' (U' R' U) (R B R')"),
			Algorithm("S (R U R' U') (R' F R f')")
		}, 
		{ // P3
			Algorithm("R' U' F' U F R"),
			Algorithm("f' (L' U' L U) f")
		}, 
		{ // P4
			Algorithm("f (R U R' U') f'"),
			Algorithm("F (U R U' R') F'")
		}, 
		{ // I1
			Algorithm("f (R U R' U') (R U R' U') f'"),
			Algorithm("F (U R U' R') (U R U' R') F'")
		}, 
		{ // I2
			Algorithm("(R' U' R U' R' U) y' (R' U R) B"),
			Algorithm("(R U R' U R U') y (R U' R') F'")
		}, 
		{ // I3
			Algorithm("(R' F R U) (R U' R2' F') R2 U' R' (U R U R')") 
		}, 
		{ // I4
			Algorithm("r' U' r (U' R' U R) (U' R' U R) r' U r") 
		}, 
		{ // F1
			Algorithm("(R U R' U') R' F (R2 U R' U') F'"),
			Algorithm("(R' U' R) y r U' r' U r U r'")
		}, 
		{ // F2
			Algorithm("(R U R' U) (R' F R F') (R U2' R')"),
			Algorithm("(R U R') y (R' F R U') (R' F' R)")		
		}, 
		{ // F3
			Algorithm("(R U2') (R2' F R F') (R U2' R')") 
		}, 
		{ // F4
			Algorithm("F (R U' R' U') (R U R' F')") 
		}, 
		{ // K1
			Algorithm("(r U' r') (U' r U r') y' (R' U R)"),
			Algorithm("F U R U' R2' F' R U (R U' R')")
		}, 
		{ // K2
			Algorithm("(R' F R) (U R' F' R) (F U' F')") 
		}, 
		{ // K3
			Algorithm("(r' U' r) (R' U' R U) (r' U r)") 
		}, 
		{ // K4
			Algorithm("(r U r') (R U R' U') (r U' r')") 
		}, 
		{ // A1
			Algorithm("(R U R' U') (R U' R') (F' U' F) (R U R')"),
			Algorithm("M U (R U R' U') (R' F R F') M'")
		}, 
		{ // A2
			Algorithm("F U (R U2 R' U') (R U2 R' U') F'"),
			Algorithm("(F R' F) (R2 U' R' U') (R U R') F2")
		}, 
		{ // A3
			Algorithm("(R U R' U R U2' R') F (R U R' U') F'") 
		}, 
		{ // A4
			Algorithm("(R' U' R U' R' U2 R) F (R U R' U') F'"),
			Algorithm("(R' F R F') (R' F R F') (R U R' U') (R U R')")
		}, 
		{ // L1
			Algorithm("F' (L' U' L U) (L' U' L U) F"),
			Algorithm("R' U' (R' F R F') (R' F R F') U R")
		}, 
		{ // L2
			Algorithm("F (R U R' U') (R U R' U') F'")
		}, 
		{ // L3
			Algorithm("r U' r2' U r2 U r2' U' r") 
		}, 
		{ // L4
			Algorithm("r' U r2 U' r2' U' r2 U r'"),
			Algorithm("(R U2 R' U' R U' R') F (R U R' U') F'")
		}, 
		{ // L5
			Algorithm("(r' U' R U') (R' U R U') R' U2 r"),
			Algorithm("r' U2' R (U R' U' R) (U R' U r)")
		}, 
		{ // L6
			Algorithm("(r U R' U) (R U' R' U) R U2' r'"),
			Algorithm("(r U2 R' U') (R U R' U') R U' r'")
		}, 
		{ // B1
			Algorithm("(r U R' U R U2' r')") 
		}, 
		{ // B2
			Algorithm("(r' U' R U' R' U2 r)"),
			Algorithm("l' U' L U' L' U2 l")
		}, 
		{ // B3
			Algorithm("r' (R2 U R' U R U2 R') U M'") 
		}, 
		{ // B4
			Algorithm("M' (R' U' R U' R' U2 R) U' M"),
			Algorithm("F (R U R' U') F' U F (R U R' U') F'")
		}, 
		{ // B5
			Algorithm("(L F') (L' U' L U) F U' L'"),
			Algorithm("F (R U R' U') F' (R' U' R U' R' U2 R)")
		}, 
		{ // B6
			Algorithm("(R' F) (R U R' U') F' U R") 
		}, 
		{ // O1
			Algorithm("(R U2') (R2' F R F') U2' (R' F R F')") 
		}, 
		{ // O2
			Algorithm("F (R U R' U') F' f (R U R' U') f'"),
			Algorithm("(r U r') U2 R U2' R' U2 (r U' r')")
		}, 
		{ // O3
			Algorithm("f (R U R' U') f' U' F (R U R' U') F'") 
		}, 
		{ // O4
			Algorithm("f (R U R' U') f' U F (R U R' U') F'") 
		}, 
		{ // O5
			Algorithm("(R U R' U) (R' F R F') U2' (R' F R F')") 
		}, 
		{ // O6
			Algorithm("R U2' (R2' F R F') U2' M' (U R U' r')"),
			Algorithm("(r U R' U R U2 r') (r' U' R U' R' U2 r)")
		}, 
		{ // O7
			Algorithm("M U (R U R' U') M' (R' F R F')") 
		}, 
		{ // O8
			Algorithm("M U (R U R' U') M2' (U R U' r')"),
			Algorithm("(r U R' U') M2' (U R U' R') U' M'")
		} 
	};

	// Static Array with all possible OLL masks (58 possibilities in 4 orientations).
	const M16 CFOP::OLL_Masks[4][58] =
	{
		{ // No turn
			0x00FFu, // OLL skip
			0x550Fu, 0x990Fu, 0x05CFu, 0x445Fu, 0x249Fu, 0x864Fu, 0x612Fu, // All edges oriented correctly
			0x445Cu, 0x885Cu, // T shapes
			0x6815u, 0x8646u, // Squares
			0xA03Cu, 0x22A3u, // C shapes
			0x2499u, 0x426Au, // W shapes
			0x00FAu, 0x00FCu, // Corners correct, edges flipped
			0x4456u, 0x4455u, 0x22A9u, 0x8855u, // P shapes
			0x990Cu, 0x6603u, 0xAA03u, 0xAA0Cu, // I shapes
			0x941Au, 0x4949u, 0x2495u, 0x249Au, // Fish shapes
			0x612Cu, 0x941Cu, 0x681Cu, 0x864Cu, // Knight move shapes
			0x0AC9u, 0x11A6u, 0x503Au, 0x05C9u, // Awkward shapes
			0x6606u, 0x990Au, 0x9906u, 0x9905u, 0xAA05u, 0xAA06u, // L shapes
			0x612Au, 0x1689u, 0x6125u, 0x1686u, 0x426Cu, 0x189Cu, // Lightning bolts
			0xAA00u, 0x9900u, 0x6810u, 0x8640u, 0x1890u, 0x05C0u, 0x0AC0u, 0x00F0u // No edges flipped correctly
		},
		{ // y turn
			0x00FFu, // OLL skip
			0xAA0Fu, 0xA50Fu, 0x22AFu, 0x0ACFu, 0x426Fu, 0x168Fu, 0x681Fu, // All edges oriented correctly
			0x0AC3u, 0x05C3u, // T shapes
			0x4946u, 0x168Au, // Squares
			0x4453u, 0x503Cu, // C shapes
			0x4265u, 0x1899u, // W shapes
			0x00F9u, 0x00F3u, // Corners correct, edges flipped
			0x0ACAu, 0x0AC6u, 0x5035u, 0x05C6u, // P shapes
			0xA503u, 0x5A0Cu, 0x550Cu, 0x5503u, // I shapes
			0x8649u, 0x2985u, 0x4266u, 0x4269u, // Fish shapes
			0x6813u, 0x8643u, 0x4943u, 0x1683u, // Knight move shapes
			0x11A5u, 0xA03Au, 0x8859u, 0x22A5u, // Awkward shapes
			0x5A0Au, 0xA509u, 0xA50Au, 0xA506u, 0x5506u, 0x550Au, // L shapes
			0x6819u, 0x9225u, 0x6816u, 0x922Au, 0x1893u, 0x8163u, // Lightning bolts
			0x5500u, 0xA500u, 0x4940u, 0x1680u, 0x8160u, 0x22A0u, 0x11A0u, 0x00F0u // No edges flipped correctly
		},
		{ // y2 turn
			0x00FFu, // OLL skip
			0x550Fu, 0x660Fu, 0x503Fu, 0x11AFu, 0x189Fu, 0x922Fu, 0x494Fu, // All edges oriented correctly
			0x11ACu, 0x22ACu, // T shapes
			0x298Au, 0x9229u, // Squares
			0x0ACCu, 0x8853u, // C shapes
			0x1896u, 0x8165u, // W shapes
			0x00F5u, 0x00FCu, // Corners correct, edges flipped
			0x11A9u, 0x11AAu, 0x8856u, 0x22AAu, // P shapes
			0x660Cu, 0x9903u, 0xAA03u, 0xAA0Cu, // I shapes
			0x1685u, 0x6126u, 0x189Au, 0x1895u, // Fish shapes
			0x494Cu, 0x168Cu, 0x298Cu, 0x922Cu, // Knight move shapes
			0xA036u, 0x4459u, 0x05C5u, 0x5036u, // Awkward shapes
			0x9909u, 0x6605u, 0x6609u, 0x660Au, 0xAA0Au, 0xAA09u, // L shapes
			0x4945u, 0x9416u, 0x494Au, 0x9419u, 0x816Cu, 0x249Cu, // Lightning bolts
			0xAA00u, 0x6600u, 0x2980u, 0x9220u, 0x2490u, 0x5030u, 0xA030u, 0x00F0u // No edges flipped correctly
		},
		{ // y' turn
			0x00FFu, // OLL skip
			0xAA0Fu, 0x5A0Fu, 0x885Fu, 0xA03Fu, 0x816Fu, 0x941Fu, 0x298Fu, // All edges oriented correctly
			0xA033u, 0x5033u, // T shapes
			0x6129u, 0x9415u, // Squares
			0x11A3u, 0x05CCu, // C shapes
			0x816Au, 0x2496u, // W shapes
			0x00F6u, 0x00F3u, // Corners correct, edges flipped
			0xA035u, 0xA039u, 0x05CAu, 0x5039u, // P shapes
			0x5A03u, 0xA50Cu, 0x550Cu, 0x5503u, // I shapes
			0x9226u, 0x681Au, 0x8169u, 0x8166u, // Fish shapes
			0x2983u, 0x9223u, 0x6123u, 0x9413u, // Knight move shapes
			0x445Au, 0x0AC5u, 0x22A6u, 0x885Au, // Awkward shapes
			0xA505u, 0x5A06u, 0x5A05u, 0x5A09u, 0x5509u, 0x5505u, // L shapes
			0x2986u, 0x864Au, 0x2989u, 0x8645u, 0x2493u, 0x4263u, // Lightning bolts
			0x5500u, 0x5A00u, 0x6120u, 0x9410u, 0x4260u, 0x8850u, 0x4450u, 0x00F0u // No edges flipped correctly
		}
	};

	// Array with OLL cases string representation
	const std::string CFOP::OLL_Strings[58] =
	{
		"SKIP", // OLL skip
		"OCLL1", "OCLL2", "OCLL3", "OCLL4", "OCLL5", "OCLL6", "OCLL7", // All edges oriented correctly
		"T1", "T2", // T shapes
		"S1", "S2",	// Squares
		"C1", "C2", // C shapes
		"W1", "W2", // W shapes
		"E1", "E2", // Corners correct, edges flipped
		"P1", "P2", "P3", "P4", // P shapes
		"I1", "I2", "I3", "I4", // I shapes
		"F1", "F2", "F3", "F4", // Fish shapes
		"K1", "K2", "K3", "K4", // Knight move shapes
		"A1", "A2", "A3", "A4", // Awkward shapes
		"L1", "L2", "L3", "L4", "L5", "L6", // L shapes
		"B1", "B2", "B3", "B4", "B5", "B6", // Lightning bolts
		"O1", "O2", "O3", "O4", "O5", "O6", "O7", "O8" // No edges flipped correctly
	};

	// Static array with PLL solve algorithms (by case)
	const std::vector<Algorithm> CFOP::PLL_Algorithms[22] =
	{
		{ // Skip
			Algorithm()
		},
		{ // Ua
			Algorithm("(R2 U' R' U') (R U R U) (R U' R)"),
			Algorithm("(R U' R U) R U (R U' R' U') R2"),
			Algorithm("(R U R' U) (R' U' R2 U') R' U R' U R (U2)")
		},
		{ // Ub
			Algorithm("(R' U R' U') (R' U' R' U) (R U R2)"),
			Algorithm("R2 U (R U R' U') R' U' (R' U R')")
		},
		{ // Z
			Algorithm("(M2 U' M2 U') (M' U2) (M2 U2) (M' U2)"),
			Algorithm("M' U (M2' U M2') U (M' U2 M2) (U')")
		},
		{ // H
			Algorithm("(M2 U') (M2 U2) (M2 U') M2"),
		},
		{ // Aa
			Algorithm("L' (B L' F2 L) (B' L' F2 L2)"),
			Algorithm("x (R' U R') D2 (R U' R') D2 R2"),
			Algorithm("x' R2 D2 (R' U' R) D2 (R' U R')")
		},
		{ // Ab
			Algorithm("(L2 F2 L B) (L' F2 L B') L"),
			Algorithm("x R2' D2 (R U R') D2 (R U' R)"),
			Algorithm("x' (R U' R) D2 (R' U R) D2 R2'")
		},
		{ // E
			Algorithm("(R' U L') D2 (L U' R) (L' U R') D2 (R U' L)"),
			Algorithm("x' (R U' R' D) (R U R' D') (R U R' D) (R U' R' D')")
		},
		{ // Ra
			Algorithm("(U R) (U2 R' U2 R) (B' R' U' R) (U R B R2)"),
			Algorithm("(R U' R' U') (R U R D) (R' U' R D') (R' U2 R') (U')"),
			Algorithm("(L U2 L' U2) L F' (L' U' L U) L F L2' (U)"),
			Algorithm("(R U R' F') (R U2' R' U2') (R' F R U) (R U2' R') U'")
		},
		{ // Rb
			Algorithm("(R' U2 R U2) (R' F) (R U R' U') (R' F' R2 U')"),
			Algorithm("(R' U2 R' D') (R U' R' D) (R U R U') (R' U' R) (U')")
		},
		{ // Ja
			Algorithm("(R' U2 R U) (R' U2 L U') (R U L')"),
			Algorithm("(R' U L' U2) (R U' R' U2 R) L (U')"),
			Algorithm("(L' U' L F) (L' U' L U) L F' L2' U L (U)")
		},
		{ // Jb
			Algorithm("(R U R' F') (R U R' U') (R' F R2 U') (R' U')")
		},
		{ // T
			Algorithm("(R U R' U') (R' F R2 U') R' U' (R U R' F')")
		},
		{ // F
			Algorithm("(U' R' U R) (U' R2) (F' U' F U) (R F R' F') R2"),
			Algorithm("(R' U' F') (R U R' U') (R' F R2 U') (R' U' R U) (R' U R)"),
			Algorithm("(R' U2 R' U') y (R' F' R2 U') (R' U R' F) R U' F")
		},
		{ // V
			Algorithm("(R U' R U) x (U F' U F) (U2 R U) (R' U' R')"),
			Algorithm("(R' U R' U') y (R' F' R2 U') (R' U R' F) R F")
		},
		{ // Y
			Algorithm("(U' B' R B) (R' U' R' U) (R2 U R' U') (R' F R F')"),
			Algorithm("F (R U' R' U') (R U R' F') (R U R' U') (R' F R F')")
		},
		{ // Na
			Algorithm("U' (L U' R ) U2 (L' U R' ) (L U' R ) U2 (L' U R' )"),
			Algorithm("(R U R' U) (R U R' F') (R U R' U') (R' F R2 U') R' U2 (R U' R')"),
			Algorithm("z (U R' D) (R2 U' R D') (U R' D) (R2 U' R D') (R')")
		},
		{ // Nb
			Algorithm("U (R' U L' ) U2 (R U' L ) (R' U L' ) U2 (R U' L )"),
			Algorithm("(R' U R U') (R' F' U' F) (R U R' F) R' F' (R U' R)"),
			Algorithm("(R' U L' U2 R U' L) (R' U L' U2 R U' L) (U)")
		},
		{ // Ga
			Algorithm("R2' (u R' U R') (U' R u' R2') y' (R' U R)"),
			Algorithm("R2 U (R' U R' U') (R U' R2) D U' (R' U R D') (U)"),
			Algorithm("R2 u (R' U R' U') R u' R2 y' (R' U R)")
		},
		{ // Gb
			Algorithm("(R' U' R) y (R2 u R' U) (R U' R u') R2"),
			Algorithm("(F' U' F) (R2 u R' U) (R U' R u') R2'"),
			Algorithm("R' U' y F (R2 u R' U) (R U' R u') R2'"),
			Algorithm("D (R' U' R U) D' (R2 U R' U) (R U' R U') R2' (U')")
		},
		{ // Gc
			Algorithm("(R2 u' R U') (R U R' u) R2 y (R U' R')"),
			Algorithm("R2 U' (R U' R U) (R' U R2 D') (U R U' R') D (U')"),
			Algorithm("R2' F2 (R U2' R U2') R' F (R U R' U') R' F R2")
		},
		{ // Gd
			Algorithm("(R U R') y' (R2 u' R U') (R' U R' u) R2"),
			Algorithm("D' (R U R' U') D (R2 U' R U') (R' U R' U) R2 (U)"),
			Algorithm("(R U R') y' (R2 u' R U') (R' U R' u) R2")
		}	
	};

	// Static Array with all possible PLL masks for last layer solved pieces (22 possibilities in 4 orientations).
	const M16 CFOP::PLL_Masks[4][22] =
	{
		{ // No turn
			0xE4E4u, // SKIP
			0xE436u, // Ua
			0xE487u, // Ub
			0xE44Eu, // Z
			0xE4B1u, // H
			0x87E4u, // Aa
			0x36E4u, // Ab
			0x4EE4u, // E
			0xC66Cu, // Ra
			0xB4C6u, // Rb
			0xB46Cu, // Ja
			0xC6C6u, // Jb
			0xC6B4u, // T
			0xC6E1u, // F
			0xD8C6u, // V
			0x276Cu, // Y
			0xD8B4u, // Na
			0x27B4u, // Nb
			0x9C9Cu, // Ga
			0x7878u, // Gb
			0x6387u, // Gc
			0x9C2Du  // Gd
		},
		{ // y turn
			0xE4E4u, // SKIP
			0xE4D2u, // Ua
			0xE4C9u, // Ub
			0xE41Bu, // Z
			0xE4B1u, // H
			0x9CE4u, // Aa
			0x78E4u, // Ab
			0xB1E4u, // E
			0xB427u, // Ra
			0x6CD8u, // Rb
			0x6C27u, // Ja
			0xB4D8u, // Jb
			0xB4E1u, // T
			0xB4B4u, // F
			0x27D8u, // V
			0xD827u, // Y
			0x27E1u, // Na
			0xD8E1u, // Nb
			0x2D2Du, // Ga
			0x6363u, // Gb
			0xD2C9u, // Gc
			0x2D36u  // Gd
		},
		{ // y2 turn
			0xE4E4u, // SKIP
			0xE49Cu, // Ua
			0xE478u, // Ub
			0xE44Eu, // Z
			0xE4B1u, // H
			0x2DE4u, // Aa
			0x63E4u, // Ab
			0x4EE4u, // E
			0x6CC6u, // Ra
			0xE16Cu, // Rb
			0xE1C6u, // Ja
			0x6C6Cu, // Jb
			0x6CB4u, // T
			0x6CE1u, // F
			0xD86Cu, // V
			0x27C6u, // Y
			0xD8B4u, // Na
			0x27B4u, // Nb
			0xC936u, // Ga
			0xD287u, // Gb
			0x3678u, // Gc
			0xC9D2u  // Gd
		},
		{ // y' turn
			0xE4E4u, // SKIP
			0xE42Du, // Ua
			0xE463u, // Ub
			0xE41Bu, // Z
			0xE4B1u, // H
			0xC9E4u, // Aa
			0xD2E4u, // Ab
			0xB1E4u, // E
			0xE1D8u, // Ra
			0xC627u, // Rb
			0xC6D8u, // Ja
			0xE127u, // Jb
			0xE1E1u, // T
			0xE1B4u, // F
			0x2727u, // V
			0xD8D8u, // Y
			0x27E1u, // Na
			0xD8E1u, // Nb
			0x87D2u, // Ga
			0x36C9u, // Gb
			0x7863u, // Gc
			0x879Cu  // Gd
		}
	};

	// Array with PLL cases string representation
	const std::string CFOP::PLL_Strings[22] =
	{
		"SKIP", // PLL skip
		"Ua", "Ub", "Z", "H", // Permutations of edges only
		"Aa", "Ab", "E", // Permutations of corners only
		"Ra", "Rb", "Ja", "Jb", "T", "F", // Swap one set of adjacent corners
		"V", "Y", "Na", "Nb", // Swap one set of diagonal corners
		"Ga", "Gb", "Gc", "Gd" // G permutations (double cycles)
	};

    // Static vector with 1LLL solve algorithms
    std::vector<Algorithm> CFOP::Algorithms_1LLL =
    {
        Algorithm("(U') R U R' U R U2 R' U2 R' U' R U' R' U2 R"),
        Algorithm("(U2) R U2 R2 U' R2 U' R2 U2 R U2 R U R' U R U2 R'"),
        Algorithm("(U2) R' U2 R U R' U R2 U2 R' U' R U' R'"),
        Algorithm("R U2 R' U' R U' R2 U2 R U R' U R"),
        Algorithm("R' U R U2 R' U' R U2 R' U' R U' R' U R"),
        Algorithm("(U') R' U' R U' R' U2 R U R' U2 R U R' U R"),
        Algorithm("R' U R2 U R' U R' U' R U' R' U' R U R U' R'"),
        Algorithm("(U') R U R' U R U' R' U R' U' R2 U' R2 U2 R"),
        Algorithm("(U2) R' U2 R U R' U R U' R' U' R U' R' U2 R"),
        Algorithm("R U2 R' U' R U' R' U R U R' U R U2 R'"),
        Algorithm("(U') R' U' R2 U R2 U R2 U2 R' U R' U R"),
        Algorithm("(U') R U R2 U' R2 U' R2 U2 R U' R U' R'"),
        Algorithm("(U) R U R' U R U R2 D' r U2 r' D R2 U R'"),
        Algorithm("(U) R' U' R U' R' U' R2 D r' U2 r D' R2 U' R"),
        Algorithm("(U2) R U' R2 D' r U2 r' D R2 U R'"),
        Algorithm("R' U R2 D r' U2 r D' R2 U' R"),
        Algorithm("R' U' R U2 R D R' U' R D' R2 U R U' R' U R"),
        Algorithm("(U2) R U R' U2 R' D' R U R' D R2 U' R' U R U' R'"),
        Algorithm("R' U' R U R2 D' R U2 R' D R2 U2 R' U2 R"),
        Algorithm("(U') R2 U' R U F' U2 R' U2 R F U' R"),
        Algorithm("(U2) R U' R' U2 R D' R U R' U2 R U R' D R'"),
        Algorithm("F U' R2 U R' U R U2 R2 U' R U2 R' F'"),
        Algorithm("(U) R U R D R' U R D' R' U L' U R' U' L"),
        Algorithm("(U) r U r' R U R' U' R U R' U' r U' r' F R U R' U' F'"),
        Algorithm("R' U R U2 L' R' U R U' L"),
        Algorithm("(U2) R U' R' U2 L R U' R' U L'"),
        Algorithm("(U2) R' U' R2 U R' F' R U R' U' R' F R2 U' R' U' R' U R"),
        Algorithm("(U2) r U' r U2 R' F R U2 r2 F"),
        Algorithm("(U') R' F' U F U R U R2 F R F' R"),
        Algorithm("(U) R U R2 F R F' R U' R' F' U F"),
        Algorithm("(U) L' U2 R U2 R' U2 L U R U R' U' R U' R'"),
        Algorithm("(U2) F U R U2 R' U R U R' F' R' U2 R U R' U R"),
        Algorithm("(U2) R' U' R U' R' U R F U' R' U2 R U F'"),
        Algorithm("R U R' U R U' R' U' L' U2 R U2 R' U2 L"),
        Algorithm("R' U2 R U R' U R F U R U2 R' U R U R' F'"),
        Algorithm("r' U' l' U2 R U' R' U2 l R U' R' U2 r"),
        Algorithm("(U') l' U2 R' D2 R U2 R' D2 R2 x'"),
        Algorithm("R' U2 R U' R' F R U R' U' R' F' R U' R"),
        Algorithm("R' U2 R' D' R U2 R' D R' U R' U R U2 R'"),
        Algorithm("(U2) R U2 R D R' U2 R D' R U' R U' R' U2 R"),
        Algorithm("(U) R U R' U R U2 R' U r U R' U' r' F R F'"),
        Algorithm("(U) R' U' F' U F R U' R' F R U R' U' F' U R"),
        Algorithm("r U R' U' r' F R F' R' U2 R U R' U R"),
        Algorithm("(U2) R U' R2 D' R U' R' D R U' R U R' U R U R'"),
        Algorithm("(U) R' U' R U' F U' R' U R U F' R' U R"),
        Algorithm("R' D' R U R' D R2 U R' U2 R U' R' U' R U' R'"),
        Algorithm("(U2) F R U R' U' R U' R' U' R U R' F'"),
        Algorithm("r U2 R2 F R F' U2 r' F R U R U' R' F'"),
        Algorithm("(U') r U R' U' r' F R F'"),
        Algorithm("(U') R U2 R' U2 R' F R U R U' R' F'"),
        Algorithm("R U R D R' U R r' U2 r D' R2"),
        Algorithm("(U') R' D' R U R' D R2 U' R' U R U R' U' R U R'"),
        Algorithm("(U') F' U' r' F2 r U' r' F' r F"),
        Algorithm("(U') R U R' U' R U' R' L U' R U R' L'"),
        Algorithm("(U) R U R' U R U R' U2 L R U' R' U L'"),
        Algorithm("R' U' R U' R2 F' R U R U' R' F U R U' R' U2 R"),
        Algorithm("(U') R U' R' U R' D' r U2 r' D R U R U R'"),
        Algorithm("(U') r U' r' U' r F R U' R' F' r' U F"),
        Algorithm("(U2) F R U R' U' R' F' U2 R U R U' R2 U2 R"),
        Algorithm("(U') R U' R' U2 M' F' U2 F M"),
        Algorithm("(U) l' U' L U l F' L' F"),
        Algorithm("(U) R U R' U' R' F' R U2 R U2 R' F"),
        Algorithm("R2 F2 R U2 R U2 R' F2 R U' R' U R"),
        Algorithm("(U') R D R' U' R D' R2 U R U' R' U' R U R' U' R"),
        Algorithm("(U) F U R U2 R' U R U R' F'"),
        Algorithm("R U R' U' R U' R' U' F R U R' U' R' F' R"),
        Algorithm("(U) R' U' R U' R' U' R U2 L' R' U R U' L"),
        Algorithm("(U) F R U R' U' R U R' U' F' R U R' U' R' F R F'"),
        Algorithm("(U') F U R' U' R F' R' U' R U R' U R"),
        Algorithm("R' U2 R F U' R' U R U F' R' U R"),
        Algorithm("(U) R' U2 R2 U R' U' R' U2 F' R U2 R U2 R' F"),
        Algorithm("(U') R' U R U R' U' R' D' R U2 R' D R U R"),
        Algorithm("(U) R U2 R' U' R U' R' U2 R' U2 R U R' U R"),
        Algorithm("R U R' U' R U' R U2 R2 U' R U R' U' R2 U' R2"),
        Algorithm("R' U' R U' R' U2 R2 U R' U R U2 R'"),
        Algorithm("(U2) R U R' U R U2 R2 U' R U' R' U2 R"),
        Algorithm("(U') R U R' U' R U' R' U2 R U' R' U2 R U R'"),
        Algorithm("(U') R' U' R U R' U R U2 R' U R U2 R' U' R"),
        Algorithm("(U) R U2 R2 U' R2 U' R' U R' U' R U R' U R"),
        Algorithm("(U) R' U2 R2 U R2 U R U' R U R' U' R U' R'"),
        Algorithm("(U) R' U2 R U R' U R U R' U' R U' R' U2 R"),
        Algorithm("(U) R U2 R' U' R U' R' U' R U R' U R U2 R'"),
        Algorithm("R' U' R U' R U R' U R U2 R' U2 R' U2 R"),
        Algorithm("(U2) R U R' U R' U' R U' R' U2 R U2 R U2 R'"),
        Algorithm("(U2) R' U' R U' F U' R' U R U R' U R U' F'"),
        Algorithm("R U R' U L' U R U' M' x' U' R U' R'"),
        Algorithm("(U') F R U R' U' R U R' U' F' U2 F R U R' U' F'"),
        Algorithm("(U') R' U2 R F U' R' U R U R' U R U' F'"),
        Algorithm("(U2) R2 D R' U' R D' R' U' R' U R U R'"),
        Algorithm("R' U2 R F U' R' U' R U F'"),
        Algorithm("R U' R' U' R U R D R' U R D' R2"),
        Algorithm("(U') F U' R' U R U F' R' U2 R"),
        Algorithm("M' U R' U' F' U F R2 U R' U R U2 r'"),
        Algorithm("(U') F R U R' U' R U R' U' F' U' R' F' U' F U R"),
        Algorithm("F R U' R' U' R U2 R' U' R U' R' U' R U2 R' U' F'"),
        Algorithm("(U) r' U' R' F R U r F R U' R' F'"),
        Algorithm("R' F R U' R' U' R U R' F' R U R' U' R' F R F' R"),
        Algorithm("(U') F2 R U' R' U' R U R' F' R U R' U' R' F R F2"),
        Algorithm("R U' R' U R U' L U r' F U2 R U2 R2 x"),
        Algorithm("(U) R' U R U R' F' R U R' U' R' F R2 U' R' U2 R U' R' U2 R"),
        Algorithm("(U) R U' L U L' U R' U' l U2 R U2 R2 x"),
        Algorithm("(U) R' U L' U' L U' R U l' U2 R' U2 R2 x'"),
        Algorithm("F R U R U2 R' U' R U' R' U2 R' U2 R U' R' U' F'"),
        Algorithm("(U') r U R' U' r' F R2 U' R' U' R U2 R' U' F'"),
        Algorithm("(U') R U R' U R U' R2 F R F' R U' R' U' F' U2 F"),
        Algorithm("(U') R U2 R' U2 R' F R U R U2 R' U' R U2 R' U' F'"),
        Algorithm("(U') R' U' R F R2 D' R U R' D R2 U' F'"),
        Algorithm("(U') r U R' U' r' F R U R' U' R F' R' U R"),
        Algorithm("x R2 U2 R' D2 R U2 R' D2 R' x'"),
        Algorithm("(U) F' R U2 R' U2 R' F R U2 R U2 R'"),
        Algorithm("R U R' U R U' R' U2 R' D' R U2 R' D R2 U' R'"),
        Algorithm("(U') R' U2 R U R' U R' D R' U2 R D' R' U2 R'"),
        Algorithm("(U') R U' R' U' R U' R' U R' D' R U R' D R2 U R'"),
        Algorithm("(U') R' U R U R' U R U' R D R' U' R D' R2 U' R"),
        Algorithm("R' U2 R U R' U R' D' R U' R' D R U R"),
        Algorithm("R U' R' U' R U2 R' U2 R' D' R U' R' D R"),
        Algorithm("R' U' R U2 R' F' R U R' U' R' F R2 U2 R' U R"),
        Algorithm("(U2) R U R' U R U R' U2 R U' R2 D' R U' R' D R"),
        Algorithm("F R U' R' U R U R' U R U' R' F'"),
        Algorithm("(U) F' R U R' U' R' F R2 U R' U2 R U R' U2 R U' R'"),
        Algorithm("R2 D' r U2 r' D R U2 R"),
        Algorithm("R2 D' R U2 R' D R U2 R"),
        Algorithm("R U' R' D R' U' R D' R2 U R' U' R' U2 R'"),
        Algorithm("(U2) R U R' U R U2 R' U2 r' F R F' r U R'"),
        Algorithm("(U) R2 D' R U' R' D R2 U' R' U2 R"),
        Algorithm("(U') R' U R U R' U2 R U2 y R U' R' U2 R U' R'"),
        Algorithm("R' U2 R U' R' U' R2 D r' U2 r D' R2 U R"),
        Algorithm("(U) F' r U2 R' U' R U' r' F R U R' U R U' R'"),
        Algorithm("(U) F U R U2 R' U R U2 R2 F R F' R U' R' F'"),
        Algorithm("(U) R' U' R U' R' U R U' R' U R F R' U R U' F'"),
        Algorithm("(U2) L' U R U' L U R' U2 R U R' U R U2 R'"),
        Algorithm("(U') R' U R U' R' U' R U2 R D R' U' R D' R2 U' R"),
        Algorithm("(U2) R2 D r' U2 r D' R' U2 R'"),
        Algorithm("(U2) R2 D R' U2 R D' R' U2 R'"),
        Algorithm("R' U' R U R U R' U' R' U F R U R U' R' F'"),
        Algorithm("R U' R' U' R U2 R' U' R' D' R U2 R' D R"),
        Algorithm("(U) R U R2 D' R U R' D R2 U2 R'"),
        Algorithm("(U') R U' R' U' R U2 R' U2 y' R' U R U2 R' U R"),
        Algorithm("(U) R' U R' U' D' R U' R' U2 R U' R' D R U' R"),
        Algorithm("(U') R U R' U R U' R' U F' R U2 R' U2 R' F R"),
        Algorithm("(U') R U2 R2 D' R U2 R' D R2 U' R' U2 R U2 R'"),
        Algorithm("(U) R U R' U R U' R' U R U' R' U' L' U R U' R' L"),
        Algorithm("(U') R U2 R D R' U2 R D' R' U2 R' U' R U' R'"),
        Algorithm("(U') R U' R' U R U R' U2 R' D' R U R' D R2 U R'"),
        Algorithm("R U2 R' U2 R' U' R U R U' R' U2 R' U2 R"),
        Algorithm("R U R' U R U' R' U R U' R' U R U2 R'"),
        Algorithm("(U2) R U2 R' U' R U' R' U2 R U R' U R U2 R'"),
        Algorithm("(U2) R U R' U R U2 R' U2 R U2 R' U' R U' R'"),
        Algorithm("R U R' U R U2 R' U R' U2 R U R' U' R U R' U R"),
        Algorithm("(U') R U R' U R U' R' U R U2 R' R' U' R U' R' U2 R"),
        Algorithm("(U) R' U2 R U R' U R U' R U2 R' U' R U' R'"),
        Algorithm("(U2) R U2 R' U' R U' R' U R' U2 R U R' U R"),
        Algorithm("(U) R2 U R' U' R' U R U R' U R U' R U' R2"),
        Algorithm("(U2) R2 U' R U R U' R' U' R U' R' U R' U R2"),
        Algorithm("(U2) R U R' U R U2 R' U R' U' R U' R' U2 R"),
        Algorithm("(U) R' U' R U' R' U2 R U' R U R' U R U2 R'"),
        Algorithm("(U') r U R' U R U2 r' U R U2 R2 F R F' U' R U' R'"),
        Algorithm("(U2) F R U R2 F R F' R U' R' F'"),
        Algorithm("L' U2 R U' R' U2 L R U' R'"),
        Algorithm("R' U' R U R' F' R U R' U' R' F R2"),
        Algorithm("F R U R' U' R' F R2 U' R' U' R U R' F2"),
        Algorithm("R' U' R U R' U' R' F R2 U' R' U' R U R' F' U R"),
        Algorithm("(U) r U2 R r2 F R' F' r2 U2 r'"),
        Algorithm("(U2) r U2 r2 F R F' r2 R' U2 r'"),
        Algorithm("(U2) F R U R' U' F' r U r' U R U' R' r U' r'"),
        Algorithm("(U) r U r' R U R' U' r U' r' F U R U' R' F'"),
        Algorithm("(U') R U R' U R U' R' F2 R U2 R' U2 R' F2 R2 U' R'"),
        Algorithm("R U R2 F2 R U2 R U2 R' F2 R U R' U' R U' R'"),
        Algorithm("(U') F' r U R' U' r' F R"),
        Algorithm("R' U' R U R' F2 R U2 R' U2 R' F2 R2"),
        Algorithm("(U') F' R U2 R' U2 R' F R U R U' R'"),
        Algorithm("(U) R' U R U' R' U R U R' U' R2 D R' U R D' R'"),
        Algorithm("F R U' R' U' R U2 R' U' F'"),
        Algorithm("(U2) R' U' R U2 R' F' R U R' U' R' F R2 U R' U2 R"),
        Algorithm("R' F R U R U' R' F' U R U R' U R U' R'"),
        Algorithm("R' U R U2 r' R' F R F r U r' F r"),
        Algorithm("(U) F R' F' R U R U' R' F U R U' R' U R U' R' F'"),
        Algorithm("(U') F' R U2 R' U2 R' F U2 R U R U' R2 U2 R"),
        Algorithm("(U2) R' U' R U' R' U R F R' U R U' F'"),
        Algorithm("(U') R U2 R' U r' F R F' M' U' R U R'"),
        Algorithm("(U2) F R' F' r U R U' r'"),
        Algorithm("(U) D' R2 U R' U' R' U R' D U' R' U R"),
        Algorithm("(U2) F R U R' U' R' F' R U2 R U2 R'"),
        Algorithm("(U2) R D' R U' R' D R U' R2 U R2 U R2"),
        Algorithm("R' F' R U R' U' R' F R U' R U R' U R"),
        Algorithm("r' F' r U R' U2 R U R' U r' F r U' R"),
        Algorithm("(U) L R U' R' U R L' U R' U R U' R'"),
        Algorithm("(U') R' U' R' F R F' U R2 U2 R' U2 R' F R F'"),
        Algorithm("(U) R' U2 R U R' U' F' R U R' U' R' F R2 U R' U R"),
        Algorithm("(U) R' U2 R2 U R' U' R' U2 F R U R U' R' F'"),
        Algorithm("(U) R U R' U R U2 R' r U R' U' r' F R F'"),
        Algorithm("(U) M' F' U2 F M U2 R U R'"),
        Algorithm("(U) R' U2 R' D' R U2 R' D R2"),
        Algorithm("(U) R' U2 R' D' r U2 r' D R2"),
        Algorithm("(U2) R D R' U2 R D' R' U' R' U2 R U' R' U' R"),
        Algorithm("R' U' R U2 R' U' R2 D r' U2 r D' R2 U R"),
        Algorithm("(U) R U R' U2 R U R' U2 y' R' U2 R U' R' U' R"),
        Algorithm("R' U2 R U R2 D' R U R' D R2"),
        Algorithm("(U) R U R' U' R U' R' F' r U R' U R U2 r' F"),
        Algorithm("R' U' R2 D r' U2 r D' R2 U R U R' U2 R"),
        Algorithm("(U) R' U2 R U2 R' U' R2 D R' U2 R D' R2 U2 R"),
        Algorithm("(U2) F' R U R' U' R' F R2 U' R' U' R U' R' U R U R'"),
        Algorithm("F R U' R' U' R2 D R' U R D' R' U R' U' F'"),
        Algorithm("(U) R' U R2 D R' U R D' R' U2 R' U R U R' U' R"),
        Algorithm("(U2) R U2 R D R' U2 R D' R2"),
        Algorithm("(U) R' F' R U R' U' R' F R2 U' R' U2 R"),
        Algorithm("(U') L' U R U' L U R2 U2 R U R' U R"),
        Algorithm("(U') F R U R' U' R' F' U' R U R U' R' U' R' U R"),
        Algorithm("(U2) R' U' R U2 R' U' R y U2 R U2 R' U R U R'"),
        Algorithm("(U') R U2 R' U' R2 D R' U' R D' R2"),
        Algorithm("(U') R' F' R U2 R U2 R' F U' R U R' U' R U' R'"),
        Algorithm("(U2) R' U R' D' R U R' U2 R U R' D U R U' R"),
        Algorithm("(U2) R U2 R' U2 R U R2 D' R U2 R' D R2 U2 R'"),
        Algorithm("(U) R' U2 R U R' U R L' U R U' L U R'"),
        Algorithm("(U) R U2 R' U R' F2 R F2 R U R' U r' F r"),
        Algorithm("(U2) R U' R2 D' R U' R' D R U2 R U' R' U' R U R'"),
        Algorithm("R U2 R' U' R U' R' U' R' U' R U' R' U2 R"),
        Algorithm("R' U2 R U R' U R U R U R' U R U2 R'"),
        Algorithm("(U) R' U' R U' R' U R U' R' U2 R"),
        Algorithm("(U') R U R' U R U' R' U R U2 R'"),
        Algorithm("R' U2 R U R' U' R U R' U R"),
        Algorithm("R U2 R' U' R U R' U' R U' R'"),
        Algorithm("(U) R U R' U R U' R' U R U' R' U R' U' R2 U' R' U R' U R"),
        Algorithm("(U) R U R' U R U2 R' U' R' U2 R U R' U R"),
        Algorithm("(U) x' U' R U' R' U R' F2 R U' R U R' U x"),
        Algorithm("F R U R' U' R U R' U' R U R' U' F'"),
        Algorithm("R U R' y' U R' U R U' R2 F R F' R"),
        Algorithm("R' U' R y U' R U' R' U R l U' R' U l'"),
        Algorithm("F R U R' U' R U R' U' F' U R' F' U' F U R"),
        Algorithm("R' U' R U' R' U2 R U R' U' R U R' F' R U R' U' R' F R2"),
        Algorithm("(U) r U2 R2 F R F' R U2 r2 F' r U' r' F2 r"),
        Algorithm("(U) R U R' U r' F R F' r U2 R2 U2 R U R' U R"),
        Algorithm("(U2) R U R' U R U2 R' F R U' R' U' R U2 R' U' F'"),
        Algorithm("R U R2 F R F' r U' r' U r U r'"),
        Algorithm("(U2) R' F R' F' R2 U' r' U r U' r' U' r"),
        Algorithm("(U) R' U' R U' R' U' L U' R U L'"),
        Algorithm("(U) R U R' U R U L' U R' U' L"),
        Algorithm("(U') R' U' R U' R' U F' R U R' U' R' F R2 U' R' U R"),
        Algorithm("(U) F R' F' R U2 R U2 R' U r' U2 R U R' U r"),
        Algorithm("(U2) R' U2 R U R2 D' R U' R' D R2 U R' U R"),
        Algorithm("R U2 R' U' R2 D R' U R D' R2 U' R U' R'"),
        Algorithm("F R U' R' U' R U2 R' U' F' U R U R' U R U2 R'"),
        Algorithm("(U') F U R' F R F' R U' R2 F' R U2 R U2 R'"),
        Algorithm("R' U2 R U R' U' F' R U R' U' R' F R U2 R"),
        Algorithm("(U2) R U R' U R U2 R' U2 F R' F' r U R U' r'"),
        Algorithm("R' U' F' U F R U R U R' U' R' F R F'"),
        Algorithm("(U2) r U2 R' U' R U' r' U R U2 R' U2 R' F R F'"),
        Algorithm("R U2 R' U L' U2 R U2 R' U2 L R U' R'"),
        Algorithm("(U') F U' R U2 R' U2 R U' R' U' R U R' U F'"),
        Algorithm("(U') R' F R U R' U' F' R U' R' U R' F R F' U R"),
        Algorithm("(U') R U2 R' U' R U' R D' R U' R' D R U R"),
        Algorithm("(U2) R U2 R2 F U' R2 U' R2 U F' U R"),
        Algorithm("(U2) R' U2 R U2 R2 F' R U R U' R' F U R"),
        Algorithm("F' R U2 R' U2 R' F R U R U R' U' R U' R'"),
        Algorithm("(U) R' U' R U' R' U R U R' F R U R' U' R' F' R2"),
        Algorithm("(U) F R U' R' U R U2 R' U' R U R' U' F'"),
        Algorithm("R U R' U R U2 R' U' R U R' U R U2 R'"),
        Algorithm("R U R' U' R' U2 R U R' U R2 U2 R'"),
        Algorithm("(U') R' U2 R U R' U R2 U R' U R U2 R'"),
        Algorithm("(U) R U2 R' U' R U' R2 U' R U' R' U2 R"),
        Algorithm("(U') R U2 R' U2 R U' R' U2 R U' R' U2 R U R'"),
        Algorithm("(U) R' U2 R U2 R' U R U2 R' U R U2 R' U' R"),
        Algorithm("(U2) R U' R' U2 R U R' U2 R U R' U2 R U2 R'"),
        Algorithm("(U2) R' U R U2 R' U' R U2 R' U' R U2 R' U2 R"),
        Algorithm("R' U2 R2 U R2 U R2 U2 R'"),
        Algorithm("R U2 R2 U' R2 U' R2 U2 R"),
        Algorithm("R U R' U' R' U' R U R U R' U' R' U R U' R U' R'"),
        Algorithm("(U) R U R' U R U2 R' U R U R' U R U2 R'"),
        Algorithm("F R2 U' R U' R U' R' U2 R' U R2 F'"),
        Algorithm("(U2) F R2 U' R U2 R U R' U R' U R2 F'"),
        Algorithm("F U R' U' R2 U' R2 U2 R U2 R U R' F'"),
        Algorithm("r' U' R U' R' U R U' R' U R' F R F' U r"),
        Algorithm("(U) R U2 R' U' F' R U2 R' U' R U' R' F R U' R'"),
        Algorithm("(U') R U R' U r' F R F' r U' R' U R U2 R'"),
        Algorithm("(U') r U R' U R' F R F' R U' R' U R U2 r'"),
        Algorithm("R' U R U F R' U R U' F' U' R' U' R"),
        Algorithm("(U2) R U2 R' U R' D' R U R' D R2 U' R' U R U' R'"),
        Algorithm("(U2) R' U2 R U' R D R' U' R D' R2 U R U' R' U R"),
        Algorithm("(U2) R U R' U R U R' U' R U R D R' U R D' R2"),
        Algorithm("(U2) R' U' R U' R' U' R U R' U' R' D' R U' R' D R2"),
        Algorithm("(U') F U R U2 R' U R U R' F' R U2 R' U' R U' R'"),
        Algorithm("r U' r' U' r U r' U' l R U' R' U l'"),
        Algorithm("r' U r U r' U' r U R2 F R F' R"),
        Algorithm("r' U' R U' R' U2 r U' R U2 R' U2 R' F R F'"),
        Algorithm("R' U' R U R2 F' R U R U' R' F U' R U R' U R"),
        Algorithm("R U2 R D' R U' R' D R' U' R2 U2 R"),
        Algorithm("R' U' R U' R2 D' R U R' D R2 U' R' U2 R"),
        Algorithm("(U2) L' U R U' L U' R' U' R U' R'"),
        Algorithm("(U') R U R' U F' R U2 R' U2 R' F R"),
        Algorithm("(U2) R' U R U' R' U R U R' U2 r' F R F' r"),
        Algorithm("(U') R2 D R' U2 R D' R2 U' R2 D R' U' R D' R2"),
        Algorithm("(U') R U2 R2 F R U R U2 R' U' R U2 R' U' F' R U R'"),
        Algorithm("(U') R U R' U R U2 R' F U R U2 R' U R U R' F'"),
        Algorithm("(U') R U R' U R U2 R2 F' r U R U' r' F"),
        Algorithm("(U') F R U' R' U' R U R' F' U2 F R U R' U' F'"),
        Algorithm("F R U R' U' R' F' R U2 R' U' R2 U' R2 U2 R"),
        Algorithm("R U R' U R' F R F' R' U' F' U F R2 U' R'"),
        Algorithm("(U') F U' R U' R' U R U R' U2 R U2 R' U F'"),
        Algorithm("(U2) R U2 R2 F R F' R' U' F' U F R U R U2 R'"),
        Algorithm("R' U' F' R U R' U' R' F R2 U2 R' U2 R"),
        Algorithm("(U') R U R' U R U' R' U' R' F' R U2 R U2 R' F"),
        Algorithm("(U2) R' U' R' D' R U R' D R' U R' U R U2 R'"),
        Algorithm("(U') R' U' F U' R2 U R2 U F' R2 U2 R'"),
        Algorithm("(U) F U R U' R' U R U2 R' U' R U R' F'"),
        Algorithm("(U2) R' U' F' U F R U' r U' r' U' r U r' F' U F"),
        Algorithm("R' F R U R' F' U' F' U F R F' r U r'"),
        Algorithm("R' F R U R' U' R' F' R2 U' R' U R U' R' U2 R"),
        Algorithm("(U) F U R U' R' F' r U' r' U' r U r' F' U F"),
        Algorithm("R U R' U R U2 R' U' R U' L' U R' U' L"),
        Algorithm("(U') R U R' U F2 R U2 R' U2 R' F2 R"),
        Algorithm("(U') R' U2 R U R' U R2 U' L' U R' U' L"),
        Algorithm("(U) R U R' U R U' R' U R U' R D R' U' R D' R2"),
        Algorithm("R U R' U' R' F R2 U R' U' R U R' U' F'"),
        Algorithm("(U') r U' r' F R' F r U R U2 r' F r U r' F"),
        Algorithm("R U2 R' U' R U R' U2 L' U R U' M' x'"),
        Algorithm("(U) r U R' U' r' F R U R' U' R F' U' R' U2 R"),
        Algorithm("(U') R U R' U R U' R2 F R F' R U' R' F' U F"),
        Algorithm("(U) F U R U2 R' U2 R U R2 F' R U2 R U2 R'"),
        Algorithm("F' U' F r U' r' U r U r' F R U R' U' F'"),
        Algorithm("(U2) R' U2 R U R' U' R U R2 F R U R U' R' F' R"),
        Algorithm("R' F2 R U2 R U2 R' F2 U' R U' R'"),
        Algorithm("(U) R' F R F' r U R' U R U2 r' U' R U' R'"),
        Algorithm("(U) R U2 R' U' R U' R' U2 r' F R F' r U R'"),
        Algorithm("(U') R' U' R U' R' U R U' R' U R' D' R U R' D R2"),
        Algorithm("(U) F U R U' R' U R U' R2 F' R U R U' R'"),
        Algorithm("(U) r U' r U' R U' R' F R U R' U r2 F"),
        Algorithm("(U2) R U2 R' U' R U R' U2 R' F' R U2 R U2 R' F"),
        Algorithm("(U) R L' U R' U' L U2 R U' R' U R U2 R'"),
        Algorithm("R' U R2 U R' U R U2 R U2 R U R' U R2"),
        Algorithm("R' U2 R2 U R U' R' U R U R2 U' R'"),
        Algorithm("(U) R U R' U R U2 R'"),
        Algorithm("R' U2 R U R' U R"),
        Algorithm("(U) R U R2 U' R2 U' R2 U2 R2 U2 R'"),
        Algorithm("(U') R' U' R U' R U R2 U R2 U2 R'"),
        Algorithm("R U R' U' R' U2 R U R U' R' U R' U R"),
        Algorithm("R' U' R U R U R' U' R' U R U R U' R'"),
        Algorithm("(U) R U R' U R U' R' U R' U' R2 U' R' U R' U R"),
        Algorithm("(U') R' U' R U' R U R' U R U2 R' U' R' U R"),
        Algorithm("(U2) R U R' U R' U' R2 U' R' U R' U' R U R' U R"),
        Algorithm("R U R' U' R' U2 R U R' U R U' R U' R'"),
        Algorithm("(U) F U' R' U R U F' R U R2 U R2 U2 R'"),
        Algorithm("(U') R U R' U L' U R U' L U2 R'"),
        Algorithm("(U) R' U2 R U R' U' R F U' R' U' R U F'"),
        Algorithm("(U) R' U R U2 R' U R U2 R D R' U' R D' R'"),
        Algorithm("F U R U' R' U R U' R' F' R' U' F' U F R"),
        Algorithm("(U2) F R U R' U' R U R2 U' F' U R U R U' R'"),
        Algorithm("(U') R U R' F' R U R' U R U2 R' F R U' R'"),
        Algorithm("(U2) R U2 L' R' U2 R U2 R' U2 L U' R U' R'"),
        Algorithm("R U' R2 U2 D' R U R' U D R2 U R'"),
        Algorithm("(U2) F U R' F R F' R U' R' U R U' R' F'"),
        Algorithm("(U) r U R' U' r' F R F' R U' L' U R' U' L"),
        Algorithm("(U2) R U R D' R U' R' D R2 U' R' U2 R2 U2 R'"),
        Algorithm("(U) R U' L' U R' U' L"),
        Algorithm("(U2) R' U2 R U R' U' R' D' R U2 R' D R2"),
        Algorithm("R' D U' R' U R U2 D' R2 U R' U' R'"),
        Algorithm("(U2) R' U' R' U R2 D' U2 R U R' U' D R'"),
        Algorithm("(U) R2 D R' U2 R D' R' U' R' U R U2 R'"),
        Algorithm("(U2) r U2 R' U' R U R' U' R U R' U2 r' F R F'"),
        Algorithm("(U') R U R' F' R U R' U R U' R' U' R' F R2 U' R'"),
        Algorithm("(U) R U' R' U R U' R' F R' F' R U' F' U F"),
        Algorithm("R' U2 F' R U R' U' R' F R U2 R"),
        Algorithm("(U) R2 D r' U2 r D' R' U' R' U R U2 R'"),
        Algorithm("(U2) R U2 R' U2 R' F R2 U R' U' R U R' U' F'"),
        Algorithm("(U2) R' U2 R U R' U' R' D' r U2 r' D R2"),
        Algorithm("F R' U2 R F' R' F U2 F' R"),
        Algorithm("R U R' U R U' R D R' U' R D' R2"),
        Algorithm("(U') R U' R' U' R U' R' U2 R U R2 D' R U2 R' D R"),
        Algorithm("(U2) F U R U' R' U R U' l U' R2 D' R U R' x"),
        Algorithm("(U') R2 D' R U' R' D R U' R U R' U R"),
        Algorithm("R' U2 R U2 R' U R U2 R' U r' F R F' r"),
        Algorithm("(U) R' D' R U R' D R2 U' R' U R U R' U' R U2 R' U R U2 R'"),
        Algorithm("(U) R U' R' U' R U R D R' U2 R D' R2 U R U2 R'"),
        Algorithm("R' U2 R' D' R U R' D R U' R U R' U R"),
        Algorithm("(U2) R' U' R U' R2 F' R U R U' R' F U2 R"),
        Algorithm("(U') R U R' U R' D' R U R' D R U' R U2 R'"),
        Algorithm("(U2) R U2 R2 F R F' R' U' F' U F R2 U' R'"),
        Algorithm("r U R' F' U F U R U2 R' U M"),
        Algorithm("(U2) R' D' R U R' D R2 U R' U2 R U R'"),
        Algorithm("(U') R U' R' U' F U R U' R' F' R U' R' U' R' F R F'"),
        Algorithm("(U2) R' U2 R U R2 D' R U' R' D R U2 R"),
        Algorithm("(U') R2 D' r U2 r' D R2 U R' U R"),
        Algorithm("(U) R' U2 R U R' U R' D' R U2 R' D R U2 R"),
        Algorithm("(U) R L' U R' U' L U2 R U2 R'"),
        Algorithm("(U') R2 D' R U2 R' D R2 U R' U R"),
        Algorithm("(U) R2 F R U R U' R' F' R U' R' U R"),
        Algorithm("(U2) R U R' U R' U' R' D' R U R' D R' U2 R'"),
        Algorithm("R' U' F U' R2 U R2 U F' R U' R U' R'"),
        Algorithm("(U) R' U2 R U R' U R' D' r U2 r' D R U2 R"),
        Algorithm("(U2) R' U' F' U F R U R' F R U R' U' F' U R"),
        Algorithm("(U) R U R' U R F U' R' U R U F' U R'"),
        Algorithm("(U') R U R' U R2 D r' U2 r D' R2"),
        Algorithm("(U) R' U R U2 R' U R2 D R' U R D' R'"),
        Algorithm("R' U' R U R2 U' R' U' R U D' R U R' D R'"),
        Algorithm("(U') R U R' U R2 D R' U2 R D' R2"),
        Algorithm("(U') R' U2 R U F R' U R U' F'"),
        Algorithm("(U) R U2 R D R' U2 R D' R' U R' U R U2 R'"),
        Algorithm("(U) F R' U' R2 U' R2 U2 R2 U' R' F'"),
        Algorithm("(U2) R U R' U' R U R2 D' R U R' D R U R U2 R'"),
        Algorithm("R' U2 R' D R' U R D' R U R U' R U' R'"),
        Algorithm("(U2) R' F R U R' U' R' F' D' R U R' D R2"),
        Algorithm("(U') R U' R2 U' R U' R' U2 R' U2 R' U' R U' R2"),
        Algorithm("(U') R U2 R2 U' R' U R U' R' U' R2 U R"),
        Algorithm("(U2) R' U' R U' R' U2 R"),
        Algorithm("(U') R U2 R' U' R U' R'"),
        Algorithm("(U2) R' U' R2 U R2 U R2 U2 R2 U2 R"),
        Algorithm("R U R' U R' U' R2 U' R2 U2 R"),
        Algorithm("(U') R' U' R U R U2 R' U' R' U R U' R U' R'"),
        Algorithm("(U') R U R' U' R' U' R U R U' R' U' R' U R"),
        Algorithm("(U2) R' U' R U' R2 U' R' U' R' U R U R U' R"),
        Algorithm("R U R' U R' U' R U' R' U2 R U R U' R'"),
        Algorithm("(U2) R U R' U R U2 R' U' R U2 R2 U' R2 U' R2 U2 R"),
        Algorithm("(U') R' U' R U R U2 R' U' R U' R' U R' U R"),
        Algorithm("(U) R U2 R2 U' R2 U' R' F U' R' U' R U F'"),
        Algorithm("R' U' R U' L U' R' U L' U2 R"),
        Algorithm("(U') R' F' U' F U R F R U R' U' R U R' U' F'"),
        Algorithm("(U2) R U' R' U2 R U' R' U2 R' D' R U R' D R"),
        Algorithm("(U) R U R' U R U' R' U r' F R F' r U2 R'"),
        Algorithm("F U R U' R' U R' F R2 U' R' F' U r U' r'"),
        Algorithm("(U2) R U R' F' R U2 R' U' R U' R' F R U' R'"),
        Algorithm("(U2) R U R' U' R' U' F U R2 U' R' U R U' R' F'"),
        Algorithm("(U') R' U R2 U2 D R' U' R U' D' R2 U' R"),
        Algorithm("(U) F R U R' U' R U R' F R' F' R U' F'"),
        Algorithm("F R' F' R U R U' R2 F R U R' U' F' U R"),
        Algorithm("R' U' R' F R F' U R U' F R U R' U' R U R' U' F'"),
        Algorithm("L' U R U' L U R'"),
        Algorithm("(U) R U2 R' U' R U R D R' U2 R D' R2"),
        Algorithm("R' U2 F U R U2 R' U R U R' F' U R"),
        Algorithm("(U) R2 F R' U R U' F' R2 U2 R' U' R U R"),
        Algorithm("(U2) R2 D' R U2 R' D R U R U' R' U2 R"),
        Algorithm("(U') R' U' R U' R' U R U' R' U R F U' R' U2 R U F'"),
        Algorithm("R' U' R D' R U' R' U R2 U R' U' R2 D"),
        Algorithm("R' F R U R' U r U r' U2 F' U' R"),
        Algorithm("F U R U' R' U R U' R2 F' R U2 R U2 R'"),
        Algorithm("(U2) R2 D' r U2 r' D R U R U' R' U2 R"),
        Algorithm("R' U2 R' F' R U R U' R' F U2 R"),
        Algorithm("(U) R U2 R' U' R U R D r' U2 r D' R2"),
        Algorithm("R' F U2 F' R F R' U2 R F'"),
        Algorithm("(U') R' U' R U' R' U R' D' R U R' D R2"),
        Algorithm("(U2) R U R' U' R' F R U2 F' U' F U' R U R' U' F'"),
        Algorithm("(U) R' D' R U2 R' D R2 U' R' U2 R U R' U R U R'"),
        Algorithm("R2 D R' U R D' R' U R' U' R U' R'"),
        Algorithm("(U') R U2 R' L' U2 R U' R' U2 L R U2 R'"),
        Algorithm("(U') R' U' R U' R' U R' D' R U' R' r U2 r' D R2"),
        Algorithm("R' U' R U' R U R' U' R' U2 F R U R U' R' F'"),
        Algorithm("(U') R U2 R' U R' D' R U' R' D R U' R U' R'"),
        Algorithm("(U) R U R' U R' D R2 U' R' U R2 D' R' U2 R'"),
        Algorithm("R' U' R U' R' U R' D' R U' R' D R U2 R"),
        Algorithm("R' U2 F' R U R' U' R' F R2 U R' U R"),
        Algorithm("(U) R U2 R2 D' R U2 R' D R2 U' R' U R U' R'"),
        Algorithm("(U2) R' U' F' R U R' U' R' F R2 U' R' U R"),
        Algorithm("F R U' R' U R U R' F' U R' U' F U R U' R' F' R"),
        Algorithm("(U2) R U R' F' R U R' U' R' F R2 U R' U' R U' R'"),
        Algorithm("R2 D r' U2 r D' R2 U' R U' R'"),
        Algorithm("(U) F R U' R' U' R U2 R' U y' R' U' R U' R'"),
        Algorithm("(U) F U R' U' R F' U' R' U2 R"),
        Algorithm("R2 D R' U2 R D' R2 U' R U' R'"),
        Algorithm("(U2) R U R' F' R U2 R' U2 R' F R2 U' R'"),
        Algorithm("(U) R' U' R U' R U R D R' U' R D' R U2 R"),
        Algorithm("R2 D R' U2 R D' R U' R2 U' R' U R' U R"),
        Algorithm("(U') L' U R U' L U R' r U R' U' r' F R F'"),
        Algorithm("(U') R U2 R' U' F' R U R' U' R' F R2 U' R'"),
        Algorithm("(U) R' U2 R' D' R U R' D R2 U' R' U2 R"),
        Algorithm("R' U' R U' R2 D' r U2 r' D R2"),
        Algorithm("(U') R' U' R U' R2 D' R U R' D R U R"),
        Algorithm("(U') R U R' U' R2 U R U R' U' D R' U' R D' R"),
        Algorithm("R' U' R U' R2 D' R U2 R' D R2"),
        Algorithm("R U2 R' U2 r' F R F' M'"),
        Algorithm("(U') R' U' R U' R' U y' R' U2 R U' R' U' R f z'"),
        Algorithm("(U2) R' U' R U R' F R U R' U' R' F' R2"),
        Algorithm("R U2 R' U' R U R' U2 R' F R U R U' R' F'"),
        Algorithm("(U') R U R' U R' F U' R2 U' R2 U F' U R"),
        Algorithm("F' r U R' U' r' F R L' U R U' L U R'"),
        Algorithm("(U)"),
        Algorithm("R U' R U R U R U' R' U' R2"),
        Algorithm("R2 U R U R' U' R' U' R' U R'"),
        Algorithm("M2 U M2 U M' U2 M2 U2 M'"),
        Algorithm("M2 U M2 U2 M2 U M2"),
        Algorithm("x' R U' R' D R U R' D' R U R' D R U' R' D' x"),
        Algorithm("R' U R' U' y R' F' R2 U' R' U R' F R F"),
        Algorithm("F R U' R' U' R U R' F' R U R' U' R' F R F'"),
        Algorithm("R U R' U R U R' F' R U R' U' R' F R2 U' R' U2 R U' R'"),
        Algorithm("R' U R U' R' F' U' F R U R' F R' F' R U' R"),
        Algorithm("(U') x R' U R' D2 R U' R' D2 R2 x'"),
        Algorithm("x R2 D2 R U R' D2 R U' R x'"),
        Algorithm("(U) L U2 L' U2 L F' L' U' L U L F L2"),
        Algorithm("(U) R' U2 R U2 R' F R U R' U' R' F' R2"),
        Algorithm("L' U' L F L' U' L U L F' L2 U L"),
        Algorithm("(U2) R U R' F' R U R' U' R' F R2 U' R'"),
        Algorithm("(U2) R U R' U' R' F R2 U' R' U' R U R' F'"),
        Algorithm("(U2) R' U' F' R U R' U' R' F R2 U' R' U' R U R' U R"),
        Algorithm("(U2) R2 u R' U R' U' R u' R2 y' R' U R"),
        Algorithm("(U2) R' U' R y R2 u R' U R U' R u' R2"),
        Algorithm("(U2) R2 u' R U' R U R' u R2 y R U' R'"),
        Algorithm("(U2) R U R' y' R2 u' R U' R' U R' u R2"),
        Algorithm("(U2) R' U' F' U F R U' R' U' R U' R' U F' U F R"),
        Algorithm("(U2) R' F' U' F U' R U R' U R F R U R' U' F'"),
        Algorithm("R U2 R2 F R U R' U' F' U R U R' F R F'"),
        Algorithm("(U2) R' F' U' F U' R U R' U R U R' F' U' F U R"),
        Algorithm("r' U' R U' R' U2 r U r U2 R' U' R U' r'"),
        Algorithm("r U R' U R U2 r' U' r' U2 R U R' U r"),
        Algorithm("F R U' R2 F2 r U r' F R2 U R' U R U' R' F'"),
        Algorithm("r' R2 U R' U R U' R' U r U2 r' U' M'"),
        Algorithm("(U) F R U R' U R U' R' F' U F U R U' R' U F'"),
        Algorithm("F U' R U R' U' F' U' F R U R' U' R U' R' F'"),
        Algorithm("(U) F R U R' U' F' r' U r2 U' r2 U' r2 U r'"),
        Algorithm("R' F' U' F U R U' r U' r2 U r2 U r2 U' r"),
        Algorithm("(U) F R U R' U' R U R' U' F' R U2 R' U' F' U2 F R U' R'"),
        Algorithm("(U) R' U R U2 R' U' R U R' U' R' F R F2 U2 F R"),
        Algorithm("(U) R U2 R2 F R F' R U2 R' U' r U R' U R U2 r'"),
        Algorithm("R U2 R2 F R F' R U2 R2 F' r U' r' F2 R"),
        Algorithm("F R U R' U' F' R U2 R' U' F' U F R U' R'"),
        Algorithm("(U') R' F' U' F U R U' R' U' F U R U' R' F' R"),
        Algorithm("R U2 R2 F R F' U2 R' F R F'"),
        Algorithm("(U') F R' F' R U2 R U2 R' U R' U' F' U F R"),
        Algorithm("(U2) r U2 R' U' R U' r' U2 F R U' R' U' R U R' F'"),
        Algorithm("(U') F R U' R' U' r' F2 r U2 r U' r' F R U R' F'"),
        Algorithm("R' U2 R U R' F' U F R2 U R' U' R' F R F'"),
        Algorithm("R U2 R' U' F' U F U R' F R F r U r' F"),
        Algorithm("(U') r U r' U2 F R U R' U' F' R U' M' U' r'"),
        Algorithm("F U R U2 R' U' R U2 R2 F R F' U' F'"),
        Algorithm("F R U' R' U R U R' F' r' U r2 U' r2 U' r2 U r'"),
        Algorithm("(U) R' F' r U2 r' F2 R U' R' U' R' F R U R"),
        Algorithm("(U2) R' F R F U2 R' F' R U2 F2 R U2 R'"),
        Algorithm("(U) R U R' U R U y R U R' F' U' F U' R U' R' F'"),
        Algorithm("(U') R' F' U' F R' F R2 U' R' U2 R U R' F' R"),
        Algorithm("(U2) r U2 R' U' R U' r' F R U R' F' U' F' r U r'"),
        Algorithm("(U2) R U2 R2 F R F' U F' U F R U' R' U2 R U2 R'"),
        Algorithm("(U2) R2 F R F' U2 R' U' F' U F R2 U' R' U R"),
        Algorithm("F R' F' R U2 R U' R' U R' F R F' R U2 R'"),
        Algorithm("(U) R U R' U R U' R' U R' F R F' U2 R' F R F'"),
        Algorithm("(U2) F R U R2 U' R U' R' U2 F R F' R U R' F'"),
        Algorithm("(U) R U' R2 D' r U' r' D R2 U R'"),
        Algorithm("(U') R' U R2 D r' U r D' R2 U' R"),
        Algorithm("(U2) r' U' r U2 R' U r' F R F' r U' r' U r"),
        Algorithm("(U') R U2 R' U2 R' F R2 U R' U2 R' F R F' R U R' F'"),
        Algorithm("F R U R' U' F' U' F R U' R' U2 R U R' F'"),
        Algorithm("r U r' R U R' U R U' R' U2 r U' r'"),
        Algorithm("(U) R U R' F' U' F R U R' U2 R' F R F'"),
        Algorithm("(U) r U r' U2 R U R' U' R U' R' r U' r'"),
        Algorithm("R' U2 R U R' F' U F R F R U R' U' F'"),
        Algorithm("F R U R' U' R U2 R' U' M' U R U' r' U' F'"),
        Algorithm("(U') F R U' R' U2 R U R' F' U F U R U' R' F'"),
        Algorithm("F R U R' U' F' f R U R' U' f'"),
        Algorithm("(U') r' U' R U2 R' U2 r U2 r' U r"),
        Algorithm("(U2) R' U' R' F R F' U R U R' U' F' U F R"),
        Algorithm("r U r' R U R' U R U2 R' U' R U' R' r U' r'"),
        Algorithm("(U') r U2 R' U' R U' r' f R U R' U' f'"),
        Algorithm("(U2) R U R' y r' U' F' R U' R' U2 r"),
        Algorithm("(U') R' U' R' F R F' U R r' U' R U' R' U2 r"),
        Algorithm("(U') F R U R' U' F' U2 r U R' U R U2 r'"),
        Algorithm("(U) F R U R' U' F' U' r U2 R' U' R U' r'"),
        Algorithm("R' F' U' F U R r' U2 R U R' U r"),
        Algorithm("(U2) r' U' R U' R' U2 r R' U' F' U F R"),
        Algorithm("(U2) r U R' U R U2 r' U F U R U' R' F'"),
        Algorithm("(U') F R U R' U' R U' R' F' U' F' r U r2 F2 r"),
        Algorithm("R' U' F' U F R r U r' R U R' U' r U' r'"),
        Algorithm("r D' R2 U' R U2 R' U R2 D r'"),
        Algorithm("r' D R2 U R' U2 R U' R2 D' r"),
        Algorithm("(U2) R U R' U R U' R2 F' U' F U R U2 R' F R F'"),
        Algorithm("(U2) F U R U2 R' U' R U R' U R' F R F' U' F'"),
        Algorithm("(U2) F' U' r U' r' F2 R U2 R' r U' r' U r U r'"),
        Algorithm("(U) F' U' F U r U r' U2 R' F R F' r U r'"),
        Algorithm("(U2) r' U' R' F R F' R U' R' U' r U r' F' U' F r"),
        Algorithm("(U2) F R U' R' U' F R' F' R U R' F' R U2 R U2 R'"),
        Algorithm("F R F' r U r' U R' U R U' R' U2 r U' r'"),
        Algorithm("F' U' F R U' R' U' F' U2 r' F r U' F R U' R'"),
        Algorithm("(U) F R U' R' U R U R' F' U' R U2 R' U2 R' F R F'"),
        Algorithm("(U2) R U R' F' U' R U R' U' R' F R U' R' F R F'"),
        Algorithm("F' r U r' U' r U r' U' r' F r U R U R' F'"),
        Algorithm("(U) r U R' U R U2 r' U r' F2 r U2 r U' r' F"),
        Algorithm("F R U' R' U F R U R' U' F' R U2 R' U' F'"),
        Algorithm("(U') R U2 R' U' F' U F U R' U' F' U F R2 U' R'"),
        Algorithm("F U R' U' F' U F R U R U2 R' U' R U R' F'"),
        Algorithm("R' U' F U R U' R' F r U r' U r' F' r F R"),
        Algorithm("(U2) r U' r' F R' F' R U2 r U' r' U' F' U F"),
        Algorithm("R U R' U' R' F R F' r' U r2 U' r2 U' r2 U r'"),
        Algorithm("(U') R U2 R' U2 R' F R F' U2 F R U' R' U' R U R' F'"),
        Algorithm("R U2 R2 D' F' R U' R' F r U r' D R"),
        Algorithm("(U2) F R' F' R U2 R U2 R' U F R U' R' U' R U R' F'"),
        Algorithm("r' U' F2 R U' R' U2 r U' F U' F'"),
        Algorithm("R U2 R' U2 R' F R F' U2 F U R U' R' F'"),
        Algorithm("(U) F R U R' U2 R' F R F' R U2 R' U' F'"),
        Algorithm("(U) R2 U' R' U' R U R U R' D r' U' r D' R2 U' R"),
        Algorithm("(U') R2 U R U R' U' R' U' R D' r U r' D R2 U R'"),
        Algorithm("(U) R' F R U' R' U2 R U R2 F' R F' U F R"),
        Algorithm("F R U R' U' R U2 R' F' U2 F R' F R F2"),
        Algorithm("(U2) F U2 R U' R2 F R2 U' R' U' R U2 R' U' F' U2 F'"),
        Algorithm("(U') R U2 R' F R' F' R U' R U R' U2 R' F R F'"),
        Algorithm("(U2) R' F' U' R U R' U' R' F R2 U' R2 F R F' U R"),
        Algorithm("F R' F' R U R U' R2 F' U' F U' R U R' U R"),
        Algorithm("(U) R' F R F' U2 R' F R F' U y' R' U' R U R' U R"),
        Algorithm("(U') R U' R2 D' r U r' D R2 U R'"),
        Algorithm("(U) R' U R2 D r' U' r D' R2 U' R"),
        Algorithm("(U2) F R' F' R U' F' r U' r' F2 U2 R U' R'"),
        Algorithm("(U) R' F R U R' U' F' U R U R' U' F' U F R"),
        Algorithm("(U') R U R' F' U' F U R U2 R' F U R U' R' F'"),
        Algorithm("(U') R' F R F' U' F2 r U r' U F"),
        Algorithm("(U') F R U' R' U' r U R' U R U2 r' R U R' F'"),
        Algorithm("(U2) R' F' U' F U R U' R U2 R' U2 R' F R F'"),
        Algorithm("(U) R U R' U' R' F R F' U r' U' R U' R' U2 r"),
        Algorithm("(U2) M' U R U' r' U2 R' F R F' U F' U F"),
        Algorithm("(U2) F' U' F R U R' U' F' U2 r' F r F R U' R'"),
        Algorithm("(U') R' U' F' U2 r' F r U r' F' r U' F R"),
        Algorithm("F R U R2 U' F' U F R U R' F R F' U' F'"),
        Algorithm("r' U2 R U R' y' R U R' U' R2 U R F z'"),
        Algorithm("(U2) r' U' R U2 R' U2 F R F' r U R' U r' U r"),
        Algorithm("(U) f R U R' U' f' U' F R U R' U' F'"),
        Algorithm("(U) R U R' U' M' U R U' r2 U2 R U R' U r"),
        Algorithm("(U2) r U R' U R U2 r2 U' R U M' U' R' U R"),
        Algorithm("R' U' F' U F R U R' F' U' F U R"),
        Algorithm("F R U' R' U2 R U R' F' U R' U' F' U F R"),
        Algorithm("(U) F' U' F R U R' F' U' F U R U R' U' F' U2 F"),
        Algorithm("r' U' R U' R' U2 r F R U R' U' R U R' U' F'"),
        Algorithm("(U) F R U R' U' F' R U R' F' U2 F R U' R'"),
        Algorithm("(U) f R U R' U' f' R' F' U' F U R"),
        Algorithm("(U2) r U R' U R U2 R' U' M U2 M' U' M"),
        Algorithm("(U2) r' R2 U R' U r U2 r' U M'"),
        Algorithm("(U) F R U R' U' F' U2 R' U' F' U F R"),
        Algorithm("(U') F R U R' U' R U R' U' F' U' F R U R' U' F'"),
        Algorithm("(U') F R U R' U' F' r' U2 R U R' U r"),
        Algorithm("(U2) M' U M U R U R' U R' F R F' r U2 r'"),
        Algorithm("(U') r U R' U R U2 r2 U' R' F R F' U r"),
        Algorithm("F U R U' R' F' U' F U R U' R' U R U' R' F'"),
        Algorithm("(U') F R U R' U' F' r' U r' F' r2 U' F U' F'"),
        Algorithm("(U') B' R' U' R U R' U' R U y R U' R' F' U' F U R"),
        Algorithm("(U') F R U R' U' R U' R' F' U' r' F U' F U r"),
        Algorithm("(U2) R' U' R U' M' U' r' U' r U r' U F' U F R"),
        Algorithm("(U') F R U R' U' R U R' U' F' R' F' U' F U R"),
        Algorithm("R' U' R' F R F' U R U F R U R' U' R U R' U' F'"),
        Algorithm("(U') r' U2 R U R' U r U R U2 R2 F R F' R U2 R'"),
        Algorithm("F R U R' U' F' U2 F R U' R' U' R U R' F'"),
        Algorithm("(U) F U R U2 R' U' R U R' U R' U' F' U F R F'"),
        Algorithm("(U2) F R U' R' r U R' U R U2 r' U' R U R' F'"),
        Algorithm("(U') R U2 R' U R U R' F R' F' R2 U2 R2 F R F'"),
        Algorithm("(U') F R U R' U' R' U R U2 r' U r U F' r' U' r"),
        Algorithm("R' U' F U R U' R' F' R U F R U R' U' F'"),
        Algorithm("(U) r U R' U' r' R U2 R' U' F' U F R2 U' R'"),
        Algorithm("R U' R2 D' r U r' D R2 U' R' U' R U' R'"),
        Algorithm("R' U F' U2 R U R' U' R' F R2 U R' F' U2 F R"),
        Algorithm("(U') F R U' R' U' R U R' U' R' F R F' R U R' F'"),
        Algorithm("R' F R U' R' U2 R U R' F2 U F R"),
        Algorithm("R' U' F U R U' R' F' R U2 R' F' U' F U R"),
        Algorithm("R U R' U F R U R' U' F2 U2 F U2 R U2 R'"),
        Algorithm("(U) R2 U' R' F R F' U R' D r' U r D' R'"),
        Algorithm("(U) r U r' U2 r U' r' F R U2 R' U2 r U2 r' F"),
        Algorithm("(U2) R U2 R' U' R U R2 F R F' U2 R' F R F'"),
        Algorithm("(U2) R' U' R U' R' U' F' U' F R U2 R2 F R F' U R"),
        Algorithm("R U2 R2 F R F' U' F' U' F R U R' U' R U' R'"),
        Algorithm("R' U F' U' F R U2 R2 F R F' R U' R' U2 R"),
        Algorithm("(U) r U R' U R U2 r' U' R U2 R' U' F' U F R U' R'"),
        Algorithm("R' F R U R' U' F' U R U' r' U2 R U R' U r"),
        Algorithm("(U) F U R U' R' F' U' F U R U2 R' U' R U R' F'"),
        Algorithm("(U') r U2 r' U' F' U F U r U r' F R' F' R"),
        Algorithm("(U') F R U' R' U' R U R' F' U' R U R' U' R' F R F'"),
        Algorithm("(U') F R U R' U' r' F' U' F r F' r' U r"),
        Algorithm("F R U R' U' R U R' U2 R' F R F' R U R' F'"),
        Algorithm("(U) F U R U' R' F' U' r U' r' U' r U r' F' U F"),
        Algorithm("(U') M' U R U' r' U' r U' r' U y' R U R U' R'"),
        Algorithm("R U' R' U2 r U' r' R U R' U r U' r' F' U F"),
        Algorithm("(U') F R' F' R U R U R' U2 R' U' F R F' R' U R"),
        Algorithm("R2 F R F' R U R' F' U2 F R U R' U2 R"),
        Algorithm("F R U' R2 F R F' U2 F' U2 F R U2 R' U' F'"),
        Algorithm("(U2) r U' r' U M' U2 R U r' F' U F"),
        Algorithm("(U') R' U' F U F' R U' R' F' R U2 M' U' M"),
        Algorithm("R2 F R F' U2 R' U' F' U F R2 U2 R' U2 R"),
        Algorithm("R' F R F' U2 F' U2 F R U2 R' U2 R' F R F'"),
        Algorithm("(U) R U R' U' R' F R F' U2 R' U' F' U F R"),
        Algorithm("(U') F' U' F U2 R U R' U2 F' U F R U R' F' U' F"),
        Algorithm("(U) R U2 R' U2 R' F R F' U r' U' R U' R' U2 r"),
        Algorithm("R' U' R U F R U R' U' F' U M U' R' U r"),
        Algorithm("(U2) F U R U R' F' U F R U R' U F'"),
        Algorithm("F U R U' R2 U' R2 U' R2 U F' U F R F'"),
        Algorithm("(U2) F' U' F U2 R U R' U2 F R' F2 U' F U R"),
        Algorithm("(U) F R U R' U' r U' r' U R U R' U r U' r' F'"),
        Algorithm("(U) R' U' R U' R' U' R2 D r' U r D' R2 U' R"),
        Algorithm("F R U R' U' R U R' F' U' F' r U r'"),
        Algorithm("(U) F R' F' R U R U' R' U' R U R' U' R' F R F'"),
        Algorithm("F R U R' U' F' U R U R' F' U F R U' R'"),
        Algorithm("R U R' F' U2 F R U' R' F U R U' R' F'"),
        Algorithm("R' F' U' F U R U' F R U' R' U2 R U R' F'"),
        Algorithm("R U R' U R U2 R2 U2 r U' r' U2 r U r' U2 R"),
        Algorithm("R U R' F' U' F R U R' U' F' U' F U R U2 R'"),
        Algorithm("(U2) R' U' F' U F R U' R' F' U' F U R"),
        Algorithm("(U') f R U R' U' f' U F R U R' U' F'"),
        Algorithm("(U2) r' U' R U' R' U2 r2 U R' U' r' R U R U' R'"),
        Algorithm("(U2) F' U2 F R U' R2 D' r U' r' D R"),
        Algorithm("(U) r' U2 R U R' U r2 U' r2 U r2 U r2 U' r"),
        Algorithm("(U2) R' U' F' U F R U2 F R U R' U' F'"),
        Algorithm("M U' r U2 r' U' R U' R2 r"),
        Algorithm("(U) F U R U' R' F' R' F' U' F U R"),
        Algorithm("(U) r' U' R U' R' U2 r F U R U' R' F'"),
        Algorithm("(U) r' U' R U' R' U2 r U F R U' R' U2 R U R' F'"),
        Algorithm("(U') R' U' R' F R F' U R U2 r U2 R' U' R U' r'"),
        Algorithm("(U2) r U2 r' F R' F' R U' R U' R' U' M' U' M"),
        Algorithm("(U') R' F r U r' F' R U2 F U R U' R' U F'"),
        Algorithm("(U) F R U R' U' R U R' U' F' U F R U R' U' F'"),
        Algorithm("(U2) R' F' U' F U R U R U R2 F R F' y' R' U R"),
        Algorithm("(U2) R U R' U' R' F2 R U2 r U' r' U2 F r U r'"),
        Algorithm("(U') R' F' U' F U' r U' r' U r U M U R' U R"),
        Algorithm("(U') F U R U' R' U R U' R' F' U2 R' U' F' U F R"),
        Algorithm("(U) F R U R' U' R U R' U' F' U2 R' F' U' F U R"),
        Algorithm("F R U R' U2 F' U' F R' F R F' R U' R' U' F'"),
        Algorithm("(U') B' U' R' U2 R U R' U' R F U R U' R' F' U' f z'"),
        Algorithm("(U) R' F' U' F U R U R U R' F' U F R U' R'"),
        Algorithm("r' U2 R U R' U r U' F R' F' R U2 R U2 R'"),
        Algorithm("R U' R' U' M' U R U' r' U2 R' F R F'"),
        Algorithm("(U') r' U' R U M' U' F U R U' R' F' U' R' U R"),
        Algorithm("(U) R' U2 R U' R' U' R U R2 F R F' U2 F R' F' R2"),
        Algorithm("r' U' R U r U2 R' U' R' U R U2 R' F R F'"),
        Algorithm("(U2) F r U r' U' R U' R' U' r U r' U R U' R' F'"),
        Algorithm("R' U R2 D r' U' r D' R2 U R U R' U R"),
        Algorithm("(U2) r U' r' F U F R U' R' U R U' R' F'"),
        Algorithm("(U2) F R' F' R U R U' R' U R U R' U' R' F R F'"),
        Algorithm("R U R' U' R' F R F' f R U R' U' f'"),
        Algorithm("(U2) F R U' R' U R U2 R' U' F' r' U' F' U F r"),
        Algorithm("(U') r U2 R2 F2 r F' R U2 r2 F2 R"),
        Algorithm("(U') R' F R U R' U' F2 U2 F U' R U R2 F R F' R"),
        Algorithm("r' U2 R U R' F U F' R U' R' F' R U M'"),
        Algorithm("F R U R' U' R U' R' U R U2 R2 F R F' U' F'"),
        Algorithm("(U') R' U R U' R' U R U2 R2 F R F' U F' U F R"),
        Algorithm("R' U' R U' R' U2 F' U2 F2 U R U' R' F' U2 R"),
        Algorithm("(U') R U R' U R U2 R' U R U2 R2 F R F' U2 R' F R F'"),
        Algorithm("(U') r' U' R U' R' U2 r U R' U' F U R U' R' F' R"),
        Algorithm("(U2) F R U' R' U R U2 R' U' F' U F R U R' U' F'"),
        Algorithm("(U2) R' F R F' r U' r' U' F' U' F U r U2 r'"),
        Algorithm("(U2) F R' F' R U R U' R' U F R U' R' U R U R' F'"),
        Algorithm("(U2) R U R' U2 F' U' F U2 R U' R' F' U' F R U R'"),
        Algorithm("(U2) R' U' R' F R F' U F' U2 F U R U2 R' U' R"),
        Algorithm("(U') R U2 R' U2 R' F R F' R U2 R2 F R F' R U2 R'"),
        Algorithm("(U) F U R U2 R' F R U R' U' F' U' R U2 R' U' F'"),
        Algorithm("(U') R U R' U2 F' U' F U2 R' F R2 U R' U' F'"),
        Algorithm("R U R2 F' U' F U R U2 M' U R U' r'"),
        Algorithm("f R U R' U' f' U R' F R U R' U' F' U R"),
        Algorithm("(U') R U R' U R U R2 D' r U' r' D R2 U R'"),
        Algorithm("(U2) r D' r2 U' r U r' U r U r' U2 r U' r D r'"),
        Algorithm("R U' R' U R' F R F r U r' U' r U' r' F2"),
        Algorithm("(U') r' U' F' U2 r U' r' F2 r U r' U' r"),
        Algorithm("(U) R' F' U' F U R U2 F R U' R' U' R U R' F'"),
        Algorithm("(U) F R U' R' F R' F' R U2 R U' R' U R U' R' F'"),
        Algorithm("(U2) R' F R F' U' R' D' r U r' D R"),
        Algorithm("(U2) R' F R F' r U' r' U F U R' F R U' F'"),
        Algorithm("(U2) R U R' U2 R U' R' F R U R' U' F' U2 R' F R F'"),
        Algorithm("(U) R U2 R2 U' F' U F R2 U R' U' F' U F R U' R'"),
        Algorithm("F R U R' U' R U R' U' F' U R U R' U' R' F R F'"),
        Algorithm("(U2) F R U' R' U' R U R2 F' U' F U R U' F'"),
        Algorithm("(U') R' U2 R U R' U R2 U' R2 D' r U r' D R2 U R'"),
        Algorithm("(U) F' U' F r U r' R U2 R' U r U r'"),
        Algorithm("(U2) R' F R F' U' r U2 r' U' F' U F U r U r'"),
        Algorithm("M' U M U R' F R U R' F R F U' F'"),
        Algorithm("(U') R' F R F2 U F R' F R F' R U R2 F R F'"),
        Algorithm("(U) R U R' U R U2 R' U2 r U R' U' r' R U R U' R'"),
        Algorithm("r' U2 R U R' U r"),
        Algorithm("r' U2 R2 U R2 U r U' R U' R'"),
        Algorithm("(U) R' F' U' F U R U R' U' F' U F R"),
        Algorithm("(U') R' U' R' F R F' R' F R F' R U' R' U2 R"),
        Algorithm("(U) R' F' U2 R U R' U R U2 R' F R"),
        Algorithm("(U') M' U R' U2 R U R' U R M"),
        Algorithm("F R U R' U' F' R' F' U' F U R"),
        Algorithm("F R U R' U' F' U' F R U R' U' F'"),
        Algorithm("R' U2 R U R' F' U F R U2 R' U' F' U F R"),
        Algorithm("(U') R' U' F' U F U2 R U R' F' U F R"),
        Algorithm("(U2) R' U' R U' y x' R2 U' R' U R' x"),
        Algorithm("F U R U' R' U R U' R' F' r' U' F' U F r"),
        Algorithm("(U) l U' R' U R U R' F' R U R' U' R' F R2 U' R' U' x"),
        Algorithm("R U' L' U R' U' L U' F R U' R' U' R U R' F'"),
        Algorithm("(U) R U2 R2 F R F' R U2 R' r' U2 R U R' U r"),
        Algorithm("(U') r U r' R U R' U2 F R U R' F r U r2 F r"),
        Algorithm("(U) R' U2 R U R' U R U' R' U2 R U R' F' U F R"),
        Algorithm("(U2) R U R' U R U2 R' U' R' F' U' F U R"),
        Algorithm("(U) R' U2 R U R' U R U2 R' U' F' U F R"),
        Algorithm("(U2) R U R' U R U2 R' U2 F R U R' U' F'"),
        Algorithm("(U) r' U2 R U R' U r U2 R' U' F' U F R"),
        Algorithm("(U) r' U2 R U R' U r U' R' U2 R U R' F' U F R"),
        Algorithm("(U) R' U' R2 U R U R' U' R U F R F' R U2 R'"),
        Algorithm("R U R' F' R U R' U R U2 R' U' F R U' R'"),
        Algorithm("(U2) R' U' R U' R' U2 R2 U2 R' U2 R' F R F'"),
        Algorithm("(U') r U R' U R U2 r' F R' F' R U R U' R'"),
        Algorithm("r' U' R' D' R U' R' D R2 U R' U r"),
        Algorithm("M U R2 F R U R U' R' F' R U' R' U r"),
        Algorithm("R U R' F' R' U2 R F U' R' U' R U R U' R'"),
        Algorithm("(U') R' U' F R' F2 R U R U' R' F R"),
        Algorithm("(U) r' D R2 U R' U R U' R2 D' r"),
        Algorithm("R' U2 R' U' F' U F R2 U' R' U' R U' R' U R"),
        Algorithm("(U) R' F' R U R' U' R' F R F' U F R"),
        Algorithm("R U2 R' U2 R' F R F' U2 r U2 R' U' R U' r'"),
        Algorithm("R U R' U' R' F R F' U' F R U R' U' F'"),
        Algorithm("(U) r' R2 U' R' U' F' U2 F U2 r U2 R'"),
        Algorithm("R' U2 R U R2 F' U' F U R2 U2 R' U' R"),
        Algorithm("(U2) F R F' U R U R' U' R' U' F R U R U' R2 F'"),
        Algorithm("(U') R U' R' U' R U2 R' F' r' U' F' U F r F"),
        Algorithm("r' U2 F' R U R' U' R' F R U2 r"),
        Algorithm("(U) r' R U R' U' F U F' R U' R' F' r"),
        Algorithm("(U2) R U' R' U R U R' U' R U' R' F' U F R U R'"),
        Algorithm("(U) r U' r' F R' F' R U2 M' U' M"),
        Algorithm("(U') R U' R' U' F' U R U R' U' R' F R"),
        Algorithm("R' U2 R U R' U2 R U' R' F U R' F R F' U' R' F' R2"),
        Algorithm("(U2) R' D' r U r' R U2 R' D R U x U R' U' R x'"),
        Algorithm("(U') R U' R' U' R U R2 U' F' U F R2 U R'"),
        Algorithm("(U') F R U' R' U R U R' U R' U' F' U R U R U' R'"),
        Algorithm("(U2) R' U' R U' R' U2 R F' r U r' U2 r' F2 r"),
        Algorithm("R U R' U R U2 R' U' F R U' R' U R U R' F'"),
        Algorithm("(U') F R U' R' U' R U R2 F2 R U2 R U2 R' F"),
        Algorithm("(U2) R U R' U' R U R' F' U' F U2 R U' R'"),
        Algorithm("(U2) r U2 R D R' U' R D' R2 U R U2 r'"),
        Algorithm("(U') F U R U2 R' U' R U R' U R U' R' F'"),
        Algorithm("(U2) F R2 D R' U' R D' R2 U' R U R' F'"),
        Algorithm("r D' R2 U' R U R' U R2 D r'"),
        Algorithm("(U) R U R2 F' R U2 R U2 R' F U' M' U R U' r'"),
        Algorithm("F U R U2 R' U' R U R' U F' U' F' r U r'"),
        Algorithm("(U2) R U R' U' R F R U R' U' F' U R' U R U' R'"),
        Algorithm("(U2) F U' R2 D R' U R D' R2 U F'"),
        Algorithm("(U') R U2 R' U' F' U' F R U R' U' R U R' U' R U' R'"),
        Algorithm("(U) R U2 R2 F2 r U r' F2 R U R U' R' F'"),
        Algorithm("(U2) R' D' R U R' D R2 U' R' U' F' U F R U R'"),
        Algorithm("(U') R U R' U R U2 R' F R U' R' U' R U R' F'"),
        Algorithm("R U R' U R U2 R' U' R U R' U' R' F R F'"),
        Algorithm("(U') R' U2 R U R' U' R2 U R' U' R' U2 F R F'"),
        Algorithm("(U') R U2 R' U R U' R' U' R U2 R2 F R F' R U R'"),
        Algorithm("(U2) R' U2 R U R' U R U' R' F R U R' U' F' U R"),
        Algorithm("(U2) M' U M R U R' U R U2 R2 F R U F U' F'"),
        Algorithm("(U2) F R U' R' U' R U R' F' U' r U R' U' r' F R F'"),
        Algorithm("(U2) R' U R' U R2 U R2 F R F' R' U2 R U' R"),
        Algorithm("(U2) M' U R U2 R' U' R U' R' U2 M"),
        Algorithm("(U') F R U R' U' R U' R' U2 R U R' F'"),
        Algorithm("(U2) r U2 R2 U' R U' r' U2 R U2 R U2 R'"),
        Algorithm("r' U2 R U R' U r U' R U R' U R U2 R'"),
        Algorithm("(U') r U2 R2 U' R2 U' r' U R' U R"),
        Algorithm("(U') r U2 R' U' R U' r'"),
        Algorithm("(U') F' U' F U' R U R' U' F' U2 F R U R'"),
        Algorithm("(U') F R U R' U' F' U' F U R U' R' F'"),
        Algorithm("(U') R U R' U' M' U R U R' U' R U' r'"),
        Algorithm("(U) F U R U' R' F' U F U R U' R' F'"),
        Algorithm("(U) F U R U' R' U R' F R F' U' F'"),
        Algorithm("(U) R U R' U F2 r U r' F"),
        Algorithm("(U') R U2 R2 F R F' R U2 R' U r U2 R' U' R U' r'"),
        Algorithm("(U) R U R' U R' F R F' R U' R' U R U' R' U R U2 R'"),
        Algorithm("(U') r R U2 R D r' U2 r D' R2 U r'"),
        Algorithm("R U' r' F2 R U2 R' U R U R' F2 r U R'"),
        Algorithm("(U') R' D R2 U' F U R U' R' F' R2 D' R"),
        Algorithm("(U') R U R' U r' U' R2 U' R2 U R' F R F' U r"),
        Algorithm("(U2) R U2 R' U' R U' R' U' F U R U' R' F'"),
        Algorithm("(U) R' U' R U' R' U2 R U2 F R U R' U' F'"),
        Algorithm("(U) R' U' R U' R' U2 R U' R' F' U' F U R"),
        Algorithm("(U2) r U2 R' U' R U' r' U' F U R U' R' F'"),
        Algorithm("(U') F U2 R U R' U R U R' U' R U' R' U F'"),
        Algorithm("R U R' F R F' r U R' U2 r' U' r U r'"),
        Algorithm("R' U R U2 R2 U' F' U F R2 U' R' U2 R"),
        Algorithm("(U') F R U2 R' U2 R U R' U2 R U R' U F'"),
        Algorithm("(U') F U R U' R' F2 U' F r U' r' U r U r'"),
        Algorithm("(U2) R' F R F' U' r' D' r U r' D r"),
        Algorithm("(U) R' U R U' R' U' R U R' U R y R U' R' F' U' F"),
        Algorithm("(U') R' U R U R' U F' U F R' U' R2 U' R2 U2 R2"),
        Algorithm("(U) r' U' R U2 R' U2 R' F R F' r U' r' U r"),
        Algorithm("(U2) r' F R F' r U R' U' F U R U' R' F'"),
        Algorithm("R' F R F' r U r' U2 M' U M"),
        Algorithm("R U' R2 U R U2 R2 F R F' R' U R' U' R2"),
        Algorithm("(U2) R' F R U F U' R U R' U' R' F' R U2 r U2 r'"),
        Algorithm("(U) F' R U R' U' R' F R U' F' U' F U R U R'"),
        Algorithm("(U) R U R' U R U2 R2 U2 R U' R' F' U F U' R"),
        Algorithm("(U') F R U2 R' U' R' U2 R U R' U R F'"),
        Algorithm("(U) F R U' R' U' F R U R' U' F' R U2 R' U' F'"),
        Algorithm("(U) r' U r' F2 R F' U' R U' R' U2 R' F2 r2"),
        Algorithm("(U) F U R' F R F' R' U' R F' R' U R"),
        Algorithm("F' r U R' U' r' F R U' r U2 R' U' R U' r'"),
        Algorithm("(U') M' U' R U R' F' R U2 R' U2 R' F R2 U' r'"),
        Algorithm("(U) R' U2 R' D' R U2 R' D R2 U R' U' F' U F R"),
        Algorithm("(U2) r D' R2 U' R U' R' U R2 D r'"),
        Algorithm("(U) F U R U2 R' U R U R' F' R' U' R' F R F' U R"),
        Algorithm("(U') F R U' R' U R U2 R' U' F'"),
        Algorithm("(U') F R U' R' U' F U R U' R' F' R U R' F'"),
        Algorithm("(U2) R U2 R' U2 R' F R F' U' F U R U' R' F'"),
        Algorithm("R U R' U' R' F R F' U2 R' U' R' F R F' U R"),
        Algorithm("(U') R' U' R U' R' U2 R U R U R' U' R' F R F'"),
        Algorithm("(U2) r U R' U' r' F R F' U' r' U' R U' R' U2 r"),
        Algorithm("(U2) R U2 R' U' R U R' U' F' U' F U R U2 R'"),
        Algorithm("F' R U R' U' R' F R U' F' U F R' F R F'"),
        Algorithm("(U2) R U2 R' U2 R' F R2 U' R' U2 R U R' F'"),
        Algorithm("(U') r' D R2 U R' U' R U' R2 D' r"),
        Algorithm("r U R' U' r' F R F' U2 F U R U' R' F'"),
        Algorithm("(U') R U R' U R U R2 U' F' U F R U R' F R F'"),
        Algorithm("(U') r U2 R' U' F' r U R' U' r' F R2 U' r'"),
        Algorithm("(U) R U' R2 U' R F R2 U' R' U R U R F' R U R'"),
        Algorithm("(U2) R U R' U R' F R F' U2 R' F R2 U R' U' F'"),
        Algorithm("(U') F U' R2 D R' U' R D' R2 U F'"),
        Algorithm("(U') F R U R' U2 R' F' r U2 R U2 r2 F r"),
        Algorithm("(U) R D r' U' r D' R' U x' U' R U R' x"),
        Algorithm("(U') R2 F R F' U2 R U2 R' F R' F' R U2 R"),
        Algorithm("(U') F R U' R' U R2 D R' U R D' R' U R' U' F'"),
        Algorithm("R' U' R U' R' U2 R U F R' F' R U R U' R'"),
        Algorithm("(U2) F R U R' F' R' F R U' R' F r U r' F R"),
        Algorithm("(U) R2 U R2 U R U2 R' U2 F U R U' F' R'"),
        Algorithm("(U2) F R' F' R U R U' R2 U' R' D' R U R' D R2"),
        Algorithm("(U') F R U R2 U' R2 U' R' F' r' F r U R' U R"),
        Algorithm("(U2) F R U' R' U R U2 R' U' F' U' F U R U' R' F'"),
        Algorithm("(U2) r U r' U R U' M' U' r'"),
        Algorithm("(U) F R U R' U' F' U F U R U' R' F'"),
        Algorithm("R' U' R U' r U R' U R U2 r' U' R' U R"),
        Algorithm("(U2) r U R' U R U2 r'"),
        Algorithm("(U) M U R U R' U R U2 R' M'"),
        Algorithm("(U') R' U' R' F R F' U R U F R U R' U' F'"),
        Algorithm("(U2) F R U R' U' R U R' U y' R' U' R U' R'"),
        Algorithm("(U2) r U' r' U R U R' U R U2 R' U r U r'"),
        Algorithm("(U') R U R' U' R U R' U r' R2 U' R' U r U' R'"),
        Algorithm("(U2) R U R' U R U' R' U' M' U R U' r'"),
        Algorithm("(U2) F U R' F R F' R U' R' F'"),
        Algorithm("(U') F U R U' R' F' U' F U R U' R' F'"),
        Algorithm("(U') R U R' U R U2 R' F U R U' R' F'"),
        Algorithm("(U2) R' U2 R U R' U R U' F R U R' U' F'"),
        Algorithm("(U) R U2 R' F R' F' R2 U' R' U R U2 R'"),
        Algorithm("(U2) R U' R' F' U F R U R' U R2 D R' U' R D' R2"),
        Algorithm("(U') R U2 R2 U' R2 U' R2 U2 R U' R' U' R' F R F' U R"),
        Algorithm("(U2) R U2 R' U' F' U' F R U R' U' R U R' U2 R' F R F'"),
        Algorithm("(U') R' U2 R U R' F' U F R U R U R' U R U2 R'"),
        Algorithm("R U2 R2 F R F' R U' R' U R U' R' U R U2 R'"),
        Algorithm("(U2) R' U2 R U R' U F' U' F U R"),
        Algorithm("(U2) R' U' F' U F R U R' U2 R U R' U R"),
        Algorithm("(U') F U' R U R' U R U' R' U' R U' R' U2 F'"),
        Algorithm("(U') r U R' U R U2 r' F U R U' R' F'"),
        Algorithm("(U2) F R U' R' U' R' U2 R U R' U R2 U R' F'"),
        Algorithm("(U2) R U' R' U' R U' R' U2 F R' F' R U2 R U' R'"),
        Algorithm("(U) R' U' R F U' R' U2 F R F' R U R' F'"),
        Algorithm("F R U' R' U R U R' U R' F R F' U' F'"),
        Algorithm("(U2) L' U2 L U2 L F' L' F"),
        Algorithm("(U2) F R' F' R U R U2 L' U R' U' L"),
        Algorithm("(U) R U R' U R U2 R' U' R' U' F U R U' R' F' R"),
        Algorithm("(U) F R U' R' U' R U' R' U' F U R U' R' F' U' F'"),
        Algorithm("(U2) R U R' U R U R' F' U F R U R2 F R F'"),
        Algorithm("R' U F' U2 F R U R' U' F' U' F U' R"),
        Algorithm("(U') F U R U2 R' U' R U R2 F' R U R U' R'"),
        Algorithm("F R U' R' F R U R' U' F' U R U R' F'"),
        Algorithm("(U') F R' F' R U2 R U2 R2 U' F' U F R"),
        Algorithm("(U2) F R U' R' U' R U R' F' R U R' U R U2 R'"),
        Algorithm("F R U' R' U' R U2 R' U' F' U2 r U R' U R U2 r'"),
        Algorithm("R' U2 R' F R F' R U2 R' U2 F R' F' R2"),
        Algorithm("(U2) F R U' R' U' R U R' F' U' R' U2 R U R' U R"),
        Algorithm("R' F' U' F U R F U R U2 R' U' R U R' F'"),
        Algorithm("F R U R2 F R U R' U' F' U R y' R' U' R U' R'"),
        Algorithm("(U') R' U2 R U R' U r U' r' F R U F R U' R' F'"),
        Algorithm("(U2) R2 U' R U F R U R' U' R' F2 U F R U' R"),
        Algorithm("(U2) F' r' F r F U R2 D R' U2 R D' R2"),
        Algorithm("(U2) r U R' U' r' F R F' r U R' U R U2 r'"),
        Algorithm("(U2) R2 F R F' R U R' U R U2 R' U R U' R' U R"),
        Algorithm("(U2) R U' R' U' F' U2 F U2 R U2 R'"),
        Algorithm("(U') R' U' F U R U' R' F' U2 R U R' U' R U R' U R"),
        Algorithm("(U') M' U R U' r' U' R U' R' F' U F"),
        Algorithm("(U') R U2 R' U' R U R' U2 R' F R2 U R' U' F'"),
        Algorithm("R U' L' U R' U' L U' F U R U' R' F'"),
        Algorithm("(U) M' U r U' r' F U' M U R' F' R"),
        Algorithm("(U) F U' R' U' F R F' R' U R2 U R' F'"),
        Algorithm("(U2) F' U' r' F r2 U R' U2 r' F r U' r' F2 R"),
        Algorithm("(U') F R' F' U' F U R2 U' F' r U R' U' r'"),
        Algorithm("R U R' U' R' F R2 U' R' U' R U2 R2 F R F' U' F'"),
        Algorithm("(U2) R U R' U' R' F R U R U2 R' U' R U R' F'"),
        Algorithm("(U') F R' F' R U R U' R' U' F R U' R' U' R U R' F'"),
        Algorithm("R' U2 R U R' F' U F R U2 F R' F' R U R U' R'"),
        Algorithm("(U) R U2 R' U' F' U F R U' R' F U R U' R' F'"),
        Algorithm("(U2) F R' F' R U R' U' R U' R' U2 R U R U R'"),
        Algorithm("(U) r U R' U' r' F R F' U F U R U' R' F'"),
        Algorithm("(U2) F R' F' R U2 R' U' R U R U2 R' U' R' U R"),
        Algorithm("(U2) F R' F' R U2 R U2 R'"),
        Algorithm("(U) R U R' U' R' F R F' U F U R U' R' F'"),
        Algorithm("F R U R' U' R' F' U' F U R U' F'"),
        Algorithm("r' D R2 U' R' U' R U' R' U R U' R2 D' r"),
        Algorithm("(U2) F R' F' R U R' U' R2 U' R2 U2 R2 U2 R'"),
        Algorithm("(U2) r' F2 r F R U R' F' U r' F r"),
        Algorithm("(U') R' F R F' U2 R U' R' U R U' R' U F' U2 F"),
        Algorithm("r' R U R' U' R U' R' U2 R U2 M'"),
        Algorithm("(U) r' U r U' R' U' R U' R' U2 R U' r' U' r"),
        Algorithm("(U2) R' U2 R U R' U R U' F U R U' R' U R U' R' F'"),
        Algorithm("(U2) R U2 R' U' F' U' F U R U' R' U' R' F R F'"),
        Algorithm("(U) r' U' r U' R' U M U r"),
        Algorithm("(U) r' U' R U' R' U2 r"),
        Algorithm("(U') R U R' U r' U' R U' R' U2 r U R U' R'"),
        Algorithm("(U') R' F' U' F U R U' R' U' F' U F R"),
        Algorithm("(U2) r U R' U' M U R U R' U' R U' R'"),
        Algorithm("(U2) r' R2 U R' U r U r' U' r U r' U r U R'"),
        Algorithm("(U2) F R U R' F R' F' R U' F'"),
        Algorithm("(U) r' F2 r U r' F U2 R U R' U r"),
        Algorithm("f R U R' U' f' U' R' U' R U' R' U2 R"),
        Algorithm("R' U' R U' R' U2 R U R' U' F' U F R"),
        Algorithm("(U) r U' r' F2 r U r' U2 F r U2 R' U R U' r'"),
        Algorithm("R' U' R U' R' U2 R U2 R' U2 R U R' F' U F R"),
        Algorithm("(U) F R U R' U2 R U R' U' F' U' F R U R' U2 F'"),
        Algorithm("(U) F R U R' U' F' U F R U R' U' R U R' U' F'"),
        Algorithm("(U) R' U R U R' U2 R U2 R2 F R F' R U R' U' R"),
        Algorithm("(U) F R U R' y' x' R U' R' U R U' R' U x U' R'"),
        Algorithm("r' U' R U' R' U R' F R F' U r"),
        Algorithm("f R U R' U' f' R U2 R' U' R U' R'"),
        Algorithm("r' U' R U' R' U2 r U R' U' F' U F R"),
        Algorithm("R' F' R U' R' U' F' U2 F R' F R F' U' F R"),
        Algorithm("(U2) F R' F' U' F U R2 U' R' U R U' R' F'"),
        Algorithm("(U) R U R' F' U R U2 R' U' R U' R' F R U' R'"),
        Algorithm("(U') R U R' U' M' U R U R' U2 r' F R F'"),
        Algorithm("(U') r U R' U' M U R U R' U2 R' F R F'"),
        Algorithm("(U2) R' U' R U' R' U2 R U R U2 R' U' F' U F R U' R'"),
        Algorithm("(U') F U R U2 R' U' R U2 R' U' R U R' U' F'"),
        Algorithm("(U') R U2 R' U2 R' F R F'"),
        Algorithm("F U' R U' F U R U' R' F' R' U F'"),
        Algorithm("(U) r' U' R U R' F R' F' r U R U R' U2 R"),
        Algorithm("(U) R' U R y R U' R2 F R F' R U R' U R U' R'"),
        Algorithm("F U' R U2 R' F' U' F U R U R' U F'"),
        Algorithm("(U) F U R U' R' F' R U R' F' U F R U' R'"),
        Algorithm("(U') R U2 R' U' R U' R' F R U' R' U R U R' F'"),
        Algorithm("r U' r' U R U R' U r U' r' F' U F"),
        Algorithm("(U2) F U' R U' R' U' R U' R' U2 F' U2 F U' F'"),
        Algorithm("R' U2 R U R' U' R U2 F R U R' U' F' R' U R"),
        Algorithm("(U') R U2 R D R' U2 R D' R2 U' R' U' F' U F R"),
        Algorithm("(U2) F R' F' U2 R U R' U R2 U' R' U R U2 R'"),
        Algorithm("(U2) F R' F' R U R U' R' U R U2 R' U' R U' R'"),
        Algorithm("R D R' U' R D' R2 U' R' U' F' U F R U R"),
        Algorithm("(U') r U r' R U R' U' r U' r' R' U' F U R U' R' F' R"),
        Algorithm("(U) F' r U' r' F U2 F R U' R2 F R F'"),
        Algorithm("(U2) R' F R2 U R' U' R U R' F' R' F R U' F'"),
        Algorithm("(U') F U R U2 R' U R U R' F' U2 r U r' R U R' U' r U' r'"),
        Algorithm("(U) F U R U' R' F' U F R U' R' U' R U R' F'"),
        Algorithm("(U) F R U' R' U' R U2 R' U2 R' F R F' R U R' F'"),
        Algorithm("(U2) F R U' R' U' R U R' F' U R U2 R' U' R U' R'"),
        Algorithm("(U2) R2 F R F' U' R U2 R' U2 R"),
        Algorithm("(U2) F R U' R' U R U R' F' U' R' U' F' U F R"),
        Algorithm("(U') F' U' r' F r2 U R' U' r' F R"),
        Algorithm("(U') R U2 R' U F' U F R U' R' U2 R U2 R'"),
        Algorithm("(U') R U2 R' U2 R F U R U' R' F' U' R' U' R U R'"),
        Algorithm("R' F' U' F U F R U R' U' F' U R"),
        Algorithm("(U') R U2 R' F' U2 F R U' R' U R U' R'"),
        Algorithm("R' U R U2 R' F R' F' R2 U R' U R U' R' U R"),
        Algorithm("(U') R U R' U' R' U' F R' F' R U R2 U' R'"),
        Algorithm("R U2 R' U' F' U F R U R' U' R U R' U' R U' R'"),
        Algorithm("R U2 R' U2 F' U2 F U R U R'"),
        Algorithm("F' U' F R U R' U r U R' U' M"),
        Algorithm("(U') R' D R' U' R D' U R U' F R F'"),
        Algorithm("(U) F R U' R' U' R U2 R' F' U' F' r U r'"),
        Algorithm("(U2) F U R' D' R U' R' D R2 U R' U' R U R' U' F'"),
        Algorithm("R U2 R2 U' F' U F R U' R' F R F'"),
        Algorithm("M' U M U2 R' F R F' r U r'"),
        Algorithm("(U') R' F R F' M U R U' R' r U r' U' r U R'"),
        Algorithm("(U') F R U' R' U R U2 R' U' R' F' r U R U' r'"),
        Algorithm("(U') F R U' R' U' R U R2 F' R U R U R' U' R U' R'"),
        Algorithm("(U) F R U' R' U' R U R' F' U2 F R' F' R U R U' R'"),
        Algorithm("R U R' U R U' y R U' R' U R U' R' F'"),
        Algorithm("(U') R' U' R' F R F' U R U' F R U R' U' F'"),
        Algorithm("(U) r' R2 U2 R' U' R U' R' U' M'"),
        Algorithm("(U') R' U2 R U R' U R F R U R' U' R U R' U' F'"),
        Algorithm("r U r' U R U' R' U2 R U2 R' U2 r U' r'"),
        Algorithm("(U) F U' R' U R U F' R' U R' F R F' U R"),
        Algorithm("(U) R' U R U R' U r U' R' U R U r' U R"),
        Algorithm("(U2) M' U' R U2 R' U' R U' R' U' M"),
        Algorithm("r' U' R U' R' U R U M' U' R' U R"),
        Algorithm("(U) R U2 R' U' R U' R' U' R U R' U' M' U R U' r'"),
        Algorithm("(U') R' U' R' F R F' U F' U' F U R"),
        Algorithm("(U') r' U2 R U R' U r F R U R' U' R U R' U' F'"),
        Algorithm("(U') R' U' R U R' U' R' F R F' R U' R' F' U' F R"),
        Algorithm("R U R' U F' U F U' R U' R' U R U2 R'"),
        Algorithm("(U') F R U R' U' R U R' U' R U' R' F' r' F r"),
        Algorithm("(U') r U r' U' F R U R' F r U r2 F r"),
        Algorithm("(U) F U R U' R' F' U2 r U2 R' U' R U' r'"),
        Algorithm("(U2) R' U' F' U F R U R U2 R' U' R U' R'"),
        Algorithm("(U') r U R' U R U' R' U R' F R F' R U2 r'"),
        Algorithm("(U') R' U2 R2 U2 F R F' U2 R' U2 R' U2 R"),
        Algorithm("(U') F R U R' U' R U R' U' F' U' F U R U' R' F'"),
        Algorithm("(U') R' U' R U' R' U R' F R F' U R"),
        Algorithm("F R U R' U' F' U' F U R U' R' U R U' R' F'"),
        Algorithm("(U') F R U R' U' F' r U2 R' U' R U' r'"),
        Algorithm("(U) R' U2 R U2 R' U' R U2 R' U' F' U' F U' R"),
        Algorithm("(U2) F U R U2 R' U2 r' F R F' r U' R' U' F'"),
        Algorithm("(U) R' U F' U2 F R U R' U' R U' R' F R' F' R2"),
        Algorithm("(U2) F R' F' R U2 R U' R' U R U' R' U R U2 R'"),
        Algorithm("(U2) R' U' R y r U' r' U r U r'"),
        Algorithm("(U') R U R2 F' U' F U R2 U' R' U' R' F R F'"),
        Algorithm("(U2) R' F R U' M' U F' r U r' U' M"),
        Algorithm("(U2) F R U R2 U2 R2 U R2 U F' R U R U' R'"),
        Algorithm("(U) R U2 R' U R' U' F U R U' R' F' R U' R U' R'"),
        Algorithm("(U2) r' F R F' R U M' U2 M U M' U R'"),
        Algorithm("(U) r' U' R' F R F' U r U' r' F R F' r U R'"),
        Algorithm("(U) R U' R2 F' U' F U R2 U' R' U R U R'"),
        Algorithm("(U2) R U R2 F' U' F R2 U' R' U R' U R"),
        Algorithm("(U) R U R' U R U' R' F' U F R' F R F2 U F"),
        Algorithm("(U) F R U' R' U2 R' F' U' F U R U R U R' F'"),
        Algorithm("(U2) R U' R' U' F' U2 F U R U R' U' R U' R'"),
        Algorithm("(U) r' U' F' U2 F R U2 R' U' r U2 R' U' R"),
        Algorithm("(U') F R U R' U' R U' R' U R U2 R' U' F'"),
        Algorithm("(U') r U2 R' U' R2 D R' U R D' R' U2 r'"),
        Algorithm("(U2) R U R2 F' U' F U R U' R U' R'"),
        Algorithm("(U') r U R' U R U' R' U R2 D R' U2 R D' r' R'"),
        Algorithm("(U') R U2 R' U' R U' R' U2 R' F R U R' U' F' U R"),
        Algorithm("F R U' R' U' R U2 R' U' F' U' R' U' F U R U' R' F' R"),
        Algorithm("R' U' R U' R2 F R F' R U2 R' U R U2 R' U2 R"),
        Algorithm("(U2) R U R' U' R' F R F' U R' F' U' F U R"),
        Algorithm("R U' R' U M U R U' R2 D' R U' R' D r"),
        Algorithm("R U2 R' U' F' R U2 R' U' R U' R' U' F R U' R'"),
        Algorithm("(U) F' U2 F U R U' R' U' R U' R' U F' U2 F"),
        Algorithm("(U) r' U' R U' R' U2 r U r U R' U' r' F R F'"),
        Algorithm("(U') F R U R' U' R' D' R U' R' D R2 U' R' U F'"),
        Algorithm("(U) r' U' r U' R' U R F' r' U r F"),
        Algorithm("(U) F R' F' R U R U R' F R' F' R U' R U' R'"),
        Algorithm("(U2) F U R U' R' U R U' R' U R U2 R' U' R U R' F'"),
        Algorithm("(U2) R U R' U' R' F R2 U R' U' F'"),
        Algorithm("R U2 R' U' F' U F R U' R' U2 R' U' R U' R' U2 R"),
        Algorithm("(U2) R U' R U R U R' U' R' U' R2 U2 R' F R F'"),
        Algorithm("R U R' U R U' R' U R U' R' F' U F U R U2 R'"),
        Algorithm("(U2) r U2 R' U' R U' r' R' U' F U R U' R' F' R"),
        Algorithm("(U2) R2 F R F' R U R U R' U R U2 R' U R' U2 R"),
        Algorithm("(U2) F' R U2 R' U2 R' r' F r U' F R2 U' R'"),
        Algorithm("(U') R' F R F' r U' r' R' F R F' r U2 r'"),
        Algorithm("(U2) R U2 R' U' R U' R2 U' F U R U' R' F' R"),
        Algorithm("R' F' U' F U R r U R' U' r' F R2 U R' U' F'"),
        Algorithm("(U2) R' U' F' U F U' R U R' F R U R' U' R' F' R2"),
        Algorithm("(U2) F R U' R2 F' U2 R U R' U R2 U2 R' F U' F'"),
        Algorithm("(U) r' U' r U' R' U r' D' R U R' D r R"),
        Algorithm("(U) r' U' R U' R' U R' D' R U R' D r R"),
        Algorithm("(U') R2 F R F' R U2 R' F' U2 F U' R U' R' U2 R"),
        Algorithm("(U) M U R' U2 R U R' U R U M'"),
        Algorithm("(U2) F R U R' U' F' U R' U' R' F R F' U R"),
        Algorithm("R U R' U R' F R F' R U2 R2 F' U' F U R"),
        Algorithm("(U2) R U2 R' U' R U' R' U' F R U R' U' R U R' U' F'"),
        Algorithm("(U) R' U F' R U R' U R U2 R' U2 F U' R"),
        Algorithm("(U2) r R2 U2 R U R' U R U M"),
        Algorithm("(U') R U R' U R U2 R' r U R' U' r' R U R U' R'"),
        Algorithm("(U') R' U' R U' R' U y' R' U R U' R' U R B"),
        Algorithm("(U') r U R' U R U' R' U' M U R U' R'"),
        Algorithm("(U2) F U' R U2 R' U R U R' U' R U2 R' U2 F'"),
        Algorithm("(U2) r U R' U' r' U2 R U R' U R U' R U' R'"),
        Algorithm("(U2) F R U R' U' R U R' U' F' U2 R U2 R' U' R U' R'"),
        Algorithm("R U R' U R U2 R2 U' R' F R F' U R"),
        Algorithm("(U2) F R2 U' R2 U' R2 U R' F' R U R' U' R'"),
        Algorithm("(U2) F R U' R' U2 R U R' U R U' R' U R U' R' F'"),
        Algorithm("(U') R' U' R U' R' U R' F R F' R U' R' U2 R"),
        Algorithm("(U') F R U' R' U R U R' U R U2 R' U' R U R' F'"),
        Algorithm("f R U R' U' f' R' U2 R U R' U R"),
        Algorithm("(U') R' U' F' U F R U r' U2 R U R' U r"),
        Algorithm("F R U' R' F' r' F' r U r' F U' R U' R' U2 r"),
        Algorithm("(U) R U R' U R' F R F' R U2 R'"),
        Algorithm("(U) F U R' F R F' U' F' R U R' U R U2 R'"),
        Algorithm("(U) R' F' U' F U R U' r' U2 R U R' U r"),
        Algorithm("(U) F U R U' R' F' U F R U R' U' R U R' U' F'"),
        Algorithm("(U) R' F R U R' U' F' U R r U R' U R U2 r'"),
        Algorithm("(U') R' U' R U' R' U R U' R' U' F' U' F R U R' U2 R"),
        Algorithm("(U2) R U R' U' R U' R' U2 R U R' F R' F' R2 U R'"),
        Algorithm("(U') F R U' R' U' R U R' F' r U R' U R U2 r'"),
        Algorithm("(U') R U' R2 U' F' U F R U' R' F R F' R U2 R'"),
        Algorithm("(U') F R U' R' U' R U R' U R' F R F' R U' R' F'"),
        Algorithm("F U R U R' F' U F R U R' U R U R' U' F'"),
        Algorithm("r' U r U2 r' R U R' U' r U' R' U' F' U' F R"),
        Algorithm("(U2) R U2 R' U' R U R' U F' U F R U' R' U R U' R'"),
        Algorithm("(U2) r U R' U R U2 r' U' r U R' U' r' F R F'"),
        Algorithm("(U') R' U' R F U R U2 R' U2 R' U2 R2 U2 R' U' F'"),
        Algorithm("F R U R' U' F' U F U R U2 R' U' R U R' F'"),
        Algorithm("(U') R' U R U' M' U' R' U R2 D R' U R D' r'"),
        Algorithm("(U) F R U' R' U R U R' F' U' F R U R' U' F'"),
        Algorithm("(U') R U R' U R2 U R' U' R' U F R F' U R'"),
        Algorithm("(U2) R U' R' F' U F R U R' U2 R U2 R'"),
        Algorithm("(U2) R U R2 F' U' F R2 U' R2 U2 R"),
        Algorithm("(U') F U R' U' R U R U2 R' U' R' U R U' R U R' F'"),
        Algorithm("(U2) r U R' U R2 D R' U' R D' R' U' r'"),
        Algorithm("R U R' U R U' R' U R U2 R' U F R U' R' U' R U R' F'"),
        Algorithm("(U') R2 U' F R F' R U' R' U F' R' U R F R"),
        Algorithm("(U') R' U' F U R U' R' F' R U2 R U R' U R U2 R'"),
        Algorithm("(U) R' U' R U R U R' U' R' F R F' R' U R"),
        Algorithm("(U2) R U R2 U' R' F R F' U R U R U' R'"),
        Algorithm("(U) R' F R U R' U' F' U R F R' F' R U2 R U2 R'"),
        Algorithm("(U2) r U R' U R' F R F' R U' R' U' r' F R F'"),
        Algorithm("(U2) R U R' U' R' F R U R' U' F' U R U R U' R'"),
        Algorithm("R U2 R' U' F' U F U R U' R' U R U2 R'"),
        Algorithm("r' U2 R U R2 D' R U' R' D R U2 r"),
        Algorithm("(U2) R U R' U' R' F R F' U R' U' R' F R F' U R"),
        Algorithm("(U) F R' F' R U2 R' F R F' R U' R' U R U2 R'"),
        Algorithm("(U2) R U R' U R' F R F' R U' R' U' R' F R F'"),
        Algorithm("(U) R' U' R U F R U R' U' F' R' U R"),
        Algorithm("(U') F R U' R' U R U R' U R U' R2 F' R U R U' R'"),
        Algorithm("r' D' R U R' D R2 U R' U2 R U r R2"),
        Algorithm("(U) R U2 R2 U' R2 U' R2 U2 R U R U R' U' R' F R F'"),
        Algorithm("(U2) F U' R U' R' U2 R U' R' U2 R U2 R' F'"),
        Algorithm("(U2) F R U R2 U' F' U F R2 U' R' U' R U R' F'"),
        Algorithm("r' R U2 R' F' U F U' r U' r' U' r"),
        Algorithm("(U2) R U R' U R U' R' U F' U F U R' F R F'"),
        Algorithm("(U') r U' r' U M' U' F R' F' R U M"),
        Algorithm("R U R' U R U' R' U R U' R' F' U F R U' R'"),
        Algorithm("(U) R U R' y R' F R U' R' F' R"),
        Algorithm("(U) R U2 R2 U' F' U F R U R U' R' U R U2 R'"),
        Algorithm("(U') R U R' U2 F U R U' R' F' R U R' U2 R U2 R'"),
        Algorithm("(U2) F R' F' R2 U' R' U' F R U R' U' R' F' R"),
        Algorithm("(U') R U' F R2 U R' U' R2 F' U2 R' U R U' R'"),
        Algorithm("(U') F R U' R' U2 R U R' F' R U' L' U R' U' L"),
        Algorithm("R' U' R U' R' U2 R U F R U R' U' R U R' U' F'"),
        Algorithm("(U) M U' R U R' U R U2 R' U' M'"),
        Algorithm("(U) r' U' R U' R' U2 r U' R U2 R' U' R U' R'"),
        Algorithm("F' U2 F U' R U R U R' F' U F R U' R' U' R'"),
        Algorithm("(U) R U' R' U2 R' U2 R U R' F U R2 U' R' F'"),
        Algorithm("(U2) F R U' R' U2 R U R' F' U' R' F' U' F U R"),
        Algorithm("r' R2 U R' U R U2 R' U M'"),
        Algorithm("R' F' U' F U R U2 F R U R' U' F'"),
        Algorithm("(U) R' U' R' F R F' U R U' R' U' R' F R F' U R"),
        Algorithm("(U') F U' R' U R U F' R' U2 R F R U R' U' F'"),
        Algorithm("(U2) r U R' U' r' R U R U' R' U R' U2 R U R' U R"),
        Algorithm("(U) r' U' R U' R' U2 F' r U' r' F2 r"),
        Algorithm("(U) R' U2 R2 U R2 U R2 U2 R2 U' F' U F R"),
        Algorithm("(U) F R U R' U' F' U r U r' U R U' R' r U' r'"),
        Algorithm("(U') R U2 R' U' R U' R' F R U R' U F' U' F U' F'"),
        Algorithm("(U') R' F R F' r U R' U' R U2 R' U2 r' F R F'"),
        Algorithm("(U') F U R U' R' U R U' R' F' U' F U R U' R' F'"),
        Algorithm("(U') F U R U' R' U R U2 R' U2 R U R' F'"),
        Algorithm("(U2) F U R' F R F' R' F R F' R U' R' F'"),
        Algorithm("(U) R U2 R' F R' F' R U' R U R' U' R U' R'"),
        Algorithm("(U) F R U R' U' F' U r U R' U R U2 r'"),
        Algorithm("R' U2 R U R' U R U R' U' R' F R F' U R"),
        Algorithm("(U) F R U R' U' R U R' U' F' U F U R U' R' F'"),
        Algorithm("R U2 R2 F R F' R U2 R2 U2 R U R' U R"),
        Algorithm("(U') R' F R U r' F R F' r U' R2 F' R U' R U' R'"),
        Algorithm("(U) r' U' R U' R' U2 R F' r U R' U2 r' F2 r"),
        Algorithm("R U R' U' R U' R' U' y F R U R' U F'"),
        Algorithm("(U') R U2 R' U2 R' F R F' U' r' F R F' r U R'"),
        Algorithm("(U2) R' U R U2 R' U' R U' R' F' U2 F R U R' U2 R"),
        Algorithm("R' U' F U R U' R' F' R U' R' F2 r U r' F R"),
        Algorithm("(U2) F R U R' U' F' R' F R U R' U' F' U R"),
        Algorithm("(U') R U' R' U R U F R U R' U' F' R' U2 R U2 R'"),
        Algorithm("(U) L' U R U' L U R' F R U R' U' R U R' U' F'"),
        Algorithm("(U2) F U R U2 R' U' R U R' F' U' R' F' U' F U R"),
        Algorithm("(U2) r U R' U R2 D R' U2 R D' R' r'"),
        Algorithm("(U2) R' U2 R U F R2 U' R' U R U R F'"),
        Algorithm("F' U' F r U r' U' R U' R' U' r U r'"),
        Algorithm("(U2) R U R' U R U2 R' U2 R' F R U R' U' F' U R"),
        Algorithm("(U') R U' R2 U2 R2 U R2 F R F' R' U R2 U R'"),
        Algorithm("(U) R' U' R U' R' U2 F R U R' F' R F U' F'"),
        Algorithm("(U2) R U2 R2 F R F' R' F R F' U2 R' F R F'"),
        Algorithm("(U') R2 D' R U2 R' D R2 U R' F' U F R"),
        Algorithm("F' U' F R U R' U' R U' R' U' r U R' U' r' R"),
        Algorithm("(U2) r U R' U R U2 r' U F' r U R' U' r' F R"),
        Algorithm("(U') F R U2 R2 F R F' U R U R' U' R U' R' U' F'"),
        Algorithm("(U2) r U r' U R U' r D R' U R D' R' U2 r'"),
        Algorithm("R' U' F U R U' R' F r U r' F U' F' U F R"),
        Algorithm("(U') r' F R U R' F U' F' R U' R' U2 R U2 M'"),
        Algorithm("(U') R' F R F' U' F R' F' R2 U R' U' R U' R'"),
        Algorithm("(U) r' U r' F2 R F' U2 R U R' U R' F2 r2"),
        Algorithm("(U) R U' R' U' R U' R' U2 F' U F U' R U R'"),
        Algorithm("(U2) r U R' U' r' F R U R U' F' r U R' U' r'"),
        Algorithm("(U2) R' U' R' F' U F U R' U' R2 U' F' U2 F R'"),
        Algorithm("(U2) r U r' F' r U R' U' r' F r U R U2 r'"),
        Algorithm("(U2) R U R U F R F' U2 R' U' r U R' U' r'"),
        Algorithm("(U') F R' F' U' R' U' R U F R U R U' F'"),
        Algorithm("(U2) R U R' U R' F R U R' U' F' U R U' R U2 R'"),
        Algorithm("(U') R' U2 R U2 F R U R' U' R' U R2 U' R' F'"),
        Algorithm("(U2) F R2 D R' U R D' R2 U' R U R' U' F'"),
        Algorithm("(U2) R U R' U' R' F R F' U2 F R U' R' U R U R' F'"),
        Algorithm("(U) r' D' R U R' D R2 U R' U' M' U' R U R'"),
        Algorithm("(U') R U2 R' U2 R' F R F' U2 R U2 R' U' R U' R'"),
        Algorithm("(U) r' F R F' r U' R' U' R U R' U2 R' F R F'"),
        Algorithm("(U') R U2 R' U2 R' F R F' U R' U' R U' R' U2 R"),
        Algorithm("(U2) F R U R' U' R U R' F' R' F U' F' U R"),
        Algorithm("(U) R' F R F' r U' R' U' R U r' U2 R' F R F'"),
        Algorithm("(U2) r U R' U R U2 r' F R' F' r U R U' r'"),
        Algorithm("(U2) F R' F' R U2 r' F R F' r U' R' U R U2 R'"),
        Algorithm("R' U2 R U' R' U' r' F R F' R U' R' U r"),
        Algorithm("R' U R U2 R2 U' F' U F R U' R U R' U R"),
        Algorithm("(U2) R U R' U' R' F R F' U2 R U R' U' R' F R F'"),
        Algorithm("(U) F U R U2 R' U' R U R' F' R U2 R2 F R F' R U2 R'"),
        Algorithm("(U) R U R' F' U2 F R U' R' U2 F R U R' U' F'"),
        Algorithm("R U2 R2 F2 r U' R U' R' U2 r' F2 R"),
        Algorithm("F R U R' U' F' U2 R' F' U' F U R"),
        Algorithm("(U') M' R' U' R U' R' U2 R U' M"),
        Algorithm("(U2) M' U R' U' R U' R' U2 R U M"),
        Algorithm("r' U r2 U' r2 U' r2 U r' U R U R' U R U2 R'"),
        Algorithm("R U2 R' U F' U' F' r U r' U' r' F r F"),
        Algorithm("(U2) r U R' U R U2 r' U R' U2 R U R' U R"),
        Algorithm("(U') R' U' R U' R' U2 R U R U R' U' M' U R U' r'"),
        Algorithm("(U) R U' R' U' R U R' U' r R U R' U R U2 R' r'"),
        Algorithm("(U) R U R' U R U2 R' r' U r2 U' r2 U' r2 U r'"),
        Algorithm("F R U R' U' F' U F R U R' U' F'"),
        Algorithm("(U2) F R U R' U' F' r U r' R U R' U' r U' r'"),
        Algorithm("(U') r U r' R U R' U' r U' r' U' F U R U' R' F'"),
        Algorithm("(U2) R U2 R2 U' R2 U' R2 U2 R U F U R U' R' F'"),
        Algorithm("(U') R' F' R U' F U2 R U R' U F' U R' F R"),
        Algorithm("(U') R U2 R' U' R U' R' U' R' U' R' F R F' U R"),
        Algorithm("(U2) R' U2 R U R' U F' U' F U' R U R' U R"),
        Algorithm("r' U' R' F R F' R' F R F' U F' U' F U r"),
        Algorithm("R U' R' U2 R U y R U R' U R U R' F'"),
        Algorithm("(U') R U2 R' U' F' R' U' R F R' U R2 U2 R'"),
        Algorithm("(U) r' U' F' U F U' R U' R' U2 r"),
        Algorithm("R U2 R2 F R F' R U2 R' U R U2 R' U' R U' R'"),
        Algorithm("F U R U' R' U R U' R' F' U' F R U R' U' F'"),
        Algorithm("R' U' R U' R' U R U' R' U R y R U R' U' F' U2 F"),
        Algorithm("(U) R U R' U R U' R2 F R F' R U R' F' U F"),
        Algorithm("(U') F' R U R' U R U2 R' U2 F' r U r' U2 F"),
        Algorithm("(U) r' U2 R' F' R U R U' R' F U2 r"),
        Algorithm("(U) R U2 R' U' R U R' U2 R' U' F R F' U' R' U2 R"),
        Algorithm("(U') R2 D' r U r' D R F' U' F R"),
        Algorithm("(U) R' F' U2 F R U R' U' R U2 R' U2 R U2 R' U2 R"),
        Algorithm("(U2) R' U2 R2 U R2 F' U F R F' U F R U' R'"),
        Algorithm("(U2) r U R' U2 r' F R U R U' R' F' r U r'"),
        Algorithm("(U') F' U' r U r' U' r' F r U r U' R' U R U r'"),
        Algorithm("(U) r' F R F' r U r' U M' U2 M U M'"),
        Algorithm("(U) F R U' R' U R U R' F' U R U R' U' R' F R F'"),
        Algorithm("(U') R' F' U' F U R F' r U r' U2 r' F2 r"),
        Algorithm("F R U' R' U R U2 R' U' F' U r U R' U' r' R U R U' R'"),
        Algorithm("(U') R U R' U R U' R2 F' U' F U R U' R U R' U' R U' R'"),
        Algorithm("(U') R2 D' r U r' F r U r' F2 D R2"),
        Algorithm("(U) R' F2 R U2 R U2 R' F2 U2 R' F R F'"),
        Algorithm("(U') r U R' U' r' F R2 U' R' U R U2 R' U' F'"),
        Algorithm("(U2) R' F' U' F U r' D' r U' r' D r U R"),
        Algorithm("(U') F U F R U R' U' F' U R U R' U R U R' F'"),
        Algorithm("(U2) F U R U2 R' U R U R' U R U' R' F'"),
        Algorithm("(U') r' F' r U r U' r' F2 R U' R' U R U R' F'"),
        Algorithm("(U') R U R' U' R' F R2 U' R' U R U2 R' U' F'"),
        Algorithm("(U2) R U R' U R U2 R' U2 F U R U2 R' U' R U R' F'"),
        Algorithm("(U') F' U' F U r U R' U' R U2 R' U' R U' r'"),
        Algorithm("R U R2 F R F' R U R' F' U' y' R U R' U R"),
        Algorithm("(U') R U R' U' R' F R F' r U2 R' U' R U' r'"),
        Algorithm("(U2) F R' F' R U2 R U2 R' U R U R' U R U2 R'"),
        Algorithm("R2 D R' U R D' R' U R' U' F' U F R U' R'"),
        Algorithm("(U') r U R' U' r' F R F' r U2 R' U' R U' r'"),
        Algorithm("F R' F R U2 r U' r' U2 F r U r'"),
        Algorithm("R U R' U' R U' F U F' R2 F R U' F'"),
        Algorithm("R' U' R U2 F R U R F R F' R U' F'"),
        Algorithm("R U2 R2 U2 R2 U R2 U R U' R' F R F'"),
        Algorithm("(U') F R U R' U' R U' R' U' R U R' U R U' R' F'"),
        Algorithm("(U) R U2 R' U' B' R2 U R U' R' U' R' f z'"),
        Algorithm("(U) R' F U' F' U R U F U R U' R' U' F'"),
        Algorithm("(U') R' F' U' F U R2 U2 R' U2 R' F R F'"),
        Algorithm("(U2) r U' r' U' r U r' F' U F r U R' U R U2 r'"),
        Algorithm("R U R' U' F' U' F R' U' R2 U' R2 U2 R2 U R'"),
        Algorithm("(U') F R U' R' U' R U R' F' U2 R U2 R2 F R F' R U2 R'"),
        Algorithm("F U R U' R' U' R U' R' U' R' F R F' U2 F'"),
        Algorithm("(U) F R U R' F R' F' R U' R U' R' U R U R' F'"),
        Algorithm("(U) R' U' F' U F R U2 R U2 R' U2 R' F R F'"),
        Algorithm("(U2) r U R' U R U2 R U R' U' r' F R F' R'"),
        Algorithm("(U) M U r U' r' U' r U R' F' U' y' R U R' U R"),
        Algorithm("(U2) R U' R' U' F' U2 F U2 R U' R' U R U2 R'"),
        Algorithm("R' U' R' F R F' U R U' R U2 R' U2 R' F R F'"),
        Algorithm("(U) R' U' r U' R' U' R U r' U' R U' R' U' R"),
        Algorithm("(U2) r U' r' U R U R' U r U2 r' U r U r'"),
        Algorithm("R' U' R U' r U R2 U R2 U2 r'"),
        Algorithm("(U2) R' U' R U M U' R' U r R U R' U R U2 R'"),
        Algorithm("R' U' F' U F R U2 F U R U' R' F'"),
        Algorithm("(U2) F U' R U R' U2 R U R' U R U R' U F'"),
        Algorithm("(U2) r U r' U R U' R2 r U' M U R U' R'"),
        Algorithm("(U) r U r' R U R' U R U2 R' U2 r U' r'"),
        Algorithm("(U2) R U R' U R U2 R' U' r U R' U' r' R U R U' R'"),
        Algorithm("(U') R U R' U R' F R F' R U' R' F' U2 F R U' R'"),
        Algorithm("M' U2 R U' r' U R U R' U2 r U r'"),
        Algorithm("(U2) R U R' U' M' U R U' r' R U R' U R U2 R'"),
        Algorithm("(U2) r' U2 R U R' U r U R' U' R' F R F' U R"),
        Algorithm("(U2) R U R' U' R' F R F' R U' L' U R' U' L"),
        Algorithm("(U') R' U2 R U R' F R' F' R2 U' R' U2 R"),
        Algorithm("(U) r U2 R' F R' F' R2 U' R' U R U2 r'"),
        Algorithm("(U') R U R' U R U2 R' U' R U R' F' U2 F R U' R'"),
        Algorithm("(U) R' U' F' U F R F R U R' U' R U R' U' F'"),
        Algorithm("R' U F2 U' F R U R' U' F' U2 F2 U' R"),
        Algorithm("(U') F R U R' U' R U R' U' F' U' R' U2 R U R' F' U F R"),
        Algorithm("(U') R U2 R2 U' R2 U' R2 U F' U F R"),
        Algorithm("(U) R' U' R' F R F' U R U' R U R' U R U2 R'"),
        Algorithm("(U') R U R' U R U2 R' U R' U' F' U F R"),
        Algorithm("(U2) F R U' R' U2 R U R' U R' F R F' R U' R' F'"),
        Algorithm("(U') R' U2 R U R' U' R U y r U' r' U r U r'"),
        Algorithm("(U2) F U R U2 R' U R U R' F' U' F U R U' R' F'"),
        Algorithm("F R U' R' U' R' U' R U' R' U2 R2 U2 R' U' F'"),
        Algorithm("(U2) R' U2 R U R' U' R U F R U' R2 U2 R2 U R' F'"),
        Algorithm("F R U R' U r U' r' U' r F R U' R' F' r'"),
        Algorithm("F' U F R U R' F2 r U r' U r' F r F"),
        Algorithm("(U') r' U' F' U F r F' r U R' U' r' F R"),
        Algorithm("(U) R U R' U R' U' F' U F R2 U' R'"),
        Algorithm("F R U R' U' R U' R' U' R U2 R' U' F'"),
        Algorithm("(U) R U R' U' R U R' F' U2 F R U2 R'"),
        Algorithm("(U2) F U R U2 R' U' R U R' F'"),
        Algorithm("(U2) F R U' R' U R U R' F' R U R' U R U2 R'"),
        Algorithm("(U) r U R' U R U2 r' U' R U R' U' R' F R F'"),
        Algorithm("(U2) R U R' U' R' F R F' R U R' U R U2 R'"),
        Algorithm("(U2) R U R' F' R U R' U R U2 R' U F R U' R'"),
        Algorithm("(U2) r U' r' F R U R' U' R F' r U R2 U R U' r'"),
        Algorithm("(U') R' U' R F U R U' R' F' U2 R' U R U' R' U2 R"),
        Algorithm("(U2) R U R' U' R' F R F' U' R' U2 R U R' U R"),
        Algorithm("r' U2 R U R' U r R U R' U' R' F R F'"),
        Algorithm("r U r' R U R' U' r U' r' U' L' U R U' L U R'"),
        Algorithm("(U2) R F U R' U' F' U2 R U2 R' U' R2 U' R2"),
        Algorithm("(U') R' U' R U' R' U' r U R' U' F' U' F M R"),
        Algorithm("(U) R' U2 F U R U2 R' U' r U2 r' U' F' U R"),
        Algorithm("(U) F R U R' U' R U R' U F' U F R U' R' U F'"),
        Algorithm("(U) F' r U R' U F' r U r2 F2 R U' R' F R"),
        Algorithm("(U) F' U F U' R U' R' U' R U R' F R' F' R"),
        Algorithm("(U') F R U R2 U' F' U F R2 U' R' U R U R' F'"),
        Algorithm("(U2) r U' r' U' r U r' y' R' U R"),
        Algorithm("(U') r' D' r U' r' D r U x U R' U' R x'"),
        Algorithm("(U') R' U2 R U2 R' U2 R U2 R' U R U' R' F' U2 F R"),
        Algorithm("(U2) F U R U' R' U R U' R2 D' R U R' D R U' F'"),
        Algorithm("(U) F R U R' U' R' F' R2 U R' F' U2 F R U2 R'"),
        Algorithm("(U2) r U' r' F R U R' U' R' F' r U2 R U' r'"),
        Algorithm("R U R' y' R2 r U R U' r' U' R"),
        Algorithm("r U2 r' U2 R' F R U R U' R' U F' U' R' F' R"),
        Algorithm("(U) R' F' U' F U' R' D' r U2 r' D R2"),
        Algorithm("(U) R U R' F' U F R U' R' r U R' U R U2 r'"),
        Algorithm("(U2) R' U' R' F' R U R U' R' U' F U' R U R' U R"),
        Algorithm("r' F' U' F U r F R' F' R U2 R U2 R'"),
        Algorithm("(U) R U2 R' U' F' U F R U' R' U R' U' F' U F R"),
        Algorithm("(U) r U R' U' r' F R F' R' F' U' F U R"),
        Algorithm("(U2) R' U' R U R' U F U R U' R' F' R U' R' U R"),
        Algorithm("(U) F' U' F U R U' R' F' U F R U R' U2 R U' R'"),
        Algorithm("r' U' M' U R' D' R U2 R' D R2 U r' U r"),
        Algorithm("(U) r U R' U' r' F R F' U' F R U R' U' F'"),
        Algorithm("(U2) F U R U' R2 F' R U R U' R'"),
        Algorithm("(U2) F U' R U' R' U' F' U F R U2 R' U F'"),
        Algorithm("(U') R U R' U2 R' U' F U R U' R' F' R2 U2 R'"),
        Algorithm("(U) F U R U' R' F' U2 R' U' F' U F R"),
        Algorithm("(U) R' F' R U2 R' U' R U' R' U2 F R"),
        Algorithm("(U) F U R U' R' F' U' R' U2 R U R' F' U F R"),
        Algorithm("(U') R' U F' U2 R U2 R' U' R U' R' F U' R"),
        Algorithm("(U') R U r' U R U R' U' r U R' U R U R'"),
        Algorithm("(U') R' U2 R U R' U R U r' U r2 U' r2 U' r2 U r'"),
        Algorithm("R U R' U r' U' R2 U' R2 U2 r"),
        Algorithm("r U R' U R U2 r' f R U R' U' R U R' U' f'"),
        Algorithm("(U2) R U R' U R U2 R' U' F R U R' U' R U R' U' F'"),
        Algorithm("(U) R' F' U' F R U R' F' R U R' U' R' F R2"),
        Algorithm("R U R' U' M' U R U' r' U' R U2 R' U' R U' R'"),
        Algorithm("(U') R' U' F' U F U2 R U R2 F R F' U R"),
        Algorithm("(U2) F R U' R' U R U R' F' U L' U R U' L U R'"),
        Algorithm("(U') R' F' U' F U R2 U2 R2 U' R2 U' R2 U2 R"),
        Algorithm("(U) r' U' R U' R' U2 r R' U' R' F R F' U R"),
        Algorithm("(U) R U2 R' U' R U R2 F R F' R U2 R'"),
        Algorithm("(U') R U R' U R' U' R2 U' R2 U R' F R F' U R"),
        Algorithm("(U') R' U' R' F R F' U R U R' U' R U' R' U2 R"),
        Algorithm("(U) R U R' U R U' R' U R' F R F' R U2 R'"),
        Algorithm("F R U' R' U R U2 R' U' R U' R' U' R U R' F'"),
        Algorithm("(U') R' U' R' F R F' U R U2 R U2 R' U' R U' R'"),
        Algorithm("(U2) R U2 R' U' R U' R' U R' U2 R U R' F' U F R"),
        Algorithm("(U) R U2 R2 U' R2 U R2 U' R2 U' R2 F' U F R"),
        Algorithm("(U2) R U2 R' U' R U' R2 U' F' U F R"),
        Algorithm("(U') R' U' R U' R' U F' U R U R' U' R' F R U R"),
        Algorithm("r U2 R' U' R U' r' R U R' U' R' F R F'"),
        Algorithm("(U) R' F' U F R U R' U R U2 R' U F' U2 F U R"),
        Algorithm("(U') R' U' F U F' R F R U' R' U R U' R' F'"),
        Algorithm("r U R' U' r' F R2 U R' U' F'"),
        Algorithm("(U2) R U2 R' U' R U R' F R' F' R U2 R' F R F'"),
        Algorithm("R U R' U' R' U R U R U' R' U R' F' U2 F R"),
        Algorithm("(U2) R U2 R' U2 F R U' R' U R U R' F' R U2 R'"),
        Algorithm("(U') R' U' R F U R U' R' F' U' R' U R"),
        Algorithm("F' U' r' F2 r U' F R U' R'"),
        Algorithm("(U') R' U' R U R' U' R y R U2 R' F' U2 F"),
        Algorithm("(U2) R U R' U' R' F R F' U' R' U' R U' R' U2 R"),
        Algorithm("(U2) F R U' R' U R U R' F' U' R' U' R U' R' U2 R"),
        Algorithm("(U') r' U' R U' R' U r' D' r U r' D r2"),
        Algorithm("(U2) R U R' U2 F' U' F U2 R' F R F'"),
        Algorithm("(U2) F R U' R' U R U R' F' R U2 R' U' R U' R'"),
        Algorithm("r U2 R' U' R U' r' F R U' R' U R U R' F'"),
        Algorithm("(U') F' U2 R' F' R U' R U R' U2 F U R' F R"),
        Algorithm("(U2) F R U' R' U R U2 R' U' F' R' U' F' U F R"),
        Algorithm("(U2) r U' r' F' R U R' U' R' F r U r' F R F'"),
        Algorithm("(U') F' r U r' U2 r' F2 r U F R U R' U' F'"),
        Algorithm("(U2) R U R' F' U' r U2 R' U' R U' r' F R U' R'"),
        Algorithm("r R D R' U R D' r' U R' U' r U' r'"),
        Algorithm("(U') F U' R U R' F' U' F U' R U' R' U R U' R' F'"),
        Algorithm("F R U R' U' F' U F R U' R' U' R U2 R' U' F'"),
        Algorithm("(U') F R U' R' U' R U R' F' r' U' R U' R' U2 r"),
        Algorithm("(U') F U R U' R' F' U' F' r U r' U2 r' F2 r"),
        Algorithm("(U2) R U R' U2 F' U F R U' R' U R U' R'"),
        Algorithm("R U2 R' U2 R U' R' F' U' F R U R'"),
        Algorithm("(U') R' U' F U R U' R' F' R F U R U' R' F'"),
        Algorithm("(U') L' U R U' L U2 R' U' R' F R F'"),
        Algorithm("(U) R' F' U' F U R U' F' r U R' U' r' F R"),
        Algorithm("(U) R' U2 R' D' R U2 R' D R U' R' F R F' U R"),
        Algorithm("(U') R' U F' U F U R U' R' F' U2 F U' R"),
        Algorithm("F' U' r' F r2 U r' U' r' F r"),
        Algorithm("(U) R' U' R U2 R U2 R' U' F' U F R U' R2 U2 R"),
        Algorithm("(U2) R' U' R U' R' U' R U2 R2 U' F' U F R U R"),
        Algorithm("(U) F U' R U R' F' U' F U' R U2 R' U' R U R' F'"),
        Algorithm("(U) F R' F' R U2 R U' R' U R' U' F' U F R2 U' R'"),
        Algorithm("(U2) r U2 R' U' R U R' U' R2 U' r' F U R' U' F'"),
        Algorithm("F U R U' R2 F' R U2 R U' R' U R U2 R'"),
        Algorithm("R' F R U R' F' R F U' F'"),
        Algorithm("L' U2 R U R' U2 L U R' F R F'"),
        Algorithm("(U2) R' F R U R U2 R2 F' R2 U2 R' F U' F'"),
        Algorithm("(U2) F U R U' R' U R2 D R' U2 R D' R' U R' F'"),
        Algorithm("(U2) R' F2 R U2 r U' r' U' r' F r U' F U r U r'"),
        Algorithm("R' U' R y r' R2 U' R' U r U R'"),
        Algorithm("R2 D' r U2 r' D R U F' U F R"),
        Algorithm("r' U' M' U' R U r' U r"),
        Algorithm("(U2) R U' R' F' U2 F U R U' R' U F' U F"),
        Algorithm("(U2) R' U' R U' R' U2 R U' r U2 R' U' R U' r'"),
        Algorithm("(U2) r U r' U2 R U2 R' U2 R U R' U' r U' r'"),
        Algorithm("F R U' R' F' U' r' F r F R U R' F'"),
        Algorithm("F R U' R2 U2 R U R' U R U2 R U R' F'"),
        Algorithm("(U') R U2 R' U' R U' R' U r' U' R U' R' U2 r"),
        Algorithm("f R U R' U' f' R U R' F' U2 F R U' R'"),
        Algorithm("R' U2 R U R' U R U r U R' U' r' R U R U' R'"),
        Algorithm("(U') R' U' R U' R' U2 R F R U R' U' R U R' U' F'"),
        Algorithm("(U) R U R' U R U2 R' U r U R' U' r' R U R U' R'"),
        Algorithm("(U2) R U2 R' U' R U' R' F R U R' U' R U R' U' F'"),
        Algorithm("r U2 R' U' R U' r' U R' U' R U' R' U F' U F R"),
        Algorithm("(U') R' F' U' F U R U' R' U2 R U R' U R"),
        Algorithm("(U') R U2 R' U' R U R' U F' U' F U' R U' R'"),
        Algorithm("(U) r' U' R U' R' U R' F R F' R U' R' U2 r"),
        Algorithm("(U) r' U2 R U R' U r R' F' U' F U R"),
        Algorithm("(U2) F R U R' U' F' U R U R' U R U2 R'"),
        Algorithm("(U') R' F' U2 F U' R U R2 F R F' R U R' U R"),
        Algorithm("(U2) r U R' U R U2 r' U2 F R U R' U' F'"),
        Algorithm("(U2) r U R' U R U2 r' U' R' F' U' F U R"),
        Algorithm("R' U R U2 R' U' R U2 R' U' R U' R' F' U F R"),
        Algorithm("(U') R' F' U' F R2 U R2 U R2 U' R2 U R2 U2 R'"),
        Algorithm("(U2) F R U R' U' F' R' U2 R U R' U R"),
        Algorithm("R U R' F' R U R' U' R' U' F R2 U' R2 U2 R"),
        Algorithm("(U2) R U R' F' U' F U R U' R' U R U2 R'"),
        Algorithm("(U2) R U2 R2 F R F' R' F R F' R U' R' U' R' F R F'"),
        Algorithm("(U2) R U R' F' U' F U R U2 R' U' R' U2 R U R' U R"),
        Algorithm("(U') R U2 R' U' R U' R' U' R U2 R' U2 R' F R F'"),
        Algorithm("(U') R' U2 F' U F U' R U2 R' U R U R' U' R"),
        Algorithm("(U') R U2 R2 U' R F' R' U R U F R U' R'"),
        Algorithm("r U R' U' r' F R F' U R' U' R' F R F' U R"),
        Algorithm("(U2) F R U' R' U R U2 R' U' R U R' U' R U R' U' F'"),
        Algorithm("R' U' R U' r U R D' R U R' D R' U2 r'"),
        Algorithm("(U') R' r U R' U' r' D' r U' r' D R2 U R' U R"),
        Algorithm("(U2) R' U2 R U R' U R2 U R' F' U F R U' R'"),
        Algorithm("(U') F R U' R' U R U2 R' U F' U F R U' R' U F'"),
        Algorithm("(U) R U2 R' U2 y R U R' F R U' R' F2 U2 F"),
        Algorithm("(U2) R' U' R U R' U2 R U' R' U2 F' U2 F U' R"),
        Algorithm("(U2) R' U R U R U2 F R F' U' R' U R' U' R2 U' R'"),
        Algorithm("(U2) R U2 R' U' R U R' U' R U R' U2 R' F R F'"),
        Algorithm("(U') R' F' U' F U R2 U' L' U R' U' L"),
        Algorithm("(U2) R' F' U F R' D' r U' r' D R2"),
        Algorithm("(U2) F R U R' U' F' U R U' L' U R' U' L"),
        Algorithm("(U2) r U2 R' U' R U R' U2 r' F R2 U R' U' F'"),
        Algorithm("R' U2 R F R U R' F' R' F U' F' R U' R' U' R"),
        Algorithm("(U2) F R U' R' F' r U r' U' r' F r R U R' F'"),
        Algorithm("(U2) R' F' U F R' D' r U r' R U2 R' D R2"),
        Algorithm("(U2) R' U' R U' R' U2 R U' F R U' R' U R U2 R' U' F'"),
        Algorithm("(U') R' U2 R U R' F U R U' R' F' R"),
        Algorithm("(U') R' F2 r U2 R U' r' F U F R U R' U' F'"),
        Algorithm("(U') R' U' R F R' U R F R' F' R U' F'"),
        Algorithm("(U') R U R' U R U' R' U' F' U2 F U R U R'"),
        Algorithm("R U2 R' F' r' F r U F U' R U2 R'"),
        Algorithm("(U) R' U2 R U R' U2 R U2 R' U' F' U F U R"),
        Algorithm("F R U R' U' F' R2 D' r U2 r' D R U2 R"),
        Algorithm("(U') R' U' F U R U' R' F' U' F' U F R"),
        Algorithm("F R U' R' U' R U R' F' U' F R U' R' U' R U R' F'"),
        Algorithm("(U') R' U2 R U F R2 U' R2 U R U R U F'"),
        Algorithm("(U) R' U' R' F R F' U R U2 F R U' R' U' R U2 R' U' F'"),
        Algorithm("(U) F R U' R' U' R U R' F' U' r' U2 R U R' U r"),
        Algorithm("(U2) R' U2 R U R' U R U F R U' R' U' R U R' F'"),
        Algorithm("(U') R U R' U' R U R' U R' F R U2 y' R2 U' R2 U' R'"),
        Algorithm("(U) R' F' R U R' D R U2 R' D' R U R' U' F U R"),
        Algorithm("R' F R U R' U r U' r' U' R U' R' F' U' R"),
        Algorithm("(U') R U2 R2 F R F' R' U' R U' R' U2 F R F'"),
        Algorithm("F U R U' R D R' U' R D' R2 U' R U R' F'"),
        Algorithm("R' F' r' F' r U F R2 D R' U R D' R'"),
        Algorithm("F R F' U2 R' U R U R' U' R U2 x U R' U' x'"),
        Algorithm("(U') F' r U R' U' r' F R U R U R' U' R' F R F'"),
        Algorithm("r' U2 R' D' R U R' D r U' R U r' U r"),
        Algorithm("(U) F' U' F r U R' U' R U' r' U' r U r'"),
        Algorithm("(U) R' U' F' U F R F U R U' R' F'"),
        Algorithm("r U' r' U' R U2 R' U' R U' R' U' r U r'"),
        Algorithm("(U) R' U' R F U R U' R' U' R' U R U F'"),
        Algorithm("(U) R' U' F' U F R U F R U' R' U2 R U R' F'"),
        Algorithm("R U R' U R U2 R' U r' U2 R U R' U r"),
        Algorithm("(U) r' U' R U' R' U2 r U' R U R' U' M' U R U' r'"),
        Algorithm("(U2) r U r' R U R' U' r U' r'"),
        Algorithm("(U) R U R' U R U2 R' U' r' U r2 U' r2 U' r2 U r'"),
        Algorithm("(U2) R' U2 R U R' U R U F R U R' U' R U R' U' F'"),
        Algorithm("(U2) R U' R' U R r' U r U' r' U' r U R'"),
        Algorithm("(U2) r U' r' U2 R U' R' U' r U R' U2 M"),
        Algorithm("(U') R U2 R2 F R F' R U2 R' U F R U R' U' F'"),
        Algorithm("r' U' r U' R' U M U r U R' U' F' U F R"),
        Algorithm("F R U R' U' R U R' U' F' R' U' F' U F R"),
        Algorithm("F R U R' U' F' R U2 R' U' R U' R'"),
        Algorithm("R' U' F' U F R U2 F R U R' U' R U R' U' F'"),
        Algorithm("(U) R' F' U' F U R U2 R' U' R U' R' U2 R"),
        Algorithm("(U) r U2 R' U' R U' r' U F R U R' U' F'"),
        Algorithm("r' U' R U' R' U2 r U' R' F' U' F U R"),
        Algorithm("(U') F R U' R' F' r' F r U r U2 R' U' R U' r'"),
        Algorithm("r' U' R U' R' U2 r U2 F R U R' U' F'"),
        Algorithm("r U r' R U R' U F' U' F U' r U' r'"),
        Algorithm("F R U R' U' F' U' R' U' R U' R' U2 R"),
        Algorithm("(U) F R U R' F R' F' R U' R U' R' U2 R U R' F'"),
        Algorithm("(U2) R' F R F' R U' R' U R U R' U F' U' F"),
        Algorithm("R U R' U' R' F R F' U R' U2 R U R' U' R U R' U R"),
        Algorithm("(U2) R U2 R' U R U R' U2 R U' R2 F R F' R U R'"),
        Algorithm("(U') r' F R F' r U2 R' U' M' U R U' r'"),
        Algorithm("(U2) F' U' F R U2 R D r' U r D' R2"),
        Algorithm("R U' R' F' U' F R U R' U R U' R' U' R U R'"),
        Algorithm("R U R' F' U' F R U R' U' R U R' U' R U' R'"),
        Algorithm("(U) F R' F' R U2 R U' R' U R' F R F r U r' F"),
        Algorithm("(U) R' F' R U R U' R' U' F U R U R'"),
        Algorithm("(U) R' U' R F R' F' U F R U R U' R' F'"),
        Algorithm("F R U' R' U' R U R' F' U' F R U R' U' R U R' U' F'"),
        Algorithm("R U R' U2 R U' R' U' R U2 R2 F R F' R U R'"),
        Algorithm("R' F R U R' U' F' R U' R' U2 R"),
        Algorithm("F U R U2 R' U' R U R' F' U R' U2 R U R' U R"),
        Algorithm("(U2) R U2 R' U F' r U' r' F2 U R' F R F'"),
        Algorithm("(U') R' U2 R2 U R2 F' U F R2 U' R'"),
        Algorithm("(U) R' U' R' D' R U R' D R U' R' F R F' U R"),
        Algorithm("R' F R U R' U' F' U R U R U2 R' U' R U' R'"),
        Algorithm("(U') r' U' R U' R' U2 r U' R' F R U R' U' F' U R"),
        Algorithm("(U2) F U R U' R' U R U2 R' U R U R' U R U' R' F'"),
        Algorithm("F U R U2 R' U' R U R' F' U2 R U R' U R U2 R'"),
        Algorithm("(U') R D r' U r D' R2 F' U' F R"),
        Algorithm("(U2) R U R' U r' U' R' D R' U' R D' R U2 r"),
        Algorithm("R U2 R' U' R U' R' F R U' R' U' R U R' F'"),
        Algorithm("(U') R U2 R' U' R U R' U' F' U F R U' R'"),
        Algorithm("R U R' U R U' R' U R U2 R' F R' F' R U R U' R'"),
        Algorithm("(U) R U2 R' U2 R' F R F' r' U' F' U F r"),
        Algorithm("(U') R' U' R U R U2 R' U' R' U R U2 R' F R F'"),
        Algorithm("(U) R U2 R' U2 R' F R F' U F R U R' U' F'"),
        Algorithm("(U') r U R' U' r' F R F' U2 R' U' R' F R F' U R"),
        Algorithm("(U2) R2 D R' U R D' R2 U' R' F R F'"),
        Algorithm("F U R' U' F' U F R U R U' R' F'"),
        Algorithm("(U2) F R U R' U' F' R2 D R' U2 R D' R' U2 R'"),
        Algorithm("(U) R' F' U' F U' F' R U R' U' R' F R2 U R' U R"),
        Algorithm("(U') R U' R' F' r U' r' F' R' F' R U' R U2 R'"),
        Algorithm("(U2) R U2 R2 F R U R' U' F' U R U2 R U' R'"),
        Algorithm("R U2 R' U2 R' F R F' R U R' U' R' F R F'"),
        Algorithm("R U R' U R U R' U' F' U R U R' U' R' F R"),
        Algorithm("(U) R2 F2 R U' F R' F R F' R U R' F U' F U R"),
        Algorithm("R U2 R' U' R U R U y R U' R' F' R U R' U F'"),
        Algorithm("(U2) R U' R' F' U' F U R U R2 D' R U' R' D R"),
        Algorithm("(U2) R2 D R' U2 R D' R' U2 R' F R U R' U' F'"),
        Algorithm("(U) R' U' R' F R F' U' R' D' R U2 R' D R2"),
        Algorithm("(U') R' U' R U' R' U2 R2 U R' U R U' R' U' R' F R F'"),
        Algorithm("r U r' R U R' U' r U' r' F R' F' r U R U' r'"),
        Algorithm("(U2) r U2 R D R' U' R D' r' U R' U' r U' r'"),
        Algorithm("(U) R U R2 D' R U R' D F R F r U r' F"),
        Algorithm("r U' r' U r U R' U R U' r' F' U F"),
        Algorithm("(U') R2 F R F' U2 R U' R' F' U F U R U R' U2 R"),
        Algorithm("(U) F U' R U R' U2 F' U F U R U2 R' U F'"),
        Algorithm("(U2) R' U F' U2 F U R U R' U2 F' U F U' R"),
        Algorithm("R U2 R' U R U' R' F' U F U R U' R2 F R F'"),
        Algorithm("(U') R' F R F' R U2 R' U' F' U' F2 R U R' U' F'"),
        Algorithm("(U2) R U R' U R U2 R' F U R U' R' F' R' F' U' F U R"),
        Algorithm("(U) r U' r' F2 R U' R' U R U R' U' F' U2 r' F r"),
        Algorithm("F' r U' r' F2 U' R U R' U2 M' U R U' r'"),
        Algorithm("(U) r' U' R U' R' U2 r U2 r' U2 R U R' U r"),
        Algorithm("(U2) r U2 R' U' R U' r' U2 r U R' U R U2 r'"),
        Algorithm("R U R' U R' F R U R' U' F' U R U R' F R F'"),
        Algorithm("r' U' r U2 r' U R U2 R2 U' R U' R' U2 R U' r"),
        Algorithm("r' F U' R U' R' U2 r F U R U' R' U' F'"),
        Algorithm("(U) R U2 R2 F R F' R U2 R' U' F R U R' U' R U R' U' F'"),
        Algorithm("(U') F U R U' R' F' U' r U r' R U R' U' r U' r'"),
        Algorithm("(U) r U2 R2 F R F' R U' R' U2 R U2 r' U2 r U' r'"),
        Algorithm("R' U2 R' D' r U' r' D R F' U2 F U R"),
        Algorithm("R U' R' U R U' R' U' F' U2 r' F r2 U' r' F2"),
        Algorithm("(U) R' U' F' U2 F R' D' r U r' D R U2 R"),
        Algorithm("(U2) r U' r' F2 R U' R' U R U' R' U' F' U2 r' F r"),
        Algorithm("(U) r U2 r' F R' F' R2 U2 R' M' U' M"),
        Algorithm("R' F R F U' R U' R' F' R U R' U F2 R U2 R'"),
        Algorithm("(U') R' U R U' R' U R U' R2 F R F2 U' F U2 R"),
        Algorithm("R' U' F' U F R U2 r U r' R U R' U' r U' r'"),
        Algorithm("(U2) R' U' F U R U' R' F2 U' F U R"),
        Algorithm("F R U R' F' U' F R U2 R' U F' U' r U' r' F"),
        Algorithm("r' U' R' F2 R F' U r F U2 F'"),
        Algorithm("R2 F r U r' R U2 F' R U' r' F r"),
        Algorithm("(U2) F R U' R' F U R U' R' F' U R U R' F'"),
        Algorithm("(U) F' R U2 R' U' F' U F R U' R' U' L' U' L U F"),
        Algorithm("R' F R U' M' U2 r' U' F' U R"),
        Algorithm("R' F R F' U2 R' F R U y' R2 U R2 U2 R'"),
        Algorithm("(U2) R' U' F U R U' R' F' R U' F R U R' U' F'"),
        Algorithm("(U') F R U2 R2 U' F' U F R U2 F'"),
        Algorithm("(U2) R' U' F' U F R U2 F R U' R' U R U R' F'"),
        Algorithm("(U) r' U2 R U R' U r F' r U r' U2 r' F2 r"),
        Algorithm("(U) F R U R' U' F' U' F' U' F r U' r' U r U r'"),
        Algorithm("(U') R U2 R' U F' U' F2 R U R' U' F' U R U R'"),
        Algorithm("x' U' R U' R' U R U' R' U F2 R U' R' U2 x"),
        Algorithm("(U) R' U F' U R' F R U R' F' R U F U R"),
        Algorithm("(U2) R' U' R' F R F' R U' R' U2 F R U R' U' F' U R"),
        Algorithm("R U R' U R' F R F' U2 R' F R F'"),
        Algorithm("(U') R U R D r' U r R' U R D' R2 U R U R'"),
        Algorithm("(U2) r U' r' F U2 F U' R U' R' F'"),
        Algorithm("(U) F U R U' R2 U' R' U' R U R F' U F R F'"),
        Algorithm("(U) r' U' R' U r U r' F' U' F R2 U' R' U2 r"),
        Algorithm("R U2 R' U F2 r U r' F U R' F R F'"),
        Algorithm("(U2) R' U' F' U F R U2 R U R' U' R' F R F'"),
        Algorithm("(U) F U R U' R' U R U' R' F' U2 F R U' R' U' R U R' F'"),
        Algorithm("(U') R' U' F' U F R2 U R' U' R' F R F'"),
        Algorithm("(U2) R U2 R' U' F' U F R U' R' U' R U R' U' R' F R F'"),
        Algorithm("F R U R' U2 R U' R' F R U R' U' F' U2 F'"),
        Algorithm("(U) R U2 R' U2 R' F R F' U2 F R U R' U' R U R' U' F'"),
        Algorithm("(U2) M' U' M U2 r U' r' U' F' U F"),
        Algorithm("(U2) F R' F' R U R U' R' U' R U R' U' M' U R U' r'"),
        Algorithm("(U) R U2 R' U' F' U F R U' R' U2 R' F' U' F U R"),
        Algorithm("F R' F' R U R U' R' U2 R' U' R' F R F' U R"),
        Algorithm("f R U R' U' f' U' R U R' U' R' F R F'"),
        Algorithm("(U) R' F' U2 F2 U R U' R' F' U2 R"),
        Algorithm("R' U2 R U2 F R F' U2 y M' U M"),
        Algorithm("(U) R' U' R' F' U' F U R2 U2 R' U2 F' U F R"),
        Algorithm("(U') R' U2 R U R' U2 R2 D r' U r D' R2 U' R"),
        Algorithm("(U) r' U2 R U R' U r R U2 R' U2 R' F R F'"),
        Algorithm("(U') R' U' F' U F R F R U' R' U R U R' F'"),
        Algorithm("(U') F U' R U' R' F' U' F R U R' U R U R' F'"),
        Algorithm("(U) R' U R2 D r' U r D' R2 U R U R' U R"),
        Algorithm("(U') F R U' R' U R U2 R' U' F' U' F R U R' U' F'"),
        Algorithm("R U R' U' R U R' F' L' U' L U' F U' R U' R'"),
        Algorithm("(U) r' U r U' r' F' U' F R U' R' U' R U R' U r"),
        Algorithm("(U) R U2 R2 F R F' U F' U' F U2 R' F R F'"),
        Algorithm("(U') F R' F' R2 U R' F' U' F U' R' F R F' R U2 R'"),
        Algorithm("f R U R' U' f' U' F R U' R' U R U R' F'"),
        Algorithm("(U) R' U' F' U F R U R' U' R U' R' U F' U F R"),
        Algorithm("r U R' U R U2 r' U F R U R' U' R U R' U' F'"),
        Algorithm("(U') R' U2 R U R2 F R F' U R U R' U' F' U F R"),
        Algorithm("(U2) F U' R U R' U F' U2 F U R U R' U2 F'"),
        Algorithm("(U) r U2 R' U' R U' r' U2 F R U R' U' R U R' U' F'"),
        Algorithm("(U') r U R' U R U2 r2 U' r U' R' U R r' U r"),
        Algorithm("(U2) R' U2 R U R2 F R F' U R U F U R U' R' F'"),
        Algorithm("R U2 R' U2 R' F R F' U' R' U' F U R U' R' F' R"),
        Algorithm("(U') r U R' U R U2 r2 U' R U' R' U2 r"),
        Algorithm("(U) r' U' R U' R' U2 r2 U R' U R U2 r'"),
        Algorithm("(U2) r2 F2 R2 U2 r' U r U2 R2 F' r U' r"),
        Algorithm("R U R' U' R' F R2 U R' U2 R' F R F' R U R' F'"),
        Algorithm("f R U R' U' f' U' R U R' U' M' U R U' r'"),
        Algorithm("(U) r U R' U' r' R U R U' R' U' F R U R' U' F'"),
        Algorithm("r U2 r' U2 R' F R F' U' F' U' F U r U r'"),
        Algorithm("(U2) r' U' R' F R F' R' F R U r F U' F'"),
        Algorithm("r' U2 R U R' U r U' F U R U' R' F'"),
        Algorithm("(U) R U R' U R' F R F' U2 M' U R U' r'"),
        Algorithm("R' F' U' F U R U2 r U R' U R U2 r'"),
        Algorithm("r U2 R' U' R U' r' U2 R' U' F' U F R"),
        Algorithm("(U') F R U' R' F U R U' R' F' R U2 R' U' F'"),
        Algorithm("R U2 R' F U' F' r U' r' U R' F2 R U F"),
        Algorithm("(U2) r' U' R U M' U' R2 F R F' U R"),
        Algorithm("R U2 R2 F R F' U2 M' U R U' r'"),
        Algorithm("(U') R U2 R' U' F' U F R U' R' U2 R' U' R' F R F' U R"),
        Algorithm("(U') r U' r' U M' U R U' R' U2 M F' U F"),
        Algorithm("(U) r' U' R U' R' U2 F2 r U2 r U' r' F"),
        Algorithm("R' F' U' F U R U R U R' F' U F U R U2 R'"),
        Algorithm("(U) R' U' R' F R F' U R U F R' F' R U2 R U2 R'"),
        Algorithm("(U') F U R U2 R' U' R U R' F' r' U' R U' R' U2 r"),
        Algorithm("(U) F' r U' r' F2 U' R U R' U2 R' F R F'"),
        Algorithm("(U2) R U R' F' U2 F R' F' U' F U R U' R U' R'"),
        Algorithm("(U') r U r' U' r' F R2 U' R' U M' U R U R' F'"),
        Algorithm("(U2) r' U' R U' R' U2 r F R' F' R U R U' R'"),
        Algorithm("(U2) r U R' U R U2 r' U F R U' R' U' R U R' F'"),
        Algorithm("F R U' R' U R U2 R' U2 R' F R F' R U R' F'"),
        Algorithm("R U R' U' R' F R F' U2 F R U' R' U' R U R' F'"),
        Algorithm("F R U' R' U R U R' F' U R U R' F' U F R U' R'"),
        Algorithm("R' F R U R' F' R F U' F' U2 F U R U' R' F'"),
        Algorithm("(U) R U R2 F' U' F U R U2 R' F R F'"),
        Algorithm("(U) F R' F' R U2 R' U' F' U F R2 U' R'"),
        Algorithm("(U') R' F' U' F R U R' U' R U2 R' U' F' U' F U' R"),
        Algorithm("F R U' R2 U' F U R U' R' F' R U' R U R' F'"),
        Algorithm("(U2) R U' R' U' F' U2 F U2 R U2 R' F U R U' R' F'"),
        Algorithm("R2 F R F' U F U R U' R' F' U R U' R' F' U F R"),
        Algorithm("R' F R F' U' R' F R F' R U2 R' F' U' F"),
        Algorithm("F R U' R' U R U2 R' F' U' F' r U r'"),
        Algorithm("(U) R U R' U' F' U2 F U R U' R' F2 r U r' F"),
        Algorithm("R' U' F' U F R r U R' U' r' F R2 U R' U' F'"),
        Algorithm("(U) F R U R' U2 R U2 R' F' U' F U R U R' U F'"),
        Algorithm("(U2) R2 F R F' U2 R' F R F' R' F R F' R"),
        Algorithm("(U) F R U R' U2 R U F R U R' U' F' U2 R' U F'"),
        Algorithm("R U R' U R U R2 D' r U r' D R2 U R'"),
        Algorithm("(U') F U R U2 R' U R' F R F' U' F' r' F2 r"),
        Algorithm("(U') F R' F' R U R U' R' U F R U R' U' F'"),
        Algorithm("(U) F R U R' U y' R' U2 R' F R F'"),
        Algorithm("F' U2 F U' R U R' U F' U F2 R U' R' U' R U R' F'"),
        Algorithm("(U') R' F2 r U r' U F M U F' U' F r"),
        Algorithm("(U) F R' F' R U' F' U' F2 R' F' R2 U2 R'"),
        Algorithm("(U') F R' F' R U R U' R' U2 R' F' U' F U R"),
        Algorithm("(U) R' F R U R' F' R F U' F' U2 R' U' F' U F R"),
        Algorithm("(U) R' F' U' F U2 R U2 R2 U' F' U F R U R"),
        Algorithm("(U') F R' F' R U2 R U2 R' r' U' R U' R' U2 r"),
        Algorithm("(U') R' U R U R2 D' R U R' r U r' D R U R"),
        Algorithm("(U2) r' U' R U' R' U2 r F R U' R' U' R U R' F'"),
        Algorithm("(U) F U R U' R' F' U F U R U2 R' U' R U R' F'"),
        Algorithm("R U2 R' U' R' F' U' F U R U2 R' F R F'"),
        Algorithm("R U R2 U' R' F R2 U' R' U2 F R F' R U R' F'"),
        Algorithm("R' F' U' F U' R U' R' F' U F U' R"),
        Algorithm("R' F R F' U R U R2 F R F2 U2 F"),
        Algorithm("R U2 R' U' R U R' F' U2 F R U' R2 F R F'"),
        Algorithm("(U2) F R U' R' U' R U R' F' U' F R U R' U' F'"),
        Algorithm("(U) R' U' R U' R' U F' U F R F R U R' U' F'"),
        Algorithm("R' F R U2 y' R' U' R' U R U2 R' F R F'"),
        Algorithm("F R U R' U' F' R U2 R2 F R F' R U2 R'"),
        Algorithm("(U) R' F R U2 R' F' R U r U R' U R U2 r2 F r"),
        Algorithm("R' U' R' F R F' U R U' R U2 R2 F R F' R U2 R'"),
        Algorithm("F U R U' R' U R' F R F' R U2 R' F' r' F r"),
        Algorithm("(U') R' F' U' F U R2 U2 R2 F R F' R U2 R'"),
        Algorithm("(U2) F U2 R U' R' U' F' U2 F U' R U' R' U F'"),
        Algorithm("r' U2 R U R' U r2 U2 R' U' R U' r'"),
        Algorithm("(U2) r U2 R' U' R U' r2 U2 R U R' U r"),
        Algorithm("(U2) R' U' R F R' F' U F R F' R U R' U' R' F R F'"),
        Algorithm("(U2) r' U' r U' R' U r' F R F' R' F R F' U r"),
        Algorithm("(U') F R U' R' U' R U R2 F' U' F R F' R' U R"),
        Algorithm("(U2) R' U' R F R' F' U F R2 U' R' U R U R' F'"),
        Algorithm("(U) F U R U2 R' U2 F R U R' U' F' R U2 R' U' F'"),
        Algorithm("(U2) r' U' r U' R' U R2 r' U' R' U F' U F r"),
        Algorithm("(U') F U' R' F' U' F R' F R U R2 U' R' F r U r'"),
        Algorithm("(U) R' F R U' R' U' R' F2 R2 U' R' U2 r U2 r' F R"),
        Algorithm("(U2) R' F R U R U2 R' U r U2 r' U' F' R U2 R'"),
        Algorithm("(U') R U2 R' F U r U2 r' U' R U2 R' U' R' F' R"),
        Algorithm("(U) R2 F2 r U r' F R2 U' R D r' U' r D' R'"),
        Algorithm("(U') r U r' U' R2 D r' U2 r D' R2 U r U' r'"),
        Algorithm("r' U' R U' R' U2 r U2 R U2 R2 F R F' R U2 R'"),
        Algorithm("(U2) r U R' U R U2 r' U' R U2 R2 F R F' R U2 R'"),
        Algorithm("(U') R' U R U2 R2 U' F' U F R U F' U' F U R"),
        Algorithm("(U2) R U R' U' R' F R2 U R' U' F' R' F' U' F U R"),
        Algorithm("(U) F R' F' R U2 R U2 R' U2 r U2 R' U' R U' r'"),
        Algorithm("(U2) R' F R F' U2 F' U F2 R' F' R2 U' R'"),
        Algorithm("(U2) R U2 R' U2 R' F R F' U2 R' U' F' U F R"),
        Algorithm("(U) F R' F' R U2 R U' R' U F2 r U r' F"),
        Algorithm("r' U2 R U R' U r F R U' R' U R U2 R' U' F'"),
        Algorithm("(U2) r' D' r U r' D r U' r U r' U2 M' U M"),
        Algorithm("(U2) R U2 R' U2 R' F R F' R U R' F' U2 F R U' R'"),
        Algorithm("(U2) R U R' U' R' F R F' r' U2 R U R' U r"),
        Algorithm("(U2) F R U2 R' F R U R' U' R U R' U' F' U F'"),
        Algorithm("(U') F R' F' R U2 R U' R' U2 F' U' F U' R U' R'"),
        Algorithm("(U') r R2 U' R U' r' U2 r U' R U R' U' r' F R F'"),
        Algorithm("R U2 R' U' F' U2 R' F' U' F U R U' F R U' R'"),
        Algorithm("M' U R U R' U r' R2 U2 R2 F R F' r U r'"),
        Algorithm("R' D' r U r' D R U2 r U' r' U r U r'"),
        Algorithm("(U') r U' r' U' r U r' U2 R' D' r U' r' D R"),
        Algorithm("(U2) R D r' U' r D' R' U2 r' U r U' r' U' r"),
        Algorithm("(U') r' U r U r' U' r U2 R D r' U r D' R'"),
        Algorithm("(U') R' U' R F U R2 U' R' F' U2 R' U' R U F R F'"),
        Algorithm("F U R' U2 R2 U R2 U R U R' F R F' U' F'"),
        Algorithm("(U) F r U r' U2 r U R' U2 R U' r' F' U' r' F r"),
        Algorithm("r' R' F2 R U' R' F2 R2 U R' F r U' r' F2 r"),
        Algorithm("F R U' R' U' R U R' F' U' r U r' R U R' U' r U' r'"),
        Algorithm("(U') R U R' U' R' F R F' U' F' L' U' L U L' U' L U F"),
        Algorithm("(U) R' U' F' U F2 R U R' U' F' U R"),
        Algorithm("(U2) F R U' R' U' R U R' F' U' R' F R U R' U' F' U R"),
        Algorithm("(U') F R U' R' U' F R U R' U' F' R U R' F'"),
        Algorithm("F R U' R' U R U2 R' U' F' U R' F R U R' U' F' U R"),
        Algorithm("(U) R' U' F U r U2 r' R U R' F' R"),
        Algorithm("R' U' F' U r' F r U F U R U2 R' U' R"),
        Algorithm("(U') R U2 R' U' F' U' F U R U2 R' F U R U' R' F'"),
        Algorithm("F U R U' R' F' U R' F R U R' U' F' U R"),
        Algorithm("(U') F U2 R' F' U' F U R2 U2 R' F'"),
        Algorithm("(U) F R U' R' U' R U R' F' U2 R' F' U' F U R"),
        Algorithm("(U') R' U2 R U R' U2 R2 D r' U' r D' R2 U' R"),
        Algorithm("M U R U R' U' M' R' F R F'"),
        Algorithm("(U') F R U' R' U R U R' F' U2 F R U R' U' R U R' U' F'"),
        Algorithm("M' U R U R' U' R U' r' R U R2 F R F'"),
        Algorithm("R' U2 R F U R' U' F' U F U R2 U' R' F'"),
        Algorithm("M U r U2 r' R U' R' U' R' F R F' M'"),
        Algorithm("R2 F R F' R U2 R2 F R F' R U' R' U' R"),
        Algorithm("(U) F' U' F U r U r' U2 M' U M"),
        Algorithm("(U') r U' r' F U' r' F' U' R' F2 R U r"),
        Algorithm("(U') r' U' R' F R F' U r R U R' U' R' F R F'"),
        Algorithm("(U2) F R' F' R U R U' R' U' F R U R' U' F'"),
        Algorithm("R' U2 F R U R' U' F2 U2 F R"),
        Algorithm("(U') R U2 R' U2 R' F R F' U2 r U R' U R U2 r'"),
        Algorithm("R' U2 R U R' F' U F R U2 F R U R' U' F'"),
        Algorithm("f R U R' U' f' R' U' R' F R F' U R"),
        Algorithm("R U R' U' M' U R U' r' U2 r U R' U' r' R U R U' R'"),
        Algorithm("M U R U R' U' M2 U R U' r'"),
        Algorithm("M' U2 M U2 M' U M U2 M' U2 M"),
        Algorithm("(U') R' U R U R2 F R F' U y' R' U' R U R' U R f z'"),
        Algorithm("(U') F R U R' U' R U R' U' F' R' U' R U' R' U F' U F R"),
        Algorithm("(U) r' U2 R U' R' U r U2 r2 F R F' r U' R' U2 r"),
        Algorithm("R U R2 U R2 U2 R F R F' U2 F' U F U' R"),
        Algorithm("r D' F2 R2 U' R U2 R' U R2 F2 D r'"),
        Algorithm("(U2) R U' R2 D' r U r' D R2 U' R' U' R U R' U' R U' R'"),
        Algorithm("(U) R U2 R' U' F' U F R U' R' U R' F R U R' U' F' U R"),
        Algorithm("(U2) F R U2 R2 F2 R U2 R U2 R' F r2 F r U' r"),
        Algorithm("R' D' r U' r' D R2 U R' U' F' U2 F"),
        Algorithm("(U2) F' U2 F U R U' R2 D' r U r' D R"),
        Algorithm("(U') R' F' U2 F U' R U' R' U' R U R' U2 F' U F R"),
        Algorithm("R U R' U' R' F R F' R U2 R2 F R F' R U2 R'"),
        Algorithm("(U') F U R' U2 R2 U R2 U R U R' U' F' U F R F'"),
        Algorithm("R D' F2 R2 U' r U r' U R2 F2 D R'"),
        Algorithm("(U') F B' U R' U R' U2 R U2 R U2 R y L' U R"),
        Algorithm("R U' R2 F2 U' R F R' U F2 R2 U R'"),
        Algorithm("(U) F R' F R2 U R' U' F2 U' r U' r' F"),
        Algorithm("(U') R U R' U' R' U' F R2 U' R2 U2 R2 U2 R' U' F'"),
        Algorithm("(U') R' U' R U2 r' U R U R' U' M' U' R"),
        Algorithm("(U) r' U' R U M' U' R' U R"),
        Algorithm("(U) M' U' M U2 M' U' M"),
        Algorithm("R U R' U2 r U' R' U' R U M U R'"),
        Algorithm("R' U' R' F R F' U R U' F R U' R' U2 R U R' F'"),
        Algorithm("M' U M U2 M' U M"),
        Algorithm("(U2) r U R' U' r' R U R U' R'"),
        Algorithm("(U) R' U' F' U F R U' f R U R' U' f'"),
        Algorithm("(U') R U R' U R U2 R' U' r' U' R U' R' U2 r"),
        Algorithm("(U') M' U M U M' U M U M' U M"),
        Algorithm("(U2) r U R' U' r' U2 R U R U' R2 U2 R"),
        Algorithm("(U2) F' U F U' R U' R' U' R U R' U2 F' U2 F"),
        Algorithm("(U') R U2 R' U2 R' F R F' R U' L' U R' U' L"),
        Algorithm("(U) R' U' R U r' F r U2 R' F U R U R' F' R"),
        Algorithm("(U) F' U2 F U R U R' U R' F R F' R U R' U' R U R'"),
        Algorithm("(U) R U R' U R' F R F' R' U2 R2 U R2 U R2 U' R'"),
        Algorithm("(U') r2 D r' U r D' r2 y' r U R' U' r'"),
        Algorithm("(U) R' U2 R U R' U R U' R' U' R U' R' U R' F R F' U R"),
        Algorithm("(U2) F R U' R' U' R U R' F' r U R' U' r' F R F'"),
        Algorithm("R' F R U R' U' F' U R2 U R' U' R' F R F'"),
        Algorithm("(U) F R U' R' F R' F' R U2 R' U' F' U F R F'"),
        Algorithm("R2 D r' U r D' R2 U' F' U' F"),
        Algorithm("(U') R2 D' r U' r' D R2 U y R U R'"),
        Algorithm("(U2) R' U' R U F R U R' U' R' U R2 U' R' F'"),
        Algorithm("(U) F' R' F R2 U R2 F R y' R U R2"),
        Algorithm("R' U' R U' R' U2 R U F R' F' R U2 R U2 R'"),
        Algorithm("(U') R' U' R U' R U2 R2 U' R' U R U' R' U' x' U' R' U x"),
        Algorithm("(U') r U R' F' R U R' U' R' F R2 U' r'"),
        Algorithm("R U2 R' U R' U' F U R U' F' R U2 R'"),
        Algorithm("(U2) R U R' U2 F' r U' r' F2 U R' F R F'"),
        Algorithm("(U2) F U R' F R F' R' U2 R2 U R2 U R F'"),
        Algorithm("(U') R U' R' U2 R U F U R U' R' F' U2 R'"),
        Algorithm("F R U R' U' R U' R' F R' F' R U2 R U' R' F'"),
        Algorithm("(U2) R' D' r U' r' D R U' r' D' r U2 r' D r"),
        Algorithm("(U') R U R' U R U2 R' U R U2 R' U2 R' F R F'"),
        Algorithm("r' D' r U r' D r U2 R' D' r U r' D R"),
        Algorithm("(U) R U R' U R' U2 R2 U R2 U R U' R' F R F'"),
        Algorithm("(U2) F R F' U R U R' U2 F U R2 U' F' U R"),
        Algorithm("l U' R U2 r' F r U2 l' R'"),
        Algorithm("(U2) R' F R U y' R U R' U' R U R2 U2 R' U R' U R"),
        Algorithm("F' U2 F R U R' U R U R' F' r U' r' F2"),
        Algorithm("(U) R' U F' U F R U' R' U' R U2 R' U2 R"),
        Algorithm("(U) l R U R' F' R U R' U' R' F R2 U' R' U' l'"),
        Algorithm("(U2) R2 F R F' R U R' U R U2 R' U R U2 R' U2 R"),
        Algorithm("(U2) R' F R U' y' R' U2 R' U2 R U' R U2 R'"),
        Algorithm("(U2) R U2 R2 U' R2 U' R' U R' U' R U' R' F' U F U' R"),
        Algorithm("(U') F' r U r' U2 r' F2 r U' R' U2 R U R' U R"),
        Algorithm("R' U R' F' U2 F U' R U' R' U' R U R' U' R2"),
        Algorithm("(U2) R' D' r U' r' D R U2 r' D' r U' r' D r"),
        Algorithm("(U') R U2 R' U2 R' F R F' U' R' U2 R U R' U R"),
        Algorithm("(U2) R2 F R U F' R U R' U F U F' U R"),
        Algorithm("(U) F R U R' F R' F' R2 U2 R' U' R U R' F'"),
        Algorithm("R' U' R U' R2 F R F' R U2 R' U R U' R' U R"),
        Algorithm("(U2) R2 F2 r U r' F2 R F' R"),
        Algorithm("R' U R U2 R2 U' F' U F R U R"),
        Algorithm("r U r' U2 r' F r2 U' r' F U' F' r U r' F'"),
        Algorithm("R U' R' F R F' R U R2 U r' U' R U r"),
        Algorithm("(U') R U2 R' U2 R' F R F' R U R' U R U2 R'"),
        Algorithm("R' U' R U' R' U2 R U r' F2 r U2 r U' r' F"),
        Algorithm("(U2) R U' R' U2 R' U' F R F' R' U R2 U' R'"),
        Algorithm("(U2) F R U R2 U' R U R U' R' F' U' R' U R"),
        Algorithm("(U2) r U R' U' M U F' R U R' U' R' F R2 U' R'"),
        Algorithm("(U2) R' F R F' R' F R2 U R' U' R' F' R2 U R'"),
        Algorithm("(U2) r U R' U' r' F R2 U' R' U' R U R' F'"),
        Algorithm("(U') R' F R' F2 r U' r' F2 R2"),
        Algorithm("(U2) R' U' R U R' U' R U2 R' F R' F' R2 U R' U R"),
        Algorithm("(U2) R' U' F' U F R' D' R U2 R' D R U2 R"),
        Algorithm("(U2) x R2 U2 R U R' U2 L U' R U M"),
        Algorithm("(U2) F R' F' R U2 R U' R' U R' U' R2 U' R2 U2 R"),
        Algorithm("(U2) F U R U' R' U2 R' D' R U2 R' D R F'"),
        Algorithm("(U2) F R' F' R U2 R U2 R' U' R U2 R' U' R U' R'"),
        Algorithm("(U) R' U R U R2 F R F' U F' U' F U2 R"),
        Algorithm("(U) R U R' U y' R' U R U' R' U R U' y R U2 R'"),
        Algorithm("R' F' U' F U' R U R' U R U R' U' F' U F R"),
        Algorithm("R U R' U2 F' U' F R' F R F' R U2 R'"),
        Algorithm("(U') r U2 R' U' R U' r' R' U2 R U R' U R"),
        Algorithm("(U2) R' U' R U R' U R U' R' F2 r U r' F U R"),
        Algorithm("R U2 R' U' R U' y R U R' U' R U R' U' F'"),
        Algorithm("(U2) r' U' R U' R' U2 r U r' U2 R U R' U r"),
        Algorithm("(U2) r U R' U R U2 r' U' R U2 R' U' R U' R'"),
        Algorithm("(U') F R U' R' U2 R U2 R' U' R U R' U' R U R' U' F'"),
        Algorithm("(U2) R' U' R U' R' U2 R U r' U2 R U R' U r"),
        Algorithm("(U) r U R' U R U2 r' U2 F R U R' U' R U R' U' F'"),
        Algorithm("(U) R U R' U R U' R' U R U2 R2 F' U' F U R"),
        Algorithm("(U') R U' R' U y' R2 U2 R U R' U R2 U' y R U R'"),
        Algorithm("(U2) r U2 R' U' R U' r' U R U2 R2 F R F' R U2 R'"),
        Algorithm("(U) r2 D' r U r' D r2 U' r' U' r"),
        Algorithm("R U2 R2 F R F' R U2 R' U' R' U2 R U R' U R"),
        Algorithm("(U) R U2 R2 F R F' R U2 R' U r' U' R U' R' U2 r"),
        Algorithm("(U') R' U' R U' R' U R U' R' U F' U F R"),
        Algorithm("(U') R' U' r D' R2 U' R U' R' U R2 D r' U' R"),
        Algorithm("f R U R' U' f' R U R' U R U' R' U R U2 R'"),
        Algorithm("R U2 R2 F R F' R U' R' U R U2 R'"),
        Algorithm("(U) R U R' U R U' R' F' U2 F R U R' U' R U' R'"),
        Algorithm("(U2) R U2 R' U' R U' R' U R U2 R2 F R F' R U2 R'"),
        Algorithm("M U' F U R U2 R' U' R U2 R' U' F' M'"),
        Algorithm("(U) f U' R' U2 R' U2 R2 U R' f'"),
        Algorithm("(U') F U2 R U2 R2 F R2 U R' U' R U R' U' F2"),
        Algorithm("(U) R U2 R2 U' R2 U' R' U R' F U R U' R' F' R"),
        Algorithm("(U2) F R' F' R U2 R U2 R' U2 R U2 R' U' R U' R'"),
        Algorithm("(U') F R U' R' U R U2 R' U' F' R' U2 R U R' U R"),
        Algorithm("(U2) R U R' U' R U' R' F' U' F R U R'"),
        Algorithm("(U) R' U2 R2 U R' U R U' R' U' R' F R F' R' U R"),
        Algorithm("(U2) R' U' R U R' F U R U' R' F' U R U R' U' R"),
        Algorithm("R U R' U R U2 R' U R U R' U' R' F R F'"),
        Algorithm("(U') R' U2 R U' R' U R U R' F' U' F U2 R"),
        Algorithm("(U2) R' F' U' F U R U R' F R U R' U' F' U R"),
        Algorithm("(U2) R' F R F' U R' U R U F' U F R' U R"),
        Algorithm("(U) R U R' U' R' F R F' r' U' R U' R' U2 r"),
        Algorithm("(U') R' U' F U R U' R' F' R U R U R' U R U2 R'"),
        Algorithm("(U) R U' R' U' F U R U' R2 F' R2 U2 R'"),
        Algorithm("(U) F R U' R' U' R U R' F' U' r U2 R' U' R U' r'"),
        Algorithm("(U') F U R U R' U y' R' U R U R' U' R U R'"),
        Algorithm("(U2) x R' U' R D' R' U2 R' U' R2 D x'"),
        Algorithm("(U') R' F R F' U R U R' U F' U F"),
        Algorithm("(U) R U R' U' R' F R F' r' U' r U' R' U M U r"),
        Algorithm("(U) R' U' R U' R' U2 F R U R' U' F' U R"),
        Algorithm("(U) r' U r U' R' U' R U' R' U r' F R F' U' r"),
        Algorithm("(U2) R U R' U R U2 R2 F R U R' F' R F U' F'"),
        Algorithm("R' U' R' F R2 U' R' F' r' F r R U R' U R"),
        Algorithm("r' F r U2 R' F r U2 r' U' F' U R"),
        Algorithm("(U2) R' U2 R U F R' F' U R U R U' R'"),
        Algorithm("(U') R U R' U R U' R2 F' U' F U R2 U2 R'"),
        Algorithm("R' F' U2 R U R' U' R' F R U' F' U' F U' R"),
        Algorithm("(U2) R' U' R U R U' R' U' F' R' U R F R U R'"),
        Algorithm("R' F' U' F U R U2 R' F R U R' U' F' U R"),
        Algorithm("(U) R' U' F' U' F U R U2 R' U R U R' U R"),
        Algorithm("f R U R' U' R U R' U' f' R U R' U' R' F R F'"),
        Algorithm("(U2) F R F' r U R2 U' M U R U' R'"),
        Algorithm("(U) R' U' F' U' F U2 R U2 R' U2 R U' R' U' R"),
        Algorithm("(U2) F R U R' U' F' U2 F R U' R' U R U R' F'"),
        Algorithm("(U) R U R' U' R' F R F' U2 R U2 R' U2 R' F R F'"),
        Algorithm("(U2) R' U2 R2 U R' U' R' U2 F R F'"),
        Algorithm("(U2) R U R2 U' R' U' R' U R U F R F'"),
        Algorithm("(U2) R2 F R F' U2 R U' R' U2 R' U2 R U R' U R2"),
        Algorithm("(U) F R U R' U R' U' F U R U' R' F' R U' F'"),
        Algorithm("(U2) R' U2 R U' R' U' R U2 R' U' F' U' F U2 R"),
        Algorithm("(U2) R U R' U' R U2 R' F R U R' U' F' R U R'"),
        Algorithm("(U2) R' U R U' R2 U2 R U R' U R U F R' F' R2"),
        Algorithm("r' U r' F R F' U F R U R' U' R' F' r U' r"),
        Algorithm("(U) M U R U R' U' R' F R F' M'"),
        Algorithm("(U2) R' U2 R r U R' U' r' U2 F R F'"),
        Algorithm("R' U' F' U' F2 U R U' R' F' U2 R"),
        Algorithm("(U2) F R' F R2 U' R' U' R U R' F2"),
        Algorithm("(U) r U R' U R U2 r' U' r U2 R' U' R U' r'"),
        Algorithm("(U') R' U2 R U R' U y' R' U' R U R' U' R U B"),
        Algorithm("(U) R U R' U' R U' R' U' F' r U' r' F2 R U R'"),
        Algorithm("(U) R U R' U R U2 R' U R U R2 F R F2 U F"),
        Algorithm("(U') R' U' F' U F R U R U2 R2 F R F' R U2 R'"),
        Algorithm("(U) R' F' U F R U R' U R U' R2 F R F' R"),
        Algorithm("(U2) R' U' R U' R' U R' F R F' R' F R F' U R"),
        Algorithm("F R U R' U F' U' F U' R U' R' U2 R U R' F'"),
        Algorithm("r' U2 R U R' U r U' R' U' R U' R' U2 R"),
        Algorithm("(U) R U R' U R U2 R' U' r U2 R' U' R U' r'"),
        Algorithm("(U2) F R U R' U' R U R' U' F' R' U' R U' R' U2 R"),
        Algorithm("(U2) F U R U' R' F' R U2 R' U' R U R' U' R U R' U' R U' R'"),
        Algorithm("(U2) R' U' R U' R' U R U' R' U2 R2 y R U R' U' F'"),
        Algorithm("(U2) r2 D r' U' r D' r2 U r U r'"),
        Algorithm("(U) r' U2 R U R' U r R U2 R2 F R F' R U2 R'"),
        Algorithm("R U r' D R2 U R' U R U' R2 D' r U R'"),
        Algorithm("R U R' U R U' R' U R U' y R U' R' F'"),
        Algorithm("(U') R U2 R2 F R F' R U2 R' r U R' U R U2 r'"),
        Algorithm("(U) R U' R' U' R U' R' F' U' F U2 R U R'"),
        Algorithm("R U R' U R U' R' U R' F R F r U r' F"),
        Algorithm("(U') r U2 R2 F R F' R U' R' U R U2 r'"),
        Algorithm("(U) R' U2 R U R' U R2 U2 R2 F R F' R U2 R'"),
        Algorithm("(U') r U' r' U' r U r' R' D' r U r' D R"),
        Algorithm("(U2) F U R U2 R' U' R U2 R' U' F'"),
        Algorithm("(U2) R2 U R' U R U2 R' U2 R' U R U y R U R' U F'"),
        Algorithm("(U2) R' U2 R2 U R U' R' U R U R U' R' F R F'"),
        Algorithm("(U) F R' F' R U2 R U2 R' U r' U' R U' R' U2 r"),
        Algorithm("(U) R' U' R U R' U R U2 R' F' U F U R"),
        Algorithm("(U) R U R' F D R' U R' U' R D' F'"),
        Algorithm("(U2) F U R U' R' U R' U' R F' R' U R"),
        Algorithm("R U2 R' U R U' R' U' r' U' F' U F r R U' R'"),
        Algorithm("(U2) R U2 R2 U' R U' R' U2 F R2 U R' U' F'"),
        Algorithm("R U2 R' U R U' R' U' R y R U R' U2 F'"),
        Algorithm("(U') R' U' R U' R' U2 R U' F R U' R' U R U R' F'"),
        Algorithm("(U') R' U' R U R' U' r' F R F' U r U r' U' r"),
        Algorithm("(U') R' U' R U' R' U2 R U' R U R' U' R' F R F'"),
        Algorithm("(U) F R U R' U' R' F' R U2 R' F R F' R U2 R'"),
        Algorithm("(U) R U2 R' U' R U' R' U' R' F R U R' U' F' U R"),
        Algorithm("(U) R' U' F' U' F U' R U' R' U' R U R' U' R"),
        Algorithm("r' U2 R U R' U r U r' F R F' r U R'"),
        Algorithm("(U2) R' U R U2 R' U' F' U F R' F R F' U R"),
        Algorithm("(U') F R' F' R U R U' R' U r' U2 R U R' U r"),
        Algorithm("(U2) F R U R2 U' R F' U' R' U F' U F R"),
        Algorithm("R U R' F' R U2 R' U' R U' R' U F R U' R'"),
        Algorithm("(U) R' U' F' U' F U R U2 R' U R U R' U' R U R' U R"),
        Algorithm("R U2 R' U' F' U F R U R' U' R U' R'"),
        Algorithm("F R U' R' U' R' F' U' F U R2 U2 R' U' F'"),
        Algorithm("(U) R U2 R2 U' R U R U2 x' U' R' U x"),
        Algorithm("(U') F U R U' R' F' R' U' F U R U' R' F' R"),
        Algorithm("(U2) R U R2 F' R U R U' R' U' F R U' R'"),
        Algorithm("(U) R U2 R' U R U R' U2 R U y R U R' U2 F'"),
        Algorithm("(U') R' F' r U r' R2 U' r' F M'"),
        Algorithm("(U2) R2 D' R U' R' D R2 y R U' R' U' F' U2 F"),
        Algorithm("(U') F R U' R' U R U2 R' U' F' R U2 R' U' R U R' U' R U' R'"),
        Algorithm("(U) F R U R' F' U' R U R' U' R' F' r U2 R U' r'"),
        Algorithm("(U) F R U R' U' F' U2 R' U' F U R U' R' F' R"),
        Algorithm("R U2 R' F2 r U2 R' U' r' F R"),
        Algorithm("(U2) F2 U' R' F2 R F R U' R' U' F R U R'"),
        Algorithm("F U R U R2 U' F' U F R U2 F'"),
        Algorithm("(U') R U2 R' U2 R' F R F' U R' U2 R U R' U R"),
        Algorithm("(U) R U R' U2 F2 U' r U' r' F U F2"),
        Algorithm("(U) R U2 R F R F' U' R2 U' R' U' R' U R"),
        Algorithm("(U) R U R' U' R' U2 F U R U' F' R' U2 R"),
        Algorithm("(U2) F U R U2 R' U' r' F R F' r U2 R' F'"),
        Algorithm("(U2) R2 U2 R2 U' R2 U' R2 U2 R U' y R U R' U F'"),
        Algorithm("R' F R F' U' r U r' R U2 R' U r U r'"),
        Algorithm("(U') F R U' R' U R U R' U R U' R' U R U' R' F'"),
        Algorithm("(U') F U R U R' U' y' R' U2 R U' R' U' R U' R'"),
        Algorithm("(U2) F U R2 U' R2 F' R' U R U' F R F'"),
        Algorithm("(U') M' U M U r U r' F' U' F r U' r'"),
        Algorithm("(U2) R' F' U' F U R U R U R' U' R' F R F'"),
        Algorithm("(U) R U2 R' U' R U' R2 U' y' R' U R U' R' U l U x"),
        Algorithm("R U2 R' U' R U' R' U r U r' U R U' R' r U' r'"),
        Algorithm("(U2) F R U R' U' R U R' U' F' R U R' U R U2 R'"),
        Algorithm("(U') F R U' R' U2 R U2 R2 F R F' R U' R' F'"),
        Algorithm("(U2) r U R' U R U2 r' U2 R U2 R2 U' R2 U' R2 U2 R"),
        Algorithm("r U2 R' U' R U' r' U r U R' U R U2 r'"),
        Algorithm("(U') R U2 R' U R' F R F2 U F U' R U R'"),
        Algorithm("(U') F R U' R' U2 R U R' U' R' U R U F' U R' U R"),
        Algorithm("(U2) R U R' U R U2 R' F U R U' R' U R U' R' F'"),
        Algorithm("R U2 R' U2 R' U2 r U R U' r' U R' U R"),
        Algorithm("R U2 R' U' R U' R' U r U R' U R U2 r'"),
        Algorithm("(U) F U R U' R' U y' R' U R U' R' U R U' y R U' R' F'"),
        Algorithm("(U') R U2 R' U R' D' R U' R' D R U2 R' F R F'"),
        Algorithm("(U) R U2 R' U' R U R' U' F' U2 F U R U2 R'"),
        Algorithm("(U) R U2 R2 F R F' r U' R' U R U2 R' U' M"),
        Algorithm("(U') R U' R' U2 R' U2 R U R' U R U y F R U' R' F'"),
        Algorithm("(U2) F R' F' R U R U' R' U r' F R F' r U R'"),
        Algorithm("(U') R U R' U R U2 R2 U' F' U F U' R U' R' U2 R"),
        Algorithm("(U') R U2 R' U' R U R' U' R U' R' F U R U' R' F'"),
        Algorithm("(U') R U2 R' U' R' D' R U2 R' D R U R' F R F'"),
        Algorithm("(U') R' U2 R U R' U' R U R2 F R F' U R"),
        Algorithm("r' F R F' r U' R2 U' F' U F R2 U' R'"),
        Algorithm("F R' F' R U R' F' U' F U R U2 R' F R F'"),
        Algorithm("(U2) F R U' R' U R U2 R' U' R U2 R' U' F' U2 F U F'"),
        Algorithm("(U') F R2 U2 R' U2 R' U' F R F' R' U F'"),
        Algorithm("R U2 R' U' R U' R' U R' F2 r U2 R U' r' F"),
        Algorithm("M U r' U' R' F R U r U' R' F' r"),
        Algorithm("(U2) R' U' r' D' r U r' D r R"),
        Algorithm("(U2) F R U R' U' R U R' U' F' R U' L' U R' U' L"),
        Algorithm("(U) R U' R' U2 R U y R U' R' U' R U R' U' F'"),
        Algorithm("(U2) R U R2 F' U' F U R2 U' R' U R U2 R'"),
        Algorithm("(U') R' U' F U R U' R' F' R"),
        Algorithm("(U) R' F R U R' U' F2 U F R"),
        Algorithm("(U') R' U' F' U2 F U' R' D' r U' r' D R2"),
        Algorithm("(U') R' U2 R U F R' U R U' F' U F U R U' R' F'"),
        Algorithm("(U) r' U r U' r' U' R' F R F' r"),
        Algorithm("(U) R' U' R' F R F' U R2 U R' U' R' F R F'"),
        Algorithm("(U2) R' U2 R U F U R U' R' F' U' R' U R"),
        Algorithm("r' U' R' F R U r U' F' r U r'"),
        Algorithm("(U) r U' r' U' r U r' R U R' U' F' U2 F"),
        Algorithm("(U2) R U2 R' U2 R' F R2 U' R' U' R U R' U R U' R' F'"),
        Algorithm("(U') R2 F2 r U r' F' r U' R U2 r' F R"),
        Algorithm("(U2) F R' F' R U R U' R' U' R' U' R U' R' U2 R"),
        Algorithm("(U2) R' U' F' U R U R' U' R' F R U R"),
        Algorithm("(U2) R' U' R U R' U R U R U R' U' R' U' F R F'"),
        Algorithm("(U) R' U' R U' R U R2 U R U2 R' F R F'"),
        Algorithm("(U) R' U2 R U F U' R' U2 R U2 R U' R' F'"),
        Algorithm("(U2) F R' F' R U R U R' U' R U' R'"),
        Algorithm("(U2) F R U' R' U' R U R' F' U' R U2 R' U' R U' R'"),
        Algorithm("(U) R U R2 F R F' R U R' U2 R U R' F' U2 F"),
        Algorithm("R U' R' U' R' U' F' U F U2 R2 U R2 U R"),
        Algorithm("(U2) r U R' U' r' F R F' U r U2 R' U' R U' r'"),
        Algorithm("(U') R' U R U' R' U R U R' U F' U F U R"),
        Algorithm("(U') R' U2 R U R' U R F R' F' R U R U' R'"),
        Algorithm("(U') R' U2 R U R' U r U R U' r' U' F' U F"),
        Algorithm("(U2) F R U' R' U' R U R' F' U2 R' U' R U' R' U2 R"),
        Algorithm("(U') M' U R U' r' U R U R' U y' R' U R"),
        Algorithm("(U2) R' U R2 D r' U' r D' R2 U2 F' U F R"),
        Algorithm("(U') R U R' U R U2 R2 U r U R' U' F' U' F R2 r'"),
        Algorithm("(U) R' U' F' U2 F2 U R U' R' F' U' F' U' F R"),
        Algorithm("(U) R' U' F' U' F U R U2 R' U' R"),
        Algorithm("R U2 R' U' F' U F U R U2 R'"),
        Algorithm("R U2 R' U2 R' F R F' U F U R U' R' F'"),
        Algorithm("(U2) F R U' R' U' R' U' R U' R' U2 R2 U R' F'"),
        Algorithm("(U') R2 D R' U R D' R' U R' U2 R' F R F'"),
        Algorithm("(U) R' F' U2 R U R' U R U' R' U' R' F R U R"),
        Algorithm("R' U' R' F R2 U' R' U2 R U R' F' R"),
        Algorithm("r U R' U' r' F R F' r' U2 R U R' U r"),
        Algorithm("(U') R U R' U R U' R2 F' U' F U R U' R U' R'"),
        Algorithm("(U) R' U' R U' F R U R' U' F' U' R' U' R"),
        Algorithm("(U') R' F' U' F U R U' F R U' R' U' R U R' F'"),
        Algorithm("R' U2 R U R' U R U2 R U R' U' R' F R F'"),
        Algorithm("(U') R U' R' F2 r U r' F U' R U' R' U2 R U R'"),
        Algorithm("(U') r' U2 R U R' U r U' r' U' R U' R' U2 r"),
        Algorithm("(U) R U2 R' U F' r U' r' F2 U' R U2 R'"),
        Algorithm("R U R' U R U2 R' U' r U r' R U R' U' r U' r'"),
        Algorithm("(U') r U R' U R U2 r' U2 r' U r2 U' r2 U' r2 U r'"),
        Algorithm("(U') R' F R U R U2 R2 F r U' R U' r2 F r"),
        Algorithm("(U2) R' U2 R U R' U R U F U R U' R' U R U' R' F'"),
        Algorithm("R U R' U R' F R F2 U F U2 R U' R'"),
        Algorithm("(U) R U2 R2 F2 r U r' F R U R U' R'"),
        Algorithm("(U) r' U' R U' R' U2 r U2 R U2 R2 U' R2 U' R2 U2 R"),
        Algorithm("(U') R' U2 R U R' U R U' r' U' R U' R' U2 r"),
        Algorithm("(U') F R U' R' U' R U R' F' R U R' U' R' F R2 U R' U' F'"),
        Algorithm("(U2) R' U2 R U R' U' R U R' U R U' R' U' F' U F R"),
        Algorithm("(U2) F U R U' R' U' F' U2 F R' U2 R U R' U R F'"),
        Algorithm("r' U' R' F R F' R U' R' U R U' R' U2 r"),
        Algorithm("(U2) F R' F' R U2 R' D' R U R' D R U' R U2 R'"),
        Algorithm("R' U' R U' R' U2 R2 U R' U R' F R F' R U2 R'"),
        Algorithm("(U2) R U' r' U' R U R2 D' r U r' D r"),
        Algorithm("(U) R U R' U R U' R' U R U2 R' U2 R' F' U' F U R"),
        Algorithm("R' U2 R U R' U' R U R' U R U R' U' F' U F R"),
        Algorithm("(U) R U R' U R U' R' U R U2 R' U F R U R' U' F'"),
        Algorithm("(U2) F' U' F2 R U R' U' F2 U' y R U' L U R'"),
        Algorithm("(U) R2 D r' U' r D' R2 U r U R' U' M"),
        Algorithm("(U2) R U2 R' U' R U R' U' R U' R' F R U R' U' F'"),
        Algorithm("(U) R U2 R2 U' F' U F R2 U' R'"),
        Algorithm("(U') F R U R' F' U F U R' F R F' R U R' F'"),
        Algorithm("(U2) F U R' F R F' U' R U' R' U' R U R' F'"),
        Algorithm("(U2) r U' r' F r U' r' F2 R U' R2 F R F' U F'"),
        Algorithm("(U2) F R U' R' U' R U R' F' U R U R' U R U2 R'"),
        Algorithm("(U2) R' F R U R' U' F' U R U F R U R' U' F'"),
        Algorithm("(U2) F R U R' U' R U R' U' F' r U R' U' r' F R F'"),
        Algorithm("(U) R U R2 F' U' F U R U' F' U2 F R U' R'"),
        Algorithm("(U2) F U R U' F' r U R' U' r'"),
        Algorithm("(U2) F R' U' R2 U R U R' U' R U R U F'"),
        Algorithm("(U) F R U R' U' F' U F R U' R' U' R U R' F'"),
        Algorithm("(U2) F R U' R' U' R U R' F' R' U2 R U R' U R"),
        Algorithm("(U') R' U2 R U R' U R U R U2 R' U2 R' F R F'"),
        Algorithm("(U2) F U' R U R2 D' R U' R' D R U2 F'"),
        Algorithm("(U2) F' U R U R' U' R' U' F2 U R2 U' R' F'"),
        Algorithm("(U) F R' F' R U R U' R' U2 F R U' R' U2 R U R' F'"),
        Algorithm("(U') R' U2 R U2 R' U R U2 R' F' U2 F R"),
        Algorithm("(U') R' U' F U F' R F R U' R' F'"),
        Algorithm("(U') R' U2 R U R' U' F' U' R' F' U' F U R F U2 R"),
        Algorithm("(U2) x' R U' R' D R U R U' R' U R' D' x"),
        Algorithm("R U2 R' U' F' U F R U' R'"),
        Algorithm("(U2) F R U R' U' R U R' U' R F' r U R' U' r'"),
        Algorithm("(U') R U R U R U R' F' U F R U R2 U' R' U' R"),
        Algorithm("(U') R' F R F' U' r U' r' U r U r'"),
        Algorithm("r' U r' F' r2 U' r' F' r F R U' R' F'"),
        Algorithm("r U2 R' U' R U' r' U F R U' R' U' R U R' F'"),
        Algorithm("(U2) R' U' R2 U' R2 U2 F' U' F U R U R U R'"),
        Algorithm("R U2 R' U' R U' R' U F R U' R' U' R U R' F'"),
        Algorithm("R U2 R' F R' F' U' F' U F R2 U' R'"),
        Algorithm("(U') r U2 R' U' R U' r' U2 r U R' U' r' F R F'"),
        Algorithm("R U' R' U R U' R' U' R U' y R U' R' U' F'"),
        Algorithm("M U' R' U r U' R' U' R U' y R U' R'"),
        Algorithm("(U') R U2 R' U' R U' R' U2 R U R' U' R' F R F'"),
        Algorithm("(U) R' U2 R2 U2 R2 U2 R' F R F' R U R U' R2 U R"),
        Algorithm("(U2) R2 D R' U2 R D' R' U2 R' F U R U' R' F'"),
        Algorithm("(U') F U R U2 R2 U' F' U F R U R U R' F'"),
        Algorithm("(U) R U' r D r' U r D' r' U R'"),
        Algorithm("(U') F U R U R' U' F' U2 F U F'"),
        Algorithm("R U2 R2 F R F r U2 r' U' r' F r"),
        Algorithm("(U') F R U R' U' R U' R' U R U2 R' F' U F U2 F'"),
        Algorithm("F' U' r U' r' F U r U R' U' r' F R"),
        Algorithm("(U) R U R' U' R' U2 R U R' U R U2 R' F R F'"),
        Algorithm("R2 D' R U' R' D R U' R U' R' F' U F U' R"),
        Algorithm("R' U' R U' R' U R U F R U R' U' F' R' U R"),
        Algorithm("(U2) l U R' D R U' R U' R' U R' D' x"),
        Algorithm("(U) F R U R' U' F' R U R' F' U F R U' R'"),
        Algorithm("(U2) R U R' U2 R' F' U' F U R2 U R'"),
        Algorithm("(U') R U2 R' U' R U' R' U2 F R U' R' U R U R' F'"),
        Algorithm("R U R' F' U2 F R U R' F R' F' R2 U2 R'"),
        Algorithm("(U) R U2 R' U' R U' R' r' U2 R U R' U r"),
        Algorithm("(U) r' U' R U' R' U R' F R F' R' F R F' U r"),
        Algorithm("R U R' U R U2 R' U2 r' U' R U' R' U2 r"),
        Algorithm("(U') r U R' U y' R' U R U' R' U R U' y R U2 r'"),
        Algorithm("(U') R' U2 R U R' U R r U2 R' U' R U' r'"),
        Algorithm("(U) R' U' R U' R' U2 R U2 r' U r2 U' r2 U' r2 U r'"),
        Algorithm("R' U' R U' R' U2 R U2 r U R' U R U2 r'"),
        Algorithm("R U R' F r2 F r U' r2 U2 r' U' F"),
        Algorithm("(U) R U' R' U' R' U y R U' R' F' U F2 R' F R"),
        Algorithm("(U') R U2 R' U F' U' F R' F R F' R U2 R'"),
        Algorithm("(U') R U2 R' U' R U R' U' R U' y R U R' U' R U R' U' F'"),
        Algorithm("(U) R U R' U R U2 R' U' R U2 R2 F R F' R U2 R'"),
        Algorithm("(U2) r' U r U r2 D' r U' r' D r2"),
        Algorithm("R U' R' U' F' U2 F R' F R F'"),
        Algorithm("(U') R2 U' F R F' U R U R' U' R' U R2"),
        Algorithm("(U) r U R' U' r' F R F' U F U R U2 R' U' R U R' F'"),
        Algorithm("(U') r2 F2 R U' R' F R F' U R' F2 r2"),
        Algorithm("(U) r' U' R U' R' U R U' R' U F' U F r"),
        Algorithm("(U2) F R U R' U y' R' U' R U R' U' R U' R'"),
        Algorithm("(U') R U R' U R U' R' U R U2 R' U2 R' U' F' U F R"),
        Algorithm("(U') R U' R2 F R F r U2 r' R U R' U' r U' r' F"),
        Algorithm("(U2) F R U R' U' F' R' U' R U' R' U R U' R' U2 R"),
        Algorithm("(U2) F R U R' U' F' U' R' U2 R U R' U' R U R' U R"),
        Algorithm("F U R U2 R' U' R U R' F' U2 R U2 R' U' R U' R'"),
        Algorithm("(U2) r' F R U F R U2 R' U2 R U R' F' M'"),
        Algorithm("R' U F' U F R U R' F' U2 F R"),
        Algorithm("R' U' F' U F R U2 F R U' R' U' R U R' F'"),
        Algorithm("F R U' R' U' R U R' F' U' F U R U' R' F'"),
        Algorithm("F U R' F R F' U F' U' R' F R U' R' F' R"),
        Algorithm("R U2 R' U F' r' U2 R U R' F U r F"),
        Algorithm("(U2) F R U R' U' R U' R' U R U2 R' U' R U R' U' F'"),
        Algorithm("(U') M U R' U' F U R U' R' F' R U' M'"),
        Algorithm("F R U' R' U R U R' F'"),
        Algorithm("(U) R2 U' R2 F R' F' U' R' U R' U R2"),
        Algorithm("r' F2 r U r U' r' F2 R U2 R' U' R U R' F'"),
        Algorithm("(U) R' U' R' F R F' U y' R' U R U R' U2 R U f z'"),
        Algorithm("(U) R' U2 R' D' R U R' D R2 U' R' U F' U F R"),
        Algorithm("(U) F U' R U' R' F' U' F R U2 R' F'"),
        Algorithm("(U') r' U' R' F R F' R' F R F' U F R F' r U R'"),
        Algorithm("(U2) F r U' r' U R U R' U r U' r' U R U' R' F'"),
        Algorithm("r U R' U R U' R' U' r' F R2 U R' U' F'"),
        Algorithm("(U) R' F' U' F U R U r U R' U' r' F R F'"),
        Algorithm("(U') M U R U2 R' U' F' U F R U' R' U' M'"),
        Algorithm("R' U' R U' R2 F R F' R U2 R' U2 x U R' U' R2 x'"),
        Algorithm("F' U' F r U r' R U R' U r U R' U M"),
        Algorithm("R U R' U' R' F R F'"),
        Algorithm("R U R' F' U' F U' R' U2 R U R U' R2 U2 R"),
        Algorithm("R' U R U' R' U' R U2 R' F R' F' R2 U' R' U' R"),
        Algorithm("R U' R' U R U R' U2 R U R2 F R F' R U R'"),
        Algorithm("(U2) r U' r' U' r U r' U2 r' D' r U' r' D r"),
        Algorithm("(U2) R U R2 F' U' F U F R F' R U2 R'"),
        Algorithm("R U2 R2 F R2 U R' U' F' U R U R'"),
        Algorithm("(U') F U R U2 R' U R U2 R2 F R F' U' F'"),
        Algorithm("r U r' R U R' U' R r U' r' F R' F'"),
        Algorithm("(U2) R U R' U y' R' U R U r' U' R U M'"),
        Algorithm("(U2) R' U' R U' y R U' R' U' r U R' U' M"),
        Algorithm("(U') R' U' R U' R' U R U' R' U' R U2 R' U' F' U F U R"),
        Algorithm("r' U2 R U R2 F R U F' r F R U' R' F'"),
        Algorithm("R U2 R' U' R2 U' R' F U R2 U' F' U' R' U2 R"),
        Algorithm("(U) R U2 R' U2 R' F R F' R' F' U' F U R"),
        Algorithm("R U R' F' U' R U R' U' R' F R2 U' R'"),
        Algorithm("(U) L F' R' F R2 U R' U F U R U R' F L'"),
        Algorithm("(U') f R U R' U' f' F R U' R' U' R U R' F'"),
        Algorithm("F R U' R' U2 R U R2 F' R U R U' R'"),
        Algorithm("R' U' F' U F R U R U R' F' U F R U' R'"),
        Algorithm("R U R' F' r' F' r2 U r' U' r' F r"),
        Algorithm("(U) R U R' U2 R U' R' F R U R' U' F r U r' F"),
        Algorithm("(U') r U2 R2 U' R2 U' r' U R' F U R U' R' F' R"),
        Algorithm("R U R' U R U2 R' F' r U r' U2 r' F2 r"),
        Algorithm("(U) R U2 R' U2 R' F R F' U' F R U R' U' F'"),
        Algorithm("R U R' U2 F' U F R U' R' U2 R U2 R'"),
        Algorithm("(U2) F R U R' U' R U R2 F R F' R U' R' F'"),
        Algorithm("r' F R F' r U R' U' R U R' U' R' F R F'"),
        Algorithm("(U2) r U R' U R U2 r' F U R U' R' U R U' R' F'"),
        Algorithm("R' F R U R' U' F' R U' R2 D' r U2 r' D R2"),
        Algorithm("R U' R' U' R U2 R' U2 F' U F U' x U R' U' R x'"),
        Algorithm("F R U R' U' R U R' F2 r U r2 F r"),
        Algorithm("(U2) F U R U' R' U R' F R F r U r' U' r' F2 r"),
        Algorithm("R U2 R2 U' R2 U' R2 U2 R U' r U2 R' U' R U' r'"),
        Algorithm("(U') r U r' U R U' R' U2 R U' R' U2 r U' r'"),
        Algorithm("(U') r' U' r U' R' U R U2 R' U R U2 r' U r"),
        Algorithm("F R U R' U' R U R' F R' F' R2 U' R' F'"),
        Algorithm("(U2) F R U R' U' R U R' U' F' r U R' U R U2 r'"),
        Algorithm("(U) R' U' R U' R' U F' U F U2 R U R' U' R U R' U R"),
        Algorithm("(U) F' R U2 R2 F R U r U' r' F' U' R U2 R' F"),
        Algorithm("(U') R' U' R' F R F' R U' R' U R U' R' U2 R"),
        Algorithm("(U2) F U R' U' F' U R U2 R U' R' U R U2 R'"),
        Algorithm("(U2) R U R' U' R' F R F' U2 r' F R F' r U R'"),
        Algorithm("(U2) F' U' F R' D' r U' r' D R U2 R U R'"),
        Algorithm("r U' r' U' F' U' F U r U r' U r U r'"),
        Algorithm("(U) r' D' r U' r' D R2 U' R' U r U R'"),
        Algorithm("(U') R' U' R' F R F' U R U' R U2 R' U' R U R' U' R U' R'"),
        Algorithm("R' F R U r U2 r' U r U2 r' U' F' R U2 R'"),
        Algorithm("R U R' U R U' R' U R U2 R2 U' F' U F R"),
        Algorithm("(U') R U2 R' U' R U R' U' R U' R' U R' U' F' U F R"),
        Algorithm("(U2) F R' F' R U R U' R' U R U2 R' U2 R' F R F'"),
        Algorithm("(U') R' U2 R2 U y R U' R2 F' R2 U' R'"),
        Algorithm("R U R' U' R' F R F' R' U2 R U R' U R"),
        Algorithm("F R U R' U' F' U F R' F' r U R U' r'"),
        Algorithm("R' U2 R2 U R2 U R U2 R' F R F'"),
        Algorithm("R U R' U' R' F R F' U R U R' U R U2 R'"),
        Algorithm("(U2) F R U R' U' F' U2 F R U' R' U' R U2 R' U' F'"),
        Algorithm("(U2) F R F' r U r' U R' U' r U' r'"),
        Algorithm("r' U2 R U R' U r U2 R U R' U' R' F R F'"),
        Algorithm("(U2) r U2 r' U' R U' R' F U F' U' R' F' R"),
        Algorithm("(U) R U R' U r U2 r' U F' U' F U r U r'"),
        Algorithm("(U2) R' F' U' F U R2 U' R2 D' r U' r' D R2 U R'"),
        Algorithm("(U') R U' R' F R' F' R2 U' R' U2 R U' R' U' R U R'"),
        Algorithm("(U') R U2 R2 F R F' R U2 R' U R U R' U' R' F R F'"),
        Algorithm("R U2 R' U' R U R' U F' U F R U' R2 F R F'"),
        Algorithm("(U) r U R' U R U2 r' U F R U' R' U R U R' F'"),
        Algorithm("F R U' R' U R U R' F' U' R U R' U R U2 R'"),
        Algorithm("(U) r' U' R U' R' U2 r U' R U R' U' R' F R F'"),
        Algorithm("(U2) R U R' U' R' F R F' R' U' R U' R' U2 R"),
        Algorithm("(U') F' U' F U' R U' R' U' x U R' U' R x'"),
        Algorithm("R U R' F' U' R U R' U R U2 R' F R U' R'"),
        Algorithm("(U) R' F' U' F U R U' R' U2 R' D' R U2 R' D R2"),
        Algorithm("(U2) F R U R' U' F' R U2 R D R' U2 R D' R2"),
        Algorithm("(U') F R' F' R U R U R2 F R F' R U2 R'"),
        Algorithm("(U) F R U' R' U' R U2 R2 F R F' U' F'"),
        Algorithm("R U R' U R U2 R' U' F R U' R' U' R U R' F'"),
        Algorithm("R' U2 R F R U R' U' F' U' R' U' R"),
        Algorithm("(U2) R' U2 R F R U R2 U' R F' U' R' U' R"),
        Algorithm("(U) F R U R' U' F' R U2 R2 F R F' U2 R' F R F'"),
        Algorithm("R U R2 U' R' F R U R U' F'"),
        Algorithm("(U2) R' U' R' D' R U R' D R' U R' U' M' U R U' r'"),
        Algorithm("R' U2 R U R' F' U' F U R U2 R' U' R"),
        Algorithm("(U2) F R U R' U' F' U' R' U2 R' D' R U2 R' D R2"),
        Algorithm("(U2) R2 F R F' U2 F R U' R' U R U2 R' U' R' F' R2"),
        Algorithm("(U') R' U' R F R2 U' R' U R U R F'"),
        Algorithm("(U2) r' R U R' U2 R U R' U2 r U R' F' U' F R"),
        Algorithm("(U2) F R U R' U' R U R' U' R' F' R U2 R U2 R'"),
        Algorithm("(U2) F R' F' R U R U' R' U' r' U' R U' R' U2 r"),
        Algorithm("(U2) R U2 R' U R' F' U' F U R2 U R'"),
        Algorithm("(U2) R' U' R U y r U R' U' M"),
        Algorithm("(U) F U R U' R' F' R U2 R' U' F' U F R U' R'"),
        Algorithm("(U) R U R' U R' F R F' R' U' F' U F R U' R' F R F'"),
        Algorithm("(U) R' U' F U R U' R' F' R F R U R' U' R U R' U' F'"),
        Algorithm("(U) R' U' R2 U R U R' U' R U R U2 R' F R F'"),
        Algorithm("(U2) R U2 R' F R U R' U' F' U R U R'"),
        Algorithm("(U2) F R U R' U' R' F' r U R U' r'"),
        Algorithm("(U2) R' F R U R' F' R y' R U R' U' R U R' U' R U' R'"),
        Algorithm("R' F' U' F U' F R U R' U' F2 U2 F R"),
        Algorithm("(U2) R' F R U r' F r F2 U' F' r U' r'"),
        Algorithm("(U2) R2 F2 r U' r' R F2 R U2 R' U2 F R"),
        Algorithm("(U2) r U R' U R U2 r' R U R' U R U' R' U R U2 R'"),
        Algorithm("F R U R U R' U' R' U2 F R F' U R' U F'"),
        Algorithm("(U) R' U2 R U R' U' r U R' U' r' R2 U R' U R"),
        Algorithm("(U') r U' r' U' R U' R' F2 U F R' F R"),
        Algorithm("(U') r U2 r' U F' r U' r' F2 r U' r' U' r U2 r'"),
        Algorithm("(U) R' U2 r U R' U' R U R' U' r' R2 U R' U R"),
        Algorithm("(U) r' U' R U' R' U2 r U' R U2 R' U' R U R' U' R U' R'"),
        Algorithm("(U') R U2 R' U' R U R' U' R U' R2 F2 r U r' F R"),
        Algorithm("(U) R' U' F' U' F r' F R F' r U' R' U' R"),
        Algorithm("(U2) F' U' r' F2 r F R U R' U' R U R' U' R U' R'"),
        Algorithm("(U2) R' U' R U' r' U2 R U' F R U R' U' F' M'"),
        Algorithm("(U') R U2 R' U' R U' R' U2 F R U R' U' F'"),
        Algorithm("(U) R U R' U R U2 r2 U' F' U F r U' M'"),
        Algorithm("R U R' U R U' R' U R U' R' U R' F R F' R U2 R'"),
        Algorithm("(U) R U R' U F' U F r U' R' U' R U r' R U R'"),
        Algorithm("R U R' F' U2 F R U' R' U R' U' R U' R' U2 R"),
        Algorithm("R U2 R2 F R F' R U2 R'"),
        Algorithm("(U') F R U' R' F' r' F r U R U R' U R U2 R'"),
        Algorithm("(U2) R' U' F' U F R U2 R U2 R' U' R U' R'"),
        Algorithm("f R U R' U' f' U' R' U2 R U R' U R"),
        Algorithm("R' U2 R U R' U R U2 F R U R' U' F'"),
        Algorithm("(U') R U2 R' U' R U' R' U' R' F' U' F U R"),
        Algorithm("(U') R U R' U R U' R' U' R U' R' F' U' F R U R'"),
        Algorithm("(U') R' U' F2 U' R U R' U' R' F' R F U2 F2 R"),
        Algorithm("(U) R U2 R' U' R U' R' U' R U R' U' R' F R F'"),
        Algorithm("(U) r' U r' F R F' r U2 R' U' R U R' U r"),
        Algorithm("(U2) R2 F2 R U' F R' F R F' R U R' F2 R"),
        Algorithm("(U2) R' U2 R U R' U' R U F R' U R2 U' R' F'"),
        Algorithm("(U) r' U' R' F R F' U F R F' r U R'"),
        Algorithm("(U) R U2 R2 U2 y R' F' R U2 r U r'"),
        Algorithm("(U') R' U' R' F R F' U R U' R U R' U' R' F R F'"),
        Algorithm("(U2) R' U' F' U F r U' r' F R F' r U r'"),
        Algorithm("R U R' U' R U' R' F R U R' U' F' U2 R U' R'"),
        Algorithm("(U2) R2 F R F' R U2 R' U R U2 R' U' R"),
        Algorithm("R' F R U R' U' F' U R F R U R' U' F'"),
        Algorithm("(U') R' U' R' F R F' U R U' F R U' R' U R U R' F'"),
        Algorithm("r' U' r U' R' U R' U' F' U F R2 U r' U r"),
        Algorithm("(U) R U2 R' U' R U' R' U' F R U' R' U R U R' F'"),
        Algorithm("R U2 R2 U2 R2 U R F R U R U' F'"),
        Algorithm("R' F R U R' U' F' U R U' r' U' F' U F r"),
        Algorithm("(U) R' F R U R' F' R U F U' F R' F' R U' F'"),
        Algorithm("(U2) R' U' R U' R' U' R U2 R' U' F' U F U R"),
        Algorithm("(U) M U R' F R U R' U' F' U R U' M'"),
        Algorithm("(U') R' U' R U' R' U R U' R' U R F R' F' U F R F'"),
        Algorithm("R' U R U R' U2 R U2 R' U2 F' U F U R"),
        Algorithm("(U2) F U2 R' F' U' F U R2 U' R' U' F'"),
        Algorithm("F U R U' R' U R U' R' F' U R' F R U R' U' F' U R"),
        Algorithm("(U2) R' U' r U R' U' R2 D r' U' r D' r' R' U R"),
        Algorithm("(U2) R' U2 R U R' U R U F R U' R' U R U R' F'"),
        Algorithm("(U2) F R U R' U' F' R U R2 U' R' F R U R U' F'"),
        Algorithm("R U2 R' U' y' r' U r U' r' U' r"),
        Algorithm("L' U R U' L U R' U' R U2 R2 F R F' R U2 R'"),
        Algorithm("R U R2 F R F' R U' R' U' R U' R' U F' U2 F"),
        Algorithm("(U2) L F U' R U R' U' y' R' U R U R' F'"),
        Algorithm("(U2) R' U2 R2 U2 y r U r' U2 R' F' R"),
        Algorithm("(U') F R' U R U2 R' U2 R U F' R2 F R F' U2 R"),
        Algorithm("f R U R' U' f' R U' L' U R' U' L"),
        Algorithm("(U2) F R' F' R2 U' R' U2 R U' R' U2 R U R'"),
        Algorithm("(U') F U2 R' D' R U R' D R2 U' R' U F'"),
        Algorithm("(U') M' U M U' r U r' F' U F r U' r'"),
        Algorithm("(U) R' U' R U' F' r U R' U' r2 F r U F U R"),
        Algorithm("(U) R U' r' U R U R' U' R' D' r U' r' D r"),
        Algorithm("r U' r' U' r U r' U' R U' R' U F' U2 F"),
        Algorithm("(U2) R' U2 R U R' U R U R U R' U' R' F R F'"),
        Algorithm("(U2) R U' R2 F R F' U y' x' R U' R' U R U' R' U x"),
        Algorithm("M U R U R' F' U' F U R U2 R' U' M'"),
        Algorithm("(U) R U R' U R U R' U2 R U y R U' R' U' F'"),
        Algorithm("(U') R' F R U R' U' F' U R U2 F R U R' U' R U R' U' F'"),
        Algorithm("R U R' U R U' R' U R U' R' y R' F R U' R' F' R"),
        Algorithm("(U2) R' U2 F R U R' U' F2 U F U R"),
        Algorithm("(U') R U R' F' R U R' U' R' F R U' R' F R F'"),
        Algorithm("(U') F' r U' r' F2 U' R U R' U' R U' R'"),
        Algorithm("(U') F R U R' U' F' R' F R F' R U2 R' U' F' U' F"),
        Algorithm("r' U2 R U R' U r U2 R' U' R U' R' U2 R"),
        Algorithm("(U) R U R' U R U2 R' U r' U' r U' R' U M U r"),
        Algorithm("(U') r U' R' U2 r U' R' U2 r U' r' U r U M' R'"),
        Algorithm("(U') r U2 R' U' R U' r' R U2 R' U' R U R' U' R U' R'"),
        Algorithm("(U') R U R' U r' R2 U' R' U r U' R' U R U2 R'"),
        Algorithm("(U) r U R' U R U2 r' U r' U' r U' R' U M U r"),
        Algorithm("(U2) F U' R2 U R' U R U2 R2 U' R U' R' U' F'"),
        Algorithm("(U) R U R' U R U2 R' U r' U' R U' R' U2 r"),
        Algorithm("(U') R' U2 F R U R' U' F' R U2 R' F R' F' R2"),
        Algorithm("R U2 R' U' R U' R' U' R U R' F' U2 F R U' R'"),
        Algorithm("(U') F R U' R' U2 R U R' F' R U2 R' U' R U' R'"),
        Algorithm("(U) R U R' U2 F' U' F U' R U' R'"),
        Algorithm("(U2) F U R' F R F r U r' U' r' F2 r"),
        Algorithm("(U') F U R U' R' F' U r' U2 R U R' U r"),
        Algorithm("(U) R U R' U2 R' U' F R F' R' U R U2 R U' R'"),
        Algorithm("R U2 R' U' R U' R' U R' U' F' U F R"),
        Algorithm("(U') R' F R U' R' U R U2 R' U' F' R U R' U R"),
        Algorithm("(U') R' U' R U' R' U2 R U' F R U R' U' F'"),
        Algorithm("(U) F R U R' U' F' U' r' U2 R U R' U r"),
        Algorithm("f R U R' U' f' R' U' R U' R' U2 R"),
        Algorithm("r U2 R' U' R U' r2 U' R' F R F' U r"),
        Algorithm("r U' r' U R U2 R2 F R F' r U' r' F' U' F"),
        Algorithm("(U) R U' R' F' U F R U R' U F' U F R U' R'"),
        Algorithm("R' F' U F U' F' U' r U' r' F2 R"),
        Algorithm("(U) R U R' U R' U' F' U F R U' R' F R F'"),
        Algorithm("(U) F R U R' U' R U R' F2 r U r' U r U' r' F"),
        Algorithm("(U) R U R' U' F' U2 F U R U R'"),
        Algorithm("F R U' R' U R U R' U R' U' F' U F R F'"),
        Algorithm("(U') R U R' F' R U R' F' U' F U' R' F R2 U' R'"),
        Algorithm("(U) R' U' R U' R' U2 R2 U R' U' R' F R F'"),
        Algorithm("(U2) F R' F' R U R U R' U' R U R' U' R U' R'"),
        Algorithm("(U2) F R U R' U' R U R' U' R' F' r U R U' r'"),
        Algorithm("(U) F' U' F R U2 R' U' F' U F r U' r' U r U r'"),
        Algorithm("(U) R U R' U R U2 R' U' F' r U r' U2 r' F2 r"),
        Algorithm("(U2) R U R2 F' U' F U R2 U2 R'"),
        Algorithm("R U R' U' R' U' F R F' U' R' U2 R"),
        Algorithm("(U2) R' U2 R F U' R' U R U F' R' F' U F R"),
        Algorithm("(U') F U F R U R' U' F' U R U' R' U' F'"),
        Algorithm("(U') M' F R U' R' U' R U2 R' U' F' M"),
        Algorithm("(U') R2 U R' U R U2 R' U2 R' U' R U' R2 F R F'"),
        Algorithm("(U') F U R U' R' U R U2 R' U' R U R' U R U' R' F'"),
        Algorithm("(U') R' F' U' F2 U R U' R' F' R"),
        Algorithm("R' U' R' F R F' U R U' R' U' F U R U' R' F' R"),
        Algorithm("(U') l' U' L U l F' L' U' L' U L F"),
        Algorithm("(U) R' U' R U' R' U R U x' R U' R' U x"),
        Algorithm("R' F' U' F U R U2 F R U' R' U R U R' F'"),
        Algorithm("(U') R' U' R' D' R F U' R U R' U F' R' D R2"),
        Algorithm("(U2) R' U' F' U F R U2 F U R U2 R' U R U R' F'"),
        Algorithm("R U2 R' U' F' R U2 R' U' R U' R' U' F U R U2 R'"),
        Algorithm("(U) R U' L' U R' U' L U r' U' R U' R' U2 r"),
        Algorithm("(U2) F R2 D R' U R' U' R U R2 D' R U' F'"),
        Algorithm("(U') R' U2 R U R' U R U R' U' F U R U' R' F' R"),
        Algorithm("(U) r U R' U R U2 r' U' R U2 R' U2 R' F R F'"),
        Algorithm("(U2) R' U' F' U F U' R F R' U R U' F'"),
        Algorithm("(U2) F R U' R' U2 R U R' F' U2 F R U' R' U R U R' F'"),
        Algorithm("r' U2 R' D' r U2 r' D R2 U' M'"),
        Algorithm("(U') r' U' r R' U' R U r2 D' r U r' D r2"),
        Algorithm("(U) R' U F U2 F' U' R F U' R U R' U' F'"),
        Algorithm("(U) M U' r U r' F' U F r U' r' U M'"),
        Algorithm("R U R' U' R' F R F' R' U' R' F R F' U R"),
        Algorithm("(U) R' F' U2 F R U2 R' U' R U2 R' U2 R"),
        Algorithm("(U2) F R U' R' F' r' F r R U R' U' R' F R F'"),
        Algorithm("R' F' U' F U R U2 R U R' U' R' F R F'"),
        Algorithm("(U') R U' L' U R' U' L F R U R' U' R U R' U' F'"),
        Algorithm("(U) R U' R' U' R U R D R' U2 R D' R2 U' R' F R F'"),
        Algorithm("R U' R' U' F U R U' R' F' R U2 R'"),
        Algorithm("(U') R' U2 R U R' D' U r U' r' D R F' U F"),
        Algorithm("(U2) r U R' U' r' F R F' U2 r' U2 R U R' U r"),
        Algorithm("(U') R U R' U' R' F R F' R U2 R' U2 R' F R F'"),
        Algorithm("(U') r U' r' U' R U R' U r U' r' F2 r U r' F"),
        Algorithm("(U2) R U' R' U' F' U2 F R' F R F' R' U' F' U F R"),
        Algorithm("(U2) r U R' U R U2 r' U2 R U2 R' U' R U' R'"),
        Algorithm("(U2) r U2 R' U' R U' r' U r' U2 R U R' U r"),
        Algorithm("(U) R' U2 R U R' U R U R U R2 F R F2 U F"),
        Algorithm("(U2) R' F R F' U2 R U' R' U' R U2 R' U' F' U' F"),
        Algorithm("(U) r' U2 R U R' U r U' r U2 R' U' R U' r'"),
        Algorithm("(U) r' U' R U' R' U2 r U2 R' U2 R U R' U R"),
        Algorithm("(U2) R U R' U R U' R' U R U2 R' U r' U2 R U R' U r"),
        Algorithm("(U) R' U2 R U R' U R U' r U2 R' U' R U' r'"),
        Algorithm("(U2) R U R' U R U2 R' U2 r U r' R U R' U' r U' r'"),
        Algorithm("R U R' U R U' R' U R U' R' F' r' F2 r U F"),
        Algorithm("(U) f R U R' U' f' r' U' R U' R' U2 r"),
        Algorithm("(U) R U2 R2 U' F D' F D F U F R"),
        Algorithm("(U) R' U' F' U F R U r U R' U R U2 r'"),
        Algorithm("(U2) l' U R U R' F' R U R' U' R' F R2 U' R' U2 l"),
        Algorithm("(U2) R' U2 R U R2 F R F' U R"),
        Algorithm("(U') R U R' U R U2 R2 U' F' U F R"),
        Algorithm("(U) R U' R' r U' R' U R U r' F' U' F U' R U' R'"),
        Algorithm("R' U' R U' R' U2 R U F U R U' R' F'"),
        Algorithm("r' U' R U' R' U2 r U F U R U' R' F'"),
        Algorithm("(U) F R U R' U' F' r' U' R U' R' U2 r"),
        Algorithm("(U) R U2 R' U' R U' R2 U' R' F R F' U R"),
        Algorithm("R' U' R' F R F' U R U2 r U R' U R U2 r'"),
        Algorithm("R U R' U R' U' R U' R' U2 F R F'"),
        Algorithm("(U) F R U' R' U R U R' F' U' R U R' U' R' F R F'"),
        Algorithm("(U) F R' F' R U2 R U2 R' U2 R' U' F' U F R"),
        Algorithm("(U') R U R' U R U R' F' U F R U R' U R U R' U' R U' R'"),
        Algorithm("(U') r U2 R' U' R U' r' U' r U R' U' r' F R F'"),
        Algorithm("(U') F' U F R' F R F' R U R' U' F' U' F"),
        Algorithm("(U2) R' U' F' U F R U2 r U R' U' r' F R F'"),
        Algorithm("(U') r U R' U' r' F R F' U' F R' F' R U2 R U2 R'"),
        Algorithm("(U) R' F' U F U R' U' R U' R' U2 R F' U' F R"),
        Algorithm("R' F' U' F U R2 U R' U' R' F R F'"),
        Algorithm("(U) R U R' U R' F R F r U2 r' U' r' F r"),
        Algorithm("(U') R U R' U R U R' U' F' U2 F U R U' R'"),
        Algorithm("(U2) R' U' F' U F R F U R U2 R' U R U R' F'"),
        Algorithm("(U2) R' F R U2 y' R' U' R' U R2 U2 R'"),
        Algorithm("(U2) R' F R U y' R U R' U' R' U' R2 U R"),
        Algorithm("(U2) R' U R' U' F R F' R' U R2 U R' U2 R"),
        Algorithm("(U) R U2 R2 U' F' U F R2 U R' U' R U' R'"),
        Algorithm("(U2) R' U2 R F U' R' U' F R F' R U2 R' U' F'"),
        Algorithm("(U2) F U R' U' R' F' R U R2 U' R'"),
        Algorithm("(U2) F R U' R' U R U R' F' U R U2 R2 F R F' U' R U' R'"),
        Algorithm("F U R U2 R' U R U R' F' U2 R' U' F' U F R"),
        Algorithm("(U2) F R U' R' U' R U R' F'"),
        Algorithm("(U') R U2 R' U2 y l' U' L U M"),
        Algorithm("R' F U' R' F R F' U R U R' F' R"),
        Algorithm("(U2) R U R' U' R' F R2 U' R' U R U R' F'"),
        Algorithm("(U') R' U' F' U F U' F U R U' R' F' R"),
        Algorithm("(U') R U2 R' U2 R' F R F' U R U R' U R U2 R'"),
        Algorithm("(U) R U' R' F R' F' R F' U' F U R U R'"),
        Algorithm("(U') R U2 R' U2 R' F R F' R' U2 R U R' U R"),
        Algorithm("(U2) R' U' R' F R F' U R U R' U' F U R U' R' F' R"),
        Algorithm("r' U2 R2 D R' U R D' R2 U r"),
        Algorithm("R U2 R2 U' R2 U' R2 U2 R U' F R U' R' U' R U R' F'"),
        Algorithm("R' F R F' U' F R' F' R2 U R' U2 R' F R F'"),
        Algorithm("R U R' U' R' U' F R F' R' U' R U R' U R"),
        Algorithm("F R U R' U' F' U' F R U' R' U R U R' F'"),
        Algorithm("R' U' R U' R' U' R U y R U2 R' U' F' U F"),
        Algorithm("(U2) F R' F' U2 R U R U' R2 U2 R"),
        Algorithm("(U) F R U R' U' F' U2 R U2 R' U2 R' F R F'"),
        Algorithm("r' U F R U R' F' U' R' F' r U' R"),
        Algorithm("(U') F R U R' U' r U r' U' R U' R' U' r U r' F'"),
        Algorithm("(U2) M' U R U' r' U' F' U F"),
        Algorithm("F R U R' U2 R U' R' F' U' F R U2 R' F'"),
        Algorithm("(U2) r' D R U R U R' U R U R' U R' D' r"),
        Algorithm("(U2) R2 D R' U2 R D' R' U2 R2 U' F' U F R"),
        Algorithm("(U) R U R' U' R' F R F' U2 R' U2 R U R' F' U F R"),
        Algorithm("(U) R U R' U' R' F R F' U R' U' F' U F R"),
        Algorithm("(U2) F R' F' R U R U' R'"),
        Algorithm("F R U R' F' U' F' r U r'"),
        Algorithm("R' U2 r U R' U' r' R2 U R' U' R U R' U R"),
        Algorithm("(U') R U R' F' U2 F U R U' R' U R' F R F' R U2 R'"),
        Algorithm("(U) R U' R' U2 R' U' F R F' R' U R U' R' F R F'"),
        Algorithm("(U2) R' U2 F' U2 R U2 R' U' R U' R' F R U R' U R"),
        Algorithm("(U) R U R2 F R F' y' R' U R U R U R' U R U2 R'"),
        Algorithm("(U) R U R2 F R F' y' R' U' R U R' U R"),
        Algorithm("(U2) r' U' R U' R' U2 r U' r U R' U R U2 r'"),
        Algorithm("(U') F' r U' r' F2 R U' R' U R U2 R'"),
        Algorithm("R' U' R U R' U' R U' R2 F R F' r' F R F' r"),
        Algorithm("(U') R2 D r' U' r D' R D' r U r' D R"),
        Algorithm("(U2) R' U' R U' R' U2 R U' r U R' U R U2 r'"),
        Algorithm("(U) R2 F R F' R U2 R' F U R U' R' F' U2 R"),
        Algorithm("r' U' R' F R F' U r U' r U2 R' U' R U' r'"),
        Algorithm("(U2) R' U' F' U F U2 R U R' U R"),
        Algorithm("R U R' F' U2 F R U' R2 U2 R U R' U R"),
        Algorithm("R U R' F' U2 F R U' R' U R U R' U R U2 R'"),
        Algorithm("(U2) R' U2 R U R' U' R U R' U' R U' y R U R' U F' U F"),
        Algorithm("(U) R' U' F' U F R U2 r U2 R' U' R U' r'"),
        Algorithm("(U) R' U' R U' R' U2 R U R' U' R' F R F' U R"),
        Algorithm("(U') R' U2 R U R' U R F U R U' R' F'"),
        Algorithm("R U R' U R U2 R' U2 R' F' U' F U R"),
        Algorithm("(U') r' U2 R U R' U r F U R U' R' F'"),
        Algorithm("(U') R' U2 R U R' F' U F R2 U R' U R U2 R'"),
        Algorithm("(U2) R' U' F' U F R U R U R' U R U2 R'"),
        Algorithm("(U) R' U' R U F R U R' U' F' U' R' U2 R"),
        Algorithm("F' U2 R' F R U R' F' R U F R U2 R'"),
        Algorithm("(U2) R2 F2 r U r' F R2 U' R' U' F' U' F R"),
        Algorithm("(U2) F U R' F R U R' U' F' U R U' R U' R' F'"),
        Algorithm("(U') R U2 R' U' F' U' F R2 D R' U' R D' R2"),
        Algorithm("(U2) F U R U' R' U R U2 R' U' F' U' r' F2 r"),
        Algorithm("(U2) R U R' U' R' F R F' U2 F R U R' U' F'"),
        Algorithm("(U2) r U R' U R U' R' U' r' F R F'"),
        Algorithm("(U2) F R U' R' U' R U2 R' U' R U R' U' R U R' U' F'"),
        Algorithm("(U2) r U R' U' r' F R U R U' R' F'"),
        Algorithm("(U2) R U R U F R F' U2 R' U' F R' F'"),
        Algorithm("(U2) R U R' U R U' R' U' R' F R F'"),
        Algorithm("F R U' R' U R U2 R' U' F' U F U R U' R' F'"),
        Algorithm("(U2) R' U' R U F R2 U R2 U' R U R U' F'"),
        Algorithm("(U') R U' R2 F R F' U R U R' U' R U R'"),
        Algorithm("(U2) R' U2 r' D' r U2 r' D R r"),
        Algorithm("(U') R U R' U' R' F R F' R' U' F U R U' R' F' R"),
        Algorithm("(U') r U r' U' r' F R2 U' R' U r U R' F'"),
        Algorithm("(U') R U' R' F R U R' U' R U R' U' F' R' F R F'"),
        Algorithm("(U2) R U R' U R U2 R' F R U' R' U R U R' F'"),
        Algorithm("(U) R U2 R2 U' F' U F R U R U2 R'"),
        Algorithm("(U) F R U R' U' F' R U2 R2 U' F' U F R2 U' R'"),
        Algorithm("(U2) R' F R U R' U' F' R U' R' U F' U F R"),
        Algorithm("F U R' U' R U' R' U R U F' x' R U' R' U x"),
        Algorithm("(U2) R' U2 R U2 R' U R U2 R2 F R F' R U' R' U' R"),
        Algorithm("F R U R' U' F' U R U R' U' R' F R F'"),
        Algorithm("(U2) R U' R' U' F' U2 F U R U' R2 U2 R U R' U R"),
        Algorithm("(U) r U r' U R' F R F' U' M' U' r' F R F'"),
        Algorithm("R U2 R' U' R U' R' U' R U2 R' U' F' U F R U' R'"),
        Algorithm("(U) F R U R' U F' U' F U' R U' R' U' R U R' F'"),
        Algorithm("r' F R F' r U R' U r U R' U R U2 r'"),
        Algorithm("f R U R' U' f' U r U R' U' r' F R F'"),
        Algorithm("(U2) r' U' R U' R' U2 r U' R' F2 r U2 R U' r' F"),
        Algorithm("(U') L' U2 R U' R' U2 L U R U' R' U' R' F R F'"),
        Algorithm("(U) R U R' F' r' F' r F R U R' U' R' F R F'"),
        Algorithm("r U r' R U R' U' r U' r' U' R U R' U' R' F R F'"),
        Algorithm("(U) R' U R U R' U2 R U2 R' U2 F' U2 F R"),
        Algorithm("(U) F U R U2 R' U R U R' F' R' F' U' F U R"),
        Algorithm("(U') F R U' R' U R U2 R' F' U F U2 F'"),
        Algorithm("F R U R' U' F' U F R U' R' U R U R' F'"),
        Algorithm("(U) R' F R U2 r U2 r' U2 F' U' R U R'"),
        Algorithm("(U) F U R U2 R' U R U R' F' U' F R U R' U' F'"),
        Algorithm("(U2) R U R' U R' F R2 U R' U' F' U R U R'"),
        Algorithm("(U') R' U R U2 R' U' F' U F R U' R' U2 R"),
        Algorithm("(U') R' U' R F U R2 U' F' R U R' U' R'"),
        Algorithm("(U') F R' F' r U F' R U R' U' R' F R2 U' r'"),
        Algorithm("(U2) R2 U' R U' R U F R F' R2 U R2"),
        Algorithm("(U) F R U' R' U' R U R' F' U2 F U R U' R' F'"),
        Algorithm("R U2 R' U' R U R' U' R U' R' U' r U R' U R U2 r'"),
        Algorithm("(U2) F R' F' R U2 R U2 R' R' F R U R' U' F' U R"),
        Algorithm("(U) R U2 R' U' R U R' F2 r U r' F"),
        Algorithm("(U) R U2 R' U' R U R' U' l R U' R' U2 F' U' R' x"),
        Algorithm("(U') r U r' F U F2 r' F' r U' R' F' R"),
        Algorithm("(U) R U R' U R U' R2 F R F' y' R' U R"),
        Algorithm("(U) R U R' U R U2 R' U2 r U2 R' U' R U' r'"),
        Algorithm("(U2) R' U' R U' R' U R U' R' U y' R' U2 R U2 R' U' R f z'"),
        Algorithm("(U2) R' F R F' U R U R' U2 R U2 R' U' F' U' F"),
        Algorithm("R U R' U' F2 r U r' F U' R U R'"),
        Algorithm("(U2) F' U' F R U R' F R U R' U' F' U2 x U R' U' R x'"),
        Algorithm("(U') r' F r F R U R' U' R U' R' F' r' F' r"),
        Algorithm("R U2 R2 U' R2 U' R' U R' U R F R U R' U' F'"),
        Algorithm("R U2 R' U' R' F R F r U r' U F"),
        Algorithm("r U2 R' U' R U' r' U' R' F' U' F U R"),
        Algorithm("(U2) R U R' U R U2 R' F R U' R' U2 R U R' F'"),
        Algorithm("(U') r' U' R U' R' U2 r U' F R U R' U' F'"),
        Algorithm("R U R2 D' R U2 R' D R U R' F R F'"),
        Algorithm("F R U R' U' F' R' U' R U' R' U2 R"),
        Algorithm("(U) R' F' U' F U R2 U2 R' U' R U' R'"),
        Algorithm("(U') R' U' R' F R F' U R U R' U2 R U R' U R"),
        Algorithm("R U2 R' U' R U' R' F U R U' R' F'"),
        Algorithm("(U2) R U R' U R U2 R' U' F U R U' R' F'"),
        Algorithm("(U') R' U' R U' R U2 R2 U' R2 U' R2 F' U F R"),
        Algorithm("(U') F U R U2 R' U R U R' U R' F R F' U' F'"),
        Algorithm("(U) R U R' U R U2 R' U2 F R U' R' U R U2 R' U' F'"),
        Algorithm("(U) R' U R U F U R U' R' F' R' U2 R"),
        Algorithm("(U') R' F R U R U' R' F' U R U R' M' U R U' r'"),
        Algorithm("(U') r' R' D' r U' r' D r U R"),
        Algorithm("R2 U2 R' U R U' R U2 R F' U2 F R"),
        Algorithm("(U') F U R U2 R' U' R' U' F' U F R F' r' F r"),
        Algorithm("(U2) R U2 R' U' R2 U' R' F U R2 U' F' R' U R"),
        Algorithm("(U2) r U R U' r' F U R' U' F'"),
        Algorithm("F' U' F U' R' D' R U R' r U r' D R"),
        Algorithm("(U2) R U2 R2 U' F' U F R2 U' R' U' R' U' F' U F R"),
        Algorithm("(U') R' U' R F R F' R U R' U' M' U R' U' r'"),
        Algorithm("(U2) F U R' U' R U R U' R' F' U2 R' U2 R"),
        Algorithm("F U R U R' F' U F R U R' U2 R U' R' F'"),
        Algorithm("R2 F R U R U' R' F' R U' R' F' U F R"),
        Algorithm("(U') L' U R U' L U R' U2 F R U' R' U R U R' F'"),
        Algorithm("(U') r' U' F' U F r U' r' F R F' r U R'"),
        Algorithm("(U2) F R U R' U' F' U r U R' U' r' F R F'"),
        Algorithm("(U2) F U R' U2 R2 U R2 U F' R U R U' R'"),
        Algorithm("(U) R' U' R U' R U R' U' R' U2 F R F'"),
        Algorithm("F R U R' U' F' U2 r' F R F' r U R'"),
        Algorithm("(U') R' U2 R U R' F U R U' R' F' U' R U' R' U2 R"),
        Algorithm("(U') R' F' U' F U R r U R' U' r' F R F'"),
        Algorithm("(U') F U R U' R2 F R F' U F R' F' R2 U R' F'"),
        Algorithm("(U') r' U2 R U R' U r U R U R' U' R' F R F'"),
        Algorithm("(U2) R U R' U' R' F R F' U2 R' U2 R U R' U R"),
        Algorithm("(U) F R U2 R' F' U F R U R' U F'"),
        Algorithm("r U R' U' r' F R F' U2 F R U R' U' F'"),
        Algorithm("(U) R2 U' R' F R F' U R U' R' F R F' R"),
        Algorithm("(U2) F R U R' U' R F' U2 R' U' R U' r U R' U' r'"),
        Algorithm("(U') R' U2 F' U F U R U2 R' U R U R' U2 R"),
        Algorithm("(U2) F R U R' U' R U R' U' R U' R' U' R U R' F'"),
        Algorithm("(U2) R U R' F' U' F U R U2 R'"),
        Algorithm("F U R U' R' U R U2 R' U' R U2 R' U' F'"),
        Algorithm("(U2) F R U R' U2 R' U2 R U F' U' R' U2 R"),
        Algorithm("R U R' F' U' R' U2 R F U' R' U' F R F'"),
        Algorithm("F U R U' F' r U R2 U R U2 r'"),
        Algorithm("(U2) R' U' R U2 R' F' U F U R U R' U R"),
        Algorithm("(U') R U' R' U R2 U2 R U' R2 U2 F' U F R U' R"),
        Algorithm("R' U' R U' R' r U R' U' r' D' r U2 r' D R2"),
        Algorithm("(U2) R' U R' F' U' F R U R U' R' U' R' U R2"),
        Algorithm("(U') F' r U r' U2 r' F2 r U' F R U R' U' F'"),
        Algorithm("(U') R U2 R2 F R F' U2 R' U' F R F' R' U R"),
        Algorithm("(U') R' U2 R U' R' U R U R2 F' U' F U R U R"),
        Algorithm("(U) R' U' R U' R2 U2 R U R' U R U F' U F U R"),
        Algorithm("R U R' U R U2 R2 F R U' R' F' r' F r U' R"),
        Algorithm("(U) R' U' R' F R F' R' D' R U R' D R2"),
        Algorithm("R U R' U R U2 R2 U' F U R U' R' F' R"),
        Algorithm("(U) R' U' R U' R' U2 R U2 r' U2 R U R' U r"),
        Algorithm("(U2) F' r U' r' F2 r U r' U R U R' U2 r U r'"),
        Algorithm("(U2) R U' R' F2 R U2 R' U2 R' F2 R U R' F R F'"),
        Algorithm("R U R' U R U' R' U R U2 R' r U R' U R U2 r'"),
        Algorithm("(U) R' U2 R U R' U R U2 r' U' R U' R' U2 r"),
        Algorithm("F' r U' r' F2 r U r' U' R U' R' U r U r'"),
        Algorithm("(U2) r U r' R U R' U' r U' r' U R' U2 R U R' U R"),
        Algorithm("R U R' U r' R2 U' R' U R U' R' U r U2 R'"),
        Algorithm("(U) R U' R' U F' r U' r' F2 U R U' R'"),
        Algorithm("(U2) R U R' F' R U2 R' U' R U' R' U2 F U R U2 R'"),
        Algorithm("(U2) F R U R' U' R U' R2 U2 R U R' U R2 U R' F'"),
        Algorithm("R' F R U R' U' F' U2 L' U2 R U' R' U2 R L"),
        Algorithm("R' U' R U' R' U2 R2 U R' F' U2 F R U' R'"),
        Algorithm("(U2) r' U2 R U R' U r U2 F R U R' U' F'"),
        Algorithm("(U2) R U2 R2 F R U R' F' R F U' F' U R U R'"),
        Algorithm("(U2) R' U2 R2 U R U R U' R' U' R F R F' U R"),
        Algorithm("(U2) R' U2 R U R' F' U' R U R' U R U2 R' F R"),
        Algorithm("(U') r U R' U R U2 r2 U' F' U F r"),
        Algorithm("(U2) F R U R' U' F' U' R' U2 R U R' U R"),
        Algorithm("(U') R' F' U' F U R U' R U R' U R U2 R'"),
        Algorithm("R' U' R U' R' U2 R U' R' U2 R U R' F' U F R"),
        Algorithm("(U2) F R U R' U' F' R U R' U R U2 R'"),
        Algorithm("(U') F R U R' U' R U R' U' F' R U2 R2 F R F' R U2 R'"),
        Algorithm("(U') r U R' U R U2 r' U F R U R' U' F'"),
        Algorithm("(U') R' U' F U R U' R' F r U r' F R"),
        Algorithm("(U) r' R2 U R' U R U2 R' U M' U' F R U' R' U R U R' F'"),
        Algorithm("(U') R' F' U2 R' U2 R U R' F U F' R F U' R"),
        Algorithm("(U) R' U2 R U R' U R2 U2 R' U2 R' F R F'"),
        Algorithm("R' U2 R F R U R' U' F' U' R' U R U R' U R"),
        Algorithm("(U) R' F' U' F U R F U R U2 R' U R U R' F'"),
        Algorithm("(U2) R U R' U' R' F R2 F' r U R' U' r'"),
        Algorithm("(U2) r U R' U' r' F R2 U' R' U R U R' F'"),
        Algorithm("(U2) R U' R' U R U R' U' F' U F U' R U R'"),
        Algorithm("F R U R' U2 r' F R F' r U R' F'"),
        Algorithm("(U') R U2 R' U' R U R' U' F' U F U R U2 R'"),
        Algorithm("(U) F R2 U R' U R2 F R F' R2 U2 R2 F'"),
        Algorithm("(U) M' U M U R U R' F' U' F U r U2 r'"),
        Algorithm("(U') R' U' R' F R F' R U' R2 D' R U2 R' D R2"),
        Algorithm("(U2) R U2 R' U2 R' F R F' U2 R U R' U' R' F R F'"),
        Algorithm("(U2) R2 U2 R U' R' U R' U2 R' y R U2 R' F'"),
        Algorithm("(U2) R' U2 R F U R' U' F' U2 R U R U' R'"),
        Algorithm("(U2) R U R' U' R' F R F' r U R' U' r' F R F'"),
        Algorithm("F R U R' U' F' U' r U R' U' r' F R F'"),
        Algorithm("R' U' R U R U R' U' R' U F R F'"),
        Algorithm("F' U2 F R U R' U2 R U2 R' U R U' R' F' U' F"),
        Algorithm("(U) r' R2 U R' U R U2 R' U M' U' R U R' U' R' F R F'"),
        Algorithm("(U) r U' R' U' F U R U' R' F' R U2 R' U' M"),
        Algorithm("(U') R' U' R' U2 R2 U R2 F R F' R' U R U R"),
        Algorithm("F R U' R' U R U R' F' U R U2 R' U' R U' R'"),
        Algorithm("(U') R U2 R' U2 R' U' F R F' R' U R"),
        Algorithm("(U2) R' F' U2 F R U' R' F' U' F U' R"),
        Algorithm("(U) r' F R F' r U R' F U R U' R' U R U' R' F'"),
        Algorithm("(U) R2 D' R U2 R' D R U2 R U' F R U R' U' F'"),
        Algorithm("(U') F U R U' R' U' R' F R F' R U2 R' U' F'"),
        Algorithm("(U) F U R U' R' F' U' R' U' F U R U' R' F' R"),
        Algorithm("R' F R U R' U' F' U R"),
        Algorithm("(U2) F R U R' U' R' U' R2 U' R2 U2 R2 U' R' F'"),
        Algorithm("(U) R2 D' R U2 R' D R U2 F' U' F U R"),
        Algorithm("(U) M' U R' F R F' U' F' U F M"),
        Algorithm("(U2) R U' R' F' r' U2 R U R' U r U F"),
        Algorithm("R U R' F' U' F R U R' U' R U' R'"),
        Algorithm("(U') r U r' U' R2 D r' U r D' R2 U r U' r'"),
        Algorithm("F R U R' U2 R' U2 R U F' R' U' R U R' U R"),
        Algorithm("(U) F R' F' R U2 R U2 R2 F' U' F U R"),
        Algorithm("(U') R' U2 R2 U R' U R U' R' U' R' U F R F'"),
        Algorithm("R2 U2 R U' R' U' R' F R F' R U2 R' U2 R2"),
        Algorithm("(U) F U' R' U' R U R U R' U' R' F' U F R F'"),
        Algorithm("(U2) r' U' R U R' F' r U2 R' U' r U' r' F R"),
        Algorithm("R' F R F' U2 F' U2 F2 U R U' R' U R U' R' F'"),
        Algorithm("R U R' U' R' F R F' U2 R' U' R U' R' U2 R"),
        Algorithm("(U2) R' U' R U' R' U2 R' U R' F' U2 F R U' R' U' R'"),
        Algorithm("(U2) r' U' R U' R' U2 r R U R' U' R' F R F'"),
        Algorithm("(U') r U2 R' U' R U' r' U2 R' U2 R U R' U R"),
        Algorithm("(U2) R U2 R2 D' R U2 R' D R2 U' R2 F R F'"),
        Algorithm("r' U2 R U R' U r U2 R U2 R2 U' R2 U' R2 U2 R"),
        Algorithm("(U2) F R U R' U' R U R' U' F' U' R' U' R U' R' U2 R"),
        Algorithm("R U R' U R U2 R' U r U r' R U R' U' r U' r'"),
        Algorithm("(U) r' U' R U' R' U2 r U' R U2 R2 U' R2 U' R2 U2 R"),
        Algorithm("(U) R U R' U R' F R F' r' F R F' r U2 R'"),
        Algorithm("R' D' r U r' D R U R' F R F' U F' U F"),
        Algorithm("r' R2 U R' U R U2 R' U r U2 R' U' R U' R'"),
        Algorithm("(U2) F R U R' U' R U R' U' F' R U2 R' U' R U' R'"),
        Algorithm("(U') r U2 R' U' R U' r' U' R U R' U R U2 R'"),
        Algorithm("R' U2 R U R' U R F U R U' R' U R U' R' F'"),
        Algorithm("(U2) M' R' F' U' F U R U' R r'"),
        Algorithm("(U2) F U R U' R' F' R' U2 R U R' U R"),
        Algorithm("(U2) R U R U' R' F U R2 U2 R' U2 R U F'"),
        Algorithm("(U2) F U R' U' R2 U' R2 U2 R2 U2 R' U' F'"),
        Algorithm("(U) R U2 R' U' R U' R2 F' U' F U R"),
        Algorithm("(U') r R2 U' R' F R F' U R U M"),
        Algorithm("(U) r U r' R U R2 F R F' U' r U' r'"),
        Algorithm("(U') F R U' R' F' r' F r U' R' U2 R U R' U R"),
        Algorithm("R U R' U' M' U R U' r' U F R U R' U' F'"),
        Algorithm("(U2) R' F' U' F U R U' R U R' U' M' U R U' r'"),
        Algorithm("(U2) R U R' U R U2 R' F R U R' U' F'"),
        Algorithm("(U) R U2 R' U' R U' R' U' F R U R' U' F'"),
        Algorithm("R U' R' U2 R U y R U' R' U' F'"),
        Algorithm("(U) F U R U R' U2 R U R' U R' F R F' U2 F'"),
        Algorithm("R U R' U' r' F R2 U' R' F' r' F r U M'"),
        Algorithm("(U2) F R' F' R U2 R U' R D R' U' R D' R2"),
        Algorithm("(U2) F R U' R2 U2 R U R' U R U R U R' F'"),
        Algorithm("(U') F' r U r' R U R' U2 r' F r U2 R U2 R'"),
        Algorithm("R U R' U' R' F R F' U2 R' F' U' F U R"),
        Algorithm("F' U2 F R' F R F' U R' D' r U r' D R"),
        Algorithm("r' F2 r U' F R U R' U' F' U2 F R U' R' U' F'"),
        Algorithm("(U2) R U R2 F R F' r U2 r' U' F' U F U r U r'"),
        Algorithm("(U2) F R U' R' U' R U R' F' U R' U2 R U R' U R"),
        Algorithm("(U2) F R U' R' U' R U R' F' U2 R U R' U R U2 R'"),
        Algorithm("(U2) R U2 R' U R U' R U R' U F R2 F' R' U2 R2"),
        Algorithm("(U') r U' r' U' r U r' F' U F U2 F R U R' U' F'"),
        Algorithm("(U2) F U' R U R' F' U' F U' R U2 R' U R U R' F'"),
        Algorithm("(U) r' U' F R' F R U' R U R' F U F r"),
        Algorithm("(U2) R2 F2 r U2 R U' r' F R' F R F' R"),
        Algorithm("(U2) F U R2 D R' U' R D' R2 F'"),
        Algorithm("(U) F R U' R' U R U R2 F' U' F U R U' F'"),
        Algorithm("(U') R' U' R U' R' U R U' R' U y' R' U2 R U R' U2 R U f z'"),
        Algorithm("(U') r U' r' U' r U r' U' R' F R F' U F' U F"),
        Algorithm("(U2) R U R' U' R F U R' U' R U R U' R' F' R'"),
        Algorithm("r' R' F R F' U F' r U' r' F2 R U' R' U' r"),
        Algorithm("(U2) F' U' F R U R2 D' r U r' D R"),
        Algorithm("(U') R' U' R U' R' U R U' r U R' U' r' U2 F R F'"),
        Algorithm("(U2) F R' F' U2 R U R' U R U' R U' R'"),
        Algorithm("(U2) F R' F' R U R U' R' U R U R' U R U2 R'"),
        Algorithm("(U2) F R U R' F' R' F U' F' R' F R F' U R"),
        Algorithm("(U') R' F' U' F R U R' U R U R' F' U' F U' R"),
        Algorithm("(U') F R F' R U2 R' U' F' U' F R' U R U2 R'"),
        Algorithm("(U') F R U' R' U R U R' U F' U F U' R U' R' F'"),
        Algorithm("(U2) F R' F' U2 R U R U' R' U R' U R"),
        Algorithm("(U2) F R' F' R U R U' R2 U2 R U R' U R"),
        Algorithm("(U') R U R' U R U' R' U R U' R' U' R' F R F'"),
        Algorithm("F R U R' F' r2 F r U' F r U r' F r"),
        Algorithm("(U) R U R' U' F' U2 F U R U' R' U' R U' R'"),
        Algorithm("(U') R U R' U' R' F R2 U' R' F' r' F' r U r' F r"),
        Algorithm("R' U R U' R' U R U R' U F' U2 F R"),
        Algorithm("(U) F R U' R' U' R U2 R' U' F' U2 R' F' U' F U R"),
        Algorithm("(U') R' U' R U' R' U' R U F U R U' R' F' R' U2 R"),
        Algorithm("(U2) R U R U' R' F R' U R' U' R2 U R U' F'"),
        Algorithm("F' U2 F U' R U R' U R U R' F R' F' R2 U' R'"),
        Algorithm("(U) R U R U R2 U' R U R F R2 F' R' U2 R'"),
        Algorithm("(U') R' U' R' U' F' U F R2 U' R' U' R U R' U2 R"),
        Algorithm("(U) F R' F' R U2 R U' R2 F R F' U F R' F' R"),
        Algorithm("(U) F R U' R' U' R U2 R' U' F' U F R U R' U' F'"),
        Algorithm("(U') R U2 R' U' F' U' F U R U' R' U R U2 R'"),
        Algorithm("(U2) R2 F2 U' R U' R' U2 R U' F R' F R F R"),
        Algorithm("(U') R U2 R' U2 R' F R F' r U R U' r' F R' F'"),
        Algorithm("(U) R' F2 R2 U' F U' F' U2 R2 F2 R"),
        Algorithm("F R U R' U' F' R' U' R U' R' U F' U F R"),
        Algorithm("(U2) F R U' R' U' R U R' F' U L' U R U' L U R'"),
        Algorithm("(U2) R' F R F' R' F R F' R U R' U' R U R'"),
        Algorithm("r' U' R U2 R' U R' U2 R U R' U R2 U R' U2 r"),
        Algorithm("(U') F R U R' U' R U R' U' F' r U2 R' U' R U' r'"),
        Algorithm("R2 F2 r U' r' F2 R2 U' R' U' R' F R U R"),
        Algorithm("(U) r' U2 R U R' U r U2 F R U R' U' R U R' U' F'"),
        Algorithm("R' U2 R U R' U R U2 r U r' R U R' U' r U' r'"),
        Algorithm("r' U2 R U R' U r U R' U' R U' R' U2 R"),
        Algorithm("(U) R U R' U R U' R' U R U' y R U' R' U R U' R' F'"),
        Algorithm("(U) R' U' R U' R' U2 R F R U R' U' F'"),
        Algorithm("(U) M U F R U R' U' F' M'"),
        Algorithm("(U) R' F' U' F U R U F R U R' U' R U R' U' F'"),
        Algorithm("(U2) F R U' R2 U2 R2 U R2 F' U R U R U' R'"),
        Algorithm("(U') R U2 R' F' U' F R U2 R' U F' U2 F"),
        Algorithm("(U') r D' R2 U2 R U' R' U' R2 D r'"),
        Algorithm("(U2) F R U R' U' F' R U R' U' M' U R U' r'"),
        Algorithm("(U2) R' U2 R U R' U R U F R U R' U' F'"),
        Algorithm("(U') R' U2 R U R' U R U2 R U2 R2 F R F' R U2 R'"),
        Algorithm("(U') R' U' F' U F R U' F R U R' U' R U R' U' F'"),
        Algorithm("(U2) R' U2 R U R' U R U2 R' F' U' F U R"),
        Algorithm("(U) R' U' R U' R' U2 R U R' F' U' F U R"),
        Algorithm("(U) R U2 R2 U' F' U R U2 R U2 R' F U R U2 R'"),
        Algorithm("(U') R' U R U2 R' U' F' U F U R"),
        Algorithm("(U') r' F R U F U' F' R U R' U R U2 R' U M'"),
        Algorithm("(U2) F R' F' R U2 R' U' R2 U' R2 U2 R"),
        Algorithm("(U') F R U' R' U R U R' F' U2 F R U R' U' F'"),
        Algorithm("(U2) R' U F' U' F R U R' U R' D' R U R' D R2"),
        Algorithm("R U R' U R U2 R' U' R' F R U R' U' F' U R"),
        Algorithm("R' U R U' R2 F' U' F U R U' R U' R' U R"),
        Algorithm("R' U R U' R' U' F R U R' U' F' R U' R' U R"),
        Algorithm("(U2) F R' F' R U R U' R' U' R U2 R' U' R U' R'"),
        Algorithm("(U) F R U' R' U' R U R' F' R U2 R2 F R F' R U2 R'"),
        Algorithm("(U) R U R' F' U F R U' R' U2 R' U' R U' R' U2 R"),
        Algorithm("(U') R U2 R' U F' U F R U' R2 F R U R U' R' F'"),
        Algorithm("(U) R U R' U R' F R F2 R U2 R' U2 R' F R"),
        Algorithm("F R U' R' U' R U2 R' U' F' U' R U2 R' U2 R' F R F'"),
        Algorithm("(U2) R' U' F' U F R L' U R U' L U R'"),
        Algorithm("(U2) R U R' U' R' F R F' R' F R U R' U' F' U R"),
        Algorithm("(U') F U' R U' R' U2 R U' R' U2 R U' R' U' F'"),
        Algorithm("(U2) R' U F' U' F R U R2 D' R U R' D R U R"),
        Algorithm("(U2) R' F R U R' F' R F U' R U R' U' F'"),
        Algorithm("(U2) R U' R' U' F' U2 F U2 R' U' R2 U' R2 U2 R"),
        Algorithm("(U2) R U R' U R U' R2 F R F' R U' y R U2 R' U' F'"),
        Algorithm("(U) R' U' R U F R U R' U' R' U R U' F'"),
        Algorithm("(U') R' F' U F U R2 D r' U' r D' R'"),
        Algorithm("(U') R U' R' U R U' R' U' R U' y R U2 R' F'"),
        Algorithm("R U R' U F' R' U' R U F U' R' U R2 U2 R'"),
        Algorithm("R' U' R U' R' U2 R2 U R' U' F' U2 F U R U R'"),
        Algorithm("(U') R' U2 R U R' U' F R U R' U' F2 U F U R"),
        Algorithm("(U2) r U R' U' r' F R F' U2 R U2 R2 F R F' R U2 R'"),
        Algorithm("R U R' U R U R2 U' F' U F R U' R U2 R'"),
        Algorithm("(U2) F R U R U2 R2 U' R2 U R' F' R U2 R' U2 R'"),
        Algorithm("(U') R' F R F' U2 F' U F2 R' F' R U' R' F R F'"),
        Algorithm("(U') R U R' r U' r' R U' R' U' r U' r' U' F' U2 F"),
        Algorithm("R' U2 R U R' U F R U R' U' F' R U' R' U2 R"),
        Algorithm("(U') F R U R' F' U2 F R U' R' U R U R' U' F'"),
        Algorithm("(U') R' U2 R U R' U' R U R' U R U R U R' U' R' F R F'"),
        Algorithm("(U) R U2 R' U' R U' R' U R' F R U R' U' F' U R"),
        Algorithm("R' F R U R' U' F' U R r U r' R U R' U' r U' r'"),
        Algorithm("(U2) F R U' R' U' R U R' F' U' R' U' R U' R' U2 R"),
        Algorithm("r' U2 R U R' U r U' r' F R F' r U R'"),
        Algorithm("R U R' U' R' F R F' R' U' R U' R' U F' U F R"),
        Algorithm("(U2) R' F R U2 R' r U r' F' R U' F R U' R' F'"),
        Algorithm("(U2) F R U' R' U' R U2 R' U' F' R' U' F' U F R"),
        Algorithm("(U2) F R U' R' U' R U R' F' R U2 R' U' R U' R'"),
        Algorithm("(U') R U' R' U F' U' F U R U' R' U' R U R'"),
        Algorithm("(U') F' U' F U R U2 R' U' F' U' F R U R' U R U2 R'"),
        Algorithm("(U2) R' F' U' F U' R U R' F U R U' R' F' R"),
        Algorithm("(U2) R' U2 r' D' r U2 r' D r U2 R U R' U R"),
        Algorithm("r' U' R U' R' U2 r U' r' U2 R U R' U r"),
        Algorithm("(U') R' F' U2 R U R' U F2 r U2 r' F R"),
        Algorithm("R' U' F' r U' r' F2 R U R' U' R U' R' U R"),
        Algorithm("(U2) r U R' U R U2 r' R' U' R U' R' U2 R"),
        Algorithm("R' U' R D r' U r D' R2 U R2 D r' U' r D'"),
        Algorithm("(U2) F R U R' U' R U R' U' F' R' U2 R U R' U R"),
        Algorithm("(U) R U2 R2 F R F' R U' R' F' U2 F R U' R'"),
        Algorithm("(U) r' U2 R U R' U r U r' U' R U' R' U2 r"),
        Algorithm("(U) R' U2 R U R' U R U r' U' R U' R' U2 r"),
        Algorithm("(U2) F R U R' U' R U R' U' F' U R U R' U R U2 R'"),
        Algorithm("(U2) r U R' U R U2 r' U R U2 R' U' R U' R'"),
        Algorithm("(U) R U2 R2 F R F' R U2 R' U2 R' U' F' U F R"),
        Algorithm("r U r' F' U2 F r U' R' U M"),
        Algorithm("(U') R' U2 R U R' U R U R' U2 R U R' F' U F R"),
        Algorithm("(U') F' R U R' U2 r' F r U R U' R' F"),
        Algorithm("(U') R' U2 R U R' F' U F R"),
        Algorithm("(U2) R' U' F' U F R"),
        Algorithm("(U) r' U' r R2 F R F' M U r"),
        Algorithm("(U2) R' U' R U' R' U2 R U' R' U' F' U F R"),
        Algorithm("f R U R' U' f' U R' U' R U' R' U2 R"),
        Algorithm("(U) r2 U' r R' F R F' R U' R' U r' U r2"),
        Algorithm("(U2) F R U R' F' U r' U' R' F2 R U r"),
        Algorithm("(U2) F U R U' R' F' R U2 R' U' R U' R'"),
        Algorithm("R U R' F' U2 F R U' R'"),
        Algorithm("M' U R' U' R U' r' U' r U r' F' U' F R"),
        Algorithm("(U) F R U' R' U' R U R' F' U2 R' U' F' U F R"),
        Algorithm("R U' R' U R U' R' U' F R' F' R2 U R'"),
        Algorithm("(U2) R2 U' R U R U R' U' R' F' U F R U' R"),
        Algorithm("(U2) F' r U R' U' r' F U' F' U F R"),
        Algorithm("(U2) r U R' U R U2 r' U2 r' F R F' r U R'"),
        Algorithm("r' U2 R U' R' U' R2 D r' U2 r D' R2 U r"),
        Algorithm("R U R2 F R F' R U R' U' F' U2 F"),
        Algorithm("(U) R' F R U2 r U' r' y' U2 R2 U2 R"),
        Algorithm("(U) F' U2 F R U' F R U R' U' F' U' R' U' F' U F"),
        Algorithm("(U') F R U' R' U' R U R' F' U' r' U' R U' R' U2 r"),
        Algorithm("(U) r2 D' r U' r' D r2 U' R' U M U r"),
        Algorithm("(U) F R' F' R U R U' R' U F R U' R' U' R U R' F'"),
        Algorithm("(U2) R U' R' F' U F R U R' U R U R' U' R U' R'"),
        Algorithm("(U) R' F' U' F U R U2 R U2 R' U2 R' F R F'"),
        Algorithm("R U' L' U R' U' L U' R' U' F' U F R"),
        Algorithm("(U') R' U' F' U F R2 U2 R' U2 R' F R F'"),
        Algorithm("(U) F R' F' R U F' U R U R' U' R' F R2 U' R'"),
        Algorithm("(U2) r R D r' U2 r D' r' U2 R'"),
        Algorithm("(U2) R U' R' U' F' U2 F R' U2 R U R U' R2 U2 R"),
        Algorithm("(U2) R U R2 F' U' F R2 U' R' U R' U' R U R' U R"),
        Algorithm("(U') M' U' R2 D r' U2 r D' R' U2 r'"),
        Algorithm("(U2) F R' F' r U R U' r' R' U' F' U F R"),
        Algorithm("R' U R U2 R' U' R U2 R' F R' F' R2"),
        Algorithm("(U2) F U R' U2 R2 U R2 U R F'"),
        Algorithm("(U) F' U2 F U R U R' U' F' U2 F"),
        Algorithm("(U) R' F' U' F U R U R' F R F' U2 F' U2 F"),
        Algorithm("(U) R' U' F' U' F R U2 R' U' R U' R' U R"),
        Algorithm("(U) r' U2 R U R' U r U' R U2 R' U2 R' F R F'"),
        Algorithm("R' U R U2 R2 U' F' U R U R U' R' F R"),
        Algorithm("(U2) R U2 R' U' R U' R' U' F R' F' R U R U' R'"),
        Algorithm("(U2) R U2 R' U2 R' F R F' U' r U R' U R U2 r'"),
        Algorithm("(U2) R U R' U' R' F R F' U' R' U' R' F R F' U R"),
        Algorithm("(U2) F' U F R U R' U2 R' F R F' M' U R U' r'"),
        Algorithm("F R U' R' U R U R' F' U R' U' F' U F R"),
        Algorithm("(U) R' U2 R U R' U R U' R U2 R' U2 R' F R F'"),
        Algorithm("(U') R' F' R U2 R U2 R' F2 R' F' R U' R U' R'"),
        Algorithm("(U2) F R U R' F U R U' R' F' R U R' U2 F'"),
        Algorithm("R U R' U' F' U' R' F R U R' F' R F"),
        Algorithm("(U') R U2 R2 D' R U R' D R U R' F R F'"),
        Algorithm("(U2) R U' R' U' F' U2 F R' F R2 U' R' U' R U R' F'"),
        Algorithm("(U') r' F R F' r U R' U2 R' U' F' U F R"),
        Algorithm("(U') R2 F R U R U' R' F' R U2 R' U F' U F R"),
        Algorithm("(U2) R' U R U R' F R' F' R2 U' R' F' U' F U' R"),
        Algorithm("(U') R' U' R F R' U R U' R' F' R U R U' R'"),
        Algorithm("(U') R U R' y' R2 D' r U' r' D R2"),
        Algorithm("(U') R2 F R F' R U2 R' F' U2 F R"),
        Algorithm("R D r' U r D' R2 U' F' U' F R"),
        Algorithm("(U) R' F U R' U' F' R U' R' U2 F R F' U2 R"),
        Algorithm("(U2) r U2 R' U' R U' r' U' r U R' U R U2 r'"),
        Algorithm("(U2) R' U F' U2 F R U R' F R' F' R2 U R' U R"),
        Algorithm("(U) r' U' r U' R' U M U r U' R' U2 R U R' U R"),
        Algorithm("(U') r U R' U R U2 r' U r U2 R' U' R U' r'"),
        Algorithm("(U) r' U' R U' R' U2 r R U R' U R U2 R'"),
        Algorithm("R U R' U R U2 R' U' F U R U' R' U R U' R' F'"),
        Algorithm("(U2) r U R' U2 F' r U' r' F2 U2 R U' r'"),
        Algorithm("(U') R U R' U r' U' R U' R' U2 r U2 R U2 R'"),
        Algorithm("(U') R U R' U R U2 R' U r U2 R' U' R U' r'"),
        Algorithm("(U) r' U' R U' R' U2 r U' R' U2 R U R' U R"),
        Algorithm("(U') R U2 R2 F R F' R U2 R' F U R U' R' F'"),
        Algorithm("R U2 R2 U' R2 U' R2 U2 R U' R' U' F' U F R"),
        Algorithm("(U) R U R' U' M' U R U' r' U F U R U' R' F'"),
        Algorithm("R U2 R2 F R F' U' R U' R'"),
        Algorithm("(U) R U2 R2 F R F r U r' F"),
        Algorithm("(U2) R' U' F' U F R2 U R' U R U2 R'"),
        Algorithm("(U) R U R' U R U2 R' f R U R' U' f'"),
        Algorithm("F' U' F R' U' R' F R F' U R2 U2 R'"),
        Algorithm("(U2) F U R U' R' F'"),
        Algorithm("(U') R' U' F' U F R U' r U R' U' r' R U R U' R'"),
        Algorithm("(U) F R U R' U' F' U2 r U2 R' U' R U' r'"),
        Algorithm("(U') F R U' R' U2 R U R' F'"),
        Algorithm("(U2) R' U' F' U F R U' R' U2 R U R' U R"),
        Algorithm("(U') F R' F' R U R U' R' U' F U R U' R' F'"),
        Algorithm("(U) R' U2 F' U2 F R' F R F' U R U' R' U R"),
        Algorithm("(U') R' U R U' R' U R U2 R2 F R F' U2 R"),
        Algorithm("r U r' U2 r' D' r U2 r' D r2 U' r'"),
        Algorithm("R U R' U R U' R' U R U' R' F' U F R U R' U' R U' R'"),
        Algorithm("(U) R2 U R' U' R' U' R U' F' U' F R U2 R' U R'"),
        Algorithm("(U2) R U R' U' R' F R U R U' R' U R U' R' F'"),
        Algorithm("r U' r' U2 R' F R y' U2 R2 U2 R'"),
        Algorithm("(U') R U R' U' R' F R U R U2 R' U R U2 R' U' F'"),
        Algorithm("R2 U F' U F R U' R' F R' F' R'"),
        Algorithm("(U') R U R' U2 F U R U' R' F' R U R' U R U' R'"),
        Algorithm("(U2) r2 D r' U r D' r2 U R U' M' U' r'"),
        Algorithm("(U) F R U' R' U' R U2 R' U' R' F' U' F U R U' F'"),
        Algorithm("(U') F R U' R' U' R U R2 F' R U R U' R'"),
        Algorithm("(U') F R U R' U' F' U' R' F2 r U2 R U' r' F"),
        Algorithm("(U) R' F R U R' U' F' U R F R' F' R U R U' R'"),
        Algorithm("(U2) F' U F U R U2 R' U' F' U F"),
        Algorithm("(U) r' F R F' r U R' F U R U' R' F'"),
        Algorithm("(U) r U R U' r' F R' U R' F R F' U' F'"),
        Algorithm("(U2) R U2 R2 F R F2 U2 F R U' R2 F R F'"),
        Algorithm("R2 U R' U F' U F U2 R U R' U' R U' R' U R'"),
        Algorithm("(U') F' r U R' U' r' F R U' F U R U' R' F'"),
        Algorithm("r' R U R2 D' r U2 r' D R U2 r"),
        Algorithm("(U') R U' R' U2 R U R' U2 R U R2 F R F'"),
        Algorithm("(U2) F U2 R U' R' F R U R' U' F' R U' R' F'"),
        Algorithm("(U2) F' U' F R U R' U2 R U R2 F R F' U F' U F"),
        Algorithm("(U2) R U' L' U R' U2 r U l U R' F'"),
        Algorithm("(U2) R U' L' U R' U' L U F U R U' R' F'"),
        Algorithm("(U) R' U2 R U' R' U' F' R U R' U R U2 R' U F R"),
        Algorithm("R' U' R' D' R U' R' D R2 U' R' F' U F U' R"),
        Algorithm("(U') F U R U R' U2 R U R' U2 R U R' U F'"),
        Algorithm("(U2) F U R U2 R' U R U R2 F' R U R U' R'"),
        Algorithm("(U') F R F' U R U R' U' R' U' R U F' U' F U' R'"),
        Algorithm("F R U2 R' F' U2 F R' F R F2"),
        Algorithm("(U) F' U' F R2 D r' U r D' R2"),
        Algorithm("(U') R' D' r U' r' D R2 U' R' F' U F"),
        Algorithm("(U') R U2 R' U' F' U' F U R U2 R'"),
        Algorithm("(U') F U R U2 R' U R U2 R' U' F'"),
        Algorithm("(U') r U R' U' r' F R2 U' R' U2 R U R' F'"),
        Algorithm("(U') R U R' U' R' F R2 U' R' U2 R U R' F'"),
        Algorithm("(U) R' U2 R U R' U R U2 F R U' R' U' R U R' F'"),
        Algorithm("(U2) R U' R' F' U F R U R' U R U' R'"),
        Algorithm("(U) R' U' R U' R' U2 R F U R U2 R' U' R U R' F'"),
        Algorithm("(U) F R U' R' U' R U R' F' U2 r U R' U R U2 r'"),
        Algorithm("(U2) r U R' U R U' R U' r' F R' F'"),
        Algorithm("(U') R U R' U' R' F R F' U' F U R U' R' F'"),
        Algorithm("(U') R U' R' F' U2 r' F r U y' R U' R' U R"),
        Algorithm("(U') R' F R U R' U' F' U R U2 r U R' U R U2 r'"),
        Algorithm("(U2) R U2 R2 F R F' R U2 R' U R' U' R' F R F' U R"),
        Algorithm("(U) R' F' R U R' U R U2 R' F U2 F' U' F U' R"),
        Algorithm("F' U2 F U' R U R' U' R U R' U F' U F"),
        Algorithm("(U) R' U' R U' R' U2 R r U R' U R U2 r'"),
        Algorithm("R' U' R U' R' F' U F R U' R' U' F' U F U' R"),
        Algorithm("(U2) r U r' R U R' U' r U' r' U' R U R' U R U2 R'"),
        Algorithm("(U') R U2 R2 F R F2 U F U' R U2 R'"),
        Algorithm("(U') R U R' U R U2 R' r' U' R U' R' U2 r"),
        Algorithm("(U') F R U R' U' R U R' U' F' r' U2 R U R' U r"),
        Algorithm("(U') r U r' U2 R U R' U2 R U R' U' r U' r'"),
        Algorithm("F' U2 F R' F R F' R U' R' U F' U2 F"),
        Algorithm("F U R U' R' U R U' R' U y' R' U R U' R' U R U2 R'"),
        Algorithm("(U') R' U' R' F R F' U R U' R' U' R U' R' U2 R"),
        Algorithm("(U') M U M' U2 M U R' U' F' U F r"),
        Algorithm("F U' R' U2 R U2 R2 U' F' R U R' U' R'"),
        Algorithm("(U) r' R2 U R' U R U2 R' U M' U' F R U R' U' F'"),
        Algorithm("F R U R' U' F'"),
        Algorithm("(U) R' F' U' F U R"),
        Algorithm("(U2) R U R' U R U2 R' U R U2 R2 F R F' R U2 R'"),
        Algorithm("(U) M' U' F R U' R' F' U' r' F2 R"),
        Algorithm("(U') R2 U R U R' U' R' U' R' U R2 U' F' U F R"),
        Algorithm("R U2 R2 U' R2 U' R2 U2 R f R U R' U' f'"),
        Algorithm("(U) F U R U' R' F' r' U2 R U R' U r"),
        Algorithm("R' U' F' U F R U' r U2 R' U' R U' r'"),
        Algorithm("R U' R' U' F U R U' R' F r U r' F"),
        Algorithm("R' U2 R U2 F R U R' U' R' U R U' F'"),
        Algorithm("(U2) R' F U' R' F R U' R U R' U F' R U R' F' R"),
        Algorithm("(U') R U R' U F' r' F r F U' R U R' U' R U' R'"),
        Algorithm("F R' F' R U R' F' U' F U R U' R U' R'"),
        Algorithm("(U') F R' F' r U R U' r' U2 R' F' U' F U R"),
        Algorithm("(U) r' U2 R U R' U' R U R' y' R U R' U' R' U F z'"),
        Algorithm("R2 D R' U R D' R' U' R' F R U R' U' F'"),
        Algorithm("r U' r U2 R' F R U2 r2 F2 R U R' U' F'"),
        Algorithm("F R' F' R U R' F' U' F R2 U' R' U R' U R"),
        Algorithm("(U2) r U R' U' r' F R U R U' R' U R U' R' F'"),
        Algorithm("(U) F R' F' R U R U' R' r' U2 R U R' U r"),
        Algorithm("(U') R' U' R' F R F' R U' R' U R' D' R U R' D R2"),
        Algorithm("(U2) r' U' R U' R' U' r U r' F' U' F r"),
        Algorithm("(U') R U2 R2 F2 R U F U' r U2 r' F U' F'"),
        Algorithm("(U') F' r U R' U' r' F R U F R U R' U' F'"),
        Algorithm("(U') r U2 R' U' R U R' U2 r' U' F R F' R' U R"),
        Algorithm("(U2) R' F R U R' U' F' U R U' R' U' R U' R' U2 R"),
        Algorithm("(U) R' F R F' U' F R U R' U' F' U F' U F"),
        Algorithm("F R U' R' U' R U2 R' U' R U' R' F' r' F r"),
        Algorithm("(U') F' r U R' U' r' F R U2 R' F' U' F U R"),
        Algorithm("F U2 r U2 r' U' F' U F r U r' U2 F'"),
        Algorithm("(U) r' F R F' r U R' U2 F R U R' U' F'"),
        Algorithm("F R U' R' U' R U R' F' r U2 R' U' R U' r'"),
        Algorithm("(U') R' F2 R U R U2 R2 F R U' r U' r' R U' R' F"),
        Algorithm("(U) F' U F U2 R U2 R' U2 R U' R' U' F' U F"),
        Algorithm("(U') R' U R U' x' U r' F r U2 r U' R' U M x"),
        Algorithm("R U' R' U' F' U R U R' U' R' F U' F' U F R"),
        Algorithm("(U2) R U' L' U R' U' L R' F' U' F U R"),
        Algorithm("(U') R' U' R' F R F' U R U r' F R F' r U R'"),
        Algorithm("F R2 D R' U R D' R2 U' F'"),
        Algorithm("R U R' U' R' F R2 U' R' U' R U2 R' U' F'"),
        Algorithm("R U R' U' R' F R U R' U' R F' R' U R"),
        Algorithm("F' U R U R' U R' F2 r U2 r' F R2 U' R'"),
        Algorithm("(U2) F U R' U' R U R U' R' F' U' R' U R"),
        Algorithm("F R F' U' R U' R U R F' U' F R U' R"),
        Algorithm("(U) R U R2 F R2 U R' U' F2 U2 F"),
        Algorithm("F' U' F2 R' F2 U' F U R2 U2 R'"),
        Algorithm("(U2) R U R U' R' F U R2 U' F' R2 F R F' U R"),
        Algorithm("(U') R U R' U R U2 R' U2 R U2 R' U2 R' F R F'"),
        Algorithm("F R U R D r' U2 r D' R' U2 R' U' F'"),
        Algorithm("(U) F R U' R' F R U R' U' F' U' R U2 R' U' F'"),
        Algorithm("(U2) R' U' R' F' R U R U R' U' R U' R' U2 F R"),
        Algorithm("R U' R2 F R F' U' F U R' U' F' U R2 U R'"),
        Algorithm("F U R U' R2 F' U2 R U R' U R2 U2 R'"),
        Algorithm("(U') r U R' U' r' F R F' U F R U R' U' F'"),
        Algorithm("(U') R U' R2 U' F' U F R U2 R U' R'"),
        Algorithm("F R U R' U2 R' F R2 U' R' U' R U R' F' R U R' F'"),
        Algorithm("R' U R U2 R' U' R U R' F2 r U r' F U R"),
        Algorithm("(U2) R U2 R2 F R F' R U2 R' U2 F R U R' U' F'"),
        Algorithm("R U R' U' R' F r U' r' F R F' r U r' F'"),
        Algorithm("(U') R U R' U R' F R F' R' F R F' R U2 R'"),
        Algorithm("R U2 R2 U' R2 U' R2 U2 R U r' U' R U' R' U2 r"),
        Algorithm("(U) R U2 R2 F R F' R U2 R2 F' U' F U R"),
        Algorithm("(U') R2 D r' U2 r D' R2 U2 R' F R F'"),
        Algorithm("(U2) B' U' R' U R U' R' U R U' y R U' R' U2 R"),
        Algorithm("(U) R U2 R2 F R F' R U2 R' U' F R U R' U' F'"),
        Algorithm("(U2) R U2 R2 F R F' R U2 R' U' R' F' U' F U R"),
        Algorithm("(U') R U R' U R U2 R' U F R U R' U' R U R' U' F'"),
        Algorithm("r U2 R' U' R U' r' F U R U' R' U R U' R' F'"),
        Algorithm("(U) R' U' R' F R F' U R"),
        Algorithm("(U) M F U R U' R' F' U' M'"),
        Algorithm("(U') M U' R' U' F' U F R U2 M'"),
        Algorithm("(U2) F R U R' y' R' U R U2 R'"),
        Algorithm("F R U R' U' F' U2 R U2 R' U' R U' R'"),
        Algorithm("(U') R' F' U' F U R U R' U2 R U R' U R"),
        Algorithm("R U R' U R U2 R' U R U R' F' U2 F R U' R'"),
        Algorithm("(U2) R' U' R U' R' U2 R U' F R U' R' F' r' F r"),
        Algorithm("(U') R' U2 R U R' U R U' F U R U' R' F'"),
        Algorithm("(U2) R' U' R U' R' U2 R f R U R' U' f'"),
        Algorithm("(U2) r' U' R U' R' U2 r F R U R' U' F'"),
        Algorithm("R U R' U R U2 R2 U2 R U R' F' U F R"),
        Algorithm("(U) R' U' R U' R' U2 R F R U' R' U' R U R' F'"),
        Algorithm("(U) F R U' R' U2 F R U R' U' F' U R U R' F'"),
        Algorithm("(U) R' F' U R U2 R D r' U2 r D' R2 F R"),
        Algorithm("(U2) R' F R U R' F' R U F U2 F'"),
        Algorithm("R U' R' U' F' U F R' F R F' R U R'"),
        Algorithm("(U2) r U r' R U R' U' r U' r' F' r U R' U' r' F R"),
        Algorithm("(U2) F' r U R' U' r' F R U' R' U' R' F R F' U R"),
        Algorithm("(U) F R U' R' F U R U' R' F' U' R U R' F'"),
        Algorithm("(U2) R U2 R' U' R' F' U' F U R2 U2 R'"),
        Algorithm("F' U R U R' U R r' F r U2 R' U F"),
        Algorithm("(U) F R U' R' U' R U R' F' U F U R U' R' F'"),
        Algorithm("F R2 U2 R2 F R' F' R2 U' R U' R2 F'"),
        Algorithm("(U2) r U r' U' R2 D r' U' r D' R2 U r U' r'"),
        Algorithm("(U) R U R' U R U' R' F' U F R U' R'"),
        Algorithm("(U) R' F' U' F R U R' F R U R' U' R' F' R2"),
        Algorithm("(U') R' U' F' U F R2 U R' U' R' F R2 U R' U' F'"),
        Algorithm("(U) r R D r' U r D' r' R' U R U2 R'"),
        Algorithm("(U2) r U' r' U' r U r' U' F' U2 F"),
        Algorithm("(U) F' U F R U' R' U R U2 R2 F R F' R U' R'"),
        Algorithm("(U2) R U' R' U' F' U2 F M' U R U' r'"),
        Algorithm("(U2) R2 U' R' U R U R' U' F' U F U' R U R2"),
        Algorithm("(U2) F R' F' R U R U' R2 U' F' U F R"),
        Algorithm("(U2) R' U R U' R2 U' F' U F R U R U R' U' R"),
        Algorithm("(U2) R U R' U2 F U R U' R' F' R U R' M' U R U' r'"),
        Algorithm("F R U R2 U' R F' U' R' U2 R"),
        Algorithm("(U) R' F' U' R U R' U' R' F R2 U' R' U R"),
        Algorithm("(U) R U R' U R U2 R' U F R U' R' U' R U R' F'"),
        Algorithm("(U2) R U R' F' R U R' U' R' U' F U R2 U2 R'"),
        Algorithm("(U) R' D' y' R U' R' U R' D y R F' U F"),
        Algorithm("R' F R U' R' U2 R U R2 F' R U R"),
        Algorithm("(U2) F D R' U R U' R D' F' R U' R'"),
        Algorithm("(U2) R U2 R' U' F' U F R U' R' U' R' U' F' U F R"),
        Algorithm("(U) R U R' U R' U' F' U F R2 U R' U' R U' R'"),
        Algorithm("F' r U' r' F2 U2 R' F R2 U R' U' F'"),
        Algorithm("(U) R' U2 R' D' R U R' D F R F' U R"),
        Algorithm("(U2) r U r' F R U R' U' F2 U F U' r U' r'"),
        Algorithm("(U') F' U' F U R U R' U2 R U2 R' U2 F' U' F"),
        Algorithm("(U2) F U R U' R2 F R F r U' R' U' R U2 r' F"),
        Algorithm("(U') R' D R' U' R U D' R U' F R2 U R' U' F'"),
        Algorithm("(U') R' U' F U R U' R' F' R F R' F' R U R U' R'"),
        Algorithm("F R U R' U' F' U' r' F R F' r U R'"),
        Algorithm("F U R' U' F' U F R2 U' R' U' R U R' F'"),
        Algorithm("(U') R U R' F' R U R' U' R' F R F' r' F' r F"),
        Algorithm("F U R U' R' U F' R' F R U' R' F' R"),
        Algorithm("F' U' r' F r U' F r U' r' U r U r'"),
        Algorithm("(U) R2 D' r U r' D R2 y R U' R'"),
        Algorithm("(U) R2 D r' U' r D' R2 y' R' U R"),
        Algorithm("(U2) R' F U R U R2 F' R2 U' R' U' R U' F U F'"),
        Algorithm("(U2) r U r' U R U' M' U' r' R' U2 R U R' U R"),
        Algorithm("(U') F' L' U' L U L' U' L U F"),
        Algorithm("(U) r' U2 R U R' U r U2 r U R' U R U2 r'"),
        Algorithm("(U2) r U R' U R U2 r' U R U R' U R U2 R'"),
        Algorithm("r' U2 R U R' U r U' R' U2 R U R' U R"),
        Algorithm("R U2 R' U2 R U' R' U2 r U' R' U2 R U r'"),
        Algorithm("(U') R' U' R' F R F' R' F R F' U R"),
        Algorithm("F R U' R' U2 R U R' F' R' F' U' F U R"),
        Algorithm("(U) R U2 R' U' R U' R' U' r U r' R U R' U' r U' r'"),
        Algorithm("(U) R' U2 R U R' U R U2 r U R' U R U2 r'"),
        Algorithm("R' U' R U' R' U2 r' R' U2 R' U' R U' R' U' M'"),
        Algorithm("r' U2 R U R' U r R U R' U R U2 R'"),
        Algorithm("(U') R U R' U R U' R' U R U2 R' F R U R' U' F'"),
        Algorithm("(U2) r U R U' r' F R' U R U' F' r U R' U' r'"),
        Algorithm("R U R' F' U2 F U R U' R' U R U2 R'"),
        Algorithm("R' U2 R U R' U' R U R' U R U F U R U' R' F'"),
        Algorithm("(U') R' U' F' U F R U' r U R' U R U2 r'"),
        Algorithm("(U') R' U' R U' R' U2 R U2 R' F' U' F U R"),
        Algorithm("(U') F R U' R' F' r' F r U' R U R' U R U2 R'"),
        Algorithm("(U2) F U R U' R' F' R U R' U R U2 R'"),
        Algorithm("(U2) R' U' R' F R F' U R r U R' U R U2 r'"),
        Algorithm("(U2) R' U' F' U F R U' R U2 R' U' R U R' U' R U' R'"),
        Algorithm("(U) R' F' U' F U R U r U R' U R U2 r'"),
        Algorithm("(U') R' U' R U' R' U2 R U F R U R' U' F'"),
        Algorithm("(U2) R U2 R' U2 R' F R2 U' R' U R U2 R' U' F'"),
        Algorithm("(U') R U2 R' U2 R' F R F' R' U' R U' R' U2 R"),
        Algorithm("F U R U' R' U R U' R' F' U' R' F R U R' U' F' U R"),
        Algorithm("(U) R' U' R U' R' U2 F R U R' U' F' R U' R' U2 R"),
        Algorithm("(U2) R U2 R2 U' R2 U' R2 U2 R U F R U' R' U' R U R' F'"),
        Algorithm("R' U2 R U R' U R r U' r' U' r U r' F' U F"),
        Algorithm("(U2) F' r U R' U2 r' F r U' r' F2 R"),
        Algorithm("(U') R U2 R' U2 R' F R F' U R U2 R' U' R U' R'"),
        Algorithm("(U2) R U R2 F' U' F U R U' R U R' U' R U' R'"),
        Algorithm("R U2 R2 F R U2 F' U' R F U' F' U2 R'"),
        Algorithm("(U') B' U' R' U2 R U R' U' R y R U R' F' U' F U R"),
        Algorithm("(U') R U R' U' R' F R F' U R U2 R2 F R F' R U2 R'"),
        Algorithm("(U2) R U R' U' R U R' F' U' F U' R U2 R'"),
        Algorithm("(U2) F U R U2 R' U R U R2 F' R U2 R U2 R'"),
        Algorithm("(U2) F R' F' R U2 R U' R' U R U2 R'"),
        Algorithm("(U2) F R' F' R U2 R U2 R' U' R' U2 R U R' U R"),
        Algorithm("F R U' R' U R U2 R' U' R U R2 U' F' U F R F'"),
        Algorithm("(U') R' F2 r U r' F' r U2 R U' r' F"),
        Algorithm("(U) F' U' F R U R' F R U R' U' F' U F' U F"),
        Algorithm("(U) M U F R U R' U' F' R' F R F' r U R'"),
        Algorithm("(U') R U2 R D r' U2 r D' R F' U' F U R"),
        Algorithm("(U) r' U' R U' R' U2 r U' r' F R F' r U R'"),
        Algorithm("(U) r' U r U' F' r U r' U' r' F U' r U R' U2 R"),
        Algorithm("(U2) F R U R2 U' R' F' U' R' U R U F R F'"),
        Algorithm("B' R' U R U R' U2 R U R' U' R U f z'"),
        Algorithm("(U2) F U R U2 R' U R U R' F' r U R' U R U2 r'"),
        Algorithm("(U') R2 U' R2 U R U R' U' R U R' U2 F R F' U2 R'"),
        Algorithm("(U') r U2 R' U' R U' r' U r U R' U' r' F R F'"),
        Algorithm("(U2) F R U' R' U' R U R' F' R U2 R2 U' R2 U' R2 U2 R"),
        Algorithm("(U) F' U2 F U' R U R' U R U R' F' U F"),
        Algorithm("(U2) R' F R U R' U' F' R' F R F' U R"),
        Algorithm("(U') R U2 R' U' R U R' F R U R' U' F' U R U R'"),
        Algorithm("(U2) F R U R' U' F' r U R' U' r' F R2 U R' U' F'"),
        Algorithm("(U) F R U R' F' U' F' r U r' F R U R' U' F'"),
        Algorithm("(U) F R U2 R2 U' F' U F R U2 R U R' U' F'"),
        Algorithm("(U') R2 D r' U2 r D' R2 F2 r U r' F"),
        Algorithm("(U) R U R' U R' F R F' R U' R D R' U' R D' R2"),
        Algorithm("(U) F U2 R U' R' F R U R' U' F' U y' R' U' R U' R'"),
        Algorithm("(U2) R U R' U' R' F R2 U R' U' F' R U2 R' U' R U' R'"),
        Algorithm("R' U' R U R' U' R U2 R' U' F' U' F U' R"),
        Algorithm("(U2) R U2 R' U2 R' F R F' r U2 R' U' R U' r'"),
        Algorithm("(U') F R U' R' U R U2 R' U' F' U r U R' U' r' F R F'"),
        Algorithm("(U') R' F R F' U M U R U' R' U' r U R'"),
        Algorithm("r U R' U' r' F R F' U2 r U R' U R U2 r'"),
        Algorithm("(U) F R' F' R U2 R U' R' U F' U F U' R U2 R'"),
        Algorithm("(U) R U R' U' R U F U2 F' U' R2 F R U' F'"),
        Algorithm("R U2 R' U R' U2 R U R' U F R F' U2 R U' R'"),
        Algorithm("R' U2 R U R' U R F U R U2 R' U' R U R' F'"),
        Algorithm("(U') r U2 R' U' R U' r' U R U2 R' U' R U' R'"),
        Algorithm("(U2) r' U' F U r F U' R U R' U' F'"),
        Algorithm("(U2) r U R' U' r' U2 R U R' U R2 U2 R'"),
        Algorithm("(U) R U2 R2 F R F' R' F R F' R U2 R'"),
        Algorithm("(U) R' U' R U' R' U2 R r U r' R U R' U' r U' r'"),
        Algorithm("(U2) r U R' U R U2 r' U' R U R' U R U2 R'"),
        Algorithm("(U2) r U2 R' U' R U' r' U2 r' U' R U' R' U2 r"),
        Algorithm("(U2) F R U R' U' R U R' U' F'"),
        Algorithm("(U2) r U R' U R U2 r' U2 R' U2 R U R' U R"),
        Algorithm("(U) M U R U R' U R U2 R2 F2 r U r' F r"),
        Algorithm("(U) R U' R' U R U R' U2 R' F R F2 U F R U R'"),
        Algorithm("(U') r U2 R' U' R U' r' R' U' R U' R' U2 R"),
        Algorithm("(U) F R U R' F R' F' R U' R U R' U' F'"),
        Algorithm("(U2) F U R U' R' F' R U2 R' U' R U R' U' R U' R'"),
        Algorithm("(U') R U2 R' U' R U R' U' R U' R2 U' F' U F R"),
        Algorithm("(U) R U2 R' U' R U R' U' F' U2 F R U' R'"),
        Algorithm("(U) R U R' U R' F R F' R U' R' U R U2 R'"),
        Algorithm("(U') r' U' M' U' R U r' U' R U R' F' U F r"),
        Algorithm("R U R' U R U2 R' U' F R U R' U' F'"),
        Algorithm("(U) F U R U' R' F' r' U' R U' R' U2 r"),
        Algorithm("(U) R U2 R' U' R U' R' U2 R' U' R' F R F' U R"),
        Algorithm("R' U' R U' R' U R U' R' U2 R F R U R' U' F'"),
        Algorithm("R U R' U R U2 R2 F' U' F U R"),
        Algorithm("(U') F R U R' U' F' U2 r' U' R U' R' U2 r"),
        Algorithm("(U) R U R' F R' F' R U R U' R' U F' U F"),
        Algorithm("(U) F U R U' R' U2 R U' R' F R U R' U' F' U' F'"),
        Algorithm("(U2) R' U' F U R U' R' F' R U F R U R' U' R U R' U' F'"),
        Algorithm("R U R' U R' U' F' U F R F' U F R U' R'"),
        Algorithm("(U') F R' F' R U2 R U2 R' r U R' U R U2 r'"),
        Algorithm("(U') F R U' R' F' U' F R' F2 r U r' F R F'"),
        Algorithm("(U2) R' U2 R U R' U' R U R' F U R U' R' F' R"),
        Algorithm("(U') R2 U R' U R' U2 R' F R F' R U R U' R2"),
        Algorithm("(U2) R' U' F' U F R U r' F R F' r U R'"),
        Algorithm("F U R U2 R' U' R U R' F' U' F R U R' U' F'"),
        Algorithm("(U2) R U2 R2 U' F' U' F U R U2 R' U' R U R U' R'"),
        Algorithm("R' F R2 U R' U' F' U' R U' R2 F R F' R U2 R'"),
        Algorithm("(U2) F U R' F R F2 R' F R U' R' F' R"),
        Algorithm("(U') R U2 R' U' F' U' R U2 R' U2 R' F R2 U' R'"),
        Algorithm("(U2) R U2 R' U' R U R' U2 R' F R F'"),
        Algorithm("(U2) r U2 R' U' R U R' U2 r' F R F'"),
        Algorithm("(U2) F R U' R' U R U2 R2 U' R2 U' R2 U2 R2 U R' F'"),
        Algorithm("(U2) R' F R F' U2 F' U2 F R U2 R' U' R U' R'"),
        Algorithm("(U2) r U R' U' r' F R2 U R' U' R U R' U' F'"),
        Algorithm("(U) r R' U R U2 R' U' R U r' U' F' U' F R U' R'"),
        Algorithm("R' U' F' U2 F U' R2 D r' U' r D' R'"),
        Algorithm("(U2) R U R' U' R' F R F' f R U R' U' R U R' U' f'"),
        Algorithm("R U2 R' U2 R' F R F' r' U' R U' R' U2 r"),
        Algorithm("(U') R U R' U2 R' D' R U R' D R2 U' R' R' F R F'"),
        Algorithm("(U') F U R U2 R' U' R U R' F' r U R' U R U2 r'"),
        Algorithm("(U2) R' F R' F' R2 U' r' U F' U' F r"),
        Algorithm("(U') r U R' U R U2 r' F U F' R' F R U' R' F' R"),
        Algorithm("(U) R U R' F' R U2 R' U2 R' U' F U R U' R U' R'"),
        Algorithm("(U2) F R U R' U' R2 D R' U R D' R2 U' F'"),
        Algorithm("(U') R' U' F U R U' R' F' R U' R' U' R U' R' U2 R"),
        Algorithm("(U') R U R' U' R U2 R' F' U' F U R U R2 F R F'"),
        Algorithm("(U') R U R' U2 F' U F R U' R2 F R F'"),
        Algorithm("r' U2 R U R' U r U' r U R' U' r' F R F'"),
        Algorithm("R U R' U' F' U' F U' R2 U R' U R' U' R2 U' R2"),
        Algorithm("(U') F R U' R' U R U R' F' U2 r U r' R U R' U' r U' r'"),
        Algorithm("(U') R U2 R' U2 R' F R F' R U2 R' U' R U' R'"),
        Algorithm("(U') F R U' R' U R U2 R' U' F' R U2 R' U' R U' R'"),
        Algorithm("(U') F R U' R' U' R U2 R' U' R U R' U' F'"),
        Algorithm("(U') F R U R' U' F' R U2 R' U2 R' F R F'"),
        Algorithm("(U') R U2 R' U F' U' F U2 R' F R F'"),
        Algorithm("(U2) F R' F' U2 R U R' U R2 U2 R'"),
        Algorithm("R U2 R' U2 R' F R F' U2 R U2 R' U2 R' F R F'"),
        Algorithm("(U) R' F R U R' U' F' U R F R U R' U' R U R' U' F'"),
        Algorithm("(U') f R U R' U' f' R U2 R' U2 R' F R F'"),
        Algorithm("R U R' U R' U2 R' U R' U' R U2 F R F'"),
        Algorithm("(U') F R U' R' U' R U2 R' U' F' U' r' U' F' U F r"),
        Algorithm("(U') R' F' U' F U2 R U2 R' U' F' U F U R"),
        Algorithm("(U2) R U2 R' U R' U' F' U R U2 R U' R' U' R' F R"),
        Algorithm("(U') r U' r2 U r2 U r2 U' r"),
        Algorithm("r' R2 U R' U R U2 R' U M' R U R' U R U2 R'"),
        Algorithm("(U') F R U R' U' R U' R' F' U' r' F2 r"),
        Algorithm("(U) R' U' R' F R F' U R U' R' F' U' F U R"),
        Algorithm("R' F' U' F U R U R' U' R' F R F' U R"),
        Algorithm("(U) F U R U' R2 F' R U F' U F R U' R'"),
        Algorithm("(U') r U2 R' U' R U' r' U' R U2 R' U' R U' R'"),
        Algorithm("R U2 R' F R' F' R F R' F' R2 U2 R'"),
        Algorithm("(U) R' U' R' F R F' U R U2 F R U R' U' F'"),
        Algorithm("(U') R U R' U R U2 R2 F2 r U r' F R"),
        Algorithm("(U') R' U' R F U' R U R2 U R2 U' R' U F'"),
        Algorithm("R U2 R' U' R U' R' r' U' R U' R' U2 r"),
        Algorithm("(U2) r' F2 r R U2 R' U' R U' R' U' F R U R' F'"),
        Algorithm("(U) R U R' U R U2 R' U' R' U2 R U R' F' U F R"),
        Algorithm("(U) R' U' R U' R' U2 R U' R' U' R' F R F' U R"),
        Algorithm("(U) R U R' U R U2 R' U2 R' U' F' U F R"),
        Algorithm("R U2 R2 F R F' R' U' R2 U' R2 U2 R"),
        Algorithm("R' U2 R U R' U R U R' F' U' F U R"),
        Algorithm("(U2) r U2 R' U' R U' r' U R U R' F' U2 F R U' R'"),
        Algorithm("f R U R' U' f' U' R U2 R' U' R U' R'"),
        Algorithm("(U) r U r' U R U' R' U R' F R F' U' r U' r'"),
        Algorithm("R' U2 R U R' U R F R U R' U' F'"),
        Algorithm("(U2) r U2 R' U' R U' r' U' R' U' F' U F R"),
        Algorithm("(U) r U R' U R U2 r2 F' U' F U r"),
        Algorithm("(U') F R U' R' U R U2 R' U' F' U2 R' U' R U' R' U2 R"),
        Algorithm("(U') R' U' F' U F R F R U' R' U R U2 R' U' F'"),
        Algorithm("(U') F R U R' U2 F' U' r' F2 r U F U' F'"),
        Algorithm("(U') R' U' R' F R2 U' R' U2 R U R' F r U r' F R"),
        Algorithm("(U2) R U' L' U R' U' L U R' U' F' U F R"),
        Algorithm("(U) R' F' U' F U R U2 F R U' R' U R U2 R' U' F'"),
        Algorithm("(U') R' U R U2 R' U' F' U F U' R U R' U R"),
        Algorithm("(U') F r U' r' U R U2 R' U r U2 r' U' r U' r' F'"),
        Algorithm("(U') F R U' R' F' r U r' U' r' F r F' U' r' F2 r"),
        Algorithm("(U2) r U R2 F R F' R U' r' U' F' U2 F"),
        Algorithm("(U2) R U' r' F R' F r U r' U' F U r"),
        Algorithm("(U') r U r' R U R' U' r U R' U2 r' F R F'"),
        Algorithm("(U') R U' R' F' U r' F2 r U' y' R U' R' U R"),
        Algorithm("(U2) R' F R U R' F' R F2 R' F' R U' F'"),
        Algorithm("(U') F R U' R' U2 R U R' F' U' r' F R F' r U R'"),
        Algorithm("(U2) F R F' U' R' F' U F R2 U2 R' U2 R'"),
        Algorithm("f R U R' U' f' L' U R U' L U R'"),
        Algorithm("R U R' U R U' y R U2 R' U' R U R' F'"),
        Algorithm("(U) F U R U2 R' U' R U R' F' U2 R' U' F' U F R"),
        Algorithm("(U') R U2 R' U R U R' F R' F' R2 U2 R' U R U' R'"),
        Algorithm("R U R' U R U' R' U R' U' F' U F R2 U' R'"),
        Algorithm("(U') R' U2 R U R' U' R U F R2 U' R' U R U R F'"),
        Algorithm("(U2) R' F R F' r U R' U' r' U' F' U F R"),
        Algorithm("(U) R' F2 r U r' U F R2 D r' U' r D' R'"),
        Algorithm("(U) R U2 R' U' R U' R' U R U R' U' R' F R F'"),
        Algorithm("(U') R U2 R' U' R U R' U2 R U' R' F' U' F R U R'"),
        Algorithm("(U') R' F2 r U r' F R U R' U' F U R U' R' F' R"),
        Algorithm("(U) R' U R U2 R' U' R U' R' F' U' F U' R"),
        Algorithm("(U') F U F' R U2 R' U2 R' F R2 U R' F'"),
        Algorithm("(U') F' r U R' U' r2 F r U' F R"),
        Algorithm("R' U' R F U' R' U2 R U2 R U' R' F'"),
        Algorithm("(U2) F U2 R2 U2 R' U2 R' F R F' R' U2 F'"),
        Algorithm("R' F R U R' U' F' U R U' R' F' U' F U R"),
        Algorithm("(U) r' U r' F R F' r U R' U R' F R F' U r"),
        Algorithm("(U) R U R' U' R' F R F' U F R' F' R U R U' R'"),
        Algorithm("R' F R U R' U' F' U R U2 F R U R' U' F'"),
        Algorithm("(U2) F R' F' R U R' F R F' R U' R' F' U F"),
        Algorithm("(U2) R U R' U R U2 R' U2 R U R' U' R' F R F'"),
        Algorithm("(U2) R U' r' U R U R' U' r U l U' R' U l'"),
        Algorithm("(U') r U R' U R2 D R' U' R D' R2 U R U2 r'"),
        Algorithm("R r' U' R U2 R' U' R U' R2 F R F' r U R'"),
        Algorithm("R' U' R U' R' U2 R U2 R' U' F U R U' R' F' R"),
        Algorithm("B' U' R U2 R2 U' R2 U' R' U' y R' F R F' U R"),
        Algorithm("(U') R' F2 R F' r U' r' F r U r' F r' F2 r"),
        Algorithm("(U) R U R' U R U' R2 F R F' R U R' U' F' U2 F"),
        Algorithm("(U) r' U2 R U R2 F R U r U' F' r U r'"),
        Algorithm("(U) r' F' r2 U' r' F U' F' r U r'"),
        Algorithm("F R U' R' U R U R' F' U2 r U2 R' U' R U' r'"),
        Algorithm("F R U R' U2 F R U' R' U R U R' F' U' F'"),
        Algorithm("(U') R' U2 R U R' U F' U' F R' F R F' U R"),
        Algorithm("r' U2 R U R' U r U R' U2 R U R' U R"),
        Algorithm("(U2) R' r U R' U2 R U R' U R2 U R' U R U2 r'"),
        Algorithm("r' U r2 U' r2 U' r2 U r'"),
        Algorithm("r U2 R2 F R F' U' R U' r' F R U R' U' F'"),
        Algorithm("(U2) R' U' R' F R F' U R F U R U' R' F'"),
        Algorithm("(U) R u R' U R' U' R u' R2 U2 R"),
        Algorithm("R' U' R U' R' U2 R U2 r U2 R' U' R U' r'"),
        Algorithm("(U2) F R F' R U R' U' R' F R' F' U' R' U R"),
        Algorithm("F R U R' U' F' U2 R' U' R' F R F' U R"),
        Algorithm("(U') R' U2 R U R' U R r U R' U R U2 r'"),
        Algorithm("(U2) R2 U R U' R' F R' U R2 U' F' R'"),
        Algorithm("(U') F R U' R' F' U R U R' U R U2 R' r' F2 r"),
        Algorithm("(U) R' U2 R U R' U R U2 F U R U' R' F'"),
        Algorithm("(U') R' U2 R U R' F' U F R U R' U2 R U R' U R"),
        Algorithm("(U2) R' U' F' U F R U2 R' U2 R U R' U R"),
        Algorithm("(U) r' U2 R U R' U r U' F R U' R' U2 R U R' F'"),
        Algorithm("(U') R U2 R' U' R U' R' F R U R' U' F'"),
        Algorithm("(U') F' r U R' U' r' F U' F U R U' R' F' R"),
        Algorithm("(U) r' U' R' F R F' U r R U R' U R U2 R'"),
        Algorithm("(U2) R' U' F' U F R U' R U R' U R U2 R'"),
        Algorithm("(U') F R U R' U' F' U r' U2 R U R' U r"),
        Algorithm("(U2) R U R' U R U2 R' U R' U' R' F R F' U R"),
        Algorithm("R U R' U F' R U2 R' U2 R' U' F U R"),
        Algorithm("R' U2 R U R' U R U2 F U R U2 R' U' R U R' F'"),
        Algorithm("(U2) R U R2 U' R' F R F' U F R U R U' R' F'"),
        Algorithm("(U') R' U' R F R' U R U' R' F' R U2 R U2 R'"),
        Algorithm("R U R' F' U r' F2 r U' y' R U R' U R"),
        Algorithm("(U') R' F R U R' F' R F U' R U' R' U2 R U R' F'"),
        Algorithm("(U') r' F R F' r U R' U2 F U R U' R' F'"),
        Algorithm("(U) F R' F' R U2 r U' R' U R U2 R' U' M"),
        Algorithm("(U2) r' U' R U2 R' U' r U r' F' U' F r U r' U r"),
        Algorithm("(U2) F' U2 F U R2 D r' U r D' R2"),
        Algorithm("(U) r' F R F' r U R' U r U2 R' U' R U' r'"),
        Algorithm("(U') r' F R F' r U R' U' F R U' R' U2 R U R' F'"),
        Algorithm("(U') R U2 R' U2 R' F R2 U' R' U' R U2 R' U' F'"),
        Algorithm("(U') R' U' R U R' U y r' F2 r U' F R U R'"),
        Algorithm("(U2) F U R' F R F' R U2 R' U R U R' U R U' R' F'"),
        Algorithm("(U') R' U' R U' R' U F' U2 F R' F R F' U' R"),
        Algorithm("(U') R U2 R' U2 R' F R U R' U' R F' R' U R"),
        Algorithm("(U') R U R' U R U' R' U2 R' F' U' F U R2 U R'"),
        Algorithm("(U2) R' U' F' U F R U' R U' L' U R' U' L"),
        Algorithm("(U) R U' L' U R' U' L U2 r U R' U R U2 r'"),
        Algorithm("(U2) F U R U2 R2 U2 R U R' U R U' R U2 R' U' F'"),
        Algorithm("(U) R' U' F' U2 F U' R U R2 F R F' R"),
        Algorithm("(U) R U R' U' R' F R F' U2 F R U' R' U R U2 R' U' F'"),
        Algorithm("(U) R U R' U R U' R' U R U2 R' U' R U R' U' R' F R F'"),
        Algorithm("(U') R' U2 R U R' U F2 r U2 R U' r' F"),
        Algorithm("F U2 R U R' F R' F' R2 U2 R' U F'"),
        Algorithm("(U) R' U r U' R' U' R U r' U' R' F R F' R"),
        Algorithm("(U') R U R' U F' U F U' R U' R' U' R' F R F'"),
        Algorithm("(U') R U2 R' U2 R' y r U' R' F R' F' R2 U2 r'"),
        Algorithm("r' U' R U' R2 D' R U R' D R2 U' R' U2 r"),
        Algorithm("(U2) R' F R F' r U' R' U' R U' R' U2 M"),
        Algorithm("(U') r U R' U R U r' F U F R U' R' F'"),
        Algorithm("(U2) R' U' R U' R' U R' F R F' y' R' U2 R U R' U' R f z'"),
        Algorithm("R U R2 F R F' U F R' F' R"),
        Algorithm("(U2) R' U R U' R2 F R2 U R' U' F' R"),
        Algorithm("(U') R U R' U' R' F R F' U r' U2 R U R' U r"),
        Algorithm("(U') r' U r' U r2 U r2 U' r F' U' F r"),
        Algorithm("(U') F R U' R' U' R U R' U R U' R' F'"),
        Algorithm("(U') R' U' F U R U' R' F' R U' R' U2 R U R' U R"),
        Algorithm("(U2) F R' F' r U2 F R' F' R2 U2 r'"),
        Algorithm("F' r U R' U' r' F R U2 F U R U' R' F'"),
        Algorithm("(U) R' F R U R' U' F' U R F U R U' R' F'"),
        Algorithm("(U) R' U' R U' R' U2 R U2 R U R' U' R' F R F'"),
        Algorithm("(U2) F R' F' r U R U' r' F U R U' R' F'"),
        Algorithm("(U') r U R' U R U' R' U' r' F' R U2 R U2 R' F"),
        Algorithm("(U2) F R U' R' U R U R' F2 r U r' U' r' F r"),
        Algorithm("R U R2 F R y' R2 U R2 U R' U' R' F R F'"),
        Algorithm("(U') R U R' F' U' F U R U2 R' U' R' F' U' F U R"),
        Algorithm("R' U' R U' R' U2 R U r' U' R U' R' U2 r"),
        Algorithm("(U2) F U R U' R' U R U' R' F'"),
        Algorithm("(U) R U R' U R U2 R' U r U R' U R U2 r'"),
        Algorithm("(U') R' U' R F R' U R2 U2 R' U' R U R' F'"),
        Algorithm("(U2) R U R' U' F' U' F R' F R F' R U R'"),
        Algorithm("(U2) f' L' U' L U L' U' L U f"),
        Algorithm("R U R' U R U2 R' U' r U R' U R U2 r'"),
        Algorithm("F R U R' U2 R' U R U F' R' U2 R"),
        Algorithm("(U') R' U' R F R2 U' R' U R' U' R2 U2 R2 U' R' F'"),
        Algorithm("(U2) R U R' U' R' F R F' U' F R U' R' U' R U2 R' U' F'"),
        Algorithm("(U') R' U' F U R U' R' F r U2 R U' r' F"),
        Algorithm("(U) R U R' U R U2 R' U r U r' U R U' M' U' r'"),
        Algorithm("(U) R' U' R' F R F' U R2 U R' U R U2 R'"),
        Algorithm("(U') R' F' U' F U R2 U R' U R U' R' U R U2 R'"),
        Algorithm("(U') r U2 R' U' R U' r' U2 R' U' R' F R F' U R"),
        Algorithm("(U2) R F U R2 U' R F' R U R' U' R2"),
        Algorithm("R' F R U R' U' F' U F' r U R U' r' F"),
        Algorithm("(U2) r U R' U R U2 r' U R' U' R' F R F' U R"),
        Algorithm("(U) R' U2 R U R' U R U R U R' F' U2 F R U' R'"),
        Algorithm("(U') R U2 R' U' R U' R' U' F R U' R' U2 R U R' F'"),
        Algorithm("(U') R' U' R' F R F' R U' R' U2 R"),
        Algorithm("(U2) F R U R' U' F' R U2 R' U' R U R' U' R U' R'"),
        Algorithm("(U) R' U2 R U R' U R U' R' U' F' U F R"),
        Algorithm("(U') R U2 R' U' R U' R' U2 F U R U' R' F'"),
        Algorithm("(U) R U R' U R U' R' U R' U' F' U F R U' M' U R U' r'"),
        Algorithm("(U) F' U2 F U2 F R' F2 U' F U R"),
        Algorithm("(U2) F R U R' U R2 U R' U R U2 R' U R' U2 F'"),
        Algorithm("(U') R' U2 F' U F U' R U R' U' R U' R' U' R"),
        Algorithm("(U') r' U' R U' R' U R U' R' U r' D' r U r' D r2"),
        Algorithm("(U') L' U R U' L U R' U R' F' U' F U R"),
        Algorithm("(U) R U R' U R U2 R' U r' F2 r U2 r U' r' F"),
        Algorithm("(U') L' U R U' L U R' F R U R' U' F'"),
        Algorithm("(U2) R U R' U2 F' U F R U' R2 F R U R U' R' F'"),
        Algorithm("(U2) F' R U2 R' U' R U R' U2 R' F R2 U' R2 F R F'"),
        Algorithm("(U) R2 D' r U r' D R2 U y R U2 R'"),
        Algorithm("r' U r U' r' R' F R F' R U' R2 F R F' r"),
        Algorithm("R U2 R' U2 R' F R2 U R' U' F'"),
        Algorithm("(U) R' F' U' F U' R U2 F U' R' U R U F'"),
        Algorithm("(U2) R' F R U R' U' F' U R2 U R' U R U' R' U R U2 R'"),
        Algorithm("(U') R U' L' U R' U' L U2 F R U R' U' F'"),
        Algorithm("(U') R' U' R U' R' U2 R U R U2 R' U2 R' F R F'"),
        Algorithm("(U2) R' F R U R' U' F' R U' R' U R U' R' U2 R"),
        Algorithm("(U2) F R U' R' U2 R U R' U F' R' F R U' R' F' R"),
        Algorithm("(U) R U R' U' R U2 R2 F R F' R U' R' U' R U2 R'"),
        Algorithm("(U') R U' L' U R' U' L U' R' F' U' F U R"),
        Algorithm("(U') R2 D r' U' r D' R2 U' F' U2 F"),
        Algorithm("(U') R U R' U R U2 R2 U' F' U' F U R U2 R' U' R"),
        Algorithm("(U) R' U' R U R2 D' R U' R' D R2 U' R' F' U F R"),
        Algorithm("(U2) R U2 R' U' R U' R' U R' U' F U R U' R' F' R"),
        Algorithm("(U2) R' U2 R U R' U R U' R U2 R' U' F' U F R U' R'"),
        Algorithm("(U2) F R U2 R' F U F' R U' R' U2 y' R U2 R' U R'"),
        Algorithm("(U2) F R2 F' R U R' U2 R' U R U' F' U2 F R2"),
        Algorithm("(U2) R' F R F' U R U R' U r U' r' U r U r'"),
        Algorithm("(U') r U2 R' F R' F' R U' R U R' U2 r' F R F'"),
        Algorithm("(U') R U2 R2 F' U' F R F' U F U' R' U R"),
        Algorithm("R' U' R U' R' U2 R U' R U2 R' U2 R' F R F'"),
        Algorithm("R U R' U R U2 R' U' R' F2 r U2 R U' r' F"),
        Algorithm("(U') R U R' U R U' R' F' U F R U R' U' R U' R'"),
        Algorithm("(U') R' U2 R2 U R2 U F2 r U' R U2 r' F"),
        Algorithm("R U R2 F R F' R U' R' F' r' F r F"),
        Algorithm("R U2 R' U r' U' F' U F r U R U' R'"),
        Algorithm("R' U2 R U2 F R U R' U' F' R' U R"),
        Algorithm("(U') r' R2 U R' U R U2 R' U M' U F R U' R' U R U R' F'"),
        Algorithm("F' r U R' U' r' F R U R' F' U' F U R"),
        Algorithm("(U) R U R' U R U' R' F' U F U R U2 R'"),
        Algorithm("F R U R' U R' D' R U2 R' D R F'"),
        Algorithm("(U) R U R' F' U F R U' R' F U R U' R' F'"),
        Algorithm("(U) R' U' R F R U' R2 U2 R2 U R' U R U' R' F'"),
        Algorithm("(U2) R' U' R U R' U2 R U2 R' U R U R' F R' F' R2"),
        Algorithm("F' r U R' U' r' F R F R U R' U' F'"),
        Algorithm("(U2) F R' F' r U R U' r' U' R' F' U' F U R"),
        Algorithm("(U') F R' F' R U2 R U2 R' U R U R' U' R' F R F'"),
        Algorithm("(U') R' U' y' x' R U' R' U R U' R' U F U x"),
        Algorithm("(U') R' U2 R U R' U R U r' U2 R U R' U r"),
        Algorithm("(U') R' U2 R U R' F' U F R U' R' U' F' U F R"),
        Algorithm("(U') R' U2 R2 u R' U R U' R u' R'"),
        Algorithm("F U F R U' R' U' R U R' F' U2 R U' R' F'"),
        Algorithm("(U') R U2 R' U' R U' R' U' r U2 R' U' R U' r'"),
        Algorithm("(U') R U2 R2 U' R U' R' U2 r U R U' r'"),
        Algorithm("(U') R U2 R2 u' R U' R' U R' u R"),
        Algorithm("r U R' U R U2 r2 U' r R' U' R U r' U r"),
        Algorithm("(U2) R' U2 R U R' U F' U2 R U R' U R U2 R' F R"),
        Algorithm("r U r' U2 r U2 r' R U' R' U' R U R' r U r'"),
        Algorithm("(U') R U R' U' R' U' F R2 U' R' U R' U R2 U R' F'"),
        Algorithm("(U') R' F' U' F U R U R U R' U R U2 R'"),
        Algorithm("F U R U' R' U R' F R F' R U' R' F'"),
        Algorithm("(U) r' U' r U' R' U R r' U r U' F U R U' R' F'"),
        Algorithm("(U2) F R U R' U' F' U R' U2 R U R' U R"),
        Algorithm("(U') F R U' R' F' r' F r U' r' U' R U' R' U2 r"),
        Algorithm("(U') R U R' F' U2 F R U' R' U' r U R' U R U2 r'"),
        Algorithm("(U) R U R' U R' F R F r U r' F"),
        Algorithm("(U2) r U2 R' U' R U' r' U R' F' U' F U R"),
        Algorithm("(U) R U R' U R U' y R U' R' F'"),
        Algorithm("(U2) r U2 R' U' R U' r' F R U R' U' F'"),
        Algorithm("(U) R' F' U' F U R U R' U' R U' R' U2 R"),
        Algorithm("(U2) F R U R' U' F' U2 R U R' U R U2 R'"),
        Algorithm("(U') R' U' F' U F2 R F' U2 F' U2 F"),
        Algorithm("(U2) R U2 R' U2 R' F R2 U' R' U' F' U' r' F2 r"),
        Algorithm("R' F' R U R' F' U' R' F R U F' r U2 r' F R"),
        Algorithm("F' U' r' F r U' r' F r2 U R' U' r' F R"),
        Algorithm("(U) R U2 R U2 R2 F' U' F R U x U R' U' x'"),
        Algorithm("(U2) F R U R' U' F' U2 R U' L' U R' U' L"),
        Algorithm("(U2) R U' L' U R' U' L R' U' R' F R F' U R"),
        Algorithm("(U') R U2 R' U2 R' F R F' U2 R' U' R' F R F' U R"),
        Algorithm("R' F' R U' R' U' F U R U' R' F r U2 r' F R"),
        Algorithm("f R U R' U' f' U' F R U' R' U R U2 R' U' F'"),
        Algorithm("(U') R' F' U' F U R U R U' L' U R' U' L"),
        Algorithm("R' F R F' U' F R' F' R U' R' F R F'"),
        Algorithm("R' F' R U R' U' R' F R2 U' R' U F' U F R"),
        Algorithm("F U R U' R2 F' R U2 R U2 R'"),
        Algorithm("r U2 r' U2 R U' R' U' F' U' r U' r' F2 r U r'"),
        Algorithm("(U) R' F' U' F U R U' r' F R F' r U R'"),
        Algorithm("(U2) r' F R F' r U' R' U' F' U2 F R U' R'"),
        Algorithm("F U R U' R' U R U' R2 F' r U R U' r'"),
        Algorithm("(U') R U' R2 U' F' U F R U2 R U R' U' R U' R'"),
        Algorithm("(U') F r U r' U r U2 r' U' R U2 R' U' r U r' F'"),
        Algorithm("(U') R D r' U r D' R2 U F' U2 F U R"),
        Algorithm("F R U R' U' F' L' U R U' L U R'"),
        Algorithm("(U') R' U2 r U R' U' r' R2 U R' F U R U' R' F' R"),
        Algorithm("(U') F R' F' R U R' F R F' R U R' F' U F"),
        Algorithm("R U R' U' R' F R F' U R' U' R U' R' U2 R"),
        Algorithm("(U2) F R U' R' U R U R' F' U2 R U R' U R U2 R'"),
        Algorithm("F R U' R' U' R U2 R' U' F' U' R' U' F' U F R"),
        Algorithm("R U R' F' U' F U R' U' R2 U' R2 U2 R"),
        Algorithm("R U2 R2 F R F' U2 R' F R2 U R' U' F'"),
        Algorithm("(U) r U2 R' U' R U' r' U R U R' U' R' F R F'"),
        Algorithm("R U R' U' R' F R F' U2 R U2 R' U' R U' R'"),
        Algorithm("R' U' R U' R' U F' U' F2 U R U' R' F' U2 R"),
        Algorithm("F U R U2 R' U' R' U2 R U R' U R2 U R' F'"),
        Algorithm("(U2) F' R U2 R' U2 R' F R2 U' R' F' U' F R U R'"),
        Algorithm("(U2) F R' F' R F R' F' R U2 R U' R' F' U' F"),
        Algorithm("R F R U R' U' F' U R' U R U' R' U2 R U' R'"),
        Algorithm("(U2) F' U' F r U' r' U r U' R' U' R U' r'"),
        Algorithm("(U2) F U F' R' F R U' R' F r U r' F R"),
        Algorithm("(U2) R U R' U' R' F R F' U2 R U R' U R U2 R'"),
        Algorithm("(U') R' U' F' U2 F R' F R F' U2 R U' R' U2 R"),
        Algorithm("r' U' R U' R' U2 F' r U r U' r' F"),
        Algorithm("F U R U2 R' U' R U R' F' R U R' U R U2 R'"),
        Algorithm("(U2) r U R' U R U2 r' U2 R U R' U' R' F R F'"),
        Algorithm("F R U' R' U R U R' F' U2 R U2 R' U' R U' R'"),
        Algorithm("(U2) R U R' U' R' F R F' U R' U2 R U R' U R"),
        Algorithm("(U') R U' r' F2 R U' R' U' R U2 R' F' R' F' r"),
        Algorithm("(U2) R U' R' F' U' F U2 R U R' U' R U R'"),
        Algorithm("R' F R2 U R' U r U r' U2 F2 U2 F"),
        Algorithm("(U) r' U' r R' U' R U R' U' R U r' U r"),
        Algorithm("(U) r' U2 R U R' U' R U R' U r"),
        Algorithm("(U2) r U R' U R U2 r' U' R' U2 R U R' U R"),
        Algorithm("(U') r U' R' U R U' R' U' R U2 R' U2 R U r'"),
        Algorithm("r' U' R U' R' U R U' R' U2 r"),
        Algorithm("R' U' R U' R' U2 R r' U' r U' R' U M U r"),
        Algorithm("(U2) M' U' R' U2 R U R' U' R U R' U R M"),
        Algorithm("(U') R U' R' U' F' U R U R2 U' R' F R U R"),
        Algorithm("(U2) r U R' U R U2 r' R U R' U R U2 R'"),
        Algorithm("(U2) R' r U r' U r U r' U' r U' r' U' R"),
        Algorithm("r' R2 U R' U R U2 R' U M' U' R U R' U R U2 R'"),
        Algorithm("(U') F U R U' R2 F R F r U r' U r' F r"),
        Algorithm("R' U2 F R U R' U' F' R U' R' F' U' F U' R"),
        Algorithm("(U2) R U R U' R' F U R U' R F' R' U R U' R' U R"),
        Algorithm("(U2) R2 D' R U' R' D R2 y r U' r' U r U r'"),
        Algorithm("(U') r U R' U R U2 r' U2 R U2 R2 F R F' R U2 R'"),
        Algorithm("R U R' F' U' F R U R' U2 R' F R2 U R' U' F'"),
        Algorithm("(U) R' U2 R2 U R2 U R2 U2 R' F U R U' R' F'"),
        Algorithm("(U') R U R' U' R' F R F' U' F R U' R' U' R U R' F'"),
        Algorithm("(U2) R' U2 R U R' U F' U F R U R2 F R F' R"),
        Algorithm("(U') F R U R' U' R U R' U' R U' R' F' U' r' F2 r"),
        Algorithm("(U) R U2 R2 U' R2 U' R2 U R' F R F' U R"),
        Algorithm("(U') R U R' U R U2 R' U2 R U2 R2 F R F' R U2 R'"),
        Algorithm("r' F R U F R U' R' F' U' R' F R F' r U R'"),
        Algorithm("(U2) F R U R' U' R U' R' U R U R' F'"),
        Algorithm("(U2) R U R' U R U2 R' F U R U2 R' U' R U R' F'"),
        Algorithm("R' U' R U R U2 R' U2 R' U2 F R F'"),
        Algorithm("(U2) F R U' R2 F' R U2 R U2 R' F U' F'"),
        Algorithm("(U) R' U F' U F R U R' U R U2 R' U' R"),
        Algorithm("(U) R U R' U R U2 R' U R U R' F' U F R U' R'"),
        Algorithm("f R U R' U' f' r U R' U' r' F R F'"),
        Algorithm("R U' R' U' F U R U' R' F' R U' R' U R U2 R'"),
        Algorithm("(U2) R2 F R F' R U' R' U' R U2 R' U2 R U' R' U R"),
        Algorithm("(U2) R' U2 R U R' F U R U' R' F r U r' F R"),
        Algorithm("(U') R' F R F' U' F R' F2 r U R U' r' F R U' R'"),
        Algorithm("(U') R' U' F' U F R U R U2 R' U' F' U F R U' R'"),
        Algorithm("(U2) F U R U' R' U R U2 R' U R U R' F'"),
        Algorithm("r' F' U F r' U r2 U' r2 U' r U' r"),
        Algorithm("(U') R' U' R U' R' U2 R U R' F R U R' U' F' U R"),
        Algorithm("(U') r D' R U2 R' U2 R U' R' U' R U R' D r'"),
        Algorithm("(U2) r' F R F' r U' R' U2 R' F R F'"),
        Algorithm("(U2) F R U R' U' F' R U R' U' R' F R F'"),
        Algorithm("(U') F R' F' R U R U' R' U' r U R' U R U2 r'"),
        Algorithm("(U2) R U R' U' R' F R2 U R' U F' U' F U' F'"),
        Algorithm("(U2) F R U2 R' U' R' U2 R U R' U R2 U R' U' F'"),
        Algorithm("(U2) F U R U' R' F' R' F' r U R U' r' F"),
        Algorithm("(U') R U R' U' R' F R F' U' F R' F' R U R U' R'"),
        Algorithm("(U2) R' F2 r U2 R U' r' F R U R' U R U2 R'"),
        Algorithm("(U) R U R' F' U' F R U R2 F R F' R U2 R'"),
        Algorithm("r' R U' R' F R' F' R2 U' R' U' r U' r' U' r"),
        Algorithm("(U2) R' F2 r U r' R U R' U' R' F R2 U' R' U2 R"),
        Algorithm("F' r U r' U' r2 F r U2 F U r"),
        Algorithm("(U2) F' r U R' U2 r' F r U' r U' r' F r' F2 R"),
        Algorithm("(U2) R U2 R' U2 R' F R F' R U2 R' U2 R' F R F'"),
        Algorithm("(U2) R' U2 R U R' U R U R' F R U R' U' F' U R"),
        Algorithm("(U2) F R' F' R U2 R U2 R' U R' U2 R U R' U R"),
        Algorithm("R U2 R' F R F' r U R2 U R U R' U' R U r'"),
        Algorithm("(U') R' F R F' U2 x' R2 U' R' U l'"),
        Algorithm("(U) R U' R' U R U' R' U2 F' U F R U R'"),
        Algorithm("(U') F R U' R' U R U2 R' U' F' R' U' R U' R' U2 R"),
        Algorithm("R U2 R' U' R U' R' F R U R2 U' F' U F R F'"),
        Algorithm("(U') F' U' F R U R' F R' F' R U' R' F R F'"),
        Algorithm("(U2) r U' r' U' r U r' F' U F R' F2 r U r' F R"),
        Algorithm("(U) r U' r' U' r U r' U' R U' R' U' F R' F' R"),
        Algorithm("(U) R' U2 R U R' U2 F R' F' R F' U2 F U R"),
        Algorithm("(U2) r U2 r' F2 r U r' F r U' r' F R' F' R"),
        Algorithm("(U2) R' U R U2 R U2 R' U' R U R' U2 R' U2 F R F'"),
        Algorithm("(U) R U R' U R U2 R' U2 F R U' R' U' R U R' F'"),
        Algorithm("(U2) R U' L' U R' U' L U' r' U2 R U R' U r"),
        Algorithm("(U') r U r' R U R' U' r U' r' F R U' R' U R U2 R' U' F'"),
        Algorithm("(U2) R' U2 R U R' F U F' R U F U' R U' R' F'"),
        Algorithm("(U) r U R' U R U2 r' U2 F R U' R' U' R U R' F'"),
        Algorithm("(U) M U R U2 R' U' R U R' U' R U' R' M'"),
        Algorithm("(U') R U R' U R U2 R' r U r' U R U' R' r U' r'"),
        Algorithm("(U') r U R' U R U' R' U R U2 r'"),
        Algorithm("(U') F R2 D R' U R D' R' U2 R' U R U2 R' U' F'"),
        Algorithm("r' U2 R U R' U r U R U R' U R U2 R'"),
        Algorithm("(U2) r U2 R' U' R U R' U' R U' r'"),
        Algorithm("(U2) r U r' R U R' U' R U R' U' r U' r'"),
        Algorithm("r' U R U' R' U R U R' U2 R U2 R' U' r"),
        Algorithm("(U') M' U' R U' r' U' R U R' U r U r'"),
        Algorithm("(U') R U R' U R U2 R' r U R' U R U2 r'"),
        Algorithm("(U2) r' F r R U R' U R U2 R2 F r U r' F' R"),
        Algorithm("(U2) R' U2 R U F R' U R U' R U' R' U R U R' F'"),
        Algorithm("r' U' R U' R' U2 r U' R U2 R2 F R F' R U2 R'"),
        Algorithm("R U2 R2 F R F' R U2 R' U' R U R' U R U2 R'"),
        Algorithm("(U') R' U' R U R' U' R F R' U R' U' F' R U R' U' R'"),
        Algorithm("f R U R' U' R U R' U' f' F R U R' U' F'"),
        Algorithm("(U2) R U2 R2 U' R2 U' R2 U2 R U R' U' F' U F R"),
        Algorithm("(U) R U R' U R' F R F' R U2 R2 U2 R U R' U R"),
        Algorithm("(U2) R' F R U R U2 R' U' R U R' F r U r' F"),
        Algorithm("(U') R' F' U' F U R U' F R U R' U' R U R' U' F'"),
        Algorithm("f R U R' U' f' R U2 R2 U' R2 U' R2 U2 R"),
        Algorithm("R U2 R2 F R F' R U2 R' U2 R' U2 R U R' U R"),
        Algorithm("(U2) R' U2 R U R' F' U F R F R U R' U' R U R' U' F'"),
        Algorithm("R' U' R U' R' U2 R U' R U2 R2 F R F' R U2 R'"),
        Algorithm("(U') R U2 R2 F R F' R U' R' U' R' F R2 U R' U' F'"),
        Algorithm("(U2) R' U' R U' R U R' F' U' R' U2 R U' F R U' R'"),
        Algorithm("(U) R' U' R' F R F' U R U2 R U R' U' R' F R F'"),
        Algorithm("(U') R U2 R' U' F' U' F R U R' U' R U' R'"),
        Algorithm("(U) F R U' R' U' R U R' F' U r' U' R U' R' U2 r"),
        Algorithm("(U') R U2 R2 U' R2 U' R2 U2 R2 U R' U' R' F R F'"),
        Algorithm("(U) r U' r' U' r U r' U2 R U R' U2 F R' F' R"),
        Algorithm("(U') R' U' R' F R F' R' F R F' R F R' U R U' F'"),
        Algorithm("(U2) F' R U2 R' U2 R' F r U R U R' U' R U' r'"),
        Algorithm("F R U' R' U R U R' F' U F R U' R' U' R U R' F'"),
        Algorithm("(U2) R' U' F' U F R U r U R' U' r' F R F'"),
        Algorithm("(U') R U2 R' U2 R' F R F' U2 R' U' R U' R' U2 R"),
        Algorithm("r' U' R U' R' U R' F R F' U F R F' r U R'"),
        Algorithm("(U2) R' F' U' F U R U' R U R' U' R' F R F'"),
        Algorithm("(U') R U R' U R U2 R2 F2 r U2 R U' r' F"),
        Algorithm("(U2) R' U' R U' R' U2 R U' F R U' R' U' R U R' F'"),
        Algorithm("F R U' R' U2 R U R' U F' U' F' r U r'"),
        Algorithm("(U2) F R' F' R U R U' R' U2 R' U2 R U R' U R"),
        Algorithm("(U') F R U R' U' F' R' U' F U R U' R' F' R"),
        Algorithm("(U') F R U R' U' R U' R' U F' r' U' F U r"),
        Algorithm("(U') R U R' U' R' F R F' U' F R U R' U' R U R' U' F'"),
        Algorithm("(U2) R' U' F' U F R U' F U R U2 R' U R U R' F'"),
        Algorithm("(U2) F' U F R U R' U2 R' F R F' R' F R F'"),
        Algorithm("(U) F U R U' R' F' U2 R' U' F U R U' R' F' R"),
        Algorithm("(U') M' U R U R2 F R F' R U r' U r U r'"),
        Algorithm("(U2) F R U' R' U' R U R' F' U2 R' U2 R U R' U R"),
        Algorithm("(U') R' F R U R' U' F' U R U' R U2 R' U2 R' F R F'"),
        Algorithm("(U) R2 F R F' U F U R U' R' F' U R U' R' U R"),
        Algorithm("(U) R U2 R' U' R U' R' U' R U R' F' U' F U R U2 R'"),
        Algorithm("(U) F R' F' R U R U' R' U2 r U2 R' U' R U' r'"),
        Algorithm("(U') F R' F' r U2 R U' R' U R' F R F' R U2 r'"),
        Algorithm("F R U' R' U R U2 R2 F R F' U y' R' U' R U' R'"),
        Algorithm("(U) F R U' R' U' R U R' F' U' R U2 R' U2 R' F R F'"),
        Algorithm("(U2) R' U R U' R' U R y U2 R U' R' F' U' F"),
        Algorithm("(U) R' F' U F U' R U R2 F R F' R"),
        Algorithm("(U2) R U R' U R U2 R2 F R U R' U' F' U R"),
        Algorithm("(U2) F U' R U2 R2 F R F' R U' R' U2 F'"),
        Algorithm("(U2) r U2 R' U' R U' r' F R U' R' U R U2 R' U' F'"),
        Algorithm("(U2) R U2 R' U' R2 D R' U R D' R2 U2 M' U R U' r'"),
        Algorithm("(U) M' U R U' r' U' R2 D r' U' r D' R' U2 R'"),
        Algorithm("(U2) F R U R' U' F' R U2 R' U2 R' F R2 U R' U' F'"),
        Algorithm("(U') F R U' R' r' F R F' r U' R' U' F'"),
        Algorithm("(U2) R U2 R' U' R U' R' F R U' R' U R U2 R' U' F'"),
        Algorithm("(U') R' F R F' r U R' U' R U2 R' U' R U' r'"),
        Algorithm("(U2) R' U' R U' R' U2 R U2 R U R' F' U F R U' R'"),
        Algorithm("(U) R' F R U' R' U' R U R' F r U r' U2 F R"),
        Algorithm("(U') R U R' U R U R' U' F' U2 F U2 R U2 R'"),
        Algorithm("(U2) r' U' R U' R' U2 r U' F R' F' R U R U' R'"),
        Algorithm("(U') F R U' R' U2 F R U R' U' F' R U2 R' U' F'"),
        Algorithm("(U') R U R' U R U2 R' U' r' U2 R U R' U r"),
        Algorithm("(U2) r U r' R U R' U' r U' r' R U2 R' U' R U' R'"),
        Algorithm("R' U2 R U R' U R U r U R' U R U2 r'"),
        Algorithm("R' U2 R U R' U R U r U r' U R U' M' U' r'"),
        Algorithm("r U r' R U R' U' r U' r' U' R' U' R U' R' U2 R"),
        Algorithm("r U2 R' U' r' R2 U R' U' r U' r'"),
        Algorithm("r' U' R' F R U r y' U R U' R' U R U2 R'"),
        Algorithm("r' F R F' r U R' U R U R' U' R' F R F'"),
        Algorithm("r U' r' U' r U r' y' R2 D' R U R' D R2"),
        Algorithm("F R U R' U' F' R U2 R2 U' R2 U' R2 U2 R"),
        Algorithm("R U' R' U R y R U R' U2 R U2 R2 F R F' U F'"),
        Algorithm("R U2 R2 D' R U' R' D R U' R' F R2 U R' U' F'"),
        Algorithm("F U' R2 D R' U2 R D' R2 U F'"),
        Algorithm("(U) F U' R U' R' F' U' R' F R U2 R' F' R"),
        Algorithm("(U) F' U r' F r F U r U' r' U2 r U r'"),
        Algorithm("F R' F' R U R U' R2 F2 r U r' F R"),
        Algorithm("(U) F R U' R' U' R U R' F' U2 r U2 R' U' R U' r'"),
        Algorithm("(U2) R U R' U' R U' R' F' U' F R U R' F R U R' U' F'"),
        Algorithm("(U') R U2 R2 U' R U' R' U2 F R F'"),
        Algorithm("(U') r U2 R2 F R F' U2 r' F R F'"),
        Algorithm("(U) R' U2 R2 U R' U R U2 x' U' R' U x"),
        Algorithm("(U') R' F2 r2 U' r' F U2 R U' r' F"),
        Algorithm("R U2 R' U' R U' R' U R U2 R' U2 R' F R F'"),
        Algorithm("R' U2 R U R' U R U r' F2 r U2 r U' r' F"),
        Algorithm("(U) R' U' R' F R F' U R U2 r U R' U' r' F R F'"),
        Algorithm("(U2) r' F r F r U' r' U2 r U r' U' R U R' F'"),
        Algorithm("(U) F R' F' R U R U' R' U' R U2 R' U2 R' F R F'"),
        Algorithm("(U) r' U2 R U R' U r U R' F R U R' U' F' U R"),
        Algorithm("R' F R U R' U' F' U R U' R U R' U R U2 R'"),
        Algorithm("(U) R' U2 R U R' U R U' F R U' R' U' R U R' F'"),
        Algorithm("(U2) F U R2 D R' U' R D' R2 U R U' R' F'"),
        Algorithm("(U') F R' F' R U R U R' U F' U' F U' R U' R'"),
        Algorithm("(U) R U2 R' U' R U' R' F R U R' F' U' F' r U r'"),
        Algorithm("R' F R U R' U' F' U R U2 R' U2 R U R' U R"),
        Algorithm("(U2) R' U2 R U R' U R2 U R' F' U F U R U2 R'"),
        Algorithm("(U) R2 F R F' U' F R U R' U' F' U' R U' R' U R"),
        Algorithm("(U2) r U R' U R U2 r' R' F R U R' U' F' U R"),
        Algorithm("(U2) R' F U R U' R2 F' R2 U R' U' R"),
        Algorithm("R U' R' U R U' R' U' R U' F U R U' R' F' U2 R'"),
        Algorithm("(U2) R' U' R' F' R U R2 U' R' U' F U R U R'"),
        Algorithm("(U2) r U r' U R U' R' U R U' R' r U' r'"),
        Algorithm("(U) R U' R2 r U' R U' R' U r' R2 U R'"),
        Algorithm("(U2) r' U' r U' R' U R U' R' U R r' U r"),
        Algorithm("R U R' U' M' U R U' r' U' R' U2 R U R' U' R U R' U R"),
        Algorithm("(U) R U R' U R U' R2 F R F' y' R' U' R U R' U R"),
        Algorithm("r U r' U R U' R' M' U R U2 r'"),
        Algorithm("(U) R U2 R' U' R U R' U' y r' U' R' F' R U r"),
        Algorithm("(U) F R U R' U' R U R' U' F' f R U R' U' f'"),
        Algorithm("R U R' F' U2 F R U' R' U F R U R' U' R U R' U' F'"),
        Algorithm("(U2) R' U2 R U R' U R U' R U2 R2 F R F' R U2 R'"),
        Algorithm("R U2 r' F R' F' r F2 r U r' F"),
        Algorithm("R2 D R' U2 R D' R2 U2 R' F R2 U R' U' F'"),
        Algorithm("(U) R' U' R' F R F' U R U2 R U2 R2 U' R2 U' R2 U2 R"),
        Algorithm("(U) R' F R U2 R' F' R U F R U R' U F'"),
        Algorithm("(U) R U2 R' U2 R' F R F' U F R U' R' U R U R' F'"),
        Algorithm("(U') R' U' R F U R U' R' F' U2 R' U2 R"),
        Algorithm("(U') R U R' U R' U' F' U F R U R U2 R'"),
        Algorithm("F U R U2 R' U' R U R' F' U R U R' U R U2 R'"),
        Algorithm("(U2) F R U R' U' R F' r U R' U' r'"),
        Algorithm("(U') F R' F' R U2 F' U F U' R U2 R'"),
        Algorithm("(U2) F R U R' U2 R' U2 R U F' R' U R"),
        Algorithm("R' F R F' U2 R U' R' U F' U2 F"),
        Algorithm("F R U R' U' F' r U R' U' r' F R F'"),
        Algorithm("(U2) F R U R2 U' R F' R' U' R U R' U R"),
        Algorithm("(U') R' U' R U R' U' R U2 R' U' R U R' F' U2 F R"),
        Algorithm("(U') R U R' U' R U R' F' U2 F R U' R' U R U2 R'"),
        Algorithm("(U) R U R' U2 R U R' U' R U' F U R U' R' F' R'"),
        Algorithm("(U2) r' U' R U' R' U' r U r' U' r y R U' R'"),
        Algorithm("(U) r U R' U R U' R' U R' F R F' U2 r' F R F'"),
        Algorithm("R' U R U' R' U' R U R' U R' F R F' R U R' U R"),
        Algorithm("R' U' R U' R' U' R y U R U R' U R U R' U F' U' F"),
        Algorithm("(U2) R' F R U R' F' R F U' F' R U2 R' U' R U' R'"),
        Algorithm("r' U' R' U r U' R' U' R' F R F' R2 U' R' U2 R"),
        Algorithm("(U) R' U' R F U R U2 R' U2 R' U2 R2 U R' F'"),
        Algorithm("F R U R' F' U' F' r U' R' U' R U' r'"),
        Algorithm("(U2) R U R' U2 F' U F R U' R' U R U R' U' R U' R'"),
        Algorithm("(U2) L' U R U' L U R' U' r U r' R U R' U' r U' r'"),
        Algorithm("r2 F2 r U F R U R' F' r U' R2 F R F' R"),
        Algorithm("M U r U' r' U' r2 D r' U' r D' r' U2 R'"),
        Algorithm("(U2) r U r' R U R' U' r U' r' U' R' U2 R U R' U R"),
        Algorithm("(U2) R U R' U' M' U R U' r'"),
        Algorithm("R U2 R' U' R U' R2 F' U' F R' F R F' U R"),
        Algorithm("(U2) R' U' R U M U' R' U r"),
        Algorithm("F R U R' U' R' U' R F' R' U R U2 F U2 F'"),
        Algorithm("F r U r' R U' R' U' M' U M F'"),
        Algorithm("r U r' R U R' U' r U' r' R U R' U R U2 R'"),
        Algorithm("(U) r' U2 R U R' U r U r U r' R U R' U' r U' r'"),
        Algorithm("(U2) F' U2 F U2 R U' R' U R U R' U F' U' F"),
        Algorithm("(U2) r' U r U' r' F' U' r U2 R' U' R U' r' F r"),
        Algorithm("r U R U' r' y r2 D r' U' r D' r2"),
        Algorithm("(U) F' R' F R F' U' F R U R' y' R2 U R2"),
        Algorithm("R U' R' U' F U R U' R' F r U2 R' U' r' F R"),
        Algorithm("(U) F R' F R F' U' F U r U2 r' U' R U R' F2"),
        Algorithm("(U) R' F' U2 F U' R U R2 F R F' U2 R"),
        Algorithm("R U' R2 F R F' R U' y R U2 R' F'"),
        Algorithm("(U) F R' F' R U2 R U2 R' U' r U r' R U R' U' r U' r'"),
        Algorithm("M' U r' F R F' U R U R' U2 r U r'"),
        Algorithm("(U2) F R U' R' U2 R U R' U R' U2 R2 U R2 U R F'"),
        Algorithm("(U2) F R U' R' U R U2 R2 F R F' R U' R' F'"),
        Algorithm("R U2 R' U R U2 y R U R' U R U R' U F'"),
        Algorithm("R U R' U' R' F R2 U R2 F R F' R U' R' F'"),
        Algorithm("F U R U2 R' U' R U R' F' U' R' U' R U' R' U2 R"),
        Algorithm("R' U' R' F' U' F U R2 U2 R' U' R"),
        Algorithm("(U2) R U2 F R U R' U' F' U' R' U2 R U R'"),
        Algorithm("(U2) R U2 R' U' R U' R2 F2 r U2 R U' r' F"),
        Algorithm("R' U2 R U R' U R U2 R U2 R' U2 R' F R F'"),
        Algorithm("(U2) R U' R' F' U F R U R2 F R F'"),
        Algorithm("(U2) R' U' R U' F U' R' U' R U R U' R' U' R U R' F'"),
        Algorithm("(U2) R2 U R' U R' U' R U' R' F U R U' F' R'"),
        Algorithm("(U2) R' F' U2 R' F R U' R' F' R U' F U' R"),
        Algorithm("(U2) F R U' R' U R U R2 F' r U R U' r'"),
        Algorithm("(U2) R' U2 R U' R' U' R' F R F' R U2 R' U2 R"),
        Algorithm("(U2) r U r' F' R U R' U' R' F R r U' r'"),
        Algorithm("(U2) R U2 R' F U R' U' F' U R U' R U2 R'"),
        Algorithm("(U2) R U R' U' R' F R F' U2 F R U' R' U' R U2 R' U' F'"),
        Algorithm("(U2) R U2 r' U' R U R' F' r U2 R' U' r U' r' F"),
        Algorithm("F R U R' U2 R' F R F' R U R' U R U' R' F'"),
        Algorithm("R U2 R' U' R U' R' F R' F' R U2 R U2 R'"),
        Algorithm("(U') R U R' U' F' U' R' U' F' U F R F U2 R U' R'")
    };

	// Level configurations for cross and F2L searchs
	const SearchLevel CFOP::CrossLevelConf = SearchLevel(SearchActions::STEPS_LIST, SearchSteps::SINGLE_ALL, SearchCheck::CHECK);

	const SearchLevel CFOP::F2L_U_L0(SearchActions::STEPS_LIST, SearchSteps::SINGLE_D_NONE, SearchCheck::CHECK);
	const SearchLevel CFOP::F2L_U_L3(SearchActions::STEPS_LIST, SearchSteps::SINGLE_D_NONE, SearchCheck::NO_CHECK);
	const SearchLevel CFOP::F2L_U_L1(SearchActions::STEPS_LIST, SearchSteps::LATERAL_UD, SearchCheck::NO_CHECK);
	const SearchLevel CFOP::F2L_U_L2(SearchActions::STEPS_LIST, SearchSteps::SINGLE_D, SearchCheck::NO_CHECK);

	const SearchLevel CFOP::F2L_D_L0(SearchActions::STEPS_LIST, SearchSteps::SINGLE_U_NONE, SearchCheck::CHECK);
	const SearchLevel CFOP::F2L_D_L3(SearchActions::STEPS_LIST, SearchSteps::SINGLE_U_NONE, SearchCheck::NO_CHECK);
	const SearchLevel CFOP::F2L_D_L1(SearchActions::STEPS_LIST, SearchSteps::LATERAL_UD, SearchCheck::NO_CHECK);
	const SearchLevel CFOP::F2L_D_L2(SearchActions::STEPS_LIST, SearchSteps::SINGLE_U, SearchCheck::NO_CHECK);

	const SearchLevel CFOP::F2L_F_L0(SearchActions::STEPS_LIST, SearchSteps::SINGLE_B_NONE, SearchCheck::CHECK);
	const SearchLevel CFOP::F2L_F_L3(SearchActions::STEPS_LIST, SearchSteps::SINGLE_B_NONE, SearchCheck::NO_CHECK);
	const SearchLevel CFOP::F2L_F_L1(SearchActions::STEPS_LIST, SearchSteps::LATERAL_FB, SearchCheck::NO_CHECK);
	const SearchLevel CFOP::F2L_F_L2(SearchActions::STEPS_LIST, SearchSteps::SINGLE_B, SearchCheck::NO_CHECK);

	const SearchLevel CFOP::F2L_B_L0(SearchActions::STEPS_LIST, SearchSteps::SINGLE_F_NONE, SearchCheck::CHECK);
	const SearchLevel CFOP::F2L_B_L3(SearchActions::STEPS_LIST, SearchSteps::SINGLE_F_NONE, SearchCheck::NO_CHECK);
	const SearchLevel CFOP::F2L_B_L1(SearchActions::STEPS_LIST, SearchSteps::LATERAL_FB, SearchCheck::NO_CHECK);
	const SearchLevel CFOP::F2L_B_L2(SearchActions::STEPS_LIST, SearchSteps::SINGLE_F, SearchCheck::NO_CHECK);

	const SearchLevel CFOP::F2L_R_L0(SearchActions::STEPS_LIST, SearchSteps::SINGLE_L_NONE, SearchCheck::CHECK);
	const SearchLevel CFOP::F2L_R_L3(SearchActions::STEPS_LIST, SearchSteps::SINGLE_L_NONE, SearchCheck::NO_CHECK);
	const SearchLevel CFOP::F2L_R_L1(SearchActions::STEPS_LIST, SearchSteps::LATERAL_RL, SearchCheck::NO_CHECK);
	const SearchLevel CFOP::F2L_R_L2(SearchActions::STEPS_LIST, SearchSteps::SINGLE_L, SearchCheck::NO_CHECK);

	const SearchLevel CFOP::F2L_L_L0(SearchActions::STEPS_LIST, SearchSteps::SINGLE_R_NONE, SearchCheck::CHECK);
	const SearchLevel CFOP::F2L_L_L3(SearchActions::STEPS_LIST, SearchSteps::SINGLE_R_NONE, SearchCheck::NO_CHECK);
	const SearchLevel CFOP::F2L_L_L1(SearchActions::STEPS_LIST, SearchSteps::LATERAL_RL, SearchCheck::NO_CHECK);
	const SearchLevel CFOP::F2L_L_L2(SearchActions::STEPS_LIST, SearchSteps::SINGLE_R, SearchCheck::NO_CHECK);

	const SearchLevel CFOP::F2L_LC = SearchLevel(SearchActions::OPPOSITE_STEP_2_PREVIOUS, SearchSteps::NONE, SearchCheck::CHECK);

	// Configurations for F2L search according to cross layer
	const std::vector<SearchLevel> CFOP::SearchConf_F2L_U = { F2L_U_L0, F2L_U_L1, F2L_U_L2, F2L_LC,
															  F2L_U_L3, F2L_U_L1, F2L_U_L2, F2L_LC,
															  F2L_U_L3, F2L_U_L1, F2L_U_L2, F2L_LC };
	const std::vector<SearchLevel> CFOP::SearchConf_F2L_D = { F2L_D_L0, F2L_D_L1, F2L_D_L2, F2L_LC,
															  F2L_D_L3, F2L_D_L1, F2L_D_L2, F2L_LC,
															  F2L_D_L3, F2L_D_L1, F2L_D_L2, F2L_LC };
	const std::vector<SearchLevel> CFOP::SearchConf_F2L_F = { F2L_F_L0, F2L_F_L1, F2L_F_L2, F2L_LC,
															  F2L_F_L3, F2L_F_L1, F2L_F_L2, F2L_LC,
															  F2L_F_L3, F2L_F_L1, F2L_F_L2, F2L_LC };
	const std::vector<SearchLevel> CFOP::SearchConf_F2L_B = { F2L_B_L0, F2L_B_L1, F2L_B_L2, F2L_LC,
															  F2L_B_L3, F2L_B_L1, F2L_B_L2, F2L_LC,
															  F2L_B_L3, F2L_B_L1, F2L_B_L2, F2L_LC };
	const std::vector<SearchLevel> CFOP::SearchConf_F2L_R = { F2L_R_L0, F2L_R_L1, F2L_R_L2, F2L_LC,
															  F2L_R_L3, F2L_R_L1, F2L_R_L2, F2L_LC,
															  F2L_R_L3, F2L_R_L1, F2L_R_L2, F2L_LC };
	const std::vector<SearchLevel> CFOP::SearchConf_F2L_L = { F2L_L_L0, F2L_L_L1, F2L_L_L2, F2L_LC,
															  F2L_L_L3, F2L_L_L1, F2L_L_L2, F2L_LC,
															  F2L_L_L3, F2L_L_L1, F2L_L_L2, F2L_LC };

	// Reset the search results
	void CFOP::Reset()
	{
		CrossLayer = Layers::NONE;
		OLLCase = OLL::SKIP;
		PLLCase = PLL::SKIP;
        Case1LLL = 0u;
		Turn_Inspection = Steps::NONE;
		Solve_Cross.Clear();
		Solve_F2L_First.Clear();
		Solve_F2L_Second.Clear();
		Solve_F2L_Third.Clear();
		Solve_F2L_Fourth.Clear();
		Solve_F2L_1.Clear();
		Solve_F2L_2.Clear();
		Solve_F2L_3.Clear();
		Solve_F2L_4.Clear();
		Turn_OLL = Steps::NONE;
		Solve_OLL.Clear();
		Step_AUF = Steps::NONE;
		Turn_PLL = Steps::NONE;
        Turn_1LLL = Steps::NONE;
		Solve_PLL.Clear();
        Solve_1LLL.Clear();

        CubeCross = CubeF2L = CubeOLL = CubeFinal = Cube1LLL = CubeBase;
        CrossTime = F2LTime = OLLTime = PLLTime = Time1LLL = 0.0f;

		LastCrossDeep = 0u;
	}

    // Search the best cross solve algorithm with the given search deep for the scramble
    // Returns false if no cross found
	bool CFOP::SearchCross(const uint MaxDeep, const std::vector<PiecesGroups>& Crosses)
	{
        auto time_cross_start = std::chrono::system_clock::now();

		std::vector<SearchLevel> SearchConf_Cross;
        for (uint i = 0u; i < MaxDeep; i++) SearchConf_Cross.push_back(CrossLevelConf);
		LastCrossDeep = MaxDeep;

		Algorithm UCross_Solve, DCross_Solve, FCross_Solve, BCross_Solve, RCross_Solve, LCross_Solve;
        uint UCross_Score = 0u, DCross_Score = 0u, FCross_Score = 0u, BCross_Score = 0u, RCross_Score = 0u, LCross_Score = 0u;

		std::vector<PiecesGroups> CrossesGroup;

        // Review cross groups data, avoid non cross groups and repetitions of crosses
		bool UCtrl = false, DCtrl = false, FCtrl = false, BCtrl = false, RCtrl = false, LCtrl = false;
		for (const auto& C : Crosses)
		{
			if (((C == PiecesGroups::C_U) && !UCtrl) || ((C == PiecesGroups::C_D) && !DCtrl) ||
				((C == PiecesGroups::C_F) && !FCtrl) || ((C == PiecesGroups::C_B) && !BCtrl) ||
				((C == PiecesGroups::C_R) && !RCtrl) || ((C == PiecesGroups::C_L) && !LCtrl))
				{
					CrossesGroup.push_back(C);

					if (C == PiecesGroups::C_U) UCtrl = true;
					else if (C == PiecesGroups::C_D) DCtrl = true;
					else if (C == PiecesGroups::C_F) FCtrl = true;
					else if (C == PiecesGroups::C_B) BCtrl = true;
					else if (C == PiecesGroups::C_R) RCtrl = true;
					else if (C == PiecesGroups::C_L) LCtrl = true;
				}
		}

		// First level is extended in the search to improve the multithreading - first level will not be checked
		// (it's supose that the cross not will be solved in a single movement)
		// All crosses will be evaluated separatelly, so multiple search is enabled here
		DeepSearch DS_Cross(Scramble, CrossesGroup, SearchConf_Cross, true, true);
		DS_Cross.Run(Cores);
		Cores = DS_Cross.GetCoresUsed(); // Update to the real number of cores used
		
		if (UCtrl) UCross_Score = DS_Cross.EvaluateF2LResult(UCross_Solve, Layers::U, SearchPolicies::BEST_SOLVES);
		if (DCtrl) DCross_Score = DS_Cross.EvaluateF2LResult(DCross_Solve, Layers::D, SearchPolicies::BEST_SOLVES);
		if (FCtrl) FCross_Score = DS_Cross.EvaluateF2LResult(FCross_Solve, Layers::F, SearchPolicies::BEST_SOLVES);
		if (BCtrl) BCross_Score = DS_Cross.EvaluateF2LResult(BCross_Solve, Layers::B, SearchPolicies::BEST_SOLVES);
		if (RCtrl) RCross_Score = DS_Cross.EvaluateF2LResult(RCross_Solve, Layers::R, SearchPolicies::BEST_SOLVES);
		if (LCtrl) LCross_Score = DS_Cross.EvaluateF2LResult(LCross_Solve, Layers::L, SearchPolicies::BEST_SOLVES);

        // Get the layer with a best cross score
		CrossLayer = GetBestScoreLayer(UCross_Score, DCross_Score, FCross_Score, BCross_Score, RCross_Score, LCross_Score);

		switch (CrossLayer)
		{
		case Layers::U:
			Solve_Cross = UCross_Solve;
			Turn_Inspection = Steps::z2;
			break;
		case Layers::D:
			Solve_Cross = DCross_Solve;
			Turn_Inspection = Steps::NONE;
			break;
		case Layers::F:
			Solve_Cross = FCross_Solve;
			Turn_Inspection = Steps::xp;
			break;
		case Layers::B:
			Solve_Cross = BCross_Solve;
			Turn_Inspection = Steps::x;
			break;
		case Layers::R:
			Solve_Cross = RCross_Solve;
			Turn_Inspection = Steps::z;
			break;
		case Layers::L:
			Solve_Cross = LCross_Solve;
			Turn_Inspection = Steps::zp;
			break;
        default: // Cross not found
			Reset();
			LastCrossDeep = MaxDeep;

            auto time_cross_end = std::chrono::system_clock::now();
            std::chrono::duration<double> cross_elapsed_seconds = time_cross_end - time_cross_start;
            CrossTime = cross_elapsed_seconds.count();

			return false;
		}

		CubeCross.ApplyAlgorithm(Solve_Cross);
		
        auto time_cross_end = std::chrono::system_clock::now();
        std::chrono::duration<double> cross_elapsed_seconds = time_cross_end - time_cross_start;
        CrossTime = cross_elapsed_seconds.count();

		return true;
	}

    // Search the best F2L 'Solves' algorithms for the 'Scramble'
    // Returns true if the search is complete. If returns false, call this function again (executed step by step)
    bool CFOP::SearchF2LStep()
	{     
		if (!IsCrossSolved()) return true; // F2L search complete as no cross in the cube

		PiecesGroups F2L_1_Pieces, F2L_2_Pieces, F2L_3_Pieces, F2L_4_Pieces;
		switch (CrossLayer)
		{
		case Layers::U:
			F2L_1_Pieces = PiecesGroups::F2L_U_UFR;
			F2L_2_Pieces = PiecesGroups::F2L_U_UFL;
			F2L_3_Pieces = PiecesGroups::F2L_U_UBR;
			F2L_4_Pieces = PiecesGroups::F2L_U_UBL;
			break;
		case Layers::D:
			F2L_1_Pieces = PiecesGroups::F2L_D_DFR;
			F2L_2_Pieces = PiecesGroups::F2L_D_DFL;
			F2L_3_Pieces = PiecesGroups::F2L_D_DBR;
			F2L_4_Pieces = PiecesGroups::F2L_D_DBL;
			break;
		case Layers::F:
			F2L_1_Pieces = PiecesGroups::F2L_F_UFR;
			F2L_2_Pieces = PiecesGroups::F2L_F_UFL;
			F2L_3_Pieces = PiecesGroups::F2L_F_DFR;
			F2L_4_Pieces = PiecesGroups::F2L_F_DFL;
			break;
		case Layers::B:
			F2L_1_Pieces = PiecesGroups::F2L_B_UBR;
			F2L_2_Pieces = PiecesGroups::F2L_B_UBL;
			F2L_3_Pieces = PiecesGroups::F2L_B_DBR;
			F2L_4_Pieces = PiecesGroups::F2L_B_DBL;
			break;
		case Layers::R:
			F2L_1_Pieces = PiecesGroups::F2L_R_UFR;
			F2L_2_Pieces = PiecesGroups::F2L_R_UBR;
			F2L_3_Pieces = PiecesGroups::F2L_R_DFR;
			F2L_4_Pieces = PiecesGroups::F2L_R_DBR;
			break;
		case Layers::L:
			F2L_1_Pieces = PiecesGroups::F2L_L_UFL;
			F2L_2_Pieces = PiecesGroups::F2L_L_UBL;
			F2L_3_Pieces = PiecesGroups::F2L_L_DFL;
			F2L_4_Pieces = PiecesGroups::F2L_L_DBL;
			break;
		default: return true; // Invalid cross layer
		}

        // Apply all the current algorithms
		Algorithm AuxAlg = Scramble + Solve_Cross +
						   Solve_F2L_First + Solve_F2L_Second + Solve_F2L_Third + Solve_F2L_Fourth;

		Cube CubeAux(AuxAlg);
		bool F2L_1_IsSolved = CubeAux.IsSolved(F2L_1_Pieces),
			 F2L_2_IsSolved = CubeAux.IsSolved(F2L_2_Pieces),
			 F2L_3_IsSolved = CubeAux.IsSolved(F2L_3_Pieces),
			 F2L_4_IsSolved = CubeAux.IsSolved(F2L_4_Pieces);

		if (F2L_1_IsSolved && F2L_2_IsSolved && F2L_3_IsSolved && F2L_4_IsSolved)
		{
			CubeF2L = CubeCross;
			CubeF2L.ApplyAlgorithm(Solve_F2L_First);
			CubeF2L.ApplyAlgorithm(Solve_F2L_Second);
			CubeF2L.ApplyAlgorithm(Solve_F2L_Third);
			CubeF2L.ApplyAlgorithm(Solve_F2L_Fourth);
			CubeF2L.ApplyStep(Turn_Inspection);
			return true; // F2L search complete
		}

		std::vector<SearchLevel> SearchConf_F2L;
		switch (CrossLayer)
		{
		case Layers::U: SearchConf_F2L = SearchConf_F2L_U; break;
		case Layers::D: SearchConf_F2L = SearchConf_F2L_D; break;
		case Layers::F: SearchConf_F2L = SearchConf_F2L_F; break;
		case Layers::B: SearchConf_F2L = SearchConf_F2L_B; break;
		case Layers::R: SearchConf_F2L = SearchConf_F2L_R; break;
		case Layers::L: SearchConf_F2L = SearchConf_F2L_L; break;
		default: 
			Solve_F2L_First.Clear();
			Solve_F2L_Second.Clear();
			Solve_F2L_Third.Clear();
			Solve_F2L_Fourth.Clear();
			return true; // Search complete, no F2L found (invalid cross layer)
		}

		// Pieces to search F2L
		std::vector<PiecesGroups> F2L_1_PiecesToSearch, F2L_2_PiecesToSearch, F2L_3_PiecesToSearch, F2L_4_PiecesToSearch;

		switch (CrossLayer)
		{
		case Layers::U:
			F2L_1_PiecesToSearch = { PiecesGroups::C_U, PiecesGroups::F2L_U_UFR };
			F2L_2_PiecesToSearch = { PiecesGroups::C_U, PiecesGroups::F2L_U_UFL };
			F2L_3_PiecesToSearch = { PiecesGroups::C_U, PiecesGroups::F2L_U_UBR };
			F2L_4_PiecesToSearch = { PiecesGroups::C_U, PiecesGroups::F2L_U_UBL };
			break;
		case Layers::D:
			F2L_1_PiecesToSearch = { PiecesGroups::C_D, PiecesGroups::F2L_D_DFR };
			F2L_2_PiecesToSearch = { PiecesGroups::C_D, PiecesGroups::F2L_D_DFL };
			F2L_3_PiecesToSearch = { PiecesGroups::C_D, PiecesGroups::F2L_D_DBR };
			F2L_4_PiecesToSearch = { PiecesGroups::C_D, PiecesGroups::F2L_D_DBL };
			break;
		case Layers::F:
			F2L_1_PiecesToSearch = { PiecesGroups::C_F, PiecesGroups::F2L_F_UFR };
			F2L_2_PiecesToSearch = { PiecesGroups::C_F, PiecesGroups::F2L_F_UFL };
			F2L_3_PiecesToSearch = { PiecesGroups::C_F, PiecesGroups::F2L_F_DFR };
			F2L_4_PiecesToSearch = { PiecesGroups::C_F, PiecesGroups::F2L_F_DFL };
			break;
		case Layers::B:
			F2L_1_PiecesToSearch = { PiecesGroups::C_B, PiecesGroups::F2L_B_UBR };
			F2L_2_PiecesToSearch = { PiecesGroups::C_B, PiecesGroups::F2L_B_UBL };
			F2L_3_PiecesToSearch = { PiecesGroups::C_B, PiecesGroups::F2L_B_DBR };
			F2L_4_PiecesToSearch = { PiecesGroups::C_B, PiecesGroups::F2L_B_DBL };
			break;
		case Layers::R:
			F2L_1_PiecesToSearch = { PiecesGroups::C_R, PiecesGroups::F2L_R_UFR };
			F2L_2_PiecesToSearch = { PiecesGroups::C_R, PiecesGroups::F2L_R_UBR };
			F2L_3_PiecesToSearch = { PiecesGroups::C_R, PiecesGroups::F2L_R_DFR };
			F2L_4_PiecesToSearch = { PiecesGroups::C_R, PiecesGroups::F2L_R_DBR };
			break;
		case Layers::L:
			F2L_1_PiecesToSearch = { PiecesGroups::C_L, PiecesGroups::F2L_L_UFL };
			F2L_2_PiecesToSearch = { PiecesGroups::C_L, PiecesGroups::F2L_L_UBL };
			F2L_3_PiecesToSearch = { PiecesGroups::C_L, PiecesGroups::F2L_L_DFL };
			F2L_4_PiecesToSearch = { PiecesGroups::C_L, PiecesGroups::F2L_L_DBL };
			break;
		default: 
			Solve_F2L_First.Clear();
			Solve_F2L_Second.Clear();
			Solve_F2L_Third.Clear();
			Solve_F2L_Fourth.Clear();
			return true; // Search complete, no F2L found (invalid cross layer)
		}

		if (F2L_1_IsSolved)
		{
			F2L_2_PiecesToSearch.push_back(F2L_1_Pieces);
			F2L_3_PiecesToSearch.push_back(F2L_1_Pieces);
			F2L_4_PiecesToSearch.push_back(F2L_1_Pieces);
		}
		if (F2L_2_IsSolved)
		{
			F2L_1_PiecesToSearch.push_back(F2L_2_Pieces);
			F2L_3_PiecesToSearch.push_back(F2L_2_Pieces);
			F2L_4_PiecesToSearch.push_back(F2L_2_Pieces);
		}
		if (F2L_3_IsSolved)
		{
			F2L_1_PiecesToSearch.push_back(F2L_3_Pieces);
			F2L_2_PiecesToSearch.push_back(F2L_3_Pieces);
			F2L_4_PiecesToSearch.push_back(F2L_3_Pieces);
		}
		if (F2L_4_IsSolved)
		{
			F2L_1_PiecesToSearch.push_back(F2L_4_Pieces);
			F2L_2_PiecesToSearch.push_back(F2L_4_Pieces);
			F2L_3_PiecesToSearch.push_back(F2L_4_Pieces);
		}

		// Get the score for algorithms found
		uint F2L_1_Score = 0u, F2L_2_Score = 0u, F2L_3_Score = 0u, F2L_4_Score = 0u;

		// As each level should be evaluated, first level is not extended in the F2L search
		// All pieces groups (Cross + F2L) must be avaluated together, so multiple search is disabled
		if (!F2L_1_IsSolved) // First F2L search
		{
			DeepSearch DS_1_F2L(AuxAlg, F2L_1_PiecesToSearch, SearchConf_F2L);
			DS_1_F2L.Run(Cores);
			Cores = DS_1_F2L.GetCoresUsed(); // Update to the real number of cores used
			F2L_1_Score = DS_1_F2L.EvaluateF2LResult(Solve_F2L_1, CrossLayer, SearchPolicies::SHORT);
		}
		if (!F2L_2_IsSolved) // Second F2L search
		{
			DeepSearch DS_2_F2L(AuxAlg, F2L_2_PiecesToSearch, SearchConf_F2L);
			DS_2_F2L.Run(Cores);
			Cores = DS_2_F2L.GetCoresUsed(); // Update to the real number of cores used
			F2L_2_Score = DS_2_F2L.EvaluateF2LResult(Solve_F2L_2, CrossLayer, SearchPolicies::SHORT);
		}
		if (!F2L_3_IsSolved) // Third F2L search
		{
			DeepSearch DS_3_F2L(AuxAlg, F2L_3_PiecesToSearch, SearchConf_F2L);
			DS_3_F2L.Run(Cores);
			Cores = DS_3_F2L.GetCoresUsed(); // Update to the real number of cores used
			F2L_3_Score = DS_3_F2L.EvaluateF2LResult(Solve_F2L_3, CrossLayer, SearchPolicies::SHORT);
		}
		if (!F2L_4_IsSolved) // Fourth F2L search
		{
			DeepSearch DS_4_F2L(AuxAlg, F2L_4_PiecesToSearch, SearchConf_F2L);
			DS_4_F2L.Run(Cores);
			Cores = DS_4_F2L.GetCoresUsed(); // Update to the real number of cores used
			F2L_4_Score = DS_4_F2L.EvaluateF2LResult(Solve_F2L_4, CrossLayer, SearchPolicies::SHORT);
		}

		if (F2L_1_Score == 0u && F2L_2_Score == 0u && F2L_3_Score == 0u && F2L_4_Score == 0u)
		{
			Solve_F2L_First.Clear();
			Solve_F2L_Second.Clear();
			Solve_F2L_Third.Clear();
			Solve_F2L_Fourth.Clear();
			return true; // Search complete, no F2L found
		}

		if (F2L_1_Score >= F2L_2_Score && F2L_1_Score >= F2L_3_Score && F2L_1_Score >= F2L_4_Score)
		{
			F2L_1_IsSolved = true;
			if (!F2L_2_IsSolved) Solve_F2L_2.Clear();
			if (!F2L_3_IsSolved) Solve_F2L_3.Clear();
			if (!F2L_4_IsSolved) Solve_F2L_4.Clear();

			if (Solve_F2L_First.GetSize() == 0u) Solve_F2L_First = Solve_F2L_1;
			else if (Solve_F2L_Second.GetSize() == 0u) Solve_F2L_Second = Solve_F2L_1;
			else if (Solve_F2L_Third.GetSize() == 0u) Solve_F2L_Third = Solve_F2L_1;
			else Solve_F2L_Fourth = Solve_F2L_1;
		}
		else if (F2L_2_Score >= F2L_3_Score && F2L_2_Score >= F2L_4_Score)
		{
			F2L_2_IsSolved = true;
			if (!F2L_1_IsSolved) Solve_F2L_1.Clear();
			if (!F2L_3_IsSolved) Solve_F2L_3.Clear();
			if (!F2L_4_IsSolved) Solve_F2L_4.Clear();

			if (Solve_F2L_First.GetSize() == 0u) Solve_F2L_First = Solve_F2L_2;
			else if (Solve_F2L_Second.GetSize() == 0u) Solve_F2L_Second = Solve_F2L_2;
			else if (Solve_F2L_Third.GetSize() == 0u) Solve_F2L_Third = Solve_F2L_2;
			else Solve_F2L_Fourth = Solve_F2L_2;
		}
		else if (F2L_3_Score >= F2L_4_Score)
		{
			F2L_3_IsSolved = true;
			if (!F2L_1_IsSolved) Solve_F2L_1.Clear();
			if (!F2L_2_IsSolved) Solve_F2L_2.Clear();
			if (!F2L_4_IsSolved) Solve_F2L_4.Clear();

			if (Solve_F2L_First.GetSize() == 0u) Solve_F2L_First = Solve_F2L_3;
			else if (Solve_F2L_Second.GetSize() == 0u) Solve_F2L_Second = Solve_F2L_3;
			else if (Solve_F2L_Third.GetSize() == 0u) Solve_F2L_Third = Solve_F2L_3;
			else Solve_F2L_Fourth = Solve_F2L_3;
		}
		else
		{
			F2L_4_IsSolved = true;
			if (!F2L_1_IsSolved) Solve_F2L_1.Clear();
			if (!F2L_2_IsSolved) Solve_F2L_2.Clear();
			if (!F2L_3_IsSolved) Solve_F2L_3.Clear();

			if (Solve_F2L_First.GetSize() == 0u) Solve_F2L_First = Solve_F2L_4;
			else if (Solve_F2L_Second.GetSize() == 0u) Solve_F2L_Second = Solve_F2L_4;
			else if (Solve_F2L_Third.GetSize() == 0u) Solve_F2L_Third = Solve_F2L_4;
			else Solve_F2L_Fourth = Solve_F2L_4;
		}

		if (F2L_1_IsSolved && F2L_2_IsSolved && F2L_3_IsSolved && F2L_4_IsSolved)
		{
			CubeF2L = CubeCross;
			CubeF2L.ApplyAlgorithm(Solve_F2L_First);
			CubeF2L.ApplyAlgorithm(Solve_F2L_Second);
			CubeF2L.ApplyAlgorithm(Solve_F2L_Third);
			CubeF2L.ApplyAlgorithm(Solve_F2L_Fourth);

            CubeF2L.ApplyStep(Turn_Inspection); // Turn inspection must be applied here
		
			return true; // F2L search complete
		}
		return false; // F2L search not complete
	}

	// Orientation of last layer search
	bool CFOP::SearchOLL()
	{
        auto time_OLL_start = std::chrono::system_clock::now();

		M16 MaskOLL = 0u;

		if (!IsF2LSolved()) return false; // No F2L

        // Get the mask for OLL
		switch (CrossLayer)
		{
		case Layers::U: // z2 as first inspection turn
			if (CubeF2L.GetFace_DF_D() == Faces::D) MaskOLL |= 0x0001u; // Reference: UF_U
			if (CubeF2L.GetFace_DB_D() == Faces::D) MaskOLL |= 0x0002u; // Reference: UB_U
			if (CubeF2L.GetFace_DL_D() == Faces::D) MaskOLL |= 0x0004u; // Reference: UR_U
			if (CubeF2L.GetFace_DR_D() == Faces::D) MaskOLL |= 0x0008u; // Reference: UL_U
			if (CubeF2L.GetFace_DFL_D() == Faces::D) MaskOLL |= 0x0010u; // Reference: UFR_U
			if (CubeF2L.GetFace_DFR_D() == Faces::D) MaskOLL |= 0x0020u; // Reference: UFL_U
			if (CubeF2L.GetFace_DBL_D() == Faces::D) MaskOLL |= 0x0040u; // Reference: UBR_U
			if (CubeF2L.GetFace_DBR_D() == Faces::D) MaskOLL |= 0x0080u; // Reference: UBL_U
			if (CubeF2L.GetFace_DFL_F() == Faces::D) MaskOLL |= 0x0100u; // Reference: UFR_F
			if (CubeF2L.GetFace_DFL_L() == Faces::D) MaskOLL |= 0x0200u; // Reference: UFR_R
			if (CubeF2L.GetFace_DFR_F() == Faces::D) MaskOLL |= 0x0400u; // Reference: UFL_F
			if (CubeF2L.GetFace_DFR_R() == Faces::D) MaskOLL |= 0x0800u; // Reference: UFL_L
			if (CubeF2L.GetFace_DBL_B() == Faces::D) MaskOLL |= 0x1000u; // Reference: UBR_B
			if (CubeF2L.GetFace_DBL_L() == Faces::D) MaskOLL |= 0x2000u; // Reference: UBR_R
			if (CubeF2L.GetFace_DBR_B() == Faces::D) MaskOLL |= 0x4000u; // Reference: UBL_B
			if (CubeF2L.GetFace_DBR_R() == Faces::D) MaskOLL |= 0x8000u; // Reference: UBL_L
			break;
		case Layers::D: // No turn as first inspection turn
			if (CubeF2L.GetFace_UF_U() == Faces::U) MaskOLL |= 0x0001u; // Reference: UF_U
			if (CubeF2L.GetFace_UB_U() == Faces::U) MaskOLL |= 0x0002u; // Reference: UB_U
			if (CubeF2L.GetFace_UR_U() == Faces::U) MaskOLL |= 0x0004u; // Reference: UR_U
			if (CubeF2L.GetFace_UL_U() == Faces::U) MaskOLL |= 0x0008u; // Reference: UL_U
			if (CubeF2L.GetFace_UFR_U() == Faces::U) MaskOLL |= 0x0010u; // Reference: UFR_U
			if (CubeF2L.GetFace_UFL_U() == Faces::U) MaskOLL |= 0x0020u; // Reference: UFL_U
			if (CubeF2L.GetFace_UBR_U() == Faces::U) MaskOLL |= 0x0040u; // Reference: UBR_U
			if (CubeF2L.GetFace_UBL_U() == Faces::U) MaskOLL |= 0x0080u; // Reference: UBL_U
			if (CubeF2L.GetFace_UFR_F() == Faces::U) MaskOLL |= 0x0100u; // Reference: UFR_F
			if (CubeF2L.GetFace_UFR_R() == Faces::U) MaskOLL |= 0x0200u; // Reference: UFR_R
			if (CubeF2L.GetFace_UFL_F() == Faces::U) MaskOLL |= 0x0400u; // Reference: UFL_F
			if (CubeF2L.GetFace_UFL_L() == Faces::U) MaskOLL |= 0x0800u; // Reference: UFL_L
			if (CubeF2L.GetFace_UBR_B() == Faces::U) MaskOLL |= 0x1000u; // Reference: UBR_B
			if (CubeF2L.GetFace_UBR_R() == Faces::U) MaskOLL |= 0x2000u; // Reference: UBR_R
			if (CubeF2L.GetFace_UBL_B() == Faces::U) MaskOLL |= 0x4000u; // Reference: UBL_B
			if (CubeF2L.GetFace_UBL_L() == Faces::U) MaskOLL |= 0x8000u; // Reference: UBL_L
			break;
		case Layers::F: // x' as first inspection turn
			if (CubeF2L.GetFace_UB_B() == Faces::B) MaskOLL |= 0x0001u; // Reference: UF_U
			if (CubeF2L.GetFace_DB_B() == Faces::B) MaskOLL |= 0x0002u; // Reference: UB_U
			if (CubeF2L.GetFace_BR_B() == Faces::B) MaskOLL |= 0x0004u; // Reference: UR_U
			if (CubeF2L.GetFace_BL_B() == Faces::B) MaskOLL |= 0x0008u; // Reference: UL_U
			if (CubeF2L.GetFace_UBR_B() == Faces::B) MaskOLL |= 0x0010u; // Reference: UFR_U
			if (CubeF2L.GetFace_UBL_B() == Faces::B) MaskOLL |= 0x0020u; // Reference: UFL_U
			if (CubeF2L.GetFace_DBR_B() == Faces::B) MaskOLL |= 0x0040u; // Reference: UBR_U
			if (CubeF2L.GetFace_DBL_B() == Faces::B) MaskOLL |= 0x0080u; // Reference: UBL_U
			if (CubeF2L.GetFace_UBR_U() == Faces::B) MaskOLL |= 0x0100u; // Reference: UFR_F
			if (CubeF2L.GetFace_UBR_R() == Faces::B) MaskOLL |= 0x0200u; // Reference: UFR_R
			if (CubeF2L.GetFace_UBL_U() == Faces::B) MaskOLL |= 0x0400u; // Reference: UFL_F
			if (CubeF2L.GetFace_UBL_L() == Faces::B) MaskOLL |= 0x0800u; // Reference: UFL_L
			if (CubeF2L.GetFace_DBR_D() == Faces::B) MaskOLL |= 0x1000u; // Reference: UBR_B
			if (CubeF2L.GetFace_DBR_R() == Faces::B) MaskOLL |= 0x2000u; // Reference: UBR_R
			if (CubeF2L.GetFace_DBL_D() == Faces::B) MaskOLL |= 0x4000u; // Reference: UBL_B
			if (CubeF2L.GetFace_DBL_L() == Faces::B) MaskOLL |= 0x8000u; // Reference: UBL_L
			break;
		case Layers::B: // x as first inspection turn
			if (CubeF2L.GetFace_DF_F() == Faces::F) MaskOLL |= 0x0001u; // Reference: UF_U
			if (CubeF2L.GetFace_UF_F() == Faces::F) MaskOLL |= 0x0002u; // Reference: UB_U
			if (CubeF2L.GetFace_FR_F() == Faces::F) MaskOLL |= 0x0004u; // Reference: UR_U
			if (CubeF2L.GetFace_FL_F() == Faces::F) MaskOLL |= 0x0008u; // Reference: UL_U
			if (CubeF2L.GetFace_DFR_F() == Faces::F) MaskOLL |= 0x0010u; // Reference: UFR_U
			if (CubeF2L.GetFace_DFL_F() == Faces::F) MaskOLL |= 0x0020u; // Reference: UFL_U
			if (CubeF2L.GetFace_UFR_F() == Faces::F) MaskOLL |= 0x0040u; // Reference: UBR_U
			if (CubeF2L.GetFace_UFL_F() == Faces::F) MaskOLL |= 0x0080u; // Reference: UBL_U
			if (CubeF2L.GetFace_DFR_D() == Faces::F) MaskOLL |= 0x0100u; // Reference: UFR_F
			if (CubeF2L.GetFace_DFR_R() == Faces::F) MaskOLL |= 0x0200u; // Reference: UFR_R
			if (CubeF2L.GetFace_DFL_D() == Faces::F) MaskOLL |= 0x0400u; // Reference: UFL_F
			if (CubeF2L.GetFace_DFL_L() == Faces::F) MaskOLL |= 0x0800u; // Reference: UFL_L
			if (CubeF2L.GetFace_UFR_U() == Faces::F) MaskOLL |= 0x1000u; // Reference: UBR_B
			if (CubeF2L.GetFace_UFR_R() == Faces::F) MaskOLL |= 0x2000u; // Reference: UBR_R
			if (CubeF2L.GetFace_UFL_U() == Faces::F) MaskOLL |= 0x4000u; // Reference: UBL_B
			if (CubeF2L.GetFace_UFL_L() == Faces::F) MaskOLL |= 0x8000u; // Reference: UBL_L
			break;
		case Layers::R: // z as first inspection turn
			if (CubeF2L.GetFace_FL_L() == Faces::L) MaskOLL |= 0x0001u; // Reference: UF_U
			if (CubeF2L.GetFace_BL_L() == Faces::L) MaskOLL |= 0x0002u; // Reference: UB_U
			if (CubeF2L.GetFace_UL_L() == Faces::L) MaskOLL |= 0x0004u; // Reference: UR_U
			if (CubeF2L.GetFace_DL_L() == Faces::L) MaskOLL |= 0x0008u; // Reference: UL_U
			if (CubeF2L.GetFace_UFL_L() == Faces::L) MaskOLL |= 0x0010u; // Reference: UFR_U
			if (CubeF2L.GetFace_DFL_L() == Faces::L) MaskOLL |= 0x0020u; // Reference: UFL_U
			if (CubeF2L.GetFace_UBL_L() == Faces::L) MaskOLL |= 0x0040u; // Reference: UBR_U
			if (CubeF2L.GetFace_DBL_L() == Faces::L) MaskOLL |= 0x0080u; // Reference: UBL_U
			if (CubeF2L.GetFace_UFL_F() == Faces::L) MaskOLL |= 0x0100u; // Reference: UFR_F
			if (CubeF2L.GetFace_UFL_U() == Faces::L) MaskOLL |= 0x0200u; // Reference: UFR_R
			if (CubeF2L.GetFace_DFL_F() == Faces::L) MaskOLL |= 0x0400u; // Reference: UFL_F
			if (CubeF2L.GetFace_DFL_D() == Faces::L) MaskOLL |= 0x0800u; // Reference: UFL_L
			if (CubeF2L.GetFace_UBL_B() == Faces::L) MaskOLL |= 0x1000u; // Reference: UBR_B
			if (CubeF2L.GetFace_UBL_U() == Faces::L) MaskOLL |= 0x2000u; // Reference: UBR_R
			if (CubeF2L.GetFace_DBL_B() == Faces::L) MaskOLL |= 0x4000u; // Reference: UBL_B
			if (CubeF2L.GetFace_DBL_D() == Faces::L) MaskOLL |= 0x8000u; // Reference: UBL_L
			break;
		case Layers::L: // z' as first inspection turn
			if (CubeF2L.GetFace_FR_R() == Faces::R) MaskOLL |= 0x0001u; // Reference: UF_U
			if (CubeF2L.GetFace_BR_R() == Faces::R) MaskOLL |= 0x0002u; // Reference: UB_U
			if (CubeF2L.GetFace_DR_R() == Faces::R) MaskOLL |= 0x0004u; // Reference: UR_U
			if (CubeF2L.GetFace_UR_R() == Faces::R) MaskOLL |= 0x0008u; // Reference: UL_U
			if (CubeF2L.GetFace_DFR_R() == Faces::R) MaskOLL |= 0x0010u; // Reference: UFR_U
			if (CubeF2L.GetFace_UFR_R() == Faces::R) MaskOLL |= 0x0020u; // Reference: UFL_U
			if (CubeF2L.GetFace_DBR_R() == Faces::R) MaskOLL |= 0x0040u; // Reference: UBR_U
			if (CubeF2L.GetFace_UBR_R() == Faces::R) MaskOLL |= 0x0080u; // Reference: UBL_U
			if (CubeF2L.GetFace_DFR_F() == Faces::R) MaskOLL |= 0x0100u; // Reference: UFR_F
			if (CubeF2L.GetFace_DFR_D() == Faces::R) MaskOLL |= 0x0200u; // Reference: UFR_R
			if (CubeF2L.GetFace_UFR_F() == Faces::R) MaskOLL |= 0x0400u; // Reference: UFL_F
			if (CubeF2L.GetFace_UFR_U() == Faces::R) MaskOLL |= 0x0800u; // Reference: UFL_L
			if (CubeF2L.GetFace_DBR_B() == Faces::R) MaskOLL |= 0x1000u; // Reference: UBR_B
			if (CubeF2L.GetFace_DBR_D() == Faces::R) MaskOLL |= 0x2000u; // Reference: UBR_R
			if (CubeF2L.GetFace_UBR_B() == Faces::R) MaskOLL |= 0x4000u; // Reference: UBL_B
			if (CubeF2L.GetFace_UBR_U() == Faces::R) MaskOLL |= 0x8000u; // Reference: UBL_L
			break;
		default: break;
		}

		if (MaskOLL == 0u) return false; // Can`t get mask

		// Determine OLL case and PLL turn
		uint OLL_Index;
		for (OLL_Index = 0u; OLL_Index < 58u; OLL_Index++)
		{
			if (OLL_Masks[0][OLL_Index] == MaskOLL || 
			    OLL_Masks[1][OLL_Index] == MaskOLL || 
			    OLL_Masks[2][OLL_Index] == MaskOLL || 
			    OLL_Masks[3][OLL_Index] == MaskOLL) { OLLCase = static_cast<OLL>(OLL_Index); break; }
		}
		if (OLL_Index == 58u) return false; // No OLL case found

        // Get the OLL algorithm
        Solve_OLL = OLL_Algorithms[static_cast<uint>(OLLCase)][0]; // Only use the first algorithms in the array

        // Get the turn that must be done before applying OLL algorithm
		for (uint Turn_Index = 0u; Turn_Index < 4u; Turn_Index++)
		{
			if 		(Turn_Index == 0u) Turn_OLL = Steps::NONE;
			else if (Turn_Index == 1u) Turn_OLL = Steps::y;
			else if (Turn_Index == 2u) Turn_OLL = Steps::y2;
			else 					   Turn_OLL = Steps::yp;

			CubeOLL = CubeF2L;
			CubeOLL.ApplyStep(Turn_OLL);
			CubeOLL.ApplyAlgorithm(Solve_OLL);

            if (IsLastLayerOriented())
            {
                auto time_OLL_end = std::chrono::system_clock::now();
                std::chrono::duration<double> OLL_elapsed_seconds = time_OLL_end - time_OLL_start;
                OLLTime = OLL_elapsed_seconds.count();

                return true; // OLL found
            }
		}

		return false; // OLL not found
	}

	// Permutation of last layer search
	bool CFOP::SearchPLL()
	{
        auto time_PLL_start = std::chrono::system_clock::now();

		if (!IsLastLayerOriented()) return false;

		Cube CubeAux = CubeOLL;
		M16 PLLMask;
		Step_AUF = Turn_PLL = Steps::NONE;

		bool PLL_Found = false;
        do // Get the PLL mask
		{
			PLLMask = 0u;
			switch (CrossLayer)
			{
			case Layers::U: // UPPER LAYER 'D' (z2)
				if 		(CubeAux.GetPiece(PiecePositions::DF) == Pieces::DB) PLLMask |= 0x0001u;
				else if (CubeAux.GetPiece(PiecePositions::DF) == Pieces::DL) PLLMask |= 0x0002u;
				else if (CubeAux.GetPiece(PiecePositions::DF) == Pieces::DR) PLLMask |= 0x0003u;

				if 		(CubeAux.GetPiece(PiecePositions::DB) == Pieces::DB) PLLMask |= 0x0004u;
				else if (CubeAux.GetPiece(PiecePositions::DB) == Pieces::DL) PLLMask |= 0x0008u;
				else if (CubeAux.GetPiece(PiecePositions::DB) == Pieces::DR) PLLMask |= 0x000Cu;

				if 		(CubeAux.GetPiece(PiecePositions::DL) == Pieces::DB) PLLMask |= 0x0010u;
				else if (CubeAux.GetPiece(PiecePositions::DL) == Pieces::DL) PLLMask |= 0x0020u;
				else if (CubeAux.GetPiece(PiecePositions::DL) == Pieces::DR) PLLMask |= 0x0030u;

				if		(CubeAux.GetPiece(PiecePositions::DR) == Pieces::DB) PLLMask |= 0x0040u;
				else if (CubeAux.GetPiece(PiecePositions::DR) == Pieces::DL) PLLMask |= 0x0080u;
				else if (CubeAux.GetPiece(PiecePositions::DR) == Pieces::DR) PLLMask |= 0x00C0u;

				if 		(CubeAux.GetPiece(PiecePositions::DFL) == Pieces::DFR) PLLMask |= 0x0100u;
				else if (CubeAux.GetPiece(PiecePositions::DFL) == Pieces::DBL) PLLMask |= 0x0200u;
				else if (CubeAux.GetPiece(PiecePositions::DFL) == Pieces::DBR) PLLMask |= 0x0300u;

				if 		(CubeAux.GetPiece(PiecePositions::DFR) == Pieces::DFR) PLLMask |= 0x0400u;
				else if (CubeAux.GetPiece(PiecePositions::DFR) == Pieces::DBL) PLLMask |= 0x0800u;
				else if (CubeAux.GetPiece(PiecePositions::DFR) == Pieces::DBR) PLLMask |= 0x0C00u;

				if 		(CubeAux.GetPiece(PiecePositions::DBL) == Pieces::DFR) PLLMask |= 0x1000u;
				else if (CubeAux.GetPiece(PiecePositions::DBL) == Pieces::DBL) PLLMask |= 0x2000u;
				else if (CubeAux.GetPiece(PiecePositions::DBL) == Pieces::DBR) PLLMask |= 0x3000u;

				if 		(CubeAux.GetPiece(PiecePositions::DBR) == Pieces::DFR) PLLMask |= 0x4000u;
				else if (CubeAux.GetPiece(PiecePositions::DBR) == Pieces::DBL) PLLMask |= 0x8000u;
				else if (CubeAux.GetPiece(PiecePositions::DBR) == Pieces::DBR) PLLMask |= 0xC000u;
				break;

			case Layers::D: // UPPER LAYER 'U'
				if 		(CubeAux.GetPiece(PiecePositions::UF) == Pieces::UB) PLLMask |= 0x0001u;
				else if (CubeAux.GetPiece(PiecePositions::UF) == Pieces::UR) PLLMask |= 0x0002u;
				else if (CubeAux.GetPiece(PiecePositions::UF) == Pieces::UL) PLLMask |= 0x0003u;

				if 		(CubeAux.GetPiece(PiecePositions::UB) == Pieces::UB) PLLMask |= 0x0004u;
				else if (CubeAux.GetPiece(PiecePositions::UB) == Pieces::UR) PLLMask |= 0x0008u;
				else if (CubeAux.GetPiece(PiecePositions::UB) == Pieces::UL) PLLMask |= 0x000Cu;

				if 		(CubeAux.GetPiece(PiecePositions::UR) == Pieces::UB) PLLMask |= 0x0010u;
				else if (CubeAux.GetPiece(PiecePositions::UR) == Pieces::UR) PLLMask |= 0x0020u;
				else if (CubeAux.GetPiece(PiecePositions::UR) == Pieces::UL) PLLMask |= 0x0030u;

				if 		(CubeAux.GetPiece(PiecePositions::UL) == Pieces::UB) PLLMask |= 0x0040u;
				else if (CubeAux.GetPiece(PiecePositions::UL) == Pieces::UR) PLLMask |= 0x0080u;
				else if (CubeAux.GetPiece(PiecePositions::UL) == Pieces::UL) PLLMask |= 0x00C0u;

				if 		(CubeAux.GetPiece(PiecePositions::UFR) == Pieces::UFL) PLLMask |= 0x0100u;
				else if (CubeAux.GetPiece(PiecePositions::UFR) == Pieces::UBR) PLLMask |= 0x0200u;
				else if (CubeAux.GetPiece(PiecePositions::UFR) == Pieces::UBL) PLLMask |= 0x0300u;

				if 		(CubeAux.GetPiece(PiecePositions::UFL) == Pieces::UFL) PLLMask |= 0x0400u;
				else if (CubeAux.GetPiece(PiecePositions::UFL) == Pieces::UBR) PLLMask |= 0x0800u;
				else if (CubeAux.GetPiece(PiecePositions::UFL) == Pieces::UBL) PLLMask |= 0x0C00u;

				if 		(CubeAux.GetPiece(PiecePositions::UBR) == Pieces::UFL) PLLMask |= 0x1000u;
				else if (CubeAux.GetPiece(PiecePositions::UBR) == Pieces::UBR) PLLMask |= 0x2000u;
				else if (CubeAux.GetPiece(PiecePositions::UBR) == Pieces::UBL) PLLMask |= 0x3000u;

				if 		(CubeAux.GetPiece(PiecePositions::UBL) == Pieces::UFL) PLLMask |= 0x4000u;
				else if (CubeAux.GetPiece(PiecePositions::UBL) == Pieces::UBR) PLLMask |= 0x8000u;
				else if (CubeAux.GetPiece(PiecePositions::UBL) == Pieces::UBL) PLLMask |= 0xC000u;
				break;

			case Layers::F: // UPPER LAYER 'B' (x')
				if 		(CubeAux.GetPiece(PiecePositions::UB) == Pieces::DB) PLLMask |= 0x0001u;
				else if (CubeAux.GetPiece(PiecePositions::UB) == Pieces::BR) PLLMask |= 0x0002u;
				else if (CubeAux.GetPiece(PiecePositions::UB) == Pieces::BL) PLLMask |= 0x0003u;

				if 		(CubeAux.GetPiece(PiecePositions::DB) == Pieces::DB) PLLMask |= 0x0004u;
				else if (CubeAux.GetPiece(PiecePositions::DB) == Pieces::BR) PLLMask |= 0x0008u;
				else if (CubeAux.GetPiece(PiecePositions::DB) == Pieces::BL) PLLMask |= 0x000Cu;

				if 		(CubeAux.GetPiece(PiecePositions::BR) == Pieces::DB) PLLMask |= 0x0010u;
				else if (CubeAux.GetPiece(PiecePositions::BR) == Pieces::BR) PLLMask |= 0x0020u;
				else if (CubeAux.GetPiece(PiecePositions::BR) == Pieces::BL) PLLMask |= 0x0030u;

				if 		(CubeAux.GetPiece(PiecePositions::BL) == Pieces::DB) PLLMask |= 0x0040u;
				else if (CubeAux.GetPiece(PiecePositions::BL) == Pieces::BR) PLLMask |= 0x0080u;
				else if (CubeAux.GetPiece(PiecePositions::BL) == Pieces::BL) PLLMask |= 0x00C0u;

				if 		(CubeAux.GetPiece(PiecePositions::UBR) == Pieces::UBL) PLLMask |= 0x0100u;
				else if (CubeAux.GetPiece(PiecePositions::UBR) == Pieces::DBR) PLLMask |= 0x0200u;
				else if (CubeAux.GetPiece(PiecePositions::UBR) == Pieces::DBL) PLLMask |= 0x0300u;

				if 		(CubeAux.GetPiece(PiecePositions::UBL) == Pieces::UBL) PLLMask |= 0x0400u;
				else if (CubeAux.GetPiece(PiecePositions::UBL) == Pieces::DBR) PLLMask |= 0x0800u;
				else if (CubeAux.GetPiece(PiecePositions::UBL) == Pieces::DBL) PLLMask |= 0x0C00u;

				if 		(CubeAux.GetPiece(PiecePositions::DBR) == Pieces::UBL) PLLMask |= 0x1000u;
				else if (CubeAux.GetPiece(PiecePositions::DBR) == Pieces::DBR) PLLMask |= 0x2000u;
				else if (CubeAux.GetPiece(PiecePositions::DBR) == Pieces::DBL) PLLMask |= 0x3000u;

				if 		(CubeAux.GetPiece(PiecePositions::DBL) == Pieces::UBL) PLLMask |= 0x4000u;
				else if (CubeAux.GetPiece(PiecePositions::DBL) == Pieces::DBR) PLLMask |= 0x8000u;
				else if (CubeAux.GetPiece(PiecePositions::DBL) == Pieces::DBL) PLLMask |= 0xC000u;
				break;

			case Layers::B: // UPPER LAYER 'F' (x)
				if 		(CubeAux.GetPiece(PiecePositions::DF) == Pieces::UF) PLLMask |= 0x0001u;
				else if (CubeAux.GetPiece(PiecePositions::DF) == Pieces::FR) PLLMask |= 0x0002u;
				else if (CubeAux.GetPiece(PiecePositions::DF) == Pieces::FL) PLLMask |= 0x0003u;

				if 		(CubeAux.GetPiece(PiecePositions::UF) == Pieces::UF) PLLMask |= 0x0004u;
				else if (CubeAux.GetPiece(PiecePositions::UF) == Pieces::FR) PLLMask |= 0x0008u;
				else if (CubeAux.GetPiece(PiecePositions::UF) == Pieces::FL) PLLMask |= 0x000Cu;

				if 		(CubeAux.GetPiece(PiecePositions::FR) == Pieces::UF) PLLMask |= 0x0010u;
				else if (CubeAux.GetPiece(PiecePositions::FR) == Pieces::FR) PLLMask |= 0x0020u;
				else if (CubeAux.GetPiece(PiecePositions::FR) == Pieces::FL) PLLMask |= 0x0030u;

				if 		(CubeAux.GetPiece(PiecePositions::FL) == Pieces::UF) PLLMask |= 0x0040u;
				else if (CubeAux.GetPiece(PiecePositions::FL) == Pieces::FR) PLLMask |= 0x0080u;
				else if (CubeAux.GetPiece(PiecePositions::FL) == Pieces::FL) PLLMask |= 0x00C0u;

				if 		(CubeAux.GetPiece(PiecePositions::DFR) == Pieces::DFL) PLLMask |= 0x0100u;
				else if (CubeAux.GetPiece(PiecePositions::DFR) == Pieces::UFR) PLLMask |= 0x0200u;
				else if (CubeAux.GetPiece(PiecePositions::DFR) == Pieces::UFL) PLLMask |= 0x0300u;

				if 		(CubeAux.GetPiece(PiecePositions::DFL) == Pieces::DFL) PLLMask |= 0x0400u;
				else if (CubeAux.GetPiece(PiecePositions::DFL) == Pieces::UFR) PLLMask |= 0x0800u;
				else if (CubeAux.GetPiece(PiecePositions::DFL) == Pieces::UFL) PLLMask |= 0x0C00u;

				if 		(CubeAux.GetPiece(PiecePositions::UFR) == Pieces::DFL) PLLMask |= 0x1000u;
				else if (CubeAux.GetPiece(PiecePositions::UFR) == Pieces::UFR) PLLMask |= 0x2000u;
				else if (CubeAux.GetPiece(PiecePositions::UFR) == Pieces::UFL) PLLMask |= 0x3000u;

				if 		(CubeAux.GetPiece(PiecePositions::UFL) == Pieces::DFL) PLLMask |= 0x4000u;
				else if (CubeAux.GetPiece(PiecePositions::UFL) == Pieces::UFR) PLLMask |= 0x8000u;
				else if (CubeAux.GetPiece(PiecePositions::UFL) == Pieces::UFL) PLLMask |= 0xC000u;
				break;

			case Layers::R: // UPPER LAYER 'L' (z)
				if 		(CubeAux.GetPiece(PiecePositions::FL) == Pieces::BL) PLLMask |= 0x0001u;
				else if (CubeAux.GetPiece(PiecePositions::FL) == Pieces::UL) PLLMask |= 0x0002u;
				else if (CubeAux.GetPiece(PiecePositions::FL) == Pieces::DL) PLLMask |= 0x0003u;

				if 		(CubeAux.GetPiece(PiecePositions::BL) == Pieces::BL) PLLMask |= 0x0004u;
				else if (CubeAux.GetPiece(PiecePositions::BL) == Pieces::UL) PLLMask |= 0x0008u;
				else if (CubeAux.GetPiece(PiecePositions::BL) == Pieces::DL) PLLMask |= 0x000Cu;

				if 		(CubeAux.GetPiece(PiecePositions::UL) == Pieces::BL) PLLMask |= 0x0010u;
				else if (CubeAux.GetPiece(PiecePositions::UL) == Pieces::UL) PLLMask |= 0x0020u;
				else if (CubeAux.GetPiece(PiecePositions::UL) == Pieces::DL) PLLMask |= 0x0030u;

				if 		(CubeAux.GetPiece(PiecePositions::DL) == Pieces::BL) PLLMask |= 0x0040u;
				else if (CubeAux.GetPiece(PiecePositions::DL) == Pieces::UL) PLLMask |= 0x0080u;
				else if (CubeAux.GetPiece(PiecePositions::DL) == Pieces::DL) PLLMask |= 0x00C0u;

				if 		(CubeAux.GetPiece(PiecePositions::UFL) == Pieces::DFL) PLLMask |= 0x0100u;
				else if (CubeAux.GetPiece(PiecePositions::UFL) == Pieces::UBL) PLLMask |= 0x0200u;
				else if (CubeAux.GetPiece(PiecePositions::UFL) == Pieces::DBL) PLLMask |= 0x0300u;

				if (CubeAux.GetPiece(PiecePositions::DFL) == Pieces::DFL) PLLMask |= 0x0400u;
				else if (CubeAux.GetPiece(PiecePositions::DFL) == Pieces::UBL) PLLMask |= 0x0800u;
				else if (CubeAux.GetPiece(PiecePositions::DFL) == Pieces::DBL) PLLMask |= 0x0C00u;

				if (CubeAux.GetPiece(PiecePositions::UBL) == Pieces::DFL) PLLMask |= 0x1000u;
				else if (CubeAux.GetPiece(PiecePositions::UBL) == Pieces::UBL) PLLMask |= 0x2000u;
				else if (CubeAux.GetPiece(PiecePositions::UBL) == Pieces::DBL) PLLMask |= 0x3000u;

				if (CubeAux.GetPiece(PiecePositions::DBL) == Pieces::DFL) PLLMask |= 0x4000u;
				else if (CubeAux.GetPiece(PiecePositions::DBL) == Pieces::UBL) PLLMask |= 0x8000u;
				else if (CubeAux.GetPiece(PiecePositions::DBL) == Pieces::DBL) PLLMask |= 0xC000u;
				break;

			case Layers::L: // UPPER LAYER 'R' (z')
				if (CubeAux.GetPiece(PiecePositions::FR) == Pieces::BR) PLLMask |= 0x0001u;
				else if (CubeAux.GetPiece(PiecePositions::FR) == Pieces::DR) PLLMask |= 0x0002u;
				else if (CubeAux.GetPiece(PiecePositions::FR) == Pieces::UR) PLLMask |= 0x0003u;

				if (CubeAux.GetPiece(PiecePositions::BR) == Pieces::BR) PLLMask |= 0x0004u;
				else if (CubeAux.GetPiece(PiecePositions::BR) == Pieces::DR) PLLMask |= 0x0008u;
				else if (CubeAux.GetPiece(PiecePositions::BR) == Pieces::UR) PLLMask |= 0x000Cu;

				if (CubeAux.GetPiece(PiecePositions::DR) == Pieces::BR) PLLMask |= 0x0010u;
				else if (CubeAux.GetPiece(PiecePositions::DR) == Pieces::DR) PLLMask |= 0x0020u;
				else if (CubeAux.GetPiece(PiecePositions::DR) == Pieces::UR) PLLMask |= 0x0030u;

				if (CubeAux.GetPiece(PiecePositions::UR) == Pieces::BR) PLLMask |= 0x0040u;
				else if (CubeAux.GetPiece(PiecePositions::UR) == Pieces::DR) PLLMask |= 0x0080u;
				else if (CubeAux.GetPiece(PiecePositions::UR) == Pieces::UR) PLLMask |= 0x00C0u;

				if (CubeAux.GetPiece(PiecePositions::DFR) == Pieces::UFR) PLLMask |= 0x0100u;
				else if (CubeAux.GetPiece(PiecePositions::DFR) == Pieces::DBR) PLLMask |= 0x0200u;
				else if (CubeAux.GetPiece(PiecePositions::DFR) == Pieces::UBR) PLLMask |= 0x0300u;

				if (CubeAux.GetPiece(PiecePositions::UFR) == Pieces::UFR) PLLMask |= 0x0400u;
				else if (CubeAux.GetPiece(PiecePositions::UFR) == Pieces::DBR) PLLMask |= 0x0800u;
				else if (CubeAux.GetPiece(PiecePositions::UFR) == Pieces::UBR) PLLMask |= 0x0C00u;

				if (CubeAux.GetPiece(PiecePositions::DBR) == Pieces::UFR) PLLMask |= 0x1000u;
				else if (CubeAux.GetPiece(PiecePositions::DBR) == Pieces::DBR) PLLMask |= 0x2000u;
				else if (CubeAux.GetPiece(PiecePositions::DBR) == Pieces::UBR) PLLMask |= 0x3000u;

				if (CubeAux.GetPiece(PiecePositions::UBR) == Pieces::UFR) PLLMask |= 0x4000u;
				else if (CubeAux.GetPiece(PiecePositions::UBR) == Pieces::DBR) PLLMask |= 0x8000u;
				else if (CubeAux.GetPiece(PiecePositions::UBR) == Pieces::UBR) PLLMask |= 0xC000u;
				break;

			default: return false; // Invalid cross layer
			}

			for (uint Turn_Index = 0u; Turn_Index < 4u && !PLL_Found; Turn_Index++)
			{
				if (Turn_Index == 0u) Turn_PLL = Steps::NONE;
				else if (Turn_Index == 1u) Turn_PLL = Steps::y;
				else if (Turn_Index == 2u) Turn_PLL = Steps::y2;
				else 					   Turn_PLL = Steps::yp;

				for (uint PLL_Index = 0u; PLL_Index < 22u; PLL_Index++)
					if (PLLMask == PLL_Masks[Turn_Index][PLL_Index])
                    {
						PLLCase = static_cast<PLL>(PLL_Index);
						PLL_Found = true;
						break;
					}
			}

			if (!PLL_Found)
			{
				if (Step_AUF == Steps::NONE) Step_AUF = Steps::U;
				else if (Step_AUF == Steps::U) 	  Step_AUF = Steps::U2;
				else if (Step_AUF == Steps::U2)   Step_AUF = Steps::Up;
				else 							  Step_AUF = Steps::NONE;
				CubeAux.ApplyStep(Steps::U);
			}

		} while (Step_AUF != Steps::NONE && !PLL_Found);

		if (!PLL_Found) return false;

        Solve_PLL = PLL_Algorithms[static_cast<uint>(PLLCase)][0]; // Only use the first algorithms in the array

		for (uint Turn_Index = 0u; Turn_Index < 4u; Turn_Index++)
		{
			if (Turn_Index == 0u) Turn_PLL = Steps::NONE;
			else if (Turn_Index == 1u) Turn_PLL = Steps::y;
			else if (Turn_Index == 2u) Turn_PLL = Steps::y2;
			else 					   Turn_PLL = Steps::yp;

			CubeFinal = CubeOLL;
			CubeFinal.ApplyStep(Step_AUF);
			CubeFinal.ApplyStep(Turn_PLL);
			CubeFinal.ApplyAlgorithm(Solve_PLL);

            if (CubeFinal.IsSolved())
            {
                auto time_PLL_end = std::chrono::system_clock::now();
                std::chrono::duration<double> PLL_elapsed_seconds = time_PLL_end - time_PLL_start;
                PLLTime = PLL_elapsed_seconds.count();

                return true; // PLL found
            }
		}

		return false;
	}

    // One-Look Last Layer search (1LLL)
    bool CFOP::Search1LLL()
    {
        auto time_1LLL_start = std::chrono::system_clock::now();

        if (!IsF2LSolved()) return false; // No F2L

        Case1LLL = 1u;
        bool Found1LLL = false;

        for (auto &Alg1LLL : Algorithms_1LLL)
        {
            // Get the turn that must be done before applying 1LLL algorithm
            for (uint Turn_Index = 0u; Turn_Index < 4u; Turn_Index++)
            {
                if 		(Turn_Index == 0u) Turn_1LLL = Steps::NONE;
                else if (Turn_Index == 1u) Turn_1LLL = Steps::y;
                else if (Turn_Index == 2u) Turn_1LLL = Steps::y2;
                else 					   Turn_1LLL = Steps::yp;

                Cube1LLL = CubeF2L;
                Cube1LLL.ApplyStep(Turn_1LLL);
                Cube1LLL.ApplyAlgorithm(Alg1LLL);

                if (Cube1LLL.IsSolved())
                {
                    Step_AUF = Steps::NONE;
                    Found1LLL = true;
                }
                else
                {
                    Cube1LLL.U();
                    if (Cube1LLL.IsSolved())
                    {
                        Step_AUF = Steps::U;
                        Found1LLL = true;
                    }
                    else
                    {
                        Cube1LLL.U();
                        if (Cube1LLL.IsSolved())
                        {
                            Step_AUF = Steps::U2;
                            Found1LLL = true;
                        }
                        else
                        {
                            Cube1LLL.U();
                            if (Cube1LLL.IsSolved())
                            {
                                Step_AUF = Steps::Up;
                                Found1LLL = true;
                            }
                        }
                    }
                }

                if (Found1LLL)
                {
                    Solve_1LLL = Algorithms_1LLL[Case1LLL - 1u]; // Get the 1LLL algorithm

                    auto time_1LLL_end = std::chrono::system_clock::now();
                    std::chrono::duration<double> elapsed_seconds_1LLL = time_1LLL_end - time_1LLL_start;
                    Time1LLL = elapsed_seconds_1LLL.count();

                    return true; // 1LLL found
                }
            }
            Case1LLL++;
        }
        return false; // 1LLL not found
    }

	// Get the layer with the best solve score
    Layers CFOP::GetBestScoreLayer (const uint UCross_Score, const uint DCross_Score,
		const uint FCross_Score, const uint BCross_Score,
		const uint RCross_Score, const uint LCross_Score)
	{
		if (UCross_Score == 0u && DCross_Score == 0u &&
			FCross_Score == 0u && BCross_Score == 0u &&
			RCross_Score == 0u && LCross_Score == 0u) return Layers::NONE; // No cross found 

		if (UCross_Score >= DCross_Score && UCross_Score >= FCross_Score &&
			UCross_Score >= BCross_Score && UCross_Score >= RCross_Score &&
			UCross_Score >= LCross_Score) return Layers::U;

		else if (DCross_Score >= FCross_Score && DCross_Score >= BCross_Score &&
			DCross_Score >= RCross_Score && DCross_Score >= LCross_Score) return Layers::D;

		else if (FCross_Score >= BCross_Score && FCross_Score >= RCross_Score &&
			FCross_Score >= LCross_Score) return Layers::F;

		else if (BCross_Score >= RCross_Score && BCross_Score >= LCross_Score) return Layers::B;

		else if (RCross_Score >= LCross_Score) return Layers::R;

		else return Layers::L;
	}

    // Get a solve report
    std::string CFOP::GetReport() const
    {
        std::string Report  = "Scramble (" + std::to_string(Scramble.GetNumSteps()) + "): " + GetTextScramble() + "\n";

        if (!IsCrossSolved())
        {
            Report += "Cross not solved in " + std::to_string(GetLastCrossDeep()) + " movements!\n";
            Report += "Search time: " + std::to_string(GetFullTime()) + " s\n";
            return Report;
        }

        std::string Inspection = GetTextInspection();
        if (Inspection.size() > 0) Report +=  "Inspection: " + Inspection + "\n";

        std::string CrossType;
        switch (GetCrossF2LSolved()) // Number of F2L solves with the cross
        {
        case 0u: CrossType = "Cross"; break;
        case 1u: CrossType = "XCross"; break;
        case 2u: CrossType = "XXCross"; break;
        case 3u: CrossType = "XXXCross"; break;
        case 4u: CrossType = "XXXXCross"; break;
        default: CrossType = "Cross"; break;
        }
        Report += "\n" + CrossType + " (" + std::to_string(GetLengthCrossSolve()) + "): " + GetTextCrossSolve() + "\n";

        // Show F2L solves
        if (!IsF2LSolved())
        {
            Report += "F2L not solved!\n";
            Report += "Search time: " + std::to_string(GetFullTime()) + " s\n";
            return Report;
        }

        std::string F2LString = GetTextF2LFirstSolve();
        if (F2LString.size() > 0) Report += "F2L 1 (" + std::to_string(GetLengthF2LFirstSolve()) + "): " + F2LString + "\n";
        F2LString = GetTextF2LSecondSolve();
        if (F2LString.size() > 0) Report += "F2L 2 (" + std::to_string(GetLengthF2LSecondSolve()) + "): " + F2LString + "\n";
        F2LString = GetTextF2LThirdSolve();
        if (F2LString.size() > 0) Report += "F2L 3 (" + std::to_string(GetLengthF2LThirdSolve()) + "): " + F2LString + "\n";
        F2LString = GetTextF2LFourthSolve();
        if (F2LString.size() > 0) Report += "F2L 4 (" + std::to_string(GetLengthF2LFourthSolve()) + "): " + F2LString + "\n";

        if (Case1LLL == 0u) // OLL + PLL
        {
            // Show OLL solve
            if (!IsLastLayerOriented())
            {
                Report += "OLL not solved!\n";
                Report += "Search time: " + std::to_string(GetFullTime()) + " s\n";
                return Report;
            }

            std::string OLLTurnString = GetTextOLLTurn();
            std::string OLLString = GetTextOLLSolve();
            if (OLLString.size() > 0)
            {
                Report += "OLL (" + std::to_string(GetLengthOLLSolve() + GetLengthOLLTurn()) + "): ";
                if (OLLTurnString.size() == 0) Report += OLLString + "\n";
                else Report += "(" + OLLTurnString + ") " + OLLString + "\n";
            }
            else Report += "OLL: SKIP!\n";

            // Check PLL solve
            if (!IsSolved())
            {
                Report += "PLL not solved!\n";
                Report += "Search time: " + std::to_string(GetFullTime()) + " s\n";
                return Report;
            }

            // Show AUF solve
            std::string AUFString = GetTextAUFSolve();
            if (AUFString.size() > 0) Report += "AUF: " + AUFString + "\n";

            // Show PLL solve
            std::string PLLTurnString = GetTextPLLTurn();
            std::string PLLString = GetTextPLLSolve();
            if (PLLString.size() > 0)
            {
                Report += "PLL (" + std::to_string(GetLengthPLLSolve() + GetLengthPLLTurn()) + "): ";
                if (PLLTurnString.size() == 0) Report += PLLString + "\n";
                else Report += "(" + PLLTurnString + ") " + PLLString + "\n";
            }
            else Report += "PLL: SKIP!\n";
        }

        else // 1LLL
        {
            // Show 1LLL solvearray
            if (!Cube1LLL.IsSolved())
            {
                Report += "1LLL not solved!\n" + GetText1LLLCase() + "\n";
                Report += "Search time: " + std::to_string(GetFullTime()) + " s\n";
                return Report;
            }
            std::string TurnString1LLL = GetText1LLLTurn();
            std::string String1LLL = GetText1LLLSolve();
            if (String1LLL.size() > 0)
            {
                Report += "1LLL (" + std::to_string(GetLength1LLLSolve() + GetLength1LLLTurn()) + "): ";
                if (TurnString1LLL.size() == 0) Report += String1LLL + "\n";
                else Report += "(" + TurnString1LLL + ") " + String1LLL + "\n";
            }
            else Report += "1LLL: SKIP!\n";
            // Show AUF solve
            std::string AUFString = GetTextAUFSolve();
            if (AUFString.size() > 0) Report += "AUF: " + AUFString + "\n";
        }

        // Show summary
        Report += "\nSolve movements: " + std::to_string(GetLengthSolve()) + "\n";
        Report += CrossType + " in layer " + Cube::GetLayerChar(GetCrossLayer()) +
				  ", in " + std::to_string(GetLastCrossDeep()) + " or less movements\n";
        if (Case1LLL == 0u) // OLL + PLL
        {
            Report += "OLL case: " + GetTextOLLCase() + "\n";
            Report += "PLL case: " + GetTextPLLCase() + "\n";
        }
        else Report += "1LLL case: " + GetText1LLLCase() + "\n";
		Report += "Total search time: " + std::to_string(GetFullTime()) + " s\n";
		Report += "Cross search time: " + std::to_string(GetCrossTime()) + " s\n";
        Report += "F2L search time: " + std::to_string(GetF2LTime()) + " s\n";
        if (Case1LLL == 0u) // OLL + PLL
        {
            Report += "OLL search time: " + std::to_string(GetOLLTime()) + " s\n";
            Report += "PLL search time: " + std::to_string(GetPLLTime()) + " s\n";
        }
        else Report += "1LLL search time: " + std::to_string(Get1LLLTime()) + " s\n";
		Report += "Threads used: " + std::to_string(GetUsedCores() > 0 ? GetUsedCores() : 0) +
		          " of " + std::to_string(DeepSearch::GetSystemCores()) + "\n";

        return Report;
    };
}

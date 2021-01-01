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

#include "edges.h"

namespace grcube3
{
	// Criterion for edges direction:
	// 'E' layer edge into layer 'E': Positive direction if 'F/B' sticker points towards 'F/B' direction
	// 'E' layer edge into layer 'U/D': Positive direction if 'F/B' sticker points towards 'U/D' direction
	// 'U/D' layer edge into layer 'E': Positive direction if 'U/D' sticker points towards 'F/B' direction
	// 'U/D' layer edge into layer 'U/D': Positive direction if 'U/D' sticker points towards 'U/D' direction
	
	// Array to get the face (color) in the FR_F sticker position
	const Faces c_Edges::f_FR_F[12][2] = 
	{ //    Pos       Neg
		{Faces::F, Faces::R}, // FR
		{Faces::F, Faces::L}, // FL
		{Faces::B, Faces::L}, // BL
		{Faces::B, Faces::R}, // BR
		{Faces::U, Faces::F}, // UF
		{Faces::U, Faces::L}, // UL
		{Faces::U, Faces::B}, // UB
		{Faces::U, Faces::R}, // UR
		{Faces::D, Faces::F}, // DF
		{Faces::D, Faces::L}, // DL
		{Faces::D, Faces::B}, // DB
		{Faces::D, Faces::R}, // DR
	};
	
	// Array to get the face (color) in the FR_R sticker position
	const Faces c_Edges::f_FR_R[12][2] = 
	{ //    Pos       Neg
		{Faces::R, Faces::F}, // FR
		{Faces::L, Faces::F}, // FL
		{Faces::L, Faces::B}, // BL
		{Faces::R, Faces::B}, // BR
		{Faces::F, Faces::U}, // UF
		{Faces::L, Faces::U}, // UL
		{Faces::B, Faces::U}, // UB
		{Faces::R, Faces::U}, // UR
		{Faces::F, Faces::D}, // DF
		{Faces::L, Faces::D}, // DL
		{Faces::B, Faces::D}, // DB
		{Faces::R, Faces::D}, // DR
	};
	
	// Array to get the sticker in the FR_F sticker position
	const Stickers c_Edges::s_FR_F[12][2] = 
	{ //      Pos             Neg
		{Stickers::FR_F, Stickers::FR_R}, // FR
		{Stickers::FL_F, Stickers::FL_L}, // FL
		{Stickers::BL_B, Stickers::BL_L}, // BL
		{Stickers::BR_B, Stickers::BR_R}, // BR
		{Stickers::UF_U, Stickers::UF_F}, // UF
		{Stickers::UL_U, Stickers::UL_L}, // UL
		{Stickers::UB_U, Stickers::UB_B}, // UB
		{Stickers::UR_U, Stickers::UR_R}, // UR
		{Stickers::DF_D, Stickers::DF_F}, // DF
		{Stickers::DL_D, Stickers::DL_L}, // DL
		{Stickers::DB_D, Stickers::DB_B}, // DB
		{Stickers::DR_D, Stickers::DR_R}, // DR
	};
	
	// Array to get the sticker in the FR_R sticker position
	const Stickers c_Edges::s_FR_R[12][2] = 
	{ //      Pos             Neg
		{Stickers::FR_R, Stickers::FR_F}, // FR
		{Stickers::FL_L, Stickers::FL_F}, // FL
		{Stickers::BL_L, Stickers::BL_B}, // BL
		{Stickers::BR_R, Stickers::BR_B}, // BR
		{Stickers::UF_F, Stickers::UF_U}, // UF
		{Stickers::UL_L, Stickers::UL_U}, // UL
		{Stickers::UB_B, Stickers::UB_U}, // UB
		{Stickers::UR_R, Stickers::UR_U}, // UR
		{Stickers::DF_F, Stickers::DF_D}, // DF
		{Stickers::DL_L, Stickers::DL_D}, // DL
		{Stickers::DB_B, Stickers::DB_D}, // DB
		{Stickers::DR_R, Stickers::DR_D}, // DR
	};
			
	void c_Edges::e_U() // Movement U
	{
		S64 buffer = GetStatusPos_UF();
		PutStatusPos_UF(GetStatusPos_UR());
		PutStatusPos_UR(GetStatusPos_UB());
		PutStatusPos_UB(GetStatusPos_UL());
		PutStatusPos_UL(buffer);
	
		buffer = GetStatusDir_UF();
		PutStatusDir_UF(GetStatusDir_UR());
		PutStatusDir_UR(GetStatusDir_UB());
		PutStatusDir_UB(GetStatusDir_UL());
		PutStatusDir_UL(buffer);
	}
	
	void c_Edges::e_U2() // Movement U2
	{
		S64 buffer = GetStatusPos_UF();
		PutStatusPos_UF(GetStatusPos_UB());
		PutStatusPos_UB(buffer);
	
		buffer = GetStatusDir_UF();
		PutStatusDir_UF(GetStatusDir_UB());
		PutStatusDir_UB(buffer);
	
		buffer = GetStatusPos_UL();
		PutStatusPos_UL(GetStatusPos_UR());
		PutStatusPos_UR(buffer);
	
		buffer = GetStatusDir_UL();
		PutStatusDir_UL(GetStatusDir_UR());
		PutStatusDir_UR(buffer);
	}
	
	void c_Edges::e_Up() // Movement U'
	{
		S64 buffer = GetStatusPos_UF();
		PutStatusPos_UF(GetStatusPos_UL());
		PutStatusPos_UL(GetStatusPos_UB());
		PutStatusPos_UB(GetStatusPos_UR());
		PutStatusPos_UR(buffer);
	
		buffer = GetStatusDir_UF();
		PutStatusDir_UF(GetStatusDir_UL());
		PutStatusDir_UL(GetStatusDir_UB());
		PutStatusDir_UB(GetStatusDir_UR());
		PutStatusDir_UR(buffer);
	}
	
	void c_Edges::e_D() // Movement D
	{
		S64 buffer = GetStatusPos_DF();
		PutStatusPos_DF(GetStatusPos_DL());
		PutStatusPos_DL(GetStatusPos_DB());
		PutStatusPos_DB(GetStatusPos_DR());
		PutStatusPos_DR(buffer);
	
		buffer = GetStatusDir_DF();
		PutStatusDir_DF(GetStatusDir_DL());
		PutStatusDir_DL(GetStatusDir_DB());
		PutStatusDir_DB(GetStatusDir_DR());
		PutStatusDir_DR(buffer);
	}
	
	void c_Edges::e_D2() // Movement D2
	{
		S64 buffer = GetStatusPos_DF();
		PutStatusPos_DF(GetStatusPos_DB());
		PutStatusPos_DB(buffer);
	
		buffer = GetStatusDir_DF();
		PutStatusDir_DF(GetStatusDir_DB());
		PutStatusDir_DB(buffer);
	
		buffer = GetStatusPos_DL();
		PutStatusPos_DL(GetStatusPos_DR());
		PutStatusPos_DR(buffer);
	
		buffer = GetStatusDir_DL();
		PutStatusDir_DL(GetStatusDir_DR());
		PutStatusDir_DR(buffer);
	}
	
	void c_Edges::e_Dp() // Movement D'
	{
		S64 buffer = GetStatusPos_DF();
		PutStatusPos_DF(GetStatusPos_DR());
		PutStatusPos_DR(GetStatusPos_DB());
		PutStatusPos_DB(GetStatusPos_DL());
		PutStatusPos_DL(buffer);
	
		buffer = GetStatusDir_DF();
		PutStatusDir_DF(GetStatusDir_DR());
		PutStatusDir_DR(GetStatusDir_DB());
		PutStatusDir_DB(GetStatusDir_DL());
		PutStatusDir_DL(buffer);
	}
	
	void c_Edges::e_F() // Movement F
	{
		S64 buffer = GetStatusPos_FR();
		PutStatusPos_FR(GetStatusPos_UF());
		PutStatusPos_UF(GetStatusPos_FL());
		PutStatusPos_FL(GetStatusPos_DF());
		PutStatusPos_DF(buffer);
	
		buffer = GetStatusDir_FR();
		PutStatusDir_FR(GetStatusDir_UF() == EDGE_DIR_POS ? EDGE_DIR_NEG : EDGE_DIR_POS);
		PutStatusDir_UF(GetStatusDir_FL() == EDGE_DIR_POS ? EDGE_DIR_NEG : EDGE_DIR_POS);
		PutStatusDir_FL(GetStatusDir_DF() == EDGE_DIR_POS ? EDGE_DIR_NEG : EDGE_DIR_POS);
		PutStatusDir_DF(buffer == EDGE_DIR_POS ? EDGE_DIR_NEG : EDGE_DIR_POS);
	
	}
	
	void c_Edges::e_F2() // Movement F2
	{
		S64 buffer = GetStatusPos_FR();
		PutStatusPos_FR(GetStatusPos_FL());
		PutStatusPos_FL(buffer);
	
		buffer = GetStatusDir_FR();
		PutStatusDir_FR(GetStatusDir_FL());
		PutStatusDir_FL(buffer);
	
		buffer = GetStatusPos_UF();
		PutStatusPos_UF(GetStatusPos_DF());
		PutStatusPos_DF(buffer);
	
		buffer = GetStatusDir_UF();
		PutStatusDir_UF(GetStatusDir_DF());
		PutStatusDir_DF(buffer);
	}
	
	void c_Edges::e_Fp() // Movement F'
	{
		S64 buffer = GetStatusPos_FR();
		PutStatusPos_FR(GetStatusPos_DF());
		PutStatusPos_DF(GetStatusPos_FL());
		PutStatusPos_FL(GetStatusPos_UF());
		PutStatusPos_UF(buffer);
	
		buffer = GetStatusDir_FR();
		PutStatusDir_FR(GetStatusDir_DF() == EDGE_DIR_POS ? EDGE_DIR_NEG : EDGE_DIR_POS);
		PutStatusDir_DF(GetStatusDir_FL() == EDGE_DIR_POS ? EDGE_DIR_NEG : EDGE_DIR_POS);
		PutStatusDir_FL(GetStatusDir_UF() == EDGE_DIR_POS ? EDGE_DIR_NEG : EDGE_DIR_POS);
		PutStatusDir_UF(buffer == EDGE_DIR_POS ? EDGE_DIR_NEG : EDGE_DIR_POS);
	}
	
	void c_Edges::e_B() // Movement B
	{
		S64 buffer = GetStatusPos_BL();
		PutStatusPos_BL(GetStatusPos_UB());
		PutStatusPos_UB(GetStatusPos_BR());
		PutStatusPos_BR(GetStatusPos_DB());
		PutStatusPos_DB(buffer);
	
		buffer = GetStatusDir_BL();
		PutStatusDir_BL(GetStatusDir_UB() == EDGE_DIR_POS ? EDGE_DIR_NEG : EDGE_DIR_POS);
		PutStatusDir_UB(GetStatusDir_BR() == EDGE_DIR_POS ? EDGE_DIR_NEG : EDGE_DIR_POS);
		PutStatusDir_BR(GetStatusDir_DB() == EDGE_DIR_POS ? EDGE_DIR_NEG : EDGE_DIR_POS);
		PutStatusDir_DB(buffer == EDGE_DIR_POS ? EDGE_DIR_NEG : EDGE_DIR_POS);
	}

	void c_Edges::e_B2() // Movement B2
	{
		S64 buffer = GetStatusPos_BL();
		PutStatusPos_BL(GetStatusPos_BR());
		PutStatusPos_BR(buffer);
	
		buffer = GetStatusDir_BL();
		PutStatusDir_BL(GetStatusDir_BR());
		PutStatusDir_BR(buffer);
	
		buffer = GetStatusPos_UB();
		PutStatusPos_UB(GetStatusPos_DB());
		PutStatusPos_DB(buffer);
	
		buffer = GetStatusDir_UB();
		PutStatusDir_UB(GetStatusDir_DB());
		PutStatusDir_DB(buffer);
	}
	
	void c_Edges::e_Bp() // Movement B'
	{
		S64 buffer = GetStatusPos_BR();
		PutStatusPos_BR(GetStatusPos_UB());
		PutStatusPos_UB(GetStatusPos_BL());
		PutStatusPos_BL(GetStatusPos_DB());
		PutStatusPos_DB(buffer);
	
		buffer = GetStatusDir_BR();
		PutStatusDir_BR(GetStatusDir_UB() == EDGE_DIR_POS ? EDGE_DIR_NEG : EDGE_DIR_POS);
		PutStatusDir_UB(GetStatusDir_BL() == EDGE_DIR_POS ? EDGE_DIR_NEG : EDGE_DIR_POS);
		PutStatusDir_BL(GetStatusDir_DB() == EDGE_DIR_POS ? EDGE_DIR_NEG : EDGE_DIR_POS);
		PutStatusDir_DB(buffer == EDGE_DIR_POS ? EDGE_DIR_NEG : EDGE_DIR_POS);
	}
	
	void c_Edges::e_R() // Movement R
	{
		S64 buffer = GetStatusPos_FR();
		PutStatusPos_FR(GetStatusPos_DR());
		PutStatusPos_DR(GetStatusPos_BR());
		PutStatusPos_BR(GetStatusPos_UR());
		PutStatusPos_UR(buffer);
	
		buffer = GetStatusDir_FR();
		PutStatusDir_FR(GetStatusDir_DR());
		PutStatusDir_DR(GetStatusDir_BR());
		PutStatusDir_BR(GetStatusDir_UR());
		PutStatusDir_UR(buffer);
	}
	
	void c_Edges::e_R2() // Movement R2
	{
		S64 buffer = GetStatusPos_FR();
		PutStatusPos_FR(GetStatusPos_BR());
		PutStatusPos_BR(buffer);
	
		buffer = GetStatusDir_FR();
		PutStatusDir_FR(GetStatusDir_BR());
		PutStatusDir_BR(buffer);
	
		buffer = GetStatusPos_UR();
		PutStatusPos_UR(GetStatusPos_DR());
		PutStatusPos_DR(buffer);
	
		buffer = GetStatusDir_UR();
		PutStatusDir_UR(GetStatusDir_DR());
		PutStatusDir_DR(buffer);
	}
	
	void c_Edges::e_Rp() // Movement R'
	{
		S64 buffer = GetStatusPos_FR();
		PutStatusPos_FR(GetStatusPos_UR());
		PutStatusPos_UR(GetStatusPos_BR());
		PutStatusPos_BR(GetStatusPos_DR());
		PutStatusPos_DR(buffer);
	
		buffer = GetStatusDir_FR();
		PutStatusDir_FR(GetStatusDir_UR());
		PutStatusDir_UR(GetStatusDir_BR());
		PutStatusDir_BR(GetStatusDir_DR());
		PutStatusDir_DR(buffer);
	}
	
	void c_Edges::e_L() // Movement L
	{
		S64 buffer = GetStatusPos_FL();
		PutStatusPos_FL(GetStatusPos_UL());
		PutStatusPos_UL(GetStatusPos_BL());
		PutStatusPos_BL(GetStatusPos_DL());
		PutStatusPos_DL(buffer);
	
		buffer = GetStatusDir_FL();
		PutStatusDir_FL(GetStatusDir_UL());
		PutStatusDir_UL(GetStatusDir_BL());
		PutStatusDir_BL(GetStatusDir_DL());
		PutStatusDir_DL(buffer);
	}
	
	void c_Edges::e_L2() // Movement L2
	{
		S64 buffer = GetStatusPos_FL();
		PutStatusPos_FL(GetStatusPos_BL());
		PutStatusPos_BL(buffer);
	
		buffer = GetStatusDir_FL();
		PutStatusDir_FL(GetStatusDir_BL());
		PutStatusDir_BL(buffer);
	
		buffer = GetStatusPos_UL();
		PutStatusPos_UL(GetStatusPos_DL());
		PutStatusPos_DL(buffer);
	
		buffer = GetStatusDir_UL();
		PutStatusDir_UL(GetStatusDir_DL());
		PutStatusDir_DL(buffer);
	}
	
	void c_Edges::e_Lp() // Movement L'
	{
		S64 buffer = GetStatusPos_FL();
		PutStatusPos_FL(GetStatusPos_DL());
		PutStatusPos_DL(GetStatusPos_BL());
		PutStatusPos_BL(GetStatusPos_UL());
		PutStatusPos_UL(buffer);
	
		buffer = GetStatusDir_FL();
		PutStatusDir_FL(GetStatusDir_DL());
		PutStatusDir_DL(GetStatusDir_BL());
		PutStatusDir_BL(GetStatusDir_UL());
		PutStatusDir_UL(buffer);
	}
	
    // Get mask for check if edges in given list of pieces are in solve conditions
	S64 c_Edges::GetMasksSolvedEdges(const std::vector<Edges>& p_list)
	{
		S64 e_mask = 0ull;
		
		for (auto P : p_list)
		{
			switch (P)
			{
				case Edges::FR: e_mask |= EMASK_FR; break;
				case Edges::FL: e_mask |= EMASK_FL; break;
				case Edges::BL: e_mask |= EMASK_BL; break;
				case Edges::BR: e_mask |= EMASK_BR; break;
				case Edges::UF: e_mask |= EMASK_UF; break;
				case Edges::UL: e_mask |= EMASK_UL; break;
				case Edges::UB: e_mask |= EMASK_UB; break;
				case Edges::UR: e_mask |= EMASK_UR; break;
				case Edges::DF: e_mask |= EMASK_DF; break;
				case Edges::DL: e_mask |= EMASK_DL; break;
				case Edges::DB: e_mask |= EMASK_DB; break;
				case Edges::DR: e_mask |= EMASK_DR; break;
				default: break;
			}
		}

		return e_mask;
	}

	// Check if the given edge is in the given layer
	bool c_Edges::IsEdgeInLayer(const Edges P, const Layers L) const
	{
		switch (L)
		{
		case Layers::U: return IsEdgeInLayerU(P);
		case Layers::D: return IsEdgeInLayerD(P);
		case Layers::F: return IsEdgeInLayerF(P);
		case Layers::B: return IsEdgeInLayerB(P);
		case Layers::R: return IsEdgeInLayerR(P);
		case Layers::L: return IsEdgeInLayerL(P);
		case Layers::M: return IsEdgeInLayerM(P);
		case Layers::E: return IsEdgeInLayerE(P);
		case Layers::S: return IsEdgeInLayerS(P);
		default: return false;
		}
	}
}

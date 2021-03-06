
#pragma once

#include "../Entities/Minecart.h"





class cItemMinecartHandler :
	public cItemHandler
{
	typedef cItemHandler super;

public:
	cItemMinecartHandler(int a_ItemType) :
		super(a_ItemType)
	{
	}

	virtual bool IsPlaceable(void) override
	{
		return true;
	}


	virtual bool OnPlayerPlace(
		cWorld & a_World, cPlayer & a_Player, const cItem & a_EquippedItem,
		int a_BlockX, int a_BlockY, int a_BlockZ, eBlockFace a_BlockFace,
		int a_CursorX, int a_CursorY, int a_CursorZ
	) override
	{
		// Check that there's rail in there:
		BLOCKTYPE Block = a_World.GetBlock(a_BlockX, a_BlockY, a_BlockZ);
		switch (Block)
		{
			case E_BLOCK_MINECART_TRACKS:
			case E_BLOCK_POWERED_RAIL:
			case E_BLOCK_DETECTOR_RAIL:
			case E_BLOCK_ACTIVATOR_RAIL:
			{
				// These are allowed
				break;
			}
			default:
			{
				LOGD("Used minecart on an unsuitable block %d (%s)", Block, ItemTypeToString(Block).c_str());
				return false;
			}
		}

		double x = static_cast<double>(a_BlockX) + 0.5;
		double y = static_cast<double>(a_BlockY) + 0.5;
		double z = static_cast<double>(a_BlockZ) + 0.5;

		if (a_World.SpawnMinecart(x, y, z, m_ItemType) == cEntity::INVALID_ID)
		{
			return false;
		}

		if (!a_Player.IsGameModeCreative())
		{
			a_Player.GetInventory().RemoveOneEquippedItem();
		}
		return true;
	}

} ;

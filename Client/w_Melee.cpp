#include "w_Melee.h"

w_Melee::w_Melee(int& facing)
{
	facing_ = facing;
}

w_Melee::~w_Melee()
{

}

void w_Melee::OnAttack(Square& hitBox, Vector2& pos, float size, int& facing, char* keys, char* preKeys)
{
	if (Novice::IsTriggerMouse(0) && keys[DIK_S])
	{
		if (facing == RIGHT)
		{
			hitBox = MakeSquare({ pos.x + 48, pos.y + 48 }, { size,size });
			hitBox_ = MakeSquare({ pos.x + 48, pos.y + 48 }, { size,size });
			Draw(pos);
		}
		else if (facing == LEFT)
		{
			hitBox = MakeSquare({ pos.x - 32.0f, pos.y + 48 }, { size,size });
			hitBox_ = MakeSquare({ pos.x - 32.0f, pos.y + 48 }, { size,size });
			Draw({ pos.x - 28.0f, pos.y });
		}
	}
	else if (Novice::IsTriggerMouse(0) && !keys[DIK_S])
	{
		if (facing == RIGHT)
		{
			hitBox = MakeSquare({ pos.x + 48, pos.y + 16 }, { size,size });
			hitBox_ = MakeSquare({ pos.x + 48, pos.y + 16 }, { size,size });
			Draw(pos);
		}
		else if (facing == LEFT)
		{
			hitBox = MakeSquare({ pos.x - 32.0f, pos.y + 16 }, { size,size });
			hitBox_ = MakeSquare({ pos.x - 32.0f, pos.y + 16 }, { size,size });
			Draw({ pos.x - 28.0f, pos.y });
		}
	}
	
}

void w_Melee::Draw(Vector2 pos)
{
	Novice::DrawBox(hitBox_.topLeft.x, hitBox_.topLeft.y, 32, 32, 0, RED, kFillModeWireFrame);
}
	

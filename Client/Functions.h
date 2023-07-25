#include"..\[Server]\Common.h"
static Square MakeSquare(Vector2 pos, Vector2 size)
{
	Square square;
	square.topLeft = pos;
	square.topRight.x = pos.x + size.x;
	square.topRight.y = pos.y;
	square.bottomLeft.x = pos.x;
	square.bottomLeft.y = pos.y + size.y;
	square.bottomRight.x = pos.x + size.x;
	square.bottomRight.y = pos.y + size.y;

	return square;
}

static bool s_s_CollisionCheck(Square obj1, Square obj2)
{
	if (obj1.topLeft.x <= obj2.topRight.x && obj1.bottomRight.x >= obj2.topLeft.x)
	{
		if (obj1.topLeft.y <= obj2.bottomLeft.y && obj1.bottomLeft.y >= obj2.topLeft.y)
		{
			return true;
		}
	}
	return false;
}

static void DrawHpBar(Vector2 pos, int length, int width, Hp& hp)
{
	float hpBar;
	hpBar = (length / hp.maxHp) * hp.currentHp;

	if (hpBar <= 0)
	{
		hpBar = 0;
	}

	if (hp.saveHp >= hpBar)
	{
		hp.saveHp--;
	}

	Novice::DrawBox(pos.x, pos.y, hp.saveHp, width, 0, 0x8B0000FF, kFillModeSolid);
	Novice::DrawBox(pos.x, pos.y, hpBar, width, 0, RED, kFillModeSolid);
	Novice::DrawBox(pos.x, pos.y, length, width, 0, WHITE, kFillModeWireFrame);
}
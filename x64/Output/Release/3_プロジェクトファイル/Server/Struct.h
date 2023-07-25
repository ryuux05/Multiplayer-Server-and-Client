struct Matrix3x3 {
	float m[3][3];
};

struct Matrix2x2 {
	float m[2][2];
};
struct Vector2 {
	float x, y;
};

struct Hp {
	Vector2 pos;
	float barPercentage;
	float currentHp = 10;
	float maxHp;
	float saveHp;
	float receivedDamage;
	int cooldown;	
};

struct Square {
	Vector2 topLeft;
	Vector2 bottomLeft;
	Vector2 topRight;
	Vector2 bottomRight;
};

struct Square9
{
	Vector2 topLeft;
	Vector2 bottomLeft;
	Vector2 topRight;
	Vector2 bottomRight;
	Vector2 middleTop;
	Vector2 middleBot;
	Vector2 middleLeft;
	Vector2 middleRight;
	Vector2 middle;
};

struct ShakeElement
{
	Vector2 shakePos;
	bool IsShaking;
	int shakeTime;
};

struct Bullet
{
	int bulletRange;
	int bulletSpeed;
	int bulletDamage;
	int w_Damage;
	int w_Speed;
	Vector2 w_Pos;
	Vector2 w_Base_Pos;
	bool isShooting[2] = { false,false };
};

struct AnimationObject
{
	int maxFrame;
	int resetFrame;
	int currentFrame;
	int timeCount;
	int frameTime;
	int graph;
	bool repeat;
};

struct Melee
{
	Square hitBox_;
};

enum face
{
	LEFT,
	RIGHT,
};


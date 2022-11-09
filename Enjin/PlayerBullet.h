#include"Rock.h"

using namespace DirectX;
class PlayerBullet
{
public:
	PlayerBullet();
	~PlayerBullet();
	void Initialize(Input* input, Mouse* mouse,Rock*rock);

	void Update();

	void Draw();

	void Move();

	void Create(XMFLOAT3 pos ,int key);

	void PlusNumber();

	void Hit();

	int GetBFlag() { return flag[number]; };
	XMFLOAT3 GetBPosition() { return position[number]; };

#define PBULLET_MAX 50
private:
	Input* input = nullptr;
	Mouse* mouse = nullptr;
	Model* model = nullptr;
	Rock* rock = nullptr;
	Object3d* bullet[PBULLET_MAX];


	int flag[PBULLET_MAX];

	XMFLOAT3 position[PBULLET_MAX];
	XMFLOAT3 rotation = { 0,-90,0 };

	int homingTime[PBULLET_MAX];
	int homingCount[PBULLET_MAX];

	float dx[PBULLET_MAX];
	float dy[PBULLET_MAX];
	float dz[PBULLET_MAX];
	float da[PBULLET_MAX];
	float L[PBULLET_MAX];

	float speed = 7;
	int attackCT = 0;

	int number = 0;
};


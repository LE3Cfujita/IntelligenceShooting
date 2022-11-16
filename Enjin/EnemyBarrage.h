#include"GameObject.h"
using namespace DirectX;

class EnemyBarrage : public GameObject
{
public:
	EnemyBarrage();
	~EnemyBarrage();
	void Initialize();

	void Update();

	void Draw();

	void Create(XMFLOAT3 ePos);

	void Hit();

	void Move();

private:
#define EBULLET_MAX 50

	//‘_‚Á‚ÄŒ‚‚Á‚Ä‚­‚é
	Model* model = nullptr;
	//’e–‹
	Object3d* bullet = nullptr;

};


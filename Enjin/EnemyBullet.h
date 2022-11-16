#include"GameObject.h"
using namespace DirectX;
class EnemyBullet : public GameObject
{
public:
	EnemyBullet();
	~EnemyBullet();
	void Initialize();

	void Update();

	void Draw();

	void Create(XMFLOAT3 ePos);

	void Move();

	void Hit();


private:
	//‘_‚Á‚ÄŒ‚‚Á‚Ä‚­‚é
	Model* model = nullptr;
	Object3d* bullet = nullptr;


};


#ifndef PLAYER_CONTROL_H
#define PLAYER_CONTROL_H

#include <sstream>

#include "../Node.h"
#include "../../Utility/TypeID.h"
#include "../../Utility/Component.h"
#include "../Scripts.h"
#include "../Components.h"
#include "../../Utility/Math/Vector3.h"

enum class P_STATE
{
	IDLE_R = 0,
	IDLE_L,
	MOVE_L,
	MOVE_R,
	JUMP,
	FALL, 
	ATTACK_L,
	ATTACK_R,
	AIR_ATTACK,
	HIT_L,
	HIT_R,
	DYING_L,
	DYING_R,
};

class KinemeticBody;
class Sprite;
class ColInfo;
class Collider;
class Spline;
class PlayerController : public Node, public TypeID<PlayerController>, public Component
{
public:
	PlayerController(std::string name = "PlayerController");
	~PlayerController();

	virtual void Start();
	virtual void Update(double dt);
	virtual void End();
	
	PlayerController* SetTerrain(Spline * s);	
	void TakeDamage(int dmg);	
	int DamageDealt();

	bool IsDead();
	void Reset();


	void SetHealth(int h);

private:
	KinemeticBody* kinb;
	Sprite* sprite;
	Collider* attackRight, *attackLeft, *attackAir;
	Collider* hitbox;
	Spline* terrain;
	
	P_STATE currState, nextState;

	Vector3 moveSpeed;
	int direction;
	double jumpTimer, attackTimer, hitTimer, deadTimer;	
	int health;
	int damage;
    int speedincrease;

	bool walking;
	

	void TryChangeState(P_STATE state);
	void ChangeState();

	float GetTerrainHeight();

	bool CanMove();
	bool addHealth;
	bool OnGround(float offset = 0, bool exact = false);
	
	int	GetHealth();
	void Move(float inputX);
	void Friction();
	void Jump();
	void Fall();
	void Constrain();
	void Attack(double dt);
	void Die(double dt);
	void Hit(double dt);

	void PrintState();
};

#endif
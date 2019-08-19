#ifndef SCENE_PLAYER_H
#define SCENE_PLAYER_H

#include "../Scene.h"

//plain scene to show how to inherit properly
class ColorSpot;
class Player;
class ScenePlayer : public Scene  //alright to inherit because I won't need to Get it
{
public:
	ScenePlayer(std::string name = "ScenePlayer");
	~ScenePlayer();

	virtual void Start();
	virtual void Update(double dt);
	virtual void End();

	GameObj* GetPlayer();
	void SetTerrainHeight(float h);

	void Render();
protected:
	ColorSpot* colorSpot;
	Player* playerScript;
};

#endif
#include "MapScene.h"

#include "../GameObj.h"
#include "../Components/Renderable.h"
#include "../Scripts/DebugText.h"
#include "../Scripts/MapGenerator.h"
#include "../../Utility/Math/Spline.h"
#include "../Components/Sprite.h"

MapScene::MapScene(std::string name)
	: Scene(name)
{
}

MapScene::~MapScene()
{
}

void MapScene::Start()
{	
	//create gameobjects	
	//AddChild<GameObj>("axes");
	AddChild<GameObj>("debug_text");
	AddChild<GameObj>("MapGenerator");
	//add & set up components and scripts	
	//GetChild<GameObj>("axes")->AddComp<Renderable>()->AttachMesh(mg->GetCachedMesh("axes"))->AttachMaterial(mg->GetCachedMaterial("default"));
	GetChild<GameObj>("debug_text")->AddScript<DebugText>();	
	mapGen = GetChild<GameObj>("MapGenerator")->AddScript<MapGenerator>();
	mapGen->SetCamera(camera);
	Scene::Start();
}

void MapScene::Update(double dt)
{	
	Scene::Update(dt);	
}

void MapScene::End()
{
	Scene::End();
}

void MapScene::Render()
{		
	//If got diff render pipeline

	//for (auto r : *renderables)
	//{
	//	r->Render();
	//}
	
	//OR

	Scene::Render();
}

void MapScene::SetCamera(Camera * camera)
{
	this->camera = camera;
}

Spline * MapScene::GetTerrain()	
{	
	return mapGen->GetCurrChunk()->GetSpline();
}

void MapScene::ChangeToSaturated()
{
	//change all chunks to render pass post fx, and set hsv to 1
	for (int i = 0; i < mapGen->mapSize; ++i)
	{
		mapGen->chunkGO[i]->GetComp<Chunk>()->sprite->SetHSV(-1, 1, -1)->SetRenderPass(RENDER_PASS::POST_FX);
	}
}

void MapScene::ChangeToDeSat()
{
	//change all chunks to render pass geo
	for (int i = 0; i < mapGen->mapSize; ++i)
	{
		mapGen->chunkGO[i]->GetComp<Chunk>()->sprite->SetRenderPass(RENDER_PASS::GEO);
	}
}

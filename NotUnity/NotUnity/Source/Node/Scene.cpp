#include "Scene.h"
#include "GameObj.h"

#include <vector>
#include <sstream>

#include "Manager/MgrGraphics.h"
#include "Manager/MgrGameObj.h"
#include "Components/Camera.h"
#include "Components/Renderable.h"
#include "Components/Text.h"
#include "Scripts/DebugText.h"
#include "GameObj.h"

Scene::Scene(std::string name) 
	: Node(name)
	, mg(nullptr)
	, mgo(nullptr)
	, renderables(nullptr)
{
}

Scene::~Scene()
{
}

void Scene::Start()
{		
	//get singleton references
	mg = MgrGraphics::Instance();
	mgo = MgrGameObj::Instance();
	//get go list references
	renderables = mgo->GetRenderables();

	//create gameobjects
	CreateGo("mainCam");
	CreateGo("axes");
	CreateGo("debug_text");
	//add & set up components and scripts
	GetGo("mainCam")->AddComp<Camera>()->SetMode(Camera::DEBUG);
	GetGo("axes")->AddComp<Renderable>()->AttachMesh(mg->GetCachedMesh("axes"))->AttachMaterial(mg->GetCachedMaterial("default"));	
	GetGo("debug_text")->AddScript<DebugText>();
	//attach camera
	mg->AttachView(GetChild<GameObj>("mainCam")->GetComp<Camera>()->GetViewMtx());
	
	Node::Start();
}

void Scene::Update(double dt)
{
	Node::Update(dt);
	this->Render();
}

void Scene::End()
{
	Node::End();
}

void Scene::Render()
{		
	for (auto r : *renderables)
	{
		r->Render();
	}
}

GameObj* Scene::CreateGo(std::string name)
{
	return mgo->CreateGameObj(name, this);
}

GameObj* Scene::GetGo(std::string name)
{
	return GetChild<GameObj>(name);
}

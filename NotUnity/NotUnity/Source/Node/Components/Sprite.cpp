#include "Sprite.h"
#include "../Manager/MgrGraphics.h"
#include "../../Utility/Math/MyMath.h"

Sprite::Sprite(std::string name) : Renderable(name)
{
	currFrame = 0;
	currTime = 0.0;
	selectedAnim = 0;
	SetAnimation(0, 0, 1, false);	
}

Sprite::~Sprite()
{
}

void Sprite::Start()
{
	Renderable::Start();
}

void Sprite::Update(double dt)
{		
	if (anims[selectedAnim]->play)
	{
		currTime += dt;		
		currFrame = Math::Min(anims[selectedAnim]->endFrame, anims[selectedAnim]->startFrame + (int)(currTime / frameTime));

		if (currTime >= anims[selectedAnim]->animTime)
		{
			if (anims[selectedAnim]->repeat)
			{
				currTime = 0.f;
				currFrame = anims[selectedAnim]->startFrame;
			}			
			else
				anims[selectedAnim]->play = false;
		}
	}

	Renderable::Update(dt);
}

void Sprite::End()
{
	Renderable::End();
}

void Sprite::Render()
{	
	if (!m_active || !mesh || mesh->vao < 1) return;

	//get handle for MgrGraphics
	MgrGraphics* mgrG = MgrGraphics::Instance();
	
	if (shader != mgrG->GetCurrShader())
		mgrG->UseShader(shader);

	//set uniforms for transform
	mgrG->SetUniform("model", t->GetModel());

	//set uniforms for material
	mgrG->SetUniform("material.albedo", material->albedo);
	for (int i = 0; i <= Material::COLOR7; ++i)
	{
		std::string cast = "material.colorMapEnabled[" + std::to_string(i) + "]";
		mgrG->SetUniform(cast.c_str(), material->maps[i] > 0 && i == selectedAnim);
	}
	glBindTexture(GL_TEXTURE_2D, material->maps[Material::COLOR0 + selectedAnim]);

	DrawMesh(6, 6 * currFrame);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Sprite* Sprite::SetAnimation(int idx, int numFrames, float animTime, bool repeat)
{
	if (anims[idx] == nullptr)
		anims[idx] = new Animation(0, numFrames - 1, repeat, animTime, false);
	else
	{
		anims[idx]->startFrame = 0;
		anims[idx]->endFrame = numFrames - 1;
		anims[idx]->repeat = repeat;
		anims[idx]->animTime = animTime;
		anims[idx]->play = false;
	}
	return this;
}

Sprite* Sprite::SwitchAnimation(int idx)
{
	selectedAnim = idx;
	currFrame = 0;
	currTime = 0.0;	
	frameTime = anims[selectedAnim]->animTime / Math::Max(1, anims[selectedAnim]->endFrame - anims[selectedAnim]->startFrame + 1);
	return this;
}

Sprite* Sprite::PlayAnimation()
{
	anims[selectedAnim]->play = true;
	return this;
}

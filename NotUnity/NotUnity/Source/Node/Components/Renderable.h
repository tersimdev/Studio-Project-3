#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "../Node.h"
#include "../../Utility/TypeID.h"
#include "../../Utility/Graphics/Mesh.h"
#include "../../Utility/Graphics/Material.h"
#include "Transform.h"

class MgrGraphics;
class Renderable : public Node, public TypeID<Renderable>
{
public:
	Renderable(std::string name = "Renderable") : Node(name) {}
	~Renderable() {}
	
	virtual void Start();
	virtual void Update(double dt);
	virtual void End();

	void Render();

	Renderable* AttachMesh(Mesh* mesh);
	Renderable* AttachMaterial(Material* material);
	Renderable* AttachTransform(Transform* t);
	Renderable* SelectShader(MgrGraphics::SHADER shader);

protected:
	Mesh* mesh;
	Material* material;
	Transform* t;
	MgrGraphics::SHADER shader;

	void DrawMesh();
	void DrawMesh(unsigned count, unsigned offset);
};

#endif
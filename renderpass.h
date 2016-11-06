#ifndef RENDER_PASS_H
#define RENDER_PASS_H

#include <engine/core/node.h>
#include <engine/graphics/camera.h>


class RenderPass : public Node{
private:

	GLuint clearFlags;
	double clearColor[4];

protected:

    Camera* camera;
    string cameraName;


    virtual void OnSetSettings();
    virtual void OnGlobalRequest(Node* globalNodeRef,string name);


public:

    RenderPass();
	virtual void Update();
	GLuint ClearFlags();
	Camera* GetCamera();
	double* ClearColor();

};

#endif // RENDER_PASS_H

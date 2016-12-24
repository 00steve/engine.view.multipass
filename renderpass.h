#ifndef RENDER_PASS_H
#define RENDER_PASS_H


#define GLFW_INCLUDE_GLU
#define GLFW_INCLUDE_GLCOREARB
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

#include <engine/core/node.h>
#include <engine/graphics/camera.h>
#include <engine/graphics/shader.h>
#include <engine/core/stringutil.h>

class RenderPass : public Node{
private:

	GLuint clearFlags;
	double clearColor[4];
	Shader* shader;

protected:

    Camera* camera;
    string cameraName;

    GLuint glBlendSFactor,glBlendDFactor;
    bool glBlendEnable;

    virtual void OnSetSettings();
    virtual void OnGlobalRequest(Node* globalNodeRef,string name);

    static GLuint GetBlendModeGLuint(string blendMode);


public:

    RenderPass();
    ~RenderPass();
	virtual void Update();
	GLuint ClearFlags();
	Camera* GetCamera();
	double* ClearColor();
    Shader* GetShader();

    void PreRender();
    void PostRender();
};

#endif // RENDER_PASS_H

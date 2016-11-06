#ifndef ENGINE_VIEW_MULTIPASS_H
#define ENGINE_VIEW_MULTIPASS_H


#define GLEW_STATIC
#include <GL/glu.h>

#include <engine/graphics/view.h>
#include "renderpass.h"


class Multipass : public View{
private:

    double3 clearColor;
    double clearAlpha;

    List<RenderPass*> passes;

protected:

    virtual void OnSetSettings();


public:

    Multipass();

	virtual void Update();
    virtual void Draw();

    void SetCamera();


    void SetTargetNode();


};



#endif // ENGINE_VIEW_MULTIPASS_H

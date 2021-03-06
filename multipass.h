#ifndef ENGINE_VIEW_MULTIPASS_H
#define ENGINE_VIEW_MULTIPASS_H

#include <GL/gl.h>
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
	virtual void Update();
    virtual void Draw();

};



#endif // ENGINE_VIEW_MULTIPASS_H

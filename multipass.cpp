#include "multipass.h"


void Multipass::OnSetSettings(){
    VarMap settings = Settings();
    if(settings.IsSet("clear-color")){
        List<double> clearVals = settings.get<List<double> >("clear-color");
        if(clearVals.GetCount() == 4){
            clearColor = double3(clearVals[0],clearVals[1],clearVals[2]);
            clearAlpha = clearVals[3];
        }
    }
    VarMap passSettings = settings.GetGroup("passes");
    List<string> passNames = passSettings.GroupNames();
    for(int i=0;i<passNames.GetCount();i++){
        RenderPass *rp = new RenderPass();
        CopyGlobalRefsTo(rp);
        rp->Settings(passSettings.GetGroup(passNames[i]));
        passes.Push(rp);
        Link(rp);
    }
    View::OnSetSettings();
}

void Multipass::Update(){
	for(int i=0;i<passes.GetCount();i++){
		passes[i]->Update();
	}
}

void Multipass::Draw(){
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glEnable(GL_SCISSOR_TEST);
	glScissor(bottomLeft.x,bottomLeft.y,dimensions.x,dimensions.y);
	glViewport(bottomLeft.x,bottomLeft.y,dimensions.x,dimensions.y);
	for(int i=0;i<passes.GetCount();i++){
		glClearColor(passes[i]->ClearColor()[0],
					passes[i]->ClearColor()[1],
					passes[i]->ClearColor()[2],
					passes[i]->ClearColor()[3]);
        glClear(passes[i]->ClearFlags());//had a check for ClearFlags(), which I think meant not 0, so, it's dumb
        glPushMatrix();
            if(passes[i]->GetCamera()){
                passes[i]->GetCamera()->TranslateView();
            } else {
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
            }
            glMatrixMode(GL_MODELVIEW);
            glEnable(GL_DEPTH_TEST);
            glCullFace(GL_BACK);
            glEnable(GL_CULL_FACE);
                passes[i]->PreRender();
                if(renderSubject) renderSubject->Draw();
                passes[i]->PostRender();
        glPopMatrix();
	}
    glPopAttrib();
}

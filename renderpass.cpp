#include "renderpass.h"


RenderPass::RenderPass() :
    clearFlags(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT),
    clearColor{0,0,0,1},
    camera(NULL){
}


void RenderPass::OnSetSettings(){
    VarMap settings = Settings();

    if(settings.IsSet("camera")){
        cout << " - renderpass wants camera " << settings.get<string>("camera");
		cameraName = settings.get<string>("camera");
        GlobalRequest(cameraName);
    }

    if(settings.IsSet("clear")){
		List<string> clearFlagStrings = settings.GetStringList("clear");
		clearFlags = 0;
		for(int i=0;i<clearFlagStrings.GetCount();i++){
			if(clearFlagStrings[i] == "color"){
				clearFlags += GL_COLOR_BUFFER_BIT;
			} else if (clearFlagStrings[i] == "depth"){
				clearFlags += GL_DEPTH_BUFFER_BIT;
			}
		}
    }

    if(settings.IsSet("clear-color")){
		List<double> clearColors = settings.get<List<double> >("clear-color");
		if(clearColors.GetCount() == 4){
			clearColor[0] = clearColors[0];
			clearColor[1] = clearColors[1];
			clearColor[2] = clearColors[2];
			clearColor[3] = clearColors[3];
		} else if (clearColors.GetCount() == 3){
			clearColor[0] = clearColors[0];
			clearColor[1] = clearColors[1];
			clearColor[2] = clearColors[2];
			clearColor[3] = 1;
		} else {
			cout << "incorrect number of values for clear-color\n";
		}
    }


    Node::OnSetSettings();
}
void RenderPass::OnGlobalRequest(Node* globalNodeRef,string name){
	if(name == cameraName){
		camera = (Camera*)globalNodeRef;
        Link(globalNodeRef);
        cout << " - renderpass got camera " << name << endl;
		//camera->Init(_pipeRes,_targetNode);
	}
}

void RenderPass::Update(){
	if(camera) camera->Update();
}

GLuint RenderPass::ClearFlags(){
	return clearFlags;
}


double* RenderPass::ClearColor(){
	return clearColor;
}

Camera* RenderPass::GetCamera(){
	return camera;
}

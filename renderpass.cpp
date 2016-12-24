#include "renderpass.h"


RenderPass::RenderPass() :
    clearFlags(GL_COLOR_BUFFER_BIT),// | GL_DEPTH_BUFFER_BIT
    clearColor{0,0,0,1},
    shader(NULL),
    camera(NULL){
}

RenderPass::~RenderPass(){
    if(shader) delete shader;
}

void RenderPass::OnSetSettings(){
    VarMap settings = Settings();

    if(settings.IsSet("camera")){
        //cout << " - renderpass wants camera " << settings.get<string>("camera");
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

    if(settings.IsSet("blend")){
        string blend = settings.get<string>("blend");
        string sfactor,dfactor;
        splitStringAtChar(blend,sfactor, dfactor,',',1);
        sfactor = stringTrim(sfactor);
        dfactor = stringTrim(dfactor);
        glBlendSFactor = GetBlendModeGLuint(sfactor);
        glBlendDFactor = GetBlendModeGLuint(dfactor);
        glBlendEnable = true;

    } else {
        glBlendEnable = false;
    }

    if(settings.IsSet("shader")){
        shader = new Shader(settings.get<string>("shader"));
    }


    Node::OnSetSettings();
}
void RenderPass::OnGlobalRequest(Node* globalNodeRef,string name){
	if(name == cameraName){
		camera = (Camera*)globalNodeRef;
        Link(globalNodeRef);
        //cout << " - renderpass got camera " << name << endl;
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

Shader* RenderPass::GetShader(){
    return shader;
}


void RenderPass::PreRender(){
    if(shader->Valid()){
        glUseProgram(shader->Program());
    } else {
        glUseProgram(0);
    }
    if(glBlendEnable){
        glEnable(GL_BLEND);
        glBlendFunc(glBlendSFactor,glBlendDFactor);
    }
}
void RenderPass::PostRender(){
}


GLuint RenderPass::GetBlendModeGLuint(string blendMode){
    if(blendMode == "GL_ZERO")                          { return GL_ZERO; }
    else if(blendMode == "GL_ONE")                      { return GL_ONE; }
    else if(blendMode == "GL_SRC_COLOR")                { return GL_SRC_COLOR; }
    else if(blendMode == "GL_ONE_MINUS_SRC_COLOR")      { return GL_ONE_MINUS_SRC_COLOR; }
    else if(blendMode == "GL_DST_COLOR")                { return GL_DST_COLOR; }
    else if(blendMode == "GL_ONE_MINUS_DST_COLOR")      { return GL_ONE_MINUS_DST_COLOR; }
    else if(blendMode == "GL_SRC_ALPHA")                { return GL_SRC_ALPHA; }
    else if(blendMode == "GL_ONE_MINUS_SRC_ALPHA")      { return GL_ONE_MINUS_SRC_ALPHA; }
    else if(blendMode == "GL_DST_ALPHA")                { return GL_DST_ALPHA; }
    else if(blendMode == "GL_ONE_MINUS_DST_ALPHA")      { return GL_ONE_MINUS_DST_ALPHA; }
    else if(blendMode == "GL_CONSTANT_COLOR	")          { return GL_CONSTANT_COLOR; }
    else if(blendMode == "GL_ONE_MINUS_CONSTANT_COLOR") { return GL_ONE_MINUS_CONSTANT_COLOR; }
    else if(blendMode == "GL_CONSTANT_ALPHA")           { return GL_CONSTANT_ALPHA; }
    else if(blendMode == "GL_ONE_MINUS_CONSTANT_ALPHA") { return GL_ONE_MINUS_CONSTANT_ALPHA; }
    else if(blendMode == "GL_SRC_ALPHA_SATURATE")       { return GL_SRC_ALPHA_SATURATE; }
    else if(blendMode == "GL_SRC1_COLOR")               { return GL_SRC1_COLOR; }
    else if(blendMode == "GL_ONE_MINUS_SRC1_COLOR")     { return GL_ONE_MINUS_SRC1_COLOR; }
    else if(blendMode == "GL_SRC1_ALPHA")               { return GL_SRC1_ALPHA; }
    else if(blendMode == "GL_ONE_MINUS_SRC1_ALPHA")     { return GL_ONE_MINUS_SRC1_ALPHA; }
    else                                                { return 0;}
}

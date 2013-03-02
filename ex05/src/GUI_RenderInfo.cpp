#include "GUI_RenderInfo.h"


GUI_RenderInfo::GUI_RenderInfo()
{
}

GUI_RenderInfo::~GUI_RenderInfo()
{
}

void GUI_RenderInfo::Init(int windowWidth, int windowHeight)
{
	textRenderer = std::make_shared<TextRenderer>();
	textRenderer->InitTextRenderer(CreateTextProgram());
	this->windowHeight = windowHeight;
	this->windowWidth = windowWidth;
}

std::shared_ptr<GLUtils::Program> GUI_RenderInfo::CreateTextProgram()
{
	std::shared_ptr<GLUtils::Program> program;
	std::string fs_src = readFile("shaders/text.frag");
	std::string vs_src = readFile("shaders/text.vert");

	//Compile shaders, attach to program object, and link
	program.reset(new Program(vs_src, fs_src));
	program->use();
	program->disuse();
	return program;
}

void GUI_RenderInfo::Render()
{
	for(auto i = textMap.begin(); i != textMap.end(); i++)
		if(i->second.show)
			textRenderer->RenderText(i->second.text);
}

void GUI_RenderInfo::CreateText( std::string text, glm::vec2 pos, bool show )
{
	Text t = textRenderer->GenerateText(text, "calibri", pos.x, pos.y, ScaleX(0.8f), ScaleY(0.8f), glm::vec4(1));
	TextEntry entry; 
	entry.text = t;
	entry.show = show;
	entry.key = text;
	textMap[text] = entry;
}

void GUI_RenderInfo::RemoveText( std::string text )
{
	if(textMap.find(text) != textMap.end())
		textMap.erase(textMap.find(text));
}

void GUI_RenderInfo::ToggleShowText( std::string text )
{
	if(textMap.find(text) != textMap.end())
	{
		TextEntry* e = &textMap.find(text)->second;
		e->show = !e->show;
	}	
}


void GUI_RenderInfo::SetShowText( std::string text, bool show )
{
	if(textMap.find(text) != textMap.end())
	{
		TextEntry* e = &textMap.find(text)->second;
		e->show = show;
	}	
}


float GUI_RenderInfo::ScaleX(float scale)
{
	return scale/windowWidth;
}

float GUI_RenderInfo::ScaleY(float scale)
{
	return scale/windowHeight;
}

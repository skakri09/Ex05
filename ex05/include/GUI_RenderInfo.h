/********************************************************************
    created:    1:3:2013   18:45
    filename:   GUI_RenderInfo.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef GUI_RenderInfo_h__
#define GUI_RenderInfo_h__

#include <boost/filesystem.hpp>
#include <regex>
#include <string>
#include <iostream>
#include <iomanip>
#include <map>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace boost::filesystem;
#include "TextRenderer.h"

using GLUtils::readFile;

struct TextEntry{
	Text text;
	bool show;
	std::string key;
};

class GUI_RenderInfo
{
public:
    GUI_RenderInfo();
    ~GUI_RenderInfo();

	void Init(int windowWidth, int windowHeight);

	void Render();

	void CreateText(std::string text, glm::vec2 pos, bool show = true);

	void RemoveText(std::string text);

	void ToggleShowText(std::string text);

	void SetShowText(std::string text, bool show);
	
protected:

private:
	std::shared_ptr<TextRenderer> textRenderer;
	std::shared_ptr<GLUtils::Program> CreateTextProgram();

	std::map<std::string,TextEntry> textMap;

	float ScaleX(float scale);
	float ScaleY(float scale);

	int windowWidth;
	int windowHeight;
};

#endif // GUI_RenderInfo_h__
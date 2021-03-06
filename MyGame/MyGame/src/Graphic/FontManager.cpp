#include "FontManager.h"


FontManager::~FontManager()
{
	End();
	fontids_.clear();
	fontSizes_.clear();
}

void FontManager::Initialize()
{
	End();
	fontids_.clear();
	fontSizes_.clear();
	SetFontSize(16);
}

void FontManager::AddFont(FONT_ID id,const std::string & filename,const std::string& fontname,int fontSize)
{
	int i=AddFontResourceEx(filename.c_str(), FR_PRIVATE, NULL);
	fontids_[id] = CreateFontToHandle(fontname.c_str(), fontSize, 3, DX_FONTTYPE_ANTIALIASING_8X8, DX_CHARSET_DEFAULT);
	fontSizes_[id] = fontSize;
}


int FontManager::GetFontHandle(FONT_ID id)const
{
	return fontids_.at(id);
}

int FontManager::GetFontSize(FONT_ID id) const
{
	return fontSizes_.at(id);
}

void FontManager::End()
{
	InitFontToHandle();
}

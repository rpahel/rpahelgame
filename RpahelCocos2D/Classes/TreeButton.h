#ifndef __TREEBUTTON_H__
#define __TREEBUTTON_H__

#include "ui/UIButton.h"

class TreeButton : public cocos2d::ui::Button
{
public:
	static TreeButton* create(const cocos2d::Vec2& position = { 0, 0 });

private:
	float lifetime = 3.0f;
	cocos2d::Size tree_size = cocos2d::Size(106, 254);
	float tree_scale = 1.0f;
};

#endif

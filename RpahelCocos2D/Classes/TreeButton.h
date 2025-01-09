#ifndef __TREEBUTTON_H__
#define __TREEBUTTON_H__

#include "ui/UIButton.h"

class TreeButton : public cocos2d::ui::Button
{
public:
	static TreeButton* create(const cocos2d::Vec2& position = { 0, 0 });
	void bindToClickEvent(const std::function<void()>& callback);
	void bindToDeathEvent(const std::function<void()>& callback);

protected:
	void treeClicked();
	void update(float dt);

private:
	const float max_lifetime = 4.0f;
	float lifetime;
	cocos2d::Size tree_size = cocos2d::Size(106, 254);
	float tree_scale = 0.25f;

	std::function<void()> on_click;
	std::function<void()> on_death;
};

#endif

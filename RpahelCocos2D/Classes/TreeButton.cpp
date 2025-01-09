#include "TreeButton.h"
#include "2d/CCActionInterval.h"
#include "2d/CCActionEase.h"

TreeButton* TreeButton::create(const cocos2d::Vec2& position)
{
	TreeButton* tree = new (std::nothrow) TreeButton;
	if (tree && tree->init("sprites/tree_big.png"))
	{
		tree->lifetime = tree->max_lifetime;

		tree->setAnchorPoint({ 0.5f, 0.5f });
		tree->setContentSize(tree->tree_size);
		tree->setScale(0);
		tree->setPosition(position);
		tree->setColor(cocos2d::Color3B(255, 255, 255));

		tree->addTouchEventListener([tree](Ref* sender, Widget::TouchEventType type) {
			switch (type)
			{
				case Widget::TouchEventType::ENDED:
					tree->treeClicked();
					break;

				default:
					break;
			}
			}
		);

		auto bounceScale = cocos2d::ScaleTo::create(0.5f, cocos2d::RandomHelper::random_real(tree->tree_scale - 0.05f, tree->tree_scale + 0.05f));
		auto elasticEaseBounceScale = cocos2d::EaseElasticOut::create(bounceScale->clone());

		tree->runAction(elasticEaseBounceScale);

		tree->scheduleUpdate();

		tree->autorelease();
		return tree;
	}
	CC_SAFE_DELETE(tree);
	return nullptr;
}

void TreeButton::bindToClickEvent(const std::function<void()>& callback)
{
	on_click = callback;
}

void TreeButton::bindToDeathEvent(const std::function<void()>& callback)
{
	on_death = callback;
}

void TreeButton::treeClicked()
{
	if (on_click)
		on_click();

	removeFromParent();
}

void TreeButton::update(float dt)
{
	lifetime -= dt;

	const cocos2d::Vec3 color = (cocos2d::Vec3(255, 255, 255)).lerp(cocos2d::Vec3(0, 0, 0), 1.0f - (lifetime / max_lifetime));
	setColor(cocos2d::Color3B(color.x, color.y, color.z));

	if (lifetime <= 0.0f)
	{
		if (on_death)
			on_death();

		removeFromParent();
	}
}

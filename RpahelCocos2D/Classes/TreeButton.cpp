#include "TreeButton.h"
#include "2d/CCActionInterval.h"
#include "2d/CCActionEase.h"

TreeButton* TreeButton::create(const cocos2d::Vec2& position)
{
	TreeButton* tree = new (std::nothrow) TreeButton;
	if (tree && tree->init("sprites/tree_big.png"))
	{
		tree->setAnchorPoint({ 0.5f, 0.5f });
		tree->setContentSize(tree->tree_size);
		tree->setScale(0);
		tree->setPosition(position);

		auto bounceScale = cocos2d::ScaleTo::create(0.5f, tree->tree_scale);
		auto elasticEaseBounceScale = cocos2d::EaseElasticOut::create(bounceScale->clone());

		tree->runAction(elasticEaseBounceScale);

		tree->autorelease();
		return tree;
	}
	CC_SAFE_DELETE(tree);
	return nullptr;
}

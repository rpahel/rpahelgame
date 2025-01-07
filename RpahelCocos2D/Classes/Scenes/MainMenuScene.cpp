#include "MainMenuScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
	return MainMenuScene::create();
}

bool MainMenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Title
	auto label = Label::createWithTTF("Timber Clicker", "fonts/Naluka.ttf", 48);
	if (label == nullptr)
	{
		printf("Error while loading: 'fonts/Naluka.ttf'\n");
	}
	else
	{
		label->setPosition(
			Vec2(
				origin.x + visibleSize.width / 2,
				origin.y + visibleSize.height - label->getContentSize().height));

		label->setColor({ 201, 118, 77 });

		this->addChild(label, 1);
	}

	// Trees
	auto sprite_ref = Sprite::create("sprites/tree_big.png");
	if (sprite_ref == nullptr)
	{
		printf("Error while loading: 'sprites/tree_big.png'\n");
	}
	else
	{
		const Size spriteSize = sprite_ref->getContentSize();
		const int horizontal_nb = visibleSize.width / spriteSize.width + 2;
		const int vertical_nb = 2;

		auto spritesNode = Node::create();
		for (size_t i = 0; i < vertical_nb; i++)
		{
			const uint8_t value = i == 0 ? 255 * 0.5f : 255;
			for (size_t j = 0; j < horizontal_nb; j++)
			{
				auto sprite = Sprite::create("sprites/tree_big.png");
				sprite->setPosition(Vec2(
					origin.x - spriteSize.width * 0.5f + spriteSize.width * j + spriteSize.width * 0.5f * i,
					visibleSize.height / 2 + origin.y + 70 - 32 * i));

				sprite->setColor({ value, value, value });
				spritesNode->addChild(sprite, 0);
			}
		}

		this->addChild(spritesNode, 0);
	}

	// Buttons

	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);

	auto playButton = MenuItemLabel::create(Label::createWithTTF("Play", "fonts/arial.ttf", 32));
	playButton->setColor({ 255, 255, 255 });

	playButton->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));

	menu->addChild(playButton, 0);

	this->addChild(menu, 1);

	return true;
}


void MainMenuScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

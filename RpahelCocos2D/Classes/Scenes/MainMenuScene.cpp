#include "MainMenuScene.h"
#include "GameScene.h"
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

	// Highest Score
	int high_score_signed = UserDefault::getInstance()->getIntegerForKey("HIGH_SCORE");
	unsigned int high_score_unsigned = 0;
	std::memcpy(&high_score_unsigned, &high_score_signed, sizeof(int));

	if (high_score_unsigned != 0)
	{
		auto scoreLabel = Label::createWithTTF("Highest score : " + std::to_string(high_score_unsigned), "fonts/arial.ttf", 16);
		if (scoreLabel == nullptr)
		{
			printf("Error while loading: 'fonts/arial.ttf'\n");
		}
		else
		{
			scoreLabel->setPosition(
				Vec2(
					origin.x + visibleSize.width / 2,
					origin.y + visibleSize.height - scoreLabel->getContentSize().height));

			scoreLabel->setColor({ 0, 0, 0 });

			this->addChild(scoreLabel, 1);
		}
	}


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

	// Background
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("sprites/sky.png");
	Texture2D::TexParams tp(backend::SamplerFilter::LINEAR, backend::SamplerFilter::LINEAR, backend::SamplerAddressMode::REPEAT, backend::SamplerAddressMode::REPEAT);
	texture->setTexParameters(tp);
	Sprite* skyBackground = Sprite::createWithTexture(texture, Rect(0, 0, visibleSize.width, visibleSize.height));
	skyBackground->setPosition({ visibleSize.width / 2, visibleSize.height / 2 });
	this->addChild(skyBackground, -1);

	texture = Director::getInstance()->getTextureCache()->addImage("sprites/grass.png");
	texture->setTexParameters(tp);
	Sprite* grassBackground = Sprite::createWithTexture(texture, Rect(0, 0, visibleSize.width, visibleSize.height));
	grassBackground->setPosition({ visibleSize.width / 2, 0 });
	this->addChild(grassBackground, -1);

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

				auto grassPatch = Sprite::create("sprites/grass_patch.png");
				grassPatch->setAnchorPoint({ 0.5f, 0.0f });
				grassPatch->setPosition(Vec2(sprite->getPositionX(), sprite->getPositionY() - spriteSize.height * 0.5f));
				grassPatch->setScaleY(0.5f);

				grassPatch->setColor({ value, value, value });
				spritesNode->addChild(grassPatch, 0);
			}
		}

		this->addChild(spritesNode, 0);
	}

	// Buttons
	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);

	auto playButton = MenuItemLabel::create(Label::createWithTTF("Play", "fonts/arial.ttf", 32));
	playButton->setColor({ 50, 50, 50 });

	playButton->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + (playButton->getContentSize().height + 16) * 2));

	playButton->setCallback(CC_CALLBACK_1(MainMenuScene::playGameCallback, this));

	menu->addChild(playButton, 0);

	auto quitButton = MenuItemLabel::create(Label::createWithTTF("Quit", "fonts/arial.ttf", 32));
	quitButton->setColor({ 255, 100, 100 });

	quitButton->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + quitButton->getContentSize().height + 16));

	quitButton->setCallback(CC_CALLBACK_1(MainMenuScene::quitGameCallback, this));

	menu->addChild(quitButton, 0);

	this->addChild(menu, 1);

	return true;
}

void MainMenuScene::playGameCallback(cocos2d::Ref* pSender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene, {255, 255, 255}));
}

void MainMenuScene::quitGameCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();
}
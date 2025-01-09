#include "GameScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Grass background
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("sprites/grass.png");
	Texture2D::TexParams tp(backend::SamplerFilter::LINEAR, backend::SamplerFilter::LINEAR, backend::SamplerAddressMode::REPEAT, backend::SamplerAddressMode::REPEAT);
	texture->setTexParameters(tp);
	Sprite* grassBackground = Sprite::createWithTexture(texture, Rect(0, 0, visibleSize.width, visibleSize.height));
	grassBackground->setPosition({ visibleSize.width / 2, visibleSize.height / 2 });
	this->addChild(grassBackground, -1);

	// House
	auto houseSprite = Sprite::create("sprites/house.png");
	houseSprite->setAnchorPoint({ 0.0f, 1.0f });
	houseSprite->setPosition(Vec2(16, visibleSize.height - 64));
	houseSprite->setFlippedX(true);
	this->addChild(houseSprite, 0);

	// Score label
	auto scoreLabel = Label::createWithTTF("Current score : " + std::to_string(current_score), "fonts/arial.ttf", 16);
	if (scoreLabel == nullptr)
	{
		printf("Error while loading: 'fonts/arial.ttf'\n");
	}
	else
	{
		scoreLabel->setPosition(Vec2(
				origin.x + scoreLabel->getContentSize().width / 2 + 16,
				origin.y + visibleSize.height - scoreLabel->getContentSize().height / 2 - 16));

		scoreLabel->setColor({ 0, 0, 0 });

		this->addChild(scoreLabel, 1);
	}

	// Highest score label
	highest_score = (unsigned int)UserDefault::getInstance()->getIntegerForKey("HIGH_SCORE");
	auto highestScoreLabel = Label::createWithTTF("Highest score : " + std::to_string(highest_score), "fonts/arial.ttf", 16);
	if (highestScoreLabel == nullptr)
	{
		printf("Error while loading: 'fonts/arial.ttf'\n");
	}
	else
	{
		highestScoreLabel->setPosition(Vec2(
			origin.x + highestScoreLabel->getContentSize().width / 2 + 16,
			origin.y + visibleSize.height - highestScoreLabel->getContentSize().height * 1.5f - 16));

		highestScoreLabel->setColor({ 0, 0, 0 });

		this->addChild(highestScoreLabel, 1);
	}

	return true;
}

GameScene::~GameScene()
{
	if (current_score > highest_score)
		UserDefault::getInstance()->setIntegerForKey("HIGH_SCORE", (int)current_score);
}

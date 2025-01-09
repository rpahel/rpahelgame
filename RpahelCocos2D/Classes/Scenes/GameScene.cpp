#include "GameScene.h"
#include "../TreeButton.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::init())
		return false;

	current_tree_spawn_cd = tree_spawn_cd;

	visible_size = Director::getInstance()->getVisibleSize();
	const Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Grass background
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("sprites/grass.png");
	Texture2D::TexParams tp(backend::SamplerFilter::LINEAR, backend::SamplerFilter::LINEAR, backend::SamplerAddressMode::REPEAT, backend::SamplerAddressMode::REPEAT);
	texture->setTexParameters(tp);
	Sprite* grassBackground = Sprite::createWithTexture(texture, Rect(0, 0, visible_size.width, visible_size.height));
	grassBackground->setPosition({ visible_size.width / 2, visible_size.height / 2 });
	this->addChild(grassBackground, -1);

	// House
	auto houseSprite = Sprite::create("sprites/house.png");
	houseSprite->setAnchorPoint({ 0.0f, 1.0f });
	houseSprite->setPosition(Vec2(16, visible_size.height - 64));
	houseSprite->setFlippedX(true);
	this->addChild(houseSprite, 0);

	// Score label
	score_label = Label::createWithTTF("Current score : " + std::to_string(current_score), "fonts/arial.ttf", 16);
	if (score_label == nullptr)
	{
		printf("Error while loading: 'fonts/arial.ttf'\n");
	}
	else
	{
		score_label->setPosition(Vec2(
				origin.x + score_label->getContentSize().width / 2 + 16,
				origin.y + visible_size.height - score_label->getContentSize().height / 2 - 16));

		score_label->setColor({ 0, 0, 0 });

		this->addChild(score_label, 1);
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
			origin.y + visible_size.height - highestScoreLabel->getContentSize().height * 1.5f - 16));

		highestScoreLabel->setColor({ 0, 0, 0 });

		this->addChild(highestScoreLabel, 1);
	}

	this->scheduleUpdate();

	return true;
}

GameScene::~GameScene()
{
	if (current_score > highest_score)
		UserDefault::getInstance()->setIntegerForKey("HIGH_SCORE", (int)current_score);
}

void GameScene::update(float dt)
{
	printf("Update");

	current_tree_spawn_cd -= dt;
	if (current_tree_spawn_cd > 0)
		return;

	if (tree_nb >= max_tree_nb)
		return;

	if (tree_spawn_cd > tree_spawn_min_cd)
	{
		tree_spawn_cd *= tree_spawn_cd_scale;

		if (tree_spawn_cd < tree_spawn_min_cd)
			tree_spawn_cd = tree_spawn_min_cd;
	}

	current_tree_spawn_cd = tree_spawn_cd;

	spawnTree();
}

void GameScene::spawnTree()
{
	auto tree = TreeButton::create(
		{
			visible_size.width * 0.5f + RandomHelper::random_int((int)(-visible_size.width * 0.33f), (int)(visible_size.width * 0.33f)),
			visible_size.height * 0.5f + RandomHelper::random_int((int)(-visible_size.height * 0.33f), (int)(visible_size.height * 0.33f)),
		}
	);

	if (tree)
	{
		tree->bindToClickEvent(
			[this]()
			{
				--tree_nb;
				++current_score;

				if (score_label)
				{
					score_label->setString("Current score : " + std::to_string(current_score));
					score_label->setPosition(Vec2(
						score_label->getContentSize().width / 2 + 16,
						visible_size.height - score_label->getContentSize().height / 2 - 16));
				}
			}
		);

		++tree_nb;
		this->addChild(tree, visible_size.height - tree->getPositionY());
	}
}

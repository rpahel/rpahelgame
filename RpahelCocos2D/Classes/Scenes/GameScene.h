#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	~GameScene();

protected:
	void update(float dt);
	void spawnTree();

private:
	cocos2d::Size visible_size;
	cocos2d::Label* score_label = nullptr;

	unsigned int highest_score = 0;
	unsigned int current_score = 0;

	float tree_spawn_cd = 1.0f;
	float tree_spawn_min_cd = 0.25f;
	float current_tree_spawn_cd = 0.0f;
	float tree_spawn_cd_scale = 0.9f;

	unsigned int tree_nb = 0;
	unsigned int max_tree_nb = 50;
};

#endif // __GAME_SCENE_H__

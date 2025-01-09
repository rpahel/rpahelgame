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
	cocos2d::Size visibleSize;

	unsigned int highest_score = 0;
	unsigned int current_score = 0;

	float tree_spawn_cd = 5.0f;
	float current_tree_spawn_cd = 0.0f;
	float tree_spawn_cd_scale = 0.9f;
};

#endif // __GAME_SCENE_H__

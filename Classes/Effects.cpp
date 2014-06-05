#include "Effects.h"

Effects* Instance=nullptr;

Effects* Effects::getInstance()
{
	if(!Instance)
		Instance=new Effects;
	return Instance;
}

void Effects::preload()
{
	//png��plist��һ���ļ��п�������д
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("explosion.plist");
	char str[20]={};
	auto boomAnimation=Animation::create();
	boomAnimation->setDelayPerUnit(0.3f);
	boomAnimation->setLoops(-1);
	for(int i=1;i!=36;i++)
	{
		sprintf(str,"explosion_%02d.png",i);
		auto boomSpfrm=SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		boomAnimation->addSpriteFrame(boomSpfrm);
	}

	//������������뵽����������
	AnimationCache::getInstance()->addAnimation(boomAnimation,"boom");
}

void Effects::boom(Node*Target,Point point)
{
	auto sp=Sprite::createWithSpriteFrameName("explosion_01.png");
	Target->addChild(sp);
	sp->setPosition(point);

	auto animation=AnimationCache::getInstance()->getAnimation("boom");

	auto animate=Animate::create(animation);

	auto callaction=CallFuncN::create(sp,callfuncN_selector(Effects::boom_back));
}

void Effects::boom_back(Node*node)
{
	node->removeFromParentAndCleanup(true);
}
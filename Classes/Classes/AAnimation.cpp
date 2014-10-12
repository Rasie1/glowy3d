#include "AAnimation.h"


AAnimation * AAnimation::create()
{
	AAnimation * ret = new AAnimation();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool AAnimation::init()
{
	iterator = -1;
	framesSize = 0;

	//CCAction *_cached_idleAction = CCRepeatForever::create(CCSequence::createWithTwoActions(CCRepeat::create(_cached_idle_anim_1, 5), CCRepeat::create(_cached_idle_anim_2, 3)));

	

	return true;
}

void AAnimation::addFrame(TextureInfo * texture)
{
	frames.pushBack(texture);
	++framesSize;
}

TextureInfo * AAnimation::getNextFrame()
{
	++iterator;
	if (iterator == framesSize)
	{
		iterator = 0;
	}

	return frames.at(iterator);
}

void AAnimation::setFrame(int frame)
{
	iterator = std::min(frame, framesSize);
}

//AnimationSet

AnimationSet * AnimationSet::create()
{
	AnimationSet * ret = new AnimationSet();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool AnimationSet::init()
{
	Vector<SpriteFrame*> frames;
	float animationDelay = 0.07f;

	char str[100] = { 0 };

	frames.pushBack(SpriteFrame::create("Knight/Walk/walk_00000.png", Rect(0, 0, 59, 110)));
	animations[ANIMATION_IDLE_E] = Animate::create(Animation::createWithSpriteFrames(frames, animationDelay, 10));
	animations[ANIMATION_IDLE_E]->retain();
	frames.clear();

	frames.pushBack(SpriteFrame::create("Knight/Walk/walk_10000.png", Rect(0, 0, 59, 110)));
	animations[ANIMATION_IDLE_NE] = Animate::create(Animation::createWithSpriteFrames(frames, animationDelay, 10));
	animations[ANIMATION_IDLE_NE]->retain();
	frames.clear();

	frames.pushBack(SpriteFrame::create("Knight/Walk/walk_20000.png", Rect(0, 0, 59, 110)));
	animations[ANIMATION_IDLE_N] = Animate::create(Animation::createWithSpriteFrames(frames, animationDelay, 10));
	animations[ANIMATION_IDLE_N]->retain();
	frames.clear();

	frames.pushBack(SpriteFrame::create("Knight/Walk/walk_30000.png", Rect(0, 0, 59, 110)));
	animations[ANIMATION_IDLE_NW] = Animate::create(Animation::createWithSpriteFrames(frames, animationDelay, 10));
	animations[ANIMATION_IDLE_NW]->retain();
	frames.clear();

	frames.pushBack(SpriteFrame::create("Knight/Walk/walk_40000.png", Rect(0, 0, 59, 110)));
	animations[ANIMATION_IDLE_W] = Animate::create(Animation::createWithSpriteFrames(frames, animationDelay, 10));
	animations[ANIMATION_IDLE_W]->retain();
	frames.clear();

	frames.pushBack(SpriteFrame::create("Knight/Walk/walk_50000.png", Rect(0, 0, 59, 110)));
	animations[ANIMATION_IDLE_SW] = Animate::create(Animation::createWithSpriteFrames(frames, animationDelay, 10));
	animations[ANIMATION_IDLE_SW]->retain();
	frames.clear();

	frames.pushBack(SpriteFrame::create("Knight/Walk/walk_60000.png", Rect(0, 0, 59, 110)));
	animations[ANIMATION_IDLE_S] = Animate::create(Animation::createWithSpriteFrames(frames, animationDelay, 10));
	animations[ANIMATION_IDLE_S]->retain();
	frames.clear();

	frames.pushBack(SpriteFrame::create("Knight/Walk/walk_70000.png", Rect(0, 0, 59, 110)));
	animations[ANIMATION_IDLE_SE] = Animate::create(Animation::createWithSpriteFrames(frames, animationDelay, 10));
	animations[ANIMATION_IDLE_SE]->retain();
	frames.clear();

	for (int i = 1; i < 10; i++)
	{
		sprintf(str, "Knight/Walk/walk_0000%d.png", i);
		frames.pushBack(SpriteFrame::create(str, Rect(0, 0, 59, 110)));
	}
	animations[ANIMATION_RUN_E] = Animate::create(Animation::createWithSpriteFrames(frames, animationDelay, 10));
	animations[ANIMATION_RUN_E]->retain();
	frames.clear();

	for (int i = 1; i < 10; i++)
	{
		sprintf(str, "Knight/Walk/walk_1000%d.png", i);
		frames.pushBack(SpriteFrame::create(str, Rect(0, 0, 59, 110)));
	}
	animations[ANIMATION_RUN_NE] = Animate::create(Animation::createWithSpriteFrames(frames, animationDelay, 10));
	animations[ANIMATION_RUN_NE]->retain();
	frames.clear();

	for (int i = 1; i < 10; i++)
	{
		sprintf(str, "Knight/Walk/walk_2000%d.png", i);
		frames.pushBack(SpriteFrame::create(str, Rect(0, 0, 59, 110)));
	}
	animations[ANIMATION_RUN_N] = Animate::create(Animation::createWithSpriteFrames(frames, animationDelay, 10));
	animations[ANIMATION_RUN_N]->retain();
	frames.clear();


	for (int i = 1; i < 10; i++)
	{
		sprintf(str, "Knight/Walk/walk_3000%d.png", i);
		frames.pushBack(SpriteFrame::create(str, Rect(0, 0, 59, 110)));
	}
	animations[ANIMATION_RUN_NW] = Animate::create(Animation::createWithSpriteFrames(frames, animationDelay, 10));
	animations[ANIMATION_RUN_NW]->retain();
	frames.clear();

	for (int i = 1; i < 10; i++)
	{
		sprintf(str, "Knight/Walk/walk_4000%d.png", i);
		frames.pushBack(SpriteFrame::create(str, Rect(0, 0, 59, 110)));
	}
	animations[ANIMATION_RUN_W] = Animate::create(Animation::createWithSpriteFrames(frames, animationDelay, 10));
	animations[ANIMATION_RUN_W]->retain();
	frames.clear();

	for (int i = 1; i < 10; i++)
	{
		sprintf(str, "Knight/Walk/walk_5000%d.png", i);
		frames.pushBack(SpriteFrame::create(str, Rect(0, 0, 59, 110)));
	}
	animations[ANIMATION_RUN_SW] = Animate::create(Animation::createWithSpriteFrames(frames, animationDelay, 10));
	animations[ANIMATION_RUN_SW]->retain();
	frames.clear();

	for (int i = 1; i < 10; i++)
	{
		sprintf(str, "Knight/Walk/walk_6000%d.png", i);
		frames.pushBack(SpriteFrame::create(str, Rect(0, 0, 59, 110)));
	}
	animations[ANIMATION_RUN_S] = Animate::create(Animation::createWithSpriteFrames(frames, animationDelay, 10));
	animations[ANIMATION_RUN_S]->retain();
	frames.clear();

	for (int i = 1; i < 10; i++)
	{
		sprintf(str, "Knight/Walk/walk_7000%d.png", i);
		frames.pushBack(SpriteFrame::create(str, Rect(0, 0, 59, 110)));
	}
	animations[ANIMATION_RUN_SE] = Animate::create(Animation::createWithSpriteFrames(frames, animationDelay, 10));
	animations[ANIMATION_RUN_SE]->retain();
	frames.clear();

	return true;
}

AnimationSet::~AnimationSet()
{
	delete animations;
}
#pragma once
#include "cocos2d.h"
#include "AnimationInfo.h"
#include "GameConfig.h"
#include "EnemyInfo.h"
#include "PlayerInfo.h"
#include "GameService.h"
#include "AudioEngine.h"
#include "ButtonMenu.h"
using namespace std;
USING_NS_CC;
class ZVP : public Layer {
public:
	static cocos2d::Scene* createScene(GameConfig config = GameConfig::defaultConfig());
	static Layer *createBackgroundLayer();

	void setPhysicsWorld(PhysicsWorld * world);
	virtual bool init();
	
	void preloadMusic();

	//������Ϸ��ͼ
	void  loadMap();
	//"��Ⱦ"��ͼ�Ŀɼ����֡���Ⱦָ���ǰѵ�ͼ�ķ���ת����װ�λ򴴽�Ϊ��Ӧ�ľ��顣��׼�����ô�Ӧ���ǽ����������ˡ�
	void renderVisibleMap();
	//"��Ⱦ"��renderStartX��renderEndX���������ĵ�ͼ����
	void renderMapTiles(int renderStartX, int renderEndX);
	//"��Ⱦ"��ͼ�ɼ����ֵ���Ϸ����
	void renderVisibleMapObjects();
	//"��Ⱦ"��·���顣����ݵغͻ�ɫ�����ء�
	void renderLandTile(Sprite* tile);
	//"��Ⱦ"�����ƶ��ĵ�·���顣���񳬼��������������ֿ��е�һ��������ȥ�����֡�
	// �Լ������ƶ��ĵ�·���顣���񳬼������ڶ������ֿ��еġ����ϵ��¡�����ѭ�����е�����ݵ����֡�
	void renderMovingBlock(const ValueMap &obj);
	//"��Ⱦ"�������顣���������ʺŵķ��顣��һ�¿��������⡢��Ƭ�ȡ�
	void renderRewardBlock(const ValueMap &obj);
	//"��Ⱦ"��ʬ����
	void renderZombieObject(const ValueMap &obj);
	//"��Ⱦ"���ⷽ��
	void renderSunlightTile(Sprite* tile);
	
	void addPlayer();
	//���ؽ�ɫ������Ϣ������һ������Ķ�����ͼƬ�ļ���֡������С���Ա�����������ʱ����ʹ�á�
	void loadIdleAnimationInfo();
	//���ؽ�ɫ������һ������Ķ�����ͼƬ��
	void loadIdle(const string &name);
	//����name�ҵ���Ӧ��ͼƬ�ļ�������֡���ʹ�С�и
	void loadAnimation(const string &name, size_t frameCount, const Size &frameSize, float interval = 0.1f);
	//������ҵĵ�ǰֲ����л�ֲ�
	void setPlayerPlant(Sprite *player, const string &name);

	void addListeners();

	//����
	void onKeyPressed(EventKeyboard::KeyCode code, Event * event);
	//��ͣ����ʾ��Ϸ�˵�
	void pauseAndShowMenu();
	void onMenuTouchEvent(Ref * ref, Widget::TouchEventType type);
	void onPlayerKeyPressed(int i, EventKeyboard::KeyCode code, Event * event);
	void onKeyReleased(EventKeyboard::KeyCode code, Event * event);
	void movePlayer(Sprite * player, EventKeyboard::KeyCode code);
	void stopPlayer(Sprite* player, EventKeyboard::KeyCode code);

	//�������������
	void makeAttack(Sprite *player);
	//�����㶹�������㶹���֡������㶹���֡��������ֵĹ�����
	void shootPea(Sprite *player);
	//��ը�����ڻ�������ը���Ĺ�����
	void boom(Sprite *player);
	//���յ���
	void killEnemy(Sprite *enemy);

	bool onConcactBegin(PhysicsContact & contact);
	bool handlePlayerCollision(Sprite *player, Node *anotherSprite);
	//����������·����ײ
	void handlePlayerCollisionWithLand(Sprite* player, Sprite* land);

	void handleRewardBlockCollided(Sprite* player, Sprite *block);
	//����������������ײ
	void handlePlayerCollisionWithSublight(Sprite* player, Sprite* goldCoin);
	//�����������˵���ײ���������н�ʬ��
	void handlePlayerCollisionWithEnemy(Sprite* player, Sprite* enemy);
	//���������ֲ�￨Ƭ����ײ����ҽ����ȡ����ֲ�￨Ƭ��
	void handlePlayerCollisionWithPlantCard(Sprite* player, Sprite* mushroom);
	//��������㶹�͵��˵���ײ����������ֵ���١�����Ǻ������ֵ��㶹�����ٶ�ͬʱ���������������͡�
	void handlePeaCollisionWithEnemy(Sprite *pea, Sprite* enemy);
	//��ʬ�յ������Ĵ���attackΪ������������ʬ���ٵ�����ֵ��
	bool onEnemyAttacked(Sprite * enemy, int attack);
	void onContactSeparate(PhysicsContact & contact);

	//����һ��ֲ�￨Ƭ��
	Sprite *createPlantCard(const string &plantName);
	//��pos�Ϸ�����һ��ֲ�￨Ƭ��
	void createPlantCardAbove(const string &plantName, const Vec2 &pos);
	//��λ��(x, y)����һ���ʺŷ��顣
	Sprite *createQuestionBlockAt(float x, float y);
	//��λ��(x, y)����һ���ݵط��顣
	Sprite *createGrasslandBlock();
	//���ݽ�ʬ���ƴ�����ʬ
	Sprite *createZombie(const string &name);
	//����һ�����顣�����ݾ��������ҵ���Ӧ��ͼƬ�ļ�������Sunlight��ӦSunlight.png������ָ�������ΪͼƬ�Ŀ�ߡ�
	Sprite *createSprite(const string &name, float w = -1, float  h = -1);
	//Ϊ�������һ��ֲ�
	void addPlant(Sprite *player, const string &plantName, PlantInfo plantInfo, Sprite* card = nullptr);
	//��ֲ�￨Ƭ���ֲ����Ϣ����������ֵ���������⡣
	void appendPlantCardInfo(Sprite* card,  PlantInfo *plantInfo);
	//����ש��Ч�������ڼ�����鷽��ʱ�Ķ�����
	void breakBlock(Sprite *block);

	//�þ��������ƶ�
	void makeSpriteMoveBackAndForth(Sprite *sprite, float distance, float duration);

	void update(float dt);
	// ����"����ͷ"λ�á��������λ�õ���Layerλ�á�
	void setViewPoint(const Point & point);
	void updatePlayer(Sprite *player);

	void updateEnemys(float dt);
	//���½�ʬ�ĸ�����Ϊ
	void updateEnemyTraceBehavior(Sprite *enemy);
	//���½�ʬ�������Ϊ
	void updateEnemyRandomBehavior(Sprite *enemy);
	//������Ծ��ʬ����Ϊ
	void updateEnemyJumpBehavior(Sprite *enemy);
	//����������ȥ�Ľ�ʬ����Ϊ
	void updateEnemyRepeatBehavior(Sprite *enemy);
	//�������ܽ�ʬ����Ϊ
	void updateEnemyAiBehavior(Sprite *enemy);

	void initGameInfoLayer();
	//������Ϸ��Ϣ���������⡢����ֵ�ȡ�
	void updateGameInfo(float dt);

	//������ת��Ϊ�������ꡣǰ�������������ꡣ����(��������)�Ƿ����ڵ�ͼ�е�λ�ã������һ������Ϊ(0, 0)����һ�еڶ�������Ϊ(1, 0)
	Point getTileCoordFromPosition(Point pos);
	//��ȡ��ĳ��λ�õĵ�·���顣pos���������ꡣ
	Sprite *getLandTileAt(Vec2 pos);

	void gameOver();

	void win(Sprite * star);

	void enterNextGameLevel(float delay);

	void finish();

	void pauseGame();

	void resumeGame();

	void saveGame();

	ZVP(const GameConfig &config) {
		this->config = config;
	}

	static ZVP* create(const GameConfig &config) 
	{ 
		ZVP *pRet = new(std::nothrow) ZVP(config);
		if (pRet && pRet->init()) 
		{ 
			pRet->autorelease(); 
			return pRet; 
		} 
		else 
		{ 
			delete pRet; 
			pRet = nullptr; 
			return nullptr; 
		} 
	}

private:
	PhysicsWorld* m_world;
	//��Ϸ��ͼ
	TMXTiledMap* m_map;
	//��ͼ�Ĳݵز�
	TMXLayer* grasslandLayer;
	//��ͼ��Ⱥ͸߶�
	float mapPixelWidth, mapPixelHeight;
	Size visibleSize;
	//��ͼ�ɼ������ں������ϵķ�����������ͼ�ɼ�����Ŀ�ʼ�������ꡢ������������
	int mapVisibleRegionWidth, mapVisibleRegionStartX = 0, mapVisibleRegionEndX = 0;
	//����"��Ⱦ��"��map��������ַ����Ӧ����Ⱦ�����μ�renderVisibleMap������
	map<TMXLayer*, function<void(Sprite*)> > tileRenderers;
	//����"��Ⱦ��"��map������ָ���Ƿ�������Ķ������罩ʬ�����ߵȡ��μ�renderVisibleMap������
	map<TMXObjectGroup*, function<void(const ValueMap &obj)> >  objectRenders;

	//��ɫ�Ķ�����Ϣ
	map<string, AnimationInfo> idleAnimInfos;
	
	Layer* infoLayer = nullptr;

	vector<Sprite*> players;
	set<Sprite*> enemys;
	GameConfig config;
	bool isGameOver = false;
	experimental::AudioEngine audio;

};
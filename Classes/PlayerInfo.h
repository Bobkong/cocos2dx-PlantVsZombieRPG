#pragma once

#include "Tools.h"
using namespace std;


//ֲ����Ϣ
class PlantInfo {
public:
	//�ܹ�������ֵ
	int totalHealthPoint = 10;
	//��ǰ����ֵ
	int healthPoint = 0;
	//����ʱ��
	long frozenDuration = 20000;
	//�Ƿ񱻶���
	bool isFrozen = false;
	//��ֲ����Ҫ������
	int requiredSunlight = 100;
	//�ƶ��ٶ�
	int velocity = 100;
	//��Ծ�ٶȣ�Ӱ��߶ȣ�
	int jumpingVelocity = 300;
	//��¼������ʱ����������ж϶���ʱ���Ƿ��ѵ�
	long deadTime = 0;

	long attackDelay = 500;
	float repeatedAttackDelay = 0.5f;
	

	static PlantInfo create(const string &name);
	static PlantInfo createWithFullHp(const string &name);
	static PlantInfo fromValueMap(const string &name, const ValueMap &m) {
		PlantInfo info = create(name);
		auto hp = m.find("hp");
		if (hp != m.end()) {
			info.healthPoint = hp->second.asInt();
		}
		return info;
	}

	void toValueMap(ValueMap &m) {
		m["hp"] = healthPoint;
	}

	PlantInfo(int totalHp = 10, int _frozenDuration = 20, int _requiredSunlight = 100, int _velocity = 100, int _jumpingVelocity = 300, long _attackDelay = 500, float _repeatedAttackDelay = 0.6f);

	void die() {
		isFrozen = true;
		deadTime = Tools::currentTimeInMillis();
		healthPoint = 0;  
	}
};


class InfoViews {
public:
	Label *sunlightLabel = nullptr;
	Label *hpLabel = nullptr;
	Sprite *sunlightIcon;
	vector<Sprite*> plantCards;
	
};

class PlayerInfo {
public:
	float initialPosX = 60, initialPosY = 400;
	int playerIndex;
	//�Ƿ�������Ծ��Ҳ�����ڿ��С�
	bool isJumping = false;
	//x������ٶ�
	float velocityX = 0;
	// ��ǰֲ��(index)
	int currentPlant = 0;
	// ����
	int sunlight = 0;

	long lastAttackingTime;
	vector<string> plants;
	map<string, PlantInfo> plantInfo;
	InfoViews infoViews;

	static PlayerInfo fromValueMap(const ValueMap &m) {
		PlayerInfo info;
		auto sunlight = m.find("sunlight");
		if (sunlight != m.end()) {
			info.sunlight = sunlight->second.asInt();
		}
		auto currentPlant = m.find("currentPlant");
		if (currentPlant != m.end()) {
			info.currentPlant = currentPlant->second.asInt();
		}
		auto initialPosX = m.find("initialPosX");
		if (initialPosX != m.end()) {
			info.initialPosX = initialPosX->second.asFloat();
		}
		auto initialPosY = m.find("initialPosY");
		if (initialPosY != m.end()) {
			info.initialPosY = initialPosY->second.asFloat();
		}
		auto plants = m.find("plants");
		if (plants != m.end()) {
			for (const Value &plant : plants->second.asValueVector()) {
				info.plants.push_back(plant.asString());
			}
		}
		auto plantInfos = m.find("plantInfo");
		if (plantInfos != m.end()) {
			for (auto &plantInfo: plantInfos->second.asValueMap()) {
				info.plantInfo[plantInfo.first] = PlantInfo::fromValueMap(plantInfo.first, plantInfo.second.asValueMap());
			}
		}
		return info;
	}

	void toValueMap(ValueMap &m) {
		m["sunlight"] = sunlight;
		m["currentPlant"] = currentPlant;
		m["initialPosX"] = initialPosX;
		m["initialPosY"] = initialPosY;
		ValueVector plants;
		for (auto &plant : this->plants) {
			plants.push_back(Value(plant));
		}
		m["plants"] = plants;
		ValueMap plantInfos;
		for (auto &plantInfo : this->plantInfo) {
			ValueMap plantInfoMap;
			plantInfo.second.toValueMap(plantInfoMap);
			plantInfos[plantInfo.first] = plantInfoMap;
		}
		m["plantInfo"] = plantInfos;
	}

	void clearTransitveValues() {
		infoViews = InfoViews();
	}

	string switchPlant() {
		currentPlant = (currentPlant + 1) % plants.size();
		return plants[currentPlant];
	}

	string currentPlantName() {
		return plants[currentPlant];
	}

	bool hasPlant(const string &plantName) {
		return find(plants.begin(), plants.end(), plantName) != plants.end();
	}

	size_t plantCount() {
		return plants.size();
	}

	PlantInfo &currentPlantInfo() {
		return plantInfo[plants[currentPlant]];
	}

	void addPlant(const string &plantName, PlantInfo info = PlantInfo()) {
		plants.push_back(plantName);
		plantInfo[plantName] = info;
	}
};
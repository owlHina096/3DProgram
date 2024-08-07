﻿#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Terrain/Terrain.h"
#include "../../GameObject/Character/Character.h"

#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Camera/CCTVCamera/CCTVCamera.h"

// 少数第n位で四捨五入する
void round_n(float& number, int n)
{
	number = number * pow(10, n - 1);
	number = round(number);
	number /= pow(10, n - 1);
}

void GameScene::Init()
{
	//===================================================================
	// ステージ初期化
	//===================================================================
	std::shared_ptr<Terrain> _terrain = std::make_shared<Terrain>();
	_terrain->Init();
	AddObject(_terrain);

	//===================================================================
	// キャラクター初期化
	//===================================================================
	std::shared_ptr<Character> _character = std::make_shared<Character>();
	_character->Init();
	AddObject(_character);

	//===================================================================
	// カメラ初期化
	//===================================================================
	//std::shared_ptr<FPSCamera>		_camera = std::make_shared<FPSCamera>();
	//std::shared_ptr<TPSCamera>		_camera = std::make_shared<TPSCamera>();
	std::shared_ptr<CCTVCamera>		_camera = std::make_shared<CCTVCamera>();
	_camera->Init();
	_camera->SetTarget(_character);
	_camera->RegistHitObject(_terrain);
	_character->SetCamera(_camera);
	AddObject(_camera);

	//===================================================================
	// 乱数実験場
	//===================================================================
	int randRes[10] = {};
	/*
	//rand()による生成の偏りを調べる
	srand((UINT)time(NULL));
	for (int i = 0; i < 100000000; i++)
	{
		int tmp = rand() % 10000;
		int idx = tmp / 1000;

		randRes[idx]++;
	}
	//結果を出力
	OutputDebugStringA("----------------------------------\n");
	for (int i = 0; i < 10; i++)
	{
		std::stringstream ss;
		ss << "取得した値が" << i * 1000 << "～" << (i + 1) * 1000
			<< "の件数：\t" << randRes[i] << "\n";
		std::string str = ss.str();
		OutputDebugStringA(str.c_str());
	}
	OutputDebugStringA("----------------------------------\n");
	*/

	/*
	//メルセンヌツイスタ
	for (int i = 0; i < 100000000; i++)
	{
		int tmp = KdGetInt(0, 9999);
		int idx = tmp / 1000;

		randRes[idx]++;
	}
	//結果を出力
	OutputDebugStringA("----------------------------------\n");
	for (int i = 0; i < 10; i++)
	{
		std::stringstream ss;
		ss << "取得した値が" << i * 1000 << "～" << (i + 1) * 1000
			<< "の件数：\t" << randRes[i] << "\n";
		std::string str = ss.str();
		OutputDebugStringA(str.c_str());
	}
	OutputDebugStringA("----------------------------------\n");
	*/

	/*
	//レッスン１：CカードとRカードをそれぞれ50％の確立で起動時に表示せよ
	int rnd = KdGetInt(0, 1);
	//結果を出力
	OutputDebugStringA("----------------------------------\n");
	std::stringstream ss;
	if (rnd)
	{
		ss << "Cカード";

	}
	else
	{
		ss << "Rカード";
	}
	ss << " Get!\n";
	std::string str = ss.str();
	OutputDebugStringA(str.c_str());
	OutputDebugStringA("----------------------------------\n");
	*/

	/*
	//レッスン２：Cカードを99.5%、Rカードを0.5%の確率で起動時に表示せよ
	int _bunbo = 1000;
	int _thusenNum = 10000000;
	int _tosenNum[2] = { 0,0 };
	for (int i = 0; i < _thusenNum; i++)
	{
		int _rnd = KdGetFloat(0, _bunbo - 1);
		if (_rnd < 5)
		{
			_tosenNum[1]++;
		}
		else
		{
			_tosenNum[0]++;
		}
	}

	OutputDebugStringA("----------------------------------\n");
	float _prob = 0;
	for (int i = 0; i < 2; i++)
	{
		std::stringstream ss;
		_prob = ((float)_tosenNum[i] / (float)_thusenNum) * 100;
		round_n(_prob, 3);
		switch (i)
		{
		case 0:
			ss << "Cカード当選回数" << _tosenNum[0] << " " <<
				"当選確率 = " << _prob << "%" << "\n";
			break;
		case 1:
			ss << "Rカード当選回数" << _tosenNum[1] << " " <<
				"当選確率 = " << _prob << "%" << "\n";
		}
		std::string str = ss.str();
		OutputDebugStringA(str.c_str());
	}
	OutputDebugStringA("----------------------------------\n");
	*/

	/*
	//レッスン３：Cカードを34%、Rカードを33%、SRカードを33%の確立で起動時に表示せよ
	int _bunbo = 100;
	int _randNum[3] = { 34,33,33 };	//抽選値
	int _thusenNum = 10000000;
	int _tosenNum[3] = { 0,0,0 };
	for (int i = 0; i < _thusenNum; i++)
	{
		int _rnd = KdGetInt(0, _bunbo - 1);
		for (int j = 0; j < std::size(_randNum); j++)
		{
			_rnd -= _randNum[j];
			if (_rnd < 0)
			{
				_tosenNum[j]++;
				break;
			}
		}
	}

	OutputDebugStringA("----------------------------------\n");
	float _prob = 0;
	for (int i = 0; i < std::size(_randNum); i++)
	{
		std::stringstream ss;
		_prob = ((float)_tosenNum[i] / (float)_thusenNum) * 100;
		round_n(_prob, 3);
		switch (i)
		{
		case 0:
			ss << "Cカード当選回数" << _tosenNum[0] << " " <<
				"当選確率 = " << _prob << "%" << "\n";
			break;
		case 1:
			ss << "Rカード当選回数" << _tosenNum[1] << " " <<
				"当選確率 = " << _prob << "%" << "\n";
			break;
		case 2:
			ss << "SRカード当選回数" << _tosenNum[2] << " " <<
				"当選確率 = " << _prob << "%" << "\n";
			break;
		}
		std::string str = ss.str();
		OutputDebugStringA(str.c_str());
	}
	OutputDebugStringA("----------------------------------\n");
	*/

	//レッスン４：CカードとRカードとSRカードをそれぞれ50%、49.5%、0.5%の確立で起動時に表示せよ
	int _bunbo = 1000;
	int _randNum[3] = { 500,495,5 };	//抽選値
	int _thusenNum = 10000000;
	int _tosenNum[3] = { 0,0,0 };
	for (int i = 0; i < _thusenNum; i++)
	{
		int _rnd = KdGetInt(0, _bunbo - 1);
		for (int j = 0; j < std::size(_randNum); j++)
		{
			_rnd -= _randNum[j];
			if (_rnd < 0)
			{
				_tosenNum[j]++;
				break;
			}
		}
	}

	OutputDebugStringA("----------------------------------\n");
	float _prob = 0;
	for (int i = 0; i < std::size(_randNum); i++)
	{
		std::stringstream ss;
		_prob = ((float)_tosenNum[i] / (float)_thusenNum) * 100;
		round_n(_prob, 3);
		switch (i)
		{
		case 0:
			ss << "Cカード当選回数" << _tosenNum[0] << " " <<
				"当選確率 = " << _prob << "%" << "\n";
			break;
		case 1:
			ss << "Rカード当選回数" << _tosenNum[1] << " " <<
				"当選確率 = " << _prob << "%" << "\n";
			break;
		case 2:
			ss << "SRカード当選回数" << _tosenNum[2] << " " <<
				"当選確率 = " << _prob << "%" << "\n";
			break;
		}
		std::string str = ss.str();
		OutputDebugStringA(str.c_str());
	}
	OutputDebugStringA("----------------------------------\n");

}

void GameScene::Event()
{
	if (GetAsyncKeyState('E') & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
	}
}
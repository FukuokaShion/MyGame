/**
 * @file GlobalVariables.h
 * @brief 調整項目管理
 */
#pragma once
#include<variant>
#include<map>
#include<string>
#include"Vector3.h"
#include<json.hpp>

using namespace std;
using json = nlohmann::json;

class GlobalVariables {
public:
	/**
	 * @brief インスタンス取得
	*/
	static GlobalVariables* GetInstance();
	/**
	 * @brief 更新
	*/
	void Update();
	/**
	 * @brief 全ファイル読み込み
	*/
	void LoadFiles();
	/**
	 * @brief グループ作成
	*/
	void CreateGroup(const string& groupNmae);
	/**
	 * @brief int値取得
	*/
	int32_t GetIntValue(const string& groupName, const string& key)const;
	/**
	 * @brief float値取得
	*/
	float GetFloatValue(const string& groupName, const string& key)const;
	/**
	 * @brief vector3値取得
	*/
	Vector3 GetVector3Value(const string& groupName, const string& key)const;
	/**
	 * @brief 項目追加(int)
	*/
	void AddItem(const string& groupName, const string& key, int32_t value);
	/**
	 * @brief 項目追加(float)
	*/
	void AddItem(const string& groupName, const string& key, float value);
	/**
	 * @brief 項目追加(Vector3)
	*/
	void AddItem(const string& groupName, const string& key, const Vector3& value);
private:
	/**
	 * @brief ファイル読み込み
	*/
	void LoadFile(const string& groupName);
	/**
	 * @brief ファイル書き出し
	*/
	void SaveFile(const string& groupName);
	/**
	 * @brief 値セット(int)
	*/
	void SetValue(const string& groupName, const string& key, int32_t value);
	/**
	 * @brief 値セット(float)
	*/
	void SetValue(const string& groupName, const string& key, float value);
	/**
	 * @brief 値セット(Vector3)
	*/
	void SetValue(const string& groupName, const string& key,const Vector3& value);
private:
	//項目
	struct Item {
		variant<int32_t, float, Vector3> value;
	};
	//グループ
	struct Group {
		map<string, Item> items;
	};

private:
	//保存先ファイルパス
	const string kDirectoryPath = "Resources/GlobalVariables/";
	map<string, Group> datas_;
};
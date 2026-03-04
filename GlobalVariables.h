//====================================
// グローバル変数を管理するクラス
//====================================
#pragma once
#include <json.hpp> // JSONライブラリのインクルード
#include <map>      // マップ（連想配列）を扱うため
#include <string>   // 文字列を扱うため
#include <variant>  // 複数の型を扱うためのstd::variant

using json = nlohmann::json; // nlohmann::json;は長いのでjsonだけで書けるよう省略する

class GlobalVariables {};

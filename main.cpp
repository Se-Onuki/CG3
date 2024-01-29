#include <cstdio>
#include <iostream>

#include <condition_variable>
#include <mutex>
#include <thread>

#include "CSV.h"
#include "File.h"

int main(void)
{
	// 排他的処理のためのミューテックス
	std::mutex mutex;
	// 排他的処理のための条件変数
	std::condition_variable condition;

	// CSVファイル
	SoLib::IO::CSV csv;
	// ループを抜けるためのフラグ
	bool exit = false;

	// バックグラウンド処理
	std::thread th([&]()
		{
			// 離脱フラグが立っていない場合ループする
			while (not exit) {
				// csvが空なら読み込む
				if (not csv) {
					// スレッド開始時にロック用のクラスのインスタンスを生成
					std::unique_lock<std::mutex> uniqueLock(mutex); // lock関数だと、unlock関数を呼び忘れるリスクがあるため
					// lockを呼んだスレッドで使用している変数へのアクセスをlockする。

					// スレッドを停止
					condition.wait(uniqueLock, [&]()->bool
						{
							// csvのデータが存在しない場合
							return not static_cast<bool>(csv);
						});

					csv = SoLib::IO::File{ "test.csv" };
				}
			}
		});

	while (true) {
		std::unique_lock<std::mutex> uniqueLock(mutex); // lock関数だと、unlock関数を呼び忘れるリスクがあるため
		// csvの表示
		if (csv) {
			for (const auto &line : csv.Get()) {
				std::stringstream stream{};
				for (auto &item : line) {
					stream << item << ", ";
				}
				std::cout << stream.str() << std::endl;
			}
			break;
		};
		condition.notify_all();
	}

	exit = true;
	th.join();

	return 0;
}
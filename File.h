#pragma once
#include <string>
#include <fstream>
#include <sstream>

#include <variant>
#include <optional>

namespace SoLib {

	namespace IO {

		class File {
		public:
			File() = default;
			// コンストラクタ
			File(const std::string &filePath) {
				Load(filePath);
			}

			bool Load(const std::string &filePath) {
				std::ifstream file(filePath);
				if (not file) {
					// std::cerr << "ファイルが開けません。" << std::endl;
					return false;
				}

				data_ << file.rdbuf();
				file.close();

				filePath_ = filePath;
				return true;
			}

			// データを取得する
			auto &GetData() { return data_; }
			const auto &GetData() const { return data_; }
			const std::string &GetFilePath() const { return filePath_; }

			operator bool() const { return filePath_.size(); }

		private:
			std::string filePath_;
			std::stringstream data_;
		};
	}
}
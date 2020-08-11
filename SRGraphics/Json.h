#pragma once
#include <string>
#include <sstream>
#include <fstream>

#include <jansson.h>
#pragma comment(lib, "jansson.lib")

namespace SpaRcle {
	namespace Helper {
		class Json {
		private:
			json_t* root = nullptr;
			json_error_t error;
		private:
			Json() {};
		public:
			~Json() {
				json_decref(root);
			};
		public:
			static Json* Create() {
				Json* json = new Json();
				return json;
			}
			static Json* Load(std::string path) {
				Json* json = new Json();

				std::ifstream in(path);
				std::string data = "", line = ""; //TODO: Load file 
				while (!in.eof()) {
					std::getline(in, line);
					data += line;
				}
					

				json->root = json_loads(data.c_str(), 0, &json->error);
				if (!json->root) {
					fprintf(stderr, "Json error: on line %d: %s\n", json->error.line, json->error.text);
					delete json;
					json = nullptr;
					return nullptr;
				}
				
				return json;
			}
		public:
			std::string GetString(const std::string& key) {
				json_t* data = json_object_get(root, key.c_str());
				if (!json_is_string(data)) {
					fprintf(stderr, "Json error : ");
					return "";
				}
				std::string value = json_string_value(data);
				json_decref(root);
				return value;
			}
			void Save(std::string path) {

			}
		};
	}
}

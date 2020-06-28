#pragma once
#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <string>
#include <direct.h>
#include <errno.h>
#include <sys/stat.h>
#include <limits> 

#pragma comment(lib, "User32.lib")

#if defined(max)
#undef max
#endif

namespace SpaRcle {
	namespace Helper {
		class File {
		private:
			File() { };
			~File() { };
		public:
			static std::vector<std::string> GetFilesInDirectory(const char* dir) {
				std::vector<std::string> files = std::vector<std::string>(0);

				for (const auto& entry : std::filesystem::directory_iterator(dir))
					files.push_back(entry.path().string()); ///$Warning

				return files;
			}
			static int FindInFile(std::ifstream& file, const char* string) {
				if (!string) return -2;
				
				if (!file.is_open()) { 
					Debug::InternalError("File is not open!"); 
					Sleep(2000);
					return -3;
				}

				file.clear();
				file.seekg(0, std::ios_base::beg);
				
				std::string s;
				int count = 0;
				while (std::getline(file, s)) {
					count++;
					if (s == string) {
						return count;
					}
					//std::cout << count << "\t" << s << std::endl;
				}

				return -1;
			}
			static int FindInFile(std::fstream& file, const char* string) {
				if (!string) return -2;

				std::string s;
				int count = 0;

				//file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				file.clear();

				while (std::getline(file, s)) {
					count++;
					if (s == string) {
						//file.seekg(0, std::ios_base::beg);

						return count;
					}
				}

				//file.seekg(0, std::ios_base::beg);

				return -1;
			}
			static int FindInFile(const char* file, const char* string) {
				if (!string) return -2;

				std::ifstream ifs;
				ifs.open(file);

				if (ifs.is_open()) {
					std::string s;
					int count = 0;
					while (std::getline(ifs, s)) {
						count++;
						if (s == string) {
							ifs.close();
							return count;
						}
						//std::cout << count << "\t" << s << std::endl;
					}
				}
				ifs.close();
				return -1;
			}

			/*
				Example: C:\\Users\\*
				Russian folders is not finds!
			*/
			static std::vector<std::string> GetFolders(const char* dir) {
				std::vector<std::string> folders = std::vector<std::string>(0);

				WIN32_FIND_DATAW wfd;

				//HANDLE const hFind = FindFirstFileW(L"C:\\Users\\*", &wfd);
				HANDLE const hFind = FindFirstFileW(String::CharsToLPWSTR(dir), &wfd);

				char c = 0;
				if (INVALID_HANDLE_VALUE != hFind) {
					do {
						if (c < 2) { c++; continue; }
						if ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) {
							folders.push_back(String::LPCWSTRToChars(&wfd.cFileName[0]));
							//std::wcout << &wfd.cFileName[0] << std::endl;
						}
					} while (NULL != FindNextFileW(hFind, &wfd));

					FindClose(hFind);
				}
				/*
				LPWIN32_FIND_DATA data = new WIN32_FIND_DATA();
				//HANDLE h = FindFirstFile(L"*.*", data);
				HANDLE h = FindFirstFile(String::CharsToLPWSTR(dir), data);
				//HANDLE h = FindFirstFile(L"J:\\Collections\\Collection 1\\Sorted\\", data);
				if (data->dwFileAttributes | FILE_ATTRIBUTE_DIRECTORY) {
					std::string str = String::LPCWSTRToChars(data->cFileName);
					std::cout << str << std::endl;
				}
				*/
				return folders;
			}

			inline static bool CreateDir(const char* dir) { _mkdir(dir); }
			inline static bool DirExists(const char* folder) {
				static struct stat sb;
				if (stat(folder, &sb) == 0)
					return true;
				else
					return false;
			}
			inline static bool FileExists(const std::string& name) {
				static struct stat buffer;
				return (stat(name.c_str(), &buffer) == 0);
			}
			static unsigned long long CountLinesInFile(const char* file) {
				std::ifstream in(file);
				std::string s;
				unsigned long long i = 0;
				while (in.peek() != EOF) {
					getline(in, s);
					i++;
				}
				in.close();
				return i;
			}
		};
	}
}
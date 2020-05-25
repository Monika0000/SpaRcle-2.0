#pragma once
#include <string>

namespace SpaRcle {
	namespace Network {
		__interface IPackage { //__interface
		 //private:
			 //char* str;
		 //public:
			 //IPackage() { };
			 //~IPackage() { if (str) delete[] str; };
			/*
				������ ��������� ������������ ��� �������� ������, ������� ���������� ���������/�������� ����� ��������
				�����, ������� ��������� ���� ���������, ����� ���� ������� � ����� Send, � ��������� �������, ��������� ������ GetData,
				� ����� Recv ���������� ��������� ��� ������, �������� ��� ���� ������, ��������� ����� SetData
			*/
			virtual std::string GetSendData() = 0;
			virtual bool SetData(std::string data) = 0;
			//operator char*() { return str; }
		};
	}
}
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
				ƒанный интерфейс предназначен дл€ харнени€ данных, которые необходимо отправить/получить через интернет
				 ласс, который реализует этот интерфейс, может быть передан в метод Send, и отправлен клиенту, благодар€ методу GetData,
				а метод Recv возвращает указанный тип данных, заполн€€ его пол€ данных, использу€ метод SetData
			*/
			virtual std::string GetSendData() = 0;
			virtual bool SetData(std::string data) = 0;
			//operator char*() { return str; }
		};
	}
}
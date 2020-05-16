#pragma once
namespace SpaRcle {
	class Core {
	public:
		virtual void* GetData() { return nullptr; } ///$TODO
	public:
		virtual bool Init() { return false; };
		virtual bool Run() { return false; };
		virtual bool Close() { return false; };
	};
}
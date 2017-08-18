#pragma once
class IScene
{
public:
	virtual ~IScene() = 0;
	virtual void Init() = 0;
	virtual void End() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};


#pragma once


class Bounds
{
public:
	Bounds(float x, float y, float width = 1.f, float height = 1.f)
		:x(x), y(y), width(width), height(height)
	{
	}
	// ��ħ ����
	bool Instersect(const Bounds& other)const;

	// Getter Setter
	float GetX() const { return x; }
	float GetY() const { return y; }
	float GetWidth()  const { return width; }
	float GetHegith() const {return height;}

	float MaxX() const { return x + width; }
	float MaxY() const { return y + height; }

private:
	// ��ġ ������ �»��
	float x = 0.f;
	float y = 0.f;
	float width = 1.f;
	float height = 1.f;

};
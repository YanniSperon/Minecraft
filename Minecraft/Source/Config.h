#pragma once

class Config {
private:
	int m_StartingWidth, m_StartingHeight;
	bool m_HasVSync;
public:
	Config();

	void Load();
	void Save();

	bool GetStartingWidth();
	bool GetStartingHeight();
	bool GetHasVSync();

	void SetStartingWidth(unsigned int width);
	void SetStartingHeight(unsigned int height);
	void SetHasVSync(bool hasVSync);
};
#pragma once

class Config {
private:
	int m_StartingWidth;
	int m_StartingHeight;
	bool m_HasVSync;
	float m_FOV;
	bool m_HasSmoothLighting;
	int m_RenderDistance;
	int m_ParticleQuality;
	int m_ShadowQuality;
public:
	Config();

	void Load();
	void Save();

	int GetStartingWidth();
	int GetStartingHeight();
	bool GetHasVSync();
	float GetFOV();
	bool GetHasSmoothLighting();
	int GetRenderDistance();
	int GetParticleQuality();
	int GetShadowQuality();

	void SetStartingWidth(int width);
	void SetStartingHeight(int height);
	void SetHasVSync(bool hasVSync);
	void SetFOV(float fov);
	void SetHasSmoothLighting(bool hasSmoothLighting);
	void SetRenderDistance(int renderDistance);
	void SetParticleQuality(int particleQuality);
	void SetShadowQuality(int shadowQuality);
};
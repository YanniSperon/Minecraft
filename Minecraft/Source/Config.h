#pragma once

class Config {
private:
	int m_StartingWidth;
	int m_StartingHeight;
	bool m_HasVSync;
	bool m_HasRawMouseInput;
	float m_FOV;
	float m_MouseSensitivity;
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
	bool GetHasRawMouseInput();
	float GetFOV();
	float GetMouseSensitivity();
	bool GetHasSmoothLighting();
	int GetRenderDistance();
	int GetParticleQuality();
	int GetShadowQuality();

	void SetStartingWidth(int width);
	void SetStartingHeight(int height);
	void SetHasVSync(bool hasVSync);
	void SetHasRawMouseInput(bool rawMouseInput);
	void SetFOV(float FOV);
	void SetMouseSensitivity(float mouseSensitivity);
	void SetHasSmoothLighting(bool hasSmoothLighting);
	void SetRenderDistance(int renderDistance);
	void SetParticleQuality(int particleQuality);
	void SetShadowQuality(int shadowQuality);
};
#pragma once
class TextureManager
{
private:
	TextureManager();
	bool CacheTexture(string _name, const char* _fName);
	unordered_map<string, TexturePtr> mNameToTextureMap;

public:
	static void StaticInit();
	static std::unique_ptr<TextureManager> sInstance;
public:
	TexturePtr GetTexture(const string& _name);
};


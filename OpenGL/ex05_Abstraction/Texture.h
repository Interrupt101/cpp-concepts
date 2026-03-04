#pragma once

#include "Renderer.h"

class Texture
{
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;

public:
    Texture(const std::string& path);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    // ===== Getters =====
    inline unsigned int GetRendererID() const { return m_RendererID; }
    inline const std::string& GetFilePath() const { return m_FilePath; }
    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    inline int GetBPP() const { return m_BPP; }
};
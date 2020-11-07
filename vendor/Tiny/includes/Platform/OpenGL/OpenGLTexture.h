#pragma once

#include <string.h>

#include "Tiny/Renderer/Texture.h"

namespace Tiny {

	enum class TextureLoader
	{
		STB_IMAGE = 0,
		BMPCustom = 1
	};

	class OpenGLTexture : public Texture2D
	{
	public:
		OpenGLTexture(const std::string& path);
		~OpenGLTexture();

		virtual unsigned int GetWidth() const override { return m_Width; }
		virtual unsigned int GetHeight() const override { return m_Height; }

		virtual void Bind(unsigned int slot = 0) const override;

		void UseSTBLoader();
		void UseBMPCustomLoader();

		inline unsigned int GetTextureID() const override { return m_TextureID; };

	private:
		void STBLoader();
		void BMPCustomLoader();

	private:
		const std::string m_Path;
		unsigned int m_Width, m_Height;
		unsigned int m_TextureID;
		TextureLoader LOADER;

	};
}



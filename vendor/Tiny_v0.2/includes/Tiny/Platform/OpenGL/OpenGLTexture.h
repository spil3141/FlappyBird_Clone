#pragma once

#include "Tiny/Renderer/Texture.h"

#include "glad/glad.h"

namespace Tiny {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual uint32_t GetRendererID() const override { return m_RendererID; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;

		virtual bool operator==(const Texture& other) const override
		{
			return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
		}
	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};

	//enum class TextureLoader
	//{
	//	STB_IMAGE = 0,
	//	BMPCustom = 1
	//};

	//class OpenGLTexture2D : public Texture2D
	//{

	///*public:
	//	OpenGLTexture2D(const std::string& path);
	//	~OpenGLTexture2D();

	//	virtual unsigned int GetWidth() const override { return m_Width; }
	//	virtual unsigned int GetHeight() const override { return m_Height; }

	//	virtual void Bind(unsigned int slot = 0) const override;

	//	void UseSTBLoader();
	//	void UseBMPCustomLoader();

	//	inline unsigned int GetTextureID() const override { return m_TextureID; };

	//private:
	//	void STBLoader();
	//	void BMPCustomLoader();

	//private:
	//	const std::string m_Path;
	//	unsigned int m_Width, m_Height;
	//	unsigned int m_TextureID;
	//	TextureLoader LOADER;*/

	//};
}



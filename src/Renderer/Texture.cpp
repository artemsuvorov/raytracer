#include "Precompiled.h"
#include "Texture.h"

#include <GL/glew.h>

using namespace Core;

static uint32_t ImageFormatToEnum(ImageFormat format)
{
    switch (format)
    {
        case ImageFormat::kRgb8:    return GL_RGB;
        case ImageFormat::kRgba8:   return GL_RGBA;
        case ImageFormat::kRgba32f: return GL_RGBA32F;
    }

    assert(false && "Unexpected image format.");
    return 0;
}

static uint32_t ImageFilterToEnum(ImageFilter filter)
{
    switch (filter)
    {
        case ImageFilter::kLinear:  return GL_LINEAR;
        case ImageFilter::kNearest: return GL_NEAREST;
    }
    
    assert(false && "Unexpected image filter.");
    return 0;
}

static uint32_t TextureWrapToEnum(TextureWrap wrapping)
{
    switch (wrapping)
    {
        case TextureWrap::kRepeat:      return GL_REPEAT;
        case TextureWrap::kClampToEdge: return GL_CLAMP_TO_EDGE;
    }

    assert(false && "Unexpected textrue wrapping.");
    return 0;
}

TextureBuilder Texture::Create()
{
    return TextureBuilder();
}

Texture::Texture(const TextureSpecification& specification)
    : m_DataFormat(specification.Format), m_Width(specification.Width), m_Height(specification.Height)
{
    glCreateTextures(GL_TEXTURE_2D, 1, &m_Id);

    const uint32_t filter = ImageFilterToEnum(specification.Filter);
    glTextureParameteri(m_Id, GL_TEXTURE_MIN_FILTER, filter);
    glTextureParameteri(m_Id, GL_TEXTURE_MAG_FILTER, filter);

    const uint32_t wrapping = TextureWrapToEnum(specification.Wrapping);
    glTextureParameteri(m_Id, GL_TEXTURE_WRAP_S, wrapping);
    glTextureParameteri(m_Id, GL_TEXTURE_WRAP_T, wrapping);

    const uint32_t format = ImageFormatToEnum(specification.Format);
    glTextureStorage2D(m_Id, 1, format, m_Width, m_Height);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_Id);
}

void Texture::Bind(uint32_t slot) const
{
    glBindTextureUnit(slot, m_Id);
}

void Texture::BindWriteLevel(uint32_t slot, uint32_t level) const
{
    static constexpr const uint32_t kAccess = GL_WRITE_ONLY;
    const uint32_t format = ImageFormatToEnum(m_DataFormat);
	glBindImageTexture(slot, m_Id, level, GL_FALSE, 0, kAccess, format);
}

void Texture::SetData(void* data, uint32_t size)
{
    const uint32_t format = ImageFormatToEnum(m_DataFormat);
    const uint32_t bpp = format == GL_RGBA ? 4 : 3;
    assert(size == m_Width * m_Height * bpp && "Data must be entire texture.");
    glTextureSubImage2D(m_Id, 0, 0, 0, m_Width, m_Height, format, GL_UNSIGNED_BYTE, data);
}

TextureBuilder& TextureBuilder::WithSize(uint32_t width, uint32_t height)
{
    m_Specification.Width = width;
    m_Specification.Height = height;
    return *this;
}

TextureBuilder& TextureBuilder::WithFormat(ImageFormat format)
{
    m_Specification.Format = format;
    return *this;
}

TextureBuilder& TextureBuilder::WithFilter(ImageFilter filter)
{
    m_Specification.Filter = filter;
    return *this;
}

TextureBuilder& TextureBuilder::WithWrapping(TextureWrap wrapping)
{
    m_Specification.Wrapping = wrapping;
    return *this;
}

std::shared_ptr<Texture> TextureBuilder::Build()
{
    return std::make_shared<Texture>(m_Specification);
}

#pragma once

namespace Core {

enum class ImageFormat
{
    kNone = 0,
    kR8,
    kRgb8,
    kRgba8,
    kRgba32f,
};

enum class ImageFilter
{
    kNone = 0,
    kLinear,
    kNearest,
};

enum class TextureWrap
{
    kNone = 0,
    kRepeat,
    kClampToEdge,
};

struct TextureSpecification
{
    uint32_t Width = 1, Height = 1;
    
    ImageFormat Format = ImageFormat::kRgba8;
    ImageFilter Filter = ImageFilter::kLinear;
    TextureWrap Wrapping = TextureWrap::kRepeat;

    bool GenerateMips = true;
};

// Forwards.
class TextureBuilder;

class Texture final
{
public:
    static TextureBuilder Create();

    Texture(const TextureSpecification& specification);
    ~Texture();

public:
    uint32_t GetWidth() const { return m_Width; }
    uint32_t GetHeight() const { return m_Height; }

    void Bind(uint32_t slot = 0) const;
    void BindWriteLevel(uint32_t slot = 0, uint32_t level = 0) const;

    void SetData(void* data, uint32_t size);

    bool operator==(const Texture& other) const
    {
        return m_Id == other.m_Id;
    }

private:
    uint32_t m_Id;
    
    ImageFormat m_DataFormat;
    uint32_t m_Width, m_Height;
};

class TextureBuilder final
{
public:
    TextureBuilder& WithSize(uint32_t width, uint32_t height);
    TextureBuilder& WithFormat(ImageFormat format);
    TextureBuilder& WithFilter(ImageFilter filter);
    TextureBuilder& WithWrapping(TextureWrap wrapping);

    std::shared_ptr<Texture> Build();

private:
    TextureSpecification m_Specification;
};

}
#pragma once
#include <vector>
#include <utility>

enum class DataType{
    UNSIGNED_INT,
    INT,
    FLOAT
};

size_t size(DataType dataType);
unsigned int getGLIdentifier(DataType dataType);

typedef std::vector<std::pair<DataType, unsigned int>> VertexDataFormat;

class VertexBuffer{
public:
    VertexBuffer(const std::vector<float> data);
    VertexBuffer(unsigned int bufferSize);

    void bind() const;
    void unbind() const;

    void setDataFormat(const VertexDataFormat& format, unsigned int initialAttributeIndex = 0, unsigned int updateFrequency = 0) const;
    void setAttributeUpdate(unsigned int frequency);

private:
    unsigned int _handle;
};

class IndexBuffer{
public:
    IndexBuffer(const std::vector<unsigned int>& data);
    IndexBuffer(unsigned int bufferSize);

    void bind() const;
    void unbind() const;

private:
    unsigned int _handle;
};

class VertexArray{
public:
    VertexArray();

    void bind() const;
    void unbind() const;

private:
    unsigned int _handle;
};
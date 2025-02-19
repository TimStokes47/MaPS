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

    void setDataFormat(const VertexDataFormat& format) const;

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
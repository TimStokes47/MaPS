#include "buffers.h"
#include <glad/gl.h>

VertexBuffer::VertexBuffer(const std::vector<float> data)
{
    glGenBuffers(1, &_handle);
    bind();
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
    unbind();
}

VertexBuffer::VertexBuffer(unsigned int bufferSize)
{
    glGenBuffers(1, &_handle); 
    bind();
    glBufferData(GL_ARRAY_BUFFER, bufferSize * sizeof(float), nullptr, GL_STATIC_DRAW);  
    unbind();
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _handle);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

size_t size(DataType dataType){
    switch (dataType){
        case DataType::UNSIGNED_INT:
            return sizeof(unsigned int);
        case DataType::INT:
            return sizeof(int);
        case DataType::FLOAT:
            return sizeof(float);
    }

    return -1;
}

unsigned int getGLIdentifier(DataType dataType){
    switch (dataType){
        case DataType::UNSIGNED_INT:
            return GL_UNSIGNED_INT;
        case DataType::INT:
            return GL_INT;
        case DataType::FLOAT:
            return GL_FLOAT;
    }

    return -1;
}

void VertexBuffer::setDataFormat(const VertexDataFormat &format, unsigned int initialAttributeIndex, unsigned int updateFrequency) const
{
    size_t stride = 0;
    for (auto& typeBlock : format){
        stride += size(typeBlock.first) * typeBlock.second;
    }

    unsigned int index = initialAttributeIndex;
    size_t offset = 0;
    for (auto& typeBlock : format){
        size_t typeBlockSize = size(typeBlock.first) * typeBlock.second;
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, typeBlock.second, getGLIdentifier(typeBlock.first), GL_FALSE, typeBlockSize, (void*)offset);
        glVertexAttribDivisor(index, updateFrequency);
        offset += typeBlockSize;
    }
}

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &_handle);
}

void VertexArray::bind() const
{
    glBindVertexArray(_handle);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

IndexBuffer::IndexBuffer(const std::vector<unsigned int> &data)
{
    glGenBuffers(1, &_handle);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), data.data(), GL_STATIC_DRAW);
    unbind();
}

IndexBuffer::IndexBuffer(unsigned int bufferSize)
{
    glGenBuffers(1, &_handle);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize * sizeof(unsigned int), nullptr, GL_STATIC_DRAW);
    unbind();
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _handle);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

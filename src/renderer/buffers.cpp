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

void VertexBuffer::setDataFormat(const VertexDataFormat &format) const
{
    size_t stride = 0;
    for (auto& typeBlock : format){
        stride += size(typeBlock.first) * typeBlock.second;
    }

    unsigned int index = 0;
    size_t offset = 0;
    for (auto& typeBlock : format){
        size_t typeBlockSize = size(typeBlock.first) * typeBlock.second;
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, typeBlock.second, getGLIdentifier(typeBlock.first), GL_FALSE, typeBlockSize, (void*)offset);
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
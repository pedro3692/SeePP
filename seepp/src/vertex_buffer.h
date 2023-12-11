#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

#include <cstdint>

class VertexBuffer {
public:
    VertexBuffer();
    ~VertexBuffer();

    void SetData(float* vertices);
private:
    uint32_t m_id = 0;
};

#endif // VERTEX_BUFFER_H_

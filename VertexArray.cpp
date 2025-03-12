#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray(const float* verts, unsigned int numVerts,
	const unsigned int* indices, unsigned int numIndices)
	:mNumVerts(numVerts)
	, mNumIndices(numIndices)
{
	// vertex array 생성
	// 이제 사용할 Vertex Array에 대해 OpenGL ID 받아서 mVertexArray에 저장한 후에 
	// 이제부터 사용할 Vertex Array는 mVertexArray에 있는 것임을 OpenGL에 알려줌
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	// glGenBuffers(): 새로운 buffer object를 만든다
	//  glBindBuffer(): 지금부터 사용할 buffer object를 지정한다
	// glBufferData(): 지정된 buffer에 데이터를 복사한다
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, numVerts * 5 * sizeof(float), verts, GL_STATIC_DRAW);

	// GL_STATIC_DRAW: 딱 한번만 세팅되고 앞으로 계속 쓸 예정
	// GL_DYNAMIC_DRAW: 앞으로 데이터가 자주 바뀔 예정
	// GL_STREAM_DRAW: 딱 한번만 세팅되고 몇번 쓰다 버려질 예정

	// index buffer 생성
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// 정점 attribute 중 n번째를 사용하도록 설정
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5,
		reinterpret_cast<void*>(sizeof(float) * 3));
}// n: 정점의 n번째 attribute
	// size : 해당 attribute는 몇개의 값으로 구성되어 있는가?
	//	type : 해당 attribute의 데이터 타입
	//	normalized : 0~1사이의 값인가
	//	stride : 두 정점간의 간격(byte 단위)
	//	offset : 첫 정점의 헤당 attribute까지의 간격(byte 단위)

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArray);
}
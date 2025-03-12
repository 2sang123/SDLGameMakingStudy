#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray(const float* verts, unsigned int numVerts,
	const unsigned int* indices, unsigned int numIndices)
	:mNumVerts(numVerts)
	, mNumIndices(numIndices)
{
	// vertex array ����
	// ���� ����� Vertex Array�� ���� OpenGL ID �޾Ƽ� mVertexArray�� ������ �Ŀ� 
	// �������� ����� Vertex Array�� mVertexArray�� �ִ� ������ OpenGL�� �˷���
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	// glGenBuffers(): ���ο� buffer object�� �����
	//  glBindBuffer(): ���ݺ��� ����� buffer object�� �����Ѵ�
	// glBufferData(): ������ buffer�� �����͸� �����Ѵ�
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, numVerts * 5 * sizeof(float), verts, GL_STATIC_DRAW);

	// GL_STATIC_DRAW: �� �ѹ��� ���õǰ� ������ ��� �� ����
	// GL_DYNAMIC_DRAW: ������ �����Ͱ� ���� �ٲ� ����
	// GL_STREAM_DRAW: �� �ѹ��� ���õǰ� ��� ���� ������ ����

	// index buffer ����
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// ���� attribute �� n��°�� ����ϵ��� ����
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5,
		reinterpret_cast<void*>(sizeof(float) * 3));
}// n: ������ n��° attribute
	// size : �ش� attribute�� ��� ������ �����Ǿ� �ִ°�?
	//	type : �ش� attribute�� ������ Ÿ��
	//	normalized : 0~1������ ���ΰ�
	//	stride : �� �������� ����(byte ����)
	//	offset : ù ������ ��� attribute������ ����(byte ����)

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
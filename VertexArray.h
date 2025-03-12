#pragma once
class VertexArray
{
	// 버텍스버퍼 포인터와 인덱스버퍼포인터를 인자로 받음
	// OpenGL에 바인딩시키는 일련의과정을 생성자에서 처리
public:
	VertexArray(const float* verts, unsigned int numVerts,
		const unsigned int* indices, unsigned int numIndices);
	~VertexArray();

	// vertex array를 활성화
	void SetActive();
	// vertex buffer 안에 벌텍스는 몇 개인지
	unsigned int GetNumIndices() const { return mNumIndices; }
	// How many indices in the index buffer
	// index buffer 안에 인덱스는 몇 개 인지
	unsigned int GetNumVerts() const { return mNumVerts; }
private:
	// vertex buffer 안에 벌텍스는 몇 개인지
	unsigned int mNumVerts;
	// index buffer 안에 인덱스는 몇 개 인지
	unsigned int mNumIndices;
	// vertex buffer 안에 OpenGL Id 
	unsigned int mVertexBuffer;
	// index buffer 안에  OpenGL Id 
	unsigned int mIndexBuffer;
	//  vertex array 오브젝트 안에 OpenGL ID
	unsigned int mVertexArray;
};
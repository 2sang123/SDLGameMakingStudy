#pragma once
class VertexArray
{
	// ���ؽ����� �����Ϳ� �ε������������͸� ���ڷ� ����
	// OpenGL�� ���ε���Ű�� �Ϸ��ǰ����� �����ڿ��� ó��
public:
	VertexArray(const float* verts, unsigned int numVerts,
		const unsigned int* indices, unsigned int numIndices);
	~VertexArray();

	// vertex array�� Ȱ��ȭ
	void SetActive();
	// vertex buffer �ȿ� ���ؽ��� �� ������
	unsigned int GetNumIndices() const { return mNumIndices; }
	// How many indices in the index buffer
	// index buffer �ȿ� �ε����� �� �� ����
	unsigned int GetNumVerts() const { return mNumVerts; }
private:
	// vertex buffer �ȿ� ���ؽ��� �� ������
	unsigned int mNumVerts;
	// index buffer �ȿ� �ε����� �� �� ����
	unsigned int mNumIndices;
	// vertex buffer �ȿ� OpenGL Id 
	unsigned int mVertexBuffer;
	// index buffer �ȿ�  OpenGL Id 
	unsigned int mIndexBuffer;
	//  vertex array ������Ʈ �ȿ� OpenGL ID
	unsigned int mVertexArray;
};
#pragma once
#include <GL/glew.h>
#include <string>
#include "Math.h"

class Shader
{
public:
	Shader();
	~Shader();
	
	// ���� �̸��� �°� vert�� frag �ε�
	bool Load(const std::string& vertName, const std::string& fragName);
	void Unload();
	// ���̴� ���α׷����� ����
	void SetActive();
	void SetMatrixUniform(const char* name, const Matrix4& matrix);
private:
	// ������ ���̴� ������
	bool CompileShader(const std::string& fileName,
		GLenum shaderType,
		GLuint& outShader);
	// ������ Ȯ��
	bool IsCompiled(GLuint shader);
	// ���α׷� ���� Ȯ��
	bool IsValidProgram();

	// ���̴� ������Ʈ ID�� ����
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;
};
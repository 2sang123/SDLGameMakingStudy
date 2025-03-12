#pragma once
#include <GL/glew.h>
#include <string>
#include "Math.h"

class Shader
{
public:
	Shader();
	~Shader();
	
	// 받은 이름에 맞게 vert와 frag 로드
	bool Load(const std::string& vertName, const std::string& fragName);
	void Unload();
	// 셰이더 프로그램으로 설정
	void SetActive();
	void SetMatrixUniform(const char* name, const Matrix4& matrix);
private:
	// 지정된 셰이더 컴파일
	bool CompileShader(const std::string& fileName,
		GLenum shaderType,
		GLuint& outShader);
	// 컴파일 확인
	bool IsCompiled(GLuint shader);
	// 프로그램 연결 확인
	bool IsValidProgram();

	// 셰이더 오브젝트 ID를 저장
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;
};
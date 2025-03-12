#version 330
//세계 변환 및 뷰-투영 행렬을 위한 uniform
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

// 속성을 변수의 저장
// layout은 저장 공간이 어떤 변수에 해당하는 지를 지정한다
// 속성 0은 위치, 1은 텍스쳐 좌표
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;
// 텍스쳐 좌표를 출력에 추가
out vec2 fragTexCoord;

void main()
{
	// 위치를 같은 차원의 좌표로 변환
	vec4 pos = vec4(inPosition, 1.0);
	// 위치를 세계 공간으로 변환
	gl_Position = pos * uWorldTransform * uViewProj;
	// 텍스처 좌표를 frag에 전달
	fragTexCoord = inTexCoord;
}
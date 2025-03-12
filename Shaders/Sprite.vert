#version 330
//���� ��ȯ �� ��-���� ����� ���� uniform
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

// �Ӽ��� ������ ����
// layout�� ���� ������ � ������ �ش��ϴ� ���� �����Ѵ�
// �Ӽ� 0�� ��ġ, 1�� �ؽ��� ��ǥ
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;
// �ؽ��� ��ǥ�� ��¿� �߰�
out vec2 fragTexCoord;

void main()
{
	// ��ġ�� ���� ������ ��ǥ�� ��ȯ
	vec4 pos = vec4(inPosition, 1.0);
	// ��ġ�� ���� �������� ��ȯ
	gl_Position = pos * uWorldTransform * uViewProj;
	// �ؽ�ó ��ǥ�� frag�� ����
	fragTexCoord = inTexCoord;
}
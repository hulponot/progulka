#version 330

layout(location = 0) in vec3 vp;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;

out vec4 position;
out vec2 uv_Coord;
out float brightness;

uniform mat4 matT;
uniform mat4 matR;
uniform mat4 matS;
uniform mat4 matProj;
uniform mat4 matView;

uniform vec3 mainLight;

void main(){
	vec3 _normal = vec3(0.0,1.0,0.0);
	position = matT*matR*matS*vec4(vp,1.0f);
	uv_Coord = uv;
	brightness = clamp(dot( _normal, -position.xyz+mainLight.xyz ),0,1);

	gl_Position = matProj*matView*position;
	position = gl_Position;
}
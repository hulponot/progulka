#version 330

in vec4 position;
in vec2 uv_Coord;
in float brightness;

uniform sampler2D textureSampler;

out vec4 frag_Color;
void main(){
	frag_Color = clamp( brightness*texture(textureSampler, uv_Coord,0),0,1);
}
#version 130

//uniform mat4 Matrix;
//uniform mat4 viewMatrix;
//uniform mat4 modelMatrix;

uniform vec3 rotate;
uniform vec2 pos;
uniform float scale;

in vec3 position;

//in vec4 in_color;
out vec4 inColor;

void main(){
	vec3 rot = radians(rotate);
	vec3 c = cos(rot);
	vec3 s = sin(rot);

	mat4 rx = transpose(mat4( 1.0, 0.0, 0.0, 0.0,
					0.0, c.x, s.x, 0.0,
					0.0,-s.x, c.x, 0.0,
					0.0, 0.0, 0.0, 1.0)); 

	mat4 ry = transpose(mat4( c.y, 0.0,-s.y, 0.0,
					0.0, 1.0, 0.0, 0.0,
					s.y, 0.0, c.y, 0.0,
					0.0, 0.0, 0.0, 1.0)); 

	mat4 rz = transpose(mat4( c.z,-s.z, 0.0, 0.0,
					s.z, c.z, 0.0, 0.0,
					0.0, 0.0, 1.0, 0.0,
					0.0, 0.0, 0.0, 1.0)); 

	mat4 rotation = rz * ry * rx;
	mat4 translation = transpose(mat4(1.0, 0.0, 0.0, pos.x,
						    0.0, 1.0, 0.0, pos.y,
						    0.0, 0.0, 1.0, 0.0,
						    0.0, 0.0, 0.0, 1.0));

	mat4 scaleme = mat4(scale, 0.0,   0.0,   0.0,
						0.0,   scale, 0.0,   0.0,
						0.0,   0.0,   scale, 0.0,
						0.0,   0.0,   0.0,   1.0);

	gl_Position = translation * (scaleme * (rotation * vec4(position, 1.0)));
//	gl_Position = rz * ry * rx * vec4(position, 1.0); 
//	gl_Position = rotate * vec4(in_position, 1.0); 
//	gl_Position=Matrix*viewMatrix*modelMatrix*vec4(in_position,1.0); 
	inColor = vec4(position.x + 0.5, position.y + 0.5, position.z + 0.5, 1.0);
}

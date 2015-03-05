attribute vec3 coord3d;
attribute vec2 texcoord;
varying vec2 f_texcoord;
uniform mat2 model;
uniform mat2 camera;
 
void main(void) 
{
  	gl_Position = vec4((coord3d.x + model[0][0]) * camera[0][0] + camera[1][0], 
  					   (coord3d.y + model[1][1]) * camera[0][1] + camera[1][1],
  						coord3d.z,
  						1.0);
  	f_texcoord = texcoord;
}
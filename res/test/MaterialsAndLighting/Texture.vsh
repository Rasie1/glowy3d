attribute vec3 position;
attribute vec3 normal;
attribute vec2 texcoord;

uniform mat4 mvp_matrix;

varying vec2 f_texcoord;
varying vec4 f_normal;
varying vec4 f_position;

void main()
{
    f_position = mvp_matrix *
                  vec4(position.x,
                       position.y,
                       position.z,
                       1);
    f_normal = vec4(normal.x, normal.y, normal.z, 1);
    f_texcoord = 
        texcoord;
        vec4(1,1,1,0.5);

    gl_Position = f_position;
}

#version 420 core
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_UV;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_world;

out vec3 v_position;
out vec3 v_normal;
out vec2 v_UV;

void main(){
    gl_Position = u_projection * u_view * u_world * vec4(a_position, 1.0);
    v_position = vec3(u_world * vec4(a_position, 1.0));
    v_normal = mat3(transpose(inverse(u_world))) * a_normal;
    v_UV = a_UV;
}
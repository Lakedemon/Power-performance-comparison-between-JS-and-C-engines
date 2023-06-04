#version 420 core
precision highp float;

in vec3 v_normal;
in vec2 v_UV;

uniform vec4 u_diffuse;
uniform vec3 u_lightDirection;
uniform sampler2D u_texture;

out vec4 outColor;

void main() {
    vec3 normal = normalize(v_normal);
    outColor = texture(u_texture, v_UV) * vec4(u_diffuse.rgb * dot(u_lightDirection, normal), u_diffuse.a);
}
#version 130

in vec3 input_vertex;
in vec2 UVs;

out vec2 texCoords;

uniform mat4 projection;
uniform mat4 view;

void main() {
    texCoords = UVs;
    gl_Position = projection * view * vec4(input_vertex, 1.0);
}

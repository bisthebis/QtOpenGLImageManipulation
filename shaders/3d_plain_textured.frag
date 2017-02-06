#version 330

uniform sampler2D diffTexture;

in vec2 texCoords;

out vec4 color;

void main() {
    color = texture(diffTexture, texCoords);
}
in vec2 i_vUv;
out vec2 o_vUv;

uniform vec2 uvScale;
uniform sampler2D image;
uniform float time;
uniform vec2 speed;

void main() {
    gl_FragColor = texture2D( image, i_vUv + ( speed * time ) );
}


/////////////////////////////////////////////////////////


uniform mat4 modelMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat3 normalMatrix;
uniform vec2 uvScale;

attribute vec3 position;
attribute vec3 normal;
attribute vec2 uv;
attribute vec2 uv2;

void main() {
  o_vUv = uv * uvScale;
  gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
}

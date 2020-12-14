#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"
#include "ScreenPos.glsl"

/*VERTEX_PROGRAM*/

/// Updated in external code
uniform float Time;
//uniform mat4 ModelViewMatrix;
//uniform mat4 ProjectionMatrix;
uniform sampler2D Texture0;

//in vec4 in_Vertex;
in vec4 in_TexCoord;

out vec2 out_TexCoord;
out vec4 out_FragColor;

void VS()
{
     //gl_Position = ProjectionMatrix * ModelViewMatrix * in_Vertex;

     out_TexCoord = vec2( in_TexCoord );
}

void PS()
{
   /// "u" coordinate is altered
   out_FragColor = texture( Texture0, vec2(out_TexCoord.x + Time, out_TexCoord.y) );
}

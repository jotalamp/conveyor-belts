#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"

#include "ScreenPos.glsl"

in vec4 UOffset;
in vec4 VOffset;

uniform float cScrollingSpeed;

#if defined(DIFFMAP) || defined(ALPHAMAP)
    varying vec2 vTexCoord;
#endif
#ifdef VERTEXCOLOR
    varying vec4 vColor;
#endif

void VS()
{
    mat4 modelMatrix = iModelMatrix;
    vec3 worldPos = GetWorldPos(modelMatrix);
    gl_Position = GetClipPos(worldPos);
    
    #ifdef DIFFMAP
        vTexCoord = iTexCoord;
    #endif
    #ifdef VERTEXCOLOR
        vColor = iColor;
    #endif
}

void PS()
{
		//ScrollingSpeed = 2.35;
    vec4 diffColor = cMatDiffColor;
    vec4 diffInput = texture2D(sDiffMap, vec2(2,2) * ( vTexCoord + ( cScrollingSpeed ) * vec2( cElapsedTimePS, 0 ) ) );
    gl_FragColor = diffColor * diffInput; 
}


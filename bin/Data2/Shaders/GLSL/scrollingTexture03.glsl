#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"

#include "ScreenPos.glsl"

in vec4 UOffset;
in vec4 VOffset;

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
    vec4 diffColor = cMatDiffColor;

		// ?????????????
    //#ifdef VERTEXCOLOR
        //diffColor *= vColor;
    //#endif
    // ??????????????

    //#if (!defined(DIFFMAP)) && (!defined(ALPHAMAP))
        //gl_FragColor = diffColor;
    //#endif

    //#ifdef DIFFMAP
        vec4 diffInput = texture2D(sDiffMap, vec2(1,1) * ( vTexCoord + 2.35 * vec2( cElapsedTimePS, 0 ) ) );
        //#ifdef ALPHAMASK
            //if (diffInput.a < 0.5)
                //discard;
        //#endif
        gl_FragColor = diffColor * diffInput;
    //#endif

    //#ifdef ALPHAMAP
        //#ifdef GL3
            //float alphaInput = texture2D(sDiffMap, vTexCoord).r;
        //#else
            //float alphaInput = texture2D(sDiffMap, vTexCoord).a;
        //#endif
        //gl_FragColor = vec4(diffColor.rgb, diffColor.a * alphaInput);
    //#endif
    
}

/*
#include "Uniforms.glsl"
#include "Samplers.glsl"
#include "Transform.glsl"
#include "ScreenPos.glsl"

//uniform mat4 modelMatrix;
//uniform mat4 modelViewMatrix;
//uniform mat4 projectionMatrix;
//uniform mat4 viewMatrix;
//uniform mat3 normalMatrix;

uniform vec2 uvScale;
uniform sampler2D image;
//uniform float cElapsedTimePS;
uniform vec2 speed;

in vec3 position;
in vec3 normal;
in vec2 uv;
in vec2 uv2;
in vec2 i_vUv;

out vec4 out_FragColor;
out vec2 o_vUv;

void VS() {
  o_vUv = uv * uvScale;
  gl_Position = cViewProj * cModel * vec4(position, 1.0);
}

void PS() {
	//vec2 test = vec2(0.5,0.5);
    out_FragColor = texture2D( image, i_vUv + ( speed * cElapsedTimePS ) );
	//out_FragColor = texture2D( image, i_vUv );
}
*/

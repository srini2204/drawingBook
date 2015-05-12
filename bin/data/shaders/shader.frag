#version 120
#extension GL_ARB_texture_rectangle : enable


uniform sampler2DRect tex0;
uniform sampler2DRect tex1;

void main (void){
    vec2 pos = gl_TexCoord[0].st;
                                         
    vec4 rTxt = texture2DRect(tex0, pos);
    vec4 gTxt = texture2DRect(tex1, pos);
    vec4 bTxt = texture2DRect(tex0, pos) + texture2DRect(tex1, pos);
                                         
    vec4 color = vec4(0,0,0,0);
    color = mix(color, rTxt, 255 );
    color = mix(color, gTxt, 255 );
    color = mix(color, bTxt, 255 );
                                         
    gl_FragColor = gl_Color;
}
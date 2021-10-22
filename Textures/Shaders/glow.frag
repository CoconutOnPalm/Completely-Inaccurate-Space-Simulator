#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 position; // shader position
uniform float size; // shader size
uniform vec3 color; // shader color
uniform float basic_a; // basic alfa


void main()
{
    vec2 shaderPos = gl_FragCoord.xy - position;

    float alfa = basic_a;
    vec2 dist = vec2(shaderPos.xy);

    alfa -= length(dist) / size;

    gl_FragColor = vec4(color, alfa);
}
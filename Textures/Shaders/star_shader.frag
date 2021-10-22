#ifdef GL_ES
precision highp float;
#endif


uniform vec2 position; // shader position
uniform float size; // shader size
uniform float basic_a; // basic alpha value
uniform float light_sharpness_modifier; // size of the white area in the middle of the shader
uniform vec3 basic_color; // shader color

float cbrt(float n) // cube root
{
    float x = 1.0;
    for(int i = 0; i < 10; i++)
        x = (2.0 * x + n / (x * x)) / 3.0;
    return x;
}

void main()
{
    vec2 shaderPos = gl_FragCoord.xy - position;

    vec2 dist = vec2(shaderPos.xy);
    float alfa = basic_a;

    //alfa -= indensity * sqrt(sqrt(length(dist / 2.))) / size * 1000. - step(middle_circle, indensity);

    // setting shader shape
    alfa -= cbrt((length(dist.x / size)));
    alfa -= cbrt((length(dist.y / size)));

    // computing color
    vec3 color = vec3(1.0, 1.0, 1.0);
    color.x -= length(dist / light_sharpness_modifier) * (color.x - basic_color.x);
    color.y -= length(dist / light_sharpness_modifier) * (color.y - basic_color.y);
    color.z -= length(dist / light_sharpness_modifier) * (color.z - basic_color.z);

    gl_FragColor = vec4(color, alfa);

    
}
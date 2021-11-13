#ifdef GL_ES
precision highp float;
#endif


uniform vec2 position; // shader position
uniform float size; // shader size
uniform float basic_a; // basic alpha value
uniform float light_sharpness_modifier; // size of the white area in the middle of the shader
uniform vec3 basic_color; // shader color
uniform float rotation_speed; // pulsar rotation speed
uniform float max_rotation_angle; // max rotation angle for pulsar
uniform float time;


//const vec2 position = vec2(400, 400); // shader position
//const float size = 90.; // shader size
//const float basic_a = 1.; // basic alpha value
//const float light_sharpness_modifier = 1000.; // size of the white area in the middle of the shader
//const vec3 basic_color = vec3(0.1843, 0.5804, 1.0); // shader color
//const float rotation_speed = 1.; // pulsar rotation speed
//const float max_rotation_angle = .1; // max rotation angle for pulsar


float cbrt(float n) // cube root
{
    float x = 1.0;
    for(int i = 0; i < 10; i++)
        x = (2.0 * x + n / (x * x)) / 3.0;
    return x;
}


mat2 rotate(float angle)
{
    return mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
}

void main()
{
    vec2 shaderPos = gl_FragCoord.xy - position;

    shaderPos -= vec2(0.5);
    shaderPos *= rotate(sin(time * rotation_speed) * max_rotation_angle);
    shaderPos += vec2(0.5);

    vec2 dist = vec2(shaderPos.xy);
    float alfa = basic_a;

    //alfa -= indensity * sqrt(sqrt(length(dist / 2.))) / size * 1000. - step(middle_circle, indensity);

    // setting shader shape
    alfa -= ((length(dist.x / 9.)));
    alfa -= ((length(dist.y / 90.)) / 9.) / size;

    // computing color
    vec3 color = vec3(1.0, 1.0, 1.0);
    color.x -= length(dist / light_sharpness_modifier) * (color.x - basic_color.x);
    color.y -= length(dist / light_sharpness_modifier) * (color.y - basic_color.y);
    color.z -= length(dist / light_sharpness_modifier) * (color.z - basic_color.z);

    gl_FragColor = vec4(color, alfa);
}
    
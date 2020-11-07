#shader vertex

#version 400 core

layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec2 v_UV;

uniform mat4 u_PV;
uniform mat4 u_Model_Transform;


out vec2 v_UV_FragPass;
out vec2 v_myPoint;

void main() {
    gl_Position = u_PV * u_Model_Transform * vec4(v_Position, 1.0);
    v_UV_FragPass = v_UV;
    v_myPoint = gl_Position.xy;
}


#shader fragment

#version 400 core

layout(location = 0) out vec4 v_FragColor;

in vec2 v_UV_FragPass;
in vec2 v_myPoint;

uniform sampler2D u_Textures;

void main() {
    // Vignette Effect 
    float Vignette_Effect_factor =  1 - distance(v_myPoint * 0.2f, vec2(0.0f));
    Vignette_Effect_factor = clamp(Vignette_Effect_factor, 0.0f, 1.0f);

    vec4 tex_color = texture(u_Textures, v_UV_FragPass);
    /*if (tex_color.a == 0.0f)
        discard;*/
    v_FragColor = tex_color * Vignette_Effect_factor;// vec4(tex_color.a, tex_color.g, tex_color.b, 1.0f);//*vec4(1.0f, 0.0f, 0.0f, tex_color.a);
}
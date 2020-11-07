#shader vertex

#version 400 core

layout(location = 0) in vec3 v_Position;

uniform mat4 u_PV;
uniform mat4 u_Model_Transform;

uniform vec4 u_FlatColor;

out vec4 u_FragColor;

void main() {
    gl_Position = u_PV * u_Model_Transform * vec4(v_Position, 1.0);
    u_FragColor = u_FlatColor;
}


#shader fragment

#version 400 core

layout(location = 0) out vec4 v_FragColor;

in vec4 u_FragColor;

void main() {
    v_FragColor = u_FragColor;
}
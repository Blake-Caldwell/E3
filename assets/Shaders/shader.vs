#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
  
out vec3 ourColor; // output a color to the fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0);
    float sum = aPos.x + aPos.y;
    ourColor = vec3(aPos.y / 2 + 0.5 , aPos.x /2  + 0.5 , 0.5); // set ourColor to the input color we got from the vertex data
}  
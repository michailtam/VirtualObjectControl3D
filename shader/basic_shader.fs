#version 430

// The calculation for the lightning is done in the fragment
// shader (phong shading).

// Input block from the vertex shader
in VS_OUT
{
    vec2 texcoord;        // Input texture coordinate
    vec3 normalW;         // Input normal in model space
    vec3 lightvec;        // Input light vector (normalized)
    vec3 viewvec;         // Input view vector (normalized)
    vec3 blendcolor;
} fs_in;

// Input uniform data from the CPU (application)
uniform sampler2D texturemap;   // Sampler of the 2D texture
uniform vec3 ambient;           // Ambient light color

out vec4 fs_color;   // Output color


void main()
{
    // Get the RGB color (not the alpha) of the texel (pixel of the texture)
    vec3 texcolor = vec3(texture(texturemap, fs_in.texcoord).rgb) * fs_in.blendcolor;

    // ************************* Diffuse light *****************************
    vec3 diffuse = max(dot(fs_in.lightvec, fs_in.normalW), 0.0) * texcolor;
    
    // ************************* Specular light ****************************
    vec3 phong = (ambient + diffuse) * texcolor;


    // Write final color to the framebuffer
    fs_color = vec4(phong, 1.0);
}
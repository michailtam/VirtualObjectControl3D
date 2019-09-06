#version 430

// Input data
in layout(location = 0) vec3 position;	// Vertex position in model space
in layout(location = 1) vec2 texcoord;	// Texture coordinate
in layout(location = 2) vec3 normal;	// Vertex normal in model space

// Transformation matrices
uniform mat4 MVP;				// Model-View-Projection matrix
uniform mat4 MtoW;				// Model to World matrix

uniform vec3 lightpos;			// Light position
uniform vec3 blendcolor = vec3(1.0, 1.0, 1.0);	// Default blend color

// Output block
out VS_OUT 
{
	vec2 texcoord;			// Output texture coordinate
	vec3 normalW;			// Output vertex normal in model space (normalized)
	vec3 lightvec;			// Output light vector (normalized)
	vec3 viewvec;			// Output the view vector (normalized)
	vec3 blendcolor;
} vs_out;


void main()
{
	 // Calculate the position and the normal in world space
    vec4 positionW = MtoW * vec4(position, 1.0);
	vs_out.normalW = mat3(MtoW) * normal;
	
	// Calculate the light vector
	vs_out.lightvec = normalize(lightpos - positionW.xyz);

	// Calculate the view vector in world space
	vs_out.viewvec = (-positionW.xyz);

	vs_out.texcoord = texcoord;

	vs_out.blendcolor = blendcolor;

	// Calculate the NDC position (screen space)
	gl_Position = MVP * vec4(position, 1.0);	
}
#material
	vec2 mStartSize = (1.0, 1.0);
	vec2 mEndSize = (0.5, 0.5);
	vec3 mStartColor = (1.0, 1.0, 1.0);
	vec3 mEndColor = (1.0, 1.0, 1.0);
	float mStartAlpha = 1.0;
	float mEndAlpha = 0.0;
#endmaterial

#shader vert
	layout(location = 0) in vec4 in_vert;

#ifdef JWL_PARTICLE_SIZE
	layout(location = 1) in vec2 in_size;
	out vec2 size;
#endif
#ifdef JWL_PARTICLE_COLOR
	layout(location = 2) in vec3 in_color;
	out vec3 color;
#endif
#ifdef JWL_PARTICLE_ALPHA
	layout(location = 3) in float in_alpha;
	out float alpha;
#endif
#ifdef JWL_PARTICLE_ROTATION
	layout(location = 4) in float in_rotation;
	out float rotation;
#endif
#ifdef JWL_PARTICLE_AGERATIO
	layout(location = 5) in float in_ageRatio;
	out float ageRatio;
#endif

	void main()
	{
		gl_Position = Jwl_ModelView * in_vert;

#ifdef JWL_PARTICLE_SIZE
		size = in_size;
#endif
#ifdef JWL_PARTICLE_COLOR
		color = in_color;
#endif
#ifdef JWL_PARTICLE_ALPHA
		alpha = in_alpha;
#endif
#ifdef JWL_PARTICLE_ROTATION
		rotation = in_rotation;
#endif
#ifdef JWL_PARTICLE_AGERATIO
		ageRatio = in_ageRatio;
#endif
	}
#endshader

#shader geom
	//input type
	layout(points) in;

	//output type
	layout(triangle_strip, max_vertices = 4) out;
	
#ifdef JWL_PARTICLE_SIZE
	in vec2 size[];
#endif
#ifdef JWL_PARTICLE_COLOR
	in vec3 color[];
#endif
#ifdef JWL_PARTICLE_ALPHA
	in float alpha[];
#endif
#ifdef JWL_PARTICLE_ROTATION
	in float rotation[];
#endif
#ifdef JWL_PARTICLE_AGERATIO
	in float ageRatio[];
#endif

	out vec2 texcoord;
	out vec4 frag_color;
	
	vec2 OFFSETS[4] = vec2[](
		vec2(-0.5, -0.5),
		vec2(0.5, -0.5),
		vec2(-0.5, 0.5),
		vec2(0.5, 0.5));
	
	vec2 TEXCOORDS[4] = vec2[](
		vec2(0.0, 0.0),
		vec2(1.0, 0.0),
		vec2(0.0, 1.0),
		vec2(1.0, 1.0));
	
	void main()
	{
		vec3 position = gl_in[0].gl_Position.xyz;
		vec4 outPosition = vec4(0.0, 0.0, position.z, 1.0);
		
		/* resolve particle parameters */
		vec2 Size;
#ifdef JWL_PARTICLE_SIZE
		Size = size[0];
#else
		Size = mix(mStartSize, mEndSize, ageRatio[0]);
#endif

		vec4 Color;
#ifdef JWL_PARTICLE_COLOR
		Color.rgb = color[0];
#else
		Color.rgb = mix(mStartColor, mEndColor, ageRatio[0]);
#endif

#ifdef JWL_PARTICLE_ALPHA
		Color.a = alpha[0];
#else
		Color.a = mix(mStartAlpha, mEndAlpha, ageRatio[0]);
#endif

		//create rotation matrix
#ifdef JWL_PARTICLE_ROTATION
		float cosR = cos(rotation[0]);
		float sinR = sin(rotation[0]);
		mat2 rot = mat2(cosR, -sinR, sinR, cosR);
#endif
		
		/* Emit Vertices */
		for (int i = 0; i < 4; i++)
		{
			vec2 offset = OFFSETS[i] * Size;
#ifdef JWL_PARTICLE_ROTATION
			offset = rot * offset;
#endif
			outPosition.xy = position.xy + offset;
			gl_Position = Jwl_Proj * outPosition;
			
			frag_color = Color;
			texcoord = TEXCOORDS[i];
			EmitVertex();
		}
		
		EndPrimitive();
	}
#endshader

#sampler2D sTex : 0
#shader frag
	in vec2 texcoord;
	in vec4 frag_color;

	out vec4 outColor;

	void main()
	{
		outColor = texture(sTex, texcoord).rgba;

#ifdef JWL_CUTOUT
		if (outColor.a < 1.0)
		{
			discard;
		}
#endif

		outColor.rgb *= frag_color.rgb;
		outColor *= frag_color.a;
	}
#endshader

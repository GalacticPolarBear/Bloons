#shader vert
	layout(location = 0) in vec4 in_vert;
	layout(location = 1) in vec2 in_uv;

	out vec2 texcoord;

	void main()
	{
		texcoord = in_uv;

	#ifdef JWL_SPRITE_BILLBOARD
		//get the position of the sprite
		vec4 vertex = Jwl_Model[3].xyzw;

		//calculate vertex offset from the center
		vec2 offset = texcoord;
		#ifdef JWL_SPRITE_CENTERED_X
		offset.x -= 0.5f;
		#endif
		#ifdef JWL_SPRITE_CENTERED_Y
		offset.y -= 0.5f;
		#endif

		//extract the scale from the basis vectors
		vec2 scale = vec2(length(Jwl_Model[0].xyz), length(Jwl_Model[1].xyz));

		//offset in view space to create perfect billboard
		vertex = Jwl_View * vertex;
		vertex.xy += offset * scale;

		//project to screen
		gl_Position = Jwl_Proj * vertex;
	#else
		vec4 vertex = in_vert;

		//offset in local-space
		#ifdef JWL_SPRITE_CENTERED_X
		vertex.x -= 0.5f;
		#endif
		#ifdef JWL_SPRITE_CENTERED_Y
		vertex.y -= 0.5f;
		#endif

		//transform and project to screen
		gl_Position = Jwl_MVP * vertex;
	#endif
	}
#endshader

#sampler2D sTex : 0
#shader frag
	in vec2 texcoord;

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
	}
#endshader

#material
	vec3 mColor = (1.0, 1.0, 1.0);
#endmaterial

#shader vert
	layout(location = 0) in vec4 in_vert;
	layout(location = 1) in vec2 in_uv;

	out vec2 texcoord;

	void main()
	{
		texcoord = in_uv;
		gl_Position = Jwl_MVP * in_vert;
	}
#endshader

#sampler2D sTex : 0
#shader frag
	in vec2 texcoord;

	out vec4 outColor;

	void main()
	{
		outColor = vec4(mColor, texture(sTex, texcoord).r);

#ifdef JWL_CUTOUT
		if (outColor.a < 1.0)
		{
			discard;
		}
#endif
	}
#endshader

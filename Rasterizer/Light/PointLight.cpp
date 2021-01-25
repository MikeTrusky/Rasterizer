#include "PointLight.h"

float3 PointLight::calculate(Vertex & f, VertexProcessor & vp)
{
	float3 N = vp.tr_obj2view(f.normal, 0, false);
	normalize(N);

	float3 V = vp.tr_obj2view((f.position * -1.0f), 1, false);

	float3 L = position - V;
	L = L * -1.0f;

	L = normalize(L);
	V = normalize(V);

	float3 R = reflect(L * -1.0f, N);
	normalize(R);

	float3 diffuseValue = diffuse * saturate(dot(L, N));
	float3 specularValue = specular * powf(saturate(dot(R, V)), shine);

	float3 texSample(1, 1, 1);

	if (texture != nullptr)
	{
		unsigned int c = texture->frame[int(f.texturePos.x * (texture->w - 1) + 0.5f) + int(f.texturePos.y * (texture->h - 1) + 0.5f) * texture->w];

		float red = ((c >> 16) & 0xff) / 255.0f;
		float green = ((c >> 8) & 0xff) / 255.0f;
		float blue = (c & 0xff) / 255.0f;
		texSample = float3(red, green, blue);
	}

	float3 returnValue = (texture->calcLight) ? (ambient + diffuseValue) * texSample + specularValue : texSample;

	return saturate(returnValue);
}
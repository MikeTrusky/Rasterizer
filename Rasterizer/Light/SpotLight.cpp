#include "SpotLight.h"

float3 SpotLight::calculate(Vertex & f, VertexProcessor & vp)
{
	float3 N = vp.tr_obj2view(f.normal, 0, true);
	normalize(N);

	float3 V = vp.tr_obj2view((f.position * -1.0f), 1, true);

	float3 L = position - V;
	L = L * -1.0f;

	normalize(L);
	normalize(V);

	float3 R = reflect(L * -1.0f, N);
	normalize(R);

	float3 diffuseValue = diffuse * saturate(dot(L, N));
	float3 specularValue = specular * powf(saturate(dot(R, V)), shine);

	normalize(direction);

	float3 texSample(1, 1, 1);

	if (texture != nullptr)
	{
		uint32_t c = texture->frame[int(f.texturePos.x * (texture->w - 1) + 0.5f) + int(f.texturePos.y * (texture->h - 1) + 0.5f) * texture->w];

		float red = ((c >> 16) & 0xff) / 255.0f;
		float green = ((c >> 8) & 0xff) / 255.0f;
		float blue = (c & 0xff) / 255.0f;
		texSample = float3(red, green, blue);
	}

	float spotFactor = dot(L, direction);

	float3 returnValue = 0.0f;

	if (spotFactor > Cutoff)
	{
		returnValue = (texture->calcLight) ? (ambient + diffuseValue) * texSample + specularValue : texSample;
	}
	else
	{
		returnValue = (texture->calcLight) ? float3(0.2, 0.2, 0.2) * texSample : texSample;
	}

	return returnValue;
}
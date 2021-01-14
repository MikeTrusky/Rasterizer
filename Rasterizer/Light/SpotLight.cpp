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
	
	float spotFactor = dot(L, direction);

	float3 returnValue = 0.0f;

	if (spotFactor > Cutoff)
	{
		returnValue = ambient + diffuseValue + specularValue;
	}
	else
	{
		returnValue = float3(0.2, 0.2, 0.2);
	}

	return returnValue;
}
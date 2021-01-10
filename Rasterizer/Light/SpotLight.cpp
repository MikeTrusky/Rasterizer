#include "SpotLight.h"

float3 SpotLight::calculate(Vertex & f, VertexProcessor & vp)
{
	float3 N = vp.tr_obj2view(f.normal, 0);
	normalize(N);

	float3 V = vp.tr_obj2view((f.position * -1.0f), 1);

	float3 L = position - V;
	L = L * -1.0f;

	L = normalize(L);
	V = normalize(V);

	float3 R = reflect(L * -1.0f, N);
	normalize(R);

	float theta = dot(L, direction);
	float intensity = (theta > Cutoff) ? 1 : 0;

	float3 diffuseValue = diffuse * saturate(dot(L, N));
	float3 specularValue = specular * powf(saturate(dot(R, V)), shine);

	float3 returnValue = ambient + diffuseValue;
	returnValue = returnValue + specularValue;
	returnValue = saturate(returnValue);
	returnValue = returnValue * intensity;

	return returnValue;
}
cbuffer ConstantBuffer
{
    matrix  World;
	matrix  View;
	matrix  Projection;
    float4  EyePosition;
}

cbuffer MaterialBuffer
{
    float4  MatAmbient;
    float4  MatDiffuse;
    float4  MatSpecular;
    float   MatPower;
    bool    textureOn = false;
}
Texture2D   Texture;
SamplerState Sampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = WRAP;
    AddressV = WRAP;
};


cbuffer LightBuffer
{
    int     type;
    float4  LightPos;
    float4  LightDir;
    float4  LightAmb;
    float4  LightDiff;
    float4  LightSpe;
    float   LightAtt0;
    float   LightAtt1;
    float   LightAtt2;
    float   LightAlpha;
    float   LightBeta;
    float   LightFallOff;
}

struct VS_INPUT
{
    float4  Pos : POSITION;
    float4  Norm : NORMAL;
    float4  Tan : TANGENT;
    float2  Tex : TEXCOORD;
};

struct PS_INPUT
{
    float4  Pos : SV_POSITION;
    float4  Norm : TEXCOORD0;
    float4  ViewDirection : TEXCOORD1;
    float4  LightVector : TEXCOORD2;    //�Ե��Դ�;۹����Ч��ǰ3��������¼�����������������һ��������¼���վ���
    float2  Tex : TEXCOORD3;
};

//������ɫ��
PS_INPUT VS( VS_INPUT input )
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = mul(input.Pos, World);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);
    
    output.Norm = mul(input.Norm, World);
    output.Norm = normalize(output.Norm);

    float4 worldPosition = mul(input.Pos, World);   //һ��Ҫ�ǳ������������꣡
    output.ViewDirection = EyePosition - worldPosition; //һ�еļ��㶼�������������棡
    output.ViewDirection = normalize(output.ViewDirection); //����ǧ��������ͼͶӰ֮������꣡

    output.LightVector = LightPos - worldPosition;
    output.LightVector = normalize(output.LightVector);
    output.LightVector.w = length(LightPos - worldPosition);
    
    output.Tex = input.Tex;

    return output;
}

//ƽ�й�������ɫ��
float4 PSDirectionalLight(PS_INPUT input) : SV_Target
{
    float4 textureColor;
    float4 finalColor;
	float4 ambientColor, diffuseColor, specularColor;
	
	//���շ���,�͹������䷽���෴
	float4 lightVector = -LightDir;

	ambientColor = MatAmbient * LightAmb;

	float diffuseFactor = dot(lightVector, input.Norm);
	if(diffuseFactor > 0.0f)
	{
		diffuseColor = MatDiffuse * LightDiff * diffuseFactor;

		float4 reflection = reflect(-lightVector, input.Norm);
		float specularFactor = pow(max(dot(reflection, input.ViewDirection), 0.0f), MatPower);

		specularColor = MatSpecular * LightSpe * specularFactor;
	}

	finalColor = ambientColor + diffuseColor;
    if(textureOn)
    {
        textureColor = Texture.Sample(Sampler, input.Tex);
        finalColor = finalColor * textureColor;
    }
    finalColor = saturate(finalColor + specularColor);
	return finalColor;
}

//���Դ��ɫ��
float4 PSPointLight(PS_INPUT input) : SV_Target
{
    float4 textureColor;
    float4 finalColor;
	float4 ambientColor, diffuseColor, specularColor;

	float4 lightVector = input.LightVector;

	ambientColor = MatAmbient * LightAmb;

	float diffuseFactor = dot(lightVector, input.Norm);
	if(diffuseFactor > 0.0f)
	{
		diffuseColor = MatDiffuse * LightDiff * diffuseFactor;

		float4 reflection = reflect(-lightVector, input.Norm);
		float specularFactor = pow(max(dot(reflection, input.ViewDirection), 0.0f), MatPower);

		specularColor = MatSpecular * LightSpe * specularFactor;
	}

	//����˥������
	float d = input.LightVector.w;
	float att = LightAtt0 + LightAtt1 * d + LightAtt2 * d * d;

    finalColor = ambientColor + diffuseColor;
    if(textureOn)
    {
        textureColor = Texture.Sample(Sampler, input.Tex);
        finalColor = finalColor * textureColor;
    }
    finalColor = saturate(finalColor + specularColor)/att;
	return finalColor;
}

//�۹��Դ��ɫ��
float4 PSSpotLight(PS_INPUT input) : SV_Target
{
    float4  textureColor;
    float4  finalColor = 0;
    float4  ambientColor = 0, diffuseColor = 0, specularColor = 0;

    float4  lightVector = input.LightVector;
    float3 lightDir = LightDir.xyz;
    lightDir = normalize(lightDir);

    //�жϹ�������
    float cosTheta = dot(-lightVector.xyz, lightDir);
    if(cosTheta < cos(LightBeta/2))
        return float4(0.0f, 0.0f, 0.0f, 1.0f);
    
    //������
    ambientColor = LightAmb * MatAmbient;
    
    //�������
    float diffuseFactor = dot(input.Norm, lightVector);
    if(diffuseFactor > 0)
    {
        diffuseColor = MatDiffuse * LightDiff * diffuseFactor;
    }

    //�����
    float4 reflection = reflect(-lightVector, input.Norm);
    reflection = normalize(reflection);
    float specularFactor = pow(max(dot(reflection, input.ViewDirection), 0.0f), MatPower);
    specularColor = MatSpecular * LightSpe * specularFactor;

    //����˥������
    float d = input.LightVector.w;
    float att = LightAtt0 + LightAtt1 * d + LightAtt2 * d * d;

    if(cosTheta > cos(LightAlpha/2))
    {
        finalColor = ambientColor + diffuseColor;
        if(textureOn)
        {
            textureColor = Texture.Sample(Sampler, input.Tex);
            finalColor = finalColor * textureColor;
        }
        finalColor = saturate(finalColor + specularColor);
    }
    else
    {
        float spotFactor = pow((cosTheta - cos(LightBeta / 2)) / (cos(LightAlpha / 2) - cos(LightBeta / 2)), 1);
        finalColor = ambientColor + diffuseColor;
        if(textureOn)
        {
            textureColor = Texture.Sample(Sampler, input.Tex);
            finalColor = finalColor * textureColor;
        }
        finalColor = spotFactor * saturate(finalColor + specularColor)/att;
    }
    return finalColor;
}

technique11 T_DirLight
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PSDirectionalLight() ) );
    }
}

technique11 T_PointLight
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PSPointLight() ) );
    }
}

technique11 T_SpotLight
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PSSpotLight() ) );
    }
}
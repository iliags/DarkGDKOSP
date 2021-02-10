//====================================================
// Shadow Mapping
// By EVOLVED
//====================================================

//--------------
// un-tweaks
//--------------
   matrix WorldVP:WorldViewProjection; 
   matrix World:World;    
   matrix ViewInv:ViewInverse;       
   matrix ViewMat={0.5,0,0,0.5,0,-0.5,0,0.5,0,0,0.5,0.5,0,0,0,1};
   matrix ProjMatrix;

//--------------
// Tweaks
//--------------
   float3 Ambient = {0.1f, 0.1f, 0.1f};  
   float4 LightPosition = {0.0f, 150.0f, 0.0f, 1.0f};    
   float3 LightColor = {1.0f, 1.0f, 1.0f};
   float LightRange = 500.0f;    
   float3x3 LightAngle;   
   float Alpha = 1.0f;
 
//--------------
// Textures
//--------------
   texture BaseTX
      <
	string Name="";
      >;	
   sampler2D Base = sampler_state 
      {
     	texture = <BaseTX>;
      };
   texture NormalTX
      <
	string Name="";
      >;	
   sampler2D Normal = sampler_state 
      {
 	texture = <NormalTX>;
      };
   texture CubeLightTX 
      <
	string Name = "";
      >;
   sampler CubeLight = sampler_state
      {
	Texture = <CubeLightTX>;
      };
   texture DepthMapTX 
      <
	string Name="";
      >;	
   sampler2D DepthMap=sampler_state
      {
	Texture = <DepthMapTX>;	
      };

//--------------
// structs 
//--------------
   struct IN_Depth
     {
 	float4 Pos:POSITION; 
     };
   struct OUT_Depth
     {
 	float4 OPos:POSITION; 
 	float  Depth:TEXCOORD1; 
     };
   struct IN_NormalMap
     {
 	float4 Pos:POSITION; 
 	float2 UV:TEXCOORD; 
	float3 Normal:NORMAL;
 	float3 Tangent:TANGENT;
 	float3 Binormal:BINORMAL;
     };
   struct OUT_NormalMap
     {
	float4 OPos:POSITION; 
 	float2 Tex:TEXCOORD0; 
  	float3 LightVec:TEXCOORD1; 
	float3 Attenuation:TEXCOORD2;
	float3 ViewVec:TEXCOORD3; 
	float3 CubeLight:TEXCOORD4; 
 	float4 Proj:TEXCOORD5;
     };

//--------------
// vertex shaders
//--------------
   OUT_Depth VS_Depth(IN_Depth IN)
     {
       OUT_Depth OUT;
       OUT.OPos = mul(IN.Pos,WorldVP); 
       float4 WPosP = mul(IN.Pos,World); 
       float4 Proj = mul(WPosP,ProjMatrix); 
       OUT.Depth = Proj.z; 
       return OUT;
     }
   OUT_NormalMap VS_NormalMap(IN_NormalMap IN) 
     {
 	OUT_NormalMap OUT;
	OUT.OPos=mul(IN.Pos,WorldVP);
    	OUT.Tex=IN.UV;
	float3x3 TBN={IN.Tangent,IN.Binormal,IN.Normal};
	TBN=transpose(mul(TBN,World));
	float3 WPos=mul(IN.Pos,World);  
	float3 LightPos=LightPosition-WPos; 
	float3 ViewPos=ViewInv[3].xyz-WPos;
	OUT.LightVec=mul(LightPos,TBN);
	OUT.Attenuation=-(LightPos/LightRange); 
 	OUT.ViewVec=mul(ViewPos,TBN);
	OUT.CubeLight=mul(LightAngle,-LightPos); 
     	float4 Wpos = mul(IN.Pos,World); 
       	float4 Proj = mul(Wpos,ProjMatrix);
       	OUT.Proj = mul(ViewMat,Proj);	
	return OUT;
     }

//--------------
// pixel shaders
//--------------
   float4 PS_Depth(OUT_Depth IN) : COLOR
     {
        return IN.Depth/800;
     }
   float4 PS_NormalMap(OUT_NormalMap IN)  : COLOR
     {
	float3 Texture=tex2D(Base,IN.Tex); 
	float3 NormalMap=tex2D(Normal,IN.Tex)*2-1; 
	NormalMap=normalize(NormalMap);
	float3 LightV=normalize(IN.LightVec);  	
	float3 ViewV=normalize(IN.ViewVec);  	
	float Normal=saturate(dot(reflect(-ViewV,NormalMap),LightV));
	Normal=pow(Normal,16)+saturate(dot(NormalMap,LightV)); 
	float PixelLight=1-saturate(dot(IN.Attenuation,IN.Attenuation));
	float depth=(IN.Proj.z/800)-0.01f;
     	float ShadowTex=1-(tex2Dproj(DepthMap,IN.Proj+float4(-0.8,-0.8,0,0)) < depth ? 0.05f : 0.0f);
        ShadowTex=ShadowTex-(tex2Dproj(DepthMap,IN.Proj+float4(0,-0.8,0,0)) < depth ? 0.15f : 0.0f);
        ShadowTex=ShadowTex-(tex2Dproj(DepthMap,IN.Proj+float4(0.8,-0.8,0,0)) < depth ? 0.05f : 0.0f);
        ShadowTex=ShadowTex-(tex2Dproj(DepthMap,IN.Proj+float4(-0.8,0,0,0)) < depth ? 0.15f : 0.0f);
        ShadowTex=ShadowTex-(tex2Dproj(DepthMap,IN.Proj+float4(0,0,0,0)) < depth ? 0.2f : 0.0f);
        ShadowTex=ShadowTex-(tex2Dproj(DepthMap,IN.Proj+float4(0.8,0,0,0)) < depth ? 0.15f : 0.0f);
        ShadowTex=ShadowTex-(tex2Dproj(DepthMap,IN.Proj+float4(-0.8,0.8,0,0)) < depth ? 0.05f : 0.0f);
        ShadowTex=ShadowTex-(tex2Dproj(DepthMap,IN.Proj+float4(0,0.8,0,0)) < depth ? 0.15f : 0.0f);
        ShadowTex=ShadowTex-(tex2Dproj(DepthMap,IN.Proj+float4(0.8,0.8,0,0)) < depth ? 0.05f : 0.0f);
	float3 Light=LightColor*PixelLight*ShadowTex*texCUBE(CubeLight,IN.CubeLight);
	return float4(Texture*((Normal*Light)+Ambient),Alpha);
     }

//--------------
// techniques   
//--------------
    technique DepthMap
      {
 	pass p1
      {		
 	VertexShader = compile vs_2_0 VS_Depth(); 
 	PixelShader  = compile ps_2_0 PS_Depth(); 		
      }
      }
   technique ShadowMapping
      {
 	pass p1
      {		
 	vertexShader = compile vs_2_0 VS_NormalMap(); 
 	pixelShader  = compile ps_2_0 PS_NormalMap(); 
      }
      }
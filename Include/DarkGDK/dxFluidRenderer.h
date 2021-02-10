#ifndef DXFLUIDRENDERER_H
#define DXFLUIDRENDERER_H

#include <d3d9.h>
#include <d3dx9.h>

#define NUM_BLURRED_DEPTH_TEXTURES 2
#define M_PI 3.141592653589793

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) { if (p) { (p)->Release(); (p)=NULL; } }
#endif

#ifndef V
#define V(x) { hr = (x); if( FAILED(hr) ) {  } }
#endif

class DxFluidRenderer
{
	// Surface state

    // Particle properties
	int mMaxParticles;
	int mNumParticles;

    float mParticleRadius;              // particle radius in world space
    float mParticleSurfaceScale;        // amount to scale up particles to form surface
    float mDensityThreshold;            // threshold below which particles are scaled down

    D3DXVECTOR4 mFluidColor;            // fluid base color (alpha component is transparency)
    D3DXVECTOR4 mFluidColorFalloff;     // amount color (and transparency) falls off with thickness
    float       mColorFalloffScale;     // scales color falloff
    D3DXVECTOR4 mSpecularColor;         // color of specular highlight
    D3DXVECTOR4 mFresnelColor;          // color of Fresnel edge effect
    float mShininess;                   // shininess - higher values produce tighter specular highlights
    D3DXVECTOR4 mLightDirection;        // light direction in eye space

    // Camera and window dependent properties
	float mWindowW;
	float mWindowH;
	float mAspect;
    float mFovRadians;
    float mInvFocalLen;

	// Direct3d state
    // textures and surfaces
    LPDIRECT3DTEXTURE9			 m_pThicknessRenderTexture;
    LPDIRECT3DSURFACE9           m_pThicknessRenderSurface;
    LPDIRECT3DTEXTURE9			 m_pDepthRenderTexture;
    LPDIRECT3DSURFACE9           m_pDepthRenderSurface;
    LPDIRECT3DTEXTURE9			 m_pBlurredDepthRenderTexture[NUM_BLURRED_DEPTH_TEXTURES];
    LPDIRECT3DSURFACE9           m_pBlurredDepthRenderSurface[NUM_BLURRED_DEPTH_TEXTURES];
    LPDIRECT3DSURFACE9           m_pSceneBackBuffer;
    LPDIRECT3DSURFACE9           m_pSceneDepthStencilSurface;
    LPDIRECT3DSURFACE9           m_pCustomDepthStencilSurface;

	// vertex buffers
	LPDIRECT3DVERTEXBUFFER9      m_pVB;
	LPDIRECT3DVERTEXBUFFER9      m_texCoordBuffer;
	LPDIRECT3DVERTEXBUFFER9      m_pQuadVB;
	
	// shaders
	LPDIRECT3DVERTEXSHADER9      m_particleVS;
	LPDIRECT3DVERTEXSHADER9      m_passThruVS;
	LPDIRECT3DPIXELSHADER9       m_particleThicknessPS;
	LPDIRECT3DPIXELSHADER9       m_particleSpherePS;
	LPDIRECT3DPIXELSHADER9       m_particleSurfacePS;
	LPDIRECT3DPIXELSHADER9       m_depthBlurPS;
	LPDIRECT3DPIXELSHADER9       m_displaySurfacePS;
	LPDIRECT3DPIXELSHADER9       m_clearSurfacePS;

	// shader constant tables
	LPD3DXCONSTANTTABLE          m_particleVSconstantTable;
	LPD3DXCONSTANTTABLE          m_particleThicknessPSconstantTable;
	LPD3DXCONSTANTTABLE          m_particleSurfacePSconstantTable;
	LPD3DXCONSTANTTABLE          m_particleSpherePSconstantTable;
	LPD3DXCONSTANTTABLE          m_depthBlurPSconstantTable;
	LPD3DXCONSTANTTABLE          m_displaySurfacePSconstantTable;

	// vertex declarations
	LPDIRECT3DVERTEXDECLARATION9 m_pVertexDeclaration;

	// vertex format
	struct PosAndTex
	{
		D3DXVECTOR4 pos;
		float texu;
		float texv;

		PosAndTex(D3DXVECTOR4 pos,float texu,float texv) : pos(pos),texu(texu),texv(texv) {};
	};

	enum BlendMode
	{
		BLEND_NONE,
		BLEND_ALPHA,
		BLEND_ADD,
	};

    void drawPointSprites(IDirect3DDevice9 *  pd3dDevice,IDirect3DVertexShader9 *  vertexShader,IDirect3DPixelShader9 *  pixelShader,BlendMode  blendMode,int  numParticles);
    void blurDepth(IDirect3DDevice9* pd3dDevice,IDirect3DSurface9 * destSurface,IDirect3DTexture9 * srcTexture,bool vertical);
    void renderSurface(IDirect3DDevice9* pd3dDevice,D3DXMATRIX& view,D3DXMATRIX& proj, float fovRadians);

public:
	// constructor

	DxFluidRenderer() :
		m_pVB(NULL),
		m_texCoordBuffer(NULL),
		m_pQuadVB(NULL),
		m_particleVS(NULL),
		m_passThruVS(NULL),
		m_particleThicknessPS(NULL),
		m_particleSpherePS(NULL),
		m_particleSurfacePS(NULL),
		m_depthBlurPS(NULL),
		m_displaySurfacePS(NULL),
		m_clearSurfacePS(NULL),
		m_particleVSconstantTable(NULL),
		m_particleThicknessPSconstantTable(NULL),
		m_particleSurfacePSconstantTable(NULL),
		m_particleSpherePSconstantTable(NULL),
		m_depthBlurPSconstantTable(NULL),
		m_displaySurfacePSconstantTable(NULL),
		m_pVertexDeclaration(NULL),
		m_pThicknessRenderTexture(NULL),
		m_pThicknessRenderSurface(NULL),
		m_pDepthRenderTexture(NULL),
		m_pDepthRenderSurface(NULL),
		m_pSceneBackBuffer(NULL),
		m_pSceneDepthStencilSurface(NULL),
		m_pCustomDepthStencilSurface(NULL)		
	{
		mMaxParticles = 100000;
        mNumParticles = 8*8*8;
        mParticleRadius = 0.06f;
        mParticleSurfaceScale = 1.5f;
        mDensityThreshold = 300.0f;
        mFluidColor =        D3DXVECTOR4(0.5f, 0.7f, 1.0f, 1.0f);
        mFluidColorFalloff = D3DXVECTOR4(2.0f, 1.0f, 0.5f, 2.0f);
        mColorFalloffScale = 0.5f;
        mSpecularColor =     D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
        mShininess = 40.0f;
        mFresnelColor =      D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
        mLightDirection =    D3DXVECTOR4(0.577f, 0.577f, -0.577f, 0.0f);

		mWindowW = 640;
		mWindowH = 480;
        mAspect = (float) mWindowW / (float) mWindowH;

        mFovRadians = (float)M_PI/4.0f;
        mInvFocalLen = tan(mFovRadians*0.5f);

        for(int i=0;i!=NUM_BLURRED_DEPTH_TEXTURES;i++)
		{
			m_pBlurredDepthRenderTexture[i] = NULL;
			m_pBlurredDepthRenderSurface[i] = NULL;
		}
	}

	void onCreateDevice(IDirect3DDevice9* pd3dDevice);
	void onResetDevice(IDirect3DDevice9* pd3dDevice);
    void onLostDevice();
    void onDestroyDevice();

	void render(IDirect3DDevice9* pd3dDevice,D3DXMATRIX& view,D3DXMATRIX& proj, float fovRadians)
	{
		renderSurface(pd3dDevice, view, proj, fovRadians);
	}

	IDirect3DVertexBuffer9 * getVertexBuffer()
	{
		return m_pVB;
	}

	IDirect3DVertexBuffer9 * getDensityBuffer()
	{
		return m_texCoordBuffer;
	}

	void setParticleCount(int particleCount)
	{
		mNumParticles=particleCount;
	}

    void setParticleRadius(float particleRadius)
    {
        mParticleRadius = particleRadius;
    }

	//
	// Additional Members for 'The Game Creators' PhysX Screen Saver
	//
	void SetParticleRadius ( float fValue ) { mParticleRadius = fValue; }
	void SetParticleSurfaceScale ( float fValue ) { mParticleSurfaceScale = fValue; }
	void SetDensityThreshold ( float fValue ) { mDensityThreshold = fValue; }
	void SetFluidColor ( D3DXVECTOR4 mColor ) { mFluidColor = mColor; }
	void SetFluidColorFalloff ( D3DXVECTOR4 mColor ) { mFluidColorFalloff = mColor; }
	void SetColorFalloffScale ( float fValue ) { mColorFalloffScale = fValue; }
	void SetSpecularColor ( D3DXVECTOR4 mColor ) { mSpecularColor = mColor; }
	void SetShininess ( float fValue ) { mShininess = fValue; }
	void SetFresnelColor ( D3DXVECTOR4 mColor ) { mFresnelColor = mColor; }
};

#endif
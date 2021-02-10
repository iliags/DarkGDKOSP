
//
// CObjectManager Functions Header
//

#ifndef _COBJECTMANAGER_H_
#define _COBJECTMANAGER_H_

//////////////////////////////////////////////////////////////////////////////////
// INCLUDE OBJECT DATA ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#include "cObjectDataC.h"
#include <vector>

//////////////////////////////////////////////////////////////////////////////////
// INLINE MACROS /////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
inline DWORD F2DW( FLOAT f ) { return *((DWORD*)&f); }

// 301008 - Saver - Externals
extern int g_iShadowClipping;
extern float g_fShadowClippingMin;
extern float g_fShadowClippingMax;

//////////////////////////////////////////////////////////////////////////////////
// RENDER STRUCTURES /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
#define MAXTEXTURECOUNT 8
struct sRenderStates
{
	// render filter states
	DWORD			dwAddressU [ MAXTEXTURECOUNT ];
	DWORD			dwAddressV [ MAXTEXTURECOUNT ];
	DWORD			dwMagState [ MAXTEXTURECOUNT ];
	DWORD			dwMinState [ MAXTEXTURECOUNT ];
	DWORD			dwMipState [ MAXTEXTURECOUNT ];

	// render state flags
	bool			bWireframe;
	bool			bLight;
	bool			bCull;
	int				iCullMode;
	bool			bFog;
	int				iAmbient;
	bool			bTransparency;
	DWORD			dwAlphaTestValue;
	bool			bGhost;
	bool			bZRead;
	bool			bZWrite;
	int				iGhostMode;
	bool			bZBiasActive;
	float			fZBiasSlopeScale;
	float			fZBiasDepth;

	// render state data fog when ghosts override fog
	bool			bFogOverride;
	DWORD			dwFogColor;

	// render state data
	DWORD			dwAmbientColor;
	DWORD			dwCullDirection;
	DWORD			dwGlobalCullDirection;
	D3DMATERIAL9	gWhiteDefaultMaterial;
	bool			bIgnoreDiffuse;

	// restriction states (set when global render states use, ie instance alpha factor)
	bool			bNoMeshAlphaFactor;

	// camera specific states
	float			fStoreCameraFOV;
	float			fObjectFOV;
};

struct sStencilStates
{
	DWORD			dwShadowColor;
	DWORD			dwShadowShades;
	DWORD			dwShadowStrength;
	DWORD			dwReflectionColor;
};

//////////////////////////////////////////////////////////////////////////////////
// CLASS DEFINITION //////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

class CObjectManager
{
	public:
		struct sVertexData
		{
			// vertex data structure

			DWORD							dwFormat;				// data format e.g. xyz
			LPDIRECT3DVERTEXDECLARATION9	pVertexDec;				// custom FVF dec
			DWORD							dwPosition;
			DWORD							dwMaxVertexCount;		// maximum number of vertices allowed
			DWORD							dwCurrentVertexCount;	// current number of vertices

			LPDIRECT3DVERTEXBUFFER9			pVB;					// vertex buffer
			sVertexData*					pNext;					// pointer to next node

			bool							bBufferLocked;			// during fast-update
			BYTE*							pfLockedData;			// can lock once - write many times

			// constructor

			sVertexData ( );
			~sVertexData ( );

			/*
			// mike - 281106 - move these into cpp file for debugging
			sVertexData ( )
			{
				memset ( this, 0, sizeof(sVertexData) );
			}

			~sVertexData ( )
			{
				SAFE_RELEASE ( pVB );
				SAFE_DELETE  ( pNext );
			}
			*/
		};

		struct sIndexData
		{
			// index data structure

			DWORD					dwMaxIndexCount;		// maximum number of indices allowed
			DWORD					dwCurrentIndexCount;	// current index count
			LPDIRECT3DINDEXBUFFER9	pIB;					// index buffer
			sIndexData*				pNext;					// pointer to next node

			// constructor

			sIndexData ( );
			~sIndexData ( );

			/*
			// mike - 281106 - move these into cpp file for debugging
			sIndexData ( )
			{
				memset ( this, 0, sizeof(sIndexData) );
			}

			~sIndexData ( )
			{
				SAFE_RELEASE ( pIB );
				SAFE_DELETE  ( pNext );
			}
			*/
		};

		IDirect3DVertexBuffer9*		m_ppCurrentVBRef;				// current VBs being used
		IDirect3DVertexBuffer9*		m_ppLastVBRef;					// last VBs being used
		IDirect3DIndexBuffer9*		m_ppCurrentIBRef;				// current IBs being used
		IDirect3DIndexBuffer9*		m_ppLastIBRef;					// last IBs being used

		DWORD						m_dwCurrentShader;				// current shader value
		DWORD						m_dwCurrentFVF;					// current FVF value
		DWORD						m_dwLastShader;					// last shader value
		DWORD						m_dwLastFVF;					// last FVF value

		int							m_iCurrentTexture;				// current texture being used
		int							m_iLastTexture;					// last texture
		DWORD						m_dwLastTextureCount;			// to free old stages
		bool						m_bUpdateTextureList;			// flag to update sorted texture list
		bool						m_bUpdateVertexDecs;			// ensure we can restore at start of new object render cycle
		bool						m_bUpdateStreams;
		int							m_iSortedObjectCount;
		int							m_iLastCount;
		int							m_iListCount;					// number of objects in list
		int							m_iVisibleObjectCount;
		bool*						m_pbMarkedList;
		sObject**					m_ppSortedObjectList;	        // a list of objects sorted by texture
		sObject**					m_ppSortedObjectVisibleList;	// a list of objects that are visible in the scene
		sVertexData*				m_pVertexDataList;				// vertex buffer cache
		sIndexData*					m_pIndexDataList;				// index buffer cache

        std::vector< sObject* >     m_vVisibleObjectList;
        std::vector< sObject* >     m_vVisibleObjectEarly;
        std::vector< sObject* >     m_vVisibleObjectTransparent;
        std::vector< sObject* >     m_vVisibleObjectNoZDepth;
        std::vector< sObject* >     m_vVisibleObjectStandard;

		sRenderStates				m_RenderStates;					// global render state settings
		sStencilStates				m_StencilStates;				// global stencil state settings

		IDirect3DVertexBuffer9*		m_pSquareVB;					// for shadow filling

		sMesh*						m_pQUAD;						// for post processing
		cSpecialEffect*				m_pQUADDefaultEffect;			// current QUAD shader

		bool						m_bGlobalShadows;				// flag to control whether shadows are handled or not

		bool						g_bObjectReplacedUpdateBuffers;	// flag to say buffers need replacing
		
        tagCameraData*              m_pCamera;                      // Current camera details - updated in UpdateLayer

		sVertexData*	FindVertexBuffer		( DWORD dwFVF, LPDIRECT3DVERTEXDECLARATION9 pVertexDec, DWORD dwSize, DWORD dwVertexCount, DWORD dwIndexCount, bool bUsesItsOwnBuffers, int iType );
		sIndexData*		FindIndexBuffer			( DWORD dwIndexCount, bool bUsesItsOwnBuffers );
		bool			SortTextureList			( void );
		bool			SortVisibilityList		( void );
		bool			PreSceneSettings		( void );
		bool			PreDrawSettings			( void );
		bool			SetMeshMaterial			( sMesh* pMesh, D3DMATERIAL9* pMaterial );
		bool			SetMeshRenderStates		( sMesh* pMesh );
		bool			SetMeshTextureStates	( sMesh* pMesh );
		bool			DrawMesh				( sMesh* pMesh );
		bool			DrawObject				( sObject* pObject );
		bool			PostDrawRestores		( void );
		bool			Reset					( void );
		bool			SetVertexShader			( sMesh* pMesh );
		bool			SetInputStreams			( sMesh* pMesh );

	public:

		CObjectManager ( )
		{
			// use setup to set members - global manager not refreshed when display mode switched
			Setup ();
		}

		~CObjectManager ( )
		{
			// use free to  clean up - global manager not refreshed when display mode switched
			Free ();
		}

		bool Setup							( void );
		bool Free							( void );
		void UpdateInitOnce					( void );
		bool UpdateInit						( void );
		bool UpdateLayer					( int iLayer );				// update the core
		bool Update							( void );					// update
		bool UpdateGhostLayer				( void );
		bool UpdateNoZLayer					( void );					// update

		float CalculateObjectDistanceFromCamera ( sObject* pObject );
		bool AddObjectMeshToBuffers			( sMesh* pMesh, bool bUsesItsOwnBuffers );			// add an object mesh to the buffers
		bool AddObjectToBuffers				( sObject* pObject );		// adds an object to the buffers
		bool FlagAllObjectMeshesUsingBuffer	( sVertexData* pVertexData, sIndexData* pIndexData );
		bool RemoveBuffersUsedByObjectMeshDirectly	( sMesh* pMesh );
		// mike - 301106 - add flag to stop recursion
		bool RemoveBuffersUsedByObjectMesh	( sMesh* pMesh, bool bRecurse = true );
		bool AddFlaggedObjectsBackToBuffers	( void );
		bool ReplaceAllFlaggedObjectsInBuffers ( void );
		bool RemoveBuffersUsedByObject		( sObject* pObject );		// remove buffers used by object
		bool RemoveObjectFromBuffers		( sObject* pObject );		// removes an object from buffers
		bool UpdateObjectMeshInBuffer		( sMesh* pMesh );
		bool UpdateAllObjectsInBuffers		( void );
		bool CompleteUpdateInBuffers		( void );
		bool QuicklyUpdateObjectMeshInBuffer ( sMesh* pMesh, DWORD dwVertexFrom, DWORD dwVertexTo );
		bool RenewReplacedMeshes			( sObject* pObject );
		bool RefreshObjectInBuffer			( sObject* pObject );
		void RemoveTextureRefFromAllObjects ( LPDIRECT3DTEXTURE9 pTextureRef );

		bool UpdateObjectListSize			( int iSize );				// updates object list size
		bool UpdateTextures					( void );
		bool UpdateAnimationCycle			( void );
		bool UpdateOnlyVisible				( void );

		void SetGlobalShadowsOn				( void );
		void SetGlobalShadowsOff			( void );
		void DeleteStencilEffect			( sObject* pObject );
		void DoPrepareFillRender			( DWORD dwFillColor );
		void DoStencilRenderStart			( void );
		void DoStencilRenderEnd				( void );
		void StartStencilMeshWrite			( void );
		void DrawFrameOrMesh				( int iFrameCount, sFrame** ppFrameList, sMesh* pOrShadowMesh );
		void DrawStencilMesh				( int iFrameCount, sFrame** ppFrameList, sMesh* pOrShadowMesh );
		void FinishStencilMeshWrite			( void );

		void CreateScreenQUAD				( int iInitialCameraZeroImage );
		void SetScreenTextureQUAD			( int iStageIndex, int iImageID );
		void SetScreenEffectQUAD			( int iEffect );
		void RenderScreenQUAD				( void );

		int GetVisibleObjectCount				( void );
		sObject** GetSortedObjectVisibleList	( void );
};

#endif _COBJECTMANAGER_H_

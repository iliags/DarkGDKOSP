#ifndef _CSPRITEMANAGER_H_
#define _CSPRITEMANAGER_H_

#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "ddraw.lib" )
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib" )
#pragma comment ( lib, "dxerr9.lib" )

#include <ddraw.h>
#include <d3d9.h>
#include <Dxerr9.h>
#include <D3dx9tex.h>
#include <D3dx9core.h>
#include <basetsd.h>
#include <stdio.h>
#include <math.h>
#include <D3DX9.h>
#include <d3d9types.h>

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>   
#include <windowsx.h>

#include "cspritedatac.h"
#include ".\..\data\cdatac.h"
#include <vector>

class CSpriteManager
{
	private:
		CData	m_List;
		
	public:
		CSpriteManager	( void );
		~CSpriteManager	( void );

		bool  Add	        ( tagSpriteData* pData, int iID );
		bool  Delete        ( int iID );
		int   Count         ( void )                { return m_List.Count();  }

		void  DrawImmediate ( tagSpriteData* pData );

        tagSpriteData* GetData ( int iID )          { return ( tagSpriteData* ) m_List.Get ( iID ); }
		CData* GetList      ( void )                { return &m_List; }

		int   Update        ( void );

		void  DeleteAll     ( void );
		void  HideAll       ( void );
		void  ShowAll       ( void );

    private:
        static void DeleteJustOne  ( tagSpriteData* ptr );
        static void RenderDrawList ( tagSpriteData** pList, int iListSize );
        static void GetDisplaySize ();
        static bool IsSpriteInDisplay( tagSpriteData* m_ptr );

        struct PrioritiseSprite;
        typedef std::vector<PrioritiseSprite> t_SpriteList;
        typedef t_SpriteList::iterator        t_SpriteListPtr;

        static t_SpriteList m_SortedSpriteList;
        static std::vector<tagSpriteData*> m_SpriteDrawList;
        static D3DXVECTOR3  vecDisplayMin;
        static D3DXVECTOR3  vecDisplayMax;
};

#endif _CSPRITEMANAGER_H_

//=======================================
//NAVIGATION MESHES HEADER
//Marabillas 2010
//=======================================

#include "hPathfinder.h"


void CPathAgent::setStartingPoint( float x, float y, float z )
{
	m_spos[0]=x;
	m_spos[1]=y;
	m_spos[2]=z;
	m_cpos[0]=x;
	m_cpos[1]=y;
	m_cpos[2]=z;
	m_checkpoint=0;
	m_sposSet = true;
	_computePath();
}
void CPathAgent::setDestination( float x, float y, float z )
{
	m_epos[0]=x;
	m_epos[1]=y;
	m_epos[2]=z;
	m_spos[0]=m_cpos[0];
	m_spos[1]=m_cpos[1];
	m_spos[2]=m_cpos[2];
	m_checkpoint=0;
	m_eposSet = true;
	_computePath();
}

void CPathAgent::_computePath()
{
	if(m_sposSet && m_eposSet && m_NavMesh)
		m_NavMesh->ComputePath(m_spos,m_epos,m_straightPath,&m_nstraightPath);
}

void CPathAgent::moveForward( float displacement )
{
	if (m_checkpoint>m_nstraightPath-1)
	{
		//checkpoint=0;
		return;
	}
	float x = m_straightPath[m_checkpoint*3]-m_cpos[0];
	float y = m_straightPath[m_checkpoint*3+1]-m_cpos[1];
	float z = m_straightPath[m_checkpoint*3+2]-m_cpos[2];
	if (x*x<=0.2&&y*y<=0.2&&z*z<=0.2)
		m_checkpoint++;
	float mag=sqrt(x*x+y*y+z*z);
	x=displacement*x/mag;
	y=displacement*y/mag;
	z=displacement*z/mag;
	m_cpos[0]+=x;
	m_cpos[1]+=y;
	m_cpos[2]+=z;
}
//=======================================
//NAVIGATION MESHES HEADER
//Marabillas 2010
//Added S3GE in Rev 182
//=======================================

#include "hNavMesh.h"

class CPathAgent
{
private:
	float		m_straightPath[MAX_POLYS*3];
	int			m_nstraightPath;

	float		m_spos[3];
	float		m_epos[3];
	bool		m_sposSet;
	bool		m_eposSet;
	float		m_cpos[3];

	int			m_checkpoint;
	hNavMesh*	m_NavMesh;

	void		_computePath();
public:
	CPathAgent(hNavMesh* CurrentLevel=0){
		m_NavMesh=CurrentLevel;
		m_sposSet=false;
		m_eposSet=false;}
	~CPathAgent(){};

	void setNavigationMesh( hNavMesh* CurrentLevel ){m_NavMesh=CurrentLevel;}
	void setDestination( float x, float y, float z );
	void setStartingPoint( float x, float y, float z );
	void moveForward( float displacement );
	float* getStraightPathPointer(){return m_straightPath;}
	float getPositionX(){return m_cpos[0];}
	float getPositionY(){return m_cpos[1];}
	float getPositionZ(){return m_cpos[2];}
	float getDestinationX(){return m_epos[0];}
	float getDestinationY(){return m_epos[1];}
	float getDestinationZ(){return m_epos[2];}
	float getStartingPointX(){return m_spos[0];}
	float getStartingPointY(){return m_spos[1];}
	float getStartingPointZ(){return m_spos[2];}
	int	getCheckpointCount(){return m_nstraightPath;}
	int getCheckpointCurrent(){return m_checkpoint;}
	void setCheckpointCurrent( int pCheckpoint ){m_checkpoint = pCheckpoint;}
};
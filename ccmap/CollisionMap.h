//////////////////////////////////////////////////////////////////////
// CollisionMap.h: interface for the CCollisionMap class.
//
// Abin (abinn32@yahoo.com)
//////////////////////////////////////////////////////////////////////

#ifndef __COLLISIONMAP_H__
#define __COLLISIONMAP_H__

#define MAP_DATA_INVALID	-1    // Invalid
#define MAP_DATA_CLEANED	11110 // Cleaned for start/end positions
#define MAP_DATA_FILLED		11111 // Filled gaps
#define MAP_DATA_THICKENED	11113 // Wall thickened
#define MAP_DATA_AVOID		11115 // Should be avoided

typedef CArrayEx<DWORD, DWORD> DwordArray;
typedef CArrayEx<WORD, WORD> WordArray;
typedef CMatrix<WORD, WORD> WordMatrix;

typedef struct LevelExit_t
{
	POINT ptPos;
	DWORD dwTargetLevel;
} LevelExit, *LPLevelExit;

////////////////////////////////////////////////////////////////
// The CCollisionMap class. Synchronized access required.
////////////////////////////////////////////////////////////////
class CCollisionMap
{
public:		
		
	////////////////////////////////////////////////////////////
	// Constructor & Destructor
	////////////////////////////////////////////////////////////
	CCollisionMap();
	virtual ~CCollisionMap();

	////////////////////////////////////////////////////////////
	// Operations
	////////////////////////////////////////////////////////////
	BOOL CreateMap(Act* lpAct,DWORD AreaId); // Create the map data
	void DestroyMap();
	BOOL DumpMap(LPCSTR lpszFilePath, const LPPOINT lpPath, DWORD dwCount) const; // Dump map data into a disk file
	void Search(Room2 *ro, UnitAny* ptPlayer, DwordArray &aSkip);

	////////////////////////////////////////////////////////////
	// Attributes & Operations
	////////////////////////////////////////////////////////////
	POINT GetMapOrigin() const; // Map origin point(top-left)
	SIZE GetMapSize() const; // map size
	WORD GetMapData(long x, long y, BOOL bAbs) const; // Retrieve map data at a particular location
	BOOL IsValidAbsLocation(long x, long y) const; // Map location verification
	SIZE CopyMapData(WORD** ppBuffer, int cx, int cy) const;
	BOOL CopyMapData(WordMatrix& rBuffer) const;
	BOOL ReportCollisionType(POINT ptOrigin, long lRadius) const;
	INT CCollisionMap::GetLevelExits(LPLevelExit* lpLevel);
	BOOL Export(char* map); 
	////////////////////////////////////////////////////////////
	// Convertions
	////////////////////////////////////////////////////////////
	void AbsToRelative(POINT& pt) const; // Convert an absolute map location into a graph index
	void RelativeToAbs(POINT& pt) const; // Convert a graph index into an absolute map location
	static void MakeBlank(WordMatrix& rMatrix, POINT pos);
	static BOOL ThickenWalls(WordMatrix& rMatrix, int nThickenBy = 1);
	BOOL IsGap(int x, int y);
	BOOL CheckCollision(INT x, INT y);

	////////////////////////////////////////////////////////////
	// Only Used by D2Hackit! Do NOT Call It!!!
	////////////////////////////////////////////////////////////
	void OnMapChanged(BYTE iNewMapID); // Called by D2Hackit when map changes. Do not call this function manually!
	
private:	
	
	////////////////////////////////////////////////////////////
	// Private Methods
	////////////////////////////////////////////////////////////
	BOOL BuildMapData(DWORD AreaId);
	void AddCollisionData(const CollMap* pCol);	
	char CCollisionMap::IsMarkPoint(INT asd, int x, int y, const LPPOINT lpPath, DWORD dwCount) const;

	void FillGaps();

	////////////////////////////////////////////////////////////
	// Member Data
	////////////////////////////////////////////////////////////
	
	BYTE m_iCurMap; // Current map ID
	POINT m_ptLevelOrigin; // level top-left
	WordArray m_aCollisionTypes;
	WordMatrix m_map; // The map
	DWORD dwLevelId;
	Act* pAct;
};

#endif // __COLLISIONMAP_H__

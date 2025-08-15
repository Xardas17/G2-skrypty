#ifdef MEMPOOL_HOELLER

#include "zCore.h"
#include "zpolypool.h"

static zCMeshesPool MeshesPool;


zCMeshesPool& GetMeshesPool()
{
	return MeshesPool;
}

#endif
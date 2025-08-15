
#ifndef __ZLOCAL_H__
#define __ZLOCAL_H__

//#define DEBUG_EDENFELD
//#define CHASE_DEBUG

#ifdef CHASE_DEBUG

extern void zLocal_Startup();
extern void zLocal_Shutdown();
extern void zLocal_PerFrame();

#else

void zLocal_Startup();	
void zLocal_Shutdown();
void zLocal_PerFrame();

#endif


#endif // __ZLOCAL_H__


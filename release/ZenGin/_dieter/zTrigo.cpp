
#include <zTrigo.h>
#include <math.h>

/*
- Kommentare:
	- Winkel werden intern im Bereich 0..TRG_MAXANGLE repraesentiert,
	  z.B. 0..2048, wobei "0==2048" ist. Im allgemeinen sollte dies 
	  kein Problem sein. Werden allerdings dem User Angaben ueber 
	  Winkelgroessen gemacht, ist hier vielleicht der Bereich 0..360
	  angebrachter. Hierfuer kann vor der Ausgabe der entsprechende
	  Wert mit einer Funktion konvertiert werden.
	  In Anwendungen sollte man sich allerdings moeglichst *NIE* auf
	  den konkreten Bereich 0..2048 beziehen. Dieser koennte sich
	  aendern !
	- Ausgaben der Sin/Cos Funktionen werden via dirketem Array-Zugriff
	  sowohl als "zREAL" (Floating-Point) als auch "zFIX" (Fixpoint)
	  zur Verfuegung gestellt. Natuerlich *ohne* Range-Check.
*/

// disable VC++ Warning: double to float conversion
#pragma warning( disable : 4244 ) 

zREAL	trg_sin		[TRG_MAXANGLE];
zREAL	trg_cos		[TRG_MAXANGLE];

zFIX	trg_sinFix	[TRG_MAXANGLE];
zFIX	trg_cosFix	[TRG_MAXANGLE];

void Trg_Init (void)
 {
	return;
	int i;
	for (i=0; i<TRG_MAXANGLE; i++) {
		trg_sin   [i] = (zREAL) sin ((double)i / (double)TRG_MAXANGLE * M_2PI);
		trg_cos   [i] = (zREAL) cos ((double)i / (double)TRG_MAXANGLE * M_2PI);
		trg_sinFix[i] = (zFIX) (sin ((double)i / (double)TRG_MAXANGLE * M_2PI) * 65536);
		trg_cosFix[i] = (zFIX) (cos ((double)i / (double)TRG_MAXANGLE * M_2PI) * 65536);
	}
}

// enable VC++ Warning: double to float conversion
#pragma warning( default: 4244 ) 

/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150      42 ms		12 ms 0,08
    200	    139 ms		37 ms 0,185
    300      217 ms		53 ms 0,176
    400      543 ms		134 ms 0,335
    800      4407 ms		325 ms 0,40625
   1600	    31693 ms		1130 ms 0,70625
   3200     229376 ms		4696 ms 1,4675
   6400     1 835 008 ms	20110 ms  3,142
  12800    14 680 064 ms	81815 ms  6,391


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: O(N^4) (i bästa fallet O(N^3)) eftersom om alla punkter är kollinjära, då kommer den fjärde (innersta) loopen köras varje möjlig iteration. (N-3)*(N-3)*(N-3)*(N-3) i första iteration på alla loopar. 

Sortering: O(2N^2) (i bästa fallet O(N^2)) I både värsta och bästa fallet kommer de två första for looparna iterera över alla (N-1), den sista i värsta fall kommer ha N olika lines att iterera över (N-1)*((N-1) + N) eller i bästa fall 1 ((N-1)*((N-1) + 1). 

// Test program for the SolveBoard function.
// Uses the hands pre-set in hands.cpp.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dll.h"
#include "hands.h"


int main()
{
  deal		dl;
  futureTricks  fut2, // solutions == 2
  		fut3; // solutions == 3

  int 		target, 
  		solutions, 
		mode, 
		threadIndex = 0,
		res;
  char		line[80];
  bool		match2,
  		match3;

#if defined(__linux) || defined(__APPLE__)
  SetMaxThreads(0);
#endif

  for (int handno = 0; handno < 3; handno++)
  {
    dl.trump = trump[handno];
    dl.first = first[handno];

    dl.currentTrickSuit[0] = 0;
    dl.currentTrickSuit[1] = 0;
    dl.currentTrickSuit[2] = 0;

    dl.currentTrickRank[0] = 0;
    dl.currentTrickRank[1] = 0;
    dl.currentTrickRank[2] = 0;

    for (int h = 0; h < DDS_HANDS; h++)
      for (int s = 0; s < DDS_SUITS; s++)
        dl.remainCards[h][s] = holdings[handno][s][h];

    target    = -1;
    solutions = 3;
    mode      = 0;
    res = SolveBoard(dl, target, solutions, mode, &fut3, 0);

    if (res != RETURN_NO_FAULT)
    {
      ErrorMessage(res, line);
      printf("DDS error: %s\n", line);
    }

    match3 = CompareFut(&fut3, handno, solutions);

    solutions = 2;
    res = SolveBoard(dl, target, solutions, mode, &fut2, 0);
    if (res != RETURN_NO_FAULT)
    {
      ErrorMessage(res, line);
      printf("DDS error: %s\n", line);
    }

    match2 = CompareFut(&fut2, handno, solutions);

    sprintf(line, 
      "SolveBoard, hand %d: solutions 3 %s, solutions 2 %s\n",
      handno+1, 
      (match3 ? "OK" : "ERROR"),
      (match2 ? "OK" : "ERROR"));

    PrintHand(line, dl.remainCards);

    sprintf(line, "solutions == 3\n");
    PrintFut(line, &fut3);
    sprintf(line, "solutions == 2\n");
    PrintFut(line, &fut2);
  }
}
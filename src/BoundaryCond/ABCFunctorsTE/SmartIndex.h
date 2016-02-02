/*
 * SmartIndex.h
 *
 *  Created on: 01 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef SMARTINDEX_H_
#define SMARTINDEX_H_


#define EyLeft(M, Q, N) EyLeft[(N) * 6 + (Q) * 3 + (M)]
#define EyRight(M, Q, N) EyRight[(N) * 6 + (Q) * 3 + (M)]
#define ExTop(N, Q, M) ExTop[(M) * 6 + (Q) * 3 + (N)]
#define ExBottom(N, Q, M) ExBottom[(M) * 6 + (Q) * 3 + (N)]

#define Ex(M, N) Ex[(M) * (sizeY) + (N)]
#define Ey(M, N) Ey[(M) * (sizeY-1) + (N)]
#define Hz(M, N) Hz[(M) * (sizeY-1) + (N)]


#endif /* SMARTINDEX_H_ */

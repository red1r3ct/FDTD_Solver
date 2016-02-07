/*
 * SmartIndex.h
 *
 *  Created on: 06 февр. 2016 г.
 *      Author: aleksandr
 */

#ifndef SMARTINDEX_H_
#define SMARTINDEX_H_

#define Hx(M, N, P) Hx[( (M) * (sizeY-1) + N ) * (sizeZ-1) + (P)]
#define Hy(M, N, P) Hy[( (M) * (sizeY) + N ) * (sizeZ-1) + (P)]
#define Hz(M, N, P) Hz[( (M) * (sizeY-1) + N ) * (sizeZ) + (P)]

#define Ex(M, N, P) Ex[( (M) * (sizeY) + N ) * (sizeZ) + (P)]
#define Ey(M, N, P) Ey[( (M) * (sizeY-1) + N ) * (sizeZ) + (P)]
#define Ez(M, N, P) Ez[( (M) * (sizeY) + N ) * (sizeZ-1) + (P)]

#define epsilon(M, N, P) epsilon[( (M) * (sizeY) + N ) * (sizeZ) + (P)]



#endif /* SMARTINDEX_H_ */

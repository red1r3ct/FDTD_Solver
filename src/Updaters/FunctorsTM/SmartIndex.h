/*
 * SmartIndex.h
 *
 *  Created on: 11 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef SMARTINDEX_H_
#define SMARTINDEX_H_

#define Hx(M, N) Hx[(M) * (sizeY-1) + (N)]
#define Hy(M, N) Hy[(M) * (sizeY) + (N)]
#define Ez(M, N) Ez[(M) * (sizeY) + (N)]
#define epsilon(M, N) epsilon[(M) * (sizeY) + (N)]
#define sigma(M, N) sigma[(M) * (sizeY) + (N)]
#define excluded(M, N) excluded[(M) * (sizeY) + (N)]


#endif /* SMARTINDEX_H_ */

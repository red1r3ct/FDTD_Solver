/*
 * SmartIndex.h
 *
 *  Created on: 23 янв. 2016 г.
 *      Author: aleksandr
 */

#ifndef SMARTINDEX_H_
#define SMARTINDEX_H_

#define EzLeft(M, Q, N) EzLeft[(N) * 6 + (Q) * 3 + (M)]
#define EzRight(M, Q, N) EzRight[(N) * 6 + (Q) * 3 + (M)]
#define EzTop(N, Q, M) EzTop[(M) * 6 + (Q) * 3 + (N)]
#define EzBottom(N, Q, M) EzBottom[(M) * 6 + (Q) * 3 + (N)]
#define Hx(M, N) Hx[(M) * (sizeY-1) + (N)]
#define Hy(M, N) Hy[(M) * (sizeY) + (N)]
#define Ez(M, N) Ez[(M) * (sizeY) + (N)]
#define epsilon(M, N) epsilon[(M) * (sizeY) + (N)]

#endif /* SMARTINDEX_H_ */

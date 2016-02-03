SimulationType: TE
GridTE: {sizeX} {sizeY}
Epsilon: {fileName}
BoundaryCond: ABC
BoundaryCond: TFSF {firstX} {lastX} {firstY} {lastY} {SourceType} {Parametres}
Output: Hz {fileName} {firstX} {lastX} {stepX} {firstY} {lastY} {stepY} {startTime} {endTime} {period}
Source: Harmonic {amp} {lambda} {posX} {posY}
Run: {num}

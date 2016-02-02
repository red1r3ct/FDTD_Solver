SimulationType: TM
GridTM: {sizeX} {sizeY}
Epsilon: {fileName}
BoundaryCond: ABC
BoundaryCond: TFSF {firstX} {lastX} {firstY} {lastY}
Output: Ez {fileName} {firstX} {lastX} {stepX} {firstY} {lastY} {stepY} {startTime} {endTime} {period}
Source: Harmonic {amp} {lambda} {posX} {posY}
Run: {num}

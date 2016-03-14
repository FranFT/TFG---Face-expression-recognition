cd C:\Users\Fran\documents\visual studio 2013\Projects\TFG - Face recognition
CALL opencv_traincascade.exe -data data\clasificador_centerlight -vec vec_files\centerlight.vec -bg samples\background_samples\centerlight.txt -numPos 11 -numNeg 120 -numStages 2 -w 48 -h 48 -featureType LBP
CALL opencv_traincascade.exe -data data\clasificador_glasses -vec vec_files\glasses.vec -bg samples\background_samples\glasses.txt -numPos 11 -numNeg 120 -numStages 2 -w 48 -h 48 -featureType LBP
CALL opencv_traincascade.exe -data data\clasificador_happy -vec vec_files\happy.vec -bg samples\background_samples\happy.txt -numPos 11 -numNeg 120 -numStages 2 -w 48 -h 48 -featureType LBP
CALL opencv_traincascade.exe -data data\clasificador_leftlight -vec vec_files\leftlight.vec -bg samples\background_samples\leftlight.txt -numPos 11 -numNeg 120 -numStages 2 -w 48 -h 48 -featureType LBP
CALL opencv_traincascade.exe -data data\clasificador_noglasses -vec vec_files\noglasses.vec -bg samples\background_samples\noglasses.txt -numPos 11 -numNeg 120 -numStages 2 -w 48 -h 48 -featureType LBP
CALL opencv_traincascade.exe -data data\clasificador_normal -vec vec_files\normal.vec -bg samples\background_samples\normal.txt -numPos 11 -numNeg 120 -numStages 2 -w 48 -h 48 -featureType LBP
CALL opencv_traincascade.exe -data data\clasificador_rightlight -vec vec_files\rightlight.vec -bg samples\background_samples\rightlight.txt -numPos 11 -numNeg 120 -numStages 2 -w 48 -h 48 -featureType LBP
CALL opencv_traincascade.exe -data data\clasificador_sad -vec vec_files\sad.vec -bg samples\background_samples\sad.txt -numPos 11 -numNeg 120 -numStages 2 -w 48 -h 48 -featureType LBP
CALL opencv_traincascade.exe -data data\clasificador_sleepy -vec vec_files\sleepy.vec -bg samples\background_samples\sleepy.txt -numPos 11 -numNeg 120 -numStages 2 -w 48 -h 48 -featureType LBP
CALL opencv_traincascade.exe -data data\clasificador_surprised -vec vec_files\surprised.vec -bg samples\background_samples\surprised.txt -numPos 11 -numNeg 120 -numStages 2 -w 48 -h 48 -featureType LBP
CALL opencv_traincascade.exe -data data\clasificador_wink -vec vec_files\wink.vec -bg samples\background_samples\wink.txt -numPos 11 -numNeg 120 -numStages 2 -w 48 -h 48 -featureType LBP

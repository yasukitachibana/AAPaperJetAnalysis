set (SOURCES 
Particle.cc
JetAnalysis.cc
SetXML.cc
SetFile.cc
Histogram.cc
AnalyzeEvents.cc
CombineEvents.cc
LoadFileBase.cc
LoadJetScapeAscii.cc
SubtractionBase.cc
SubNegatives.cc
AnalyzeBase.cc
JetShape.cc
JetSpec.cc
FfPt.cc
FfZ.cc
CombineBase.cc
CombineJetShape.cc
CombineFfPt.cc
CombineFfZ.cc
)

add_library(main_lib ${SOURCES})

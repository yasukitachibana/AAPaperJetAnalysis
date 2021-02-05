set (SOURCES 
Particle.cc
JetAnalysis.cc
SetXML.cc
SetFile.cc
AnalyzeEvents.cc
CombineEvents.cc
AnalyzeBase.cc
JetShape.cc
Histogram.cc
LoadFileBase.cc
LoadJetScapeAscii.cc
SubtractionBase.cc
SubNegatives.cc
CombineBase.cc
CombineJetShape.cc
)

add_library(main_lib ${SOURCES})

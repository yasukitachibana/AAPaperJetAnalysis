set (SOURCES 
Particle.cc
JetAnalysis.cc
SetXML.cc
SetFile.cc
Histogram.cc
Hist1D.cc
Hist2D.cc
AnalyzeEvents.cc
CombineEvents.cc
LoadFileBase.cc
LoadJetScapeAscii.cc
SubtractionBase.cc
SubNegatives.cc
AnalyzeBase.cc
JetShape.cc
JetShapeSub.cc
JetSpec.cc
HadSpec.cc
FfPt.cc
FfZ.cc
CombineBase.cc
CombineJetShape.cc
CombineJetShapeSub.cc
CombineHadSpec.cc
CombineJetSpec.cc
CombineFfPt.cc
CombineFfZ.cc
)

add_library(main_lib ${SOURCES})

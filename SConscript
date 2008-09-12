# -*- python -*-
# $Header$
# Authors: Heather Kelly <heather@milkyway.gsfc.nasa.gov>
# Version: reconRootData-09-19-00

Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('reconRootDataLib', depsOnly = 1)
reconRootDataRootcint = libEnv.Rootcint('reconRootData/reconRootData_rootcint', ['reconRootData/AdfRecon.h',
                                         'reconRootData/AcdRecon.h',
                                         'reconRootData/CalParams.h',
                                         'reconRootData/CalClusterLayerData.h',
                                         'reconRootData/CalCluster.h',
                                         'reconRootData/CalCorToolResult.h',
                                         'reconRootData/CalEventEnergy.h',
                                         'reconRootData/CalRecon.h',
                                         'reconRootData/CalRangeRecData.h',
                                         'reconRootData/CalXtalRecData.h',
                                         'reconRootData/ReconEvent.h',
                                         'reconRootData/AcdTkrIntersection.h',
                                         'reconRootData/AcdTkrPoca.h',
                                         'reconRootData/AcdHit.h',
                                         'reconRootData/AcdPocaData.h',
                                         'reconRootData/AcdTkrLocalCoords.h',
                                         'reconRootData/AcdTkrPoint.h',
                                         'reconRootData/AcdTkrHitPoca.h',
                                         'reconRootData/AcdTkrGapPoca.h',
                                         'reconRootData/AcdSplashVars.h',
                                         'reconRootData/TkrCluster.h',
                                         'reconRootData/TkrTrack.h',
                                         'reconRootData/TkrTrackHit.h',
                                         'reconRootData/TkrTrackParams.h',
                                         'reconRootData/TkrRecon.h',
                                         'reconRootData/TkrVertex.h',
                                         'reconRootData/TkrTruncationData.h',
                                         'reconRootData/TkrDiagnostics.h',
                                         'reconRootData/TaggerCluster.h',
                                         'reconRootData/AdfRecon.h',
                                         'reconRootData/GcrXtal.h',
                                         'reconRootData/GcrTrack.h',
					 'reconRootData/LinkDef.h'], 
					  includes = [''])

reconRootData = libEnv.SharedLibrary('reconRootData', listFiles(['src/*.cxx']) + ['reconRootData/reconRootData_rootcint.cxx'])
progEnv.Tool('reconRootDataLib')

test_reconRootData = progEnv.Program('test_reconRootData', ['src/test/testReconClasses.cxx'])
progEnv.Tool('registerObjects', package = 'reconRootData', libraries = [reconRootData], 
	testApps = [test_reconRootData], includes = listFiles(['reconRootData/*.h']))
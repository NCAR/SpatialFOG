#
# Rules to build libspatialfogcore.a and export it as a SCons tool
#
tools = ['doxygen', 'logx']
thisDir = Dir('.').abspath

env = Environment(tools=['default'] + tools)
env.AppendUnique(CXXFLAGS = ['-std=c++11'])

sources = Split('''
    AckPacket.cpp
    AnppPacket.cpp
    AnppPacketFactory.cpp
    DetailedSatellitesPacket.cpp
    DeviceInformationPacket.cpp
    EulerPacket.cpp
    EulerStdDevPacket.cpp
    ExternalHeadingPacket.cpp
    GenericPacket.cpp
    NEDVelocityPacket.cpp
    RawSensorsPacket.cpp
    RequestPacket.cpp
    SatellitesPacket.cpp
    SpatialFOGCore.cpp
    SystemStatePacket.cpp
    UnixTimePacket.cpp
    VelocityStdDevPacket.cpp
''')

headers = Split('''
    AckPacket.h
    AnppPacket.h
    AnppPacketFactory.h
    DetailedSatellitesPacket.h
    DeviceInformationPacket.h
    EulerPacket.h
    EulerStdDevPacket.h
    ExternalHeadingPacket.h
    GenericPacket.h
    NEDVelocityPacket.h
    RawSensorsPacket.h
    RequestPacket.h
    SatellitesPacket.h
    SpatialFOGCore.h
    SystemStatePacket.h
    UnixTimePacket.h
    VelocityStdDevPacket.h
''')

lib = env.Library('spatialfogcore', sources)
Default(lib)

# env['DOXYFILE_DICT'].update({ "PROJECT_NAME" : "SpatialFOGCore library" })
# doxref = env.Apidocs(sources + headers)
# Default(doxref)

progEnv = env.Clone()
progEnv.Append(LIBS=[lib])
progEnv.Require('qt4')  # we need some Qt classes for AnppFileDump
progEnv.EnableQt4Modules(['QtCore'])
AnppFileDump = progEnv.Program('AnppFileDump', ['AnppFileDump.cpp'])
Default(AnppFileDump)

def spatialfogcore(env):
    env.AppendUnique(CPPPATH = thisDir)
    env.Append(LIBS=[lib])
#     env.AppendDoxref(doxref[0])
    env.Require(tools)

Export('spatialfogcore')

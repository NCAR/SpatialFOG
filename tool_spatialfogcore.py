#
# Rules to build libspatialfogcore.a and export it as a SCons tool
#
tools = ['doxygen', 'logx']
thisDir = Dir('.').abspath

env = Environment(tools=['default'] + tools)
env.AppendUnique(CXXFLAGS = ['-std=c++11'])

sources = Split('''
    AckPacket.cpp
    ANPPPacket.cpp
    ANPPPacketFactory.cpp
    EulerPacket.cpp
    EulerStdDevPacket.cpp
    GenericPacket.cpp
    NEDVelocityPacket.cpp
    RequestPacket.cpp
    SatellitesPacket.cpp
    SpatialFOGCore.cpp
    SystemStatePacket.cpp
    UnixTimePacket.cpp
    VelocityStdDevPacket.cpp
''')

headers = Split('''
    AckPacket.h
    ANPPPacket.h
    ANPPPacketFactory.h
    EulerPacket.h
    EulerStdDevPacket.h
    GenericPacket.h
    NEDVelocityPacket.h
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

# progEnv = env.Clone()
# progEnv.Append(LIBS=[lib])
# progEnv.Require(tools)
# fooProg = progEnv.Program('foo', ['foo.cpp'])
# Default(fooProg)

def spatialfogcore(env):
    env.AppendUnique(CPPPATH = thisDir)
    env.Append(LIBS=[lib])
#     env.AppendDoxref(doxref[0])
    env.Require(tools)

Export('spatialfogcore')

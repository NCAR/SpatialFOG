#
# Rules to build libspatialfogcore.a and export it as a SCons tool
#
tools = ['doxygen', 'logx', 'boost_serialization']
thisDir = Dir('.').abspath

env = Environment(tools=['default'] + tools)
env.AppendUnique(CXXFLAGS = ['-std=c++11'])

sources = Split('''
    AckPacket.cpp
    ANPPPacket.cpp
    ANPPPacketFactory.cpp
    RequestPacket.cpp
    SpatialFOGCore.cpp
''')

headers = Split('''
    AckPacket.h
    ANPPPacket.h
    ANPPPacketFactory.h
    RequestPacket.h
    SpatialFOGCore.h
''')

lib = env.Library('spatialfogcore', sources)
Default(lib)

progEnv = env.Clone()
progEnv.Append(LIBS=[lib])
progEnv.Require(tools)
fooProg = progEnv.Program('foo', ['foo.cpp'])
Default(fooProg)

env['DOXYFILE_DICT'].update({ "PROJECT_NAME" : "SpatialFOGCore library" })
doxref = env.Apidocs(sources + headers)
Default(doxref)

def spatialfogcore(env):
    env.AppendUnique(CPPPATH = thisDir)
    env.Append(LIBS=[lib])
    env.AppendDoxref(doxref[0])
    env.Require(tools)

Export('spatialfogcore')

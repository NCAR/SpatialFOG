#
# Rules to build libspatialfogcore.a and export it as a SCons tool
#
tools = ['doxygen', 'logx']
thisDir = Dir('.').abspath

env = Environment(tools=['default'] + tools)
env.AppendUnique(CPPFLAGS = ['-std=c++11'])

sources = Split('''
    SpatialFOGCore.cpp
''')

headers = Split('''
    ArchiveANPP.h
    SpatialFOGCore.h
''')

lib = env.Library('spatialfogcore', sources)
Default(lib)

progEnv = env.Clone()
progEnv.Append(LIBS=[lib])
progEnv.Require(tools)

env['DOXYFILE_DICT'].update({ "PROJECT_NAME" : "SpatialFOGCore library" })
doxref = env.Apidocs(sources + headers)

def spatialfogcore(env):
    env.AppendUnique(CPPPATH = thisDir)
    env.Append(LIBS=[lib])
    env.AppendDoxref(doxref[0])
    env.Require(tools)

Export('spatialfogcore')

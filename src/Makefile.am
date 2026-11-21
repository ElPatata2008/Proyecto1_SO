lib_LTLIBRARIES = libepipeline_engine.la
libepipeline_engine_la_SOURCES = Consumer.cpp pipeline_api.cpp PipelineEngine.cpp Producer.cpp SharedBuffer.cpp
libepipeline_engine_la_CPPFLAGS = -I$(top_srcdir)/include
libepipeline_engine_la_CXXFLAGS = -fPIC <OpenMP> <pthread> <warnings>
libepipeline_engine_la_LDFLAGS = <OpenMP> <pthread>
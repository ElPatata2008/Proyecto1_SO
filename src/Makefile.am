bin_PROGRAMS = pipeline_engine
pipeline_engine_SOURCES = main.cpp
pipeline_engine_CPPFLAGS = -I$(top_srcdir)/include
pipeline_engine_CXXFLAGS = -Wall -Wextra -fsanitize=thread
pipeline_engine_LDFLAGS = -fsanitize=thread
pipeline_engine_LDADD = libpipeline_engine.la
lib_LTLIBRARIES = libpipeline_engine.la
libpipeline_engine_la_SOURCES = Consumer.cpp pipeline_api.cpp PipelineEngine.cpp Producer.cpp SharedBuffer.cpp
libpipeline_engine_la_CPPFLAGS = -I$(top_srcdir)/include
libpipeline_engine_la_CXXFLAGS = -fPIC $(OPENMP_CXXFLAGS) $(PTHREAD_CFLAGS) -Wall -Wextra -fsanitize=thread
SUFFIXES: .cu
.cu.o:
	$(NVCC) -ccbin $(NVCC_CCBIN) -arch=$(NVCC_ARCH) -std=c++20 \
	-Xcompiler -fPIC -I$(top_srcdir)/include -c $< -o $@
libpipeline_engine_la_LIBADD = alpha_kernels.o -L$(CUDA_LIBDIR) -lcudart
libpipeline_engine_la_LDFLAGS = $(OPENMP_CXXFLAGS) $(PTHREAD_CFLAGS) -Wl,-rpath,$(CUDA_LIBDIR) -fsanitize=thread
EXTRA_DIST = alpha_kernels.cu
CLEANFILES = alpha_kernels.o
all-local: libpipeline_engine.la
	mkdir -p $(top_srcdir)/lib
	cp -P .libs/libpipeline_engine.so* $(top_builddir)/lib/

clean-local:
	rm -f $(top_builddir)/lib/libpipeline_engine.so*
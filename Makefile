CXX 		= g++
CXXFLAGS 	= `pkg-config --cflags opencv`
LIBS 		= `pkg-config --libs opencv`

# Individual Compile Tests
Demo: Demo.cpp
	$(CXX) $(CFLAGS) package_bgs/PBAS/PixelBasedAdaptiveSegmenter.h \
	package_bgs/PBAS/PixelBasedAdaptiveSegmenter.cpp 				\
	package_bgs/PBAS/PBAS.h 										\
	package_bgs/PBAS/PBAS.cpp										\
	package_tracking/cvblob/cvaux.cpp								\
	package_tracking/cvblob/cvblob.cpp								\
	package_tracking/cvblob/cvblob.h								\
	package_tracking/cvblob/cvcolor.cpp								\
	package_tracking/cvblob/cvcontour.cpp							\
	package_tracking/cvblob/cvlabel.cpp								\
	package_tracking/cvblob/cvtrack.cpp								\
	package_tracking/BlobTracking.h	 								\
	package_tracking/BlobTracking.cpp 								\
	package_analysis/VehicleCouting.h 								\
	package_analysis/VehicleCouting.cpp 							\
	Demo.cpp -o Demo $(CXXFLAGS) $(LIBS)

clean:
	rm Demo

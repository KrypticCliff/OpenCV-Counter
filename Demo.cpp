#include <iostream>
#include <opencv2/opencv.hpp>

#include "package_bgs/PBAS/PixelBasedAdaptiveSegmenter.h"
#include "package_tracking/BlobTracking.h"
#include "package_analysis/VehicleCouting.h"

int main(int argc, char **argv)
{
  std::cout << "Using OpenCV " << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << "." << CV_SUBMINOR_VERSION << std::endl;

  /* Open video file */
  CvCapture *capture = 0;
  capture = cvCaptureFromAVI("dataset/secCam.avi");
  if(!capture){
    std::cerr << "Cannot open video!" << std::endl;
    return 1;
  }

  /* Background Subtraction Algorithm */
  IBGS *bgs;
  bgs = new PixelBasedAdaptiveSegmenter;

  /* Blob Tracking Algorithm */
  cv::Mat img_blob;
  BlobTracking* blobTracking;
  blobTracking = new BlobTracking;

  /* Vehicle Counting Algorithm */
  VehicleCouting* vehicleCouting;
  vehicleCouting = new VehicleCouting;

  std::cout << "Press 'q' to quit..." << std::endl;
  int key = 0;
  IplImage *frame;
  while(key != 'q')
  {
    frame = cvQueryFrame(capture);
    if(!frame) break;

    cv::Mat img_input = cv::cvarrToMat(frame);

    cv::resize(img_input, img_input, cv::Size(320, 176), 0, 0, cv::INTER_CUBIC);
    cv::imshow("Input", img_input);



    // Grab size of frame
    // std::cout << "Width: "  << img_input.size().width  << std::endl;
    // std::cout << "Height: " << img_input.size().height << std::endl;

    // bgs->process(...) internally process and show the foreground mask image
    cv::Mat img_mask;
    bgs->process(img_input, img_mask);

    if(!img_mask.empty())
    {
      // Perform blob tracking
      blobTracking->process(img_input, img_mask, img_blob);

      // Perform vehicle counting
      vehicleCouting->setInput(img_blob);
      vehicleCouting->setTracks(blobTracking->getTracks());
      vehicleCouting->process();
    }

    key = cvWaitKey(1);
  }

  delete vehicleCouting;
  delete blobTracking;
  delete bgs;

  cvDestroyAllWindows();
  cvReleaseCapture(&capture);

  return 0;
}

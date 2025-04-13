#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <vector>

int privacyMode = 0; // 0 = No Filter, 1 = Blur, 2 = Pixelation, 3 = Black Box, 4 = Yellow Box

// Callback function for trackbar
void onTrackbar(int value, void*) {
    privacyMode = value; // Update privacy mode based on trackbar position
}

// Function to apply pixelation (Mosaic Effect)
void applyPixelation(cv::Mat& faceROI, int pixelSize = 10) {
    if (faceROI.empty() || pixelSize <= 1) return;
    cv::Mat temp;
    cv::resize(faceROI, temp, cv::Size(faceROI.cols / pixelSize, faceROI.rows / pixelSize), 0, 0, cv::INTER_LINEAR);
    cv::resize(temp, faceROI, faceROI.size(), 0, 0, cv::INTER_NEAREST);
}

int main() {
    std::string faceCascadePath = "haarcascade_frontalface_default.xml";

    // Load Haar Cascade
    cv::CascadeClassifier faceCascade;
    if (!faceCascade.load(faceCascadePath)) {
        std::cerr << "Error loading face cascade file: " << faceCascadePath << std::endl;
        return -1;
    }

    // Open webcam
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error opening video stream!" << std::endl;
        return -1;
    }

    // Create a control window and trackbar with range 0-4
    cv::namedWindow("Controls", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("Mode", "Controls", nullptr, 4, onTrackbar);

    cv::Mat frame, gray;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;
        
        // Flip the camera feed horizontally (mirror effect)
        cv::flip(frame, frame, 1);

        // Convert frame to grayscale for face detection
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Detect faces
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(gray, faces, 1.1, 3, 0, cv::Size(30, 30));

        // Apply selected privacy filter to each detected face
        for (const auto &face : faces) {
            cv::Mat faceROI = frame(face);

            if (privacyMode == 2) {
                // Gaussian Blur
                cv::GaussianBlur(faceROI, faceROI, cv::Size(55, 55), 0);
            } else if (privacyMode == 3) {
                // Pixelation (Mosaic Effect)
                applyPixelation(faceROI, 10);
            } else if (privacyMode == 4) {
                // Black Box Censoring
                cv::rectangle(frame, face, cv::Scalar(0, 0, 0), cv::FILLED);
            } else if (privacyMode == 1) {
                // Yellow Box Outline (BGR: 0, 255, 255) with thickness 2 pixels
                cv::rectangle(frame, face, cv::Scalar(0, 255, 255), 2);
            }
        }

        // Display the resulting frame
        cv::imshow("Face Privacy Filter", frame);

        // Exit on 'q' key press
        char key = cv::waitKey(30);
        if (key == 'q') break;
    }

    // Cleanup
    cap.release();
    cv::destroyAllWindows();
    return 0;
}

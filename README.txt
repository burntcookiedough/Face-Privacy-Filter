# Face Privacy Filter Project Explanation

## Key Code Features:

**Webcam Input & Display:**
- Opens the default webcam using OpenCV (`cv::VideoCapture`).
- Shows the processed video feed in a window (`cv::imshow`).

**Face Detection:**
- Loads a pre-trained Haar Cascade model (`haarcascade_frontalface_default.xml`).
- Detects faces in each frame using `faceCascade.detectMultiScale`.

**Privacy Filters:**
- Applies different effects to detected faces based on `privacyMode`.
- Includes Gaussian Blur, Pixelation, Black Box, and Yellow Outline.

**User Control:**
- Creates a separate window with a trackbar (`cv::createTrackbar`).
- Allows the user to switch between filter modes (0-4) interactively. 
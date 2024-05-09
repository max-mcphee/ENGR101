#include "images.h"
#include <cmath>
#include <iostream>
using namespace std;

void foward(int dist) {
  set_motors(dist, dist);
  update_sim(200);
}
void backwards(int dist) {
  set_motors(dist, dist);
  update_sim(200);
}
void left(int angle) { set_motors(angle, 5); }
void right(int angle) { set_motors(5, angle); }

bool startCompleation() {
  int whiteness[camera_image.width - 1];
  for (int row = 0; row <= camera_image.height - 1; row++) {
    for (int col = 0; col <= camera_image.width - 1; col++) {
      Pixel pix = get_camera_pixel(row, col);
      if (((int)pix.b < (int)pix.r / 2) && ((int)pix.g < (int)pix.r / 2)) {
        return true;
      }
    }
  }
  return false;
}

bool startChallenge() {
  int whiteness[camera_image.width - 1];
  for (int row = 0; row <= camera_image.height - 1; row++) {
    for (int col = 0; col <= camera_image.width - 1; col++) {
      Pixel pix = get_camera_pixel(row, col);
      if (((int)pix.r < (int)pix.b / 2) && ((int)pix.g < (int)pix.b / 2)) {
        return true;
      }
    }
  }
  return false;
}
bool finish() {
  int whiteness[camera_image.width - 1];
  for (int row = 0; row <= camera_image.height - 1; row++) {
    for (int col = 0; col <= camera_image.width - 1; col++) {
      Pixel pix = get_camera_pixel(row, col);
      if (((int)pix.b < (int)pix.g / 2) && ((int)pix.r < (int)pix.g / 2)) {
        return true;
      }
    }
  }
  return false;
}
bool hasPath() {
  int row = camera_image.height / 2;
  int whiteness[camera_image.width - 1];
  for (int col = 0; col <= camera_image.width - 1; col++) {
    Pixel pix = get_camera_pixel(row, col);
    if (((int)pix.r + (int)pix.g + (int)pix.b) / 3 < 30) {
      return true;
    } else if (((int)pix.b < (int)pix.r / 2) && ((int)pix.g < (int)pix.r / 2)) {
      return true;
    } else if (((int)pix.r < (int)pix.b / 2) && ((int)pix.g < (int)pix.b / 2)) {
      return true;
    }
  }
  return false;
}
int positionError() {
  int row = camera_image.height / 2;
  int whiteness[camera_image.width - 1];
  for (int col = 0; col <= camera_image.width - 1; col++) {
    Pixel pix = get_camera_pixel(row, col);
    if (((int)pix.r + (int)pix.g + (int)pix.b) / 3 < 30) {
      whiteness[col] = 1;
    } else {
      whiteness[col] = 0;
    }
  }
  int mid = (sizeof(whiteness) / sizeof(whiteness[0])) / 2;
  int middle[camera_image.width - 1];
  int p = 0 - mid;
  for (int i = 0; i <= camera_image.width - 1; i++) {
    middle[i] = p;
    p++;
  }
  int sum = 0;
  for (int i = 0; i < camera_image.width - 1; i++) {
    sum += whiteness[i] * middle[i];
  }
  return sum;
}

int checkIntersection(int arr[], int size) {
  int middle = size / 2;
  int mid[size];
  for (int i = 0; i < middle; i++) {
    mid[i] = i;
  }
  for (int i = 0; i < middle; i++) {
    mid[i + middle] = middle - i;
  }
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += arr[i] * mid[i];
  }
  return sum;
}
void display(int arr[], int size) {
  for (int i = 0; i < size; i++) {
  }
}

bool scanIntersection(int num) {
  int intTop[camera_image.width - 1];
  int intBot[camera_image.width - 1];
  for (int col = 0; col <= camera_image.width - 1; col++) {
    int row = 0;
    Pixel pix = get_camera_pixel(row, col);
    if (((int)pix.r + (int)pix.g + (int)pix.b) / 3 < 30) {
      intTop[col] = 1;
    } else {
      intTop[col] = 0;
    }
    int row2 = camera_image.height;
    Pixel pix2 = get_camera_pixel(row2, col);
    if (((int)pix2.r + (int)pix2.g + (int)pix2.b) / 3 < 30) {
      intBot[col] = 1;
    } else {
      intBot[col] = 0;
    }
  }
  int top = checkIntersection(intTop, camera_image.width - 1);
  int bot = checkIntersection(intBot, camera_image.width - 1);
  int intLeft[camera_image.height - 1];
  int intRight[camera_image.height - 1];
  for (int row = 0; row <= camera_image.height; row++) {
    int col = 1;
    Pixel pixl = get_camera_pixel(row, col);
    if (((int)pixl.r + (int)pixl.g + (int)pixl.b) / 3 < 30) {
      intLeft[row] = 1;
    } else {
      intLeft[row] = 0;
    }
    int col2 = camera_image.width - 1;
    Pixel pixl2 = get_camera_pixel(row, col2);
    if (((int)pixl2.r + (int)pixl2.g + (int)pixl2.b) / 3 < 30) {
      intRight[row] = 1;
    } else {
      intRight[row] = 0;
    }
  }
  display(intLeft, camera_image.height - 1);
  int left = checkIntersection(intLeft, camera_image.height - 1);
  int right = checkIntersection(intRight, camera_image.height - 1);
  if (num == 1) {
    if (right > 200 && left < 1) {
      return true;
      std::cout << " left=" << right;
    }
  } else if (num == 2) {
    if (left > 250) {
      return true;
      std::cout << " right=" << left;
    }
  } else if (num == 3) {
    if (left > 250 && right < 1) {
      return true;
      std::cout << " right=" << left;
    }
  } else if (num == 4) {
    if (right > 200) {
      return true;
      std::cout << " right=" << left;
    }
  }
  return false;
}
void fixPosition() {
  if (abs(positionError()) > 200) {
    for (int i = 0; i < 12; i++) {
      if (positionError() > 0) {
        left(abs(positionError()) * 0.2);
      } else if (positionError() < 0) {
        right(abs(positionError()) * 0.2);
      }
      foward(0);
    }
  } else {
    for (int i = 0; i < 12; i++) {
      if (positionError() > 0) {
        left(abs(positionError()) * 0.15);
      } else if (positionError() < 0) {
        right(abs(positionError()) * 0.15);
      }
      foward(0);
    }
  }
}
void fullTurn() {
  for (int i = 0; i < 15; i++) {
    set_motors(10, 10);
    update_sim(200);
  }
  for (int i = 0; i < 10; i++) {
    set_motors(10, -10);
    update_sim(200);
  }
  fixPosition();
}
void turnLeft() {
  for (int i = 0; i < 15; i++) {
    set_motors(10, 10);
    update_sim(200);
  }
  set_motors(0, 0);
  update_sim(200);
  set_motors(20, -20);
  update_sim(200);
  set_motors(18, -18);
  update_sim(200);
  set_motors(0, 0);
  update_sim(400);
  fixPosition();
  update_sim(200);
}
void turnRight() {
  for (int i = 0; i < 12; i++) {
    set_motors(10, 10);
    update_sim(200);
  }
  set_motors(0, 0);
  update_sim(200);
  set_motors(-20, 20);
  update_sim(200);
  set_motors(-18, 18);
  update_sim(200);
  set_motors(0, 0);
  update_sim(400);
  fixPosition();
  update_sim(200);
}
void drive() {
  if (positionError() > 0) {
    left(abs(positionError()) * 0.15);
    foward(10);
    left(abs(positionError()) * 0.15);
  } else if (positionError() < 0) {
    right(abs(positionError()) * 0.15);
    foward(10);
    right(abs(positionError()) * 0.15);
  } else {
    foward(10);
  }
  foward(0);
}
void driveCore() {
  if (positionError() > 0) {
    left(abs(positionError()) * 0.2);
    foward(20);
  } else if (positionError() < 0) {
    right(abs(positionError()) * 0.2);
    foward(20);
  } else {
    foward(20);
  }
  foward(0);
}
int main() {
  std::cout << "start simulation..." << std::endl;
  init(110, 160, 15 * 3.14159 / 180.0);
  update_sim(300); // redraw everything and pause for 300 milliseconds
  bool core = true;
  bool completion = false;
  bool challenge = false;
  while (true) {
    if (hasPath()) {
      if (core) {
        if (startCompleation()) {
          core = false;
          completion = true;
          fixPosition();
        } else {
          driveCore();
        }
      } else if (completion) {
        if (scanIntersection(1)) {
          turnLeft();
        } else if (scanIntersection(2)) {
          turnRight();
        } else {
          drive();
        }
        if (startChallenge()) {
          challenge = true;
          completion = false;
          fixPosition();
          backwards(-50);
          fixPosition();
        }
      } else if (challenge) {
        if (scanIntersection(3)) {
          turnRight();
        } else if (scanIntersection(4)) {
          turnLeft();
        } else {
          drive();
        }
        if (finish()) {
          for (int i = 0; i < 12; i++) {
            set_motors(10, 10);
            update_sim(200);
          }
          return 0;
        }
      }
    } else {
      if (core) {
        backwards(-10);
      } else {
        fullTurn();
      }
    }
  }
}
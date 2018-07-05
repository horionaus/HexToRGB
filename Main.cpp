// Copyright 2018 Z. Beaugelin, G. Jalili, H. Lanoix

#include <mbed.h>
#include <iostream>
#include <vector>
#include <pindef.h>

using std::pow;
using std::string;
using std::vector;

DigitalOut led_r(PB_10);
DigitalOut led_g(PA_8);
DigitalOut led_b(PA_9);

Serial pc(USBTX, USBRX);

int HexadecimalToDecimal(string hex) {
  int hexLength = hex.length();
  double dec = 0;

  for (int i = 0; i < hexLength; ++i) {
    char b = hex[i];

    if (b >= 48 && b <= 57)
      b -= 48;
    else if (b >= 65 && b <= 70)
      b -= 55;

    dec += b * std::pow(16.0, static_cast<double>((hexLength - i) - 1));
  }
  return (static_cast<int>(dec));
}

vector<int> HexadecimalToRGB(string hex) {
  vector<int> ColorVec;
  ColorVec.push_back(hex[0] -48);
  hex.erase(0, 2);
  ColorVec.push_back(HexadecimalToDecimal(hex.substr(0, 2)));
  ColorVec.push_back(HexadecimalToDecimal(hex.substr(2, 2)));
  ColorVec.push_back(HexadecimalToDecimal(hex.substr(4, 2)));
  return (ColorVec);
}

int main() {
  pc.baud(9600);
  char str[8];
  for (;;) {
    //if (pc.readable())
    while(char c = pc.getc()) !
    //pc.gets(str, 8);
    vector<int> v;
    v = HexadecimalToRGB("1#0d98ba");
    if (v[0]) {
      led_r = v[1] / 255;
      led_g = v[2] / 255;
      led_b = v[3] / 255;
    } else {
      led_r = 0;
      led_g = 0;
      led_b = 0;
    }
  }
}

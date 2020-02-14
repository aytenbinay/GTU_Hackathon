void readColor() {
  tcs.getRawData(&r, &g, &b, &c);
  average = (r + g + b) / 3; // renk değerlerini topla ve ortalamasını al
  red = r / average; // kırmızı renk değeri oranı
  green = g / average; // yeşil renk değeri oranı
  blue = b / average;

}

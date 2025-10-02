#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "third_party/stb/stb_image.h"

void decode_steganography(int image_data[], int data_size, std::string key) {
    int currentIndex = 1000;          
    if (key.empty() || currentIndex < 0 || currentIndex >= data_size) return;

    std::size_t kpos = 0;
    const std::size_t klen = key.size();

    while (true) {
       
        unsigned char step = static_cast<unsigned char>(key[kpos]);
        if (step == 0) break; // avoid infinite loop if key contains '\0'
        currentIndex += static_cast<int>(step);

       
        if (currentIndex < 0 || currentIndex >= data_size) break;

      
        int v = image_data[currentIndex];
        if (v == 0) break;  // stop on null terminator

       
        std::cout << static_cast<char>(v);

      
        kpos = (kpos + 1) % klen;
    }
}



int main() {
    const char* image_path = "secret.png";
    int width, height, channels;

    unsigned char* img_data_char = stbi_load(image_path, &width, &height, &channels, 1);

    int data_size = width * height;

    int* image_data_int = new int[data_size];
    for (int i = 0; i < data_size; ++i) {
        image_data_int[i] = (int)img_data_char[i];
    }

    stbi_image_free(img_data_char);

    std::string user_key;
    std::cout << "Of the four pillars of OOP, what is the principle of separating interface and implementation? (First letter capitalized): ";
    std::cin >> user_key;

    std::cout << "------------------------------------------" << std::endl;
    decode_steganography(image_data_int, data_size, user_key);
    std::cout << "\n------------------------------------------" << std::endl;

    delete[] image_data_int;

    return 0;
}

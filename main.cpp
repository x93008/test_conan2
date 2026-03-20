#include <zip.h>
#include <iostream>

int main() {
    int err = 0;
    zip_t* zip = zip_open("test.zip", ZIP_CREATE, &err);
    if (zip) {
        std::cout << "libzip version: " << zip_libzip_version() << std::endl;
        zip_close(zip);
    } else {
        std::cout << "Failed to create zip file, error: " << err << std::endl;
    }
    return 0;
}

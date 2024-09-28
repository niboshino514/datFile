#include <iostream>
#include <fstream>
#include <cstring>

// 汎用的なバイナリ書き込み関数
template <typename T>
void writeBinaryFile(const std::string& filename, const T& data) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "ファイルを開けませんでした: " << filename << std::endl;
        return;
    }
    outFile.write(reinterpret_cast<const char*>(&data), sizeof(T));
    outFile.close();
}

// 汎用的なバイナリ読み込み関数
template <typename T>
void readBinaryFile(const std::string& filename, T& data) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "ファイルを開けませんでした: " << filename << std::endl;
        return;
    }
    inFile.read(reinterpret_cast<char*>(&data), sizeof(T));
    inFile.close();
}

enum ID
{
	ID_A = 1,
	ID_B = 2,
	ID_C = 3
};


// 例として使用する構造体
struct MyStruct {
    ID id;
    float value;
    char name[20];
};

int main() {
    // データの作成
    MyStruct myData = { ID(2), 3.14f, "example"};

    // バイナリファイルに書き込む
    writeBinaryFile("data.dat", myData);

    // データを読み込むための新しいインスタンス
    MyStruct readData;

    // バイナリファイルから読み込む
    readBinaryFile("data.dat", readData);

    // 読み込んだデータの表示
    std::cout << "ID: " << readData.id << std::endl;
    std::cout << "Value: " << readData.value << std::endl;
    std::cout << "Name: " << readData.name << std::endl;

    return 0;
}

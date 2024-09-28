#include <iostream>
#include <fstream>
#include <cstring>

// �ėp�I�ȃo�C�i���������݊֐�
template <typename T>
void writeBinaryFile(const std::string& filename, const T& data) {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "�t�@�C�����J���܂���ł���: " << filename << std::endl;
        return;
    }
    outFile.write(reinterpret_cast<const char*>(&data), sizeof(T));
    outFile.close();
}

// �ėp�I�ȃo�C�i���ǂݍ��݊֐�
template <typename T>
void readBinaryFile(const std::string& filename, T& data) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "�t�@�C�����J���܂���ł���: " << filename << std::endl;
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


// ��Ƃ��Ďg�p����\����
struct MyStruct {
    ID id;
    float value;
    char name[20];
};

int main() {
    // �f�[�^�̍쐬
    MyStruct myData = { ID(2), 3.14f, "example"};

    // �o�C�i���t�@�C���ɏ�������
    writeBinaryFile("data.dat", myData);

    // �f�[�^��ǂݍ��ނ��߂̐V�����C���X�^���X
    MyStruct readData;

    // �o�C�i���t�@�C������ǂݍ���
    readBinaryFile("data.dat", readData);

    // �ǂݍ��񂾃f�[�^�̕\��
    std::cout << "ID: " << readData.id << std::endl;
    std::cout << "Value: " << readData.value << std::endl;
    std::cout << "Name: " << readData.name << std::endl;

    return 0;
}

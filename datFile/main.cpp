#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>  // typeid���g�����߂ɕK�v

/// <summary>
/// �^����v���Ă��邩�ǂ����𔻒肷��
/// </summary>
/// <typeparam name="T">���ׂ�ϐ�</typeparam>
/// <typeparam name="U">�^</typeparam>
/// <returns></returns>
template <typename T, typename U>
bool IsSameType(const U& value) 
{
    // typeid���g���Č^�𒲂ׂ�
    return std::is_same<T, U>::value;
}

template <typename T>
void Create(const std::string& filename, const std::vector<T>& dataList)
{
    // �o�C�i�����[�h�Ńt�@�C�����J��
    std::ofstream outFile(filename, std::ios::out | std::ios::binary);

    if (!outFile)
    {
        std::cerr << "�t�@�C�����J�����Ƃ��ł��܂���ł����B" << std::endl;
        return;
    }

    for (const auto& data : dataList)
    {
        // �e�����o�[�ϐ�������
        outFile.write(reinterpret_cast<const char*>(&data.id), sizeof(data.id));

        // ������̒�������������
        size_t nameLength = data.name.size();
        outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));

        // �����񎩑̂���������
        outFile.write(data.name.c_str(), nameLength);
    }

    outFile.close();
    std::cout << "�o�C�i���f�[�^�� " << filename << " �t�@�C���ɏ������܂�܂����B" << std::endl;
}

template <typename T>
auto Load(const std::string& filename) -> std::vector<T>
{
    std::ifstream inFile(filename, std::ios::binary);
    std::vector<T> dataList;

    if (!inFile) {
        std::cerr << "�t�@�C�����J���܂���ł����B" << std::endl;
        return dataList;
    }

    while (true) 
    {
        T data;

        // �e�����o�[�ϐ���ǂݍ���
        if (!inFile.read(reinterpret_cast<char*>(&data.id), sizeof(data.id))) break;

        // ������̒�����ǂݍ���
        size_t nameLength;
        if (!inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength))) break;

        // �����񎩑̂�ǂݍ���
        std::vector<char> nameBuffer(nameLength);
        inFile.read(nameBuffer.data(), nameLength);
        data.name.assign(nameBuffer.begin(), nameBuffer.end());

        dataList.push_back(data);
    }

    inFile.close();
    std::cout << "�o�C�i���`����dat�t�@�C���𐳏�ɓǂݍ��݂܂����B" << std::endl;

    return dataList;
}


struct Data
{
    int id = 0;
    std::string name;
};

int main()
{
    // �t�@�C����
    const std::string filename = "output_binary.dat";

    // �f�[�^���쐬
    std::vector<Data> dataList =
    {
        {0, "������"},
        {1, "���Ƃ�"}
    };

    // �o�C�i���f�[�^���쐬
    Create(filename, dataList);

    // �o�C�i���f�[�^��ǂݍ���
    auto loadedDataList = Load<Data>(filename);

    // �ǂݍ��񂾃f�[�^��\��
    for (const auto& data : loadedDataList)
    {
        std::cout << "ID: " << data.id << "\n";
        std::cout << "���O: " << data.name << "\n";
    }

    return 0;
}
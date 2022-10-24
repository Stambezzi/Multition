#include <iostream>
#include <map>

class CLightingDeviceData
{
public:
    CLightingDeviceData() : fNumberOfChannels(0), fDmxAddress("") {};
    CLightingDeviceData(int channels, const std::string& dmxAddress)
    {
        fNumberOfChannels = channels;
        fDmxAddress = dmxAddress;
    }

    void SetNumberOfChannels(int numChannels)
    {
        fNumberOfChannels = numChannels;
    }

    void SetDmxAddress(const std::string& dmxAddress)
    {
        fDmxAddress = dmxAddress;
    }

    friend std::ostream& operator<<(std::ostream& os, const CLightingDeviceData& data)
    {
        return os << "Number of cahnnels: " << data.fNumberOfChannels << " DMX Address: " << data.fDmxAddress << "\n";
    }

private:
    int fNumberOfChannels;
    std::string fDmxAddress;
};

using Uuid = int;

class CMultitonDatabase
{
public:
    CMultitonDatabase(const CMultitonDatabase& other) = delete;
    CMultitonDatabase operator=(const CMultitonDatabase& other) = delete;

    static CMultitonDatabase& GetInstance()
    {
        static CMultitonDatabase db;
        return db;
    }

    std::shared_ptr<CLightingDeviceData> GetDataForDevice(Uuid uuid)
    {
        std::shared_ptr<CLightingDeviceData> result = nullptr;

        if ( fUuidToData.find(uuid) != fUuidToData.end() )
        {
            result = fUuidToData[uuid];
        }
        else
        {
            result = std::make_shared<CLightingDeviceData>();
        }

        return result;
    }

private:
    CMultitonDatabase()
    {
        std::cout << "Initialization\n";
        this->InitializeDummyDatabase();
    }

    void InitializeDummyDatabase()
    {
        fUuidToData = {
            {1, std::make_shared<CLightingDeviceData>(5, "123/1")},
            {2, std::make_shared<CLightingDeviceData>(5, "128/1")},
            {3, std::make_shared<CLightingDeviceData>(5, "133/1")},
            {4, std::make_shared<CLightingDeviceData>(5, "138/1")}
        };
    }

    std::map<Uuid, std::shared_ptr<CLightingDeviceData>> fUuidToData;
};

int main()
{
    std::cout << *CMultitonDatabase::GetInstance().GetDataForDevice(1);
    std::cout << *CMultitonDatabase::GetInstance().GetDataForDevice(2);
    std::cout << *CMultitonDatabase::GetInstance().GetDataForDevice(3);
    std::cout << *CMultitonDatabase::GetInstance().GetDataForDevice(4);

    std::shared_ptr<CLightingDeviceData> second = CMultitonDatabase::GetInstance().GetDataForDevice(2);
    second.get()->SetDmxAddress("128/2");
    std::cout << *CMultitonDatabase::GetInstance().GetDataForDevice(2);

    std::cout << *CMultitonDatabase::GetInstance().GetDataForDevice(5);
}
#include <iostream>
#include <string>
#include <memory>
#include <random>

using namespace std;

class CloudStorage
{
public:
    virtual bool uploadContents(const string &content) = 0;
    virtual int getFreeSpace() = 0;
    virtual ~CloudStorage() = default;
};

class CloudDrive : public CloudStorage
{
public:
    bool uploadContents(const string& content) override
    {
        cout << "Uploading " << content.length() << " bytes to CloudDrive: " << endl;
        return true;
    }

    int getFreeSpace() override
    {
        // Generate a random number for free space (0-20 GB)
        static random_device rd; // Obtain a random number from hardware
        static mt19937 eng(rd()); // Seed the generator
        uniform_int_distribution<> distr(0, 20); // Define the range

        const int size = distr(eng);
        cout << "Available CloudDrive storage: " << size << "GB" << endl;
        return size;
    }
};

class FastShare : public CloudStorage
{
public:
    bool uploadContents(const string& content) override
    {
        cout << "Uploading " << content.length() << " bytes to FastShare: " << endl;
        return true;
    }

    int getFreeSpace() override
    {
        // Generate a random number for free space (0-10 GB)
        static random_device rd; // Obtain a random number from hardware
        static mt19937 eng(rd()); // Seed the generator
        uniform_int_distribution<> distr(0, 10); // Define the range

        const int size = distr(eng);
        cout << "Available FastShare storage: " << size << "GB" << endl;
        return size;
    }
};

// 3rd party service
class VirtualDrive
{
public:
    bool uploadData(const string& data, const int uniqueID)
    {
        cout << "Uploading to VirtualDrive: \"" << data << "\" ID: " << uniqueID << endl;
        return true;
    }
    int usedSpace()
    {
        // Generate a random number for used space (0-10 GB)
        static random_device rd;
        static mt19937 eng(rd());
        uniform_int_distribution<> distr(0, 10);

        return distr(eng);
    }
    const int totalSpace = 15;
};

int main()
{
    // Use a vector to store unique_ptr to CloudStorage objects
    vector<unique_ptr<CloudStorage>> cloudServices;
    cloudServices.push_back(make_unique<CloudDrive>());
    cloudServices.push_back(make_unique<FastShare>());

    // Iterate through the vector and invoke the uploadContents and getFreeSpace methods on each object.
    const string content = "Beam me up, Scotty!";
    for (const auto &service : cloudServices)
    {        
        service->uploadContents(content);
        service->getFreeSpace();
        cout << endl;
    }

    return 0;
}
